// CPUCardFunctions.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "inifile.h"
#include "tstdlibs.h"
#include "CardFunctions.h"
#include "CPUCardFunctions.h"

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

int ReadTradeDetailFromCard(void)
{
	if (Setup(1) == S_OK)
	{
		// Get id from ini file
		try
		{
			CIniFile fDetail;
			fDetail.Load(DETAIL_FILE_NAME);

			std::string num = fDetail.GetSection("deallist")->GetKey("num")->GetValue();

			int i = atoi(num.c_str());
			char detail[256] = {0};
			ReadTradeDetailInfo(i, detail);
			ReadDetailData(num, detail);
		}
		catch(...)
		{
			return E_FAIL;
		}
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

int ReadTradeSummaryFromCard(void)
{
	if (Setup(1) == S_OK)
	{
		char summary[256] = {0};
		ReadTradeSummaryInfo(summary);
		ReadSummaryData(summary);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

int ReadUserInfoFromCard(void)
{
	if (Setup(1) == S_OK)
	{
		char userinfo[256] = {0};
		ReadUserInfo(userinfo);
		ReadUserInfoData(userinfo);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

int WriteTradeDetailToCard(void)
{
	if (Setup(1) == S_OK)
	{
		WriteDetailData();
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

int WriteTradeSummaryToCard(void)
{
	if (Setup(1) == S_OK)
	{
		WriteSummaryData();
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

int WriteUserInfoToCard(void)
{
	if (Setup(1) == S_OK)
	{
		WriteUserInfoData();
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

void TestRead()
{
	if (Setup(1) == S_OK)
	{
		char userinfo[256] = {0};
		ReadUserInfo(userinfo);
		ReadUserInfoData(userinfo);

		char summary[256] = {0};
		ReadTradeSummaryInfo(summary);
		ReadSummaryData(summary);

		// Get id from ini file
		try
		{
			CIniFile fDetail;
			fDetail.Load(DETAIL_FILE_NAME);

			std::string num = fDetail.GetSection("deallist")->GetKey("num")->GetValue();

			int i = atoi(num.c_str());
			char detail[256] = {0};
			ReadTradeDetailInfo(i, detail);
			ReadDetailData(num, detail);
			return;
		}
		catch(...)
		{
			std::cout << "Error: Please check parameters in ini file.";
		}
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
		WriteUserInfoData();

		WriteSummaryData();

		WriteDetailData();

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

	char mdealnum[64];
	String2NChar(mdealnum, dealnum, 1);

	WriteTradeSummaryInfo(date.c_str(),
		mdealnum,
		dealtype.c_str());
}

void WriteDetailData()
{
	CIniFile fDetail;

	fDetail.Load(DETAIL_FILE_NAME);

	std::string num = fDetail.GetSection("deallist")->GetKey("num")->GetValue();

	std::string traceno = fDetail.GetSection("deallist")->GetKey("traceno")->GetValue();
	std::string batchno = fDetail.GetSection("deallist")->GetKey("batchno")->GetValue();
	std::string sellercode = fDetail.GetSection("deallist")->GetKey("sellercode")->GetValue();
	std::string sellername = fDetail.GetSection("deallist")->GetKey("sellername")->GetValue();
	std::string producingarea = fDetail.GetSection("deallist")->GetKey("producingarea")->GetValue();
	std::string marketcode = fDetail.GetSection("deallist")->GetKey("marketcode")->GetValue();
	std::string marketname = fDetail.GetSection("deallist")->GetKey("marketname")->GetValue();
	std::string uid = fDetail.GetSection("deallist")->GetKey("uid")->GetValue();
	std::string areano = fDetail.GetSection("deallist")->GetKey("areano")->GetValue();
	std::string quantity = fDetail.GetSection("deallist")->GetKey("quantity")->GetValue();
	std::string weight = fDetail.GetSection("deallist")->GetKey("weight")->GetValue();
	std::string unitprice = fDetail.GetSection("deallist")->GetKey("unitprice")->GetValue();
	std::string vechicleno = fDetail.GetSection("deallist")->GetKey("vechicleno")->GetValue();

	char mquantity[64];
	String2NChar(mquantity, quantity, 4, 100);

	char mweight[64];
	String2NChar(mweight, weight, 4, 100);

	char munitprice[64];
	String2NChar(munitprice, weight, 8, 100);

	int i = atoi(num.c_str());

	WriteTradeDetailInfo(i,
		traceno.c_str(),
		batchno.c_str(),
		sellercode.c_str(),
		sellername.c_str(),
		producingarea.c_str(),
		marketcode.c_str(),
		marketname.c_str(),
		uid.c_str(),
		areano.c_str(),
		mquantity,
		mweight,
		munitprice,
		vechicleno.c_str());
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
	char val[5];

	std::stringstream sSummary;
	sSummary << "[dealtotal]" << std::endl;

	// date		length	8
	memset(msg, 0, 64);
	memcpy(msg, summary, 8);
	sSummary << "date=" << msg << std::endl;

	// dealnum	length	1
	memset(val, 0, 5);
	memcpy(val, summary + 8, 1);
	sSummary << "dealnum=" << NChar2Long(val, 1) << std::endl;

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
	char msg[64];
	char val[5];

	std::stringstream sDetail;
	sDetail << "[deallist]" << std::endl;

	// id
	memset(msg, 0, 64);
	memcpy(msg, id.c_str(), strlen(id.c_str()));
	sDetail << "num=" << msg << std::endl;
	
	// traceno		length	20
	memset(msg, 0, 64);
	memcpy(msg, detail, 20);
	sDetail << "traceno=" << msg << std::endl;

	// batchno		length	16
	memset(msg, 0, 64);
	memcpy(msg, detail + 20, 16);
	sDetail << "batchno=" << msg << std::endl;

	// sellercode	length	13
	memset(msg, 0, 64);
	memcpy(msg, detail + 36, 13);
	sDetail << "sellercode=" << msg << std::endl;

	// sellername	length	30
	memset(msg, 0, 64);
	memcpy(msg, detail + 49, 30);
	sDetail << "sellername=" << msg << std::endl;

	// producingarea	length	40
	memset(msg, 0, 64);
	memcpy(msg, detail + 79, 40);
	sDetail << "producingarea=" << msg << std::endl;

	// marketcode	length	9
	memset(msg, 0, 64);
	memcpy(msg, detail + 119, 9);
	sDetail << "marketcode=" << msg << std::endl;

	// marketname	length	30
	memset(msg, 0, 64);
	memcpy(msg, detail + 128, 30);
	sDetail << "marketname=" << msg << std::endl;

	// uid			length	8
	memset(msg, 0, 64);
	memcpy(msg, detail + 158, 8);
	sDetail << "uid=" << msg << std::endl;

	// areano		length	6
	memset(msg, 0, 64);
	memcpy(msg, detail + 166, 6);
	sDetail << "areano=" << msg << std::endl;

	// quantity		length	4
	memset(val, 0, 5);
	memcpy(val, detail + 172, 4);
	sDetail << "quantity=" << NChar2Float(val, 4, 100) << std::endl;

	// weight		length	4
	memset(val, 0, 5);
	memcpy(val, detail + 176, 4);
	sDetail << "weight=" << NChar2Float(val, 4, 100) << std::endl;

	// unitprice	length	8
	memset(val, 0, 9);
	memcpy(val, detail + 180, 8);
	sDetail << "unitprice=" << NChar2Float(val, 8, 100) << std::endl;

	// vechicleno	length	8
	memset(msg, 0, 64);
	memcpy(msg, detail + 188, 8);
	sDetail << "vechicleno=" << msg << std::endl;

	CIniFile fDetail;
	sDetail >> fDetail;

	fDetail.Save(DETAIL_FILE_NAME);
}