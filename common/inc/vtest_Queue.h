

#ifndef _VTEST_QUEUE_H
#define _VTEST_QUEUE_H

#include "OMX_Core.h"

namespace vtest {

/**
 * @brief Queue class.
 */
class Queue {
public:

    /**
     * @brief Constructor
     *
     * @param nMaxQueueSize Max number of items in queue (size)
     * @param nMaxDataSize Max data size
     */
    Queue(OMX_S32 nMaxQueueSize,
          OMX_S32 nMaxDataSize);

    /**
     * @brief Destructor
     */
    ~Queue();

private:
    Queue(); // private default constructor
public:

    /**
     * @brief Pushes an item onto the queue.
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data in bytes
     */
    OMX_ERRORTYPE Push(OMX_PTR pData,
                       OMX_S32 nDataSize);

    /**
     * @brief Pops an item from the queue.
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data buffer in bytes
     */
    OMX_ERRORTYPE Pop(OMX_PTR pData,
                      OMX_S32 nDataSize);

    /**
     * @brief Peeks at the item at the head of the queue
     *
     * Nothing will be removed from the queue
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data in bytes
     *
     * @return OMX_ErrorNotReady if there is no data
     */
    OMX_ERRORTYPE Peek(OMX_PTR pData,
                       OMX_S32 nDataSize);

    /**
     * @brief Get the size of the queue.
     */
    OMX_S32 GetSize();

private:
    OMX_PTR m_pHandle;
};
}

#endif // #ifndef _VTEST_QUEUE_H
