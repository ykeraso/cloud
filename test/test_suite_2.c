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

void clear_test_suite_2(){
	return;
}

/**
 * Test cases
 */

int test_suite_2(){
	init_test_suite_2();

	clear_test_suite_2();
	return suite_eval();

}
