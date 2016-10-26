#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "result_codes.h"
#include "log.h"

#include "List.h"


/**
 * Local functions
 */
Result assign(node_t *target, node_t source){
	TRACE_IN
	if ( (target->service_name = malloc(strlen(source.service_name)+1)) != NULL ){
		memset(target->service_name, 0, strlen(source.service_name)+1 );
		strcpy(target->service_name, source.service_name);
		target->data_ptr = source.data_ptr;
		TRACE_OUT
		return Success;
	}
	LOG("malloc failed")
	TRACE_OUT
	return Memory_Failure;
}

Boolean is_empty_list(List_t ls){
	TRACE_IN
	if ( ls.number_of_data == 0 ){
		TRACE_OUT
		return True;
	}
	TRACE_OUT
	return False;
}

Boolean is_out_of_bounds_list(List_t ls){
	TRACE_IN
	if ( ls.point != NULL )
	if ( ls.point - ls.data > (ls.number_of_data-1)*sizeof(node_t) ){
		TRACE_OUT
		ls.point = NULL;
		return True;
	}
	TRACE_OUT
	return False;
}

void clean_node(node_t node)
{
	TRACE_IN
	free(node.service_name);
	TRACE_OUT
}


/**
 *  Creates List (initialize list struct)
 */
List_t List_create(){
	TRACE_IN
	List_t ret;

	ret.number_of_data = 0;
	ret.data = NULL;
	ret.point = NULL;

	TRACE_OUT
	return ret;
}

void List_destroy(List_t *ls){
	TRACE_IN
	if ( ls -> data != NULL){
		int i;
		for ( i = 0; i < ls->number_of_data; i++)
			clean_node( *( (node_t*)ls->data + i ) );
		free(ls->data);
	}
	ls -> data = NULL;
	ls -> point = NULL;
	ls -> number_of_data = 0;
	TRACE_OUT
}


Result List_insert(List_t *ls, node_t node_data){
	TRACE_IN
	if ( is_out_of_bounds_list(*ls) )LOG("List out of bounds")
	if ( ls->number_of_data % interval == 0 ){
		if ( ls->number_of_data == 0){
			LOG("memory allocate 1st interval")
			if ( (ls->data = malloc(interval*sizeof(node_t))) == NULL ){
				LOG("malloc failed");
				TRACE_OUT
				return Memory_Failure;
			}
		}else{
			LOG("memory reallocate intervals")
			if ( (ls->point = realloc( ls->point, (ls->number_of_data+interval) * sizeof(node_t))) == NULL ){
				LOG("realloc failed")
				TRACE_OUT
				return Memory_Failure;
			}
		}
	}
	if ( ls->point == NULL ){
		LOG("Add data at the end. ls->point == NULL");
		if ( assign( (node_t *)(ls->data + ls->number_of_data*sizeof(node_t) ), node_data) == Memory_Failure){
			TRACE_OUT
			return Memory_Failure;
		}
		ls ->number_of_data += 1;
		TRACE_OUT
		return Success;
	}else{
		LOG("End data at point. ls->point != NULL");
		memcpy(ls->point+sizeof(node_t),
			   ls->point,
               ls->data + ls->number_of_data*sizeof(void *) - ls->point - sizeof(void*) );
		assign( (node_t*)(ls->point), node_data);
	}
	TRACE_OUT
	return Success;
}

Result List_insert_first(List_t *ls, node_t node){

	return Success;
}

Result List_insert_last(List_t *ls, node_t node){
	return Success;
}

/**
 * List show procedyres
 */
Result List_show(List_t ls, node_t *node)
{
	TRACE_IN
	if ( is_out_of_bounds_list(ls) ){
		TRACE_OUT
		return List_out_of_bounds;
	}
	if ( is_empty_list(ls) ){
		TRACE_OUT
		return Empty_list;
	}
	if ( ls.point == NULL){
		*node = *(node_t*)(ls.data + (ls.number_of_data - 1)*sizeof(node_t) );
LOG("delete this line")
printf("%s - %ld\n", node->service_name, (long)node->data_ptr);
		TRACE_OUT
		return Success;
	}else{
		*node = *(node_t*)ls.point;
		TRACE_OUT
		return Success;
	}
	return Success;
}

Result List_show_first(List_t ls, node_t *node){
	TRACE_IN
	if ( is_empty_list(ls) )return Empty_list;
	*node = *(node_t*)(ls.data);;
	TRACE_OUT
	return Success;
}

Result List_show_last(List_t ls, node_t *node){
	TRACE_IN
	if ( is_empty_list(ls) )return Empty_list;
	*node = *(node_t*)(ls.data + (ls.number_of_data - 1)*sizeof(node_t) );
	printf("%s - %ld\n", node->service_name, (long)node->data_ptr);
	TRACE_OUT
	return Success;
}

Result List_delete(List_t *ls, const char *service_name, node_t *node){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	TRACE_OUT
	return Success;
}

Result List_delete_first(List_t *ls, node_t *node){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	TRACE_OUT
	return Success;
}

Result List_delete_last(List_t *ls, node_t *node){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	TRACE_OUT
	return Success;
}

Result List_first(List_t *ls){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	ls->point = ls->data;
	TRACE_OUT
	return Success;
}

Result List_last(List_t *ls){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	ls->point = ls->data + (ls->number_of_data - 1)*sizeof(node_t);
	TRACE_OUT
	return Success;
}

Result List_next(List_t *ls){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	if ( ls->point == NULL ){
		LOG("point at begin")
		ls->point = ls->data;
		TRACE_OUT
		return Success;
	}
	ls->point += sizeof(node_t);
	if (ls->point - ls->data == ls->number_of_data * sizeof(node_t) ){
		LOG("List at end")
		ls->point = ls->data;
		TRACE_OUT
		return Rewind_list;
	}
	TRACE_OUT
	return Success;
}

Result List_previous(List_t *ls){
	TRACE_IN
	if ( is_empty_list(*ls) )return Empty_list;
	if ( ls->point == NULL ){
		LOG("point at end")
		ls->point = ls->data;
		TRACE_OUT
		return Success;
	}
	if ( ls->data == ls->point ){
		ls->point = ls->data + (ls->number_of_data - 1)*sizeof(node_t);
		TRACE_OUT
		return Rewind_list;
	}
	ls->point -= sizeof(node_t);
	TRACE_OUT
	return Success;
}

