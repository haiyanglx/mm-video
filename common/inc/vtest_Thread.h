
#ifndef _VTEST_THREAD_H
#define _VTEST_THREAD_H

#include "OMX_Core.h"

namespace vtest {

/**
 * @brief Thread start function pointer
 */
typedef long (*thread_fn_type) (void* thread_data);

/**
 * @brief IThreaded class
 * This is a hack to get around the lack of RTTI
 * (real-time-type-info) in Android c++
 */
class IThreaded {
public:
    virtual ~IThreaded() {};
    virtual OMX_ERRORTYPE ThreadRun(OMX_PTR pThreadData) = 0;
};

/**
 * @brief Thread class
 */
class Thread {
public:

    /**
     * @brief Thread start function pointer
     */
    typedef OMX_ERRORTYPE(*StartFnType)(OMX_PTR pThreadData);

public:

    /**
     * @brief Constructor (NOTE: does not create the thread!)
     */
    Thread();

    /**
     * @brief Destructor (NOTE: does not destroty the thread!)
     */
    ~Thread();

    /**
     * @brief Starts the thread at the specified function
     *
     * @param pFn Pointer to the thread start function
     * @param pThreadArgs Arguments passed in to the thread (null is valid)
     * @param nPriority Priority of the thread, unique to each platform.
     */
    OMX_ERRORTYPE Start(StartFnType pFn,
                        OMX_PTR pThreadArgs,
                        OMX_S32 nPriority);

    /**
     * @brief Starts the thread at the specified function
     *
     * @param pThreadStart Pointer to the thread start object
     * @param pThreadArgs Arguments passed in to the thread (null is valid)
     * @param nPriority Priority of the thread, unique to each platform.
     */
    OMX_ERRORTYPE Start(IThreaded *pThreaded,
                        OMX_PTR pThreadArgs,
                        OMX_S32 nPriority);

    /**
     * @brief Indicates if the thread has been started
     */
    OMX_BOOL Started();

    /**
     * @brief Joins the thread
     *
     * Function will block until the thread exits.
     *
     * @param pThreadResult If not NULL the threads status will be store here
    */
    OMX_ERRORTYPE Join(OMX_ERRORTYPE *pThreadResult);

    OMX_ERRORTYPE GetStatus();

private:
    static long ThreadEntry(void *pThreadData);

private:
    IThreaded *m_pThreaded;
    StartFnType m_pFn;
    OMX_S32 m_nPriority;
    OMX_PTR m_pThread;
    OMX_PTR m_pThreadArgs;
    OMX_BOOL m_bStarted;
    OMX_ERRORTYPE m_nThreadStatus;
};

}

#endif // #ifndef _VTEST_THREAD_H
