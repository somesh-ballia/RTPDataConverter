// AllToMPGVideoConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" 
{
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <libavcodec\avcodec.h>
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavutil\avutil.h>
#include <libavutil\imgutils.h>
#include <libavutil\samplefmt.h>
#include <libavutil\timestamp.h>
#include <libswscale\swscale.h>
#include <libavutil\mathematics.h>
#include <libavutil\channel_layout.h>
#include <libswresample/swresample.h>
#include <libavutil\common.h>
#include <libavutil\opt.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "RTPStructure.h"
}

#define STREAM_FRAME_RATE	25 /* 25 images/s */
#define STREAM_PIX_FMT		AV_PIX_FMT_YUV420P

#define PATH				"d:\\DUMP_DATA_Session_1611772974_3488_-1062718875_16402.bin"
#define TEXT_SAPERATOR		"RTPPACKET"
#define TEXT_SAPERATOR_LEN	9

#define MAX_BUFFER_SIZE 24576

// FOR DEMUX
uint8_t *decoded_video_data[4]			= {NULL};
uint8_t **decoded_audio_data			= NULL;
int		decoded_video_line_size[4]		= {0};
AVPicture src_picture, dst_picture;


// FOR MUX
//int		sws_flags						= SWS_BICUBIC;
int16_t	*samples						= NULL;
int		audio_input_frame_size			= 0;
int		frame_count						= 0;
AVFrame *MUX_frame						= NULL;

// TEMP
FILE *video_dst_file					= NULL;
FILE *audio_dst_file_pre				= NULL;
FILE *audio_dst_file_post				= NULL;

void Decode(u8* pbyBuffer,u32 dwBufferLen)
{

}

int main(int argc, char* argv[])
{
	u8 pbyBuffer[MAX_BUFFER_SIZE] = {0};
	FILE *fp_read = NULL;
	fp_read = fopen(PATH,"rb");
	if(NULL != fp_read)
	{
		u32 dwRTPSize = 0;
		if( 0 < fread((u8*)&dwRTPSize,1,sizeof(dwRTPSize),fp_read) && (0 < dwRTPSize))
		{
			if(dwRTPSize == fread(pbyBuffer,1,dwRTPSize,fp_read))
			{
				STIAXRTPPktHeader stIAXRTPPkt;  
				ENMIAXRTPHeaderRetCode enmRTPRetCode = INVALID_RTP;

				enmRTPRetCode = stIAXRTPPkt.DeSerialize((pbyBuffer) , (dwRTPSize));

				if(VALID_RTP == enmRTPRetCode)
				{
					Decode(stIAXRTPPkt.m_pbyData,stIAXRTPPkt.m_dwDataLen);
				}
			}
		}

		fclose(fp_read);
	}
	_getch();
	return 0;
}

