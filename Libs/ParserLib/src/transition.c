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


Result Transition(State_stack_t *state_stack, int level, __state_enum next_state){
	TRACE_IN
	Result ret;
	CHECK( "Level in state stack", level <= None || level >= MAX_LEVEL)
	if (assert_error){
		TRACE_OUT
		return Unknown_Failure;
	}
	if ( state_stack ->l == None){
		LOG("Stack for states will be created for level : %d\n", level)
		*state_stack = StateStack_create(level);
		StateStack_push(state_stack, Blank_st);
	}else{
		CHECK("Evaluate state_stack_level", state_stack->l == level)
		if ( assert_error ){
			TRACE_OUT
			return Unknown_Failure;
		}
	}
	int i;
	State current_state = StateStack_show(*state_stack);
	switch ( state_stack->l){
		case File:
			for ( i = 0; i < __FILE_trs_max; i++){
				if ( __FILE_trs[i].current == current_state ){
					if ( __FILE_trs[i].next == next_state ){
						ret = StateStack_pop(state_stack);
						if ( ret != Success ){
							ERROR("State_stack pop returned %d", ret)
							TRACE_OUT
							return ret;
						}else{
							LOG("Found transition")
							TRACE_OUT
							return Success;
						}
					}
				}
			}
			ret = StateStack_push(state_stack, next_state);
			if ( ret != Success ){
				ERROR("State_stack pop returned %d", ret)
				TRACE_OUT
				return ret;
			}else{
				LOG("Not found transition")
				TRACE_OUT
				return Success;
			}
			break;

		case Line:
			for ( i = 0; i < __LINE_trs_max; i++){
				if ( __LINE_trs[i].current == current_state ){
					if ( __LINE_trs[i].next == next_state ){
						ret = StateStack_pop(state_stack);
						if ( ret != Success ){
							ERROR("State_stack pop returned %d", ret)
							TRACE_OUT
							return ret;
						}else{
							LOG("Found transition")
							TRACE_OUT
							return Success;
						}
					}
				}
			}
			ret = StateStack_push(state_stack, next_state);
			if ( ret != Success ){
				ERROR("State_stack pop returned %d", ret)
				TRACE_OUT
				return ret;
			}else{
				LOG("Not found transition")
				TRACE_OUT
				return Success;
			}
			break;

		default:
			ERROR("Error state stack :%d", state_stack->l)
			break;
	}
	TRACE_OUT
	return Success;
}
