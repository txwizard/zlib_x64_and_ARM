#undef UNICODE
#undef _UNICODE

#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>

#include "..\vstudio\AppHelpers.h"


void __stdcall ShowPlatform ( const char * plpszFormatString )
{
	#if defined ( PLATFORM_IS_Win32 )
		printf ( plpszFormatString , "WIN32" );
	#endif	/* #if defined ( PLATFORM_IS_Win32 ) */

	#if defined ( PLATFORM_IS_x64 )
		printf ( plpszFormatString , "x64" );
	#endif	/* #if defined ( PLATFORM_IS_x64 ) */

	#if defined ( PLATFORM_IS_ARM )
		printf ( plpszFormatString , "ARM" );
	#endif	/* #if defined ( PLATFORM_IS_ARM ) */

	#if defined ( PLATFORM_IS_ARM64 )
		printf ( plpszFormatString , "ARM64" );
	#endif	/* #if defined ( PLATFORM_IS_ARM64 ) */
}	// ShowPlatform