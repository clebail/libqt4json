Name "libqt4json"

OutFile "setup-1.0.0beta1.exe"

InstallDir $PROGRAMFILES\libqt4json

DirText "Choose a destination folder for the installation of libqt4json"

Section ""

SetOutPath $INSTDIR

CreateDirectory $INSTDIR\libqt4json
CreateDirectory $INSTDIR\libqt4json\include
CreateDirectory $INSTDIR\libqt4json\lib

File libgcc_s_dw2-1.dll
File libqt4json.dll
File mingwm10.dll
File QtCore4.dll
File example.exe

SetOutPath $INSTDIR\libqt4json\include
File libqt4json\include\libqt4json.h

SetOutPath $INSTDIR\libqt4json\lib
File libqt4json\lib\libqt4json.a

WriteUninstaller $INSTDIR\uninstall.exe

SectionEnd

Section "Uninstall"

Delete $INSTDIR\libgcc_s_dw2-1.dll
Delete $INSTDIR\libqt4json.dll
Delete $INSTDIR\mingwm10.dll
Delete $INSTDIR\QtCore4.dll
Delete $INSTDIR\example.exe
Delete $INSTDIR\libqt4json\include\libqt4json.h
Delete $INSTDIR\libqt4json\lib\libqt4json.a
Delete $INSTDIR\uninstall.exe

RMDir $INSTDIR\libqt4json\include
RMDir $INSTDIR\libqt4json\lib
RMDir $INSTDIR\libqt4json
RMDir $INSTDIR

SectionEnd
