/**
 * Standard libs
 */
#include <stdio.h>

/**
 * Unit test definitions
 */
#include "unimacros.h"
#include "testsuitedef.h"

/**
 *  Definition files for function to be tested
 */


int testnum;

void init_test_suite(){
	LOGO("test_suite_0");
	init_suite_eval();
	testnum = 0;
}

void clear_test_suite(){
	return;
}

int test_suite_0(){
	init_test_suite();
	return suite_eval();
}
