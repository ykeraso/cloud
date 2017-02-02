/**
 * Standard libs
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Project definitions
 */
#include "log.h"
#include "state_stack.h"
#include "transition.h"

/**
 * Transition tables
 */
#define __FILE_trs_max 2
__trs __FILE_trs[] = {
		{Blank_st, Start_st},
		{Start_st, Stop_st}
};


#define __LINE_trs_max 6
__trs __LINE_trs[] = {
		{Blank_st, Start_st},
		{Start_st, Stop_st},
		{Start_st, Attribute_st},
		{Attribute_st, Value_st},
		{Value_st, Stop_st},
		{Stop_st, Success_st}
};


Result Transition(State_stack_t *state_stack, int level, __state_enum state){
	TRACE_IN
	if ( state_stack ->l == None){
		LOG("Stack for states will be created for level : %d\n", level)
		*state_stack = StateStack_create(level);
	}else{
		CHECK("Evaluate state_stack_level", state_stack->l == level)
		if ( assert_error ){
			TRACE_OUT
			return Unknown_Failure;
		}
	}
	TRACE_OUT
	return Success;
}
