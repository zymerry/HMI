#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcm2aac.h"

int flag = 0;

/*
 * 函数名: encode
 * 描  述: 将获取的音频数据由pcm格式压缩为aac格式
 * 输  入: 
 * 		src: 获取的源音频数据
 * 		dst: 经过压缩后的音频数据
 * 返回值: 返回0表示压缩成功，返回-1表示压缩失败
 */
int _encode(const char *src, char *dst)
{
	// 创建音频压缩器
	S_AACENC enc;
	int framesize;
	E_AACENC_ERROR eAACEnc_Error;

	// 初始化压缩器，只执行一次
	if (flag == 0) {
		enc.m_u32SampleRate = AACRECORDER_SAMPLE_RATE;
		enc.m_u32ChannelNum = AACRECORDER_CHANNEL_NUM;
		enc.m_u32BitRate = AACRECORDER_BIT_RATE * enc.m_u32ChannelNum;
		enc.m_u32Quality = AACRECORDER_QUALITY;
		enc.m_bUseAdts = true;
		enc.m_bUseMidSide = false;
		enc.m_bUseTns = false;

		eAACEnc_Error = AACEnc_Initialize(&enc);
	
		if (eAACEnc_Error != eAACENC_ERROR_NONE) {
			printf("AAC Recorder: Fail to initialize AAC Encoder: Error code 0x%08x\n", eAACEnc_Error);
			return -1;      
		}
		flag = 1;
	}
	// 压缩音频数据
	eAACEnc_Error = AACEnc_EncodeFrame((short*)src, dst, ENCFRAME_BUFSIZE, &framesize);
	if (eAACEnc_Error != eAACENC_ERROR_NONE) {
		printf("AAC Recorder: Fail to encode file: Error code 0x%08x\n", eAACEnc_Error);
		framesize = 0;
	}
//	AACEnc_Finalize();
	return framesize;
}
