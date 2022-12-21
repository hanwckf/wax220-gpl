#ifndef __UTIL_SHELL_H__
#define __UTIL_SHELL_H__


#undef system
#define system  UTIL_DO_SYSTEM_ACTION
#define UTIL_DO_SYSTEM_ACTION(fmt, ...)    UTIL_doSystemAction(__FUNCTION__, fmt, ##__VA_ARGS__)
#define UTIL_COMM_SYSTEM_EX(pszCmd, pszResult, iCount)	UTIL_commSystemEx(pszCmd, pszResult, iCount)

int UTIL_doSystemAction(const char *from, const char *fmt, ...);
int UTIL_commSystemEx(const char *pszCmd, char * pszResult, int iCount);

/**
 * @brief Execute commands and read standard output and error output of commands  
 * Data can be written to the standard input of an executable program that is being executed via stdinFp  
 * Instead of going through the SHELL, it executes the executable directly, so there is no risk of SHELL injection.  
 * !Note that command is executed asynchronously.You can wait for the process to end either by the waitpid() function or by reading the returned standard output or standard error output
 * 
 * @param stdinFp  Returns standard input for the executable program being executed. Passing NULL indicates that the file descriptor is not needed
 * @param stdoutFp Returns the standard output of the executable program executed. Passing NULL indicates that the file descriptor is not needed
 * @param stderrFp Returns standard error output for the executable program executed. Passing NULL indicates that the file descriptor is not needed
 * @param command Executable program.
 * @param ... Pass in a list of arguments to the executable. text The last parameter must be NULL
 * @return  The child process pid. If the value is less than 0, the execution fails.
 * 
 */
pid_t UTIL_doCommand(FILE** stdinFp, FILE** stdoutFp, FILE** stderrFp, const char *command, ...);

/**
 * @brief 
 * Just like System, but it doesn't go through the shell, so there are no shell injection problems.
 * You can't pipe and redirect because it doesn't go through the shell.
 * If a pipe is required, UTIL_doCommand and UTIL_pipeLine can be combined
 * 
 * @param command Executable program.
 * @param ... Pass in a list of arguments to the executable. text The last parameter must be NULL
 * @return int -1 or the exit code of the child process
 */
int UTIL_doSystem(const char *command, ...);

/**
 * @brief Joins two file descriptors to write data from the readable file descriptor to the writable file descriptor
 * 
 * @param readable A readable stream
 * @param writable Streams can be written
 * @param autoclose If TRUE. The Readable and Writable streams are automatically closed when the function executes successfully
 * @return int 
 */
int UTIL_pipeLine(FILE* readable, FILE* writable, UBOOL8 autoclose);
#endif /* __UTIL_SHELL_H__*/