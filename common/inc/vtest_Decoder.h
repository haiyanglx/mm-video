

#ifndef _VTEST_DECODER_H
#define _VTEST_DECODER_H

#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_QCOMExtns.h"
#include "vtest_ComDef.h"
#include "vtest_SignalQueue.h"
#include "vtest_Thread.h"
#include "vtest_ISource.h"
#include "vtest_BufferManager.h"

namespace vtest {

/**
* @brief Delivers YUV data from the MDP for testing WFD.
*
*/
class Decoder : virtual public ISource {

public:
    Decoder(CodecConfigType *pConfig);
    ~Decoder();

    virtual PortBufferCapability GetBufferRequirements(OMX_U32 ePortIndex);
    virtual OMX_ERRORTYPE Start();
    virtual OMX_ERRORTYPE Stop();
    virtual OMX_ERRORTYPE Configure(CodecConfigType *pConfig,
            BufferManager *pBufManager, ISource *pSource,ISource *pSink);
    virtual OMX_ERRORTYPE SetBuffer(BufferInfo *pBufferInfo, ISource *pSource);
    virtual OMX_ERRORTYPE AllocateBuffers(BufferInfo **pBuffers,
            OMX_U32 nWidth, OMX_U32 nHeight, OMX_U32 nBufferCount,
            OMX_U32 nBufferSize, OMX_U32 ePortIndex, OMX_U32 nBufferUsage = 0);
    virtual OMX_ERRORTYPE UseBuffers(BufferInfo **pBuffers,
            OMX_U32 nWidth, OMX_U32 nHeight, OMX_U32 nBufferCount,
            OMX_U32 nBufferSize, OMX_U32 ePortIndex);

private:
    Decoder();
    virtual OMX_ERRORTYPE ThreadRun(OMX_PTR pThreadData);
    virtual OMX_ERRORTYPE FreeBuffer(
            BufferInfo *pBuffer, OMX_U32 ePortIndex);

    /**
     * @brief Set the encoder state
     *
     * This method can be asynchronous or synchronous. If asynchonous,
     * WaitState can be called to wait for the corresponding state
     * transition to complete.
     *
     * @param eState The state to enter
     * @param bSynchronous If OMX_TRUE, synchronously wait for
     *                     the state transition to complete
     */
    OMX_ERRORTYPE SetState(OMX_STATETYPE eState, OMX_BOOL bSynchronous);

    /**
     * @brief Wait for the corresponding state transition to complete
     *
     * @param eState The state to wait for
     */
    OMX_ERRORTYPE WaitState(OMX_STATETYPE eState);

    OMX_ERRORTYPE HandleOutputPortSettingsChange(OMX_U32 nData2);
    OMX_ERRORTYPE PortReconfigOutput();

    OMX_ERRORTYPE DumpCodecInfo();

    OMX_ERRORTYPE SetNativeWindowEnable();
    OMX_ERRORTYPE GetGraphicBufferUsage(OMX_U32 *nBufferUsage);
    void ParseExtraData(OMX_BUFFERHEADERTYPE *pHeader);

    static OMX_ERRORTYPE EventCallback(
            OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_PTR pAppData,
            OMX_IN OMX_EVENTTYPE eEvent, OMX_IN OMX_U32 nData1,
            OMX_IN OMX_U32 nData2, OMX_IN OMX_PTR pEventData);
    static OMX_ERRORTYPE EmptyDoneCallback(OMX_IN OMX_HANDLETYPE hComponent,
            OMX_IN OMX_PTR pAppData, OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);
    static OMX_ERRORTYPE FillDoneCallback(OMX_IN OMX_HANDLETYPE hComponent,
            OMX_IN OMX_PTR pAppData, OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);

    OMX_ERRORTYPE GetComponentRole(OMX_BOOL bSecureSession,
            FileType *eFileType, OMX_STRING *role);
    OMX_ERRORTYPE Flush(OMX_U32 nPortIndex);
    OMX_BOOL CheckColorFormatSupported(OMX_COLOR_FORMATTYPE nColorFormat,
            OMX_VIDEO_PARAM_PORTFORMATTYPE *pVideoPortFmt);
    OMX_ERRORTYPE SetPictureTypeDecode(OMX_U32 nPictureTypeDecode);

private:
    OMX_BOOL m_bInputEOSReached;
    OMX_BOOL m_bSecureSession;
    OMX_BOOL m_bPortReconfig;
    SignalQueue *m_pSignalQueue;
    SignalQueue *m_pFreeBufferQueue;
    OMX_U32 m_nFrames;
    OMX_U32 m_nFramerate;
    OMX_U32 m_nFrameWidth;
    OMX_U32 m_nFrameHeight;
    OMX_U32 m_nInputBufferCount;
    OMX_U32 m_nInputBufferSize;
    OMX_U32 m_nOutputBufferCount;
    OMX_U32 m_nOutputBufferSize;
    OMX_U32 m_nOriginalOutputBufferCount;
    OMX_U32 m_nOutputBufferUsage;
    OMX_HANDLETYPE m_hDecoder;
    OMX_STATETYPE m_eState;
    OMX_STATETYPE m_eStatePending;
    OMX_VIDEO_CODINGTYPE m_eCodec;
    OMX_PORT_PARAM_TYPE m_sPortParam;
    OMX_PARAM_PORTDEFINITIONTYPE m_sPortFmt;
    PlaybackModeType m_ePlaybackMode;
    OMX_U32 m_nColorFormat;
};

} // namespace vtest

#endif // #ifndef _VTEST_DECODER_H
