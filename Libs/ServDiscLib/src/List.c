#include <stdio.h>

#include "result_codes.h"
#include "log.h"

#include "List.h"

List_t List_create(){
	TRACE_IN
	List_t ret;

	ret.number_of_data = 0;
	ret.max_number_of_data = interval;
	ret.point = NULL;

	TRACE_OUT
	return ret;
}
