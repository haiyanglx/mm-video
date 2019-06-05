#include <stdlib.h>
#include "vtest_Script.h"
#include "vtest_Debug.h"
#include "vtest_ComDef.h"
#include "vtest_XmlComdef.h"
#include "vtest_XmlParser.h"
#include "vtest_ITestCase.h"
#include "vtest_TestCaseFactory.h"

OMX_ERRORTYPE RunTest(vtest::VideoStaticProperties* pGlobalVideoProp, vtest::VideoSessionInfo* pSessionInfo) {

    OMX_ERRORTYPE result = OMX_ErrorNone;
    static OMX_S32 testNum = 0;
    testNum++;
    vtest::ITestCase *pTest =
        vtest::TestCaseFactory::AllocTest(pSessionInfo->SessionType);
    if (pTest == NULL) {
        VTEST_MSG_CONSOLE("Unable to alloc test: %s", pSessionInfo->SessionType);
        return OMX_ErrorInsufficientResources;
    }

    VTEST_MSG_CONSOLE("Running test %s", pSessionInfo->SessionType);
    result = pTest->Start(testNum,pGlobalVideoProp, pSessionInfo);
    if (result != OMX_ErrorNone) {
        VTEST_MSG_CONSOLE("Error starting test");
    } else {
        result = pTest->Finish();
        if (result != OMX_ErrorNone) {
            VTEST_MSG_CONSOLE("Test failed");
            if(pGlobalVideoProp->fResult) {
                fprintf(pGlobalVideoProp->fResult, "\nVTEST-OMX %s, %s, FAIL\n", OMX_VTEST_VERSION, pSessionInfo->TestId);
            } else {
                VTEST_MSG_HIGH("Result file not found");
            }
        } else {
            VTEST_MSG_CONSOLE("Test passed");
            if(!strcmp(pSessionInfo->SessionType,"DECODE")) {
                if(pGlobalVideoProp->fResult) {
                    fprintf(pGlobalVideoProp->fResult, "\nVTEST-OMX %s, %s, PASS\n", OMX_VTEST_VERSION, pSessionInfo->TestId);
                } else {
                    VTEST_MSG_HIGH("Result file not found");
                }
            } else if(!strcmp(pSessionInfo->SessionType,"ENCODE")) {
                if(pGlobalVideoProp->fResult) {
                    fprintf(pGlobalVideoProp->fResult, "\nVTEST-OMX %s, %s, EPV Pending \n", OMX_VTEST_VERSION, pSessionInfo->TestId);
                } else {
                    VTEST_MSG_HIGH("Result file not found");
                }
            } else {
                if(pGlobalVideoProp->fResult) {
                    fprintf(pGlobalVideoProp->fResult, "\nVTEST-OMX %s, %s, UNSUPPORTED TEST CASE \n", OMX_VTEST_VERSION, pSessionInfo->TestId);
                } else {
                    VTEST_MSG_HIGH("Result file not found");
                }
            }
        }
    }
    vtest::TestCaseFactory::DestroyTest(pTest);
    return result;
}


int main(int argc, char *argv[]) {
    OMX_ERRORTYPE result = OMX_ErrorNone;
    vtest::XmlParser *pXmlParser = NULL;
    vtest::VideoStaticProperties sGlobalVideoProp;
    vtest::VideoSessionInfo sSessionInfo[MAX_NUM_SESSIONS];
    vtest::VideoSessionInfo *pSessionInfo = NULL;
    vtest::VideoSessionInfo *pBaseSessionInfo = NULL;
    char resultFile[MAX_STR_LEN];
    char masterXmlLocation[MAX_STR_LEN];

    VTEST_MSG_CONSOLE("Entering TestApp\n");
    OMX_Init();

    if (argc != 3) {
        VTEST_MSG_CONSOLE("Usage: %s <MasterConfg.xml path> <input.xml>\n", argv[0]);
        return OMX_ErrorBadParameter;
    }

    pXmlParser = new vtest::XmlParser;

    //Master XML Parsing
    if (OMX_ErrorNone != pXmlParser->ResolveMasterXmlPath(argv[1], masterXmlLocation)) {
        VTEST_MSG_CONSOLE("Error: Input %s is neither a valid path nor a valid filename\n", argv[1]);
        return OMX_ErrorUndefined;
    }


    if (OMX_ErrorNone != pXmlParser->ProcessMasterConfig(&sGlobalVideoProp)) {
        VTEST_MSG_CONSOLE("Error while processing MasterXml\n");
        return OMX_ErrorUndefined;
    }


    //Also open the Results.Csv file
    SNPRINTF(resultFile, MAX_STR_LEN, "%s/Results.csv", masterXmlLocation);
    sGlobalVideoProp.fResult = fopen(resultFile, "a+");

    if (!sGlobalVideoProp.fResult) {
        VTEST_MSG_CONSOLE("Results.Csv file opening failed");
        return OMX_ErrorUndefined;
    }

    VTEST_MSG_CONSOLE("Processed MasterXml. Starting parsing sessionXml:%s\n", (OMX_STRING)argv[2]);

    //Session XML Parsing and Running
    memset((char*)&sSessionInfo[0], 0, MAX_NUM_SESSIONS * sizeof(vtest::VideoSessionInfo));
    if (OMX_ErrorNone != pXmlParser->ParseSessionXml((OMX_STRING)argv[2], &sGlobalVideoProp, &sSessionInfo[0])) {
        VTEST_MSG_CONSOLE("Error while processing SessionXml and starting test\n");
        return OMX_ErrorUndefined;
    }

    pSessionInfo = pBaseSessionInfo = &sSessionInfo[0];

    while (pSessionInfo->bActiveSession == OMX_TRUE) {

        if(OMX_ErrorNone != RunTest(&sGlobalVideoProp,pSessionInfo)) {
            VTEST_MSG_CONSOLE("Failed Processing Session: %s\n", pSessionInfo->SessionType);
        } else {
            VTEST_MSG_CONSOLE("Completed Processing Session: %s\n", pSessionInfo->SessionType);
        }

        pSessionInfo++;
        if(pSessionInfo >= (pBaseSessionInfo + MAX_NUM_SESSIONS )) {
            VTEST_MSG_CONSOLE("Exceeded the number of sessions\n");
            break;
        }
    }


    if (sGlobalVideoProp.fResult) {
        fclose(sGlobalVideoProp.fResult);
        sGlobalVideoProp.fResult = NULL;
    }

    if(pXmlParser) {
        delete pXmlParser;
        pXmlParser = NULL;
    }

    OMX_Deinit();
    VTEST_MSG_CONSOLE("Exiting TestApp\n");
    return result;
}
