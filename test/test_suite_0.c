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

void init_test_suite_0(){
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

void clear_test_suite_0(){
	int i;
	for ( i = 0; i < num_data; i++){
		free( (data+i)->service_name);
	}
	free(data);
	return;
}


int test_suite_0(){
	init_test_suite_0();

	node_t l_data;
	/*1. Create list. List is empty, list show and list delete returns the same cause */
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

	/* Insert one data. List show returns the correct */
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

	/* Insert 2nd data. List show returns the correct */
	TEST(testnum++, "List show in 2 data returns correctly", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List show first in 2 data returns correctly", List_show_first(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show last in 2 data returns correctly", List_show_last(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );

	/* Insert 3rd data. List show returns the correct */
	TEST(testnum++, "List insert increases sizeof list",
			List_insert(&ls, *(data+4) ) == Success AND ls.number_of_data == 3);

	TEST(testnum++, "List show in 2 data returns correctly", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List show first in 2 data returns correctly", List_show_first(ls, &l_data) == Success
			AND l_data.data_ptr == data->data_ptr AND strcmp(l_data.service_name, data->service_name) == 0 );
	TEST(testnum++, "List show last in 2 data returns correctly", List_show_last(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );

	/* List first and list next works ok */
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

	/* List previous and list last works ok  for the 3 data */
	TEST(testnum++, "List last returns Success", List_last(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data +4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List previous returns Success", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List previous returns Success", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data)->data_ptr AND strcmp(l_data.service_name, (data)->service_name) == 0 );
	TEST(testnum++, "List previous returns Rewind_list", List_previous(&ls) == Rewind_list);
	TEST(testnum++, "List show shows 3rd", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );


	/* List insert first and list first, next, last previous works ok */
	TEST(testnum++, "List insert (6) increases sizeof list",
			List_insert_first(&ls, *(data+6) ) == Success AND ls.number_of_data == 4);
	TEST(testnum++, "List first returns Success", List_first(&ls) == Success);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List next returns Rewind_list", List_next(&ls) == Rewind_list);
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
/* Data here : 8 -> 6 -> 0 -> 2 -> 4 -> 10 */
	TEST(testnum++, "List insert (8) increases sizeof list",
			List_insert_first(&ls, *(data+8) ) == Success AND ls.number_of_data == 5);
	TEST(testnum++, "List insert_last (10) increases sizeof list",
			List_insert_last(&ls, *(data+10) ) == Success AND ls.number_of_data == 6);

	TEST(testnum++, "List last returns Success", List_last(&ls) == Success);
	TEST(testnum++, "List show shows last (10) data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data + 10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	TEST(testnum++, "List previous returns Success", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	TEST(testnum++, "List previous returns Success", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	TEST(testnum++, "List previous returns Rewind_list", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 2nd", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data)->data_ptr AND strcmp(l_data.service_name, (data)->service_name) == 0 );
	TEST(testnum++, "List previous returns Rewind_list", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	TEST(testnum++, "List previous returns Success", List_previous(&ls) == Success);
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	TEST(testnum++, "List previous returns Rewind_list", List_previous(&ls) == Rewind_list);
	TEST(testnum++, "List show shows 5th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 * At this point : 8 -> 6 -> 0 -> 2 -> 4 -> 10
	 */
	List_first(&ls);
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 *  List insert data : 8 -> 9 -> 6 -> 0 -> 2 -> 4 -> 10
	 */
	List_first(&ls);
	TEST(testnum++, "List insert (8 -> 9) increases sizeof list",
			List_insert(&ls, *(data+9) ) == Success AND ls.number_of_data == 7);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 4th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 *  List insert data : 8 -> 9 -> 6 -> 7 -> 0 -> 2 -> 4 -> 10
	 */

	List_first(&ls);
	List_next(&ls);
	List_next(&ls);
	TEST(testnum++, "List insert (6 -> 7) increases sizeof list",
			List_insert(&ls, *(data+7) ) == Success AND ls.number_of_data == 8);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 5th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	TEST(testnum++, "List next returns Success", List_next(&ls) == Success);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 *  List insert data : 8 -> 9 -> 6 -> 7 -> 0 -> 1 -> 2 -> 4 -> 10
	 */

	List_first(&ls);
	int i;
	for ( i = 0; i < 4; i++)
	List_next(&ls);
	TEST(testnum++, "List insert (0 -> 1) increases sizeof list",
			List_insert(&ls, *(data+1) ) == Success AND ls.number_of_data == 9);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+1)->data_ptr AND strcmp(l_data.service_name, (data+1)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 9th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 *  List insert data : 8 -> 9 -> 6 -> 7 -> 0 -> 1 -> 2 -> 3 -> 4 -> 10
	 */

	List_first(&ls);
	for ( i = 0; i < 6; i++)
	List_next(&ls);
	TEST(testnum++, "List insert (2 -> 3) increases sizeof list",
			List_insert(&ls, *(data+3) ) == Success AND ls.number_of_data == 10
			);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+1)->data_ptr AND strcmp(l_data.service_name, (data+1)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+3)->data_ptr AND strcmp(l_data.service_name, (data+3)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 9th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 10th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	/**
	 *  List insert data : 8 -> 9 -> 6 -> 7 -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 10
	 */

	List_first(&ls);
	for ( i = 0; i < 8; i++)
	List_next(&ls);
	TEST(testnum++, "List insert (4 -> 5) increases sizeof list",
			List_insert(&ls, *(data+5) ) == Success AND ls.number_of_data == 11	);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+1)->data_ptr AND strcmp(l_data.service_name, (data+1)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+3)->data_ptr AND strcmp(l_data.service_name, (data+3)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 9th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 10th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+5)->data_ptr AND strcmp(l_data.service_name, (data+5)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 11th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );

	TEST(testnum++, "List_delete return Success", List_delete(&ls, (data+10)->service_name, &l_data) == Success
			AND l_data.data_ptr == (data+10)->data_ptr AND strcmp(l_data.service_name, (data+10)->service_name) == 0 );
	free( l_data.service_name);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+0)->data_ptr AND strcmp(l_data.service_name, (data+0)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+1)->data_ptr AND strcmp(l_data.service_name, (data+1)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+3)->data_ptr AND strcmp(l_data.service_name, (data+3)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 9th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 10th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+5)->data_ptr AND strcmp(l_data.service_name, (data+5)->service_name) == 0 );
	TEST(testnum++, "List next returns rewind", List_next(&ls)== Rewind_list) ;
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );

	TEST(testnum++, "List_delete return Success", List_delete(&ls, (data)->service_name, &l_data) == Success
			AND l_data.data_ptr == (data)->data_ptr AND strcmp(l_data.service_name, (data)->service_name) == 0 );
	free( l_data.service_name);
	List_first(&ls);
	TEST(testnum++, "List show shows 1st data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 2nd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+9)->data_ptr AND strcmp(l_data.service_name, (data+9)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 3rd data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+6)->data_ptr AND strcmp(l_data.service_name, (data+6)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 4th data", List_show(ls, &l_data) == Success
				AND l_data.data_ptr == (data+7)->data_ptr AND strcmp(l_data.service_name, (data+7)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 5th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+1)->data_ptr AND strcmp(l_data.service_name, (data+1)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 6th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+2)->data_ptr AND strcmp(l_data.service_name, (data+2)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 7th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+3)->data_ptr AND strcmp(l_data.service_name, (data+3)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 8th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+4)->data_ptr AND strcmp(l_data.service_name, (data+4)->service_name) == 0 );
	List_next(&ls);
	TEST(testnum++, "List show shows 9th", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+5)->data_ptr AND strcmp(l_data.service_name, (data+5)->service_name) == 0 );
	TEST(testnum++, "List next returns rewind", List_next(&ls)== Rewind_list) ;
	TEST(testnum++, "List show shows 1st", List_show(ls, &l_data) == Success
			AND l_data.data_ptr == (data+8)->data_ptr AND strcmp(l_data.service_name, (data+8)->service_name) == 0 );

	TEST(testnum++, "List get data ptr returns correct value", List_get_data_ptr(ls, (data+8)->service_name) == 8);
	TEST(testnum++, "List get data ptr returns correct value", List_get_data_ptr(ls, (data+9)->service_name) == 9);
	TEST(testnum++, "List get data ptr returns correct value", List_get_data_ptr(ls, (data+6)->service_name) == 6);
	TEST(testnum++, "List get data ptr returns correct value", List_get_data_ptr(ls, (data+7)->service_name) == 7);
	TEST(testnum++, "List get data ptr returns correct value", List_get_data_ptr(ls, (data+4)->service_name) == 4);


	List_destroy(&ls);

	TEST(testnum++, "List_destroy() sets num of data = 0, ret point = NULL, ret data == NULL",
			ls.number_of_data == 0 AND ls.point == NULL AND ls.data == NULL);



	clear_test_suite_0();
	return suite_eval();

}
