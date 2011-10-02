// CardFunctions.cpp : Defines the exported functions for the DLL application.
//

#include <strsafe.h>
#include "Serial.h"

//extern "C" __declspec(dllexport)int Open(int iPort);
//extern "C" __declspec(dllexport)int Close();

// 0x01
extern "C" __declspec(dllexport)int Setup(int port);
// 0x02
extern "C" __declspec(dllexport)int CreateCard();
// 0x03
extern "C" __declspec(dllexport)int EraseCard();
// 0xff
extern "C" __declspec(dllexport)int Reset();

// 0x04
extern "C" __declspec(dllexport)int ReadUserInfo(char* info);
// 0x05
extern "C" __declspec(dllexport)int ReadTradeSummaryInfo(char* info);
// 0x06
extern "C" __declspec(dllexport)int ReadTradeDetailInfo(int id, char* info);
// 0x07
extern "C" __declspec(dllexport)int WriteUserInfo(const char* a1, const char* a2, const char* a3, const char* a4, const char* a5, const char* a6, const char* a7, const char* a8, const char* a9);
// 0x08
extern "C" __declspec(dllexport)int WriteTradeSummaryInfo(const char* a1, const char* a2, const char* a3, const char* a4);
// 0x09
extern "C" __declspec(dllexport)int WriteTradeDetailInfo(int id, const char* a1, const char* a2, const char* a3, const char* a4, const char* a5, const char* a6, const char* a7, const char* a8, const char* a9, const char* a10, const char* a11, const char* a12, const char* a13);

#define MAXREADLENGTH			512
#define MAXWRITELENGTH			512

#define COMMAND_PREFIX			0x1D
#define COMMAND_SETUP			0x01
#define COMMAND_CREATE_CARD		0x02
#define COMMAND_ERASE_CARD		0x03
#define COMMAND_RESET			0xFF

#define COMMAND_READ_USER_INFO				0x04
#define COMMAND_READ_TRADE_SUMMARY_INFO		0x05
#define COMMAND_READ_TRADE_DETAIL_INFO		0x06

#define COMMAND_WRITE_USER_INFO				0x07
#define COMMAND_WRITE_TRADE_SUMMARY_INFO	0x08
#define COMMAND_WRITE_TRADE_DETAIL_INFO		0x09

CSerial serial;
int iPort = 1;

// Fix space to end of string
void FixSpace(char* dst, const char* src, int start, int len)
{
	int l = strlen(src);
	memcpy(dst + start, src, l);
	memset(dst + start + l, 0x20, len - l);
}

// convert string "100" to 0x00, 0x00, 0x00, 0x64
void String2NChar(char* dst, std::string val, int cnt)
{
	long v = atoi(val.c_str());

	memset(dst, 0, cnt + 1);

	for(int i = 0; i < cnt; i++)
	{
		int b = (v & (0xff << 8*(cnt - i - 1))) >> 8*(cnt - i - 1);
		std::cout << std::hex << b << std::endl;
		memset(dst + i, b, 1);
	}
}

// convert 0x00, 0x00, 0x00, 0x64 to 100
long NChar2Long(const char* val, int cnt)
{
	long v = 0;
	for(int i = 0; i < cnt; i++)
	{
		v+= (unsigned char)val[i] << (8*(cnt-i-1));
	}
	return v;
}

int Action(char* readMsg, char* writeMsg, int len)
{
	char byteRead[MAXREADLENGTH]={0};
	DWORD DWReads = MAXREADLENGTH;
	DWORD DWReaded = 0;

	// Generate serail port string, for example "COM1"
	TCHAR pszPort[10]; 
	size_t cchPort = 10;

	LPCTSTR pszFormat = TEXT("COM%d");
	StringCchPrintf(pszPort, cchPort, pszFormat, iPort);

	int hr = serial.Open(pszPort, 1024, 1024);
	if (hr != 0)
		return hr;

	serial.Setup();
	serial.Write(writeMsg, len);

	serial.SetMask(CSerial::EEventRecv);
	for (int i=0; i<3; i++)
	{
		serial.WaitEvent(0, 100);
		Sleep(200);
	}

	serial.Read(byteRead, DWReads, &DWReaded);

	if (DWReaded < 2){
		serial.Close();
		return E_FAIL;
	}
	serial.Close();

	if (byteRead[1] != 0)
		return E_FAIL;

	if (DWReaded == 2)
		return S_OK;

	memcpy(readMsg, byteRead, DWReaded);
	// 1D 00 Len Data CRC

	return S_OK;
}

// Execute command only
int Execute(char* command)
{
	char wMsg[MAXWRITELENGTH] = {0};
	int iCRC = 0;

	memset(wMsg, strlen(command) + 2, 1);
	memset(wMsg + 1, COMMAND_PREFIX, 1);
	memcpy(wMsg + 2, command, strlen(command));

	int iCount = strlen(wMsg);
	for(int i=2; i<iCount;i++)
	{
		iCRC = iCRC + wMsg[i];
	}
	memset(wMsg + iCount, iCRC & 0xff, 1);

	char rMsg[MAXREADLENGTH] = {0};

	return Action(rMsg, wMsg, iCount + 1);
}

// Execute command only
int ExecuteRead(char* command, char* result)
{
	char wMsg[MAXWRITELENGTH] = {0};
	int iCRC = 0;

	memset(wMsg, strlen(command) + 2, 1);
	memset(wMsg + 1, COMMAND_PREFIX, 1);
	memcpy(wMsg + 2, command, strlen(command));

	int iCount = strlen(wMsg);
	for(int i=2; i<iCount;i++)
	{
		iCRC = iCRC + wMsg[i];
	}
	memset(wMsg + iCount, iCRC & 0xff, 1);

	char rMsg[MAXREADLENGTH] = {0};

	LONG hr = Action(rMsg, wMsg, iCount + 1);

	if (hr == S_OK)
	{
		unsigned char len = rMsg[2];
		memcpy(result, rMsg + 3, len);
	}

	return hr;
}

//// Open serial port
//int Open(int iPort)
//{
//	// Generate serail port string, for example "COM1"
//	TCHAR pszPort[10]; 
//	size_t cchPort = 10;
//
//	LPCTSTR pszFormat = TEXT("COM%d");
//	StringCchPrintf(pszPort, cchPort, pszFormat, iPort);
//
//	return serial.Open(pszPort, 1000, 1000);
//}
//
//// Close serail port
//int Close()
//{
//	return serial.Close();
//}

// Setup machine to R/W card
int Setup(int port)
{
	iPort = port;

	char msg[24] = {0};
	memset(msg, COMMAND_SETUP, 1);
	memset(msg + 1, 1, 1);

	return Execute(msg);
}


int CreateCard()
{
	char msg[24] = {0};
	memset(msg, COMMAND_CREATE_CARD, 1);
	memset(msg + 1, 1, 1);

	return Execute(msg);
}

int EraseCard()
{
	char msg[24] = {0};
	memset(msg, COMMAND_ERASE_CARD, 1);
	memset(msg + 1, 1, 1);

	return Execute(msg);
}

int Reset()
{
	char msg[24] = {0};
	memset(msg, COMMAND_RESET, 1);
	memset(msg + 1, 1, 1);

	return Execute(msg);
}

int WriteUserInfo(const char* a1, const char* a2, const char* a3, const char* a4, const char* a5, const char* a6, const char* a7)
{
	char msg[256] = {0x20};
	memset(msg, COMMAND_WRITE_USER_INFO, 1);
	memset(msg + 1, 88, 1);
	FixSpace(msg, a1, 2, 2);
	FixSpace(msg, a2, 4, 10);
	FixSpace(msg, a3, 14, 13);
	FixSpace(msg, a4, 27, 30);
	FixSpace(msg, a5, 57, 18);
	FixSpace(msg, a6, 75, 13);
	FixSpace(msg, a7, 90, 2);

	return Execute(msg);
}

int WriteTradeSummaryInfo(const char* a1, const char* a2, const char* a3)
{
	char msg[256] = {0};
	memset(msg, COMMAND_WRITE_TRADE_SUMMARY_INFO, 1);
	memset(msg + 1, 16, 1);
	FixSpace(msg, a1, 2, 8);
	FixSpace(msg, a2, 10, 1);
	FixSpace(msg, a3, 11, 1);
	
	return Execute(msg);
}

int WriteTradeDetailInfo(int id, const char* a1, const char* a2, const char* a3, const char* a4, const char* a5, const char* a6, const char* a7, const char* a8, const char* a9, const char* a10, const char* a11, const char* a12, const char* a13)
{
	char msg[256] = {0x20};
	memset(msg, COMMAND_WRITE_TRADE_DETAIL_INFO, 1);
	memset(msg + 1, 200, 1);
	memset(msg + 1 + 1, id, 1);
	FixSpace(msg, a1, 2 + 1, 20);
	FixSpace(msg, a2, 22 + 1, 16);
	FixSpace(msg, a3, 38 + 1, 13);
	FixSpace(msg, a4, 51 + 1, 30);
	FixSpace(msg, a5, 81 + 1, 40);
	FixSpace(msg, a6, 121 + 1, 9);
	FixSpace(msg, a7, 130 + 1, 30);
	FixSpace(msg, a8, 160 + 1, 8);
	FixSpace(msg, a9, 168 + 1, 6);
	FixSpace(msg, a10, 174 + 1, 4);
	FixSpace(msg, a11, 178 + 1, 4);
	FixSpace(msg, a12, 182 + 1, 8);
	FixSpace(msg, a13, 190 + 1, 8);
	
	return Execute(msg);
}

int ReadUserInfo(char* info)
{
	char msg[24] = {0};
	memset(msg, COMMAND_READ_USER_INFO, 1);
	memset(msg + 1, 1, 1);

	return ExecuteRead(msg, info);
}

int ReadTradeSummaryInfo(char* info)
{
	char msg[24] = {0};
	memset(msg, COMMAND_READ_TRADE_SUMMARY_INFO, 1);
	memset(msg + 1, 1, 1);

	return ExecuteRead(msg, info);
}

int ReadTradeDetailInfo(int id, char* info)
{
	char msg[24] = {0};
	memset(msg, COMMAND_READ_TRADE_DETAIL_INFO, 1);
	memset(msg + 1, 2, 1);
	memset(msg + 2, id, 1);

	return ExecuteRead(msg, info);
}
