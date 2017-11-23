#ifndef __AAC_H_
#define __AAC_H_

#include <stdbool.h>

#define ENCFRAME_BUFSIZE		1024

#define AACRECORDER_BIT_RATE    15000   // 64K bps
#define AACRECORDER_CHANNEL_NUM 1       // Mono
#define AACRECORDER_QUALITY     90      // 1 ~ 999
#define AACRECORDER_SAMPLE_RATE 8000   // 8K Hz

/* 编码器 */
typedef struct{
	bool            m_bUseAdts;
	bool            m_bUseMidSide;
	bool            m_bUseTns;
	unsigned int    m_u32Quality;           // 1 ~ 999
	unsigned int    m_u32BitRate;           // bps
	unsigned int    m_u32ChannelNum;
	unsigned int    m_u32SampleRate;        // Hz
} S_AACENC;

/* 错误码 */
typedef enum {
	eAACENC_ERROR_NONE          = 0x0000,   // No error                                        
	// Un-recoverable errors
	eAACENC_ERROR_BUFLEN        = 0x0001,   // Input buffer too small (or EOF)
	eAACENC_ERROR_BUFPTR        = 0x0002,   // Invalid (null) buffer pointer
	eAACENC_ERROR_NOMEM         = 0x0031,   // Not enough memory                               
	// Recoverable errors
	eAACENC_ERROR_BADBITRATE    = 0x0103,   // Forbidden bitrate value
	eAACENC_ERROR_BADSAMPLERATE = 0x0104,   // Reserved sample frequency value
} E_AACENC_ERROR;

/* 初始化编码器 */
E_AACENC_ERROR AACEnc_Initialize(S_AACENC *psEncoder);
/* 进行音频编码 */
E_AACENC_ERROR AACEnc_EncodeFrame(
			short   *pi16PCMBuf,        // [in] PCM buffer
			char    *pi8FrameBuf,       // [in] AAC frame buffer
			int     i32FrameBufSize,    // [in] Bytes of AAC frame buffer size
			int     *pi32FrameSize      // [out]Bytes of encoded AAC frame
);
/* 结束编码 */
void AACEnc_Finalize(void);

#endif
