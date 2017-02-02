#ifndef __result_codes__
#define __result_codes__

typedef enum{
	False,
	True
}Boolean;

typedef enum{
	Success,
	Unknown_Failure,
	Assert_Failure,
	Memory_Failure,
	Empty_list,
	Empty_stack,
	List_out_of_bounds,
	Rewind_list,
	Request_data_not_found,
	Max_Error_Num
}Result;

extern Result assert_error;

#endif
