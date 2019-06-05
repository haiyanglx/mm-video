

#ifndef _VTEST_SCRIPT_H
#define _VTEST_SCRIPT_H

#include "OMX_Core.h"
#include "vtest_ComDef.h"

namespace vtest {
class File; // forward declaration

/**
 * @brief Class for parsing test case script file
 */
class Script {
public:

    /**
     * @brief Constructor
     */
    Script();

    /**
     * @brief Destructor
     */
    ~Script();

public:

    /**
     * @brief Parses the script file
     *
     * This method can only be called one time per instantiation of this class
     *
     * @param pFileName The name of the script file
     */
    OMX_ERRORTYPE Configure(OMX_STRING pFileName);

    /**
     * @brief Parses the next test from the test script
     *
     * @return OMX_ErrorNoMore if there are no more tests to run
     */
    OMX_ERRORTYPE NextTest(TestDescriptionType *pTestDescription);

private:
    File *m_pFile;
};

} // namespace vtest

#endif // #ifndef _VTEST_SCRIPT_H
