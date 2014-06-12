# Microsoft Developer Studio Project File - Name="FCµØÍ¼±à¼­Æ÷" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FCµØÍ¼±à¼­Æ÷ - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FCµØÍ¼±à¼­Æ÷.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FCµØÍ¼±à¼­Æ÷.mak" CFG="FCµØÍ¼±à¼­Æ÷ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FCµØÍ¼±à¼­Æ÷ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FCµØÍ¼±à¼­Æ÷ - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FCµØÍ¼±à¼­Æ÷ - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "FCµØÍ¼±à¼­Æ÷ - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FCµØÍ¼±à¼­Æ÷ - Win32 Release"
# Name "FCµØÍ¼±à¼­Æ÷ - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChrViewerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardData.cpp
# End Source File
# Begin Source File

SOURCE=.\DefaultValueDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DiyChr.cpp
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷.cpp"
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷.rc"
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷Doc.cpp"
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷View.cpp"
# End Source File
# Begin Source File

SOURCE=.\InputTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\MapAttributeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NESViewChr.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelView.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveStyleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewColDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChrViewerDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardData.h
# End Source File
# Begin Source File

SOURCE=.\DefaultValueDlg.h
# End Source File
# Begin Source File

SOURCE=.\DiyChr.h
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷.h"
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷Doc.h"
# End Source File
# Begin Source File

SOURCE=".\FCµØÍ¼±à¼­Æ÷View.h"
# End Source File
# Begin Source File

SOURCE=.\InputTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Map.h
# End Source File
# Begin Source File

SOURCE=.\MapAttributeDlg.h
# End Source File
# Begin Source File

SOURCE=.\NESViewChr.h
# End Source File
# Begin Source File

SOURCE=.\PanelDlg.h
# End Source File
# Begin Source File

SOURCE=.\PanelView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SaveNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\SaveStyleDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\ViewColDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=".\res\FCµØÍ¼±à¼­Æ÷.ico"
# End Source File
# Begin Source File

SOURCE=".\res\FCµØÍ¼±à¼­Æ÷.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\FCµØÍ¼±à¼­Æ÷Doc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
