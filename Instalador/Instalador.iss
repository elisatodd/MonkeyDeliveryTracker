; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "MonkeyDelivery"
#define MyAppVersion "1.4.1"
#define MyAppPublisher "MonkeyDelivery"
#define MyAppURL "https://miggon23.github.io/MonkeyDelivery/"
#define MyAppExeName "MonkeyDelivery.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".myp"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{1E09AA88-1FCA-4FBE-B114-56F7BB456E6C}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputBaseFilename=MonketDeliverySetUp
SetupIconFile=..\MonkeyDelivery\MonkeyDelivery.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "espanol"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\MonkeyDelivery\x64\Release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libFLAC-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libfreetype-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libjpeg-9.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libmodplug-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libmpg123-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libogg-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libopus-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libopusfile-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libtiff-5.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libvorbis-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libvorbisfile-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\libwebp-7.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\SDL2_image.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\SDL2_mixer.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\SDL2_ttf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\tmxlite.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\tmxlite-d.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\MonkeyDelivery.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\MonkeyDelivery\Images\*"; DestDir: "{app}\Images"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\MonkeyDelivery\Sounds\*"; DestDir: "{app}\Sounds"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\MonkeyDelivery\Src\TilemapSrc\*"; DestDir: "{app}\Src\TilemapSrc"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename:"{app}\MonkeyDelivery.ico"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
[Dirs]
Name: "{app}\Images"
Name: "{app}\Sounds"
Name: "{app}\Src\TilemapSrc"