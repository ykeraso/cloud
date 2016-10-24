#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "result_codes.h"
#include "log.h"

#include "List.h"

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
	if ( ls -> data != NULL)free(ls->data);
	ls -> data = NULL;
	ls -> point = NULL;
	ls -> number_of_data = 0;
	TRACE_OUT
}


Result List_insert(List_t *ls, node_t *node_data_p){
	TRACE_IN
	if ( (ls->point-ls->data) / sizeof(void *)  > ls->number_of_data){
		ls->point = NULL;
		LOG("List out of bounds")
	}

	if ( ls->number_of_data % interval == 0 ){
		if ( ls->number_of_data == 0){
			if ( (ls->data = malloc(interval*sizeof(node_t))) == NULL ){
				LOG("malloc failed");
				TRACE_OUT
				return Memory_Failure;
			}
		}else{
			if ( (ls->point = realloc( ls->point, (ls->number_of_data+interval) * sizeof(node_t))) == NULL ){
				LOG("realloc failed")
				TRACE_OUT
				return Memory_Failure;
			}
		}
	}
	if ( ls->point == NULL ){
		LOG("End data at the end. ls->point == NULL");
		*(node_t**)(ls->data + ls->number_of_data) = node_data_p;
		ls ->number_of_data += 1;
		TRACE_OUT
		return Success;
	}else{
		LOG("End data at point. ls->point != NULL");
		memcpy(ls->point+1,
			   ls->point,
               ls->data + ls->number_of_data*sizeof(void *) - ls->point - sizeof(void*) );
		*(ls->point) = node_data_p;
	}
	TRACE_OUT
	return Success;
}

Result List_insert_first(List_t *ls, node_t node);
Result List_insert_last(List_t *ls, node_t node);

Result List_show(List_t ls, node_t *node)
{
	TRACE_IN
	if ( (ls.point-ls.data) > ls.number_of_data*sizeof(void**)){
		ls.point = NULL;
		LOG("List out of bounds")
		TRACE_OUT
		return List_out_of_bounds;
	}
	if ( ls.number_of_data == 0 ){
		TRACE_OUT
		return Empty_list;
	}
	if ( ls.point == NULL){
		node = *(ls.data + ls.number_of_data - 1);
		TRACE_OUT
		return Success;
	}else{
		node = *(ls.point);
		TRACE_OUT
		return Success;
	}
	return Success;
}

Result List_show_first(List_t ls, node_t *node){
	TRACE_IN
	TRACE_OUT
	return Success;
}

Result List_show_last(List_t ls, node_t *node){
	TRACE_IN
	TRACE_OUT
	return Success;

}

