#ifndef __UTIL_TMR_H__
#define __UTIL_TMR_H__


/*!\file timer.h
 * \brief Header file for the VOS Event Timer API.
 *  This is in the vos_util library.
 *
 */


#define MAKE_TMR_DELAY_MSG_ID(func, ctxData) ((UINT32)(func) | (UINT32)(ctxData))


/** Event handler type definition
 */
typedef void (*UtilEventHandler)(void*);


/** Max length (including NULL character) of an event timer name.
 *
 * When an event timer is created, the caller can give it a name
 * to help with debugging and lookup.  Name is optional.
 */
#define UTIL_EVENT_TIMER_NAME_LENGTH  32


/** Initialize a timer handle.
 *
 * @param tmrHandle (OUT) On successful return, a handle to be used for
 *                        future handle operation is returned.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilTmr_init(void **tmrHandle);


/** Clean up a timer handle, including stopping and deleting all 
 *  unexpired timers and freeing the timer handle itself.
 *
 * @param tmrHandle (IN/OUT) Timer handle returned by utilTmr_init().
 */
void utilTmr_cleanup(void **tmrHandle);


/** Flush all of the events */
void utilTmr_flush(void *handle);



/** Create a new event timer which will expire in the specified number of 
 *  milliseconds.
 *
 * Since lookups are done using a combination of the handler func and
 * context data, there must not be an existing timer event in the handle
 * with the same handler func and context data.  (We could allow 
 * multiple entries with the same func and ctxData, but we will have to
 * clarify what it means to cancel a timer, cancel all or cancel the
 * next timer.)
 *
 * @param tmrHandle (IN/OUT) Pointer to timer handle that was returned by utilTmr_init().
 * @param func      (IN)     The handler func.
 * @param ctxData   (IN)     Optional data to be passed in with the handler func.
 * @param ms        (IN)     Timer expiration value in milliseconds.
 * @param name      (IN)     Optional name of this timer event.
 *
 * @return VOS_RET_E enum.
 */   
VOS_RET_E utilTmr_set(void *tmrHandle, UtilEventHandler func, void *ctxData, UINT32 ms, const char *name);


/** Stop an event timer and delete it.
 *
 * The event timer is found by matching the callback func and ctxData.
 *
 * @param tmrHandle (IN/OUT) Pointer to the event timer handle;
 * @param func      (IN) The event handler.
 * @param *handle   (IN) Argument passed to the event handler.
 */   
void utilTmr_cancel(void *tmrHandle, UtilEventHandler func, void *ctxData);

/** Replace current event timer with a new event timer which will 
 *  expire in the specified number of milliseconds.  The current event timer
 *  has shorter expire time than the current event in list.  In other words,
 *  this routine will do nothing if the new event timer has longer expire time
 *  than the one in the timer list.
 *
 * @param tmrHandle (IN/OUT) Pointer to timer handle that was returned by utilTmr_init().
 * @param func      (IN)     The handler func.
 * @param ctxData   (IN)     Optional data to be passed in with the handler func.
 * @param ms        (IN)     Timer expiration value in milliseconds.
 * @param name      (IN)     Optional name of this timer event.
 *
 * @return VOS_RET_E enum.
 */   
VOS_RET_E utilTmr_replaceIfSooner(void *tmrHandle, UtilEventHandler func, void *ctxData, UINT32 ms, const char *name);


/** Get the number of milliseconds until the next event is due to expire.
 *
 * @param tmrHandle (IN)  Pointer to timer handle that was returned by utilTmr_init().
 * @param ms        (OUT) Number of milliseconds until the next event.
 *
 * @return VOS_RET_E enum.  Specifically, VOS_RET_SUCCESS if there is a next event.
 *         If there are no more events in the timer handle, VOS_RET_NO_MORE_INSTANCES
 *         will be returned and the parameter ms is set to MAX_UINT32.
 */
VOS_RET_E utilTmr_getTimeToNextEvent(const void *tmrHandle, UINT32 *ms);


/** Get the number of timer events in the timer handle.
 *
 * @param tmrHandle (IN)  Pointer to timer handle that was returned by utilTmr_init().
 *
 * @return The number of timer events in the given handle.
 */
UINT32 utilTmr_getNumberOfEvents(const void *tmrHandle);


/** Execute all events which have expired.
 *
 * This function will call the handler func with the ctxData for all
 * timer events that have expired.  There may be 0, 1, 2, etc. handler
 * functions called by this function.  It is up to the caller of this
 * function to call this function at the appropriate time (using the
 * value of utilTmr_getTimeToNextEvent() and utilTmr_getEventCount() as a guide).
 *
 * Once an event is executed, it is deleted and freed.  
 *
 * @param tmrHandle (IN/OUT) Pointer to timer handle that was returned by utilTmr_init().
 *
 */
void utilTmr_executeExpiredEvents(void *tmrHandle);


VOS_RET_E utilTmr_getTimeRemaining(const void *handle, UtilEventHandler func, void *ctxData, UINT32 *ms);


/** Return true if the specified handler func and context data (event) is set.
 *  
 * @param tmrHandle (IN) Pointer to timer handle that was returned by utilTmr_init().
 * @param func      (IN) The handler func.
 * @param ctxData   (IN) Optional data to be passed in with the handler func.
 *
 * @return TRUE if specified event is present, otherwise, FALSE.
 */   
UBOOL8 utilTmr_isEventPresent(const void *tmrHandle, UtilEventHandler func, void *ctxData);


/** Use debug logging to dump out all timers in the timer handle.
 *  
 * @param tmrHandle (IN) Pointer to timer handle that was returned by utilTmr_init().
 *
 */   
void utilTmr_dumpEvents(const void *tmrHandle);


UBOOL8 utilMsgTmr_isEventPresent(const void *handle, UtilEventHandler func, void *ctxData);

VOS_RET_E utilMsgTmr_set(void *msgHandle, void *handle, UtilEventHandler func, void *ctxData, UINT32 ms, const char *name);

void utilMsgTmr_cancel(void *msgHandle, void *handle, UtilEventHandler func, void *ctxData);

void utilMsgTmr_executeExpiredEvents(void *handle);



#endif  /* __UTIL_TMR_H__ */
