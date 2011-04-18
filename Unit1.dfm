object Form1: TForm1
  Left = 240
  Top = 152
  Width = 886
  Height = 706
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 666
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Default'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 16
  object Splitter1: TSplitter
    Left = 0
    Top = 263
    Width = 878
    Height = 4
    Cursor = crVSplit
    Align = alTop
    AutoSnap = False
    Color = clBackground
    MinSize = 88
    ParentColor = False
    ResizeStyle = rsLine
    OnMoved = Splitter1Moved
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 878
    Height = 263
    ActivePage = TABSHEET_SERVERINFO
    Align = alTop
    Constraints.MinHeight = 263
    TabIndex = 0
    TabOrder = 0
    object TABSHEET_SERVERINFO: TTabSheet
      Caption = 'Server info'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 870
        Height = 232
        Align = alClient
        BevelOuter = bvNone
        Constraints.MinHeight = 231
        TabOrder = 0
        object StringGrid2: TStringGrid
          Left = 390
          Top = 0
          Width = 480
          Height = 232
          Align = alRight
          ColCount = 4
          DefaultColWidth = 50
          DefaultRowHeight = 18
          FixedCols = 0
          RowCount = 50
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
          ParentFont = False
          ScrollBars = ssVertical
          TabOrder = 0
          OnMouseDown = StringGrid2MouseDown
          OnMouseUp = StringGrid2MouseUp
          ColWidths = (
            100
            38
            43
            75)
        end
        object GROUPBOX_FILTERS: TGroupBox
          Left = 1
          Top = 85
          Width = 368
          Height = 146
          Align = alCustom
          Caption = '  Filters  '
          TabOrder = 1
          object LABEL_FILTER_MISSIONNAME: TLabel
            Left = 245
            Top = 52
            Width = 86
            Height = 16
            Caption = 'Mission name:'
          end
          object LABEL_FILTER_SERVERNAME: TLabel
            Left = 245
            Top = 12
            Width = 80
            Height = 16
            Caption = 'Server name:'
          end
          object LABEL_FILTER_PASSWORD: TLabel
            Left = 152
            Top = 14
            Width = 63
            Height = 16
            Caption = 'Password:'
          end
          object LABEL_FILTER_MINIMUMPLAYERS: TLabel
            Left = 152
            Top = 72
            Width = 76
            Height = 16
            Caption = 'min. Players:'
          end
          object LABEL_FILTER_PLAYERNAME: TLabel
            Left = 245
            Top = 92
            Width = 79
            Height = 16
            Caption = 'Player name:'
          end
          object LABEL_FILTER_STATUS: TLabel
            Left = 12
            Top = 14
            Width = 40
            Height = 16
            Caption = 'Status:'
          end
          object CHECKBOX_FILTER_PLAYING: TCheckBox
            Left = 12
            Top = 96
            Width = 133
            Height = 17
            Caption = 'Playing'
            Checked = True
            State = cbChecked
            TabOrder = 4
            OnClick = CHECKBOX_FILTER_PLAYINGClick
          end
          object CHECKBOX_FILTER_WAITING: TCheckBox
            Left = 12
            Top = 48
            Width = 133
            Height = 17
            Caption = 'Waiting'
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = CHECKBOX_FILTER_WAITINGClick
          end
          object CHECKBOX_FILTER_CREATING: TCheckBox
            Left = 12
            Top = 32
            Width = 133
            Height = 17
            Caption = 'Creating'
            Checked = True
            State = cbChecked
            TabOrder = 0
            OnClick = CHECKBOX_FILTER_CREATINGClick
          end
          object CHECKBOX_FILTER_BRIEFING: TCheckBox
            Left = 12
            Top = 80
            Width = 133
            Height = 17
            Caption = 'Briefing'
            Checked = True
            State = cbChecked
            TabOrder = 3
            OnClick = CHECKBOX_FILTER_BRIEFINGClick
          end
          object CHECKBOX_FILTER_DEBRIEFING: TCheckBox
            Left = 12
            Top = 112
            Width = 133
            Height = 17
            Caption = 'Debriefing'
            Checked = True
            State = cbChecked
            TabOrder = 5
            OnClick = CHECKBOX_FILTER_DEBRIEFINGClick
          end
          object Edit1: TEdit
            Left = 245
            Top = 68
            Width = 116
            Height = 24
            TabOrder = 11
            OnChange = Edit1Change
          end
          object Edit2: TEdit
            Left = 245
            Top = 28
            Width = 116
            Height = 24
            TabOrder = 10
            OnChange = Edit2Change
          end
          object CHECKBOX_FILTER_WITHPASSWORD: TCheckBox
            Left = 152
            Top = 32
            Width = 73
            Height = 17
            Caption = 'With'
            TabOrder = 6
            OnClick = CHECKBOX_FILTER_WITHPASSWORDClick
          end
          object CHECKBOX_FILTER_WITHOUTPASSWORD: TCheckBox
            Left = 152
            Top = 48
            Width = 65
            Height = 17
            Caption = 'Without'
            Checked = True
            State = cbChecked
            TabOrder = 7
            OnClick = CHECKBOX_FILTER_WITHOUTPASSWORDClick
          end
          object UpDown1: TUpDown
            Left = 209
            Top = 94
            Width = 15
            Height = 24
            Associate = Edit3
            Min = 0
            Position = 0
            TabOrder = 9
            Wrap = False
            OnClick = UpDown1Click
          end
          object Edit3: TEdit
            Left = 152
            Top = 94
            Width = 57
            Height = 24
            TabOrder = 8
            Text = '0'
            OnChange = Edit3Change
          end
          object Edit4: TEdit
            Left = 245
            Top = 108
            Width = 116
            Height = 24
            TabOrder = 12
            OnChange = Edit4Change
          end
          object CHECKBOX_FILTER_SETTINGUP: TCheckBox
            Left = 12
            Top = 64
            Width = 133
            Height = 17
            Caption = 'Setting up'
            Checked = True
            State = cbChecked
            TabOrder = 2
            OnClick = CHECKBOX_FILTER_SETTINGUPClick
          end
        end
        object GROUPBOX_SERVERINFO: TGroupBox
          Left = 3
          Top = 0
          Width = 366
          Height = 84
          Caption = '  Server Info  '
          Color = clBtnFace
          ParentColor = False
          TabOrder = 2
          object LABEL_SERVERINFO_IP: TLabel
            Left = 8
            Top = 32
            Width = 15
            Height = 16
            Caption = 'IP:'
            Transparent = True
          end
          object LABEL_SERVERINFO_IP_VALUE: TLabel
            Left = 40
            Top = 32
            Width = 48
            Height = 16
            Caption = '                '
            Transparent = True
          end
          object LABEL_SERVERINFO_PORT: TLabel
            Left = 144
            Top = 32
            Width = 27
            Height = 16
            Caption = 'Port:'
            Transparent = True
          end
          object LABEL_SERVERINFO_PORT_VALUE: TLabel
            Left = 184
            Top = 32
            Width = 24
            Height = 16
            Caption = '        '
            Transparent = True
          end
          object LABEL_SERVERINFO_PLATFORM: TLabel
            Left = 232
            Top = 32
            Width = 52
            Height = 16
            Caption = 'Platform:'
            Transparent = True
          end
          object LABEL_SERVERINFO_PLATFORM_VALUE: TLabel
            Left = 328
            Top = 32
            Width = 24
            Height = 16
            Caption = '        '
            Transparent = True
          end
          object LABEL_SERVERINFO_PASSWORD: TLabel
            Left = 232
            Top = 48
            Width = 63
            Height = 16
            Caption = 'Password:'
            Transparent = True
          end
          object LABEL_SERVERINFO_PASSWORD_VALUE: TLabel
            Left = 328
            Top = 48
            Width = 27
            Height = 16
            Hint = 'Ja'
            Caption = '         '
            ParentShowHint = False
            ShowHint = False
            Transparent = True
          end
          object LABEL_SERVERINFO_VERSION: TLabel
            Left = 232
            Top = 16
            Width = 49
            Height = 16
            Caption = 'Version:'
            Transparent = True
          end
          object LABEL_SERVERINFO_VERSION_VALUE: TLabel
            Left = 328
            Top = 16
            Width = 30
            Height = 16
            Caption = '          '
            Transparent = True
          end
          object LABEL_SERVERINFO_NAME: TLabel
            Left = 8
            Top = 16
            Width = 217
            Height = 16
            AutoSize = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object LABEL_SERVERINFO_EQMODREQ: TLabel
            Left = 232
            Top = 64
            Width = 73
            Height = 16
            Caption = 'EqModReq:'
          end
          object LABEL_SERVERINFO_EQMODREQ_VALUE: TLabel
            Left = 328
            Top = 64
            Width = 27
            Height = 16
            Caption = '         '
          end
          object BUTTON_SERVERINFO_COPYADDRESS: TButton
            Left = 16
            Top = 54
            Width = 193
            Height = 22
            Caption = 'Copy address to clipboard'
            Enabled = False
            TabOrder = 0
            OnClick = BUTTON_SERVERINFO_COPYADDRESSClick
          end
        end
      end
    end
    object TABSHEET_CHAT: TTabSheet
      Caption = 'Chat'
      ImageIndex = 1
      OnShow = TABSHEET_CHATShow
      object StringGrid3: TStringGrid
        Left = 649
        Top = 0
        Width = 221
        Height = 232
        Hint = 'ALT + LeftMouse mutes the user you click on'
        Align = alRight
        ColCount = 1
        DefaultColWidth = 200
        FixedCols = 0
        RowCount = 1
        FixedRows = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDrawCell = StringGrid3DrawCell
        OnMouseDown = StringGrid3MouseDown
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 649
        Height = 232
        Align = alClient
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Panel2'
        Constraints.MinHeight = 231
        TabOrder = 1
        object MemoChatOutput: TMemo
          Left = 0
          Top = 0
          Width = 649
          Height = 206
          Align = alClient
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
          OnChange = MemoChatOutputChange
        end
        object MemoChatInput: TMemo
          Left = 0
          Top = 206
          Width = 649
          Height = 26
          Align = alBottom
          Constraints.MaxHeight = 26
          Enabled = False
          TabOrder = 1
          OnChange = MemoChatInputChange
          OnKeyDown = MemoChatInputKeyDown
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 626
    Width = 878
    Height = 34
    BorderWidth = 1
    DragMode = dmAutomatic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Constraints.MinHeight = 34
    Panels = <
      item
        Text = 'Listed: '
        Width = 100
      end
      item
        Text = 'Online: '
        Width = 100
      end
      item
        Width = 90
      end
      item
        Width = 50
      end>
    ParentColor = True
    ParentShowHint = False
    ShowHint = False
    SimplePanel = False
    SizeGrip = False
    UseSystemFont = False
  end
  object StringGrid1: TStringGrid
    Left = 0
    Top = 267
    Width = 878
    Height = 359
    Align = alClient
    BiDiMode = bdRightToLeft
    ColCount = 7
    Constraints.MinHeight = 88
    Ctl3D = True
    DefaultColWidth = 101
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 20
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goRowSelect]
    ParentBiDiMode = False
    ParentCtl3D = False
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
    OnContextPopup = StringGrid1ContextPopup
    OnDrawCell = StringGrid1DrawCell
    OnMouseDown = StringGrid1MouseDown
    OnMouseUp = StringGrid1MouseUp
    OnSelectCell = StringGrid1SelectCell
    ColWidths = (
      29
      196
      53
      68
      58
      183
      41)
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 448
    Top = 160
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer3Timer
    Left = 416
    Top = 160
  end
  object PopupMenu1: TPopupMenu
    OnPopup = PopupMenu1Popup
    Left = 384
    Top = 160
    object MENUITEM_POPUP_JOIN: TMenuItem
      Caption = 'Join'
      Enabled = False
      object MENUITEM_POPUP_JOIN_NOMODS: TMenuItem
        Caption = 'No mods'
      end
      object MENUITEM_POPUP_JOIN_SAMEMODS: TMenuItem
        Caption = 'Same mods as server'
      end
      object N21: TMenuItem
        Caption = '2'
      end
      object N31: TMenuItem
        Caption = '3'
      end
      object N41: TMenuItem
        Caption = '4'
      end
      object N52: TMenuItem
        Caption = '5'
      end
      object N62: TMenuItem
        Caption = '6'
      end
      object N72: TMenuItem
        Caption = '7'
      end
      object N82: TMenuItem
        Caption = '8'
      end
      object N92: TMenuItem
        Caption = '9'
      end
    end
    object MENUITEM_POPUP_AUTOJOIN: TMenuItem
      Caption = 'Auto-Join'
      Enabled = False
      object MENUITEM_POPUP_AUTOJOIN_NOMODS: TMenuItem
        Caption = 'No mods'
      end
      object MENUITEM_POPUP_AUTOJOIN_SAMEMODS: TMenuItem
        Caption = 'Same mods as server'
      end
      object N23: TMenuItem
        Caption = '2'
      end
      object N33: TMenuItem
        Caption = '3'
      end
      object N43: TMenuItem
        Caption = '4'
      end
      object N53: TMenuItem
        Caption = '5'
      end
      object N63: TMenuItem
        Caption = '6'
      end
      object N73: TMenuItem
        Caption = '7'
      end
      object N83: TMenuItem
        Caption = '8'
      end
      object N93: TMenuItem
        Caption = '9'
      end
    end
    object MENUITEM_POPUP_AUTOJOINB: TMenuItem
      Caption = 'Auto-Join2'
      Enabled = False
      OnClick = MENUITEM_POPUP_AUTOJOINBClick
    end
    object MENUITEM_POPUP_MODS: TMenuItem
      Caption = 'Mods'
      object N02: TMenuItem
        Caption = '0'
      end
      object N12: TMenuItem
        Caption = '1'
      end
      object N22: TMenuItem
        Caption = '2'
      end
      object N32: TMenuItem
        Caption = '3'
      end
      object N42: TMenuItem
        Caption = '4'
      end
      object N51: TMenuItem
        Caption = '5'
      end
      object N61: TMenuItem
        Caption = '6'
      end
      object N71: TMenuItem
        Caption = '7'
      end
      object N81: TMenuItem
        Caption = '8'
      end
      object N91: TMenuItem
        Caption = '9'
      end
    end
    object MENUITEM_POPUP_WATCH: TMenuItem
      Caption = 'Watch'
    end
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 512
    Top = 160
    object MENUITEM_MAINMENU_EXIT: TMenuItem
      Caption = 'Exit'
      OnClick = MENUITEM_MAINMENU_EXITClick
    end
    object MENUITEM_MAINMENU_SETTINGS: TMenuItem
      Caption = 'Settings'
      OnClick = MENUITEM_MAINMENU_SETTINGSClick
    end
    object MENUITEM_MAINMENU_NOTIFICATIONS: TMenuItem
      Caption = 'Notifications'
      object MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE: TMenuItem
        Caption = 'Active'
        ShortCut = 113
        OnClick = MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVEClick
      end
      object MENUITEM_MAINMENU_NOTIFICATIONS_SETTINGS: TMenuItem
        Caption = 'Settings'
        OnClick = MENUITEM_MAINMENU_NOTIFICATIONS_SETTINGSClick
      end
    end
    object MENUITEM_MAINMENU_FONT: TMenuItem
      Caption = 'Font'
      OnClick = MENUITEM_MAINMENU_FONTClick
    end
    object MENUITEM_MAINMENU_GETNEWSERVERLIST: TMenuItem
      Caption = 'Get new Server list'
      ShortCut = 116
      OnClick = MENUITEM_MAINMENU_GETNEWSERVERLISTClick
    end
    object MENUITEM_MAINMENU_CHAT: TMenuItem
      Caption = 'Chat'
      object MENUITEM_MAINMENU_CHAT_CONNECT: TMenuItem
        Caption = 'Connect'
        OnClick = MENUITEM_MAINMENU_CHAT_CONNECTClick
      end
      object MENUITEM_MAINMENU_CHAT_DISCONNECT: TMenuItem
        Caption = 'Disconnect'
        Enabled = False
        OnClick = MENUITEM_MAINMENU_CHAT_DISCONNECTClick
      end
      object MENUITEM_MAINMENU_CHAT_AUTOCONNECT: TMenuItem
        AutoCheck = True
        Caption = 'Connect on start'
        OnClick = MENUITEM_MAINMENU_CHAT_AUTOCONNECTClick
      end
      object MENUITEM_MAINMENU_CHAT_LOG: TMenuItem
        Caption = 'Log'
        object MENUITEM_MAINMENU_CHAT_SAVETOFILE: TMenuItem
          Caption = 'Save to file'
          OnClick = MENUITEM_MAINMENU_CHAT_SAVETOFILEClick
        end
        object MENUITEM_MAINMENU_CHAT_CLEARLOG: TMenuItem
          Caption = 'Clear'
          OnClick = MENUITEM_MAINMENU_CHAT_CLEARLOGClick
        end
      end
    end
    object Info1: TMenuItem
      Caption = 'Info'
      OnClick = Info1Click
    end
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 8
    MaxFontSize = 20
    Options = [fdForceFontExist, fdLimitSize, fdApplyButton]
    OnApply = FontDialog1Apply
    Left = 576
    Top = 160
  end
  object MP3Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = MP3TimerTimer
    Left = 608
    Top = 160
  end
  object TimerIrcChatTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = TimerIrcChatTimerTimer
    Left = 352
    Top = 160
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text file (*.txt)|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofNoNetworkButton, ofEnableSizing]
    OnCanClose = SaveDialog1CanClose
    Left = 480
    Top = 160
  end
  object CoolTrayIcon1: TCoolTrayIcon
    CycleInterval = 0
    Icon.Data = {
      0000010001002020000001001800A80C00001600000028000000200000004000
      0000010018000000000000000000FC010000FC0100000000000000000000123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF12
      3FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF
      123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF12
      3FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF
      123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF113E
      FE113FFE113FFE113FFE113FFE113FFE113FFE113FFE113FFE113EFE113EFE11
      3EFE123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF113EFE
      113EFE113FFE113FFE113FFE113FFE113FFE113FFE113FFE113FFE113FFE1144
      FC1156F71364FD1966FE1A66FE1B66FE1B66FE1D68FE155DFC1146EF1141FB11
      3EFE113FFF113FFE113FFE113FFE113FFE113FFE113FFF113EFF113EFF113EFE
      1141FA1149EB115FF81665FE1865FF1763FF1465FE1869FE266DFF2360FE114D
      F73497CA3FBCC847C0D448C0D647C4D745C7DB42CDE43FBED81B69A2113FD411
      3FF31145EC114FEC1154F51155F81156F5114FEC1145E01139D41137DA113CED
      1145D314759E32C1D73DCCE53FCCE43FC8E43FCAE24BCCD975DADC72B7C91144
      FC1459DE1D7485249A9F249BA92399AC2298AE2097B21E92B01586A211537C11
      42A511648C208FA831A0BB3AA6C22EABC02093AB15768B16535D13335011409E
      11628C1896B627A3BE2BA6BF2CAABE2DACBE3EB9C36FC8C08DC6C83D7CFA113E
      FE1142F8114DC6187C812099A72094AE1E90B01D8DB11C8CB31991B113748411
      586A11778B1394B31B9AC11F9BB81C9DB8189FC11BA6C819AECB158B9E117086
      1295B5209EBE24A3BC24A3BA25A3BB3BB1C07DCDC882BCCC3A74FC1647FF113E
      FE113EFE1142E2145C741C91911F99AE1E93B21D95B41B95B61A94B7178FB311
      85AB158BB5148EBA148CBB148BB9148CB9158DBA1691BC199ABF1E96BE1F9DBC
      1FA2C021A2BE23A3BC26A2BC38B3C178C8BF97C9CF4077FD1645FE113EFE123F
      FF113EFE1140F81144CD1468801D9BA81D9EB51C97B61A95B71999B91797B916
      94BA1A90BE1992BF1D8EBE1A8DBF1889BE178ABD1790BC1C95C21D96C41E9FC3
      1FA1C221A1C1259FBD41AEC17FCDCF8DC0CD4178FD1948FF113EFE113EFE123F
      FF113EFE113EFE1142F91148C6127485189BB91A9EBA199BBA1898BB1D95C12D
      97BE409EC953A6CD68B1C95FB5D257A7CE3699CA2095C71C99C81C9ED11CA4D1
      1DA7CF1EA2CB33ACC27AC4C09DCCD54579FD1747FE113EFE113EFE123FFF123F
      FF123FFF113EFE113EFE113FE5114E73118390169FC51FA0C939A2C262BAD27C
      B3B8669FB06589967C848F8087989298A0618F9C2DACD21FAAD924AFDF26B1DE
      26B6DC25B7D73DC1D2548B9E3165F31B49FF113EFE113EFE123FFF123FFF123F
      FF123FFF123FFF113EFE1140FA1140C411677C20B3CF55C2D593C0B5839C9147
      8E992FB5D12991B62259CE1E46E4265FD22290AF33D2F43CD6F73CD4F63DD5F5
      3FDDF549E9FA56F4F43495A61248CE113FF7113EFE123FFF123FFF123FFF123F
      FF123FFF123FFF113EFE113EFE113CE614537F47BCC692C2B5728F8332838E3C
      D2E672F4FE58E5F71968A0114BB9157DB555E7F77BF4FF77EDFF70F4FF6AF6FE
      69F7FE8CFCFE8DFEF85DE6E81F5A81113CDF113EFF123FFF123FFF123FFF113E
      FE113EFE113EFE113EFE113EFE113EFC1240D63D658B5779782D849354DFEE89
      F5FE8CF7FF89F2FE37B4D01783A74CDCF88CFAFF92F6FF94F7FF95FDFD8EE1DD
      56CACF87FEFD9EFFF988F9F9337384113EDA113EFF123FFF123FFF123FFF113E
      FE1141FC1140F11141FB113EFE113EFE113DFC1339C2194D5D2DADBB8CF7FE96
      F7FF94F6FF9AF3FF75EDFE61E4FC92F3FF94F6FF97F8FF98FDFD92E1DD5F8C97
      247E914FE9EC9EFEFA9AFEF73E9DB31149E8113FFF123FFF123FFF123FFF113E
      FF1140E711498A113CCD113DFA113CFA1139E11137AF1141511B72855FE4F299
      F9FF97F8FF96F6FF9AF7FF98F6FF95F6FF9AF8FFA3FDFE98D7CE6A92B7204FE3
      114DC92F9AAE96FCFCA5FEF34CB8CC1253F3113FFE123FFF123FFF123FFF113E
      FF113CDB114F66114F6D1139B90F2CAE0C215C114E5E113A4611459C2391BF7A
      F6FD9CFAFF96F8FF95F6FF95F6FF96F6FFA0FBFE9EDAD46F87AE224CEE1140FB
      1145E6338AA483F9FBA6FFF54AC8DD1158F8113FFE123FFF123FFF123FFF113E
      FF1137D41246571C9FA71B5E6D16303E1A7172198D911334541139D1115ADD31
      BACF8FF8FE97F8FF94F7FF94F6FF8EF5FF6FCAD355758D1F46DD113FFB113EFE
      1145E84897AD91FBF4A7FFF248C9DC1159F7113FFE123FFF123FFF123FFF113E
      FE1135CF14363D28929339CDD13FBCC04CD8DE1E67681138B6113CF31143EA17
      67A24FD4EA97F7FF96F8FF94F8FF8EF4FF44BCD91B4E77113ADA113EFE113EFE
      113AD825566C60E1D899FFEF38BDC81156F0113FFE123FFF123FFF123FFF1140
      FA113ABB12434922898C56DADD79DCDB4ED9E51E6872113EB6113DE5113FEC11
      47DA2084B771E8FC92F7FF8FF7FF92F8FF72EAFD1D7AA5113EC8113EF6113EFE
      1134CC15344A40D0D189FEF42AA4AF114EE6113FFF123FFF123FFF123FFF124C
      CC195C762D90865EDCD678EEE656CDD07BF8FD49D8E427768C1B4D83113FD711
      40EF1153D826A4C575EDFE8DF8FF92FAFF89F7FF44D2F2145691113EE6113EFE
      1137CF15475E47E8EE6DFBFE1E90B21147E7113FFE123FFF123FFF123FFF3A71
      6A53947382B98E85C1A352CCC732B2BF6ED1CD81C4B875B1AA4F8A822C558B11
      3FE91142E8145C9443C1DA9FF0F994EEF385F6FE76F2FE338FB51143E71143F9
      1152D0158CA763F7FE35E1E9126EE51143F9113EFE123FFF123FFF123FFF4962
      583357512C404F26394D1B6F641DC0CF206061263749253B5B3D5A6A264C8211
      3EE81140F71142DC3766A968879C466A803999B962C8DF4879B61141E71153DE
      1198BD32E7F864F8FD2099B9114CEC113FFE113EFE123FFF123FFF123FFF1340
      E0113CD71137CD102EA311445517B0BA0B3F7D0C27BB0F33D4113DDC113FE811
      40F8113EFE113FFA1141F11541EB113EE11148EC1654FB1346ED1148CE117199
      1BD8E168FAFE52BEBF175FDC1143F9113EFE123FFF123FFF123FFF123FFF113E
      FF113EFF113EFF113ADD14395D157780114ACD113FF7113EFE1143F9114BEC11
      55F01156F81146FD113FFE113FFE1143FB114AF2114FEC1151D6116B9818B3C0
      4BF5FD69CDC5335376113BDF113EFE113EFE123FFF123FFF123FFF123FFF123F
      FF123FFF113EFE113DF61141CE145FA01145EA113EFE113EFE1146E71B75972A
      98A42BAFD21D7EFD1360FD115BF81166EA278FC21CA4C71A9CB323C6E157EBF8
      57BEB42D5079102FC7113CF5113EFE123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF113EFE113EFE1141F91142F01141F9113EFE113EFF113FDF16445F32
      594856AA9C53D6DF3DBDD839BCD72EC0D530D6EC2FE6F94EEDF760D9D84F8A90
      213D710D2BC5113CF6113EFE113EFE123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF113EFE113EFE113EFF113EFE113EFE113EFE113EF6113BDC13
      36B2213D503D666B619BB173D0E378E6ED74D0E060A6BD3D788E233F7A183FC4
      0F35DD113CF5113EFE113EFE123FFF123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF113EFE113EFE113EFE11
      3CF51136D7123CDB1A50F82E6AFF3774FF2B69FF1951F91240E21037DC113CF6
      113EFE113EFE113EFE123FFF123FFF123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF113EFE11
      3EFE113EFF113EFF113EFE123FFE123FFF123FFE113EFE113EFE113EFF113EFE
      113EFE123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF12
      3FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF
      123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123F
      FF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF12
      3FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF
      123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF123FFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000}
    IconVisible = True
    IconIndex = 0
    OnClick = CoolTrayIcon1Click
    Left = 544
    Top = 160
  end
end
