

#ifndef _VTEST_ITEST_CASE_H
#define _VTEST_ITEST_CASE_H

#include "OMX_Core.h"
#include "vtest_ComDef.h"
#include "vtest_XmlComdef.h"

namespace vtest {

class Thread;     // forward declaration

/**
 * @brief A test case interface
 */
class ITestCase {

public:
    /**
     * @brief Constructor
     *
     * Must explicitly be called by all derived classes
     */
    ITestCase();

    /**
     * @brief Destructor
     */
    virtual ~ITestCase();

public:
    /**
     * @brief Start the test asynchronously
     */
    OMX_ERRORTYPE Start(OMX_S32 nTestNum,VideoStaticProperties* pGlobalVideoProp,VideoSessionInfo* pSessionInfo);

    /**
     * @brief Block until the test case is finished
     *
     * @return The final test result
     */
    virtual OMX_ERRORTYPE Finish();

private:
    /**
     * @brief The execution function for the test case
     *
     */
    virtual OMX_ERRORTYPE Execute(CodecConfigType *pConfig,
            DynamicConfigType *pDynamicConfig, OMX_S32 nTestNum) = 0;

    /**
     * @brief Validates test case specific configuration assumptions.
     *
     * Required to be implemented by each test case. If no assumptions are
     * made, simply return OMX_ErrorNone.
     */
    virtual OMX_ERRORTYPE ValidateAssumptions(CodecConfigType *pConfig,
            DynamicConfigType *pDynamicConfig);

    /**
     * @brief Thread entry
     *
     * Invokes the child class's Execute method
     */
    static OMX_ERRORTYPE ThreadEntry(OMX_PTR pThreadData);

private:
    Thread *m_pThread;
    CodecConfigType m_sConfig;
    DynamicConfigType m_sDynamicConfig;
    OMX_S32 m_nTestNum;
};

} // namespace vtest

#endif // #ifndef  _VTEST_ITEST_CASE_H
