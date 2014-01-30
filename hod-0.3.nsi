; Script generated with the Venis Install Wizard

; Define your application name
!define APPNAME "HOTD"
!define APPNAMEANDVERSION "HOTD 0.3.0"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "$PROGRAMFILES\HOTD"
InstallDirRegKey HKLM "Software\${APPNAME}" ""
OutFile "HOTDSetup-0.3.0.exe"

; Use compression
SetCompressor BZip2

; Modern interface settings
!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN "$INSTDIR\hotd.exe"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gpl.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Set languages (first is default language)
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL

Section "HOD" Section1

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File "hotd.exe"
	File "hadith.db"
	CreateShortCut "$DESKTOP\HOD.lnk" "$INSTDIR\hotd.exe"
	CreateDirectory "$SMPROGRAMS\HOTD"
	CreateShortCut "$SMPROGRAMS\HOD\HOD.lnk" "$INSTDIR\hotd.exe"
	CreateShortCut "$SMPROGRAMS\HOD\Uninstall.lnk" "$INSTDIR\uninstall.exe"

SectionEnd

Section -FinishSection

	WriteRegStr HKLM "Software\${APPNAME}" "" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$INSTDIR\uninstall.exe"
	WriteUninstaller "$INSTDIR\uninstall.exe"

SectionEnd

; Modern install component descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${Section1} ""
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstall section
Section Uninstall

	;Remove from registry...
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
	DeleteRegKey HKLM "SOFTWARE\${APPNAME}"
	DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Run\${APPNAME} "
	; Delete self
	Delete "$INSTDIR\uninstall.exe"

	; Delete Shortcuts
	Delete "$DESKTOP\HOTD.lnk"
	Delete "$SMPROGRAMS\HOTD\HOTD.lnk"
	Delete "$SMPROGRAMS\HOTD\Uninstall.lnk"

	; Clean up HOD
	Delete "$INSTDIR\hotd.exe"
	Delete "$INSTDIR\hadith.db"

	; Remove remaining directories
	RMDir "$SMPROGRAMS\HOTD"
	RMDir "$INSTDIR\"

SectionEnd

BrandingText "DataDefinitionsInterlinks Limited"

; eof