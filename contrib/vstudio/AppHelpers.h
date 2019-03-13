#if !defined ( APPHELPERS_WIN32_INCLUDED )
#define APPHELPERS_WIN32_INCLUDED

#define GFV_SUCCEEDED					0x00000000
#define GFV_GETFILEVERSIONINFOSIZE_FAIL	0x00000001
#define GFV_GETFILEVERSIONINFO_FAIL		0x00000002
#define GFV_VERQUERYVALUE_FAIL			0x00000003

#if defined ( __cplusplus )
extern "C" {
#endif  /* #if defined ( __cplusplus ) */
	int     __stdcall GetFileVersion
	(
		char *       plpOutBuf ,		// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
		const int    pintOutBufSize		// Capacity of buffer plpOutBuf in wide characters
	);

	char * __stdcall ProgramIDFromArgV
	(
		const char * plpszArg0			// Pointer to argv [0], which always contains the name of the program that started the process
	);

	int     __stdcall ReportSystemError
	(
		const int pintFinalReturnCode
	);

	void    __stdcall ShowPlatform
	( 
		const char * plpszFormatString
	);

	int     __stdcall ShowProgramInfo
	(
		char * plpszArg0				// Pointer to argv [0], which always contains the name of the program that started the process
	);
#if defined ( __cplusplus )
}   /* ... extern "C" */
#endif  /* #if defined ( __cplusplus ) */
#endif	/* #if !defined ( APPHELPERS_WIN32_INCLUDED ) */