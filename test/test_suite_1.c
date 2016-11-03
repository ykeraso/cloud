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


int testnum;

void init_test_suite_1(){
	LOGO("test_suite_1 : The scope is to test State stack");
	init_suite_eval();
	testnum = 1;
	return;
}

void clear_test_suite_1(){
	return;
}


int test_suite_1(){
	init_test_suite_1();

	clear_test_suite_1();
	return suite_eval();

}
