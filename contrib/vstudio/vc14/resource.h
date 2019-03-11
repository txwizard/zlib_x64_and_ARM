//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by zlibapps.rc

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE			101
#define _APS_NEXT_COMMAND_VALUE				40001
#define _APS_NEXT_CONTROL_VALUE				1001
#define _APS_NEXT_SYMED_VALUE				101
#endif	// #ifndef APSTUDIO_READONLY_SYMBOLS
#endif	// #ifdef APSTUDIO_INVOKED

#define VER_COMPANY_NAME					"Jean-loup Gailly & Mark Adler"
#define VER_FILE_VERSION					"1.2.11.0"
#define VER_LEGAL_COPYRIGHT					"(C) 1995-2017 Jean-loup Gailly & Mark Adler"
#define VER_PRODUCT_NAME					"ZLib.DLL"
#define VER_PRODUCT_VERSION					"1.2.11.0"

#if   defined ( PROJ_IS_miniunz )
    #define VER_FILE_DESCRIPTION			"Stand-alone UnZip Utility"
    #define VER_INTERNAL_NAME				"miniunz.exe"
#elif defined ( PROJ_IS_minizip )
    #define VER_FILE_DESCRIPTION			"Stand-alone Zip Utility"
    #define VER_INTERNAL_NAME				"minizip.exe"
#elif defined ( PROJ_IS_minizip )
    #define VER_FILE_DESCRIPTION			"Stand-alone UnZip Utility"
    #define VER_INTERNAL_NAME				"miniunz.exe"
#elif defined ( PROJ_IS_testzlib )
    #define VER_FILE_DESCRIPTION			"Test Program for Zlib Static Link Library"
    #define VER_INTERNAL_NAME				"testzlib.exe"
#elif defined ( PROJ_IS_testzlibdll )
    #define VER_FILE_DESCRIPTION			"Test Program for Zlib Dynamic Link Library"
    #define VER_INTERNAL_NAME				"testzlibdll.exe"
#else
    #define VER_FILE_DESCRIPTION			"zlib data compression and ZIP file I/O library"
	#define VER_INTERNAL_NAME				"zlibdll.exe"
#endif /* #if defined ( PROJ_minizip_DEFINED ) */

#if defined ( PLATFORM_IS_Win32 )
    #define VER_PLATFORM					" for WIN32"
#endif	/* #if defined ( PLATFORM_IS_Win32 ) */

#if defined ( PLATFORM_IS_x64 )
    #define VER_PLATFORM					" for x64"
#endif	/* #if defined ( PLATFORM_IS_x64 ) */

#if defined ( PLATFORM_IS_ARM )
    #define VER_PLATFORM					" for ARM"
#endif	/* #if defined ( PLATFORM_IS_ARM ) */

#if defined ( PLATFORM_IS_ARM64 )
    #define VER_PLATFORM					" for ARM64"
#endif	/* #if defined ( PLATFORM_IS_ARM64 ) */

//	#define DOTTED_VERSION EXPAND(MAJOR_VERSION) “.” EXPAND(MINOR_VERSION) “.” EXPAND(RELEASE_NUMBER) “.”
//	#if defined ( RC_INVOKED )
    #define VER_DESCRIPTION_AND_PLATFORM    VER_FILE_DESCRIPTION VER_PLATFORM
//#else
//	  #define VER_DESCRIPTION_AND_PLATFORM	VER_FILE_DESCRIPTION VER_PLATFORM
//#endif	/* #if defined( RC_INVOKED ) */
