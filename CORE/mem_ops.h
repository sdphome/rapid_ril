#ifndef __mem_ops_h__
#define __mem_ops_h__

#define MEM_ZERO_INIT       0x0001

///////////////////////////////////////////////////////////////////////////////
inline void *AllocBlob(UINT32 bytes, BOOL fClearMem = TRUE)
{
    void * pBlob = malloc(bytes);

    if ((fClearMem) && (NULL != pBlob))
    {
        memset(pBlob, 0, bytes);
    }

    return pBlob;
}

///////////////////////////////////////////////////////////////////////////////
inline void *FreeBlob(void *pblob)
{
    free(pblob);
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
inline void *ReallocBlob(void *pblob, UINT32 bytes)
{
    if (!pblob)
    {
        return malloc(bytes);
    }

    return realloc(pblob, bytes);
}

#endif // __mem_ops_h__
