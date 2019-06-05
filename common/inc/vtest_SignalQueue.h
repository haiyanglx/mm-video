

#ifndef _VTEST_SIGNAL_QUEUE_H
#define _VTEST_SIGNAL_QUEUE_H

#include "OMX_Core.h"

namespace vtest {

class Signal;
class Mutex;
class Queue;

/**
 * @brief Signal queue class.
 *
 * Reader will block on Pop until the writer adds an item
 * to the queue via the Push method.
 */
class SignalQueue {

public:
    /**
     * @brief Constructor
     *
     * @param nMaxQueueSize Max number of items in queue (size)
     * @param nMaxDataSize Max data size
     */
    SignalQueue(OMX_S32 nMaxQueueSize, OMX_S32 nMaxDataSize);

    /**
     * @brief Destructor
     */
    ~SignalQueue();

private:
    SignalQueue(); // private default constructor

public:
    /**
     * @brief Pushes an item onto the queue.
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data in bytes
     */
    OMX_ERRORTYPE Push(OMX_PTR pData, OMX_S32 nDataSize);

    /**
     * @brief Pops an item from the queue.
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data buffer in bytes
     * @param nTimeoutMillis Milliseconds before timeout. Specify 0 for infinite.
     */
    OMX_ERRORTYPE Pop(OMX_PTR pData, OMX_S32 nDataSize, OMX_S32 nTimeoutMillis);

    /**
     * @brief Peeks at the item at the head of the queue
     *
     * Method will not block and nothing will be removed from the queue
     *
     * @param pData Pointer to the data
     * @param nDataSize Size of the data in bytes
     *
     * @return OMX_ErrorNotReady if there is no data
     */
    OMX_ERRORTYPE Peek(OMX_PTR pData, OMX_S32 nDataSize);

    /**
     * @brief Get the size of the queue.
     */
    OMX_S32 GetSize();

    /**
     * @brief Broadcast the signal to get out of Pop(wait)
     */
    OMX_S32 WakeAll();

private:
    Signal *m_pSignal;
    Mutex *m_pMutex;
    Queue *m_pQueue;
    OMX_BOOL m_bBroadcast;
};

}

#endif // #ifndef _VTEST_SIGNAL_QUEUE_H
