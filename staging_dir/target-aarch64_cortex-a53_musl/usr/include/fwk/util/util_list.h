#ifndef __UTIL_LIST_H__
#define __UTIL_LIST_H__

#include "../fwk.h"

typedef struct list_entry {
    struct list_entry *next;
    void *data;
} LIST_ENTRY_T, *pLIST_ENTRY_T;


typedef struct list_node {
   struct list_entry *head;
   struct list_entry *tail; 
} LIST_T, *pLIST_T; 


/* Crate a new list entry */
pLIST_ENTRY_T list_create_entry(void *data);

VOS_RET_E list_prepend(pLIST_ENTRY_T entry, pLIST_T list);

VOS_RET_E list_append(pLIST_ENTRY_T entry, pLIST_T list);

VOS_RET_E list_merge(const pLIST_T list1, pLIST_T list2);

void* list_deleteHead(pLIST_T list);

void* list_deleteTail(pLIST_T list);

void  *list_delete(pLIST_ENTRY_T entry, pLIST_T list);

VOS_RET_E list_compareWithString(const char *pluginName, pLIST_T list);


#endif /* __UTIL_LIST_H__ */

