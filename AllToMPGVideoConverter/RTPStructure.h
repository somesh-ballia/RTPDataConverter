#ifndef RTP_STRUCTURE_H
#define RTP_STRUCTURE_H
#include "CommonALl.h"

#define DEFAULT_RTP_HEADER_SIZE   12

enum ENMIAXRTPHeaderRetCode
{
	INVALID_RTP = 0,
	VALID_RTP	
};

// RTP packet header
struct STIAXRTPPktHeader
{
	//Payload
	u8 *m_pbyData;

	//Payload len
	u32 m_dwDataLen;

	// csrc count
	u32 m_dwCSRCCount;

	// timestamp of this packet
	u32 m_dwRTPTimeStamp;

	// source of packet
	u32 m_dwRTPSource;

	// sequence number of this packet
	u16 m_unSeqNumber;

	// protocal version
	u8	m_byVersion : 2;

	// padding flag - for encryption
	u8	m_byPadding : 1;

	// header extension flag
	u8	m_byExtension : 1;

	// marker bit - for profile
	u8  m_byMarker : 1;

	// payload type
	u8	m_byRTPPayLoad;

	STIAXRTPPktHeader()
	{
		m_pbyData = NULL;
		m_dwDataLen = 0;
		m_dwCSRCCount = 0;
		m_dwRTPTimeStamp = 0;
		m_dwRTPSource = 0;
		m_byVersion = 0;
		m_byPadding = 0;
		m_byExtension = 0;
		m_byMarker = 0;
		m_byRTPPayLoad = 0;
	}

	~STIAXRTPPktHeader()
	{
		m_pbyData = NULL;
		m_dwDataLen = 0;
		m_dwCSRCCount = 0;
		m_dwRTPTimeStamp = 0;
		m_dwRTPSource = 0;
		m_byVersion = 0;
		m_byPadding = 0;
		m_byExtension = 0;
		m_byMarker = 0;
		m_byRTPPayLoad = 0;
	}

	ENMIAXRTPHeaderRetCode DeSerialize(u8 *pbyRTPData , u32 dwDataLen)
	{
		ENMIAXRTPHeaderRetCode enmRetCode = INVALID_RTP;
		if((NULL != pbyRTPData) && (0 < dwDataLen))
		{
			m_byVersion = (pbyRTPData[0]>>6)&3;

			//check for version
			if ((pbyRTPData[0] != 0x80) && (pbyRTPData[0] != 0xA0))
			{
				return enmRetCode;
			}

			m_byPadding = (pbyRTPData[0]>>5)&1;
			m_byExtension = pbyRTPData[0] & 0x10;
			m_dwCSRCCount = pbyRTPData[0] & 0x0F;
			m_byMarker = (pbyRTPData[1]>>7)&1;

			m_byRTPPayLoad = pbyRTPData[1] & 0x7F;

			m_unSeqNumber = ((u16)(pbyRTPData[2]) << 8) & 0xFF00 |										
				(((u16)(pbyRTPData[3])) & 0x00FF);

			m_dwRTPTimeStamp = ((u32)(pbyRTPData[4]) <<  24) & 0xFF000000 |										
				((u32)(pbyRTPData[5] << 16) & 0x00FF0000) |
				((u32)(pbyRTPData[6] << 8) & 0x0000FF00) |
				((u32)(pbyRTPData[7]) & 0x000000FF); 

			m_dwRTPSource = ((u32)(pbyRTPData[8]) << 24) & 0xFF000000 |										
				((u32)(pbyRTPData[9] << 16) & 0x00FF0000) |
				((u32)(pbyRTPData[10] << 8) & 0x0000FF00)|
				((u32)(pbyRTPData[11]) & 0x000000FF);

			//validate CRC counters for audio data extraction
			u16 unDataOffset = DEFAULT_RTP_HEADER_SIZE;
			unDataOffset += (4 * m_dwCSRCCount);
			if(unDataOffset < dwDataLen)
			{
				m_pbyData = (pbyRTPData + unDataOffset);
				m_dwDataLen = (dwDataLen - unDataOffset);
				enmRetCode = VALID_RTP;
			}
		}

		return enmRetCode;
	}

};

#endif