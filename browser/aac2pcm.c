#include <stdio.h>
#include <string.h>

#include "neaacdec.h"

/* 定义全局变量 */
unsigned long m_nSampleRate;									//波特率
unsigned char m_nChannels;										//通道
NeAACDecHandle m_hAACDecoder;									//解码器
int m_bInit;  													//初始化标识
NeAACDecFrameInfo hInfo;  										//解码数据

/*
 * 函数名: DestroyAACDecoder
 * 描  述: 解码结束或解码出错时关闭解码器
 * 输  入: 无
 * 返回值: 无
 */
void _DestroyAACDecoder()
{
	if (m_hAACDecoder != NULL)  
	{  
		NeAACDecClose(m_hAACDecoder);  
		m_hAACDecoder = NULL;  
	}
}

/*
 * 函数名: InitAACDecoder
 * 描  述: 初始化AAC解码器，设置采样率和通道数
 * 输  入:
 * 		nSamplesPerSec: 采样率
 * 		nChannels: 通道数(note: 设置值无效，解码时NeAACDecInit自动设置为2)
 * 返回值: 成功返回0, 失败返回-1
 */
int _InitAACDecoder(int nSamplesPerSec, int nChannels)
{
	m_nSampleRate     = nSamplesPerSec;  					//采样率
    m_nChannels       = nChannels;  						//通道数
	m_bInit			  = 0;									//初始化标志
  
	// 打开解码器
    m_hAACDecoder = NeAACDecOpen();  
    if (!m_hAACDecoder)  
    {  
        printf("NeAACDecOpen() failed");  
        _DestroyAACDecoder();  
        return -1;  
    }  

    // 设置解码参数  
    NeAACDecConfigurationPtr conf = NeAACDecGetCurrentConfiguration(m_hAACDecoder);  
    if (!conf)   
    {  
        printf("NeAACDecGetCurrentConfiguration() failed");  
        _DestroyAACDecoder();  
        return -1;  
    }  
    conf->defSampleRate           = nSamplesPerSec;  
    conf->defObjectType           = LC;  
    conf->outputFormat            = 1;  
    conf->dontUpSampleImplicitSBR = 1;  
    NeAACDecSetConfiguration(m_hAACDecoder, conf);  

    return 0;
}

/*
 * 函数名: Decoder
 * 描  述: 将aac数据转换成pcm数据
 * 输  入: 
 * 		pszAAC: aac数据指针
 * 		nLen: aac数据大小
 *      pszOut: pcm数据指针
 *      pnOutLen: pcm数据大小指针
 * 返回值: 失败返回-1，成功返回未进行解码的aac数据大小
 */
int _Decoder(char *pszAAC, unsigned int nLen, char *pszOut, int *pnOutLen)  
{ 
	// 解码前，需要根据第一个AAC包来初始化解码器
    if (m_bInit == 0)  
    {  
        if (NeAACDecInit(m_hAACDecoder, pszAAC, nLen, &m_nSampleRate, &m_nChannels) < 0)  
        {  
            printf("NeAACDecInit failed!\n");  
            return -1;  
        }  
        m_bInit = 1;  
        return nLen; 
    }  

    // 解码AAC数据（注意，首次解码数据错误，应该是解码器内部初始化）  
    unsigned char *pInputPtr  = pszAAC;  
    char *pOutputPtr = (char*)pszOut;  
    int   nRemainLen = *pnOutLen;  
    int   nDecodeLen = 0;  
	void  *out;
    *pnOutLen        = 0;  

	// 进行解码, 第一次解码出错，为正常现象
    out = NeAACDecDecode(m_hAACDecoder, &hInfo, pInputPtr, nLen);

    if (hInfo.error != 0 || hInfo.samples == 0)  
    {  	
    	printf("NeAACDecDecode failed!\n");  
        return nLen;  
    }

    // bytesconsumed 是指消费掉了多少AAC数据，如果你提供的AAC数据较多，那么可能会分几次解出PCM数据  
    pInputPtr += hInfo.bytesconsumed;    
    nLen      -= hInfo.bytesconsumed;  
    nDecodeLen = hInfo.channels * hInfo.samples; // 实际解出的PCM数据需要将样本数和通道数相乘  
	if (nDecodeLen > nRemainLen)  
    {  
    	printf("The remaining buffer is insufficient, can not complete the encoding\n");  
        return -1;  
    } 
	
    // 输出解码数据
    *pnOutLen  += nDecodeLen;  
    memcpy(pOutputPtr, out, nDecodeLen);  
	
    return nLen;  
}  
