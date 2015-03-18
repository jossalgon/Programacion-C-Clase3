#include "concesionario.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
	struct coche *c1;
	struct concesionario *con;
	char info[4000];

	c1 = curso_coche_alloc();
	con = curso_concesionario_alloc();

	int val = 0, option_index = 0;
	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm' },
		{ "id", required_argument, 0, 'i' },
		{ "gama", required_argument, 0, 'g' },
		{ "dueno", required_argument, 0, 'd' },
		{ "help", optional_argument, 0, 'h' },
		{ 0 }
	};

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
					   c1);

	if (val == -1)
		return val;

	while (val != -1){

		switch (val) {
		case 'm':
			curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA, optarg);
			break;
		case 'i':
			curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID, atoi(optarg));
			break;
		case 'g':
			curso_coche_attr_set_str(c1,
				CURSO_COCHE_ATTR_MARCA, optarg);
			break;
		case 'd':
			curso_concesionario_attr_set_str(con,
				CURSO_CONCESIONARIO_ATTR_DUENO, optarg);
			break;
		case 'h':
			printf("Uso: nombrePrograma [-m/--matricula] [-i/--id]"
				" [-g/--gama] [-d/--dueno] o [-h/--help]\n\n"
				"m -> matrícula de nuestro vehículo\n"
				"i -> id de nuestro coche\n"
				"g -> gama o marca del vehículo\n"
				"d -> dueño del concesionario\n"
				"h -> Ayuda con el uso correcto del programa"
					" y los parámetros aceptados\n");
			return 0;
		case 0:
			break;
		default:
			printf("Debe usar el parametro -m/--matricula, -i/--id"
			       " -g/--gama, -d/--dueno o -h\n");
			return -1;
		}
		val = getopt_long(argc, argv, "m:i:g:d:h:", long_options,
			&option_index);
	}

	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);

	return 0;
}
