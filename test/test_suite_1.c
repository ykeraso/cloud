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
State_stack_t st;

void init_test_suite_1(){
	LOGO("test_suite_1 : The scope is to test State stack");
	init_suite_eval();
	testnum = 1;
	return;
}

void clear_test_suite_1(){
	return;
}

/**
 * Test cases
 */
Result S1_test1(){
	StateStack_push( &st, Start_st);
	if ( StateStack_show(st) == Start_st )return Success;
	else return Unknown_Failure;
}

Result S1_test2(){
	Result res;
	res = StateStack_push( &st, Attribute_st);
	if ( res != Success)return res;
	if ( StateStack_show(st) != Attribute_st )return Unknown_Failure;
	res = StateStack_pop(&st);
	if ( res != Success )return res;
	if ( StateStack_show(st) != Start_st )return Unknown_Failure;
	res = StateStack_pop(&st);
	if ( res != Success )return res;
	if ( StateStack_show(st) != None_st )return Unknown_Failure;
	return Success;
}


int test_suite_1(){
	init_test_suite_1();
	st = StateStack_create(File);
	TEST(testnum++, "StateStack_create returns an empty stack", st.l == File AND st.top == NULL);
	TEST(testnum++, "StateStack_show returns None_st", StateStack_show(st) == None_st);
	TEST(testnum++, "StateStack_pop returns Empty_stack", StateStack_pop(&st) == Empty_stack);
	TEST(testnum++, "Add correctly a state on stack", S1_test1() == Success);
	TEST(testnum++, "Add one more state on stack and pop 2 gives empty stack", S1_test2() == Success );
	clear_test_suite_1();
	return suite_eval();

}
