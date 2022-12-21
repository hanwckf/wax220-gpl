/**********************************************************************************************************************
*     Copyright (C), 2008, T&W. Ltd. All rights reserved.
*
*     FileName    : util_vector.h
*     Author      : Cai Suyuan
*     Version     : V1.0       
*     Date        : 2008/10/21
*     Description : the head file of vos_vector.c
*     Other       :
*     History     :        
*********************************************************************************************************************/
#ifndef __UTIL_VECTOR_H__
#define __UTIL_VECTOR_H__


#define UTIL_VectorSlot(V,I)  ((V)->index[(I)])
#define UTIL_VectorMax(V) ((V)->max)


struct _util_vector 
{
    UINT32 max;       
    UINT32 alloced;   
    void **index;    
};
typedef struct _util_vector *UTIL_VECTOR;


void *UTIL_VectorRealloc( void * ptr, UINT32 old_size, UINT32 new_size );
UTIL_VECTOR UTIL_VectorInit( UINT32 size );
VOS_RET_E UTIL_VectorEnsure( UTIL_VECTOR v, UINT32 num );
VOS_RET_E UTIL_VectorEmptySlot( UTIL_VECTOR v, UINT32 * num );
VOS_RET_E UTIL_VectorSet( UTIL_VECTOR v, void * val );
VOS_RET_E UTIL_VectorSetIndex( UTIL_VECTOR v, UINT32 i, void * val );
void *UTIL_VectorLookupIndex( UTIL_VECTOR v, UINT32 i );
VOS_RET_E UTIL_VectorUnset( UTIL_VECTOR v, UINT32 i );
UINT32 UTIL_VectorCount( UTIL_VECTOR v );
void UTIL_VectorOnlyWapperFree( UTIL_VECTOR v );
void UTIL_VectorOnlyIndexFree( void * idx );
void UTIL_VectorFree (UTIL_VECTOR v);
UTIL_VECTOR UTIL_VectorCopy (UTIL_VECTOR v);


#endif /* __UTIL_VECTOR_H__ */
