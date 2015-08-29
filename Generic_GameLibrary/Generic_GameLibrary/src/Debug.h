#ifndef Debug_h__
#define Debug_h__

// Debug Tools
#ifdef GGL_USE_DEBUG

#define GglDebug_PrintExceptionLine()					printf("\n**********iiCatch Exception!!**********\nfrom : %s [L%d]\nfunction: %s\n", __FILE__, __LINE__, __func__)
#define GglDebug_PrintAlertLine(str)					printf("\n*****iiALERT!!*****\nSummary : %s\nfrom : %s [L%d]\n", str, __FILE__, __LINE__)
#define GglDebug_PrintInformationLine(str)				printf("\n----- Information -----\nSummary : %s\n   from : %s [L%d]\n", str, __FILE__, __LINE__)

#else

#define GglDebug_PrintExceptionLine()
#define GglDebug_PrintAlertLine(str)
#define GglDebug_PrintInformationLine(str)

#endif

#endif