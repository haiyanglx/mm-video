

#ifndef _VTEST_FILE_H
#define _VTEST_FILE_H

#include "OMX_Core.h"

namespace vtest {

/**
 * @brief Class for reading from and writing to files
 */
class File {

public:

    /**
     * @brief Constructor
     */
    File();

    /**
     * @brief Destructor
     */
    ~File();

    /**
     * @brief Opens the file in read or write mode
     *
     * @param pFileName The name of the file
     * @param bReadOnly Set to OMX_TRUE for read access, OMX_FALSE for write access.
     */
    OMX_ERRORTYPE Open(OMX_STRING pFileName, OMX_BOOL bReadOnly);

    /**
     * @brief Reads the file. Only valid in read mode.
     *
     * @param pBuffer The buffer to read into
     * @param nBytes The number of bytes to read
     * @param pBytesRead The number of bytes actually read (output)
     */
    OMX_ERRORTYPE Read(OMX_U8 *pBuffer, OMX_S32 nWidth,
                       OMX_S32 nHeight, OMX_S32 *pBytesRead, OMX_U32 nConfig,
                       OMX_U32 format);
    /**
     * @brief Writes to the file. Only valid in write mode.
     *
     * @param pBuffer The buffer to write from
     * @param nBytes The number of bytes to write
     * @param pBytesWritten The number of bytes actually written (output)
     */
    OMX_ERRORTYPE Write(OMX_U8 *pBuffer, OMX_S32 nBytes, OMX_S32 *pBytesWritten);

    /**
     * @brief Reposition the file pointer.
     *
     * @param nBytes The number of bytes from the start of file
     */
    OMX_ERRORTYPE SeekStart(OMX_S32 nBytes);

    /**
     * @brief Closes the file
     */
    OMX_ERRORTYPE Close();

private:
    void *m_pFile;
    OMX_BOOL m_bReadOnly;
};

}

#endif // #ifndef _VTEST_FILE_H
