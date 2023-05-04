object WINDOW_SETTINGS: TWINDOW_SETTINGS
  Left = 369
  Top = 148
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Settings'
  ClientHeight = 473
  ClientWidth = 505
  Color = clBtnFace
  ParentFont = True
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 505
    Height = 473
    ActivePage = TABSHEET_MODS
    TabIndex = 2
    TabOrder = 0
    object TABSHEET_GENERAL: TTabSheet
      Caption = 'General'
      OnShow = TABSHEET_GENERALShow
      object GROUPBOX_SERVERLIST: TGroupBox
        Left = 8
        Top = 62
        Width = 249
        Height = 51
        Caption = 'Server list '
        TabOrder = 1
        object LABEL_SERVERLIST_INTERVAL: TLabel
          Left = 16
          Top = 22
          Width = 102
          Height = 13
          Caption = 'Update-Interval (sec):'
          Transparent = True
        end
        object EDIT_SERVERLIST_UPDATE: TEdit
          Left = 192
          Top = 17
          Width = 33
          Height = 21
          TabOrder = 0
          Text = '2'
        end
        object UPDOWN_SERVERLIST_UPDATE: TUpDown
          Left = 225
          Top = 17
          Width = 15
          Height = 21
          Associate = EDIT_SERVERLIST_UPDATE
          Min = 1
          Max = 60
          Position = 2
          TabOrder = 1
          Wrap = False
          OnClick = UPDOWN_SERVERLIST_UPDATEClick
        end
      end
      object GROUPBOX_LANGUAGE: TGroupBox
        Left = 8
        Top = 6
        Width = 481
        Height = 51
        Caption = 'Language '
        TabOrder = 0
        object ComboBox1: TComboBoxEx
          Left = 16
          Top = 20
          Width = 449
          Height = 22
          ItemsEx.CaseSensitive = False
          ItemsEx.SortType = stNone
          ItemsEx = <>
          Style = csExDropDownList
          StyleEx = []
          ItemHeight = 16
          TabOrder = 0
          OnChange = ComboBox1Change
          Images = ImageListFlags
          DropDownCount = 8
        end
      end
      object GROUPBOX_NOTIFICATIONS: TGroupBox
        Left = 264
        Top = 62
        Width = 225
        Height = 51
        Caption = 'Notifications'
        TabOrder = 2
        object CHECKBOX_NOTIFICATIONS_ACTIVE: TCheckBox
          Left = 16
          Top = 20
          Width = 185
          Height = 17
          Caption = 'Active'
          TabOrder = 0
          OnClick = CHECKBOX_NOTIFICATIONS_ACTIVEClick
        end
      end
      object GROUPBOX_BANDWIDTHCONSUMPTION: TGroupBox
        Left = 264
        Top = 120
        Width = 225
        Height = 107
        Caption = 'Bandwidth usage'
        TabOrder = 3
        object LABEL_BANDWIDTH_VERYLOW: TLabel
          Left = 56
          Top = 87
          Width = 40
          Height = 13
          Caption = 'Very low'
          Transparent = True
        end
        object LABEL_BANDWIDTH_LOW: TLabel
          Left = 56
          Top = 65
          Width = 20
          Height = 13
          Caption = 'Low'
          Transparent = True
        end
        object LABEL_BANDWIDTH_MODERATE: TLabel
          Left = 56
          Top = 43
          Width = 45
          Height = 13
          Caption = 'Moderate'
          Transparent = True
        end
        object LABEL_BANDWIDTH_HIGH: TLabel
          Left = 56
          Top = 21
          Width = 22
          Height = 13
          Caption = 'High'
          Transparent = True
        end
        object TRACKBAR_BANDWIDTH: TTrackBar
          Left = 16
          Top = 16
          Width = 29
          Height = 89
          Max = 3
          Orientation = trVertical
          PageSize = 1
          Frequency = 1
          Position = 0
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          TickMarks = tmBottomRight
          TickStyle = tsAuto
          OnChange = TRACKBAR_BANDWIDTHChange
        end
      end
      object GROUPBOX_UPDATE: TGroupBox
        Left = 8
        Top = 232
        Width = 481
        Height = 49
        Caption = 'Updates '
        TabOrder = 4
        object CHECKBOX_UPDATE_CHECKATSTART: TCheckBox
          Left = 16
          Top = 20
          Width = 233
          Height = 17
          Caption = 'Check for new version at start'
          TabOrder = 0
          OnClick = CHECKBOX_UPDATE_CHECKATSTARTClick
        end
        object BUTTON_UPDATE: TButton
          Left = 256
          Top = 16
          Width = 217
          Height = 25
          Caption = 'Check for updates now'
          TabOrder = 1
          OnClick = BUTTON_UPDATEClick
        end
      end
      object GROUPBOX_VOLUME: TGroupBox
        Left = 8
        Top = 120
        Width = 249
        Height = 107
        Caption = 'Output volume for watched servers '
        TabOrder = 5
        object Label1: TLabel
          Left = 16
          Top = 72
          Width = 17
          Height = 13
          Caption = '0 %'
        end
        object Label2: TLabel
          Left = 212
          Top = 72
          Width = 29
          Height = 13
          Caption = '100 %'
        end
        object TRACKBAR_VOLUME: TTrackBar
          Left = 8
          Top = 32
          Width = 225
          Height = 40
          Max = 100
          Orientation = trHorizontal
          PageSize = 10
          Frequency = 10
          Position = 100
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          TickMarks = tmBoth
          TickStyle = tsAuto
          OnChange = TRACKBAR_VOLUMEChange
        end
      end
    end
    object TABSHEET_GAMES: TTabSheet
      Caption = 'Games'
      ImageIndex = 1
      object GROUPBOX_OFPCWC: TGroupBox
        Left = 8
        Top = 8
        Width = 481
        Height = 121
        TabOrder = 1
        Visible = False
        object LABEL_OFPCWC_PLAYERNAME: TLabel
          Left = 16
          Top = 72
          Width = 61
          Height = 13
          Caption = 'Player name:'
          Transparent = True
        end
        object EDIT_OFPCWC_EXECUTABLE: TEdit
          Left = 16
          Top = 40
          Width = 449
          Height = 21
          ReadOnly = True
          TabOrder = 2
        end
        object COMBOBOX_OFPCWC_PROFILE: TComboBox
          Left = 16
          Top = 88
          Width = 313
          Height = 21
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 1
          OnChange = COMBOBOX_OFPCWC_PROFILEChange
        end
        object BUTTON_OFPCWC_BROWSE: TButton
          Left = 356
          Top = 72
          Width = 109
          Height = 37
          Caption = 'Browse ...'
          TabOrder = 0
          OnClick = BUTTON_OFPCWC_BROWSEClick
        end
        object Panel1: TPanel
          Left = 16
          Top = 24
          Width = 449
          Height = 14
          BevelOuter = bvNone
          TabOrder = 3
          object LABEL_OFPCWC_EXECUTABLE: TLabel
            Left = 0
            Top = 0
            Width = 56
            Height = 13
            Align = alLeft
            Caption = 'Executable:'
          end
          object LABEL_OFPCWC_DETECTEDVERSION: TLabel
            Left = 345
            Top = 0
            Width = 84
            Height = 13
            Align = alRight
            Caption = 'Detected version:'
            Transparent = True
          end
        end
      end
      object GROUPBOX_OFPRES: TGroupBox
        Left = 8
        Top = 136
        Width = 481
        Height = 121
        TabOrder = 3
        Visible = False
        object LABEL_OFPRES_PLAYERNAME: TLabel
          Left = 16
          Top = 72
          Width = 61
          Height = 13
          Caption = 'Player name:'
          Transparent = True
        end
        object BUTTON_OFPRES_BROWSE: TButton
          Left = 356
          Top = 72
          Width = 109
          Height = 37
          Caption = 'Browse ...'
          TabOrder = 0
          OnClick = BUTTON_OFPRES_BROWSEClick
        end
        object EDIT_OFPRES_EXECUTABLE: TEdit
          Left = 16
          Top = 42
          Width = 449
          Height = 21
          ReadOnly = True
          TabOrder = 2
        end
        object COMBOBOX_OFPRES_PROFILE: TComboBox
          Left = 16
          Top = 88
          Width = 313
          Height = 21
          AutoDropDown = True
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 1
          OnChange = COMBOBOX_OFPRES_PROFILEChange
        end
        object Panel2: TPanel
          Left = 16
          Top = 24
          Width = 449
          Height = 14
          BevelOuter = bvNone
          TabOrder = 3
          object LABEL_OFPRES_EXECUTABLE: TLabel
            Left = 0
            Top = 0
            Width = 56
            Height = 13
            Align = alLeft
            Caption = 'Executable:'
            Transparent = True
          end
          object LABEL_OFPRES_DETECTEDVERSION: TLabel
            Left = 345
            Top = 0
            Width = 84
            Height = 13
            Align = alRight
            Caption = 'Detected version:'
            Transparent = True
          end
        end
      end
      object GROUPBOX_ARMACWA: TGroupBox
        Left = 8
        Top = 264
        Width = 481
        Height = 121
        TabOrder = 5
        Visible = False
        object LABEL_ARMACWA_PLAYERNAME: TLabel
          Left = 16
          Top = 72
          Width = 61
          Height = 13
          Caption = 'Player name:'
          Transparent = True
        end
        object EDIT_ARMACWA_EXECUTABLE: TEdit
          Left = 16
          Top = 40
          Width = 449
          Height = 21
          ReadOnly = True
          TabOrder = 2
        end
        object COMBOBOX_ARMACWA_PROFILE: TComboBox
          Left = 16
          Top = 88
          Width = 313
          Height = 21
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 1
          OnChange = COMBOBOX_ARMACWA_PROFILEChange
        end
        object BUTTON_ARMACWA_BROWSE: TButton
          Left = 356
          Top = 72
          Width = 109
          Height = 37
          Caption = 'Browse ...'
          TabOrder = 0
          OnClick = BUTTON_ARMACWA_BROWSEClick
        end
        object Panel3: TPanel
          Left = 16
          Top = 24
          Width = 449
          Height = 14
          BevelOuter = bvNone
          TabOrder = 3
          object LABEL_ARMACWA_EXECUTABLE: TLabel
            Left = 0
            Top = 0
            Width = 56
            Height = 13
            Align = alLeft
            Caption = 'Executable:'
            Transparent = True
          end
          object LABEL_ARMACWA_DETECTEDVERSION: TLabel
            Left = 345
            Top = 0
            Width = 84
            Height = 13
            Align = alRight
            Caption = 'Detected version:'
            Transparent = True
          end
        end
      end
      object CHECKBOX_OFPCWC: TCheckBox
        Left = 8
        Top = 8
        Width = 197
        Height = 17
        Caption = 'Arma: Resistance'
        TabOrder = 0
        OnClick = CHECKBOX_OFPCWCClick
      end
      object CHECKBOX_OFPRES: TCheckBox
        Left = 8
        Top = 136
        Width = 177
        Height = 17
        Caption = 'Operation Flashpoint: Resistance'
        TabOrder = 2
        Visible = False
        OnClick = CHECKBOX_OFPRESClick
      end
      object CHECKBOX_ARMACWA: TCheckBox
        Left = 8
        Top = 264
        Width = 135
        Height = 17
        Caption = 'ArmA: Cold War Assault'
        TabOrder = 4
        OnClick = CHECKBOX_ARMACWAClick
      end
    end
    object TABSHEET_MODS: TTabSheet
      Caption = 'Mod configurations'
      ImageIndex = 2
      OnShow = TABSHEET_MODSShow
      object GROUPBOX_CONFIGURATIONS: TGroupBox
        Left = 8
        Top = 40
        Width = 481
        Height = 185
        Caption = 'List of configurations'
        TabOrder = 1
        object BUTTON_EDITCONFIGURATION_COPY: TButton
          Left = 181
          Top = 148
          Width = 94
          Height = 25
          Caption = 'Copy'
          TabOrder = 3
          OnClick = BUTTON_EDITCONFIGURATION_COPYClick
        end
        object BUTTON_EDITCONFIGURATION_EDIT: TButton
          Left = 274
          Top = 148
          Width = 97
          Height = 25
          Caption = 'Edit'
          Enabled = False
          TabOrder = 4
          OnClick = BUTTON_EDITCONFIGURATION_EDITClick
        end
        object LISTBOX_CONFIGURATIONS: TListBox
          Left = 12
          Top = 16
          Width = 457
          Height = 129
          ItemHeight = 13
          TabOrder = 0
          OnClick = LISTBOX_CONFIGURATIONSClick
        end
        object BUTTON_EDITCONFIGURATION_UP: TButton
          Left = 12
          Top = 148
          Width = 50
          Height = 25
          Caption = 'Up'
          TabOrder = 1
          OnClick = BUTTON_EDITCONFIGURATION_UPClick
        end
        object BUTTON_EDITCONFIGURATION_DOWN: TButton
          Left = 61
          Top = 148
          Width = 50
          Height = 25
          Caption = 'Down'
          TabOrder = 2
          OnClick = BUTTON_EDITCONFIGURATION_DOWNClick
        end
        object BUTTON_CONFIGURATION_REMOVE: TButton
          Left = 370
          Top = 148
          Width = 99
          Height = 25
          Caption = 'Remove'
          TabOrder = 5
          OnClick = BUTTON_CONFIGURATION_REMOVEClick
        end
      end
      object GROUPBOX_NEWCONFIGURATION: TGroupBox
        Left = 8
        Top = 228
        Width = 481
        Height = 213
        Caption = 'New configuration'
        TabOrder = 2
        object LABEL_NEWCONFIGURATION_PASSWORD: TLabel
          Left = 272
          Top = 100
          Width = 49
          Height = 13
          Caption = 'Password:'
          Transparent = True
        end
        object LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS: TLabel
          Left = 274
          Top = 146
          Width = 104
          Height = 13
          Caption = 'Additional parameters:'
          Transparent = True
        end
        object LABEL_NEWCONFIGURATION_MODFOLDERS: TLabel
          Left = 8
          Top = 16
          Width = 55
          Height = 13
          Caption = 'Modfolders:'
          Transparent = True
        end
        object LABEL_NEWCONFIGURATION_LABEL: TLabel
          Left = 272
          Top = 58
          Width = 29
          Height = 13
          Caption = 'Label:'
          Transparent = True
        end
        object BUTTON_EDITCONFIGURATION_OK: TButton
          Left = 274
          Top = 16
          Width = 97
          Height = 33
          Caption = 'OK'
          Enabled = False
          TabOrder = 12
          Visible = False
          OnClick = BUTTON_EDITCONFIGURATION_OKClick
        end
        object EDIT_NEWCONFIGURATION_PASSWORD: TEdit
          Left = 273
          Top = 114
          Width = 192
          Height = 21
          TabOrder = 1
        end
        object LISTBOX_MODFOLDERS_ALL: TListBox
          Left = 8
          Top = 40
          Width = 121
          Height = 161
          ItemHeight = 13
          MultiSelect = True
          Sorted = True
          TabOrder = 4
        end
        object CHECKBOX_NEWCONFIGURATION_NOSPLASH: TCheckBox
          Left = 272
          Top = 184
          Width = 73
          Height = 17
          Caption = ' -nosplash'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object CHECKBOX_NEWCONFIGURATION_NOMAP: TCheckBox
          Left = 345
          Top = 184
          Width = 65
          Height = 17
          Caption = ' -nomap'
          Checked = True
          State = cbChecked
          TabOrder = 14
        end
        object EDIT_NEWCONFIGURATION_PARAMETERS: TEdit
          Left = 273
          Top = 160
          Width = 192
          Height = 21
          TabOrder = 2
        end
        object BUTTON_NEWCONFIGURATION_ADD: TButton
          Left = 274
          Top = 16
          Width = 97
          Height = 33
          Caption = 'Add'
          TabOrder = 10
          OnClick = BUTTON_NEWCONFIGURATION_ADDClick
        end
        object LISTBOX_MODFOLDERS_SELECTED: TListBox
          Left = 136
          Top = 40
          Width = 121
          Height = 161
          ItemHeight = 13
          TabOrder = 5
        end
        object BUTTON_NEWCONFIGURATION_MOVELEFT: TButton
          Left = 136
          Top = 16
          Width = 33
          Height = 25
          Caption = '<'
          TabOrder = 7
          OnClick = BUTTON_NEWCONFIGURATION_MOVELEFTClick
        end
        object BUTTON_NEWCONFIGURATION_MOVERIGHT: TButton
          Left = 96
          Top = 16
          Width = 33
          Height = 25
          Caption = '>'
          TabOrder = 6
          OnClick = BUTTON_NEWCONFIGURATION_MOVERIGHTClick
        end
        object BUTTON_NEWCONFIGURATION_UP: TButton
          Left = 168
          Top = 16
          Width = 45
          Height = 25
          Caption = 'Up'
          TabOrder = 8
          OnClick = BUTTON_NEWCONFIGURATION_UPClick
        end
        object BUTTON_NEWCONFIGURATION_DOWN: TButton
          Left = 212
          Top = 16
          Width = 45
          Height = 25
          Caption = 'Down'
          TabOrder = 9
          OnClick = BUTTON_NEWCONFIGURATION_DOWNClick
        end
        object EDIT_NEWCONFIGURATION_LABEL: TEdit
          Left = 272
          Top = 74
          Width = 193
          Height = 21
          TabOrder = 0
        end
        object BUTTON_EDITCONFIGURATION_CANCEL: TButton
          Left = 370
          Top = 16
          Width = 99
          Height = 33
          Caption = 'Cancel'
          Enabled = False
          TabOrder = 13
          Visible = False
          OnClick = BUTTON_EDITCONFIGURATION_CANCELClick
        end
        object BUTTON_NEWCONFIGURATION_CLEAR: TButton
          Left = 370
          Top = 16
          Width = 99
          Height = 33
          Caption = 'Clear'
          TabOrder = 11
          OnClick = BUTTON_NEWCONFIGURATION_CLEARClick
        end
      end
      object ComboBox2: TComboBox
        Left = 24
        Top = 12
        Width = 449
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
        OnChange = ComboBox2Change
      end
    end
    object TABSHEET_SERVERS: TTabSheet
      Caption = 'Servers'
      ImageIndex = 5
      OnShow = TABSHEET_SERVERSShow
      object BUTTON_SERVERS_ADD: TButton
        Left = 8
        Top = 8
        Width = 150
        Height = 41
        Caption = 'Add'
        TabOrder = 0
        OnClick = BUTTON_SERVERS_ADDClick
      end
      object BUTTON_SERVERS_REMOVE: TButton
        Left = 172
        Top = 8
        Width = 150
        Height = 41
        Caption = 'Remove'
        TabOrder = 1
        OnClick = BUTTON_SERVERS_REMOVEClick
      end
      object StringGrid1: TStringGrid
        Left = 0
        Top = 56
        Width = 497
        Height = 387
        ColCount = 7
        DefaultRowHeight = 21
        FixedCols = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 2
        OnDrawCell = StringGrid1DrawCell
        OnMouseDown = StringGrid1MouseDown
        ColWidths = (
          33
          117
          173
          27
          25
          28
          29)
      end
      object BUTTON_SERVERS_EXPORT: TButton
        Left = 336
        Top = 8
        Width = 150
        Height = 41
        Caption = 'Export to file ...'
        TabOrder = 3
        OnClick = BUTTON_SERVERS_EXPORTClick
      end
    end
    object TABSHEET_NOTIFICATIONS: TTabSheet
      Caption = 'Notifications'
      ImageIndex = 3
      OnShow = TABSHEET_NOTIFICATIONSShow
      object LABEL_AUDIOFILE: TLabel
        Left = 186
        Top = 288
        Width = 75
        Height = 13
        Caption = 'Audio file (mp3):'
        Transparent = True
      end
      object LABEL_NOTIFICATION_NAME: TLabel
        Left = 6
        Top = 288
        Width = 31
        Height = 13
        Caption = 'Name:'
        Transparent = True
      end
      object LABEL_VOLUME: TLabel
        Left = 6
        Top = 332
        Width = 38
        Height = 13
        Caption = 'Volume:'
      end
      object LABEL_MARKINGCOLOR: TLabel
        Left = 270
        Top = 382
        Width = 67
        Height = 13
        Caption = 'Marking color:'
        Transparent = True
      end
      object LABEL_AUDIO_TO: TLabel
        Left = 186
        Top = 382
        Width = 16
        Height = 13
        Caption = 'To:'
        Transparent = True
      end
      object LABEL_AUDIO_FROM: TLabel
        Left = 186
        Top = 332
        Width = 26
        Height = 13
        Caption = 'From:'
        Transparent = True
      end
      object BUTTON_NOTIFICATION_REMOVE: TButton
        Left = 6
        Top = 200
        Width = 169
        Height = 25
        Caption = 'Remove'
        TabOrder = 3
        OnClick = BUTTON_NOTIFICATION_REMOVEClick
      end
      object BUTTON_EDITNOTIFICATION_EDIT: TButton
        Left = 6
        Top = 224
        Width = 169
        Height = 25
        Caption = 'Edit'
        TabOrder = 4
        OnClick = BUTTON_EDITNOTIFICATION_EDITClick
      end
      object BUTTON_EDITNOTIFICATION_OK: TButton
        Left = 6
        Top = 248
        Width = 85
        Height = 25
        Caption = 'OK'
        Enabled = False
        TabOrder = 5
        Visible = False
        OnClick = BUTTON_EDITNOTIFICATION_OKClick
      end
      object BUTTON_EDITNOTIFICATION_CANCEL: TButton
        Left = 90
        Top = 248
        Width = 85
        Height = 25
        Caption = 'Cancel'
        Enabled = False
        TabOrder = 6
        Visible = False
        OnClick = BUTTON_EDITNOTIFICATION_CANCELClick
      end
      object CHECKBOX_REPEAT: TCheckBox
        Left = 272
        Top = 350
        Width = 89
        Height = 17
        Caption = 'Repeat'
        TabOrder = 18
      end
      object TrackBar1: TTrackBar
        Left = 2
        Top = 345
        Width = 177
        Height = 31
        BorderWidth = 5
        Ctl3D = True
        Max = 100
        Orientation = trHorizontal
        ParentCtl3D = False
        Frequency = 10
        Position = 100
        SelEnd = 0
        SelStart = 0
        TabOrder = 11
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar1Change
      end
      object EDIT_SONGEND_SEC: TEdit
        Left = 210
        Top = 400
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 16
        Text = '0'
        OnChange = EDIT_SONGEND_SECChange
      end
      object EDIT_SONGEND_MIN: TEdit
        Left = 186
        Top = 400
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 15
        Text = '0'
        OnChange = EDIT_SONGEND_MINChange
      end
      object EDIT_SONGSTART_MILL: TEdit
        Left = 234
        Top = 348
        Width = 28
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 3
        ParentBiDiMode = False
        TabOrder = 14
        Text = '0'
        OnChange = EDIT_SONGSTART_MILLChange
      end
      object EDIT_SONGSTART_SEC: TEdit
        Left = 210
        Top = 348
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 13
        Text = '0'
        OnChange = EDIT_SONGSTART_SECChange
      end
      object EDIT_SONGSTART_MIN: TEdit
        Left = 186
        Top = 348
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 12
        Text = '0'
        OnChange = EDIT_SONGSTART_MINChange
      end
      object EDIT_SONGEND_MILL: TEdit
        Left = 234
        Top = 400
        Width = 28
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 3
        ParentBiDiMode = False
        TabOrder = 17
        Text = '0'
        OnChange = EDIT_SONGEND_MILLChange
      end
      object ColorBox1: TColorBox
        Left = 275
        Top = 400
        Width = 214
        Height = 22
        Style = [cbStandardColors, cbCustomColor, cbPrettyNames]
        ItemHeight = 16
        TabOrder = 19
      end
      object BUTTON_BROWSE: TButton
        Left = 371
        Top = 336
        Width = 118
        Height = 41
        Caption = 'Browse ...'
        TabOrder = 10
        OnClick = BUTTON_BROWSEClick
      end
      object EDIT_NOTIFICATION_FILE: TEdit
        Left = 186
        Top = 304
        Width = 303
        Height = 21
        ReadOnly = True
        TabOrder = 9
        OnChange = EDIT_NOTIFICATION_FILEChange
        OnKeyUp = EDIT_NOTIFICATION_FILEKeyUp
      end
      object EDIT_NOTIFICATION_NAME: TEdit
        Left = 6
        Top = 304
        Width = 169
        Height = 21
        TabOrder = 8
        Text = ' '
      end
      object GROUPBOX_NOTIFICATIONS_FILTERS: TGroupBox
        Left = 184
        Top = 8
        Width = 305
        Height = 263
        Caption = 'Filters'
        TabOrder = 1
        object LABEL_FILTER_SERVERNAME_BOX: TLabel
          Left = 152
          Top = 96
          Width = 60
          Height = 13
          Caption = 'Servername:'
          Transparent = True
        end
        object LABEL_FILTER_MISSIONNAME_BOX: TLabel
          Left = 152
          Top = 16
          Width = 67
          Height = 13
          Caption = 'Mission name:'
          Transparent = True
        end
        object LABEL_FILTER_PLAYERNAME_BOX: TLabel
          Left = 152
          Top = 176
          Width = 58
          Height = 13
          Caption = 'Playername:'
          Transparent = True
        end
        object LABEL_FILTER_STATUS: TLabel
          Left = 16
          Top = 16
          Width = 33
          Height = 13
          Caption = 'Status:'
          Transparent = True
        end
        object LABEL_FILTER_PASSWORD: TLabel
          Left = 16
          Top = 136
          Width = 49
          Height = 13
          Caption = 'Password:'
        end
        object LABEL_FILTER_PLAYERS: TLabel
          Left = 16
          Top = 192
          Width = 37
          Height = 13
          Caption = 'Players:'
          Transparent = True
        end
        object CHECKBOX_FILTER_CREATING: TCheckBox
          Left = 16
          Top = 32
          Width = 129
          Height = 17
          Caption = 'Creating'
          TabOrder = 0
        end
        object CHECKBOX_FILTER_WAITING: TCheckBox
          Left = 16
          Top = 48
          Width = 129
          Height = 17
          Caption = 'Waiting'
          TabOrder = 1
        end
        object CHECKBOX_FILTER_SETTINGUP: TCheckBox
          Left = 16
          Top = 64
          Width = 129
          Height = 17
          Caption = 'Setting up'
          TabOrder = 2
        end
        object CHECKBOX_FILTER_BRIEFING: TCheckBox
          Left = 16
          Top = 80
          Width = 129
          Height = 17
          Caption = 'Briefing'
          TabOrder = 3
        end
        object CHECKBOX_FILTER_PLAYING: TCheckBox
          Left = 16
          Top = 96
          Width = 129
          Height = 17
          Caption = 'Playing'
          TabOrder = 4
        end
        object CHECKBOX_FILTER_DEBRIEFING: TCheckBox
          Left = 16
          Top = 112
          Width = 129
          Height = 17
          Caption = 'Debriefing'
          TabOrder = 5
        end
        object CHECKBOX_FILTER_WITHPASSWORD: TCheckBox
          Left = 16
          Top = 152
          Width = 97
          Height = 17
          Caption = 'With'
          TabOrder = 6
        end
        object CHECKBOX_FILTER_WITHOUTPASSWORD: TCheckBox
          Left = 16
          Top = 168
          Width = 97
          Height = 17
          Caption = 'Without'
          TabOrder = 7
        end
        object MEMO_FILTER_MISSIONNAME: TMemo
          Left = 152
          Top = 32
          Width = 145
          Height = 57
          ScrollBars = ssVertical
          TabOrder = 14
        end
        object MEMO_FILTER_SERVERNAME: TMemo
          Left = 152
          Top = 112
          Width = 145
          Height = 57
          ScrollBars = ssVertical
          TabOrder = 15
        end
        object MEMO_FILTER_PLAYERNAME: TMemo
          Left = 152
          Top = 192
          Width = 145
          Height = 57
          ScrollBars = ssVertical
          TabOrder = 16
        end
        object UPDOWN_MINPLAYERS: TUpDown
          Left = 49
          Top = 225
          Width = 15
          Height = 21
          Associate = EDIT_FILTER_MINPLAYERS
          Enabled = False
          Min = 0
          Position = 0
          TabOrder = 10
          Wrap = False
        end
        object UPDOWN_MAXPLAYERS: TUpDown
          Left = 113
          Top = 225
          Width = 15
          Height = 21
          Associate = EDIT_FILTER_MAXPLAYERS
          Enabled = False
          Min = 0
          Position = 0
          TabOrder = 13
          Wrap = False
        end
        object EDIT_FILTER_MINPLAYERS: TEdit
          Left = 16
          Top = 225
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 9
          Text = '0'
          OnChange = EDIT_FILTER_MINPLAYERSChange
        end
        object EDIT_FILTER_MAXPLAYERS: TEdit
          Left = 80
          Top = 225
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 12
          Text = '0'
          OnChange = EDIT_FILTER_MAXPLAYERSChange
        end
        object CHECKBOX_FILTER_MINPLAYERS: TCheckBox
          Left = 16
          Top = 208
          Width = 49
          Height = 17
          Caption = 'Min'
          TabOrder = 8
          OnClick = CHECKBOX_FILTER_MINPLAYERSClick
        end
        object CHECKBOX_FILTER_MAXPLAYERS: TCheckBox
          Left = 80
          Top = 208
          Width = 49
          Height = 17
          Caption = 'Max'
          TabOrder = 11
          OnClick = CHECKBOX_FILTER_MAXPLAYERSClick
        end
      end
      object LISTBOX_NOTIFICATIONS: TListBox
        Left = 6
        Top = 13
        Width = 169
        Height = 185
        ItemHeight = 13
        TabOrder = 0
        OnClick = LISTBOX_NOTIFICATIONSClick
      end
      object BUTTON_NEWNOTIFICATION_ADD: TButton
        Left = 6
        Top = 248
        Width = 85
        Height = 25
        Caption = 'Add'
        TabOrder = 2
        OnClick = BUTTON_NEWNOTIFICATION_ADDClick
      end
      object BUTTON_NEWNOTIFICATION_CLEAR: TButton
        Left = 90
        Top = 248
        Width = 85
        Height = 25
        Caption = 'Clear'
        TabOrder = 7
        OnClick = BUTTON_NEWNOTIFICATION_CLEARClick
      end
      object GROUPBOX_PREVIEW: TGroupBox
        Left = 8
        Top = 380
        Width = 161
        Height = 46
        TabOrder = 20
        object LabelMinutes: TLabel
          Left = 54
          Top = 13
          Width = 25
          Height = 24
          Caption = '00:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object LabelSeconds: TLabel
          Left = 80
          Top = 13
          Width = 25
          Height = 24
          Caption = '00:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object LabelMilli: TLabel
          Left = 106
          Top = 13
          Width = 30
          Height = 24
          Caption = '000'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object PLAY: TBitBtn
          Left = 0
          Top = 5
          Width = 41
          Height = 41
          TabOrder = 0
          OnClick = PLAYClick
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000020000000200000000100
            180000000000000C0000130B0000130B00000000000000000000ACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACAC8F908F767877ACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC9C9C9C595C5B5D6260666A686C6F
            6D8B8C8BACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC9596954D514F8E93917F8482666B
            68626664818382ACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B89848A888489
            87767C7A626865686C6A8D8E8EACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B89858A886469
            67787D7B878B89676C6A5B605E868787ACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B89858A88696D
            6B5659577176748A908E787D7B626564717372ACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B89858A886C70
            6E6064625F6361686C6A7D8280858A886A6F6D5B5E5D858786ACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B89858A886D72
            70636866626765636866646967747977888D8B787D7B666967737473ACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B898489876F75
            73666B69666B69666B69646967676C6A7378767C82807F84827276745C605E7B
            7D7CACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B898489877277
            756A6F6D6A6F6D6A6F6D6B706E696E6C686D6B6E7472787D7B80868473787664
            6866848685ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B898489877579
            776E72706E72706E73716E73716E73716E72706A6F6D6A6F6D868B8991969464
            69676E7270ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B89848987777B
            79727674727674727674727674717573717573787C7A7F83817F8482696E6C62
            6664898B8AACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B89848987797E
            7C757A78757A78757A78747876777B79808583848987777C7A6D706F61656384
            8685ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B898388867C81
            7F787E7C787D7B797E7C7B817F8186848085836D72706467667D7E7EACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B898388867E83
            817C817F7C817F8287858489877B7F7D666A68616462909191ACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B898388868085
            837E83818388868389866D716F636664848585ACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979797515553868B898388868287
            85888D8B7E83815B605E5F6260949594ACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC979897515553868B89848987888D
            8B6A6F6C6366657E807FACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC9596964D52508D9290767C7A555A
            57636665ACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC9D9E9D5C5F5D565B58686B6A7D7F
            7EACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACAC969696838484ACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACAC}
          Layout = blGlyphBottom
        end
        object STOP: TBitBtn
          Left = 0
          Top = 5
          Width = 41
          Height = 41
          TabOrder = 1
          Visible = False
          OnClick = STOPClick
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000020000000200000000100
            180000000000000C0000130B0000130B00000000000000000000ACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC7577765F62616063626265646265
            646265646265646265646265646265646265646265646265646164625E616074
            7675ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC7678775458565D625F6065636267646166
            646166646166646166646166646166646166646166646267646065635D626054
            5856747675ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6164625A605D8E9391898E8C848987858A
            88858A88858A88858A88858A88858A88858A88858A88848987888D8B8F94925D
            62605E6160ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6366655E6360888D8B717573626664666B
            69666B69666B69666B69666B69666B69666B69666B696266646F7472888D8B60
            6563616462ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665F6462858A88666A68525654585C
            5A585C5A585C5A585C5A585C5A585C5A585C5A585C5A52565464686684898761
            6664626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665E6361868B896E72705D615F6165
            636165636165636165636165636165636165636165635D615F6C706E858A8860
            6563626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665E6360868B897074726064626468
            666468666468666468666468666468666468666468666164626E7270868B8960
            6563626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665D6260868B89737876666A68696D
            6B696D6B696E6C696E6C696E6C696E6C696D6B696D6B666A68727775868B895F
            6462626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665D625F878C8A777C7A6B706E6E73
            716E73716E73716E73716E73716E73716E73716E73716B706E757B79878C8A5F
            6462626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665D625F878C8A787D7B6E73717176
            747176747176747176747176747176747176747176746E7371777C7A878C8A5F
            6461626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665C615F878C8A7B807E737876757A
            78757A78757A78757A78757A78757A78757A78757A787378767A7F7D888D8B5E
            6361626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6568665C615E888D8B7F8482787D7B7A7F
            7D7A7F7D7A7F7D7A7F7D7A7F7D7A7F7D7A7F7D7A7F7D787D7B7E8381888D8B5E
            6360626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665B605E888D8B8186847B807E7C81
            7F7C817F7C817F7C817F7C817F7C817F7C817F7C817F7B807E808583898E8C5E
            6360626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6567665B605E888D8B8489877F84828085
            838085838085838085838085838085838085838085837F8482838886898E8C5D
            6260626564ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6366645A5F5D8B908E898E8C868B89868B
            89868B89868B89868B89868B89868B89868B89868B89868B89888D8B8C918F5D
            625F606362ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC6265635A5F5D8D92908B908E898E8C898E
            8C898E8C898E8C898E8C898E8C898E8C898E8C898E8C898E8C8B908E8E93915C
            615F5F6261ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACAC7779785458565A5F5D5A605D5B605E5B60
            5E5B605E5B605E5B605E5B605E5B605E5B605E5B605E5B605E5B605D5A5F5D54
            5856757776ACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACAC7779786265636366646567666567
            6665686665676665676665676665676665676665676665676663666561646276
            7877ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACACAC
            ACACACACACACACACACACACACACACACACACACACACACACACACACAC}
          Layout = blGlyphBottom
        end
      end
    end
    object TABSHEET_CHATSETTINGS: TTabSheet
      Caption = 'Chat'
      ImageIndex = 4
      OnExit = TABSHEET_CHATSETTINGSExit
      OnShow = TABSHEET_CHATSETTINGSShow
      object GROUPBOX_CHATSETTINGS_SERVER: TGroupBox
        Left = 8
        Top = 80
        Width = 481
        Height = 113
        Caption = 'Chat server '
        TabOrder = 1
        object LABEL_CHAT_IRCSERVER_ADDRESS: TLabel
          Left = 16
          Top = 16
          Width = 95
          Height = 13
          Caption = 'IRC Server address:'
          Transparent = True
        end
        object LABEL_CHAT_IRCSERVER_PORT: TLabel
          Left = 384
          Top = 16
          Width = 22
          Height = 13
          Caption = 'Port:'
          Transparent = True
        end
        object LABEL_CHAT_IRCSERVER_CHANNEL: TLabel
          Left = 16
          Top = 60
          Width = 42
          Height = 13
          Caption = 'Channel:'
          Transparent = True
        end
        object EDIT_CHAT_IRCSERVER_ADDRESS: TEdit
          Left = 16
          Top = 32
          Width = 353
          Height = 21
          MaxLength = 32
          TabOrder = 0
        end
        object EDIT_CHAT_IRCSERVER_PORT: TEdit
          Left = 384
          Top = 32
          Width = 73
          Height = 21
          MaxLength = 5
          TabOrder = 1
          OnChange = EDIT_CHAT_IRCSERVER_PORTChange
        end
        object EDIT_CHAT_IRCSERVER_CHANNEL: TEdit
          Left = 16
          Top = 76
          Width = 209
          Height = 21
          MaxLength = 32
          TabOrder = 2
        end
        object BUTTON_CHAT_SETDEFAULT: TButton
          Left = 256
          Top = 64
          Width = 203
          Height = 33
          Caption = 'Set default server'
          TabOrder = 3
          OnClick = BUTTON_CHAT_SETDEFAULTClick
        end
      end
      object GROUPBOX_CHATSETTINGS_GENERAL: TGroupBox
        Left = 8
        Top = 8
        Width = 481
        Height = 65
        Caption = 'General settings '
        TabOrder = 0
        object LABEL_CHAT_USERNAME: TLabel
          Left = 16
          Top = 16
          Width = 54
          Height = 13
          Caption = 'User name:'
          Transparent = True
        end
        object COMBOBOX_CHAT_USERNAME: TComboBox
          Left = 16
          Top = 32
          Width = 209
          Height = 21
          ItemHeight = 0
          MaxLength = 14
          Sorted = True
          TabOrder = 0
        end
        object CHECKBOX_CHAT_AUTOCONNECT: TCheckBox
          Left = 256
          Top = 32
          Width = 209
          Height = 17
          Caption = 'Autoconnect on startup'
          TabOrder = 1
        end
      end
      object GROUPBOX_CHATSETTINGS_NOTIFICATIONS: TGroupBox
        Left = 8
        Top = 200
        Width = 481
        Height = 129
        Caption = 'Notifications on incoming messages '
        TabOrder = 2
        object Bevel1: TBevel
          Left = 10
          Top = 48
          Width = 460
          Height = 2
        end
        object LABEL_CHATSETTINGS_SELECTEDAUDIOFILE: TLabel
          Left = 16
          Top = 72
          Width = 3
          Height = 13
        end
        object CHECKBOX_CHATSETTINGS_BALLONHINT: TCheckBox
          Left = 16
          Top = 24
          Width = 449
          Height = 17
          Caption = 'Display ballon hint at the tray icon'
          TabOrder = 0
          OnClick = CHECKBOX_CHATSETTINGS_BALLONHINTClick
        end
        object BUTTON_CHATSETTINGS_BROWSEAUDIOFILE: TButton
          Left = 12
          Top = 90
          Width = 101
          Height = 31
          Caption = 'Browse'
          TabOrder = 1
          OnClick = BUTTON_CHATSETTINGS_BROWSEAUDIOFILEClick
        end
        object BUTTON_CHATSETTINGS_CLEARAUDIOFILE: TButton
          Left = 112
          Top = 90
          Width = 101
          Height = 31
          Caption = 'Clear'
          TabOrder = 2
          OnClick = BUTTON_CHATSETTINGS_CLEARAUDIOFILEClick
        end
        object CHECKBOX_CHATSETTINGS_AUDIONOTIFICATION: TCheckBox
          Left = 16
          Top = 54
          Width = 457
          Height = 17
          Caption = 'Play audio file:'
          TabOrder = 3
          OnClick = CHECKBOX_CHATSETTINGS_AUDIONOTIFICATIONClick
        end
      end
    end
    object TABSHEET_MASTERSERVERS: TTabSheet
      Caption = 'Master servers'
      ImageIndex = 6
      OnShow = TABSHEET_MASTERSERVERSShow
      object GROUPBOX_MASTERSERVERS: TGroupBox
        Left = 8
        Top = 8
        Width = 481
        Height = 169
        Caption = ' Community hosted Masterservers  '
        TabOrder = 0
        object BUTTON_MASTERSERVERS_ADD: TButton
          Left = 8
          Top = 24
          Width = 185
          Height = 50
          Caption = 'Add domain'
          TabOrder = 0
          OnClick = BUTTON_MASTERSERVERS_ADDClick
        end
        object BUTTON_MASTERSERVERS_REMOVE: TButton
          Left = 8
          Top = 78
          Width = 185
          Height = 50
          Caption = 'Remove domain'
          TabOrder = 1
          OnClick = BUTTON_MASTERSERVERS_REMOVEClick
        end
        object LISTBOX_MASTERSERVERS: TListBox
          Left = 200
          Top = 24
          Width = 273
          Height = 105
          ItemHeight = 13
          TabOrder = 2
          OnClick = LISTBOX_MASTERSERVERSClick
        end
        object CHECKBOX_MASTERSERVERS_UPDATEONSTART: TCheckBox
          Left = 8
          Top = 138
          Width = 465
          Height = 17
          Caption = 'Update list on start'
          TabOrder = 3
          OnClick = CHECKBOX_MASTERSERVERS_UPDATEONSTARTClick
        end
      end
    end
  end
  object OpenDialogGameFile: TOpenDialog
    Filter = 'OFP:R (FLASHPOINTRESISTANCE.EXE)|FLASHPOINTRESISTANCE.EXE'
    Options = [ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofDontAddToRecent]
    OptionsEx = [ofExNoPlacesBar]
    OnCanClose = OpenDialogGameFileCanClose
    Left = 8
    Top = 440
  end
  object OpenDialogAudioFile: TOpenDialog
    Filter = 'Audio File (mp3, wav)|*.mp3;*.wav'
    Options = [ofReadOnly, ofHideReadOnly, ofNoNetworkButton, ofEnableSizing, ofDontAddToRecent]
    OnCanClose = OpenDialogAudioFileCanClose
    Left = 40
    Top = 440
  end
  object ImageListPropertyIcons: TImageList
    DrawingStyle = dsTransparent
    Left = 104
    Top = 440
    Bitmap = {
      494C010104000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001001000000000000018
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000004E66015200000000
      0000000000000000A5664E66000000000000765212423A670000000000000000
      0000000000000000000000000000000000000000AF5EAE5E4B566A5E485A6862
      0556055A055A075A06560856E75509560000000000000000000000000000EA65
      66594661A96D000000000000000000000000000000000000EC592977635E0000
      000000000000225609734E66000000000000B85A7652CF393B6B000000000000
      0000000000000000000000000000000000000000AF5EB67F957FD57FD57FD47F
      F47FD37F917F937F717F537F527F2A5A000000000000000000004A51A53C6655
      A85D68656765A63CA63C0000000000000000000000000000AE62C47FA27F8066
      A06AC06E8066827F817F8C5E0000000000009C735A6BD65AEF3D176300000000
      00000000000000000000000000000000000000006B5AB47F3077EB6EEC72EA72
      0B7B0B7BC972896E886AED76717FC551000000000000AF7DA764236C44700B79
      4C7D2B754C7D6574877C24586E7D00000000000000000000F06A0077A37F857F
      C06E01770177C37F607F094E00000000000000005B6BF762B55ACE3D38670000
      0000000000000000000000000000000000000000AD5ED57F717B0D77707FD17F
      B07F8F7FB07F0C7BCA72ED76B37FE65100000000000086642354857844700358
      0B79A7680A7101640268665C0354000000000000000000000000606A217FA37F
      627F617F827F007F217F000000000000000000000000596B3763B556CE395A67
      D75AB6523242F039734A39630000000000000000CD66B37F507B0C732D7B6D7F
      6666025A4D7FA86EA86ECB72907F065A000000008C4D4254004C4154835C4B65
      0000000000006E5A243164584254C63400000000000000000000A06E647F207F
      207F007F407F857FA0720000000000000000000000000000BB73B55230421142
      534696527C6B7C6BB5527246D6529B6B000000000F73D37F717F4E7F6F7FAF7F
      876A245EB07F0B7BEB76EC76917F475E00000000A42C215042542154004C8548
      4A610000000000008F6200482150852C0000000000000000495EE072E072677F
      467F667F467F407BC06E485E00000000000000000000000000005B67113E5546
      9F6F7F6B9F6B5D635C63395F7446B44A00000000106BB57F30732F7330774F7B
      CC6AAA6A717FED72AB6ACD6E927F295600004E7240300134C648AC55832C2158
      215847550000000000002A55633C003C696500000000075ACD6E207B837F047B
      257F457F257F207BA37FAB6A275A000000000000000000000000195F54469F6F
      7F6B7F6B9F6B3B5F5C63BD6BF8567346385B0000CE66F77F727B727FB37F717F
      B37F917F927F507FED72307BD57F28560000A95DA13C002C4B5D00006A49225C
      0158813C695D00000000295500302040065DF07E0966E9764D7F887F667B6D7F
      4C7F6D7F2B7B457B667F6D7FE9762A6AEF7E0000000000000000D956974E7F6B
      5F675F635F635E635D5F5B5F7D67954AB64E00001467B87BFB7FD97FD97FD87F
      FA7FFA7FB87FFA7FB77F987FB87F4E5600004A750048654CE95C00000000AC71
      4144026024682A5500002B6901406048055D0A664B6E0B7B4C7F467B45776D7F
      4C7F2B7BAE7FA87F877F2B7F4C7F6C72C75D0000000000000000133E3C635E63
      7F6B1D5B5F633D5F3D5FBF6F7D675B63313E000034676F522C4A2C4EF262126B
      8F5A8E5AD166F266A83DC941EA45B1620000EF7D205002400A61000000000000
      AC7123680364A640AE618654444C61486869D372357BD46A725E2E5A4F62AF76
      757F747FCF7A2D5A4D5E0D529262D272906A0000000000000000F23D5D673D5F
      1C5B7F675F675E639F6BDF777D6B7C6B534600000000514AF75E304600000000
      0000000000000000CD3DF6623046000000000000E73C8560445C000000000000
      0000AE65E950855CA56064606460C638000000000000000000000000777F6D6E
      337F957F4C6A1477000000000000000000000000000000000000B856974E5E67
      3E633E639F6B9F6B5E679E6BFF7BF85A534600000000514AF75E514A00000000
      0000000000000000514AB55A314A0000000000002A498D7D2A75243100000000
      00000000D06D0869296D6B7D08714A4D00000000000000000000000000004C66
      557F557F2C6600000000000000000000000000000000000000005B67113E195B
      FF7B9E6F9E6F9D6FFF7BFF7BBE77534E186700000000514AD65AF75A514A0000
      000000000000514AB656524A514A00000000000000004B65CF75AE7DC7642A51
      2A514C59C748E7688C79AE716B6900000000000000000000000000000000B076
      F27ED17A6E6E00000000000000000000000000000000000000000000F85A3342
      5C67BF73FF7BDF77FF7BFF7B3246B5560000000000000000514AF75EB656514A
      32465246514A95529552514A00000000000000000000F079AE71957E327E116E
      F16DAE653276527E317EAD71107E000000000000000000000000000000000000
      725EB4660000000000000000000000000000000000000000000000000000934E
      B44EB452BC739C73D55A9356935600000000000000000000514A514AF75EF75E
      F75EF75EF85ED65A514A514A00000000000000000000000000004C51336EF57E
      D47E147FD27A126A116A00000000000000000000000000000000000000000000
      30560F5600000000000000000000000000000000000000000000000000000000
      185FD5520F3A3046D55AF66200000000000000000000000000000000514A514A
      514A514A514A514A00000000000000000000000000000000000000007576AB65
      8A61AA55CA59326A00000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000E7E71FFF8001FC3FE3C70FFF8001F00F
      E00707FF8001C003E00783FF8001C003F00FC007800181C1F00FE001800180E1
      E007F00180010070C003F000800108300000F00080010C100000F00080010E00
      0000F000C7E38F01F81FF000C7E38781FC3FF000C3C3C003FC3FF801E007C003
      FE7FFC03E007F00FFE7FFE07F81FF81F00000000000000000000000000000000
      000000000000}
  end
  object ImageListFlags: TImageList
    Left = 72
    Top = 440
    Bitmap = {
      494C01010A000E00040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001001000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF7FFF7FFF7FFF7FFF7FFF7F
      FF7FFF7FFF7FFF7FFF7FFF7FFF7FFF7F00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000009C737B6F7B6F7B6F7B6F7B6F
      7B6F7B6F7B6F7B6F7B6F7B6F7B6F9C730000FF7F9C737B6F7B6F7B6F7B6F7B6F
      7B6F7B6F7B6F7B6F7B6F7B6F7B6F9C73FF7F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C73524ACE39CE39CE39CE39CE39
      CE39CE39CE39CE39CE39CE39CE39524A9C739C73524ACE39CE39CE39CE39CE39
      CE39CE39CE39CE39CE39CE39CE39524A9C730000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E278867D867DA67DA77DA77D867D
      867D657D657D447D237D027DE17CCE397B6FE370E370E36CE36CE36CC368C268
      A264A264A26081608160615C4250CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000479877D877DA87DA87DA87DA87D
      877D667D457D257D037DE27CE17CCE397B6F0375A77DA77DA77D867D867D657D
      447D437D237D027DE17CE07C605CCE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A379257E057A257E257E467A267E
      257E047EE47DE37DC27DA17DA17DCE397B6F0379A77DC87DC87DA77D867D657D
      647D447D237D027D017DE07C6060CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000417FC07FE07FA17F817BE07FE07F
      C07FA07FA07F807F807F607F607FCE397B6F2379C87DC87DC87DA77D867D657D
      657D447D237D027D017DE07C6060CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000417FC07F246F827A217AC36EA17B
      C07FA07FA07F807F607F607F607FCE397B6F222AA53AA53AA53AA53AA4368436
      8332632E422A41262122001E8019CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000417FC07F867A216949594A76A17F
      C07FA07FA07F807F807F607F607FCE397B6F8212052B052B052B052BE426E422
      C31EC31AA216A212810A6006E001CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000417FC07FE372226D1056086BC07F
      C07FA07FA07F807F807F607F607FCE397B6F8212052F052F052F052B0427E422
      E31EC31AA216A212810E6006E005CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000617FC07FA07B416E226A807BE07F
      C07FC07FA07F807F807F607F807FCE397B6FA8262B3F4C434C434C432B3F2B3B
      0A370A33E92EC92AC826A7222516CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000417FC07FE07FA17F817BE07FE07F
      C07FA07FA07F807F807F607F607FCE397B6F3967BD77DE7BDE7BDE7BDE7BDE7B
      BD77BD779C737B6F7B6F5A6BB556CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008379057E057E257E467E267E267E
      057E047EE47DC37DA27D817D817DCE397B6F3967BD77DE7BDE7BFF7FFF7FDE7B
      BD77BD779C737B6F7B6F5A6BB556CE397B6F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000479877D877DA87DC97DC97DA87D
      877D667D457D457D237D027DE17C524A9C735A6BBD77DE7BDE7BFF7FFF7FDE7B
      DE7BBD779C739C737B6F5A6BB556524A9C730000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000027D867D867DA77DC87DC87DA77D
      867D657D657D447D237D027DE17C9C7300003967396739673967396718631863
      F75EF75EF75ED65AD65AD65AB5569C73DE7B0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF7FFF7FFF7FFF7FFF7FFF7F
      FF7FFF7FFF7FFF7FFF7FFF7FFF7FFF7F00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000014011501140114011401D55A9452
      9452B552615C405C405C4058004C00000000B909B905B905B905B90599059805
      980577057705570556055605140900000000E278E278E274E274E270C270C26C
      C26CA268A264816461606160415400000000A070C270C16CC16CA168A1688164
      816481606060605C405C405C004C000000005601DB01DA01BA01DA019B737B6F
      5A6B9C6B227D017D017D017D405C00000000BA053E023E025E025F025F025E02
      3E021D021C02FC01DB01DA013501000000000279867D867D867DA77DA77D867D
      867D657D447D237D027D017D605C00000000E274C87DA77DA77DA77D867D857D
      657D447D237D227D017DE07C405C000000005701DB01DB01DB01DA019B777B6F
      7B6F9C6F237D227D027D027D606000000000DA053E023E025F025F025F023E02
      3D021D021C02FB01DB01DA01360100000000027D867D867DA77DA77DA77DA77D
      867D657D447D437D027D017D615C00000000E278C87DC87DC87DA77D867D657D
      647D447D237D027D017DE07C405C000000005701FC01FB01FB01FB01BC7B9C73
      9C73BD6F447D447D437D437D616000000000BA051E023E023F025F023F023E02
      1D02FD01FC01DB01BB01BA01360100000000027D867DA77DA87DC87DC87DA77D
      867D857D657D437D227D017D616000000000E07CC77DC77DC77DA67D857D647D
      637D427D217D017DE07CE07C40640000000078011D02FC01FC01FC01DD7FBD77
      9C73DE73657D657D457D647D816400000000FA567D637D639E679E679E677E67
      7D635D635C5F3B5F1A5B1A5B554600000000027D867DA77DC87DC97DC87DA77D
      867D657D657D447D227D017D61600000000074191A161A161A161A161A161916
      F915F815D815B715B6159615F0100000000078011D021D021D021C02DD7FBD77
      BD77DE77867D657D657D657D8164000000005A6BDD7BDE7BDE7FDE7FDE7FDE7B
      DE7BBD779C779B737B6F5A6FB55600000000E17C657D857D867DA77DA77D867D
      657D447D437D227D017DE07C416400000000BA013E023E025F025F025F023E02
      3E021D021D02FC01DB01BB0115010000000098013E023D021D021D02FE7FDE7B
      DE7BDF77A77D867D867D867DA168000000005B6BDE77DF7BDF7BDF7BDF7BFF7B
      DE7BBE77BD739C737B6F7B6BB656000000005A63DE77DF77DF77FF77FF77DF77
      DE77DE73BE739D6F9C6B7C6BD75600000000BA013E023E025F025F025F023E02
      3D021D02FC01FB01DB01BA0115010000000099015E023E023E023D02FE7FDE7B
      DE7BFF77C87DA77DA77DA67DA16C00000000D56E387B387B597F597F597F587B
      387B17771677F572D572D46E315A000000003967BD77DE77DE7BDE7BDE7BDE7B
      BD77BD779C737B6F7B6F5A6BD65600000000FA159D1E9E1EBE1EBE1EBE1E9E1E
      9D1E7D1A7C1A5B1A3B1A1A1A751100000000BA015F025F023E023D02FE7FDE7B
      DE7BFF7BC97DC87DA77DA77DC16C00000000E17C647D657D867D867D867D657D
      657D447D237D027DE07CC07C205C000000003967DE7BDE7BDE7BFF7FFF7FDE7B
      BD77BD779C739C737B6F5A6BD65A00000000596FDD7FDE7FFE7FFE7FFE7FFE7F
      DD7FBD7BBC7B9B777B737A73B55A00000000BA017F025F023E023E02FE7FDE7B
      DE7BFF77C97DC87DA87DA77DC17000000000027D867DA77DA87DC87DC87DA77D
      867D657D647D437D027D017D6160000000005A6BDE7BDE7BFF7FFF7FFF7FDE7B
      DE7BBD779C739C737B6F7B6FD65A000000003967BD77DE7BFF7FFF7FFF7FDE7B
      BD77BD779C737B6F7B6F5A6BB55600000000BA017F025F023E023E06FE7FDE7B
      DE7BFF77C97DC87DA77DA77DC17000000000027DA67DA77DC87DE97DC97DC87D
      A77D867D657D447D227D017D6160000000005A6BDE7BDE7BFF7FFF7FFF7FFF7F
      DE7BBD77BD779C737B6F7B6FF75E000000005A6BDE7BDE7BFF7FFF7FFF7FFF7F
      DE7BBD77BD779C737B6F7B6FB556000000009901DA01BA01BA01BA017A735A6B
      5A6B5B670279E178E178E178A07400000000E27CE278E278E274E274C270C270
      A26CA16C816881646160606041580000000039675A6B5A6B5A6B396739673967
      3967186318631863F75EF75ED65A0000000039675A6B39673967396739671863
      18631863F75EF75ED65AD65AB556000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FF7F9C737B6F7B6F7B6F7B6F7B6F
      7B6F7B6F7B6F7B6F7B6F7B6F7B6F9C73FF7FFF7F9C737B6F7B6F7B6F7B6F7B6F
      7B6F7B6F7B6F7B6F7B6F7B6F7B6F9C73FF7FFF7F9C737B6F7B6F7B6F7B6F7B6F
      7B6F7B6F7B6F7B6F7B6F7B6F7B6F9C73FF7F0000000000000000000000000000
      0000000000000000000000000000000000009C73524ACE39CE39CE39CE39CE39
      CE39CE39CE39CE39CE39CE39CE39524A9C739C73524ACE39CE39CE39CE39CE39
      CE39CE39CE39CE39CE39CE39CE39524A9C739C73524ACE39CE39CE39CE39CE39
      CE39CE39CE39CE39CE39CE39CE39524A9C730000000000000000000000000000
      000000000000000000000000000000000000826CA26CA268A268826882648264
      8264826461606160616061606258CE397B6F2869E17CE27CE278E278E274C274
      C270A26CA26C816861686164415CCE397B6F037B247B04770577057705770473
      E472E472C36EC36EA26EA26E6266CE397B6F5605531D57015701370136366064
      6064F33D1501150115013121F20400000000A170447D447D647D647D647D447D
      447D437D237D227D017DE17C8164CE397B6F7905D429857D867DA77DA77D867D
      867D657D447D237D027D017D6164CE397B6F447BCD7FCF7FD07FF07FF07FCF7F
      CD7FAB7F8A7F877F657F427FA16ECE397B6FF81DF27E544EFD01FD01FD46427D
      227DD952DC01DC01544EB07E952100000000A274647D657D657D657D657D657D
      447D447D437D237D027D017D8164CE397B6F7809FD01D719A67DA77DA77DA77D
      867D657D447D437D027D017D6164CE397B6F447FCD7FCF7FF07FF17FF17FCF7F
      AD7FAB7F897F677F657F427FA16ECE397B6F5801FD3E147F535A1E02FD42437D
      437DD952DD017556B17EFC42F40000000000C274657D657D657D657D657D657D
      657D647D447D237D227D027D8268CE397B6F9809FC01FC01D90DC979C77DA77D
      867D857D657D437D227D017D6164CE397B6F647FEE7FEF7FF17FF37FF17FF07F
      EE7FCC7FAA7FA87F857F827FC172CE397B6F7801FD01BE2A367F315E1E43447D
      447DFA527456D27EBC36BB01150100000000E278867D867D867D867D867D867D
      657D657D457D447D237D227DA268CE397B6F99091C02FC01FC01DB01CB71A77D
      867D657D657D447D227D017D6164CE397B6F627DC77DE77D087E087E087EE77D
      E77DC67DA57D847D627D417DC060CE397B6F79361E3FFF369F5F797FBC7B657D
      647D5A7BF57A9E63BD32DC3A162E00000000E278867D867D877D277EA77D867D
      867D857D657D447D237D227DA26CCE397B6FB9091D02FC01FC01FC01FC01AC59
      657D647D437D227D017DE07C4168CE397B6F027D867D867DA77DA87DA87DA77D
      867D657D447D237D027DE17C415CCE397B6FC178647D857D857D867D867D867D
      867D647D447D237D227D017D406000000000E27CA77DA77DA77DE87D077EA77D
      877D867D657D447D447D237DA270CE397B6FDB093D021D021C02FC01FC019E63
      DE77DE73BD739D6F9C6B7C6BF85ACE397B6F027D867DA77DC87DC97DC87DA77D
      867D657D647D437D027D017D615CCE397B6FC178857D857D867DA67DA67DA77D
      867D657D447D237D227D017D406400000000027DC77DA77DE77DC87DE87DA77D
      A77D867D657D647D447D237DC270CE397B6FDB093E021D021D023D0ABE77DE7F
      BD77BD779C737B6F7B6F5A6BF75ECE397B6F036987698869A869A969A8698869
      67696669456924690365E268614CCE397B6F98421D4B1E43BF6B587F9B7FA67D
      867D597BD47E9D6BBB3EDB42153600000000027DA77D877F877EC97DC87D487E
      A77D867D657D657D447D237DC274CE397B6FFC093E021E027D16DE7BDE7BDE7B
      BD77BD779C739C737B6F5A6BF75ECE397B6FE8186B296B296B296B296B294A25
      4A2529212921081DE818E7186304CE397B6F99011E021F33367F73627F4BA67D
      857D1B537552D27EFD3ABC01360100000000027D697E8A7FE87EC87DC87DA87D
      877D867D657D647D447D237DC274CE397B6FFC053F02BE26DE7BDE7BDE7BDE7B
      DE7BBD779C739C737B6F7B6FF75ECE397B6F08216B2D8C318C318C316B2D4A29
      4A29292529250821E71CE71C630CCE397B6F99015F4B147F955A5F023F47867D
      857DFA561E02764EB17E1D47360100000000027D867D497EA77DA87D687EA77D
      A77D867D657D647D447D237DE278524A9C73FD051F37FE7FDE7BDE7BDE7BDE7B
      DE7BBD77BD779C737B6F7B6F1863524A9C7308218C318C318C318C316B2D6B2D
      4A294A29292508210821E71C630C524A9C733A26D17E764A5F023F023F4B857D
      857DFA561D02FD0156428F7EF72100000000017D027D027D027D027D027D027D
      027DE27CE27CE27CE17CC17CE27C9C73FF7F7D639C779B737B6F7B6F7B6F7B6F
      7B6F5A6B5A6B5A6B3967396739679C73FF7FE71CE71CE71CE71CC618C618A514
      A514A514A5148410630C630C630C9C73DE7BB80595199A0199019901983EC174
      C170554A78017701580154153505000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFF8001000000008001000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0001000000000000FFFF800100000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      C003C003C003C003000100010001000100010001000100010001000100010001
      0001000100010001000100010001000100010001000100010001000100010001
      0001000100010001000100010001000100010001000100010003000300030003
      0003000300030003FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFF
      000000000000C003000000000000000100000000000000010000000000000001
      0000000000000001000000000000000100000000000000010000000000000001
      0000000000000001000000000000000100000000000000010000000000000003
      0000000000000003FFFFFFFFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 136
    Top = 440
  end
  object SaveDialog1: TSaveDialog
    FileName = 'hosts.txt'
    Options = [ofHideReadOnly, ofExtensionDifferent, ofPathMustExist, ofEnableSizing, ofDontAddToRecent]
    OnCanClose = SaveDialog1CanClose
    Left = 168
    Top = 440
  end
end
