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


State_stack_t StateStack_create(Level l){
	TRACE_IN
	State_stack_t st;
	st.l = l;
	st.top = NULL;
	TRACE_OUT
	return st;
}

Boolean is_empty(State_stack_t st){
	TRACE_IN
	if ( st.top == NULL ){
		TRACE_OUT
		return True;
	}
	TRACE_OUT
	return False;
}

void StateStack_destroy(State_stack_t *st){
	TRACE_IN
	void *pr;
	while (st->top != NULL ){
		LOG("Loop for destroy stack nodes")
		pr = st->top->pr;
		free(st->top);
		st->top = (Stack_t*)pr;
	}
	TRACE_OUT
}

State StateStack_show(State_stack_t st){
	TRACE_IN
	if ( is_empty(st) ){
		LOG("Empty stack")
		TRACE_OUT
		return 0;
	}
	TRACE_OUT
	return st.top->st;
}

Result StateStack_push(State_stack_t *st, State state){
	TRACE_IN
	Stack_t *new;
	if ( ( new = malloc(sizeof(Stack_t))) == NULL ){
		LOG("Malloc failed")
		TRACE_OUT
		return Memory_Failure;
	}
	new->pr = (void *)(st->top);
	st->top = (Stack_t *)new;
	st->top->st = state;
	TRACE_OUT
	return Success;
}
Result StateStack_pop(State_stack_t *st){
	if ( is_empty(*st) ){
		LOG("Empty stack")
		TRACE_OUT
		return Empty_stack;
	}
	Stack_t *top = (Stack_t*)st->top->pr;
	free(st->top);
	st->top = top;
	TRACE_OUT
	return Success;
}



