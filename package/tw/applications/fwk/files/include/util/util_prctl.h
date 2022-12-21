#ifndef __UTIL_PRCTL_H__
#define __UTIL_PRCTL_H__

#include "../fwk.h"
/*
 * Technically, I should not include linux specific header here.
 * But I really don't want to redefine all the LINUX signals just
 * for the sake of OS independence....
 */
#include <signal.h> 


/*!\file util_prctl.h
 * \brief Header file for the VOS Process Control API.
 *
 *  Process control functions are included in the vos_util library.
 *  Process control is intended primary for smd, which is supposed
 *  to manage all process spawning, and for the unittests.  The RCL
 *  handler functions may also use them as we slowly transition from
 *  the 3.x implementation to the new CMC (4.x) implementation.
 *
 *  Typically, management applications should not need to call process
 *  control functions directly.  Instead, they should interact with the
 *  MDM and let the RCL handler functions spawn the appropriate daemons
 *  or spawn commands to do system actions.
 */

typedef enum
{
   SPAWN_AND_RETURN=1,  /**< spawn the process and return. */
   SPAWN_AND_WAIT  =2   /**< spawn the process and wait for it to exit.
                         *   The number of milliseconds to wait must be
                         *   specified in SpawnProcessInfo.timeout.
                         *   While waiting, the caller will block (but will
                         *   not spin in the CPU).
                         *   If the spawned process does not exit by the
                         *   timeout time, it will be terminated with a SIGKILL.
                         *   This mode will always collect the child before
                         *   returning.
                         */
} SpawnProcessMode;


typedef enum
{
   COLLECT_PID=1,  /**< Collect the specified pid, waiting indefinately. */
   COLLECT_PID_TIMEOUT=2, /**< Collect the specified pid, waiting for specified amount of time only. */
   COLLECT_ANY=3,  /**< Collect any spawned child process, waiting indefinately. */
   COLLECT_ANY_TIMEOUT=4 /**< Collect any spawned child process, waiting for specified amount of time only. */
} CollectProcessMode;


typedef enum
{
   PSTAT_RUNNING=1, /**< process is running. */
   PSTAT_EXITED=2,  /**< process has exited. */
} SpawnedProcessStatus;



/** Info needed to spawn a process.
 *
 */
typedef struct 
{
    const char *exe;  /**< full path and name of executable */
    const char *args; /**< args to pass to executable */
    const char *workPath; /**< the lanched app work path */
    const char *libPath; /**< the lanched app lib path */
    SpawnProcessMode spawnMode;  /**< Various spawning options. */
    UINT32 timeout;   /**< If SPAWN_AND_WAIT, how many milliseconds to wait before returning. */
    SINT32 stdinFd;   /**< Standard input of spawned process tied to this, -1 means /dev/null */
    SINT32 stdoutFd;  /**< Standard output of spawned process tied to this, -1 means /dev/null */
    SINT32 stderrFd;  /**< Standard error of spawned process tied to this, -1 means /dev/null */
    SINT32 serverFd;  /**< Special hack for smd dynamic launch service.
                       *   This server fd, if not -1, is tied to VOS_DYNAMIC_LAUNCH_SERVER_FD */
    SINT32 maxFd;     /**< Close all fd's up to and including this, but excluding
                       *   the stdinFd, stdoutFd, stderrFd, and serverFd */
    UBOOL8 inheritSigint;  /**< Check if the process needs to inherit sigint. */
    UINT32 uid;
    UINT8 maxCpuUsage;
    UINT32 maxPhyRam;
    UINT32 maxVirtRam;
    UINT32 maxDiskSize;
    UINT32 maxSocketNum;
    UBOOL8 coreDump;
    UBOOL8 newSession;
    UBOOL8 monOut;
    const char *netNs;
} SpawnProcessInfo;



/** Info needed to collect (wait for termination of) a process.
 *
 */
typedef struct
{
   CollectProcessMode collectMode; /**< Various collect options. */
   SINT32 pid; /**< If collecting a specific process, the pid of the process to collect. */
   UINT32 timeout; /**< If using a collect mode with timeout, the number of milliseconds to wait. */
} CollectProcessInfo;


/** Info about a spawned process, returned by spawnProcess and collectProcess.
 *
 */
typedef struct
{
   SINT32  pid;          /**< pid of the process that this structure is reporting on. */
   SpawnedProcessStatus status; /**< current status of process. */
   SINT32  signalNumber; /**< If process exited due to Linux signal, the signal number is stored here. */
   SINT32  exitCode;     /**< If process exited and not due to Linux signal, the exit code is stored here. */
   SINT32 ptyFd;
} SpawnedProcessInfo;


/** Spawn a process, possibly also wait for its completion.
 *
 * The child process's actions for all signals are set to default action.
 *
 * @param collectInfo (IN) parameters affecting which command to spawn.
 * @param procInfo   (OUT) Info about the spawned process.
 *
 * @return VOS_RET_E enum.
 */
extern VOS_RET_E prctl_spawnProcess(const SpawnProcessInfo *spawnInfo, SpawnedProcessInfo *procInfo);



/** Wait for a specific process or any process to exit, with a possible timeout.
 *
 * @param collectInfo (IN) parameters affecting which process to collect and
 *                         possible timeout for getting a process.
 * @param procInfo   (OUT) Info about the collected process, if any.
 *
 * @return VOS_RET_E enum.  Specifically, VOS_RET_SUCCESS means a process was
 *         collected.  VOS_RET_TIMED_OUT means a process was not collected
 *         during the timeout period (timeout period could be 0).
 *         VOS_RET_INVALID_ARGUMENTS means other error.
 */
extern VOS_RET_E prctl_collectProcess(const CollectProcessInfo *collectInfo, SpawnedProcessInfo *procInfo);

extern VOS_RET_E prctl_terminateProcessGracefully(SINT32 pid);

extern VOS_RET_E prctl_terminateProcessForcefully(SINT32 pid);

extern void prctl_signalProcessDelay(void *tPid);

extern VOS_RET_E prctl_signalProcess(SINT32 pid, SINT32 sig);


/** Execute the given command and wait indefinately for it to exit.
 *
 * Ported over from 3.x bcmSystemMute() to ease porting effort.  This function can be
 * used, but please consider using prctl_spawnProcess instead.  The only place
 * where you really need to use this function is if your command redirects its output
 * to another file, as in iptables -L > /tmp/iptables_out.
 * 
 * @param command (IN) The command line to execute.
 *
 * @return 0 on success, all other values indicate error.
 */
int prctl_runCommandInShellBlocking(char *command);


/** Execute the given command and wait for a limited (hard-coded) amount of time
 *  for it to exit.
 *
 * Ported over from 3.x bcmSystemMute() to ease porting effort.  This function can be
 * used, but please consider using prctl_spawnProcess instead.  The only place
 * where you really need to use this function is if your command redirects its output
 * to another file, as in iptables -L > /tmp/iptables_out.
 * 
 * @param command (IN) The command line to execute.
 *
 * @return 0 on success, all other values indicate error.
 */
int prctl_runCommandInShellWithTimeout(char *command);


/** Given a process name, return the pid.
 *
 * @param name (IN) the name of the process
 *
 * @return on success, the pid, otherwise, UTIL_INVALID_PID
 */
int prctl_getPidByName(const char *name);

#define VOS_UTIL_HAS_GETPIDBYNAME   1


#endif /* __UTIL_PRCTL_H__ */
