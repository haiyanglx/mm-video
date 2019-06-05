

#ifndef _VTEST_DECODER_FILE_SINK_H
#define _VTEST_DECODER_FILE_SINK_H

#include "OMX_Core.h"
#include "vtest_ISource.h"
#include "vtest_SignalQueue.h"
#include "vtest_File.h"
#include "vtest_Mutex.h"
#include "vtest_Thread.h"
#include "vtest_BufferManager.h"
#include "vtest_Crypto.h"

namespace vtest {

//typedef int (*OMX_ReadBuffer)(OMX_BUFFERHEADERTYPE* pBuffer);

/**
 * @brief Delivers YUV data in two different modes.
 *
 * In live mode, buffers are pre-populated with YUV data at the time
 * of configuration. The source will loop through and deliver the
 * pre-populated buffers throughout the life of the session. Frames will be
 * delivered at the configured frame rate. This mode is useful for gathering
 * performance statistics as no file reads are performed at run-time.
 *
 * In  non-live mode, buffers are populated with YUV data at run time.
 * Buffers are delivered downstream as they become available. Timestamps
 * are based on the configured frame rate, not on the system clock.
 *
 */
class DecoderFileSink : virtual public ISource {

public:
    DecoderFileSink(Crypto *pCrypto);
    virtual ~DecoderFileSink();

    virtual PortBufferCapability GetBufferRequirements(OMX_U32 ePortIndex);
    virtual OMX_ERRORTYPE Configure(CodecConfigType *pConfig,
            BufferManager *pBufManager, ISource *pSource, ISource *pSink);
    virtual OMX_ERRORTYPE SetBuffer(BufferInfo *pBuffer, ISource *pSource);

private:
    DecoderFileSink();
    virtual OMX_ERRORTYPE PortReconfig(OMX_U32 ePortIndex,
              OMX_U32 nWidth, OMX_U32 nHeight, const OMX_CONFIG_RECTTYPE& sRect);
    virtual OMX_ERRORTYPE ThreadRun(OMX_PTR pThreadData);
    OMX_ERRORTYPE WriteToFile(
            OMX_U8 *pData, OMX_U32 nFilledLen, OMX_S32 &nBytes);

private:
    OMX_U32 m_nFrames;
    OMX_U32 m_nFramerate;
    OMX_U32 m_nFrameWidth;
    OMX_U32 m_nFrameHeight;
    File *m_pFile;
    int m_nFileFd;
    OMX_BOOL m_bSecureSession;
    Crypto *m_pCrypto;
    OMX_U32 m_nColorFormat;
};

} // namespace vtest

#endif // #ifndef _VTEST_FILE_SOURCE_H
