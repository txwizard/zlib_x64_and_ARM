#undef UNICODE
#undef _UNICODE

#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>

#include "..\vstudio\AppHelpers.h"


char * __stdcall GetExeHameFromWindows ( );

int    __stdcall GetFileVersion
(
    char *       plpOutBuf ,			// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
	const int    pintOutBufSize			// Capacity of buffer plpOutBuf in wide characters
)
{
	LPTSTR lpModuleFileName = GetExeHameFromWindows ( );
	DWORD dwHandle , dwVersionInfoSize = GetFileVersionInfoSize ( lpModuleFileName ,
		                                                          &dwHandle );
	
	if ( !dwVersionInfoSize )
	{
		printf ( "GetFileVersion = lpModuleFileName = %s" ,
			     lpModuleFileName );
		return ReportSystemError ( GFV_GETFILEVERSIONINFOSIZE_FAIL );
	}	// if ( !dwVersionInfoSize )

	wchar_t * buf = malloc ( dwVersionInfoSize );
	memset ( buf ,
		     0 ,
		     dwVersionInfoSize );

	if ( !GetFileVersionInfo ( lpModuleFileName ,
		                       dwHandle ,
		                       dwVersionInfoSize ,
		                       &buf [ 0 ] ) )
	{
		free ( buf );
		return ReportSystemError ( GFV_GETFILEVERSIONINFO_FAIL );
	}	// if ( !GetFileVersionInfo ( lpwcFileName , dwHandle , dwVersionInfoSize , &buf [ 0 ] ) )

	VS_FIXEDFILEINFO * pvi;
	dwVersionInfoSize = sizeof ( VS_FIXEDFILEINFO );
	
	if ( !VerQueryValue ( &buf [ 0 ] ,
		                  "\\" ,
		                  ( LPVOID* ) &pvi ,
		                  ( unsigned int* ) &dwVersionInfoSize ) )
	{
		free( buf );
		return ReportSystemError ( GFV_VERQUERYVALUE_FAIL);
	}	// if ( !VerQueryValue ( &buf [ 0 ] , L"\\" , ( LPVOID* ) &pvi , ( unsigned int* ) &dwVersionInfoSize ) )

	_stprintf_s ( plpOutBuf ,
		          pintOutBufSize ,
		          "%d.%d.%d.%d" ,
		          pvi->dwProductVersionMS >> 16 ,			// Major
		          pvi->dwFileVersionMS & 0xFFFF ,			// Minor
		          pvi->dwFileVersionLS >> 16 ,				// Build
		          pvi->dwFileVersionLS & 0xFFFF );			// Revision
	free( buf );

	return GFV_SUCCEEDED;
}	// GetFileVersion


char * __stdcall GetExeHameFromWindows ( )
{
	static char  rachrModuleNameBuffer [ MAX_PATH ];

	if ( GetModuleFileName ( NULL ,							// HMODULE hModule:		A handle to the loaded module whose path is being requested. If this parameter is NULL, GetModuleFileName retrieves the path of the executable file of the current process.
		                     &rachrModuleNameBuffer ,		// LPSTR   lpFilename:	A pointer to a buffer that receives the fully qualified path of the module. If the length of the path is less than the size that the nSize parameter specifies, the function succeeds and the path is returned as a null-terminated string. If the length of the path exceeds the size that the nSize parameter specifies, the function succeeds and the string is truncated to nSize characters including the terminating null character.
		                     MAX_PATH ) )					// DWORD   nSize:		The size of the lpFilename buffer, in TCHARs
	{
		printf ( "\nDEBUG: String returned by GetModuleFileName = %s\n" ,
			     &rachrModuleNameBuffer );
		return rachrModuleNameBuffer;
	}	// TRUE (anticipated outcome) block, if ( GetModuleFileName ( NULL , &rachrModuleNameBuffer , MAX_PATH ) )
	else
	{
		return NULL;
	}	// FALSE (unanticipated outcome) block, if ( GetModuleFileName ( NULL , &rachrModuleNameBuffer , MAX_PATH ) )
}	// GetExeHameFromWindows