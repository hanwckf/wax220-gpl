#ifndef __UTIL_LINKLIST_H__
#define __UTIL_LINKLIST_H__

typedef enum
{
   KEY_INT=0,
   KEY_STRING=1
} *pLIST_KEY_TYPE, LIST_KEY_TYPE;

typedef struct entryType
{
   struct entryType *next;
   LIST_KEY_TYPE keyType;       
   void *key;              /* key is used for sorting */
   void *data;
} *pENTRY_TYPE, ENTRY_TYPE;

typedef struct listType
{
   struct entryType *head;
   struct entryType *tail;
} *pLIST_TYPE, LIST_TYPE;

/** Add an entry to the front of the list
 *
 * @param entry (IN) Pointer to the entry to be added to list.  Caller
 *                    pre-allocated and initialize data and key.
 * @param list (IN)  Pointer to the list.  The list's head and tail will be updated.
 * @return VOS_RET_E enum.
 */
VOS_RET_E addFront(pENTRY_TYPE entry, pLIST_TYPE list);

/** Add an entry to the end of the list
 *
 * @param entry (IN) Pointer to the entry to be added to list.  Caller
 *                    pre-allocated and initialize data and key.
 * @param list (IN)  Pointer to the list.  The list's head and tail will b e updated
 * @return VOS_RET_E enum.
 */
VOS_RET_E addEnd(pENTRY_TYPE entry, pLIST_TYPE list);

/** Remove the first entry of the list, and return to caller.
 *
 * @param list (IN)  Pointer to the list.  The list's head and tail will be updated
 * @return pointer to the entry.  Caller needs to free data, key and entryType.
 */
void *removeFront(pLIST_TYPE list);

/** Remove the last entry of the list, and return to caller.
 *
 * @param list (IN)  Pointer to the list.  The list's head and tail will be updated
 * @return pointer to the entry.  Caller needs to free data, key and entryType.
 */
void *removeEnd(pLIST_TYPE list);

/** Remove the last entry of the list, and return to caller.
 *
 * @param list (IN)  Pointer to the list.  The list's head and tail will be updated
 * @param key (IN)  Pointer to the key which is used to look for the entry.
 * @param type (IN)  Key type, integer or string
 * @return pointer to the entry.  Caller needs to free data, key and entryType.
 */
void *removeEntry(pLIST_TYPE list, void *key, LIST_KEY_TYPE type);

/** Find a particular entry in the list with matching key.
 *
 * @param list (IN)  Pointer to the list.  The list's head and tail will be updated
 * @param key (IN)  Pointer to the key which is used to look for the entry.
 * @param type (IN)  Key type, integer or string
 * @param prev (OUT)  Pointer to store found entry's previous location.
 * @param ptr (OUT)  Pointer to store found entry's location. 
 * @return 1 if found, 0 if not found
 */
int findEntry(pLIST_TYPE list, void *key, LIST_KEY_TYPE type, pENTRY_TYPE *prevPtr, pENTRY_TYPE *ptr);

void *removeFoundEntry(pENTRY_TYPE ptr, pENTRY_TYPE prevPtr, pLIST_TYPE list);
void *removeIntEntry(pLIST_TYPE list, int key);
void *removeStrEntry(pLIST_TYPE list, char *key);
void sortIntList(pLIST_TYPE list);
void printList(const pLIST_TYPE list, LIST_KEY_TYPE type);
int findIntEntry(pLIST_TYPE list, int key, pENTRY_TYPE *prevPtr, pENTRY_TYPE *ptr);

#endif /* __UTIL_LINKLIST_H__ */
