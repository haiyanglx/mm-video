

#ifndef _VTEST_CHANGE_QUALITY_H
#define _VTEST_CHANGE_QUALITY_H

#include "OMX_Core.h"
#include "vtest_ITestCase.h"

namespace vtest {
class EncoderFileSource;       // forward declaration
class EncoderFileSink;         // forward declaration
class Encoder;          // forward declaration
class Mutex;            // forward declaration

/**
 * @brief Test case for dynamic quality configuration
 */
class TestChangeQuality : public ITestCase {
public:

    /**
     * @brief Constructor
     */
    TestChangeQuality();

    /**
     * @brief Destructor
     */
    virtual ~TestChangeQuality();

private:

    virtual OMX_ERRORTYPE Execute(CodecConfigType *pConfig,
                                  DynamicConfigType *pDynamicConfig,
                                  OMX_S32 nTestNum);

    virtual OMX_ERRORTYPE ValidateAssumptions(CodecConfigType *pConfig,
                                              DynamicConfigType *pDynamicConfig);

    static void SourceDeliveryFn(OMX_BUFFERHEADERTYPE *pBuffer);

    static void SinkReleaseFn(OMX_BUFFERHEADERTYPE *pBuffer);

    static OMX_ERRORTYPE EBD(OMX_IN OMX_HANDLETYPE hComponent,
                             OMX_IN OMX_PTR pAppData,
                             OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);

    static OMX_ERRORTYPE FBD(OMX_IN OMX_HANDLETYPE hComponent,
                             OMX_IN OMX_PTR pAppData,
                             OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);

private:
    EncoderFileSource *m_pSource;
    EncoderFileSink *m_pSink;
    Encoder *m_pEncoder;
    Mutex *m_pMutex;
    OMX_S32 m_nFramesCoded;
    OMX_S32 m_nFramesDelivered;
    OMX_S64 m_nBits;
};

} // namespace vtest

#endif // #ifndef _VTEST_CHANGE_QUALITY_H
