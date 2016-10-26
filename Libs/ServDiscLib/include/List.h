#include "result_codes.h"

#ifndef __LIST__
#define __LIST__

#define interval 10

typedef
struct _Snode{
		char *service_name;
		void *data_ptr;
	} node_t;

typedef
struct _Slist{
	unsigned short number_of_data;
	void *point;
	void *data;


}List_t;

List_t List_create();
void List_destroy(List_t *ls);

Result List_insert(List_t *ls, node_t node);
Result List_insert_first(List_t *ls, node_t node);
Result List_insert_last(List_t *ls, node_t node);

Result List_delete(List_t *ls, const char *service_name, node_t *node);
Result List_delete_first(List_t *ls, node_t *node);
Result List_delete_last(List_t *ls, node_t *node);

Result List_show(List_t ls, node_t *node);
Result List_show_first(List_t ls, node_t *node);
Result List_show_last(List_t ls, node_t *node);

Result List_first(List_t *ls);
Result List_last(List_t *ls);
Result List_next(List_t *ls);
Result List_previous(List_t *ls);


void *List_get_data_ptr(List_t ls,const char *service_name);


#endif
