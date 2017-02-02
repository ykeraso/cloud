
#include "result_codes.h"
#include "states.h"
#include "state_stack.h"

#ifndef __transition
#define __transition

Result Transition(State_stack_t *state_stack, int level, __state_enum state);

#endif //__transition
