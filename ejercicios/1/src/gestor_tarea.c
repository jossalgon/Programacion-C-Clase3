#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea {
	struct list_head	tareas;
	uint32_t		num_tareas;

	uint32_t 		flags;
};

struct gestor_tarea *gestor_tarea_alloc(void)
{
	struct gestor_tarea *g = malloc(sizeof(struct gestor_tarea));
	memset(g, 0, (sizeof(struct gestor_tarea)));

	if (g == NULL)
		return NULL;

	INIT_LIST_HEAD(&g->tareas);
	g->flags |= (1 << GESTOR_TAREA_ATTR_NUM_TAREAS);

	return g;
}

void gestor_tarea_free(struct gestor_tarea *g)
{
	int i;
	struct tarea *t, *tmp;

	list_for_each_entry_safe(t, tmp, &g->tareas, head) {
		list_del(&t->head);
		tarea_free(t);
	}

	xfree(g);
}

bool gestor_tarea_attr_is_set(const struct gestor_tarea *g, uint16_t attr)
{
	return g->flags & (1 << attr);
}

void gestor_tarea_attr_unset_tarea(struct gestor_tarea *g, uint32_t pos)
{
	int i = 0;
	struct tarea *t, *tmp;

	if (pos < 0 || pos >= g->num_tareas)
		return;

	list_for_each_entry_safe(t, tmp, &g->tareas, head) {
		if (i==pos) {
			list_del(&t->head);
			xfree(t);
			break;
		}

		i++;
	}

	g->num_tareas--;
}

void gestor_tarea_attr_set_tarea(struct gestor_tarea *g, struct tarea *t)
{
	if (g->num_tareas > 10)
		printf("No se admiten más tareas\n");
	else {
		struct gestor_tarea *g;
		struct tarea *t0;

		list_add(&t->head, &g->tareas);

		g->num_tareas++;

		g->flags |= (1 << GESTOR_TAREA_ATTR_TAREAS);
	}
}

struct tarea *gestor_tarea_attr_get_tarea(struct gestor_tarea *g, uint32_t pos)
{
	int i = 0;
	struct tarea *t;

	if (!(g->flags &(1 << GESTOR_TAREA_ATTR_TAREAS)))
		return NULL;

	list_for_each_entry(t, &g->tareas, head) {
		if (i == pos)
			break;

			i++;
	}

	return t;
}

int gestor_tarea_snprintf(char *buf, size_t size, struct gestor_tarea *g)
{
	int ret = 0;
	struct tarea *t;

	list_for_each_entry(t, &g->tareas, head) {
		ret += tarea_snprintf(buf + ret, size - ret, t);
		ret += snprintf(buf + ret, size - ret, "\n");
	}
	return ret;
}
