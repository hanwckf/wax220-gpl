#ifndef __VOS_SM_H__
#define __VOS_SM_H__

#ifdef __cplusplus
extern "C" {
#endif


VOS_RET_E vosSm_cleanup(void *shmAddr);

VOS_RET_E vosSm_delete(SINT32 shmId);

VOS_RET_E vosSm_creat(UINT32 key, UINT32 size, SINT32 *shmId, void **shmAddr);

VOS_RET_E vosSem_cleanup(SINT32 semId);

VOS_RET_E vosSem_init(UINT32 key, UBOOL8 attachExisting, SINT32 *semId);

VOS_RET_E vosSem_unlock(SINT32 semId);

VOS_RET_E vosSem_lock(SINT32 semId, const UINT32 * timeoutMs);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif 
