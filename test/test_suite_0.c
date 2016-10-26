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
	for ( i = 0; i < num_data; i++){
		free( (data+i)->service_name);
	}
	free(data);
	return;
}


int test_suite_0(){
	init_test_suite();

	node_t l_data;
	List_t ls = List_create();
	TEST(testnum++, "List create returns num of data = 0, ret point = NULL, ret data == NULL",
			ls.number_of_data == 0 AND ls.point == NULL AND ls.data == NULL);

	TEST(testnum++, "List show returns Empty_list", List_show(ls, &node_data) == Empty_list);
	TEST(testnum++, "List show first returns Empty_list", List_show_first(ls, &node_data) == Empty_list);
	TEST(testnum++, "List show last returns Empty_list", List_show_last(ls, &node_data) == Empty_list);

	TEST(testnum++, "List delete returns Empty_list", List_delete(&ls, "service", &node_data) == Empty_list);
	TEST(testnum++, "List delete first returns Empty_list", List_delete_first(&ls, &node_data) == Empty_list);
	TEST(testnum++, "List delete last returns Empty_list", List_delete_last(&ls, &node_data) == Empty_list);

	TEST(testnum++, "List first returns Empty_list", List_first(&ls) == Empty_list);
	TEST(testnum++, "List last returns Empty_list", List_last(&ls) == Empty_list);
	TEST(testnum++, "List next  returns Empty_list", List_next(&ls) == Empty_list);
	TEST(testnum++, "List previous returns Empty_list", List_previous(&ls) == Empty_list);

	TEST(testnum++, "List insert increases sizeof list",
			List_insert(&ls, *data) == Success AND ls.number_of_data == 1);

	TEST(testnum++, "List show in one data returns correctly", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show in one data returns correctly", List_show_first(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show in one data returns correctly", List_show_last(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );

	TEST(testnum++, "List insert increases sizeof list",
			List_insert(&ls, *(data+2) ) == Success AND ls.number_of_data == 2);

	TEST(testnum++, "List show in 2 data returns correctly", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List show first in 2 data returns correctly", List_show_first(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show last in 2 data returns correctly", List_show_last(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );

	TEST(testnum++, "List insert increases sizeof list",
			List_insert(&ls, *(data+4) ) == Success AND ls.number_of_data == 3);

	TEST(testnum++, "List show in 2 data returns correctly", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List show first in 2 data returns correctly", List_show_first(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show last in 2 data returns correctly", List_show_last(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );

	TEST(testnum++, "List first returns Success", List_first(&ls) == Success);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List next returns Rewind_list", List_next(&ls) == Rewind_list);
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );

	List_destroy(&ls);

	TEST(testnum++, "List_destroy() sets num of data = 0, ret point = NULL, ret data == NULL",
			ls.number_of_data == 0 AND ls.point == NULL AND ls.data == NULL);



	clear_test_suite();
	return suite_eval();

}
