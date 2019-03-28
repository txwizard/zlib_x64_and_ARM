# ZLib for Windows for Intel and ARM Processors ReadMe

The purpose of this repository is to publish a port of the famous ZLib (zlib,
for purists - you know who you are) library for creating Zip archives and
extracting files from them to Windows 10 running on ARM processors, such as the
Qualcomm Snapdragon series, which powers the Asus ASUS NovaGo TP370QL, about
which you can learn more at
<https://www.asus.com/us/2-in-1-PCs/ASUS-NovaGo-TP370QL/>.

This code builds on the latest version of ZLib (__1.2.11__) published on the
official site, at <https://www.zlib.net/>, adding the following configurations:

- __ARM__ runs in 32-bit mode on any ARM processor.
- __ARM64__ runs in 64-bit mode on any ARM processor.
- __x64__ runs in 64-bit mode on Intel and AMD processors.

For completeness, this repository includes the __Win32__ (32 bit Windows on
Intel/AMD) binaries, and the Visual Studio project included herein can build any
of them.

## Using These Libraries

If you have any edition of Visual Studio 2017 installed on a 64-bit copy of
Microsoft Windows, and you intend to use only the 64-bit Intel libraries, you
may skip the rest of this section, because the required runtime libraries are
already installed.

Otherwise, please keep reading, especially if your target is an ARM processor,
since the Microsoft C runtime for ARM is tucked away, and finding them took
many searches, spread across about a week, to find a proper package. Moreover,
extracting them from that package requires some specialized knowledge about the
internal format of a NuGet package.

For your convenience, the required CRT libraries are included in the binary
packages, and the build scripts deposit a copy into the output directory of each
project.

## The Visual Studio Solution and Projects

Since the repository retains the structure of the official distribution, the
Visual Studio solution and projects are in directory `zlib-1.2.11\contrib\vstudio\vc14`.

The following table describes the organization of the output directories

   | Platform | Configuration | Project    | Description                       | Directory               |
   |----------|---------------|------------|-----------------------------------|-------------------------|
   | ARM      | Debug         |miniunz     | Stand-alone unzipper              | ARM\miniunz_Debug       |
   | ARM      | Release       |miniunz     | Stand-alone unzipper              | ARM\miniunz_Release     |
   | ARM      | Debug         |minizip     | Stand-alone zipper                | ARM\minizip_Debug       |
   | ARM      | Release       |minizip     | Stand-alone zipper                | ARM\minizip_Release     |
   | ARM      | Debug         |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Debug   |
   | ARM      | Release       |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Release |
   | ARM      | Debug         |testzlib    | Unit test for Zlib static library | ARM\testzlib_Debug      |
   | ARM      | Release       |testzlib    | Unit test for Zlib static library | ARM\testzlib_Release    |
   | ARM      | Debug         |zlibstat    | Zlib static library               | ARM\zlibstat_Debug      |
   | ARM      | Release       |zlibstat    | Zlib static library               | ARM\zlibstat_Release    |
   | ARM      | Debug         |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Debug        |
   | ARM      | Release       |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Release      |
   | ARM64    | Debug         |miniunz     | Stand-alone unzipper              | ARM\miniunz_Debug       |
   | ARM64    | Release       |miniunz     | Stand-alone unzipper              | ARM\miniunz_Release     |
   | ARM64    | Debug         |minizip     | Stand-alone zipper                | ARM\minizip_Debug       |
   | ARM64    | Release       |minizip     | Stand-alone zipper                | ARM\minizip_Release     |
   | ARM64    | Debug         |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Debug   |
   | ARM64    | Release       |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Release |
   | ARM64    | Debug         |testzlib    | Unit test for Zlib static library | ARM\testzlib_Debug      |
   | ARM64    | Release       |testzlib    | Unit test for Zlib static library | ARM\testzlib_Release    |
   | ARM64    | Debug         |zlibstat    | Zlib static library               | ARM\zlibstat_Debug      |
   | ARM64    | Release       |zlibstat    | Zlib static library               | ARM\zlibstat_Release    |
   | ARM64    | Debug         |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Debug        |
   | ARM64    | Release       |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Release      |
   | Win32    | Debug         |miniunz     | Stand-alone unzipper              | ARM\miniunz_Debug       |
   | Win32    | Release       |miniunz     | Stand-alone unzipper              | ARM\miniunz_Release     |
   | Win32    | Debug         |minizip     | Stand-alone zipper                | ARM\minizip_Debug       |
   | Win32    | Release       |minizip     | Stand-alone zipper                | ARM\minizip_Release     |
   | Win32    | Debug         |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Debug   |
   | Win32    | Release       |testzlibdll | Unit test for Zlib DLL            | ARM\testzlibdll_Release |
   | Win32    | Debug         |testzlib    | Unit test for Zlib static library | ARM\testzlib_Debug      |
   | Win32    | Release       |testzlib    | Unit test for Zlib static library | ARM\testzlib_Release    |
   | Win32    | Debug         |zlibstat    | Zlib static library               | ARM\zlibstat_Debug      |
   | Win32    | Release       |zlibstat    | Zlib static library               | ARM\zlibstat_Release    |
   | Win32    | Debug         |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Debug        |
   | Win32    | Release       |zlibvc      | Zlib dynamic link library         | ARM\zlibvc_Release      |
   | X64      | Debug         |miniunz     | Stand-alone unzipper              | X64\miniunz_Debug       |
   | X64      | Release       |miniunz     | Stand-alone unzipper              | X64\miniunz_Release     |
   | X64      | Debug         |minizip     | Stand-alone zipper                | X64\minizip_Debug       |
   | X64      | Release       |minizip     | Stand-alone zipper                | X64\minizip_Release     |
   | X64      | Debug         |testzlibdll | Unit test for Zlib DLL            | X64\testzlibdll_Debug   |
   | X64      | Release       |testzlibdll | Unit test for Zlib DLL            | X64\testzlibdll_Release |
   | X64      | Debug         |testzlib    | Unit test for Zlib static library | X64\testzlib_Debug      |
   | X64      | Release       |testzlib    | Unit test for Zlib static library | X64\testzlib_Release    |
   | X64      | Debug         |zlibstat    | Zlib static library               | X64\zlibstat_Debug      |
   | X64      | Release       |zlibstat    | Zlib static library               | X64\zlibstat_Release    |
   | X64      | Debug         |zlibvc      | Zlib dynamic link library         | X64\zlibvc_Debug        |
   | X64      | Release       |zlibvc      | Zlib dynamic link library         | X64\zlibvc_Release      |

Within each directory, the output (`.dll`, `.exp`, `.exe`, `.map`, `.lib`, and
`.pdb`) files occupy the top level directory, while the intermediate outputs
(`.asm` and `.obj`) are in the `Intermediate` subdirectory.

The Visual Studio projects fully specify the settings, to guarantee that certain
required settings have the correct values. For your convenience, these required
values are set forth in the following table.

| Target          | Property Name                 | Project    | Property Value                      |
|-----------------|-------------------------------|------------|-------------------------------------|
| ClCompile       | AdditionalIncludeDirectories  | All        | ..\..\..;..\..\masmx86;             |
| ClCompile       | PreprocessorDefinitions       | All        | BUILD_ENV_IS_VISUAL_STUDIO;         |
|                 |                               |            | PLATFORM_IS_$(Platform);            |
|                 |                               |            | WIN32;                              |
|                 |                               |            | \_CRT_NONSTDC_NO_DEPRECATE;         |
|                 |                               |            | \_CRT_SECURE_NO_DEPRECATE;          |
|                 |                               |            | \_CRT_NONSTDC_NO_WARNINGS;          |
|                 |                               |            | ZLIB_WINAPI                         |
| ClCompile       | ObjectFileName                | All        | $(IntDir)                           |
| ClCompile       | OmitFramePointers             | All        | false                               |
| ClCompile       | FloatingPointExceptions       | WIN32      | true                                |
| ClCompile       | FloatingPointExceptions       | All Others | false                               |
| ResourceCompile | PreprocessorDefinitions       | All        | BUILD_ENV_IS_VISUAL_STUDIO;         |
|                 |                               |            | PLATFORM_IS_$(Platform);            |
|                 |                               |            | NDEBUG;                             |
| Lib             | OutputFile                    | zlibstat   | $(OutDir)$(ProjectName)$(TargetExt) |
| Link            | OutputFile                    | All Others | $(OutDir)$(ProjectName)$(TargetExt) |
| Link            | ImportLibrary                 | zlibvc     | ImportLibrary                       |
| Link            | ImageHasSafeExceptionHandlers | All Win32  | true                                |
| Link            | ImageHasSafeExceptionHandlers | All Others | false                               |

__Notes__

1) `BUILD_ENV_IS_VISUAL_STUDIO` enables certain features when the project is built
   by either Visual Studio or MSBuild. Most of these are related to the next item.

2) `PLATFORM_IS_$(Platform)` causes the Visual C/C++ compiler and the Microsoft
   Resource Compiler to emit code that labels the output file (.exe or .dll)
   with the platform on which it runs. All Applications display this information
   as part of their output.

As a convenience, the Visual C runtime libraries for all four supported
platforms are organized by platform under directory `vcruntime140`, and the
project build script installs the correct CRT library into the output
directory. Two additional targets are configured to follow that; their goal is
to maintain the directories of reference libraries required by the __libxml2__
project, published at <https://github.com/txwizard/libxml2_x64_and_ARM>, and the
reference libraries used at the TXWizard shop for native code development.

Rather than using a __Post-Build__ step, these file copying operations use a
`Copy` task in an `AfterBuild` target. This choice arose from research that led
to the development of another custom target, `BeforeBuildGenerateSources`, that
lists the resolved values of the major MSBuild macros. Its aoutput appears very
close to the top of the build log, and the need for it arose from some early
trouble shooting on the __zlib__ project, of which this project is one of the
three dependencies that had to be found and built first. Since it earned its
keep on that project, all four of these projects, in addition to two unrelated
projects developed at the same time, incorporate this target.

Though neither target is visible in the Visual Studio property pages, the VS
property page editor preserves them when you edit the project properties in the
IDE, though they won't retain the beautified form that you see here, since it
removes all unnecessary white space.

## Getting the CRT Libraries: The Gory Details

To use these libraries on any supported platform, you must acquire and install
the Microsoft« C Runtime Library, version 14.00.24234.1 or later, called
`vcruntime140.dll` on all platforms. Microsoft distributes it as part of the
"Microsoft Visual C++ 2015 Redistributable Update 3 RC" package, available from
<https://www.microsoft.com/en-us/download/details.aspx?id=52685> for Intel and
AMD CPUs, and from <https://dotnet.myget.org/F/dotnet-core/api/v2/package/vc-runtime/2.0.0/>
for ARM processors.

- The __Intel/AMD__ packages come as self-extracting `EXE` files, one each for
__x86__ (32 bits) and __x64__ (64 bits), which correspond to the __Win32__ and
__x64__ configurations, respectively, in the Visual Studio project configuration
files. Though they are packaged separately, the download page offers the option
of fetching both in one pass. If you take that option, you should elect to
__dwonload__ both, then view the packages in your `Downloads` folder. This
suggestion applies to Edge and Chrome for certain, and is sound advice for other
Web browsers. Though technically self-extracting archives, manually extracting
them makes clear that they are intended to be executed, so that the executable
code embedded therein can reassemble the numerous bits into a handful of program
files before it installs them.

- The __ARM__ package comes as a `.nupkg` that can be renamed to `.zip`, and
treated as an ordinary ZIP archive. Both __ARM__ and __ARM64__ (32 and 64 bit)
runtimes come in one package. To get the goods, extract the archive into a new
directory, and use the file explorer to drill down into it. Inside directory
`content\VC\Redist\MSVC\14.14.26405\onecore` are two subdirectories, helpfully
named `arm` and `arm64`. Unlike the Intel/AMD packages, the __ARM__ package is
a straightforward, if opaque, ZIP archive, and the contents of the two leaf
directories need only to be copied into a directory that is in your __PATH__
list, and they are ready for use.

For those who are interested, the directory structure in the NuGet package
reflects the location into which the files are installed into Visual Studio
when you install the ARM compilers and tools.

To get the tools for Microsoft Visual Studio, start the __Visual Studio Installer__,
which should be on the main list of __Programs__ (not APPs), answer the UAC
prompt, and select the __Modify__ button. Once the form draws itself, select the
__Individual Components__ tab, and scroll down almost to the bottom, where you
will eventually find __Visual C++ compilers and libraries for ARM and ARM64__,
listed as two items. Still further down, you will find packages for __ATL__ and
__MFC__, which you will need if the code you plan to port uses either. Check
the packages you want, and click __Modify__. When the installer is done, you are
ready to go.
