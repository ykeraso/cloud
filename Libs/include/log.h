#ifndef __log_LIB__
#define __log_LIB__

#define LOG_BUFF 300

/**
 * Debug levels
 * 0: Fatal
 * 1: Error logs
 * 2: Error & trace logs
 * 3: All logs
 */
#define FATAL_ERR 0
#define ERROR_LOG 1
#define TRACE_LOG 2
#define EVERY_LOG 3


#define FATAL(...) \
		{ \
			char log_buff[LOG_BUFF]; \
			sprintf(log_buff, __VA_ARGS__); \
			fprintf(stderr, "FATAL ERROR (%s & %s): %s\n", __DATE__, __TIME__, log_buff ); \
		}

#define CHECK(msg, eval) \
	if ( !(eval) ) { \
		FATAL("EXECUTION CHECK FAILED at File:%s, Line:%d [%s]) : %s\n", __FILE__, __LINE__, __func__, (msg) ) \
		assert_error = Assert_Failure; \
	}else{ \
		assert_error = Success; \
	}

#if DEBUG_LEVEL == 1 || DEBUG_LEVEL == 2 || DEBUG_LEVEL == 3
#	define ERROR(...) \
		{ \
		char log_buff[LOG_BUFF]; \
		sprintf(log_buff, __VA_ARGS__); \
		fprintf(stderr, "ERROR (File:%s, Line:%d [%s]) : %s\n",  __FILE__, __LINE__, __func__, log_buff ); \
	}
	#else
#	define ERROR(...) ;
#endif

#if DEBUG_LEVEL == 2 || DEBUG_LEVEL == 3
#	define TRACE_IN 	fprintf(stderr, "TRACE In function: %s [%s]\n", __func__, __FILE__ );
#	define TRACE_OUT    fprintf(stderr, "TRACE --> Out at %d\n",__LINE__ );
#else
#	define TRACE_IN ;
#   define TRACE_OUT ;
#endif

#if DEBUG_LEVEL == 3
#	define LOG(...) \
		{\
			char log_buff[LOG_BUFF]; \
			sprintf(log_buff, __VA_ARGS__); \
			fprintf(stderr, "LOG (%s & %s) : (File:%s, Line:%d [%s]) : %s\n",  __DATE__, __TIME__, __FILE__, __LINE__, __func__, (log_buff) ); \
		}
#else
#	define LOG(...) ;
#endif

#endif

