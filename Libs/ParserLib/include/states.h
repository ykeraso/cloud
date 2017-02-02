#ifndef __parser_state
#define __parser_state


typedef char State;
typedef char Level;

typedef struct{ State current; State next; }__trs;


/**
 *  Levels
 */
typedef enum{
	None,
	File,
	Line,
	Data
}__level_enum;

/**
 *  Level states
 */
typedef enum{
	None_st,
	Blank_st,
	Start_st,
	Stop_st,
	Start_line,
	End_line,
	Attribute_st,
	Value_st,
	Jason_start_st,
	Jason_end_st,
	Comment,
	Success_st,
	Error_st
}__state_enum;


/*
__state_enum get_state(char **c){
	switch (**c){
		case '#':
			while ( *( *c += 1 )  != '\n' );
			return Comment;
		case '!': return Start_line;
		default:
			break;
	}
	return Error_st;
}

int is_valid_transition(State_stack_t stack, __state_enum state)
		{
			__state_enum ___ = StateStack_show( (stack) );
			if ( ___ >= Error_st )return 0;
			int __i, found  = 0;
			__trs trans;
			trans.current = ___;
			trans.next = state;

			switch( stack.l ){
				case File:
					for ( __i = 0; __i < __FILE_trs_max; __i++)
					{
						if ( !(trans^__FILE_trs[__i] ) )return 1;
					}
					break;

				case Line:
					for ( __i = 0; __i < __LINE_trs_max; __i++)
					{
						if ( !(trans^__LINE_trs[__i] ) )return 1;
					}
					break;

				default:
					return 0;

			}
		}
*/

#endif
