//{{NO_DEPENDENCIES}}
#ifndef _CHARPOSMACROS_WW_DEFINED
#define _CHARPOSMACROS_WW_DEFINED

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

/*
    ============================================================================

    File Name:          CharPosMacros_WW.H

    File Synopsis:      This C/C++ header file defines some macros to simplify
                        some fairly simple, but obtuse character manipulations
                        and string evaluations.

    Remarks:            Since it is composed entirely of macros, there is no DLL
                        or link library associated with this header.

                        This header was created when I moved SecondCharOfString
                        from UniqueDENameGen\StdAfx.h and moved the other macros
                        from P6CStringLib1.H, so that the whole set can be made
                        available through several related headers without the
                        overhead of maintaining multiple copies, in the unlikely
                        event that I find a bug in any of them.

                        The first header to incorporate this one by inclusion is
                        Inclusion of MathMacros_WW.H

    License:            Copyright (C) 2014-2019, David A. Gray. All rights reserved.

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
    ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Date Created:       Sunday, 17 August 2014

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2014/08/17 DAG Header created and first used in RoboCopyExitCodeMapper.exe.

    2015/03/07 DAG Add ThirdCharOfString and StringIsEffectivelyEmptyWW, both of
                   which are fully exercised by LineLab.exe.

    2015/03/13 DAG Move macros BytesToTCHARsP6C and ByteOffsetToTCHARsP6C from
                   TcharMacros_WW.H to this header; add //{{NO_DEPENDENCIES}} to
                   this header, since this is the first time since I discovered
                   and tested it in TcharMacros_WW.H that this file needed work.

    2016/01/20 DAG Define the generic case macro, NthCharOfString.

    2016/11/27 DAG Add my BSD license, and correct a couple of typographical
                   errors.

    2016/11/27 DAG Define ByteOffsetWW, to accompany ByteOffsetToTCHARsP6C, for
                   applications that need offsets expressed in bytes, such as,
                   for example, to feed to memory allocators.

	2019/03/06 DAG Adapt for incorporation into my zlib port.
	============================================================================
*/

#include "..\vstudio\MathMacros_WW.H"

/*
    ----------------------------------------------------------------------------
    Name:       BytesToTCHARsP6C

    Synopsis:   Given a size expressed in bytes, compute its capacity in TCHARs.

    In:         pNBytes             = Difference between two addresses expressed
                                      in bytes

    Out:        The return value is the number of TCHARs that fit into that many
                bytes.
    ----------------------------------------------------------------------------
*/

#if !defined ( BytesToTCHARsP6C )
    #define BytesToTCHARsP6C(pNBytes)   ( pNBytes / sizeof ( TCHAR ) )
#endif  /* #if !defined ( BytesToTCHARsP6C ) */

/*
    ----------------------------------------------------------------------------
    Name:       ByteOffsetWW and ByteOffsetToTCHARsP6C

    Synopsis:   Given a pair of addresses, such as the start of a string and the
                location where a substring was found, return the offset,
                expressed in TCHARs.

    In:         pBaseAddr               = Address of beginning of string
                pOffsetAddr             = Address where substring starts

    Out:        ByteOffsetWW:           = offset, expressed in bytes
                ByteOffsetToTCHARsP6C   = offset, expressed in TCHARs
    ----------------------------------------------------------------------------
*/

#if !defined ( ByteOffsetWW )
    #define ByteOffsetWW(pBaseAddr, pOffsetAddr)   \
                                        ( ( DWORD_PTR ) pOffsetAddr - ( DWORD_PTR ) pBaseAddr )
#endif /* #if !defined ( ByteOffsetWW ) */

#if !defined ( ByteOffsetToTCHARsP6C )
    #define ByteOffsetToTCHARsP6C(pBaseAddr, pOffsetAddr)   \
                                        ( BytesToTCHARsP6C ( ( ( DWORD_PTR ) pOffsetAddr - ( DWORD_PTR ) pBaseAddr ) ) )
#endif  /* #if !defined ( ByteOffsetToTCHARsP6C ) */

//  ----------------------------------------------------------------------------
//  Define macros to extract the first and last character, respectively, of a
//  string.
//
//      PosLastCharOfString(plngStringLen) = Position of last character
//
//      FirstCharOfString(plpString) = First character - IMPORTANT: See Note 7
//
//      SecondCharOfString(plpString) = Second character - IMPORTANT: See Note 7
//
//      LastCharOfStringKnownLen(plpString,plngStringLen) = Last character of
//                                                          string
//      LastCharOfStringUnKnownLen(plpString) = Last character of string
//
//  Arguments, as applicable, for all macros, are as follows.
//
//      plpString       = Pointer to string to be evaluated. In your code, this
//                        may be cast to LPTSTR or LPCTSTR. The macro casts it
//                        to TCHAR, so that it works in the context of any
//                        character set.
//
//      plngStringLen   = Length, in TCHARs, of plpString. Use _tcslen (CRT) or
//                        lstrlen (Windows) to get the length.
//
//  There are two macros for returning the last character of a string.
//
//  1)  LastCharOfStringKnownLen is the macro to use when the string length is
//      known.
//
//  2)  LastCharOfStringUnKnownLen is the macro to use when the string length is
//      unknown. Internally, this macro calls CRT library function _tcslen,
//      which gives slightly better performance than lstrlen, especially for the
//      ANSI case, UNLESS you define __NOCRT_CALLS.
//
//  3)  If __NOCRT_CALLS is defined, macro LastCharOfStringUnKnownLen calls
//      lstrlen instead of _tcslen.
//
//  4)  StringIsEmptyWW evaluates to TRUE if its argument is the empty string.
//
//  5)  StringIsEffectivelyEmptyWW evaluates to TRUE if its argument is one of
//      the following:
//
//      a)  the empty string,
//      b)  a string containing only a newline character,
//      c)  a string containing only a carriage return character, or
//      d)  a string containing only a carriage return/linefeed sequence.
//
//  6)  StringIsNullOrEmptyWW evaluates to TRUE if its argument is either null,
//      or if it points to an empty string. This macro takes its name from a
//      static function of the String class in the Microsoft .NET Framework. Its
//      implementation was inspired by it, and the realization that it has only
//      to examine the pointer, and, unless it is NULL, return the result of a
//      test for the first character being a NULL character (0x00).
//
//      When you just need to know if the string is empty, StringIsNullOrEmptyWW
//      is orders of magnitude more efficient than _tcslen. Not only is it coded
//      inline, amounting to three machine instructions, it ovoids the O(1) cost
//      of scanning the string, a character at a time, to find its end.
//
//  7)  StringStartsWithCharWW evaluates the first character of a string. Ie
//      evaluates to TRUE if the first character of the string is pchr. You are
//      expected to pass in a TCHAR, which may be a literal.
//
//  8)  FirstCharOfString and SecondCharOfString cast plpString to TCHAR, and
//      treat it as an array of characters. Nothing is tested; if the string is
//      too short, the return value is garbage. Use at your own risk. (Hint:
//      If _tcslen returns a length of at least 2 for plpString, you are safe.)
//
//  See CmdArgs_P6C.H for related, but more specialized, macros, and
//  TcharMacros_WW.H for other general purpose macros similar to these.
//
//  Final Note: The guard code protects sets of macros, all of which are defined
//              if the tested macro is defined, and are undefined if it is
//              undefined.
//  ----------------------------------------------------------------------------

#ifndef PosLastCharOfString
    #define PosLastCharOfString(plngStringLen)                  ( ( unsigned int ) plngStringLen - PLUS_ONE_P6C )
    #define PosLastCharOfStringP6C                              PosLastCharOfString
    #define PosLastCharOfStringWW                               PosLastCharOfString
#endif  /* #ifndef PosLastCharOfString */

#ifndef LastCharOfString
    #define LastCharOfStringKnownLen(plpString, plngStringLen)  ( ( TCHAR ) ( ( TCHAR ) plpString [ PosLastCharOfStringWW ( plngStringLen) ] ) )
    #define LastCharOfStringKnownLenP6C                         LastCharOfStringKnownLen
    #define LastCharOfStringKnownLenWW                          LastCharOfStringKnownLen
#endif  /* #ifndef LastCharOfString */

#ifndef FirstCharOfString
    #define FirstCharOfString(plpString)                        ( ( TCHAR ) ( ( TCHAR ) plpString [ ARRAY_FIRST_ELEMENT_P6C ] ) )
    #define FirstCharOfStringP6C                                FirstCharOfString
    #define FirstCharOfStringWW                                 FirstCharOfString
#endif  /* #ifndef FirstCharOfString */

#ifndef SecondCharOfString
    #define SecondCharOfString(plpString)                       ( ( TCHAR ) ( ( TCHAR ) plpString [ 1 ] ) )
    #define SecondCharOfStringP6C                               SecondCharOfString
    #define SecondCharOfStringWW                                SecondCharOfString
#endif  /* #ifndef SecondCharOfString */

#ifndef ThirdCharOfString
    #define ThirdCharOfString(plpString)                       ( ( TCHAR ) ( ( TCHAR ) plpString [ 2 ] ) )
    #define ThirdCharOfStringP6C                               ThirdCharOfString
    #define ThirdCharOfStringWW                                ThirdCharOfString
#endif  /* #ifndef ThirdCharOfString */

#ifndef NthCharOfString
    #define NthCharOfString(plpString, pOrdinalPos)             ( ( TCHAR ) ( ( TCHAR ) plpString [ pOrdinalPos ] ) )
    #define NthCharOfStringP6C                                  NthCharOfString
    #define NthCharOfStringWW                                   NthCharOfString
#endif  /* #ifndef NthCharOfString */

#ifndef NULL_CHARACTER_P6C
    #define NULL_CHARACTER_P6C                                  ( ( TCHAR ) '\0' )
#endif  /* #ifndef NULL_CHARACTER_P6C */

#ifndef StringStartsWithCharWW
    #define StringStartsWithCharWW(plpString,pchr)              ( ( BOOL ) ( FirstCharOfStringWW ( plpString ) == pchr ) )
#endif  /* #ifndef StringStartsWithCharWW */

#ifndef StringIsEmptyWW
    #define StringIsEmptyWW(plpString)                          ( ( BOOL ) ( FirstCharOfStringWW ( plpString ) == NULL_CHARACTER_P6C ) )
    #define StringIsEffectivelyEmptyWW(plpString) \
                                        ( ( BOOL ) ( ( FirstCharOfStringWW ( plpString ) == NULL_CHARACTER_P6C ) \
                                        || ( ( FirstCharOfStringWW ( plpString ) == NEWLINE_CHAR_WW )            \
                                            && ( SecondCharOfString  ( plpString ) == NULL_CHARACTER_P6C  ) )    \
                                        || ( ( FirstCharOfStringWW ( plpString ) == CARRIAGE_RETURN_P6C )        \
                                            && ( SecondCharOfString  ( plpString ) == NULL_CHARACTER_P6C  ) )    \
                                        || ( ( FirstCharOfStringWW ( plpString ) == CARRIAGE_RETURN_P6C )        \
                                            && ( SecondCharOfString  ( plpString ) == NEWLINE_CHAR_WW )          \
                                            && ( ThirdCharOfString   ( plpString ) == NULL_CHARACTER_P6C  ) ) ) )

    #define StringIsNullOrEmptyWW(plpString)                    ( ( BOOL ) ( plpString == NULL || StringIsEmptyWW ( plpString ) ) )
#endif  /* #ifndef StringIsEmptyWW */

#ifndef LastCharOfStringUnKnownLen
    #ifdef  __NOCRT_CALLS
        #define LastCharOfStringUnKnownLen(plpString)           ( ( TCHAR ) ( ( TCHAR ) plpString [ PosLastCharOfStringWW ( lstrlen ( plpString ) ) ] ) )
    #else
        #define LastCharOfStringUnKnownLen(plpString)           ( ( TCHAR ) ( ( TCHAR ) plpString [ PosLastCharOfStringWW ( _tcslen ( plpString ) ) ] ) )
    #endif  /*  #ifdef  __NOCRT_CALLS */

    #define LastCharOfStringUnKnownLenP6C                       LastCharOfStringUnKnownLen
    #define LastCharOfStringUnKnownLenWW                        LastCharOfStringUnKnownLen
#endif  /* #ifndef LastCharOfStringUnKnownLen */

#ifndef TOKEN_INDEX_MINIMUM_P6C
    #define TOKEN_INDEX_MINIMUM_P6C                             PLUS_ONE_P6C
#endif  /* #ifndef TOKEN_INDEX_MINIMUM_P6C */

#endif  /* _CHARPOSMACROS_WW_DEFINED */