/**
 * Standard libs
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Unit test definitions
 */
#include "unimacros.h"
#include "testsuitedef.h"

/**
 *  Definition files for function to be tested
 */
#include "../Libs/ServDiscLib/include/List.h"


int testnum;

node_t *data;
int num_data = 14;
node_t node_data;

void init_test_suite(){
	LOGO("test_suite_0 : The scope is to test list functions");
	init_suite_eval();
	int i;
	data = malloc(num_data*sizeof(node_t));
	for( i = 0; i < num_data; i++){
		(data+i)->service_name = malloc(10);
		sprintf( (data+i)->service_name, "service%2x", i);
		(data+i)->data_ptr = (void*)i;
	}
	testnum = 1;
	return;
}

void clear_test_suite(){
	int i;
	for ( i = 0; i < 10; i++){
		free( (data+i)->service_name);
	}
	free(data);
	return;
}


int test_suite_0(){
	init_test_suite();
	List_t ls = List_create();
	TEST(testnum++, "List create returns num of data = 0, ret point = NULL, ret data == NULL",
			ls.number_of_data == 0 AND ls.point == NULL AND ls.data == NULL);
	TEST(testnum++, "List insert increases sizeof list",
			List_insert(&ls, data) == Success AND ls.number_of_data == 1);
	List_destroy(&ls);
	TEST(testnum++, "List_destroy() sets num of data = 0, ret point = NULL, ret data == NULL",
			ls.number_of_data == 0 AND ls.point == NULL AND ls.data == NULL);
	return suite_eval();

}
