#ifndef _VTEST_CONFIG_H
#define _VTEST_CONFIG_H

#include "OMX_Core.h"
#include "vtest_ComDef.h"
#include "vtest_XmlComdef.h"

namespace vtest {

class File;

/**
 * @brief Class for configuring video encoder and video encoder test cases
 */
class Config {

public:
    /**
     * @brief Constructor
     */
    Config();

    /**
     * @brief Destructor
     */
    ~Config();

    /**
     * @brief Parses the config file obtaining the configuration
     *
     * @param pFileName The name of the config file
     * @param pEncoderConfig The encoder config.
     * @param pDynamicConfig The dynamic encoder config. Optional (NULL is valid).
     */
    OMX_ERRORTYPE Parse(OMX_STRING pFileName,
            CodecConfigType *pEncoderConfig, DynamicConfigType *pDynamicConfig);

    /**
     * @brief Parses the Xml file and maps to the configuration
     *
     * @param pGlobalVideoProp Global master xml config
     * @param pXmlNode Ptr to the sessionXml
     * @param pEncoderConfig The configuration
     * @param pDynamicConfig The dynamic encoder config. Optional (NULL is valid).
     * @param pTestId TestId Name
     */
    OMX_ERRORTYPE ParseXml(VideoStaticProperties* pGlobalVideoProp, VideoSessionInfo* pSessionInfo,
            CodecConfigType *pEncoderConfig, DynamicConfigType *pDynamicConfig);

    /**
     * @brief Gets the current or default encoder configuration.
     *
     * @param pEncoderConfig The configuration
     */
    OMX_ERRORTYPE GetCodecConfig(CodecConfigType *pEncoderConfig);

    /**
     * @brief Gets the current or default dynamic encoder configuration.
     *
     * @param pDynamicConfig The configuration
     */
    OMX_ERRORTYPE GetDynamicConfig(DynamicConfigType *pDynamicConfig);

    void MapPreferredOmxIndex(OMX_STRING, struct PreferredOmxIndexType*);

private:
    CodecConfigType m_sCodecConfig;
    DynamicConfigType m_sDynamicConfig;
    DynamicConfig *m_pDynamicProperties;
};

} // namespace vtest

#endif // #ifndef _VTEST_CONFIG_H
