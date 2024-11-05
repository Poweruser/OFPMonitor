object WINDOW_MAIN: TWINDOW_MAIN
  Left = 731
  Top = 245
  Width = 666
  Height = 500
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 666
  DefaultMonitor = dmDesktop
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Default'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnConstrainedResize = FormConstrainedResize
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Splitter1: TSplitter
    Left = 0
    Top = 303
    Width = 658
    Height = 3
    Cursor = crVSplit
    Align = alTop
    AutoSnap = False
    Color = clBlack
    MinSize = 88
    ParentColor = False
    ResizeStyle = rsLine
    OnMoved = Splitter1Moved
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 658
    Height = 303
    ActivePage = TABSHEET_SERVERINFO
    Align = alTop
    Constraints.MinHeight = 271
    Images = ImageListTabIcons
    OwnerDraw = True
    TabIndex = 0
    TabOrder = 0
    OnDrawTab = PageControl1DrawTab
    object TABSHEET_SERVERINFO: TTabSheet
      Caption = 'Server info'
      ImageIndex = 3
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 650
        Height = 272
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object StringGrid2: TStringGrid
          Left = 368
          Top = 0
          Width = 282
          Height = 272
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
          Left = 3
          Top = 85
          Width = 366
          Height = 155
          Align = alCustom
          Caption = '  Filters  '
          TabOrder = 1
          object LABEL_FILTER_MISSIONNAME: TLabel
            Left = 245
            Top = 59
            Width = 86
            Height = 16
            Caption = 'Mission name:'
            Transparent = True
          end
          object LABEL_FILTER_SERVERNAME: TLabel
            Left = 245
            Top = 13
            Width = 80
            Height = 16
            Caption = 'Server name:'
            Transparent = True
          end
          object LABEL_FILTER_PASSWORD: TLabel
            Left = 152
            Top = 22
            Width = 63
            Height = 16
            Caption = 'Password:'
            Transparent = True
          end
          object LABEL_FILTER_MINIMUMPLAYERS: TLabel
            Left = 152
            Top = 86
            Width = 76
            Height = 16
            Caption = 'min. Players:'
            Transparent = True
          end
          object LABEL_FILTER_PLAYERNAME: TLabel
            Left = 245
            Top = 105
            Width = 79
            Height = 16
            Caption = 'Player name:'
            Transparent = True
          end
          object LABEL_FILTER_STATUS: TLabel
            Left = 12
            Top = 22
            Width = 40
            Height = 16
            Caption = 'Status:'
            Transparent = True
          end
          object CHECKBOX_FILTER_PLAYING: TCheckBox
            Left = 12
            Top = 112
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
            Top = 64
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
            Top = 48
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
            Top = 96
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
            Top = 128
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
            Top = 78
            Width = 116
            Height = 24
            TabOrder = 11
            OnChange = Edit1Change
          end
          object Edit2: TEdit
            Left = 245
            Top = 32
            Width = 116
            Height = 24
            TabOrder = 10
            OnChange = Edit2Change
          end
          object CHECKBOX_FILTER_WITHPASSWORD: TCheckBox
            Left = 152
            Top = 48
            Width = 73
            Height = 17
            Caption = 'With'
            TabOrder = 6
            OnClick = CHECKBOX_FILTER_WITHPASSWORDClick
          end
          object CHECKBOX_FILTER_WITHOUTPASSWORD: TCheckBox
            Left = 152
            Top = 64
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
            Top = 112
            Width = 15
            Height = 24
            Associate = Edit3
            Min = 0
            Position = 0
            TabOrder = 9
            Wrap = False
            OnChangingEx = UpDown1ChangingEx
          end
          object Edit3: TEdit
            Left = 152
            Top = 112
            Width = 57
            Height = 24
            ReadOnly = True
            TabOrder = 8
            Text = '0'
          end
          object Edit4: TEdit
            Left = 245
            Top = 124
            Width = 116
            Height = 24
            TabOrder = 12
            OnChange = Edit4Change
          end
          object CHECKBOX_FILTER_SETTINGUP: TCheckBox
            Left = 12
            Top = 80
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
            Left = 304
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
            Transparent = True
          end
          object LABEL_SERVERINFO_EQMODREQ_VALUE: TLabel
            Left = 328
            Top = 64
            Width = 27
            Height = 16
            Caption = '         '
            Transparent = True
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
    object TABSHEET_GAMECONTROL: TTabSheet
      Caption = 'Automation'
      OnShow = TABSHEET_GAMECONTROLShow
      object GROUPBOX_GAMECONTROL_PROCESS: TGroupBox
        Left = 3
        Top = 0
        Width = 644
        Height = 100
        Caption = 'Game process and Server '
        TabOrder = 0
        object LABEL_GAMECONTROL_PROCESS: TLabel
          Left = 16
          Top = 24
          Width = 92
          Height = 16
          Caption = 'Game process:'
        end
        object LABEL_GAMECONTROL_SERVER: TLabel
          Left = 16
          Top = 52
          Width = 43
          Height = 16
          Caption = 'Server:'
        end
        object Label9: TLabel
          Left = 136
          Top = 78
          Width = 3
          Height = 16
        end
        object LABEL_GAMECONTROL_EXE: TLabel
          Left = 16
          Top = 78
          Width = 70
          Height = 16
          Caption = 'Executable:'
        end
        object ComboBox1: TComboBox
          Left = 128
          Top = 20
          Width = 329
          Height = 24
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 0
          OnChange = ComboBox1Change
        end
        object ComboBox2: TComboBox
          Left = 128
          Top = 49
          Width = 329
          Height = 24
          Style = csDropDownList
          ItemHeight = 0
          Sorted = True
          TabOrder = 1
          OnChange = ComboBox2Change
        end
        object CHECKBOX_GAMECONTROL_AUTODETECT: TCheckBox
          Left = 464
          Top = 18
          Width = 177
          Height = 17
          Caption = 'Automatic detection'
          TabOrder = 2
          OnClick = CHECKBOX_GAMECONTROL_AUTODETECTClick
        end
        object BUTTON_GAMECONTROL_REFRESH: TButton
          Left = 464
          Top = 36
          Width = 169
          Height = 37
          Caption = 'Refresh Lists'
          TabOrder = 3
          OnClick = BUTTON_GAMECONTROL_REFRESHClick
        end
      end
      object GROUPBOX_GAMECONTROL_AUTOGREENUP: TGroupBox
        Left = 3
        Top = 104
        Width = 318
        Height = 85
        TabOrder = 1
        object LABEL_GAMECONTROL_AUTOGREENUP_DELAY: TLabel
          Left = 16
          Top = 30
          Width = 102
          Height = 16
          Caption = 'Delay (seconds):'
        end
        object RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE: TRadioButton
          Left = 16
          Top = 48
          Width = 113
          Height = 17
          Caption = 'Only once'
          TabOrder = 0
          OnClick = RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCEClick
        end
        object RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT: TRadioButton
          Left = 16
          Top = 64
          Width = 169
          Height = 17
          Caption = 'Repeat until game start'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEATClick
        end
        object Edit5: TEdit
          Left = 216
          Top = 28
          Width = 33
          Height = 24
          ReadOnly = True
          TabOrder = 2
          Text = '10'
        end
        object UpDown2: TUpDown
          Left = 249
          Top = 28
          Width = 16
          Height = 24
          Associate = Edit5
          Min = 10
          Max = 360
          Increment = 5
          Position = 10
          TabOrder = 3
          Thousands = False
          Wrap = False
          OnChangingEx = UpDown2ChangingEx
        end
        object CHECKBOX_GAMECONTROL_AUTOGREENUP: TCheckBox
          Left = 4
          Top = 10
          Width = 301
          Height = 17
          Caption = 'Automatic confirmation in briefing'
          TabOrder = 4
          OnClick = CHECKBOX_GAMECONTROL_AUTOGREENUPClick
        end
      end
      object GROUPBOX_GAMECONTROL_RESTORE: TGroupBox
        Left = 326
        Top = 104
        Width = 323
        Height = 85
        BiDiMode = bdLeftToRight
        ParentBiDiMode = False
        TabOrder = 2
        object CHECKBOX_GAMECONTROL_RESTORE_CREATING: TCheckBox
          Left = 16
          Top = 30
          Width = 169
          Height = 17
          Caption = 'Creating'
          TabOrder = 0
          OnClick = CHECKBOX_GAMECONTROL_RESTORE_CREATINGClick
        end
        object CHECKBOX_GAMECONTROL_RESTORE_WAITING: TCheckBox
          Left = 16
          Top = 46
          Width = 169
          Height = 17
          Caption = 'Waiting'
          TabOrder = 1
          OnClick = CHECKBOX_GAMECONTROL_RESTORE_WAITINGClick
        end
        object CHECKBOX_GAMECONTROL_RESTORE_BRIEFING: TCheckBox
          Left = 16
          Top = 62
          Width = 169
          Height = 17
          Caption = 'Briefing'
          TabOrder = 2
          OnClick = CHECKBOX_GAMECONTROL_RESTORE_BRIEFINGClick
        end
        object CHECKBOX_GAMECONTROL_RESTORE_PLAYING: TCheckBox
          Left = 160
          Top = 46
          Width = 161
          Height = 17
          Caption = 'Playing'
          TabOrder = 3
          OnClick = CHECKBOX_GAMECONTROL_RESTORE_PLAYINGClick
        end
        object CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING: TCheckBox
          Left = 160
          Top = 62
          Width = 161
          Height = 17
          Caption = 'Debriefing'
          TabOrder = 4
          OnClick = CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFINGClick
        end
        object CHECKBOX_GAMECONTROL_RESTORE: TCheckBox
          Left = 4
          Top = 10
          Width = 309
          Height = 17
          Caption = 'Restore game on'
          TabOrder = 5
          OnClick = CHECKBOX_GAMECONTROL_RESTOREClick
        end
      end
      object GROUPBOX_OVERWRITE_MASTERSERVER: TGroupBox
        Left = 3
        Top = 189
        Width = 646
        Height = 51
        TabOrder = 3
        object CHECKBOX_GAMECONTROL_OVERWRITE_MASTERSERVER: TCheckBox
          Left = 4
          Top = 10
          Width = 317
          Height = 17
          Caption = 'Overwrite master server address'
          TabOrder = 0
          OnClick = CHECKBOX_GAMECONTROL_OVERWRITE_MASTERSERVERClick
        end
        object COMBOBOX_OVERWRITE_MASTERSERVER: TComboBox
          Left = 328
          Top = 16
          Width = 305
          Height = 24
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 1
          OnChange = COMBOBOX_OVERWRITE_MASTERSERVERChange
        end
      end
    end
    object TABSHEET_CHAT: TTabSheet
      Caption = 'Chat'
      ImageIndex = 2
      OnShow = TABSHEET_CHATShow
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 490
        Height = 272
        Align = alClient
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Constraints.MinHeight = 231
        TabOrder = 0
        object TabControl1: TTabControl
          Left = 0
          Top = 0
          Width = 490
          Height = 272
          Align = alClient
          MultiLine = True
          OwnerDraw = True
          TabOrder = 0
          OnChange = TabControl1Change
          OnChanging = TabControl1Changing
          OnContextPopup = TabControl1ContextPopup
          OnDrawTab = TabControl1DrawTab
          object MemoChatInput: TMemo
            Left = 4
            Top = 242
            Width = 482
            Height = 26
            Align = alBottom
            Constraints.MaxHeight = 26
            Enabled = False
            MaxLength = 450
            TabOrder = 0
            WantReturns = False
            OnKeyDown = MemoChatInputKeyDown
          end
          object MemoChatOutput: TMemo
            Left = 4
            Top = 6
            Width = 482
            Height = 236
            Align = alClient
            ReadOnly = True
            ScrollBars = ssVertical
            TabOrder = 1
          end
        end
      end
      object StringGrid3: TStringGrid
        Left = 490
        Top = 0
        Width = 160
        Height = 272
        Hint = 'ALT + LeftMouse mutes the user you click on'
        Align = alRight
        ColCount = 1
        Constraints.MaxWidth = 160
        Constraints.MinWidth = 160
        DefaultColWidth = 140
        FixedCols = 0
        RowCount = 1
        FixedRows = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
        PopupMenu = PopupMenuChat
        ScrollBars = ssVertical
        TabOrder = 1
        OnContextPopup = StringGrid3ContextPopup
        OnDrawCell = StringGrid3DrawCell
        OnMouseDown = StringGrid3MouseDown
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 412
    Width = 658
    Height = 34
    BorderWidth = 1
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
        Style = psOwnerDraw
        Text = 'Volume'
        Width = 32
      end
      item
        Style = psOwnerDraw
        Text = 'Notifications'
        Width = 32
      end
      item
        Style = psOwnerDraw
        Text = 'Bandwidth'
        Width = 32
      end
      item
        Style = psOwnerDraw
        Text = 'Always on top'
        Width = 32
      end
      item
        Bevel = pbNone
        Width = 50
      end>
    ParentColor = True
    ParentShowHint = False
    ShowHint = False
    SimplePanel = False
    SizeGrip = False
    UseSystemFont = False
    OnMouseDown = StatusBar1MouseDown
    OnDrawPanel = StatusBar1DrawPanel
  end
  object StringGrid1: TStringGrid
    Tag = -1
    Left = 0
    Top = 306
    Width = 658
    Height = 106
    Align = alClient
    BiDiMode = bdRightToLeft
    ColCount = 7
    Constraints.MinHeight = 88
    Ctl3D = True
    DefaultColWidth = 101
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 40
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
    OnTimer = Timer1Timer
    Left = 536
    Top = 192
  end
  object PopupMenu1: TPopupMenu
    OnPopup = PopupMenu1Popup
    Left = 504
    Top = 224
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
      OnClick = ClickWatchButton
    end
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 568
    Top = 224
    object MENUITEM_MAINMENU_EXIT: TMenuItem
      Caption = 'Exit'
      OnClick = MENUITEM_MAINMENU_EXITClick
    end
    object MENUITEM_MAINMENU_SETTINGS: TMenuItem
      Caption = 'Settings'
      OnClick = MENUITEM_MAINMENU_SETTINGSClick
    end
    object MENUITEM_MAINMENU_LOCALGAME: TMenuItem
      Caption = 'Local game'
      OnClick = MENUITEM_MAINMENU_LOCALGAMEClick
    end
    object MENUITEM_MAINMENU_SERVERLIST: TMenuItem
      Caption = 'Server list'
      object MENUITEM_MAINMENU_GETNEWSERVERLIST: TMenuItem
        Caption = 'Get new Server list '
        ShortCut = 116
        OnClick = MENUITEM_MAINMENU_GETNEWSERVERLISTClick
      end
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
    end
    object MENUITEM_MAINMENU_FONT: TMenuItem
      Caption = 'Font'
      OnClick = MENUITEM_MAINMENU_FONTClick
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
    Left = 600
    Top = 192
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
    Left = 600
    Top = 224
  end
  object PopupMenuChat: TPopupMenu
    Left = 536
    Top = 160
    object Openchat1: TMenuItem
      Caption = 'Chat with...'
      OnClick = Openchat1Click
    end
  end
  object PopupMenuChat2: TPopupMenu
    Left = 568
    Top = 160
    object Close1: TMenuItem
      Caption = 'Close'
      OnClick = Close1Click
    end
  end
  object ImageListTabIcons: TImageList
    Left = 504
    Top = 256
    Bitmap = {
      494C010105000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3604
      000000000000360400002800000040000000300000000100080000000000000C
      0000000000000000000000000000000000000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      80008000000080008000F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000F0F0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000F0F0F0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000F0F0F0F0F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000F0F0F0F0F0F0F0F0F0F0F0F
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000F0F0F0F0F0F0F0F0F0F0F0F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F000000000000000000000000
      0F0F000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000F0F0F0F0F0F0F0F0F0F0F0F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000F0F0F0F0F0F0F0F0F0F0F0F
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000C0C0C0C0C0C000000
      000000000000000202020202020000000000000000000C0C0000000000000000
      0000000C0606060606060606060606060C000000000B0B0B0B0B0B0C0C0C0C00
      0000000000020202020202020202020000000000000C0C0C0000000000000000
      00000B06060606060606060606060606060B00000B0B0B0B0B0B0B0B0B0C0C0C
      00000000020202020202020202020202000000000C0C0C0C0C00000000000000
      000006060606060606060606060606060606000B0B0B0B0B0B0B0B0B0B0B0C0C
      0C000002020202020202020202020202020000000C0C0C0C0C0C0C0C0C0C0C0C
      00000606060606060A131309060606060606000B0B0B0B0B0B0B0B0B0B0B0B0C
      0C0000020202020202020202020202020200000C0C0C0C0C0C0C0C0C0C0C0C0C
      0C000606060606060C1313060606060606060B0B0B07070707070B0B0B0B0B0C
      0C0C0202020E0E0E0E0E02020202020202020C0C000000000000000000000000
      0C0C0606060606060B1313060606060606060B0B070707070707070B0B0B0B0B
      0C0C02020E0E0E0C0E0E0E020202020202020C0C000000000000000000000000
      0C0C0606060606060B1313060606060606060B0707070808080707070B0B0B0B
      0C0C020E0E0C0C0C0C0C0E0E0202020202020C0C000000000000000000000000
      0C0C060606060606091313060606060606060B0707080A0A0A0807070B0B0B0B
      0C0C020E0E0C0C0C0C0C0E0E0202020202020C0C000000000000000000000000
      0C0C060606060606091313060606060606060B0707080A0A0A0807070B0B0B0B
      0C0C020E0C0C0C0B0C0C0C0E0202020202020C0C000000000000000000000000
      0C0C060C060606061313130C060606060C060B0707080A0A0A0807070B0B0B0B
      0C0C020E0E0C0C0C0C0C0E0E0202020202020C0C000000000000000000000000
      0C0C060B0C0C0C0C0C0C0C0C0C0C0C0C0B06000707070808080707070B0B0B0B
      0C00000E0E0C0C0C0C0C0E0E0202020202000C0C000000000000000000000000
      0C0C060B0B0B0B0B0B130A0B0B0B0B0B0B06000B070707070707070B0B0B0B0B
      0C0000020E0E0E0C0E0E0E020202020202000C0C000000000000000000000000
      0C0C060B0B0B0B0B0B130A0B0B0B0B0B0B0600000B07070707070B0B0B0B0B0C
      00000000020E0E0E0E0E02020202020200000C0C000000000000000000000000
      0C0C060B0B0B0B0B0B0B0B0B0B0B0B0B0B060000000B0B0B0B0B0B0B0B0B0B00
      000000000002020202020202020202000000000C0C0C0C0C0C0C0C0C0C0C0C0C
      0C0009060B0B0B0B0B0B0B0B0B0B0B0B060900000000000B0B0B0B0B0B000000
      00000000000000020202020202000000000000000C0C0C0C0C0C0C0C0C0C0C0C
      00000009060B0B0B0B0B0B0B0B0B0B060900424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000F3FF000000000000E3FF000000000000
      C1FF000000000000C00300000000000080010000000000003FFC000000000000
      3FFC000000000000300C0000000000003FFC000000000000300C000000000000
      3FFC000000000000300C0000000000003FFC0000000000003FFC000000000000
      8001000000000000C003000000000000F81FF81FF3FF8001E007E007E3FF0000
      C003C003C1FF000080018001C00300008001800180010000000000003FFC0000
      000000003FFC000000000000300C0000000000003FFC000000000000300C0000
      000000003FFC000080018001300C0000800180013FFC0000C003C0033FFC0000
      E007E00780010000F81FF81FC003800100000000000000000000000000000000
      000000000000}
  end
  object ImageListVolume: TImageList
    DrawingStyle = dsTransparent
    Height = 24
    Width = 24
    Left = 384
    Top = 224
    Bitmap = {
      494C010104000900040018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3604
      000000000000360400002800000060000000480000000100080000000000001B
      0000000000000000000000000000000000000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      80008000000080008000F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000B0C0C0C000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000C06060C0C0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000C0606060C00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000B06060C0C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000C060C00000000000000000000000000
      00000000000000000C060C00000B06060C0000000000000000000C0C00000000
      0000000000000000000000000000000000000C0C000000000000000000000000
      000000000000000000000C0C000000000C060606000000000000000000000000
      00000C0C000000000C06060600000C06060C000000000000000C060C00000000
      00000000000000000000000000000000000C060C000000000000000000000000
      0000000000000000000C060C00000000000B06060C0000000000000000000000
      000C060C00000000000B06060C000B06060C0000000000000C06060C00000000
      000000000000000000000000000000000C06060C000000000000000000000000
      00000000000000000C06060C0000000000000B06060C00000000000000000000
      0C06060C0000000000000B06060C000C06060C0C0C0C0C060606060C00000000
      000000000000000000000C0C0C0C0C060606060C00000B0C0700000000000000
      00000C0C0C0C0C060606060C00000B0C0C000006060C000000000C0C0C0C0C06
      0606060C00000B0C0C000006060C000B06060606060606060606060C00000000
      000000000000000000000606060606060606060C00000C06060B000000000000
      00000606060606060606060C00000C06060C000B060600000000060606060606
      0606060C00000C06060C000B0606000006060606060606060606060C00000000
      000000000000000000000606060606060606060C0000000C060C000000000000
      00000606060606060606060C0000080C060C0000060600000000060606060606
      0606060C0000000C060C00000606000006060606060606060606060C00000000
      000000000000000000000606060606060606060C000000090606000000000000
      00000606060606060606060C0000000906060000060600000000060606060606
      0606060C0000000906060000060600000C060606060606060606060C00000000
      000000000000000000000606060606060606060C000000070606000000000000
      00000606060606060606060C0000000706060000060600000000060606060606
      0606060C0000000706060000060600000C060606060606060606060C00000000
      000000000000000000000606060606060606060C0000000C060C000000000000
      00000606060606060606060C0000080C060C0000060600000000060606060606
      0606060C0000000C060C0000060600000C060606060606060606060C00000000
      000000000000000000000606060606060606060C00000B060607000000000000
      00000606060606060606060C00000B060600000B060600000000060606060606
      0606060C00000B060607000B0606000006060000000000060606060C00000000
      000000000000000000000909090909060606060C00000B0C0900000000000000
      00000909090909060606060C00000B0C00000006060C00000000090909090906
      0606060C00000B0C09000006060C000706060000000000000606060C00000000
      000000000000000000000000000000090606060C000000000000000000000000
      00000000000000090606060C0000000000000C06060000000000000000000009
      0606060C0000000000000C060607000C060C0000000000000006060C00000000
      000000000000000000000000000000000806060C000000000000000000000000
      00000000000000000806060C00000000000C06060B0000000000000000000000
      0806060C00000000000C06060B000006060B00000000000000000C0700000000
      0000000000000000000000000000000000080C07000000000000000000000000
      000000000000000000080C07000000000B06060C000000000000000000000000
      00080C07000000000B06060C00000C060C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000C060B00000000000000000000000000
      00000000000000000C060B00000B060607000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000C06060B00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000C06060C0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000C06060B000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000B0C070000000000424D3E000000000000003E000000
      2800000060000000480000000100010000000000600300000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFF
      FFFFFFFFFFFFFF07FFFFFFFFFFFFFFFFFFFFFF83FFFFFFFFFFFFFFFFFFFFFFC1
      FFFFFFFFFFFFFFFC7FFFFC61FF3FFFFF3FFFFF3C3FFF3C30FE3FFFFE3FFFFE3E
      1FFE3E10FC3FFFFC3FFFFC3F0FFC3F08003FFF0031FF00318F003188003FFF00
      30FF00308F00308C003FFF0038FF0030CF0038CC003FFF0038FF0038CF0038CC
      003FFF0038FF0038CF0038CC003FFF0038FF0030CF0038CC003FFF0030FF0031
      8F00308CF83FFF0031FF00338F003188FC3FFFF83FFFF83F1FF83F08FE3FFFFC
      3FFFFC3E1FFC3E18FF3FFFFE3FFFFE3C3FFE3C31FFFFFFFFFFFFFFFC7FFFFC61
      FFFFFFFFFFFFFFFFFFFFFFC3FFFFFFFFFFFFFFFFFFFFFF87FFFFFFFFFFFFFFFF
      FFFFFF0FFFFFFFFFFFFFFFFFFFFFFF1F00000000000000000000000000000000
      000000000000}
  end
  object ImageListNotification: TImageList
    DrawingStyle = dsTransparent
    Height = 24
    Width = 24
    Left = 384
    Top = 256
    Bitmap = {
      494C010102000400040018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3604
      0000000000003604000028000000600000001800000001000800000000000009
      0000000000000000000000000000000000000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      80008000000080008000F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000070B0B0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B0B070000000B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B
      0B00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C0C0C07000B0606060606060606060606060606060606060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0C0C0B0B0B0C0C0C0C0B0B
      0B0B0C0C0B0B0B0C0C0B000B0606060606060606060606060606060606060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B070A0A0A0B0C0C0C0708
      08070C0B0808080C0C0B000B060609080A08060606060B070707060B07070706
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B080A0A0A080C0C0C070A
      0A070C070808080C0C0B000B1206070A0A0A080606060B080809060B07070706
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B080A0A0A0A0B0C0B080A
      0A070C070808080C0C0B000B1206070A0A0A0806060607080809060B07070706
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B07080A0A070B0B070A0A
      080B0B070808070C0C0B000B12120B0708080906060B08080706060B07070906
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B0B0B070B0B0B0B080A0A
      070C0B080A080B0C0C0B00091212060C0B0B0606060708080906060708070606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B0B0B0B0B0B0B080A0A08
      0B0B07080A080B0C0C0B000912121212121206060908080806060B0808070606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B0B0B0B0B0B080A0A0A07
      0B0B080A08070B0C0C0B000912121212121212080808080B06060708080B0606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B0B0B07070A0A0A0A070B
      0B070A0A080B0B0C0C0B0009121212121209080A080807120609080807060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B080A0A0A0A0A0A070B0B
      070A0A0A070B0B0B0B0B0009121209080A0A0A0A0807121209080A0809060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B080A0A0A0A08070B0B07
      0A0A0A080B0B0B0B0B0B00091212080A0A0A0A08091212090A0A0A0712060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B080A0808070B0B0B070A
      0A0A0A0B0B0B0B0B0B0B000912120708070709121212090A0A0A081212060606
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B07070B0B0B0B070A0A0A
      0A0A070B0B0B0B0B0B0B0009121209121212121212090A0A0A08091212121206
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B0B0B0B0B070A0A13130A
      0A070B0B0B0B0B0B0B0B000912121212121212090A0A0A0A0809121212121212
      060B000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000B0B0B07080A0A131313130A08
      070B0B0B0B0B0B0B0B0B00091212090909130A0A0A0A0A091212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000070B0B0A13131313130A08070B
      0B0B0B0B0B0B0B0B0B0B00091212080A0A0A0A0A0A0709121212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000070B0B0A0A0A0A0A08070B0B0B
      0B0B0B0B0B0B0B0B0B0B00091212080A0A0A0807091212121212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000070B0B07070707070B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B00091212090909121212121212121212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000070B0B0B0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B00091212121212121212121212121212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000070B0B0B0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B00091212121212121212121212121212121212121212
      120B000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000070B0B0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0000001212121212121212121212121212121212121212
      0900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000060000000180000000100010000000000200100000000000000000000
      000000000000000000000000FFFFFF00C00001C0000100000000000080000080
      0000000000000000800000800000000000000000800000800000000000000000
      8000008000000000000000008000008000000000000000008000008000000000
      0000000080000080000000000000000080000080000000000000000080000080
      0000000000000000800000800000000000000000800000800000000000000000
      8000008000000000000000008000008000000000000000008000008000000000
      0000000080000080000000000000000080000080000000000000000080000080
      0000000000000000800000800000000000000000800000800000000000000000
      800000800000000000000000800000800000000000000000C00001C000010000
      00000000FFFFFFFFFFFF00000000000000000000000000000000000000000000
      000000000000}
  end
  object ImageListBandwidth: TImageList
    DrawingStyle = dsTransparent
    Height = 24
    Width = 24
    Left = 384
    Top = 192
    Bitmap = {
      494C010104000900040018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3604
      000000000000360400002800000060000000480000000100080000000000001B
      0000000000000000000000000000000000000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      80008000000080008000F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000707070B0B0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B0807070707070B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B08
      07070707070B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0707070707070B0B0B
      0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0807070707020202020202020202020202
      0202020202020202070707070202020202020202020202020202020202020202
      0707070702020202020202020202020202020202020202020707070702020202
      0202020202020202020202020202020207070B0C020202020202020202020202
      02020202020202020C070B0C0202020202020202020202020202020202020202
      0C070B0C02020202020202020202020202020202020202020C070B0C02020202
      020202020202020202020202020202020C070707020202020202020202020202
      0202020202020202070707070202020202020202020202020202020202020202
      0707070702020202020202020202020202020202020202020707070702020202
      020202020202020202020202020202020707070B070C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C070B07070B070C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C07
      0B07070B070C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C070B07070B070C0C0C
      0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C070B070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      070707070707070707070707070707070707070B0B0C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C0B0B07070B0B0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0B
      0B07070B0B0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0B0B07070B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0707070F0F0F0F0F0F0F0F0F0F0F0F
      0F0F0F0F0F0F0F0F070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
      070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0707070700000000
      000000000000000000000000000000000707070B0F0F0F0F0F0F0F0F0F0F0F0F
      0F0F0F0F0F0F0F0F0B07070B0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
      0B07070B0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0B07070700000000
      00000000000000000000000000000000070707070F0F0F0F0F0F0F0F0F0F0F0F
      0F0F0F0F0F0F0F0F070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
      070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0707070700000000
      000000000000000000000000000000000707070B070B0C0B0B0B0B0B0B0B0B0B
      0B0B0B0B0B0B0B070B07070B070B0C0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B07
      0B07070B070B0C0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B070B07070B07070707
      070707070707070707070707070707070B070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      070707070707070707070707070707070707070B0B0C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C0B0B07070B0B0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0B
      0B07070B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B07070B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0707070F0F0F0F0F0F0F0F0F0F0F0F
      0F0F0F0F0F0F0F0F070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
      0707070700000000000000000000000000000000000000000707070700000000
      000000000000000000000000000000000707070B0F0F0D0D0D0D0D0D0D0D0D0D
      0D0D0D0D0D0F0F0F0B07070B0F0F0D0D0D0D0D0D0D0D0D0D0D0D0D0D0D0F0F0F
      0B07070700000000000000000000000000000000000000000707070700000000
      00000000000000000000000000000000070707070F0F0F0F0F0F0F0F0F0F0F0F
      0F0F0F0F0F0F0F0F070707070F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
      0707070700000000000000000000000000000000000000000707070700000000
      000000000000000000000000000000000707070B070C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C070B07070B070C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C07
      0B07070B07070707070707070707070707070707070707070B07070B07070707
      070707070707070707070707070707070B070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      070707070707070707070707070707070707070B0B0C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C0B0B07070B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B
      0B07070B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B07070B0B0B0B0B
      0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0707070D0D0D0D0D0D0D0D0D0D0D0D
      0D0D0D0D0D0D0D0D070707070000000000000000000000000000000000000000
      0707070700000000000000000000000000000000000000000707070700000000
      000000000000000000000000000000000707070B0D0D0D0D0D0D0D0D0D0D0D0D
      0D0D0D0D0D0D0D0D0C0707070000000000000000000000000000000000000000
      0707070700000000000000000000000000000000000000000707070700000000
      00000000000000000000000000000000070707070D0D0D0D0D0D0D0D0D0D0D0D
      0D0D0D0D0D0D0D0D070707070000000000000000000000000000000000000000
      0707070700000000000000000000000000000000000000000707070700000000
      000000000000000000000000000000000707070B070C0C0C0C0C0C0C0C0C0C0C
      0C0C0C0C0C0C0C070B07070B0707070707070707070707070707070707070707
      0B07070B07070707070707070707070707070707070707070B07070B07070707
      070707070707070707070707070707070B070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      0707070707070707070707070707070707070707070707070707070707070707
      070707070707070707070707070707070707424D3E000000000000003E000000
      2800000060000000480000000100010000000000600300000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000003FFFFC0000000000000000003FFFFC00000000
      00000000003FFFFC000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003FFFFC3FFFFC0000000000003FFF
      FC3FFFFC0000000000003FFFFC3FFFFC00000000000000000000000000000000
      00000000000000000000000000000000000000000000003FFFFC3FFFFC3FFFFC
      0000003FFFFC3FFFFC3FFFFC0000003FFFFC3FFFFC3FFFFC0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object ImageListPinned: TImageList
    DrawingStyle = dsTransparent
    Height = 24
    Width = 24
    Left = 384
    Top = 160
    Bitmap = {
      494C010102000400040018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3604
      0000000000003604000028000000600000001800000001000800000000000009
      0000000000000000000000000000000000000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      8000800000008000800080800000C0C0C00099A8AC00D8E9EC00F0FBFF00984E
      0000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF0000000000000080000080000000808000800000008000800080800000C0C0
      C00099A8AC00D8E9EC00F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000008000008000000080
      80008000000080008000F0FBFF00984E0000808080000000FF0000FF000000FF
      FF00FF000000FF00FF00FFFF0000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000070C0B070000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000B0B0B0000
      00000000000000000B00000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0B00
      000000000000000B0C0B000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0B
      0B0B0B0B0B0B0B0C0C0C000000000000000000000B0C0C0B0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0C
      0C0C0C0C0C0C0C0C0C0C00000000000009090909090909090909090900000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0C
      0C0C0C0C0C0C0C0C0B0B00000000000606060606060606060606060609000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000070B0B0B0B0B0B0B0B0C0C0C0C0C
      0C0C0C0C0C0C0C0C0B0B0000000000060606060606060606060606060B000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000B0C0C0C0C0C0C0C0B0C0C0C0C0C
      0C0C0C0C0C0C0C0B0B0B00000000000606060606060606060606060609000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000C0C0C0C0C0C0C0C0B0C0C0C0C0C
      0C0C0C0C0C0C0C0B0B0B00000000000009060612060606060606060900000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000070B0B0B0B0B0B0B0B0C0C0C0C0C
      0C0B0B0B0B0B0B0B0B0B00000000000000060609060606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0B
      0B0B0B0B0B0B0B0B0B0B00000000000000060609120606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0C
      0C0C0C0C0B0B0B0B0B0B00000000000000060609090606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0C0C
      0C0C0C0C0B0B0B0B0B0B00000000000000060609090606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0C0C0C0B00
      000000000000000B0B0B00000000000000121209090606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000C0C0C0000
      00000000000000000B0000000000000000121209090606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000090909090606060606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000090909091212120606090000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000009090909090909121206060900000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000909090909090909091212060609000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000009090909090909091212060900000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000060000000180000000100010000000000200100000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFC3FF000000000000FFFFFFFF
      C3FF000000000000FFFFFFFFC3FF000000000000FFFFFFFFC3FF000000000000
      FFFFFFFFC3FF000000000000FF8FFDFFC3FF000000000000FF07F8FFC3FF0000
      00000000FF0000FFC3FF000000000000FF0000FC003F000000000000FF0000F8
      001F000000000000000000F8001F000000000000000000F8001F000000000000
      000000FC003F000000000000000000FE007F000000000000FF0000FE007F0000
      00000000FF0000FE007F000000000000FF0000FE007F000000000000FF07F8FE
      007F000000000000FF8FFDFE007F000000000000FFFFFFFE007F000000000000
      FFFFFFFE007F000000000000FFFFFFFC003F000000000000FFFFFFF8001F0000
      00000000FFFFFFFC003F00000000000000000000000000000000000000000000
      000000000000}
  end
end
