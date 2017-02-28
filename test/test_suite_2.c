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
#include "../Libs/ParserLib/include/state_stack.h"
#include "../Libs/ParserLib/include/states.h"
#include "../Libs/ParserLib/include/transition.h"


int testnum;

void init_test_suite_2(){
	LOGO("test_suite_2 : The scope is to test transitions");
	init_suite_eval();
	testnum = 1;
	return;
}

/**
 * Test cases
 */
Result S2_test1(){
	State_stack_t st;
	return Transition(&st, None, Start_st);
}

Result S2_test2(){
	State_stack_t st;
	Result ret = Transition(&st, File, Start_st);
	StateStack_destroy(&st);
	return ret;
}

Result S2_test3(){
	State_stack_t st;
	Result ret;
	if ( (ret = Transition(&st, File, Start_st) ) != Success ){
		StateStack_destroy(&st);
		return ret;
	}
	if ( (ret = Transition(&st, File, Stop_st) ) != Success ){
		StateStack_destroy(&st);
		return ret;
	}
	StateStack_destroy(&st);
	return ret;
}


void clear_test_suite_2(){
	return;
}

/**
 * Test cases
 */

int test_suite_2(){
	init_test_suite_2();
	TEST(testnum++, "Failed to add a transition for no level", S2_test1() == Unknown_Failure);
	TEST(testnum++, "Successfully create a transition stack", S2_test2() == Unknown_Failure);
	clear_test_suite_2();
	return suite_eval();

}
