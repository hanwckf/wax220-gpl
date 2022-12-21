#ifndef __UTIL_FTRACE_H__
#define __UTIL_FTRACE_H__

/** This is where the debugfs filesystem will be mounted if ftrace is enabled.
 *  The ftrace directories and files are all in the tracing sub-directory.
 */
#define FTRACE_MOUNTPOINT "/var/debug"

/** This is the file that controls tracing on or off.
 */
#define FTRACE_ON         "/var/debug/tracing/tracing_on"

/** This is the file that allows userspace apps to insert a trace line
 */
#define FTRACE_INSERT_MARKER "/var/debug/tracing/trace_marker"

/** This is the file that selects which type of tracing we are doing
 */
#define FTRACE_CURRENT_TRACER  "/var/debug/tracing/current_tracer"

/** This is the file that allows you to get and set current options.
 */
#define FTRACE_TRACE_OPTIONS  "/var/debug/tracing/trace_options"



/** Enable tracing
 */
void utilFtr_enable(void);

/** Disable tracing
 */
void utilFtr_disable(void);

/** Insert a string in the current trace.
 * @param (IN) string to insert
 */
void utilFtr_insertMarker(const char *s);

/** Set the specified option in trace_option.
 *  This function does not do error checking on the option
 *  string, so make sure the option name is correct.
 */
void utilFtr_setTraceOption(const char *s);

/** Set the current trace type to function tracing.
 *  Tracing must still be enabled/disabled separately.
 */
void utilFtr_doFunctionTracing(void);

/** Set the current trace type to function graph tracing.
 *  Tracing must still be enabled/disabled separately.
 */
void utilFtr_doFunctionGraphTracing(void);

/** Set the current trace type to nothing.
 *  This will also clear the trace buffer.
 */
void utilFtr_doNopTracing(void);


#endif /* __UTIL_FTRACE_H__ */
