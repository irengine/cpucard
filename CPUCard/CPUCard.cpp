// CPUCard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inifile.h"
#include "tstdlibs.h"
#include "CardFunctions.h"

#define USER_INFO_FILE_NAME		"c:\\scweigh\\userinfo.ini"
#define SUMMARY_FILE_NAME		"c:\\scweigh\\dealtotal.ini"
#define DETAIL_FILE_NAME		"c:\\scweigh\\dealdetail.ini"

void WriteUserInfoFile();
void WriteSummaryFile();
void WriteDetailFile();

void ReadUserInfoData(char* userinfo);
void ReadSummaryData(char* summary);
void ReadDetailData(std::string id, char* detail);

void WriteUserInfoData();
void WriteSummaryData();
void WriteDetailData();

void TestRead();
void TestWrite();


int _tmain(int argc, _TCHAR* argv[])
{
	TestRead();
	TestWrite();

	return 0;
}

void TestRead()
{
	if (Setup(1) == S_OK)
	{
		//char userinfo[256] = {0};
		//ReadUserInfo(userinfo);
		//ReadUserInfoData(userinfo);

		char summary[256] = {0};
		ReadTradeSummaryInfo(summary);
		ReadSummaryData(summary);

		//// Get id from ini file
		//try
		//{
		//	CIniFile fDetail;
		//	fDetail.Load(DETAIL_FILE_NAME);

		//	std::string num = fDetail.GetSection("deallist")->GetKey("num")->GetValue();

		//	int i = atoi(num.c_str());
		//	char detail[256] = {0};
		//	ReadTradeDetailInfo(i, detail);
		//	ReadDetailData(num, detail);
		//	return;
		//}
		//catch(...)
		//{
		//	std::cout << "Error: Please check parameters in ini file.";
		//}
	}
	else
	{
		std::cout << "Error: Search card failed.";
	}

	return;
}

void TestWrite()
{
	if (Setup(1) == S_OK)
	{
		//WriteUserInfoData();

		WriteSummaryData();

		//WriteDetailData();

		return;
	}
	else
	{
		std::cout << "Error: Search card failed.";
	}

	return;
}

void WriteUserInfoData()
{
	CIniFile fUserInfo;

	fUserInfo.Load(USER_INFO_FILE_NAME);

	std::string cardtype = fUserInfo.GetSection("userifmt")->GetKey("cardtype")->GetValue();
	std::string cardid = fUserInfo.GetSection("userifmt")->GetKey("cardid")->GetValue();
	std::string clientno = fUserInfo.GetSection("userifmt")->GetKey("clientno")->GetValue();
	std::string clientname = fUserInfo.GetSection("userifmt")->GetKey("clientname")->GetValue();
	std::string clientid = fUserInfo.GetSection("userifmt")->GetKey("clientid")->GetValue();
	std::string clientphone = fUserInfo.GetSection("userifmt")->GetKey("clientphone")->GetValue();
	std::string clienttype = fUserInfo.GetSection("userifmt")->GetKey("clienttype")->GetValue();

	WriteUserInfo(cardtype.c_str(),
		cardid.c_str(),
		clientno.c_str(),
		clientname.c_str(),
		clientid.c_str(),
		clientphone.c_str(),
		clienttype.c_str());
}

void WriteSummaryData()
{
	CIniFile fSummary;

	fSummary.Load(SUMMARY_FILE_NAME);

	std::string date = fSummary.GetSection("dealtotal")->GetKey("date")->GetValue();
	std::string dealnum = fSummary.GetSection("dealtotal")->GetKey("dealnum")->GetValue();
	std::string dealtype = fSummary.GetSection("dealtotal")->GetKey("dealtype")->GetValue();

	WriteTradeSummaryInfo(date.c_str(),
		String2Int(dealnum),
		dealtype.c_str());
}

void WriteDetailData()
{
	CIniFile fDetail;

	fDetail.Load(DETAIL_FILE_NAME);

	std::string num = fDetail.GetSection("deallist")->GetKey("num")->GetValue();

	std::string clientno = fDetail.GetSection("deallist")->GetKey("clientno")->GetValue();
	std::string gysm = fDetail.GetSection("deallist")->GetKey("gysm")->GetValue();
	std::string uid = fDetail.GetSection("deallist")->GetKey("uid")->GetValue();
	std::string areano = fDetail.GetSection("deallist")->GetKey("areano")->GetValue();
	std::string quan = fDetail.GetSection("deallist")->GetKey("quan")->GetValue();
	std::string weight = fDetail.GetSection("deallist")->GetKey("weight")->GetValue();
	std::string amount = fDetail.GetSection("deallist")->GetKey("amount")->GetValue();
	std::string backward = fDetail.GetSection("deallist")->GetKey("backward")->GetValue();
	std::string basename = fDetail.GetSection("deallist")->GetKey("basename")->GetValue();
	std::string producer = fDetail.GetSection("deallist")->GetKey("producer")->GetValue();
	std::string lastgybm = fDetail.GetSection("deallist")->GetKey("lastgybm")->GetValue();
	std::string lastgysm = fDetail.GetSection("deallist")->GetKey("lastgysm")->GetValue();
	std::string lastbkwd = fDetail.GetSection("deallist")->GetKey("lastbkwd")->GetValue();

	int i = atoi(num.c_str());

	WriteTradeDetailInfo(i,
		clientno.c_str(),
		gysm.c_str(),
		uid.c_str(),
		areano.c_str(),
		quan.c_str(),
		weight.c_str(),
		amount.c_str(),
		backward.c_str(),
		basename.c_str(),
		producer.c_str(),
		lastgybm.c_str(),
		lastgysm.c_str(),
		lastbkwd.c_str());
}

void ReadUserInfoData(char* userinfo)
{
	char msg[64];

	std::stringstream sUserInfo;
	sUserInfo << "[userifmt]" << std::endl;

	// cardtype		length	2
	memset(msg, 0, 64);
	memcpy(msg, userinfo, 2);
	sUserInfo << "cardtype=" << msg << std::endl;

	// cardid		length	10
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 2, 10);
	sUserInfo << "cardid=" << msg << std::endl;

	// clientno		length	13
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 12, 13);
	sUserInfo << "clientno=" << msg << std::endl;

	// clientname	length	30
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 25, 30);
	sUserInfo << "clientname=" << msg << std::endl;

	// clientid		length	18
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 55, 18);
	sUserInfo << "clientid=" << msg << std::endl;

	// clientphone		length	13
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 73, 13);
	sUserInfo << "clientphone=" << msg << std::endl;

	// clienttype		length	2
	memset(msg, 0, 64);
	memcpy(msg, userinfo + 86, 2);
	sUserInfo << "clienttype=" << msg << std::endl;

	CIniFile fUserInfo;
	sUserInfo >> fUserInfo;

	fUserInfo.Save(USER_INFO_FILE_NAME);
}

void ReadSummaryData(char* summary)
{
	char msg[64];
	int cnt = 0;

	std::stringstream sSummary;
	sSummary << "[dealtotal]" << std::endl;

	// date		length	8
	memset(msg, 0, 64);
	memcpy(msg, summary, 8);
	sSummary << "date=" << msg << std::endl;

	// dealnum	length	1
	cnt = 0;
	memcpy(&cnt, summary + 8, 1);
	sSummary << "dealnum=" << cnt << std::endl;

	// dealtype	length	1
	memset(msg, 0, 64);
	memcpy(msg, summary + 9, 1);
	sSummary << "dealtype=" << msg << std::endl;

	CIniFile fSummary;
	sSummary >> fSummary;

	fSummary.Save(SUMMARY_FILE_NAME);
}

void ReadDetailData(std::string id, char* detail)
{
	//[deallist]
	//;第几笔交易
	//num=1
	//;供货客户统一编码
	//clientno=0110092
	//;供货客户名称
	//gysm=张三
	//;商品统一编码
	//uid=31
	//;产地统一编码
	//areano=31
	//;成交数量
	//quan=5
	//;成交重量
	//weight=2000
	//;成交金额
	//amount=4300
	//;追溯码
	//backward=010123456789a
	//;生产基地
	//basename=山东寿光
	//;生产者
	//producer=李明
	//;一级批供应商编码
	//lastgybm=0200891
	//;一级批供应商名称
	//lastgysm=王勇
	//;一级批追溯码
	//lastbkwd=010123456789a

	//char detail[256] = {0x30, 0x32, 0x30, 0x30, 0x30, 0x30, 0x34, 0xBD, 0xF0, 0xB0,
	//					0xAE, 0xC1, 0xBC, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30,
	//					0x30, 0x30, 0x31, 0x30, 0x31, 0x31, 0x2E, 0x30, 0x30, 0x20,
	//					0x20, 0x20, 0x20, 0x31, 0x32, 0x35, 0x2E, 0x30, 0x30, 0x20,
	//					0x20, 0x20, 0x20, 0x33, 0x37, 0x35, 0x2E, 0x30, 0x30, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x34, 0x30, 0x30, 0x33, 0x30,
	//					0x30, 0x32, 0x31, 0x30, 0x30, 0x39, 0x32, 0x39, 0xC9, 0xCF,
	//					0xBA, 0xA3, 0xC4, 0xCF, 0xD1, 0xF4, 0xCA, 0xDF, 0xB2, 0xCB,
	//					0xB4, 0xF3, 0xC5, 0xEF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xBD, 0xF0,
	//					0xB0, 0xAE, 0xC1, 0xBC, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x32,
	//					0x30, 0x30, 0x30, 0x30, 0x34, 0xBD, 0xF0, 0xB0, 0xAE, 0xC1,
	//					0xBC, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	//					0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x31, 0x31,
	//					0x33, 0x32, 0x31, 0x32, 0x35, 0x38, 0x39, 0x35};

	char msg[64];

	//FixSpace(msg, a1, 2, 7);
	//FixSpace(msg, a2, 9, 30);
	//FixSpace(msg, a3, 39, 6);
	//FixSpace(msg, a4, 45, 2);
	//FixSpace(msg, a5, 47, 8);
	//FixSpace(msg, a6, 55, 10);
	//FixSpace(msg, a7, 65, 12);
	//FixSpace(msg, a8, 77, 13);
	//FixSpace(msg, a9, 90, 40);
	//FixSpace(msg, a10, 130, 20);
	//FixSpace(msg, a11, 150, 7);
	//FixSpace(msg, a12, 157, 30);
	//FixSpace(msg, a13, 187, 13);

	std::stringstream sDetail;
	sDetail << "[deallist]" << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, id.c_str(), strlen(id.c_str()));
	sDetail << "num=" << msg << std::endl;
	
	memset(msg, 0, 64);
	memcpy(msg, detail, 7);
	sDetail << "clientno=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 7, 30);
	sDetail << "gysm=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 37, 6);
	sDetail << "uid=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 43, 2);
	sDetail << "areano=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 45, 8);
	sDetail << "quan=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 53, 10);
	sDetail << "weight=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 63, 12);
	sDetail << "amount=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 75, 13);
	sDetail << "backward=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 88, 40);
	sDetail << "basename=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 128, 20);
	sDetail << "producer=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 148, 7);
	sDetail << "lastgybm=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 155, 30);
	sDetail << "lastgysm=" << msg << std::endl;

	memset(msg, 0, 64);
	memcpy(msg, detail + 185, 13);
	sDetail << "lastbkwd=" << msg << std::endl;

	CIniFile fDetail;
	sDetail >> fDetail;

	fDetail.Save(DETAIL_FILE_NAME);
}