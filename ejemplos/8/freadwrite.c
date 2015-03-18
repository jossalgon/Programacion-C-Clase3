#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char c[] = "ejemplo fwrite/fread";
	char buffer[20];

	fp = fopen("datos.dat", "w+");
	if (fp == NULL)
		return -1;

	if ((fwrite(c, strlen(c) + 1, 1, fp)) != 1)
		return -1;

	rewind(fp);

	if ((fread(buffer, strlen(c) + 1, 1, fp)) != 1)
		return -1;

	printf("%s\n", buffer);

	if (fclose(fp))
		return -1;

	return 0;
}
