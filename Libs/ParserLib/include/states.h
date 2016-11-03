#ifndef __parser_state
#define __parser_state

typedef char State;
typedef char Level;
typedef struct{ State current; State next; }__trs;


/**
 *  Levels
 */
typedef enum{
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
	Attribute_st,
	Value_st,
	Jason_start_st,
	Jason_end_st,
	Success_st,
	Error_st
}__state_enum;


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
		{Stop_st, Success}
};


#endif
