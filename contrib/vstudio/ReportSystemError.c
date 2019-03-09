#undef UNICODE
#undef _UNICODE

#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>

#include "..\vstudio\AppHelpers.h"

#ifndef RCDATA_MAX_LENGTH_P6C
#define RCDATA_MAX_LENGTH_P6C				4097
#endif	/* _RCDATA_MAX_LENGTH_P6C */

#ifndef RCDATA_MAX_BUFFER_P6C
#define RCDATA_MAX_BUFFER_P6C				RCDATA_MAX_LENGTH_P6C + 1
#endif	/* _RCDATA_MAX_LENGTH_P6C */

int __stdcall ReportSystemError ( const int pintFinalReturnCode )
{
	char achrFormatMessageBuffer [ RCDATA_MAX_BUFFER_P6C ];
	LPTSTR lpFmtMsgResStr = &achrFormatMessageBuffer;
	DWORD dwLastError = GetLastError ( );
	DWORD dwResult = FormatMessage ( FORMAT_MESSAGE_FROM_SYSTEM |
		                             FORMAT_MESSAGE_IGNORE_INSERTS , 			// DWORD dwFlags,       // source and processing options
		                             NULL ,                    					// lpSource             // message source
		                             dwLastError ,								// MessageID,, usually from GetLastError
		                             MAKELANGID ( LANG_NEUTRAL ,
			                                      SUBLANG_DEFAULT ) ,			// language identifier
		                             lpFmtMsgResStr ,							// Pointer to message buffer
		                             RCDATA_MAX_BUFFER_P6C ,         			// DWORD nSize, maximum  size of buffer
		                             NULL );                         			// System messages contain no arguments.

	if ( dwResult )
	{
		printf ( "System status code = %#08x (%d decimal): %s" ,
			     dwLastError ,
			     dwLastError ,
			     lpFmtMsgResStr );
	}	// TRUE (anticipated outcome) block, if ( dwResult )
	else
	{
		printf ( "An internal error arose while attempting to translate a system status code.\n\nThe status code in question is %#08x (%d decimal).\n\nThat, in turn, gave rise to status code %#08x (%d decimal).\n\n" ,
			     dwLastError ,
 			     dwLastError ,
			     GetLastError ( ) ,
			     GetLastError ( ) );
	}	// FALSE (unanticipated outcome) block, if ( dwResult )

	return pintFinalReturnCode;
}	// ReportSystemError