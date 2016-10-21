#ifndef __log_LIB__
#define __log_LIB__

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

#	define FATAL(str) fprintf(stderr, "FATAL ERROR (%s & %d): %s\n", __DATE__, __TIME__, (str) );

#if DEBUG_LEVEL == 1 || DEBUG_LEVEL == 2 || DEBUG_LEVEL == 3
#	define ERROR(str) \
	fprintf(stderr, "ERROR (File:%s, Line:%d [%s]) : %s\n",  __FILE__, __LINE__, __func__, (str) );
#else
#	define ERROR(str) ;
#endif

#if DEBUG_LEVEL == 2 || DEBUG_LEVEL == 3
#	define TRACE_IN 	fprintf(stderr, "In function: %s [%s]\n", __func__, __FILE__ );
#	define TRACE_OUT    fprintf(stderr, "--> Out at %d\n",__LINE__ );
#else
#	define TRACE_IN ;
#   define TRACE_OUT ;
#endif

#if DEBUG_LEVEL == 3
#	define LOG(str) \
	fprintf(stderr, "(%s & %s) : (File:%s, Line:%d [%s]) : %s\n",  __DATE__, __TIME__, __FILE__, __LINE__, __func__, (str) );
#else
#	define LOG(str) ;
#endif

#endif

