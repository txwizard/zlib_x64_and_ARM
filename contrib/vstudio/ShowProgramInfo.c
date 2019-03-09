#undef UNICODE
#undef _UNICODE

#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>

#include "..\vstudio\AppHelpers.h"


int __stdcall ShowProgramInfo ( char * plpszArg0 )
{
#define BUFSIZE_VERSION_STRING			0x00000020

	int rintResult = ERROR_SUCCESS;

	char * lpszVersionString = malloc ( BUFSIZE_VERSION_STRING );
	
	if ( rintResult = GetFileVersion ( lpszVersionString , BUFSIZE_VERSION_STRING ) )
	{
		printf ( "ERROR: Internal routine GetFileVersion returned a status code of %d\n" ,
			     rintResult );
	}	// TRUE (unanticipated outcome) block, if ( rintResult = GetFileVersion ( lpszVersionString , BUFSIZE_VERSION_STRING ) )
	else
	{
		printf ( "%s, version %s begin\n\n" ,
			     ProgramIDFromArgV ( plpszArg0 ) ,
		         lpszVersionString );
	}	// FALSE (anticipated outcome) block, if ( rintResult = GetFileVersion ( lpszVersionString , BUFSIZE_VERSION_STRING ) )

	free ( lpszVersionString );

	ShowPlatform ( "Execution Platform = %s\n\n" );

	return rintResult;
}	// ShowProgramInfo