// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CPUCARDFUNCTIONS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CPUCARDFUNCTIONS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CPUCARDFUNCTIONS_EXPORTS
#define CPUCARDFUNCTIONS_API __declspec(dllexport)
#else
#define CPUCARDFUNCTIONS_API __declspec(dllimport)
#endif

extern "C" CPUCARDFUNCTIONS_API int ReadTradeDetailFromCard(void);

extern "C" CPUCARDFUNCTIONS_API int ReadTradeSummaryFromCard(void);

extern "C" CPUCARDFUNCTIONS_API int ReadUserInfoFromCard(void);

extern "C" CPUCARDFUNCTIONS_API int WriteTradeDetailToCard(void);

extern "C" CPUCARDFUNCTIONS_API int WriteTradeSummaryToCard(void);

extern "C" CPUCARDFUNCTIONS_API int WriteUserInfoToCard(void);
