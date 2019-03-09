//{{NO_DEPENDENCIES}}

#if !defined ( _MATHMACROS_WW_DEFINED )
#define _MATHMACROS_WW_DEFINED

/*
    ============================================================================

    File Name:          MathMacros_WW.H

    File Synopsis:      This C/C++ header file defines some macros to simplify
                        some fairly simple, but obtuse mathematical operations.

    Remarks:            Since it is composed entirely of macros, there is no DLL
                        or link library associated with this header.
                        The macros defined herein are defined in such a way that
                        they can be incorporated into expressions as though they
                        were

    Date Created:       Saturday, 06 April 2013

    License:            Copyright (C) 2013-2017, David A. Gray. All rights reserved.

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
    2013/04/06 DAG Header created and first used in HotkeyHook.dll.

    2013/05/06 DAG Add IsLastLoopLT_WW and IsLastLoopLE_WW macros, for use in
                   SafeMemCpy_TestStand.

    2013/05/06 DAG Move the macros defined within the code block guarded by CPP
                   variable _ARRAY_MACROS_P6C guard variables from their initial
                   home, CommonConstants_P6C.H. For now, I'll leave them in both
                   places, to prevent Visual Studio from marking everything in
                   my library as out of date.

    2013/05/19 DAG Define symbolic constants for zero, plus one, and minus one,
                   unless each is already defined, making this header file fully
                   independent of CommonConstants_P6C.H.

    2013/05/25 DAG Move the rest of the ambiguous constant definitions from
                   CommonConstants_P6C.H, and merge this header into it by way
                   of an include directive.

    2013/06/10 DAG Add guard blocks around the ambiguous and array constants,
                   which are defined here and there in other headers and source
                   files.

                   NOTE: Existing code is unaffected, and need not be compiled.

    2013/06/12 DAG Add a guarded copy of my Unless macro.

    2013/06/18 DAG Move EVENLY_DIVISIBLE_WW from CommonConstants_P6C.H. Since
                   CommonConstants_P6C.H includes this header, this is a
                   transparent change, but it allows EVENLY_DIVISIBLE_WW to be
                   defined without calling the rest of this header into the
                   translation stream.

    2013/08/03 DAG Define a new macro, ClearMaskedBits_WW, to simplify
                   stripping flags, such as APPLICATION_ERROR_MASK, from bit
                   masks, such as LastDllError and HRESULTs.

    2013/09/29 DAG Rewrite macro ClearMaskedBits_WW, and prove, via function
                   BitMasking, defined in BitMasking.cpp, that it behaves
                   correctly with one or more bits in the mask.

    2015/01/16 DAG I finally remembered to define ARRAY_NEXT_ELEMENT_P6C.

    2015/08/23 DAG 1) Incorporate XorSwap, which I thoroughly tested in one of
                      my experiment program sand boxes.

                   2) Correct typographical errors flagged by the spelling
                      checker extension that I installed into the Visual Studio
                      2013 IDE.

    2015/08/27 DAG Since CommonConstants_P6C.H always includes this header, this
                   header may as well be the sole source of the Unless macro.

    2015/09/21 DAG Correct typographical errors flagged by the spelling checker.

    2016/01/19 DAG 1) Add ITOA_RADIX_ constants that cover the most common uses
                      of the _itoa and _itoa_s constellations of functions that
                      format integers as alphanumeric strings.

                   2) Move the AMBIGUOUS_NUMERALS and _AMBIGUOUS_CHARACTERS
                      groups from CommonConstants_P6C.H.

    2016/03/06 DAG Eliminate MEMSET_ZERO_WW, the only change to this header in a
                   set of duplication edits coordinated with the help of
                   UltraEdit and Excel.

    2016/07/05 DAG Define seven macros IsEvenlyDivisible, a set of six, and
                   MakePtr.

    2017/05/24 DAG Correct some annoying typographical errors in these comments.

    2017/06/17 DAG Define a new ToggleSign_WW macro.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

//  ----------------------------------------------------------------------------
//  Define symbolic constants for ambiguous numeric literals.
//
//  NOTE:   ZERO_P6C always means numeric zero, unlike NULL, which is intended
//          to represent a null pointer. Consequently, its actual value
//          depends on whether UNICODE is defined.
//  ----------------------------------------------------------------------------

#ifndef _AMBIGUOUS_NUMBERS
    #define _AMBIGUOUS_NUMBERS

    #ifndef MINUS_ONE_P6C
        #define MINUS_ONE_P6C               ( -1 )
    #endif  /* MINUS_ONE_P6C */

    #ifndef MINUS_TWO_P6C
        #define MINUS_TWO_P6C               ( -2 )
    #endif  /* MINUS_TWO_P6C */

    #ifndef PLUS_ONE_P6C
        #define PLUS_ONE_P6C                ( +1 )
    #endif  /* PLUS_ONE_P6C */

    #ifndef PLUS_TWO_P6C
        #define PLUS_TWO_P6C                ( +2 )
    #endif  /* PLUS_TWO_P6C */

    #ifndef ZERO_P6C
        #define ZERO_P6C                    (  0 )
    #endif  /* ZERO_P6C */

    //  ------------------------------------------------------------------------
    //  Map _P6C constants to like named_WW constants.
    //  ------------------------------------------------------------------------

    #ifndef ZERO_WW
        #define ZERO_WW                     ZERO_P6C
    #endif  /* ZERO_WW */

    #ifndef MINUS_ONE_WW
        #define MINUS_ONE_WW                MINUS_ONE_P6C
    #endif  /* MINUS_ONE_WW */

    #ifndef MINUS_TWO_WW
        #define MINUS_TWO_WW                MINUS_TWO_P6C
    #endif  /* MINUS_TWO_WW */

    #ifndef PLUS_ONE_WW
        #define PLUS_ONE_WW                 PLUS_ONE_P6C
    #endif  /* PLUS_ONE_WW */

    #ifndef PLUS_TWO_WW
        #define PLUS_TWO_WW                 PLUS_TWO_P6C
    #endif  /* PLUS_TWO_WW */
#endif  /* _AMBIGUOUS_NUMBERS */

//  ----------------------------------------------------------------------------
//  These alphabetic characters are easy to confuse with numerals.
//  ----------------------------------------------------------------------------

#ifndef _AMBIGUOUS_CHARACTERS
    #define _AMBIGUOUS_CHARACTERS

    #define LETTER_B_LC_WW                  ( ( TCHAR ) 'b' )
    #define LETTER_B_UC_WW                  ( ( TCHAR ) 'B' )

    #define LETTER_I_LC_WW                  ( ( TCHAR ) 'i' )
    #define LETTER_I_UC_WW                  ( ( TCHAR ) 'I' )

    #define LETTER_J_LC_WW                  ( ( TCHAR ) 'j' )
    #define LETTER_J_UC_WW                  ( ( TCHAR ) 'J' )

    #define LETTER_L_LC_WW                  ( ( TCHAR ) 'l' )
    #define LETTER_L_UC_WW                  ( ( TCHAR ) 'L' )

    #define LETTER_O_LC_WW                  ( ( TCHAR ) 'o' )
    #define LETTER_O_UC_WW                  ( ( TCHAR ) 'O' )

    #define LETTER_S_LC_WW                  ( ( TCHAR ) 's' )
    #define LETTER_S_UC_WW                  ( ( TCHAR ) 'S' )

    #define LETTER_Z_LC_WW                  ( ( TCHAR ) 'z' )
    #define LETTER_Z_UC_WW                  ( ( TCHAR ) 'Z' )
#endif  /* #ifndef _AMBIGUOUS_CHARACTERS */

#ifndef _AMBIGUOUS_NUMERALS
    #define _AMBIGUOUS_NUMERALS

    #define NUMERAL_ZERO_WW                 ( ( TCHAR ) '0' )
    #define NUMERAL_ONE_WW                  ( ( TCHAR ) '1' )
    #define NUMERAL_TWO_WW                  ( ( TCHAR ) '2' )
    #define NUMERAL_THREE_WW                ( ( TCHAR ) '3' )
    #define NUMERAL_FOUR_WW                 ( ( TCHAR ) '4' )
    #define NUMERAL_FIVE_WW                 ( ( TCHAR ) '5' )
    #define NUMERAL_SIX_WW                  ( ( TCHAR ) '6' )
    #define NUMERAL_SEVEN_WW                ( ( TCHAR ) '7' )
    #define NUMERAL_EIGHT_WW                ( ( TCHAR ) '8' )
    #define NUMERAL_NINE_WW                 ( ( TCHAR ) '9' )
#endif  /* #ifndef _AMBIGUOUS_NUMERALS */

#define EVENLY_DIVISIBLE_WW                 ZERO_WW


//  ----------------------------------------------------------------------------
//  Define constants for processing arrays.
//
//  Add ARRAY_ORDINAL_TO_INDEX_P6C to an ordinal (1, 2, 3) value to derive an
//  array subscript.
//
//  Add ARRAY_INDEX_TO_ORDINAL_P6C to an array subscript to derive an ordinal
//  value.
//
//  Better yet, use the macros.
//
//      OrdinalToArrayIndexP6C - Given an ordinal index (1, 2, 3...), return an
//                               array subscript (0, 1, 2...).
//
//      ArrayIndexToOrdinalP6C - Given an array index (0, 1, 2...), return an
//                               ordinal index (1, 2, 3...).
//
//  ----------------------------------------------------------------------------

#ifndef _ARRAY_CONSTANTS
    #define _ARRAY_CONSTANTS

    #ifndef ARRAY_FIRST_ELEMENT_P6C
        #define ARRAY_FIRST_ELEMENT_P6C     ZERO_P6C
    #endif  /* ARRAY_FIRST_ELEMENT_P6C */

    #ifndef ARRAY_NEXT_ELEMENT_P6C
        #define ARRAY_NEXT_ELEMENT_P6C      PLUS_ONE_P6C
    #endif  /* ARRAY_NEXT_ELEMENT_P6C */

    #ifndef ARRAY_INVALID_SUBSCRIPT_P6C
        #define ARRAY_INVALID_SUBSCRIPT_P6C MINUS_ONE_P6C
    #endif  /* ARRAY_INVALID_SUBSCRIPT_P6C */

    #ifndef ARRAY_ORDINAL_TO_INDEX_P6C
        #define ARRAY_ORDINAL_TO_INDEX_P6C  MINUS_ONE_P6C
    #endif  /* ARRAY_ORDINAL_TO_INDEX_P6C */

    #ifndef ARRAY_INDEX_TO_ORDINAL_P6C
        #define ARRAY_INDEX_TO_ORDINAL_P6C  PLUS_ONE_P6C
    #endif  /* ARRAY_INDEX_TO_ORDINAL_P6C */

    #ifndef ARGV_PROGRAM_NAME_P6C
        #define ARGV_PROGRAM_NAME_P6C       ARRAY_FIRST_ELEMENT_P6C
    #endif  /* ARGV_PROGRAM_NAME_P6C */

    #ifndef ARGV_FIRST_CMDLINE_ARG_P6C
        #define ARGV_FIRST_CMDLINE_ARG_P6C  PLUS_ONE_P6C
    #endif  /* ARGV_FIRST_CMDLINE_ARG_P6C */

    #ifndef BUFFER_BEGINNING_P6C
        #define BUFFER_BEGINNING_P6C        ZERO_P6C
    #endif  /* BUFFER_BEGINNING_P6C */

    #ifndef BUFFER_INVALID_OFFSET_P6C
        #define BUFFER_INVALID_OFFSET_P6C   MINUS_ONE_P6C
    #endif  /* BUFFER_INVALID_OFFSET_P6C */

    #ifndef STRCMP_EQUAL_P6C
        #define STRCMP_EQUAL_P6C            ZERO_P6C
    #endif  /* STRCMP_EQUAL_P6C */

    #ifndef STRLEN_EMPTY_P6C
        #define STRLEN_EMPTY_P6C            ZERO_P6C
    #endif  /* #ifndef STRLEN_EMPTY_P6C */

    #ifndef STRCMP_EQUAL_WW
        #define STRCMP_EQUAL_WW             ZERO_WW
    #endif  /* STRCMP_EQUAL_WW */

    #ifndef CHARS_TO_COPY_NONE_P6C
        #define CHARS_TO_COPY_NONE_P6C      ZERO_P6C
    #endif  /* CHARS_TO_COPY_NONE_P6C */

    #ifndef NONE_P6C
        #define NONE_P6C                    ZERO_P6C
    #endif  /* NONE_P6C */

    #ifndef STRPOS_FOUND_P6C
        #define STRPOS_FOUND_P6C            PLUS_ONE_P6C
    #endif  /* STRPOS_FOUND_P6C */

    #ifndef STRPOS_NOT_FOUND_P6C
        #define STRPOS_NOT_FOUND_P6C        ZERO_P6C
    #endif  /* STRPOS_NOT_FOUND_P6C */

    #ifndef TINY_SCRATCH_BUFFER_255
        #define TINY_SCRATCH_BUFFER_255     255
    #endif  /* TINY_SCRATCH_BUFFER_255 */

    #ifndef TINY_SCRATCH_BUFFER_256
        #define TINY_SCRATCH_BUFFER_256     256
    #endif  /* TINY_SCRATCH_BUFFER_256 */
#endif  /* _ARRAY_CONSTANTS */

//  ----------------------------------------------------------------------------
//  Use these constants to specify the radix argument (the last argument) to CRT
//  library functions _itoa, _itoa_s, and itoa, the last of the three being
//  deprecated in favor of the former two.
//
//  1)  According to https://msdn.microsoft.com/en-us/library/ms235327.aspx,
//      itoa is classified as a posix function, and is deprecated.
//
//  2)  https://msdn.microsoft.com/en-us/library/yakksftt.aspx describes a
//      constellation of functions, _itoa, _i64toa, _ui64toa, _itow, _i64tow,
//      and _ui64tow, that cover unsigned and signed 32 and 64 bit integers.
//
//  3)  https://msdn.microsoft.com/en-us/library/0we9x30h.aspx describes another
//      constellation of security enhanced functions, _itoa_s, _i64toa_s,
//      _ui64toa_s, _itow_s, _i64tow_s, and _ui64tow_s, that sandwich a size_t
//      sizeInCharacters argument between the buffer and radix arguments.
//  ----------------------------------------------------------------------------

#if !defined ( _ITOA_RADIX_ )
    #define _ITOA_RADIX_
    #define ITOA_RADIX_BINARY               0x02
    #define ITOA_RADIX_DECIMAL              0x0A
    #define ITOA_RADIX_HEXADECIMAL          0x0F
    #define ITOA_RADIX_OCTAL                0x08
#endif  /* _ITOA_RADIX_ */

#ifndef _ARRAY_MACROS_P6C
    #define _ARRAY_MACROS_P6C

//  ----------------------------------------------------------------------------
//  These macros document conversions between array index values, understood by
//  silicon units, and ordinal values, understood by carbon units.
//
//  NOTE:   The returned value is cast to an unsigned integer, as is the input
//          value. This should cause the compiler to issue a warning if the real
//          input cannot be cast to unsigned integer. The second addend, defined
//          above, as ARRAY_ORDINAL_TO_INDEX_P6C, of necessity, is signed.
//  ----------------------------------------------------------------------------


/*
    ----------------------------------------------------------------------------

    Name:   OrdinalToArrayIndexP6C  = Convert an ordinal number to an array
                                      index (subscript).

    In:     puintOrdinal            = Ordinal, such as a common item number.

    Out:    Array subscript corresponding to the item in position puintOrdinal
            of an array.

    Note:   The idea behind this macro is that you can start with a list of item
            numbers that are meaningful to carbon units, and get back the index,
            or subscript, of a corresponding array element, that is meaningful
            to silicon units.

            The inverse of this macro is ArrayIndexToOrdinalP6C.

    ----------------------------------------------------------------------------
*/

    #define OrdinalToArrayIndexP6C(puintOrdinal)    ( ( unsigned int ) ( ( unsigned int ) puintOrdinal + ARRAY_ORDINAL_TO_INDEX_P6C ) )


/*
    ----------------------------------------------------------------------------

    Name:   ArrayIndexToOrdinalP6C  = Convert an array index (subscript) to an
                                      ordinal (counted from one).

    In:     puintIndex              = Array index (subscript).

    Out:    Ordinal number corresponding to the specified index (subscript) of
            an array.

    Note:   The idea behind this macro is that you can start with an array index
            (subscript) that is meaningful to a silicon unit, and get back an
            ordinal number that is meaningful to carbon units.

            The inverse of this macro is OrdinalToArrayIndexP6C.

    ----------------------------------------------------------------------------
*/

    #define ArrayIndexToOrdinalP6C(puintIndex)      ( ( unsigned int ) ( ( unsigned int ) puintIndex   + ARRAY_INDEX_TO_ORDINAL_P6C ) )


/*
    ----------------------------------------------------------------------------

    Name:               ElementAddress

    Synopsis:           Compute the address of a specified element in an array,
                        for retrieving an element from the array, given a
                        pointer to its base (starting) address.

    In:                 pdwSubscript            = Zero based subscript

                        pElementType            = The typedef for an element.
                                                  See Remarks.

                        pArray                  = Void pointer to array returned
                                                  by malloc or a specialized
                                                  memory allocator that returns
                                                  void pointers.

    Out:                Address of the element at the specified subscript, for
                        use in reading or writing the element.

    Dependencies:       This macro calls another macro, ElementOffset, to get
                        the offset, relative to the base address, of an element.

    NOTE:   To date, the only routine that uses this macro is MemoryPoolWW.C. If
            it proves it worth in that routine, keep it. Otherwise, discard it.

    Example:

            PVOID * pArray ;
            int     element;
            int     nElements       = 100 ;
            int     pdwSubscript    = 10 ;

            pArray  = malloc ( nElements * sizeof ( element ) ) ;   // Allocate an array of 100 integers.
            //  Populate the array.
            element = ElementAddress ( pdwSubscript , int , pArray ) ;

    Discussion:         This macro takes the ElementOffset macro a step further,
                        by hiding the byte array from view. Internally, it calls
                        ElementOffset, and uses the returned value and the base
                        address in an expression like the example shown in the
                        internal documentation of the ElementOffset macro.
    ----------------------------------------------------------------------------
*/

    #define ElementAddress(pdwSubscript, pElementType, pArray)  ( & ( pArray [ ElementOffset ( pdwSubscript , pElementType ) ] ) )


/*
    ----------------------------------------------------------------------------

    Name:               ElementOffset

    Synopsis:           Compute the address (offset) of a specified element in
                        an array, for retrieving an element from the array,
                        given a pointer to its base (starting) address.

    In:                 pdwSubscript            = Zero based subscript

                        pElementType            = The typedef for an element.
                                                  See Remarks.

    Out:                Address (offset) of the element at the specified
                        subscript, relative to the base (starting) address of
                        the array.

    Remarks:            Use the value returned by this macro as the subscript of
                        an array of bytes.

    Example:

            PVOID * pArray ;
            int     element;
            int     nElements    = 100 ;
            int     pdwSubscript = 10 ;

            pArray  = malloc ( nElements * sizeof ( element ) ) ;   // Allocate an array of 100 integers.
            //  Populate the array.
            &element    = pArray [ ElementOffset ( pdwSubscript , int ] ; // Get the address of the 11th integer.

    Discussion:         When treated as an array, the void pointer behaves like
                        an array of bytes. Hence, the offset of the element at
                        subscript pdwSubscript is derived by multiplying
                        pdwSubscript by the size of an element, which is
                        determined from its type of int.

                        A more concise way to achieve the same result is the
                        ElementAddress macro.
    ----------------------------------------------------------------------------
*/

    #define ElementOffset(pdwSubscript, pElementType)   ( pdwSubscript * sizeof ( pElementType ) )


/*
    ----------------------------------------------------------------------------

    Name:               ElementsInArray

    Synopsis:           Compute the number of elements in an array from the
                        definition of the array as a whole and that of one of
                        its elements. See Remarks.

    In:                 pEntireArray            = The whole array. See Remarks.

                        ptypOfElement           = The typedef for an element.
                                                  See Remarks.

                        pNDimensions            = The total

        Macro Prototype                                                  Example
        ---------------------------------------------------------------- -------
        ElementsInArray ( pEntireArray, ptypOfElement)                   1
        RowsInNBy2Array ( pEntireArray, ptypOfElement)                   2
        RowsInNBy3Array ( pEntireArray, ptypOfElement, pnColumns )       3
        RowsInNByPArray ( pEntireArray, ptypOfElement, pNOtherDimes )    4

    Out:                For ElementsInArray, the return value is the number of
                        elements in the array. For all others, the return value
                        is the number of rows in the array, especially handy for
                        indexing a classic FOR loop to process the table.

    Remarks:            The motivation for the first of these macros is that I
                        needed the size (number of elements) of a const array to
                        use as the stop limit of a classic FOR loop (the kind I
                        first saw and used in Fortran). The others had a similar
                        motivation, except that the array was a table.

    Examples:           1)  Example 1 is a one-dimensional array, often called a
                            vector, the most common array found in C and C++
                            source code.

                                -------------------
                                Static initializer:
                                -------------------

                                    static DWORD adwBufSizes [ ] =
                                    {
                                        TEST_BLOCK_1_SIZE ,
                                        TEST_BLOCK_2_SIZE ,
                                        TEST_BLOCK_3_SIZE ,
                                        TEST_BLOCK_4_SIZE
                                    } ;

                                -------------------
                                Element Reference:
                                -------------------

                                    adwBufSizes [ 1 ] = TEST_BLOCK_2_SIZE;

                        2)  Example 2 is a two-dimensional array, often called a
                            matrix, table, or grid, containing two elements per
                            row.

                                -------------------
                                Static initializer:
                                -------------------

                                    static const signed __int16 aint16Samples [ 7 ] [ 2 ] =
                                    {
                                        { 10  , 3 } ,   // Subscript 0, element 1
                                        { 10  , 4 } ,   // Subscript 1, element 2
                                        { 10  , 5 } ,   // Subscript 2, element 3
                                        { 16  , 4 } ,   // Subscript 3, element 4
                                        { -10 , 3 } ,   // Subscript 0, element 5
                                        { -12 , 3 } ,   // Subscript 0, element 6
                                        { -14 , 3 } ,   // Subscript 0, element 7
                                    };  // aint16Samples

                                -------------------
                                Element Reference:
                                -------------------

                                    aint16Samples [ 5 ] [ 0 ] = -10;

                            3)  Example 3 is another two-dimensional array
                                containing three elements per row.

                                    static const signed __int16 aint16Samples3 [ 7 ] [ 2 ] =
                                    {
                                        { 10  , 3 , 0 } ,   // Subscript 0, element 1
                                        { 10  , 4 , 0 } ,   // Subscript 1, element 2
                                        { 10  , 5 , 1 } ,   // Subscript 2, element 3
                                        { 16  , 4 , 1 } ,   // Subscript 3, element 4
                                        { -10 , 3 , 0 } ,   // Subscript 0, element 5
                                        { -12 , 3 , 1 } ,   // Subscript 0, element 6
                                        { -14 , 3 , 0 } ,   // Subscript 0, element 7
                                    };  // aint16Samples

                                -------------------
                                Element Reference:
                                -------------------

                                    aint16Samples [ 5 ] [ 0 ] = -10;

                        4)  Example 4 is a three-dimensional array, which can be
                            visualized as a Parallelepiped, about which please
                            see https://en.wikipedia.org/wiki/Parallelepiped, of
                            which the cube is the best known special case.
                            However, unlike a cube, the three dimensions of a 3D
                            array can differ.

                                -------------------
                                Static initializer:
                                -------------------

                                    double cprogram [ 3 ] [ 2 ] [ 4 ] =
                                    {
                                        {
                                            {-0.1 , 0.22 , 0.3  , 4.3  } ,
                                            {2.3  , 4.7  , -0.9 , 2    }
                                         } ,
                                         {
                                            {0.9  , 3.6  , 4.5  , 4    } ,
                                            {1.2  , 2.4  , 0.22 , -1   }
                                         } ,
                                         {
                                            { 8.2 , 3.12 , 34.2 , 0.1  } ,
                                            { 2.1 , 3.2  , 4.3  , -2.0 }
                                         }
                                    } ;

                            Credit for the above example goes to
                            http://www.programiz.com/c-programming/c-multi-dimensional-arrays

                                -------------------
                                Element Reference:
                                -------------------

                                    cprogram [ 0 ] [ 1 ] [ 3 ] = 2;

    Discussion:         In the first examples above, sizeof ( adwBufSizes ) is
                        the size, in bytes, occupied by the entire array, while
                        sizeof ( DWORD ) returns the size, in bytes, occupied by
                        one of its elements. The macro instructs the compiler to
                        compute the two sizes, then divide the size of the array
                        by the size of one of its elements.

                        The remaining examples are complicated by the fact that
                        the array is a table, and we need to know the number of
                        rows contained therein to drive a loop that is expected
                        to process one row on each iteration, while RowsInNBy*
                        macros return row counts that can stop a FOR loop that
                        executes once per row (outermost dimension representing
                        a row).

    ----------------------------------------------------------------------------
*/

    #define ElementsInArray(pEntireArray, ptypOfElement)                \
                                        (   sizeof ( pEntireArray ) / sizeof ( ptypOfElement ) )
    #define RowsInNBy2Array(pEntireArray, ptypOfElement)                \
                                        ( ( sizeof ( pEntireArray ) ) / ( sizeof ( ptypOfElement ) * 2 ) )
    #define RowsInNBy3Array(pEntireArray, ptypOfElement)                \
                                        ( ( sizeof ( pEntireArray ) ) / ( sizeof ( ptypOfElement ) * 3 ) )
    #define RowsInNByPArray(pEntireArray, ptypOfElement, pNDimensions)  \
                                        ( ( sizeof ( pEntireArray ) ) / ( sizeof ( ptypOfElement ) * pNDimensions ) )
#endif  /* #ifndef _ARRAY_MACROS_P6C */


/*
    ============================================================================

    Macro Name:         ClearMaskedBits_WW

    Arguments:          pdwBitMaskIn    = The bit mask from which to clear bits.

                        pdwMaskToRemove = The mask of bits to clear.

    Returns:            Intended for use as an expression, this macro evaluates
                        to pdwBitMaskIn, with the bits in pdwMaskToRemove turned
                        off.

    Remarks:            For maximum flexibility, the inputs are not typecast.
                        However, they must be of the same type, or the result is
                        unpredictable, because the smaller value is promoted to
                        a type that has the same number of bits as the larger
                        (wider) value.

    Example:            ClearMaskedBits_WW ( dwStatus , APPLICATION_ERROR_MASK )

    ============================================================================
*/

#define ClearMaskedBits_WW(pdwBitMaskIn, pdwMaskToRemove)   \
                                            ( pdwBitMaskIn & (~ pdwMaskToRemove ) )


/*
    ============================================================================

    Macro Name:         IsBitOn_WW

    Arguments:          pdwMask         = The constant bit mask agaainst which
                                          to evaluate an unknown variable bit
                                          array

                        pdwBitArray     = The bit array to test against constant
                                          bit mask pdwMask

    Returns:            The return value is TRUE if ALL bits that are ON in
                        pdwMask are also ON in pdwBitArray. Otherwise, the
                        return value is FALSE.

    Example:            if ( IsBitOn_WW ( pdwMask , pdwBitArray ) )

                        where: pdwMask     = 0x00000080 0x00000080 0x00000080
                               pdwBitArray = 0xffffffff 0xffffff7f 0000000000
                               return      = TRUE       FALSE      FALSE

    Remarks:            All three examples use the same value for pdwMask.

                        1)  In the first example, pdwMask is compared against a
                            bit array which has all of its bits turned on.

                        2)  In the second example, pdwMask is compared against a
                            bit array which has all of its bits turned on EXCEPT
                            the bit that is turned on in pdwMask.

                        3)  In the third example, pdwMask is compared against a
                            bit array which has all of its bits turned off.

                        The point to keep in mind is that this test ignores all
                        bits in pdwMask, unless they are ON, which is taken to
                        be TRUE.

                        Argument pdwMask is expected to be a constant, such as
                        are found throughout the Windows Platform SDK headers,
                        and elsewhere.

                        Argument pdwBitArray is expected to be an unknown, such
                        as a set of state flags whose values represent the state
                        of various internal switches or parameter settings that
                        affect the desired behavior of your program.

    ============================================================================
*/

#define IsBitOn_WW(pdwMask, pdwBitArray)    ( ( pdwMask & pdwBitArray ) == pdwMask )


/*
    ============================================================================

    Macro Name:         IsLastLoopLT_WW and IsLastLoopLE_WW

    Arguments:          pintLoopIndex   = The current value of the loop index.

                        pintLoopLimit   = The stop limit of the loop index.

    Returns:            The return value is logically TRUE if the loop is on its
                        last iteration.

    Remarks:            Use these macros within the scope of a FOR loop to test
                        for the last iteration.

                            Loop termination Condition      Macro to Use
                            ------------------------------  ---------------
                            pintLoopIndex < pintLoopLimit   IsLastLoopLT_WW
                            pintLoopIndex <= pintLoopLimit  IsLastLoopLE_WW

    Example:            for ( pintLoopIndex = 0 ; pintLoopIndex < pintLoopLimit ; pintLoopIndex++ )
                        {
                            // Do stuff on every iteration.

                            if ( IsLastLoopLT_WW ( pintLoopIndex , pintLoopLimit ) )
                            {
                                // Do something once only, on the last iteration.
                            }
                            else
                            {
                                // Do something on every iteration EXCEPT the last.
                            }   // if ( IsLastLoopLT_WW ( pintLoopIndex , pintLoopLimit ) )

                            // Do more stuff on every iteration.

                        }   // for ( pintLoopIndex = 0 ; pintLoopIndex < pintLoopLimit ; pintLoopIndex++ )

    ============================================================================
*/

#define IsLastLoopLT_WW(pintLoopIndex, pintLoopLimit)   ( ( pintLoopIndex + 1 ) == pintLoopLimit )
#define IsLastLoopLE_WW(pintLoopIndex, pintLoopLimit)   ( pintLoopIndex == pintLoopLimit )


/*
    ----------------------------------------------------------------------------

    Name:               IsEvenlyDivisible

    Synopsis:           Having discovered that it can be somewhat tricky to get
                        right if your need for it is infrequent, I created this
                        little macro that encodes the modulus operation and test
                        required to return TRUE if integer A, the Dividend is
                        evenly divisible by integer B, the Divisor.

    In:                 pintDividend        = The integer to evaluate against
                                              pintDivisor

                        pintDivisor         = The integer against which to
                                              evaluate pintDividend

    Out:                The macro evaluates to TRUE if Dividend is evenly
                        divisible by Divisor, although it is not literally cast
                        to Boolean.

    Remarks:            This macro uses the Modulus macro, defined below, to get
                        the remainder to test against zero, the indicator that a
                        dividend is evenly divisible by a divisor. As is true of
                        the underlying Modulus macro, this macro is not tricky,
                        so I think of it as FDA tested syntactic sugar.

    See Also:           Modulus, which returns the modulus of its arguments.
    ----------------------------------------------------------------------------
*/

#define IsEvenlyDivisible(pintDividend, pintDivisor)      \
                                            ( ( Modulus ( pintDividend , pintDivisor ) ) == EVENLY_DIVISIBLE_WW )

/*
    ----------------------------------------------------------------------------

    Name:               Modulus

    Synopsis:           Having discovered that I can never remember the modulus
                        operator, which I need infrequently, I created this
                        little macro that encodes the modulus operation and its
                        operands in the correct order, since Modulus is not
                        commutative.

    In:                 pintDividend        = The integer to evaluate against
                                              pintDivisor

                        pintDivisor         = The integer against which to
                                              evaluate pintDividend

    Out:                The macro returns the modulus (remainder) from integer
                        division of Dividend by Divisor.

    Remarks:            While this macro isn't especially tricky, I wrote it so
                        that I didn't have to look up the symbol for the modulus
                        operator for the one or two times a year that I need it.
                        Instead, I just input "Modulus (" and let IntelliSense
                        show me the way.

    See Also:           IsEvenlyDivisible, which returns TRUE or FALSE depending
                        whether or not the modulus is zero.
    ----------------------------------------------------------------------------
*/

#define Modulus(pintDividend, pintDivisor)  ( pintDividend % pintDivisor )

/*
    ----------------------------------------------------------------------------

    Name:               MakePtr

    Synopsis:           Having discovered that it can be somewhat tricky to get
                        right if your need for it is infrequent, I created this
                        little macro that returns a strongly typed pointer to a
                        specified type of variable, including an optional offset
                        to add to the input pointer.

    In:                 cast                = Type to which pointer is cast

                        ptr                 = Pointer address, internally cast
                                              to DWORD by the macro

                        addValue            = Offset to add to ptr before it is
                                              cast as specified and returned

    Out:                The return value is a pointer of the specified type.

    Remarks:            This macro arrived via P6CUtilLib1_Pvt.H, into which it
                        arrived from the source code of PEDump.exe, which I took
                        apart when I created my routine for querying the Windows
                        subsystem in which a program runs.
    ----------------------------------------------------------------------------
*/

#define MakePtr(cast, ptr, addValue )       ( ( cast ) ( ( DWORD ) ( ptr ) + ( DWORD ) ( addValue ) ) )


/*
    ----------------------------------------------------------------------------

    Name:               ToggleSign_WW

    Synopsis:           Toggle (invert) the sign of any numeric value.

    In:                 pAnyNumber          = Any expression that evaluates to a
                                              numeric value that has a sign

    Out:                The negative of pAnyNumber

    Examples:           The following table gives enough examples that any
                        competent programmer should be able to understand how to
                        use this macro.

                        -------------------------
                        pAnyNumber  ToggleSign_WW
                        ----------  -------------
                        12345       -12345
                        3.14159     -3.14159
                        -98765      98765
                        -1.333      1.333
                        0           0
                        -------------------------

    Remarks:            This macro is syntactic sugar, since all it does is flip
                        the sign of pAnyNumber, by multiplying it by -1. hence,
                        it doesn't save any instructions, but I believe that it
                        makes the code clearer by eliminating the need for two
                        successive arithmetic operator tokens, and its name
                        should make its intent quite eveident.

                        For those for whom English is not your first language:

                        Toggle (intransitive verb): to switch between two
                               options especially of an electronic device
                               usually by pressing a single button or a simple
                               key combination

    Reference:          "Toggle" (definition), in Merriam-Webster Dicttionary of
                        the English Language
                        https://www.merriam-webster.com/dictionary/toggle
    ----------------------------------------------------------------------------
*/

#if !defined ( ToggleSign_WW )
    #define ToggleSign_WW(pAnyNumber)       ( pAnyNumber * MINUS_ONE_WW )
#endif  /* #if !defined ( ToggleSign_WW ) */


/*
    ----------------------------------------------------------------------------

    Name:               Unless

    Synopsis:           Implement the unless(pExpr) idiom of Perl.

    In:                 pExpr               = Any expression that evaluates to
                                              TRUE or FALSE.

    Out:                The inverse of the Boolean value of pExpr.

    Remarks:            This becomes ever more useful for making the intent of a
                        test clear as the complexity of pExpr increases.
    ----------------------------------------------------------------------------
*/

#define Unless(pExpr)                       if ( !(pExpr) )

/*
    ----------------------------------------------------------------------------
    Name:               XorSwap

    Synopsis:           Swap two values, pdwX and pdwY, where pdwX and pdwY are
                        of like INTEGRAL types.

    In:                 pdwX    = Integer 1 of 2
                        pdwY    = Integer 2 of 2

    Out:                pdwX    = becomes pdwY.
                        pdwY    = becomes pdwX.

    Remarks:            If you are accustomed to treating macros as functions,
                        then treat this one as a function that takes arguments
                        by reference, updates both of them, and returns nothing.

                        The swap is performed by executing three XOR operations,
                        in a very specific order, so that it can be accomplished
                        without using a temp variable, although, strictly
                        speaking, you might count the CPU register in which the
                        XOR operations are performed, although the register can
                        be optimized away if XOR can operate on a pair of memory
                        locations.
    ----------------------------------------------------------------------------
*/

#define XorSwap(pdwX, pdwY) \
                                            pdwX ^= pdwY ;  \
                                            pdwY ^= pdwX ;  \
                                            pdwX ^= pdwY ;
#endif  /* _MATHMACROS_WW_DEFINED */