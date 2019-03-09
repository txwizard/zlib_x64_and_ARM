/*
    ============================================================================

    File Name:			ProgramIDFromArgV.C

    Header:				At present, this function has no corresponding header to
                        call "home." At least for now, it is anticipated that it
                        will be declared in the main application header (e. g.,
                        stdafx.h).

    File Synopsis:		This file defines function ProgramIDFromArgV.

    Function Synopsis:	ProgramIDFromArgV provides a portable mechanism to 
                        identify the name of a program, for display on its
                        console. Hence, it depends exclusively on CRT routines.

    Remarks:			A problem discovered on Tuesday, 05 July 2016 led to new
                        code that leverages two macros, one in MathMacros_WW.H,
                        and the other in TcharMacros_WW.H. Though I could have
                        taken advantage of my memory allocation macros, I chose
                        to leave the memory allocation as is, idiosyncrasies and
                        all, to preserve compatibility with the CRT library, at
						the cost of the extra overhead incurred by using native
						Windows memory allocation routines indirectly through
						the CRT memory allocators.

    Author:				David A. Gray

	License:            Copyright (C) 2015-2017, David A. Gray. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	*   Redistributions of source code must retain the above copyright notice,
	this list of conditions and the following disclaimer.

	*   Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.

	*   Neither the name of David A. Gray nor the names of his contributors may
	be used to endorse or promote products derived from this software without
	specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL David A. Gray BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2015/01/04 DAG Function created and tested to meet an immediate need.

    2015/05/06 DAG Replace all char entities with char entities, so that this
                   routine works in either ANSI or Unicode.

    2015/05/21 DAG 1) Revert from C++ to C.

                   2) Make this source file freestanding with respect to any
                      project that includes it.

                   3) Truncate the extension, too.

    2015/05/25 DAG Switch from the default calling convention (currently _cdecl)
                   to the ever so slightly more efficient (more so in a debug
                   build than a release build) __pascal.

    2015/05/27 DAG Correct errors in the degenerate cases that dropped the first
                   character of the program when the name is unqualified, and
                   causes it to be completely truncated when the extension is
                   omitted.

    2016/07/07 DAG Correct errors in the prime case that started the extension
                   delimiter scan way beyond the end of the string, posing a 
                   small risk of returning too many characters in the event that
                   the core between the end of the program name string and where
                   the scan started happened to contain the sought delimiter
                   character, stopping the scan prematurely.

	2019/03/07 DAG At long last, this routine has a header to call home,
	               AppHelpers.h, along with a proper open source license. The
				   argument is renamed plpszArg0, from plpPgmPtr, to align with
				   argument name used by ShowProgramInfo, through which it is
				   called, and to clarify that it must point to argv[0].
				   With a one-line change to acommodate the fact that MakePtr
				   yields an ivalid pointer, this routine works in either 32 or
				   64 bit implementations.
    ============================================================================
*/

#include <stdlib.h>

#include "..\vstudio\targetver.h"

#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#undef _UNICODE

#include "..\vstudio\AppHelpers.h"

//	----------------------------------------------------------------------------
//	Since CommonConstants_P6C.H is out of the picture, MathMacros_WW.H and
//	TcharMacros_WW.H must follow windows.h, as they would if they were included
//	via CommonConstants_P6C.H. In particular, TcharMacros_WW.H must follow
//	windows.h because the default implementation of the memory allocator macros
//	calls HeapAlloc with its dwFlags argument set to HEAP_ZERO_MEMORY.
//
//	For the same reason, stdio.h follows windows.h, while tchar.h comes with
//	TcharMacros_WW.H.
//	----------------------------------------------------------------------------

#include <stdio.h>						// TcharMacros_WW.H requires stdio.h, and insists that it be explicitly included first, to call the resultant CRT library dependencies to your immediate attention.
#include "..\vstudio\MathMacros_WW.H"	// Since TcharMacros_WW.H is included, MathMacros_WW.H comes along for the ride.
#include "..\vstudio\TcharMacros_WW.H"	// Since the only way to avoid having HEAP_ZERO_MEMORY defined in advance is to completely disable the heap allocator macros, and I need windows.h anyway, I'll take the least burdensome option, and have this header follow it.

//	----------------------------------------------------------------------------
//	Since neither of these messages is likely ever to be needed in production, I
//	deviated from my usual practice, and hard coded them.
//
//	2016/07/06: Marking everything static excludes it from the externally linked
//	            symbol table, to which they would otherwise belong because they
//				are defined at file scope and have static initializers.
//	----------------------------------------------------------------------------

static char chrArg0IsNull  [ ]					= TEXT ( "ERROR: The first string in the argument list passed into routine ProgramIDFromArgV is a null reference.\n" ) ;
static char chrArg0IsBlank [ ]					= TEXT ( "ERROR: The first string in the argument list passed into routine ProgramIDFromArgV is the empty string.\n" ) ;

static char chrPathDlm [ ]						= TEXT ( "\\" ) ;
static char chrExtnDlm [ ]						= TEXT ( "." ) ;

static char * lpchrArg0IsNull					= ( char * ) &chrArg0IsNull ;
static char * lpchrArg0IsBlank					= ( char * ) &chrArg0IsBlank ;
static char * lpchrPathDlm						= ( char * ) &chrPathDlm ;

char * __stdcall ProgramIDFromArgV ( const char * plpszArg0 )
{	// Unlike C++, straight C needs everything defined before any executable code, apart from initializers.
    char *		rlpBaseNameByItself				= NULL ;

    BOOL		fBaseNameIsolated				= FALSE ;
    BOOL		fIsFirstDoLoop					= TRUE ;

    int			intPgmIdLengthbBytes			= -1 ;
    int			intPgmPtrLength					= -1 ;

    char *		lpLastCharacterInString			= NULL ;
    char *		lpLastDelimiterScan				= NULL ;
    char *		lpLastExtnDelimiter				= NULL ;
    char *		lpLastPathDelimiter				= NULL ;

    if ( plpszArg0 )
    {
        if ( ( intPgmPtrLength = intPgmPtrLength = _tcslen ( plpszArg0 ) ) )
        {
            lpLastDelimiterScan					= ( char * ) plpszArg0 ;
            lpLastPathDelimiter					= ( char * ) plpszArg0 ;

            do  // while ( lpLastDelimiterScan ) ;
            {
                lpLastDelimiterScan				= _tcsstr ( lpLastDelimiterScan ,
                                                            lpchrPathDlm ) ;

                if ( lpLastDelimiterScan )
                {
                    if ( fIsFirstDoLoop )
                    {
                        fIsFirstDoLoop			= FALSE ;
                    }	// TRUE (degenerate case, where the program name is unqualified) block, if ( fIsFirstDoLoop )

                    lpLastPathDelimiter			= lpLastDelimiterScan ;
                    lpLastDelimiterScan++ ;
                }	// TRUE block, if ( lpLastDelimiterScan )
                else
                {
                    if ( fIsFirstDoLoop )
                    {
                        fIsFirstDoLoop			= FALSE ;
                    }	// TRUE (degenerate case, where the program name is unqualified) block, if ( fIsFirstDoLoop )
                    else
                    {
                        lpLastPathDelimiter++ ;
                    }	// FALSE (standard case, where the program name is at least partially qualified) block, if ( fIsFirstDoLoop )
                }	// FALSE block, if ( lpLastDelimiterScan )
            } while ( lpLastDelimiterScan ) ;

            //	----------------------------------------------------------------
            //	Sanity check the string pointer. Find the extension delimiter,
            //	unless it is NULL.
            //	----------------------------------------------------------------

            if ( lpLastPathDelimiter )
            {
				#pragma warning ( suppress : 4047 )
				lpLastCharacterInString			= ( DWORD_PTR ) ( plpszArg0 + TcharsToBytesP6C( ( OrdinalToArrayIndexP6C( intPgmPtrLength ) ) ) );
                lpLastExtnDelimiter				= lpLastCharacterInString;

                do
                {
                    if ( ( char ) lpLastExtnDelimiter [ ARRAY_FIRST_ELEMENT_P6C ] == chrExtnDlm [ ARRAY_FIRST_ELEMENT_P6C ] )
                    {	// Found extension delimiter.
                        fBaseNameIsolated		= TRUE;
                    }	// TRUE (Extension delimiter found.) block, if ( ( char ) lpLastExtnDelimiter [ ARRAY_FIRST_ELEMENT_P6C ] == chrExtnDlm [ ARRAY_FIRST_ELEMENT_P6C ] )
                    else
                    {
                        lpLastExtnDelimiter		= _tcsdec ( plpszArg0 ,
                                                            lpLastExtnDelimiter ) ;

                        if ( ( DWORD_PTR ) lpLastExtnDelimiter == ( DWORD_PTR ) lpLastPathDelimiter )
                        {	// Reached the beginning of the base name.
                            fBaseNameIsolated	= TRUE;
                        }	// if ( ( DWORD_PTR ) lpLastExtnDelimiter == ( DWORD_PTR ) lpLastPathDelimiter )
                    }	// TRUE (Extension delimiter not yet found.) block, if ( ( char ) lpLastExtnDelimiter [ ARRAY_FIRST_ELEMENT_P6C ] == chrExtnDlm [ ARRAY_FIRST_ELEMENT_P6C ] )
                }
                while ( !fBaseNameIsolated ) ;

				//	------------------------------------------------------------
				//	Though I almost always save computed values for reuse, since
				//	the compiler optimizes away the multiplcation operation, it
				//	is not worth the extra storage to compute and store the
				//	product.
				//	------------------------------------------------------------

                intPgmIdLengthbBytes			=    ( ( DWORD_PTR ) lpLastExtnDelimiter     == ( DWORD_PTR ) lpLastPathDelimiter )
                                                   ? ( ( DWORD_PTR ) lpLastCharacterInString -  ( DWORD_PTR ) lpLastPathDelimiter )
                                                   : ( ( DWORD_PTR ) lpLastExtnDelimiter     -  ( DWORD_PTR ) lpLastPathDelimiter ) ;

				#if defined ( _char_MACROS_SEH_ALLOCATORS_ )
					rlpBaseNameByItself			= AllocBytes_WW ( intPgmIdLengthbBytes + sizeof ( char ) ) ;
				#elif defined ( WIN32 )
					rlpBaseNameByItself			= HeapAlloc ( GetProcessHeap ( ) ,
		                                                      HEAP_ZERO_MEMORY ,
                                                              intPgmIdLengthbBytes + sizeof ( char ) ) ;
				#else
				rlpBaseNameByItself = malloc ( intPgmIdLengthbBytes + sizeof ( char ) );
					memset ( &zcpr ,
						     0 ,
						     sizeof ( intPgmIdLengthbBytes + sizeof( char ) ) );
				#endif	/* FALSE block, #if defined ( _char_MACROS_SEH_ALLOCATORS_ ) AND #elif defined ( WIN32 ) */

                memcpy ( rlpBaseNameByItself ,
                         lpLastPathDelimiter ,
                         intPgmIdLengthbBytes ) ;

                return rlpBaseNameByItself ;
            }	// TRUE (expected outcome) block, if ( lpLastPathDelimiter )
            else
            {
                return lpchrArg0IsBlank ;
            }	// FALSE (UNexpected outcome) block, if ( lpLastPathDelimiter )
        }	// TRUE (expected outcome) block, if ( ( intPgmPtrLength = intPgmPtrLength = _tcslen ( plpszArg0 ) ) )
        else
        {
            return lpchrArg0IsBlank ;
        }	// FALSE (UNexpected outcome) if ( ( intPgmPtrLength = intPgmPtrLength = _tcslen ( plpszArg0 ) ) )
    }	// TRUE (expected outcome) block, if ( plpszArg0 )
    else
    {
        return lpchrArg0IsNull ;
    }	// FALSE (UNexpected outcome) if ( plpszArg0 )
}	// LPTSTR ProgramIDFromArgV