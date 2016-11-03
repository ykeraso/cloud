
#include "result_codes.h"
#include "states.h"

#ifndef __stack_state
#define __stack_state

typedef struct _SStack_t{
	State st;
	void *pr;
}Stack_t;

typedef struct _SState_stack_t{
	Level l;
	Stack_t *top;
}State_stack_t;

State_stack_t StateStack_create(Level l);
void StateStack_destroy(State_stack_t *state_stack);

State StateStack_show(State_stack_t state_stack);
Result StateStack_push(State_stack_t *state_stack, State state);
Result StateStack_pop(State_stack_t *state_stack);


#endif //__stack_state
