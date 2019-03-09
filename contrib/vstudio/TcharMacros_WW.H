#if !defined ( TCHARMACROS_WW_INCLUDED )
#define TCHARMACROS_WW_INCLUDED

/*
    ============================================================================

    Name:               TcharMacros_WW.H

    Synopsis:           Library include to segregate the TCHAR buffer calculator
                        macros, so that they can be used independently in MFC
                        code.

    Remarks:            As of Saturday, 25 May 2013, this header is included by
                        CommonConstants_P6C.H, the birthplace of these macros.

    Author:             David A. Gray

    Copyright:          2012-2016, David A. Gray.
                        All rights reserved world wide.

    Created:            Monday, 01 October 2012

    License:            Copyright (C) 2012-2017, David A. Gray. All rights reserved.

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

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- ----------------------------------------------------------
    2012/10/01 DAG Initial trial implementation, tested in WWWILMuscle.dll
                   function ASCIIZStringFromBSTR.

    2013/05/17 DAG Post guards around the macro definitions, making this header
                   compatible with their initial home, CommonConstants_P6C.H,
                   and add a #pragma once directive.

    2013/05/26 DAG Substitute sizeof ( TCHAR ) for TCHAR_SIZE_P6C, and eliminate
                   this macro, which I long since found is unnecessary, since
                   sizeof ( TCHAR ) behaves more like a preprocessor macro than
                   a C operator, which is how it is defined in the ANSI standard
                   and the Microsoft compiler documentation.

    2014/08/17 DAG Include CharPosMacros_WW.H, which defines macros that were
                   originally defined in P6CStringLib1.H. Importing them here,
                   too, enables me to omit P6CStringLib1.H unless a program
                   calls functions exported by P6CStringLib1.dll.

                   Multiple levels of preprocessor guard code prevent macros
                   being redefined and the associated harmless but necessary
                   warnings emitted by the preprocessor, via the compiler.

    2015/01/14 DAG 1) Eliminate the casts to DWORD from the TCHAR macros.

                   2) Merge the macros that I defined and tested as part of
                      HMAC_SHAx_Pvt.H.

    2015/01/16 DAG Verify that stdio.h is included by checking for existence of
                   CPP symbol _INC_STDIO. If so, auto-include TCHAR.H and
                   CharPosMacros_WW.H, and emit a message to that effect into
                   the output stream.

    2015/02/10 DAG Define macros, BytesToTCHARsP6C and ByteOffsetToTCHARsP6C.

    2015/02/18 DAG Define 3 new macros to support reallocating anything that was
                   allocated by one of the original Alloc*_WW macros, and a full
                   set of allocators that call the SEH protected heap allocators
                   exported by WWKernelLibWrapper.dll, and add a no dependencies
                   directive, exactly like those inserted by the Visual Studio
                   IDE into resource.h.

    2015/06/29 DAG Move macro TcsLenEvenIfNull from FixedStringBuffers_Pvt.H, a
                   private header, in which they were developed and tested, and
                   map it to TcsLenEvenIfNullWW.

                   I decided against putting these macros in alphabetical order,
                   because there are too many dependencies that would probably
                   break one or more of them if the definitions were in alpha
                   order.

    2016/01/15 DAG Define STPRINTF_S_ERROR, for testing the status code returned
                   by the sprintf_s family of functions, and MINUS_ONE_WW, from
                   which it derives.

    2016/01/20 DAG Define SPrintFsBufSize, to document lessons learned and
                   confirmed by testing in SecurePrintFHazard.exe, and document
                   that it is intended for use as the  SizeInWords argument of
                   the sprintf_s family of CRT functions.

    2016/05/07 DAG 1) Substitute SEHHeapAllocators.H for WWKernelLibWrapper.H to
                      break a dependency caused by CType.H being included by the
                      version of WinNT.H that comes with the new Platform SDK.

                   2) Macros ShrinkBufToFitStringP6C and ShrinkBufToFitASCIIZP6C
                      wrap the ReAllocBytes_WW macro, to take advantage of the
                      SEH allocation wrappers defined in WWKernelLibWrapper.dll,
                      and to degrade to call the Windows API heap routines or
                      the CRT memory allocation routines, depending on the value
                      of a preprocessor symbol.

    2016/05/21 DAG Correct a longstanding typographical error in the text of a
                   message that goes into the standard output generated by the
                   C preprocessor.

    2016/07/09 DAG Identify the file from which the messages are being emitted,
                   and add one that appears when UNICODE is defined, to state
                   explicitly that _UNICODE is, too, so that if the Windows API
                   treats characters as Unicode (wide), so does the CRT library.

    2016/07/22 DAG Insert a space between the FILE directive and the text in the
                   messages, so that the text and the file name are separated.

    2016/08/14 DAG Insert a space between the FILE directive and the text in the
                   messages, and numerous typographical errors that I missed.

    2016/11/18 DAG Define INPLACE_POINTER.

    2016/12/29 DAG Add OmitTrailingNull as the inverse of TCharsPlusSZP6C, and
                   RCDATA_LOOK_IN_STARTUP_PE_FILE, for use along with
                   RCDATA_INPLACE_POINTER and RCDATA_HIDE_LENGTH, both for use
                   with LoadString.

    2017/04/16 DAG The single argument to macro OmitTrailingNull was misspelled.
                   Today must be the first time that I have actually referenced
                   this macro. Please see the Remarks section below.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

//  ----------------------------------------------------------------------------
//  If included by CommonConstants_P6C.H, windows.h is implicitly sanctioned,
//  and included, and P6CStringLib1.H is fair game.
//  ----------------------------------------------------------------------------

#if defined ( COMMON_CONSTANTS_P6C_INCLUDED )
    #pragma message ( __FILE__ " CommonConstants_P6C.H is included in this translation unit; auto-including P6CStringLib1.H." )
    #include <P6CStringLib1.H>
#else
    #if defined ( _INC_WINDOWS )
        #pragma message  ( __FILE__ " Prerequisite header Windows.h is already included." )
    #else
        #pragma message  ( __FILE__ " Auto-including prerequisite header Windows.h, since this file was included independently." )
        #include <Windows.h>
    #endif  /* #if defined ( _INC_WINDOWS ) */
#endif  /* #if defined ( COMMON_CONSTANTS_P6C_INCLUDED ) */

#if !defined ( ZERO_WW )
    #define ZERO_WW                         0x00000000
#endif  /* #if !defined ( ZERO_WW ) */

#if !defined ( MINUS_ONE_WW )
    #define MINUS_ONE_WW                ( -1 )
#endif  /* #if !defined ( MINUS_ONE_WW ) */

#if !defined ( TCHAR_SIZE_P6C )
    #define TCHAR_SIZE_P6C              sizeof ( TCHAR )
#endif /* #if !defined ( TCHAR_SIZE_P6C ) */

#if !defined ( TRAILING_NULL_ALLOWANCE_P6C )
    #define TRAILING_NULL_ALLOWANCE_P6C PLUS_ONE_WW
#endif  /* #if !defined ( TRAILING_NULL_ALLOWANCE_P6C ) */

#if !defined ( TRAILING_NULL_ALLOWANCE_WW )
    #define TRAILING_NULL_ALLOWANCE_WW  TRAILING_NULL_ALLOWANCE_P6C
#endif  /* #if !defined ( TRAILING_NULL_ALLOWANCE_WW ) */

#if !defined ( LOOK_IN_THIS_EXE )
    #define LOOK_IN_THIS_EXE            ZERO_WW
#endif /* #if !defined ( LOOK_IN_THIS_EXE ) */

//  ----------------------------------------------------------------------------
//  Use this constant as the last argument to LoadStringW, the wide character
//  implementation of LoadString, to return a pointer to a null terminated
//  string resource, thereby avoiding the wasted effort and memory overhead of a
//  memory copy operation.
//
//  LOOK_IN_THIS_EXE, defined above, and RCDATA_LOOK_IN_STARTUP_PE_FILE, defined
//  below, are equivalent; the former remains for backward compatibility.
//  ----------------------------------------------------------------------------

#if !defined ( RCDATA_INPLACE_POINTER )
    #define RCDATA_INPLACE_POINTER              ZERO_WW
#endif  /* #if !defined ( RCDATA_INPLACE_POINTER ) */

#if !defined ( RCDATA_LOOK_IN_STARTUP_PE_FILE )
    #define RCDATA_LOOK_IN_STARTUP_PE_FILE      LOOK_IN_THIS_EXE
#endif  /* #if !defined ( RCDATA_LOOK_IN_STARTUP_PE_FILE ) */

#if !defined ( RCDATA_HIDE_LENGTH )
    #define RCDATA_HIDE_LENGTH                  ZERO_WW
#endif /* #if !defined ( RCDATA_HIDE_LENGTH ) */
//  ----------------------------------------------------------------------------
//  Croak unless stdio.h is included, to ensure that use of the CRT library is
//  sanctioned.
//
//  Another header pulling TCHAR.H into the translation unit is no foul. Its
//  guard macros prevent multiple inclusions.
//
//  If UNICODE is defined for the Win32 libraries, define its twin, _UNICODE,
//  for the CRT libraries if it isn't already defined.
//  ----------------------------------------------------------------------------

#if defined ( _INC_STDIO )
    #pragma message ( __FILE__ " CRT header stdio.h is included, which is taken as sanctioning the CRT library." )
    #pragma message ( __FILE__ "     TCHAR.H auto-included, to establish the generic TCHAR mappings that make writing code that supports ANSI, MBCS, and Unicode so much easier" )
    #pragma message ( __FILE__ "     CharPosMacros_WW.H auto-included, to define special purpose macros used herein, and available for general use" )

    //  ------------------------------------------------------------------------
    //  The secure implementations of the sprintf_s family of functions reserve
    //  an integer value of -1 (0xffffffff) to report an outright error. Since
    //  it is theoretically possible to succeed without writing anything, zero
    //  is a legal return value.
    //  ------------------------------------------------------------------------

    #define STPRINTF_S_ERROR            MINUS_ONE_WW

    #ifdef UNICODE
        #ifndef _UNICODE
            #define _UNICODE
            #pragma message ( __FILE__ " UNICODE is defined for the Windows Platform SDK. The corresponding CRT symbol, _UNICODE, was just defined." )
        #endif  /* #ifndef _UNICODE */
    #endif  /* #ifdef UNICODE */

    #include <TCHAR.H>                          // Define generic text mappings for the routines declared in stdio.h.
    #include "..\vstudio\CharPosMacros_WW.H"	// Define macros to get the first and last character from a string.
#else
    #error ( "This header file requires routines declared in stdio.h. For the benefit of anyone who prefers to avoid the CRT library, you are required to include it ahead of this statement to signify your consent to use of the CRT library." )
#endif  /* #if defined ( _INC_STDIO ) */

//  ----------------------------------------------------------------------------
//  These macros simplify the extremely repetitive task of computing the correct
//  size for a string buffer. Their goal is to reduce the risk of off-by-one and
//  ANSI versus Unicode size errors, and their associated risk of creating
//  opportunities for buffer overflow attacks and memory access violations, in
//  this critical calculation.
//
//  Remarks:    The return values of all but the last macro are cast to a DWORD,
//              as is the input value. Unless you have disabled warnings for
//              missing or invalid casts, the compiler should issue a warning if
//              the real input or output cannot be cast to DWORD. (You left
//              warnings about missing or invalid type casts enabled, right?
//              Good!<G> If you disabled them, get into a refresher course on
//              best practices for C programming as soon as possible, and pay
//              close attention. There will be a test.<G>)
//  ----------------------------------------------------------------------------


/*
    ----------------------------------------------------------------------------

    Name:       TCharsPlusSZP6C and SPrintFsBufSize

    Synopsis:   Adjust a size, in TCHARS, such as the length returned by _tcslen
                or lstrlen, to account for the trailing null.

                SPrintFsBufSize is the same macro, explicitly named to associate
                it with the sprintf_s family of CRT functions.

    In:         pdwTChars           = Number of TCHARs to be accommodated in the
                                      buffer you are about to allocate

    Out:        pdwTChars + 1 (allowance for trailing null)

                Output is typecast as a DWORD.

    Remarks:    These macros are primarily intended for internal use, such as in
                macro TcharsMinBufSizeP6C, which performs further computations
                to account for the size of a TCHAR in the active character
                encoding.

                OmitTrailingNull saw its first actual use on 16 April 2017, when
                I employed it in STDH_DLL_LoadString and SHD_pvt_LoadString to
                adjust away the trailing null, so that the returned length is
                consistent with the lengths returned by virtually every other
                function that reports the length of a string, in particular
                _tcslen and the default invocation of LoadString, which copies
                the string resource into a supplied output buffer.
    ----------------------------------------------------------------------------
*/

#if !defined ( TCharsPlusSZP6C )
    #define TCharsPlusSZP6C(pdwTChars)  ( ( ( DWORD ) pdwTChars + TRAILING_NULL_ALLOWANCE_P6C ) )
    #define SPrintFsBufSize(pdwTChars)  ( ( ( DWORD ) pdwTChars + TRAILING_NULL_ALLOWANCE_P6C ) )
    #define OmitTrailingNull(pdwTChars) ( ( ( DWORD ) pdwTChars - TRAILING_NULL_ALLOWANCE_P6C ) )
#endif  /* #ifndef TCharsPlusSZP6C */



/*
    ----------------------------------------------------------------------------

    Name:       TcharsMinBufSizeP6C

    Synopsis:   Given a number of TCHARs to be accommodated, compute the minimum
                number of bytes needed to accommodate the string and its trailing
                NULL character.

    In:         pdwTChars           = Number of TCHARs to be accommodated in the
                                      buffer you are about to allocate

    Out:        Minimum size, in bytes, of a buffer to hold a string of
                pdwTChars TCHARs and its trailing NULL character.

                Output is typecast as a DWORD.

    Remarks:    This macro is sensitive to the UNICODE preprocessor symbol, and
                adjusts its output accordingly.
    ----------------------------------------------------------------------------
*/

#ifndef TcharsMinBufSizeP6C
    #define TcharsMinBufSizeP6C(pdwTChars) \
                                        ( ( ( DWORD ) TCharsPlusSZP6C ( pdwTChars ) * sizeof ( TCHAR ) ) )
#endif  /* #ifndef TcharsMinBufSizeP6C */


/*
    ----------------------------------------------------------------------------

    Name:       TcharsToBytesP6C

    Synopsis:   Given a size, in TCHARS, such as the length returned by _tcslen
                or lstrlen, return the number of bytes occupied by that many
                TCHARs, excluding the obligatory trailing NULL.

    In:         pdwTChars           = Number of TCHARs

    Out:        Number of bytes required to hold pdwTChars TCHARs.

                Output is typecast as a DWORD.

    Remarks:    This macro makes no allowance for a trailing null character. For
                that, use TcharsMinBufSizeP6C. Use it when you only to convert a
                size in TCHARs to a size in BYTES.

                The inverse of this macro is TCharsMaxForBufSizeP6C.
    ----------------------------------------------------------------------------
*/

#ifndef TcharsToBytesP6C
    #define TcharsToBytesP6C(pdwTChars) ( ( ( DWORD ) pdwTChars * sizeof ( TCHAR ) ) )
#endif  /* TcharsToBytesP6C */


/*
    ----------------------------------------------------------------------------

    Name:       TCharsMaxForBufSizeP6C

    Synopsis:   Given the size of a buffer, expressed in bytes, return the size,
                in TCHARS, of the longest string that will fit in it.

    In:         pdwBufSize          = Buffer size, in BYTES

    Out:        Maximum number of TCHARs that the buffer can hold, including
                room for the trailing NULL.

                Output is typecast as a DWORD.

    Remarks:    This macro takes into account the space needed for the trailing
                null character, and is sensitive to the UNICODE preprocessor
                symbol, adjusting its output accordingly.

                The inverse of this macro is TcharsToBytesP6C.

                BytesToTCHARsP6C performs the same calculation, EXCLUDING the
                terminal NULL character.
    ----------------------------------------------------------------------------
*/

#ifndef TCharsMaxForBufSizeP6C
    #define TCharsMaxForBufSizeP6C(pdwBufSize) \
                                        ( ( ( DWORD ) ( ( pdwBufSize ) / ( sizeof ( TCHAR ) ) - TRAILING_NULL_ALLOWANCE_P6C ) ) )
#endif  /* #ifndef TCharsMaxForBufSizeP6C */


/*
    ----------------------------------------------------------------------------

    Name:       TCharBufSizeP6C

    Synopsis:   Compute the minimum number of bytes needed to hold a copy of a
                string, including room for its trailing NULL character.

    In:         plpString           = Pointer to a null terminated string,
                                      explicitly cast to a LPCTSTR, to match the
                                      generic TCHAR-mapped prototype of _tcslen,
                                      so that your compiler will leave you alone.

    Out:        Minimum number of bytes needed to hold the string.

                Output is typecast as a DWORD.

    Remarks:    This macro takes into account the spece needed for the trailing
                null character, and is sensitive to the UNICODE preprocessor
                symbol, adjusting its output accordingly. Internally, the macro
                calls CRT library function _tcslen to compute the length of the
                string.
    ----------------------------------------------------------------------------
*/

#ifndef TCharBufSizeP6C
    #define TCharBufSizeP6C(plpString)  ( ( ( DWORD ) TcharsMinBufSizeP6C ( _tcslen ( ( LPCTSTR ) plpString ) ) ) )
#endif  /* #ifndef TCharBufSizeP6C */


/*
    ----------------------------------------------------------------------------

    Name:       LPSzMinBufSizeP6C

    Synopsis:   Compute the minimum number of bytes needed to hold a copy of a
                string, including room for its trailing NULL character.

    In:         plpString               = Pointer to a null terminated string,
                                          explicitly cast to a LPCTSTR, to match
                                          the generic TCHAR-mapped prototype of
                                          _tcslen, so that your compiler will
                                          leave you alone.

    Out:        Minimum number of bytes needed to hold the string.

                Output is typecast as a DWORD.

    Remarks:    This macro and TCharBufSizeP6C return the same result. This one
                came into being because none of these macros was documented, and
                I overlooked see the other one when I needed it.
    ----------------------------------------------------------------------------
*/

#ifndef LPSzMinBufSizeP6C
    #define LPSzMinBufSizeP6C(plpString) \
                                        ( ( ( DWORD ) TCharsPlusSZP6C ( _tcslen ( ( LPCTSTR ) plpString ) ) * sizeof ( TCHAR ) ) )
#endif  /* #ifndef LPSzMinBufSizeP6C */


/*
    ----------------------------------------------------------------------------

    Name:       LPSzToBytesP6C

    Synopsis:   Compute the minimum number of bytes needed to hold a copy of a
                string, EXCLUDING its trailing NULL character.

    In:         plpString           = Pointer to a null terminated string,
                                      explicitly cast to a LPCTSTR, to match the
                                      generic TCHAR-mapped prototype of _tcslen,
                                      so that your compiler will leave you
                                      alone.

    Out:        Length of any string, expressed in BYTES.

                Output is typecast as a DWORD.

    Remarks:    Unlike LPSzMinBufSizeP6C, this macro returns the length of a
                string, in BYTES, whether the string is ANSI, MBCS, or Unicode.
    ----------------------------------------------------------------------------
*/

#ifndef LPSzToBytesP6C
    #define LPSzToBytesP6C(plpString)   ( ( ( DWORD ) _tcslen ( ( LPCTSTR ) plpString ) * sizeof ( TCHAR ) ) )
#endif  /* #ifndef LPSzToBytesP6C */


/*
    ----------------------------------------------------------------------------------------------
    The following four macros provide a variety of mechanisms for shrinking big buffers to
    precisely fit a string that starts at its base address. Use the table below to determine
    the best macro for the task at hand.

    ----------------------------------------------------------------------------------------------
    String Length                              Heap Handle         Macro to Use
    ---------------------------------------    ----------------    ------------------------------
    IS Known                                   Default, unknown    ShrinkBufToFitStringP6C
    Is Unknown, but would be useful to have    Default, unknown    ShrinkBufToFitStringP6C
    Is Unknown, and of no further use          Default, unknown    ShrinkBufToFitASCIIZP6C

    Is Known                                   Is Known            ShrinkBufToFitStringAnyHeapP6C
    Is Unknown, but would be useful to have    Is Known            ShrinkBufToFitStringAnyHeapP6C
    Is Unknown, and of no further use          Is Known            ShrinkBufToFitASCIIZAnyHeapP6C

    All four macros refer to symbolic constant HEAP_ALL_FLAGS_OFF, which may not be defined.
    hence, it is defined immediately below, if necessary, as are two aliases.
    ----------------------------------------------------------------------------------------------
*/

#ifndef HEAP_ALL_FLAGS_OFF
    #define HEAP_ALL_FLAGS_OFF          0x00000000L

    #ifndef HEAP_ALL_FLAGS_OFF_WW
        #define HEAP_ALL_FLAGS_OFF_WW   HEAP_ALL_FLAGS_OFF
    #endif  /* #ifndef HEAP_ALL_FLAGS_OFF_WW */

    #ifndef HEAP_ALL_FLAGS_OFF_P6C
        #define HEAP_ALL_FLAGS_OFF_P6C  HEAP_ALL_FLAGS_OFF
    #endif  /* #ifndef HEAP_ALL_FLAGS_OFF_P6C */
#endif  /* #ifndef HEAP_ALL_FLAGS_OFF */


/*
    ----------------------------------------------------------------------------

    Name:       ShrinkBufToFitStringP6C

    Synopsis:   Shrink a buffer to minimum size required to hold an ASCIIZ
                string of known length.

    In:         plpvBigBuffer       = Pointer to a buffer that was allocated
                                      from the default process heap, which is
                                      filled by a string of a known length that
                                      starts at the beginning of the buffer.

                pdwCharCount        = A DWORD containing the length of the
                                      string, in TCHARs, which happens to be
                                      the units in which the standard string
                                      length counting functions return it.

    Out:        The return value is a pointer to the shrunk buffer, which
                should be the same as plpvBigBuffer, since a buffer can be
                shrunk without moving it.

    Remarks:    If the length of the string is unknown, but you have no further
                use for it (e. g., the macro is in the last statement of your
                function, or is used as an argument to a function), use
                ShrinkBufToFitStringP6C, which computes and discards the length.

                On the other hand, if the routine has more work to do, and could
                reuse the string length, it is more efficient to call _tcslen,
                store the length in a local variable, and use it with this macro.

                If you already have a handle to your default process heap, macro
                ShrinkBufToFitASCIIZAnyHeapP6C is slightly faster, because it
                skips the call to GetProcessHeap.

                Unlike ShrinkBufToFitASCIIZP6C, this macro assumes that the
                length of the input string is known.

    ----------------------------------------------------------------------------
*/

#define ShrinkBufToFitStringP6C(plpvBigBuffer, pdwCharCount) \
                                        ( ReAllocBytes_WW ( ( LPVOID ) plpvBigBuffer ,          \
                                                            TcharsMinBufSizeP6C ( pdwCharCount ) ) )

/*
    ----------------------------------------------------------------------------

    Name:       ShrinkBufToFitASCIIZP6C

    Synopsis:   Shrink a buffer to the minimum size required to hold an ASCIIZ
                string of unknown length.

    In:         plpvBigBuffer       = Pointer to a buffer that was allocated
                                      from the default process heap, which is
                                      filled by a string of a known length that
                                      starts at the beginning of the buffer.

    Out:        The return value is a pointer to the shrunk buffer, which should
                be the same as plpvBigBuffer, since shrinking doesn't require it
                to be moved.

    Remarks:    If the length of the string is known, ShrinkBufToFitStringP6C is
                much more efficient.

                If you already have a handle to your default process heap, macro
                ShrinkBufToFitStringAnyHeapP6C is slightly faster, since it can
                skip the call to GetProcessHeap.

                Unlike ShrinkBufToFitStringP6C, this macro assumes that the
                length of the input string is unknown, but the string is null
                terminated; hence, it's length can be determined.
    ----------------------------------------------------------------------------
*/

#define ShrinkBufToFitASCIIZP6C(plpvBigBuffer)  \
                                        ( ReAllocBytes_WW ( ( LPVOID ) plpvBigBuffer , \
                                          TCharBufSizeP6C ( plpvBigBuffer ) ) )



/*
    ----------------------------------------------------------------------------

    Name:       ShrinkBufToFitStringAnyHeapP6C

    Synopsis:   Shrink a buffer to minimum size required to hold an ASCIIZ
                string of known length.

    In:         plpvBigBuffer       = Pointer to a buffer that was allocated
                                      from the default process heap, which is
                                      filled by a string of a known length that
                                      starts at the beginning of the buffer.

                pdwCharCount        = A DWORD containing the length of the
                                      string, in TCHARs, which happens to be the
                                      units in which the standard string length
                                      counting functions (_tcslen and lstrlen)
                                      return it.

                phHeap              = A HANDLE that holds the handle to the heap
                                      to which the memory to which plpvBigBuffer
                                      points belongs.

    Out:        The return value is a pointer to the shrunk buffer, which should
                be the same as plpvBigBuffer, since a buffer can be shrunk
                without moving it.

    Remarks:    This macro is similar to ShrinkBufToFitStringP6C, except that it
                can shrink a buffer allocated from ANY heap.

                Since I usually save the handle to my default process heap, this
                macro offers a small performance improvement, because it skips
                the otherwise required call to GetProcessHeap.
    ----------------------------------------------------------------------------
*/

#define ShrinkBufToFitStringAnyHeapP6C(plpvBigBuffer, pdwCharCount, phHeap) \
                                        ( HeapReAlloc ( phHeap ,                                 \
                                                        HEAP_ALL_FLAGS_OFF ,                     \
                                                        ( LPVOID ) plpvBigBuffer ,               \
                                                        TcharsMinBufSizeP6C ( pdwCharCount ) ) )


/*
    ----------------------------------------------------------------------------

    Name:       ShrinkBufToFitASCIIZAnyHeapP6C

    Synopsis:   Shrink a buffer to the minimum size required to hold an ASCIIZ
                string of unknown length.

    In:         plpvBigBuffer       = Pointer to a buffer that was allocated
                                      from the default process heap, which is
                                      filled by a string of a known length that
                                      starts at the beginning of the buffer.

                phHeap              = A HANDLE that holds the handle to the heap
                                      from which the memory to which plpvBigBuffer
                                      points was allocated.

    Out:        The return value is a pointer to the shrunk buffer, which should
                be the same as plpvBigBuffer, since a buffer can be shrunk
                without moving it.

    Remarks:    This macro is similar to ShrinkBufToFitASCIIZP6C, except that it
                can shrink a buffer allocated from ANY heap.

                Since I usually save the handle to my default process heap, this
                macro offers a small performance improvement, because it skips
                the otherwise required call to GetProcessHeap.
    ----------------------------------------------------------------------------
*/

#define ShrinkBufToFitASCIIZAnyHeapP6C(plpvBigBuffer, phHeap) \
                                        ( HeapReAlloc ( phHeap ,                              \
                                                        HEAP_ALL_FLAGS_OFF ,                  \
                                                        ( LPVOID ) plpvBigBuffer ,            \
                                                        TCharBufSizeP6C ( plpvBigBuffer ) ) )

//  =========================================================================================================
//  The following macros were developed and tested in HMAC_SHAx.dll.
//  See C:\Documents and Settings\DAG\My Documents\Programming\Visual Studio 6\DLL\HMAC_SHAx\HMAC_SHAx_Pvt.H.
//  The code in this header is somewhat simpler because HEAP_ALL_FLAGS_OFF is already defined.
//  =========================================================================================================

//  ----------------------------------------------------------------------------
//  These macros support two compile time configurations.
//
//  1)  The default configuration uses HeapAlloc as its memory allocator, with
//      HeapFree for memory deallocation.
//
//  2)  The alternative configuration, which is emitted when _HMAC_SHAX_MALLOC
//      or _MALLOC_AS_MEMORY_ALLOCATOR, uses malloc as its memory allocator,
//      with free for memory deallocation.
//
//      When linked against the version of the Standard C Runtime Library that
//      ships with Microsoft Visual C++, the alternative configuration uses
//      HeapAlloc and HeapFree indirectly, which is my reason for favoring the
//      default configuration.
//
//  Anything allocated by AllocBytes_WW, AllocCString_WW, or AllocTchars_WW must
//  be discarded by calling FreeBuffer_WW before the calling routine returns.
//
//  HEAP_ZERO_MEMORY is defined if HeapAlloc is declared, which will be true if
//  the current translation unit includes windows.h. If windows.h is excluded,
//  do one of the following.
//
//  1)  Define _MALLOC_AS_MEMORY_ALLOCATOR, include either stdlib.h or malloc.h,
//      and link against LIBC.LIB, LIBCMT.LIB, or MSVCRT.LIB to enable the CRT
//      memory allocators.
//
//  2)  Define _TCHAR_MACROS_SEH_ALLOCATORS_ and link WWKernelLibWrapper.lib to
//      enable the Win32 memory allocators with Structured Exception Handling
//      and detailed error reports via SetLastError.
//
//  TcharsMinBufSizeP6C and TcharsToBytesP6C are macros; both of which are
//  defined herein.
//
//  The nested block of preprocessor code that follows is the result of an
//  expensive lesson learned while developing and testing CPP macros. Without
//  tests of this sort, you get almost no help from the compiler, and you may
//  chase down many false leads before you find the sources of your syntax
//  errors, which may be many and varied.
//
//  Along the same lines, this block uses tests for the CPP guard symbols
//  defined by the standard library headers to cause the compiler to abort with
//  an explicit error message when their absence indicates the absence of a
//  required header.
//  ----------------------------------------------------------------------------

#if defined ( _HMAC_SHAX_MALLOC ) || defined ( _MALLOC_AS_MEMORY_ALLOCATOR )
    #if defined ( _INC_STDLIB ) || defined ( _INC_MALLOC )
        #pragma message ( __FILE__ " Using CRT memory allocators. " )

        #define AllocBytes_WW(pCount)       (             malloc    (                       pCount )   )
        #define AllocCString_WW(pCount)     ( ( LPTSTR )  malloc    ( TcharsMinBufSizeP6C ( pCount ) ) )
        #define AllocTchars_WW(pCount)      ( ( TCHAR * ) malloc    ( TcharsToBytesP6C    ( pCount ) ) )

        #define ReAllocBytes_WW(pBuffer, pCount)    \
                                            (             realloc   ( pBuffer ,                       pCount )   )
        #define ReAllocCString_WW(pBuffer, pCount)  \
                                            ( ( LPTSTR )  realloc   ( pBuffer , TcharsMinBufSizeP6C ( pCount ) ) )
        #define ReAllocTchars_WW(pBuffer, pCount)   \
                                            ( ( TCHAR * ) realloc   ( pBuffer , TcharsToBytesP6C    ( pCount ) ) )

        #define FreeBuffer_WW(pBuffer)          (             free      (                       pBuffer )  )
    #else
        #error ( "To use the CRT memory allocators, you must include either stdlib.h or malloc.h." )
    #endif  /* #if defined ( _INC_STDLIB ) || defined ( _INC_MALLOC ) */
#else   /* #if defined ( _HMAC_SHAX_MALLOC ) || defined ( _MALLOC_AS_MEMORY_ALLOCATOR ) */
    #if defined ( _TCHAR_MACROS_SEH_ALLOCATORS_ )
        #if defined ( _WWKERNELLIBWRAPPER_DEFINED )
            #pragma message ( __FILE__ " WWKernelLibWrapper.H is already in the translation stream." )
        #else
            #pragma message ( __FILE__ " Auto-including SEHHeapAllocators.H, since WWKernelLibWrapper.H is absent from the translation stream." )
            #include <SEHHeapAllocators.H>
        #endif  /* #if defined ( _WWKERNELLIBWRAPPER_DEFINED ) */

        #pragma message ( __FILE__ " Using Win32 memory allocators with Structured Exception Handling and calls to SetLastError. " )

        #define AllocBytes_WW(pCount)       (             AllocDfltHeapBufSEH_P6C (                       pCount )   )
        #define AllocCString_WW(pCount)     ( ( LPTSTR  ) AllocDfltHeapBufSEH_P6C ( TcharsMinBufSizeP6C ( pCount ) ) )
        #define AllocTchars_WW(pCount)      ( ( TCHAR * ) AllocDfltHeapBufSEH_P6C ( TcharsToBytesP6C    ( pCount ) ) )

        #define ReAllocBytes_WW(pBuffer, pCount)    \
                                            (             ReAllocDfltHeapBufSEH_P6C ( pBuffer ,                       pCount )   )
        #define ReAllocCString_WW(pBuffer, pCount)  \
                                            ( ( LPTSTR  ) ReAllocDfltHeapBufSEH_P6C ( pBuffer , TcharsMinBufSizeP6C ( pCount ) ) )
        #define ReAllocTchars_WW(pBuffer, pCount)   \
                                            ( ( TCHAR * ) ReAllocDfltHeapBufSEH_P6C ( pBuffer , TcharsToBytesP6C    ( pCount ) ) )

        #define FreeBuffer_WW(pBuffer)      (             FreeDfltHeapBuf_P6C     (                       pBuffer )  )
    #else   /* #if defined ( _TCHAR_MACROS_SEH_ALLOCATORS_ ) */
        #if defined ( HEAP_ZERO_MEMORY )
            #pragma message ( __FILE__ " Using Win32 memory allocators withOUT Structured Exception Handling OR calls to SetLastError. " )

            #define AllocBytes_WW(pCount)   (             HeapAlloc   ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        pCount ) )
            #define AllocCString_WW(pCount) ( ( LPTSTR )  HeapAlloc   ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        TcharsMinBufSizeP6C ( pCount ) ) )
            #define AllocTchars_WW(pCount)  ( ( TCHAR * ) HeapAlloc   ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        TcharsToBytesP6C    ( pCount ) ) )

            #define ReAllocBytes_WW(pBuffer, pCount)    \
                                            (             HeapReAlloc ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        pBuffer ,                           \
                                                                        pCount ) )
            #define ReAllocCString_WW(pBuffer, pCount)  \
                                            ( ( LPTSTR )  HeapReAlloc ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        pBuffer ,                           \
                                                                        TcharsMinBufSizeP6C ( pCount ) ) )
            #define ReAllocTchars_WW(pBuffer, pCount)   \
                                            ( ( TCHAR * ) HeapReAlloc ( m_hProcHeap ,                       \
                                                                        HEAP_ZERO_MEMORY ,                  \
                                                                        pBuffer ,                           \
                                                                        TcharsToBytesP6C    ( pCount ) ) )

            #define FreeBuffer_WW(pBuffer)  (             HeapFree    ( m_hProcHeap ,                       \
                                                                        HEAP_ALL_FLAGS_OFF ,                \
                                                                        pBuffer ) )
        #else
            #error ( "Preprocessor macro HEAP_ZERO_MEMORY must be defined, in order for nacros AllocBytes_WW, AllocCString_WW, and AllocTchars_WW to expand correctly; include Windows.h." )
        #endif  /* #if defined ( HEAP_ZERO_MEMORY ) */
    #endif  /* #if defined ( _TCHAR_MACROS_SEH_ALLOCATORS_ ) */
#endif  /* #if defined ( _HMAC_SHAX_MALLOC ) || defined ( _MALLOC_AS_MEMORY_ALLOCATOR ) */

//  ----------------------------------------------------------------------------
//  GetStringFromThisDLL honors the UNICODE flag, while GetWideStringFromThisDLL
//  trumps it. Since it has just one argument, which specifies the resource ID,
//  GetConsoleResource_WW doesn't warrant a macro.
//
//  Both expect m_hinstDLL to be defined and initialized, and HEAP_ALL_FLAGS_OFF
//  to map to numeric zero. This header covers HEAP_ALL_FLAGS_OFF, but you are
//  responsible for m_hinstDLL.
//
//  Use FreeProcHeapMem_WW to discard the string before the caller returns.
//  ----------------------------------------------------------------------------

#define GetStringFromThisDLL(pNId)      ( GetAnyResource_WW  ( pNId , m_hinstDLL ) )
#define GetWideStringFromThisDLL(pNId)  ( GetAnyResourceW_WW ( pNId , m_hinstDLL ) )

#define FreeProcHeapMem_WW(pBuffer)     ( HeapFree ( m_hProcHeap ,        \
                                                     HEAP_ALL_FLAGS_OFF , \
                                                     pBuffer ) )

#ifdef _FORMATMSGS_WW
    #define FormatMsgForConsole_WW(plpHint, pdwError)                                            \
                                        ( EM_ShowMsgOnConsole_WW   ( plpHint ,                   \
                                                                     pdwError ,                  \
                                                                     STATUS_CODE_HEXADECIMAL ) )
    #define FormatMsgForMsgbox_WW(plpHint, pdwError)                                             \
                                        ( EM_FormatMsgForMsgbox_WW ( plpHint ,                   \
                                                                     pdwError ,                  \
                                                                     STATUS_CODE_HEXADECIMAL ) )
#else
    #pragma message ( __FILE__ " Since neither FormatMsgs_WW.H, nor P6CStringLib1.H is included in this translation unit," )
    #pragma message ( __FILE__ "     macros FormatMsgForConsole_WW and FormatMsgForMsgbox_WW are disabled." )
#endif  /* #ifdef _FORMATMSGS_WW */


/*
    ----------------------------------------------------------------------------

    Name:       TcsLenEvenIfNull

    Synopsis:   Compute the length of a string, given a pointer that may be a
                null reference.

    In:         plpString           = Pointer to a null terminated string,
                                      explicitly cast to a LPCTSTR, to match the
                                      generic TCHAR-mapped prototype of _tcslen,
                                      so that your compiler will leave you alone.

    Out:        Length of string, or zero if plpString is a null reference.

    Remarks:    This macro masks a shortcoming in the CRT library, which is that
                _tcslen fails badly when passed a null reference, because it
                assumes that the pointer it receives is valid, and dispenses
                with a null reference check.

                STRLEN_EMPTY_P6C is defined upstream in MathMacros_WW.H, which
                CharPosMacros_WW.H pulls into the stream.
    ----------------------------------------------------------------------------
*/

#ifndef TcsLenEvenIfNull
    #define TcsLenEvenIfNull(plpString) StringIsNullOrEmptyWW ( plpString ) \
                                        ? STRLEN_EMPTY_P6C                  \
                                        : _tcslen ( plpString )

    #ifndef TcsLenEvenIfNullWW
        #define TcsLenEvenIfNullWW      TcsLenEvenIfNull
    #endif  /* #ifndef TcsLenEvenIfNullWW */
#endif  /* #ifndef TcsLenEvenIfNull */
#endif  /* #if !defined ( TCHARMACROS_WW_INCLUDED ) */