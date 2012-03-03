object WINDOW_SETTINGS: TWINDOW_SETTINGS
  Left = 368
  Top = 109
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
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 505
    Height = 473
    ActivePage = TABSHEET_GENERAL
    TabIndex = 0
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
          Images = ImageList2
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
          ItemHeight = 13
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
            Height = 14
            Align = alLeft
            Caption = 'Executable:'
          end
          object LABEL_OFPCWC_DETECTEDVERSION: TLabel
            Left = 365
            Top = 0
            Width = 84
            Height = 14
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
          ItemHeight = 13
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
            Height = 14
            Align = alLeft
            Caption = 'Executable:'
            Transparent = True
          end
          object LABEL_OFPRES_DETECTEDVERSION: TLabel
            Left = 365
            Top = 0
            Width = 84
            Height = 14
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
          ItemHeight = 13
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
            Height = 14
            Align = alLeft
            Caption = 'Executable:'
            Transparent = True
          end
          object LABEL_ARMACWA_DETECTEDVERSION: TLabel
            Left = 365
            Top = 0
            Width = 84
            Height = 14
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
        Caption = 'Operation Flashpoint: Cold War Crisis'
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = CHECKBOX_OFPCWCClick
      end
      object CHECKBOX_OFPRES: TCheckBox
        Left = 8
        Top = 136
        Width = 177
        Height = 17
        Caption = 'Operation Flashpoint: Resistance'
        Checked = True
        State = cbChecked
        TabOrder = 2
        OnClick = CHECKBOX_OFPRESClick
      end
      object CHECKBOX_ARMACWA: TCheckBox
        Left = 8
        Top = 264
        Width = 135
        Height = 17
        Caption = 'ArmA: Cold War Assault'
        Checked = True
        State = cbChecked
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
          TabOrder = 13
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
          TabOrder = 5
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
          Left = 360
          Top = 184
          Width = 65
          Height = 17
          Caption = ' -nomap'
          Checked = True
          State = cbChecked
          TabOrder = 4
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
          TabOrder = 11
          OnClick = BUTTON_NEWCONFIGURATION_ADDClick
        end
        object LISTBOX_MODFOLDERS_SELECTED: TListBox
          Left = 136
          Top = 40
          Width = 121
          Height = 161
          ItemHeight = 13
          TabOrder = 6
        end
        object BUTTON_NEWCONFIGURATION_MOVELEFT: TButton
          Left = 136
          Top = 16
          Width = 33
          Height = 25
          Caption = '<'
          TabOrder = 8
          OnClick = BUTTON_NEWCONFIGURATION_MOVELEFTClick
        end
        object BUTTON_NEWCONFIGURATION_MOVERIGHT: TButton
          Left = 96
          Top = 16
          Width = 33
          Height = 25
          Caption = '>'
          TabOrder = 7
          OnClick = BUTTON_NEWCONFIGURATION_MOVERIGHTClick
        end
        object BUTTON_NEWCONFIGURATION_UP: TButton
          Left = 168
          Top = 16
          Width = 45
          Height = 25
          Caption = 'Up'
          TabOrder = 9
          OnClick = BUTTON_NEWCONFIGURATION_UPClick
        end
        object BUTTON_NEWCONFIGURATION_DOWN: TButton
          Left = 212
          Top = 16
          Width = 45
          Height = 25
          Caption = 'Down'
          TabOrder = 10
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
          TabOrder = 14
          Visible = False
          OnClick = BUTTON_EDITCONFIGURATION_CANCELClick
        end
        object BUTTON_NEWCONFIGURATION_CLEAR: TButton
          Left = 370
          Top = 16
          Width = 99
          Height = 33
          Caption = 'Clear'
          TabOrder = 12
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
      object ListBox1: TListBox
        Left = 8
        Top = 8
        Width = 233
        Height = 353
        DragMode = dmAutomatic
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 0
      end
      object RADIOBUTTON_SERVERS_SHOW_ADDRESS: TRadioButton
        Left = 256
        Top = 424
        Width = 233
        Height = 17
        Caption = 'Show addresses'
        TabOrder = 1
        OnClick = RADIOBUTTON_SERVERS_SHOW_ADDRESSClick
      end
      object RADIOBUTTON_SERVERS_SHOW_NAME: TRadioButton
        Left = 256
        Top = 408
        Width = 233
        Height = 17
        Caption = 'Show names'
        Checked = True
        TabOrder = 2
        TabStop = True
        OnClick = RADIOBUTTON_SERVERS_SHOW_NAMEClick
      end
      object TreeView1: TTreeView
        Left = 256
        Top = 8
        Width = 233
        Height = 393
        Images = ImageList1
        Indent = 19
        PopupMenu = POPUPMENU_SERVERLISTEDITOR
        ReadOnly = True
        RightClickSelect = True
        TabOrder = 3
        OnContextPopup = TreeView1ContextPopup
        OnDragDrop = TreeView1DragDrop
        OnDragOver = TreeView1DragOver
        Items.Data = {
          0400000022000000010000000100000000000000FFFFFFFF0000000000000000
          094661766F726974657320000000020000000200000000000000FFFFFFFF0000
          000000000000075761746368656423000000030000000300000000000000FFFF
          FFFF00000000000000000A50657273697374656E742000000004000000040000
          0000000000FFFFFFFF000000000000000007426C6F636B6564}
      end
      object GROUPBOX_SERVERS_ADD: TGroupBox
        Left = 8
        Top = 368
        Width = 233
        Height = 73
        Caption = 'Add Server  IP[:Port]'
        TabOrder = 4
        object Edit1: TEdit
          Left = 8
          Top = 16
          Width = 217
          Height = 21
          TabOrder = 0
        end
        object BUTTON_SERVERS_ADD: TButton
          Left = 8
          Top = 40
          Width = 217
          Height = 25
          Caption = 'Add'
          TabOrder = 1
          OnClick = BUTTON_SERVERS_ADDClick
        end
      end
    end
    object TABSHEET_NOTIFICATIONS: TTabSheet
      Caption = 'Notifications'
      ImageIndex = 3
      OnShow = TABSHEET_NOTIFICATIONSShow
      object LABEL_AUDIOFILE: TLabel
        Left = 190
        Top = 296
        Width = 75
        Height = 13
        Caption = 'Audio file (mp3):'
        Transparent = True
      end
      object LABEL_NOTIFICATION_NAME: TLabel
        Left = 6
        Top = 296
        Width = 31
        Height = 13
        Caption = 'Name:'
        Transparent = True
      end
      object LabelMinutes: TLabel
        Left = 54
        Top = 344
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
        Top = 344
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
        Top = 344
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
      object LABEL_VOLUME: TLabel
        Left = 54
        Top = 372
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
        Left = 182
        Top = 382
        Width = 16
        Height = 13
        Caption = 'To:'
        Transparent = True
      end
      object LABEL_AUDIO_FROM: TLabel
        Left = 182
        Top = 338
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
        Top = 358
        Width = 89
        Height = 17
        Caption = 'Repeat'
        TabOrder = 20
      end
      object TrackBar1: TTrackBar
        Left = 0
        Top = 388
        Width = 161
        Height = 37
        BorderWidth = 5
        Ctl3D = True
        Max = 100
        Orientation = trHorizontal
        ParentCtl3D = False
        Frequency = 10
        Position = 100
        SelEnd = 0
        SelStart = 0
        TabOrder = 12
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar1Change
      end
      object PLAY: TBitBtn
        Left = 6
        Top = 344
        Width = 41
        Height = 42
        TabOrder = 11
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
        Left = 6
        Top = 344
        Width = 41
        Height = 41
        TabOrder = 13
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
      object EDIT_SONGEND_SEC: TEdit
        Left = 206
        Top = 400
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 18
        Text = '0'
        OnChange = EDIT_SONGEND_SECChange
      end
      object EDIT_SONGEND_MIN: TEdit
        Left = 182
        Top = 400
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 17
        Text = '0'
        OnChange = EDIT_SONGEND_MINChange
      end
      object EDIT_SONGSTART_MILL: TEdit
        Left = 230
        Top = 356
        Width = 28
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 3
        ParentBiDiMode = False
        TabOrder = 16
        Text = '0'
        OnChange = EDIT_SONGSTART_MILLChange
      end
      object EDIT_SONGSTART_SEC: TEdit
        Left = 206
        Top = 356
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 15
        Text = '0'
        OnChange = EDIT_SONGSTART_SECChange
      end
      object EDIT_SONGSTART_MIN: TEdit
        Left = 182
        Top = 356
        Width = 21
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 2
        ParentBiDiMode = False
        TabOrder = 14
        Text = '0'
        OnChange = EDIT_SONGSTART_MINChange
      end
      object EDIT_SONGEND_MILL: TEdit
        Left = 230
        Top = 400
        Width = 28
        Height = 21
        BiDiMode = bdRightToLeft
        MaxLength = 3
        ParentBiDiMode = False
        TabOrder = 19
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
        TabOrder = 21
      end
      object BUTTON_BROWSE: TButton
        Left = 371
        Top = 344
        Width = 118
        Height = 41
        Caption = 'Browse ...'
        TabOrder = 10
        OnClick = BUTTON_BROWSEClick
      end
      object EDIT_NOTIFICATION_FILE: TEdit
        Left = 186
        Top = 312
        Width = 303
        Height = 21
        ReadOnly = True
        TabOrder = 9
        OnChange = EDIT_NOTIFICATION_FILEChange
        OnKeyUp = EDIT_NOTIFICATION_FILEKeyUp
      end
      object EDIT_NOTIFICATION_NAME: TEdit
        Left = 6
        Top = 312
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
    end
    object TABSHEET_CHATSETTINGS: TTabSheet
      Caption = 'Chat'
      ImageIndex = 4
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
          ItemHeight = 13
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
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'OFP:R (FLASHPOINTRESISTANCE.EXE)|FLASHPOINTRESISTANCE.EXE'
    Options = [ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofDontAddToRecent]
    OptionsEx = [ofExNoPlacesBar]
    OnCanClose = OpenDialog1CanClose
    Left = 424
  end
  object OpenDialog2: TOpenDialog
    Filter = '*.mp3|*.mp3'
    Options = [ofReadOnly, ofHideReadOnly, ofNoNetworkButton, ofEnableSizing, ofDontAddToRecent]
    OnCanClose = OpenDialog2CanClose
    Left = 456
  end
  object MP3Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = MP3TimerTimer
    Left = 392
  end
  object ImageList1: TImageList
    Left = 304
    Top = 408
    Bitmap = {
      494C010105000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E7E7FF00ADAEFF005279CE003159B5003151C6004A69DE00A5A6EF00D6D7
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDBE
      D6005251A50029287B003159AD004269BD004259CE003959CE0031287B003128
      7B00A5A6A5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B69FF003928
      CE001808DE002110E7005A41F7006351FF005A49EF006351FF002918EF003920
      FF002108B5007359FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000BDBED6003120CE001808
      AD002920F7002110E7001800B5005A41F7003928D6005241E7000800CE001000
      D6003118BD001800AD00B5B6AD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DEDFFF0063619C001010AD000000
      9C000810AD001820BD005A51CE00E7DFFF000000000000000000739EB5002149
      63002118B5001010AD0031306B00DED7FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C6CFFF0021285A000808A5001010
      AD000808AD0000009C00292094005251C6000000000000000000000000007BA6
      C600000094000808A50029205A00A5A6DE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007396E7000010630008006B003130
      94006369AD0018205A000808B5000808B5003951AD0000000000000000000000
      00005249AD0018187B0000007B004A59CE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004A69BD0008287B0000005A005A51
      BD0000000000525994001008BD000800B50008207B004A59BD00000000000000
      00004A49AD0000006300000884003141BD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000005251EF000000940029189C004A38
      BD0000000000000000006369E70008108C001000C6002108D6005249AD00E7DF
      FF005A49D60008008400001894002941BD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B79FF000008A500100084005241
      C6000000000000000000000000006369E7001808D6001800CE00312884007369
      C6003120AD0021109C00081894004259D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BDBEFF0039387B002920C6002110
      BD007B9EB5000000000000000000000000007369CE004A38A5002920BD002928
      C6002118C6002118C60031307300A5A6EF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DEDFFF00524994006B61FF005249
      EF002149630084AEC6000000000000000000EFDFFF008471DE004241D6004A49
      DE005A59FF004241E70052519C00D6D7FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D6DFB5005A51CE007B71
      EF007369FF003930CE005249A5005249A5006351B500393094003938D6006361
      F7007369E7005A59D600ADB6B500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008479F7007369
      E700ADA6FF00948EFF008C86DE008C79DE007369CE00948EEF009496FF008C8E
      FF006B69E7008486FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDB6
      C6006351A5009C8EDE00ADBEFF00A5B6FF00A5C7FF0094B6F7009486D6008C86
      D600A59ECE000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7E7FF00AD9EEF005A69CE005261C6005269AD005271B500948ED600DED7
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007396
      CE000886A50000000000000000000000000000000000000000000000000029AE
      CE007396CE000000000000000000000000000000000094868400D6CFCE00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000007BAEBD0073AEBD005A96
      AD00529EBD004296B500429EC6002986AD002986B5002986B5003986B5003186
      AD004286AD003979AD004A86AD00000000000000000000000000C6C3C600ADAE
      AD009C9E9C0084868400848284007B797B0073757300848284007B797B008C8E
      8C00A5A2A500BDBABD0000000000000000000000000000000000000000006379
      B5004ACFEF00189EBD0000000000000000000000000000000000108EAD004AC7
      E7007396CE00000000000000000000000000C6AEB500B59EA5007B717300DECF
      D600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000007BAEBD00B5EFFF00ADE7
      FF00ADF7FF00ADF7FF00A5F7FF00A5FFFF009CF7FF008CE7FF009CE7FF008CDF
      FF009CD7FF0094D7FF00528EB5000000000000000000BDBEBD007B797B008486
      8400ADAEAD00ADAEAD00A5A2A500949294009C9A9C00C6C7C600D6D7D600CECF
      CE00A5A6A5008C8E8C00C6C3C6000000000000000000000000000000000073AE
      C60021F7FF0010EFFF0000A6CE0000AED60000B6DE0000A6CE0010E7FF0008E7
      FF0063A6BD00000000000000000000000000E7E7E700D6D7D600B5B6B5007B79
      7B00BDC7C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000005A9EB500A5EFFF0084CF
      EF005ABEDE0063BEE70052BEE7005AC7F7005AC7F7004AB6E7004AA6DE0042A6
      D6006BBEEF008CDFFF002971A5000000000000000000E7E7E700ADAEAD00C6C3
      C600EFEBEF00CECFCE008C8E8C005255520073717300BDBABD00F7F3F7000000
      0000CECFCE00B5B2B500DEDFDE000000000000000000000000000000000084BE
      D60000C7EF0018EFFF0029E7FF0000B6DE0008C7EF0008C7EF0018F7FF0000DF
      FF004A869C00000000000000000000000000FFFFFF00DED7D600BDBEC600ADAE
      B50073717B00C6CFCE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000006BAEBD00ADF7FF008CDF
      F7006BC7EF0084DFFF008CF7FF0084EFFF007BE7FF0084EFFF0063C7F70052B6
      E7006BBEEF009CEFFF003179A5000000000000000000F7F3F700C6C7C600B5B6
      B500BDBEBD00A5A2A5007B797B005A595A006B6D6B0094969400BDBABD00D6D3
      D600C6C3C600C6C7C600EFEFEF00000000000000000000000000000000000000
      0000009ED60008CFFF0018EFFF0010DFFF0008DFFF0010E7FF0000C7FF0008CF
      FF0000000000000000000000000000000000FFFFFF00FFFFFF00CED7D600BDCF
      C600ADAEAD0073717300D6D7CE00BDB6B500B5AEA500948E8400847973009C9E
      9400CECFC600FFFFFF00FFFFFF00FFFFFF00000000006BB6CE009CEFFF0084D7
      F70063C7E7006BCFF7006BDFFF00319ECE001086B5006BD7FF0042AEDE0042AE
      DE005AB6E70084E7FF003186B500000000000000000000000000C6C7C6009496
      94009C9E9C00949294007B797B006B696B00636563007B7D7B009C9E9C00B5B2
      B500A5A6A500B5B6B50000000000000000000000000000000000000000000000
      000000AEDE0021DFFF0000CFFF0000CFFF0000C7FF0000D7FF0029E7FF0000AE
      E70000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00DEEF
      E700ADAEA500848E84008C8684009C968C00B5A6A500E7DFD600E7DFD600ADAE
      A500949E8C00B5B6A500DEE7D600FFFFFF00000000007BC7E7009CF7FF008CDF
      FF0073D7FF007BDFFF007BEFFF0039A6D600218EBD0084EFFF005AC7F7005ABE
      EF0063BEEF008CE7FF003996BD00000000000000000000000000C6C3C600BDBA
      BD00E7E3E700CECBCE00949694007371730094929400C6C3C600F7F3F700FFFB
      FF00C6C7C600BDBEBD0000000000000000000000000000000000000000004A96
      BD0000BEE70000BEE70039DFFF0031D7FF0031DFFF0031D7FF0000D7F70000B6
      DE004296BD00000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00DED7CE008C867B00AD968C00FFE7DE00FFDFD600FFE7D600EFD7C600E7D7
      C600CECFBD00A59E8C00A5AE9400FFFFFF000000000084C7D600ADEFFF0084CF
      E7007BCFE70084CFEF007BD7F70063B6D60052AED6008CDFFF006BBEE7005AAE
      D6006BB6DE0094E7FF004A8EAD00000000000000000000000000C6C3C600BDBE
      BD00DEDFDE00BDBEBD00848684006B6D6B0073757300ADAEAD00EFEBEF00FFFB
      FF00CECBCE00C6C3C600000000000000000000000000000000003986B5006BB6
      DE0000CFF70018E7FF0021C7F70029CFFF0029D7FF0029CFFF0000CFF70018EF
      FF005AAED600398EB5000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CEC7BD00A5968C00FFE7DE00FFDFD600FFDFD600FFE7D600DECFBD00E7D7
      C600EFEFD600C6BEAD009C9E8C00C6CFB5000000000073B6CE00BDFFFF0094DF
      F70094DFFF009CEFFF008CDFFF009CEFFF008CE7FF0094E7FF0084D7FF006BBE
      E70084CFF700ADF7FF00428EAD00000000000000000000000000C6C3C6009C9E
      9C009C9E9C0084868400636163004A4D4A005A595A006B6D6B008C8E8C00ADAA
      AD00A5A2A500BDBEBD00000000000000000084BEFF004A86CE004ABEEF006BD7
      FF0042E7FF0031DFF7006BDFFF0063D7FF006BDFFF005ACFF70029D7F70031DF
      FF006BDFFF004ABEEF00528ED6007BBEFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CEB6AD00BDA69C00FFDFD600FFD7CE00FFD7C600FFD7C600F7D7C600EFD7
      BD00DED7BD00EFDFCE00ADA69400B5AE9C0000000000A5C7CE00C6EFF700DEFF
      FF00CEF7FF00CEF7FF00C6F7FF00D6FFFF00D6FFFF00C6EFFF00D6FFFF00BDEF
      FF00C6E7FF00C6EFFF007396AD00000000000000000000000000C6C7C600B5B6
      B500CECBCE00BDBABD0094969400737573008C8A8C00ADAAAD00D6D7D600E7E7
      E700C6C3C600C6C7C60000000000000000005286CE005A96DE005AC7F70063D7
      FF0031D7F70029D7EF006BDFFF0063D7FF005ACFF70073EFFF0042EFFF0039E7
      FF005ACFFF0063D7FF00639EE7003971BD00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF009C867B00E7CFC600F7D7C600FFDFD600EFC7B500FFD7C600EFCFBD00EFCF
      BD00FFEFDE00EFDFCE00DED7C6008C8E7B0000000000A5CFCE007B9EA500638E
      9400638E9C0094BEC60094C7D6007BA6B50073A6B5008CB6CE0094BECE004269
      7B004A71840052798C008CAEC600000000000000000000000000BDBEBD00B5B2
      B500CECFCE00C6C3C600949694006B6D6B0084868400BDBABD00EFEFEF00F7F7
      F700C6C7C600BDBABD0000000000000000009CB6E700ADCFF700A5B6D600949E
      BD00738EB5007B96C6007BAEEF00ADDFFF00A5DFFF007BB6F7006B8EB5006B96
      BD006B86A50094A6C60094B6E70084A6D600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0094797B00EFD7CE00EFCFBD00E7C7B500FFDFCE00FFD7CE00F7D7C600FFE7
      D600FFF7EF00EFDFD600E7DFD6009C968C000000000000000000ADB6B500D6DF
      D600848E8C000000000000000000000000000000000000000000000000006B71
      7B00B5BEC600848E8C0000000000000000000000000000000000CECBCE00C6C7
      C600DEDFDE00D6D7D600BDBABD009C9A9C00ADAAAD00D6D7D600F7F7F700FFFB
      FF00D6D3D600C6C3C60000000000000000000000000000000000000000000000
      000000000000BDDFFF006B9EDE009CCFFF00ADE7FF006396D600A5C7EF000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6AEAD00BDA69C00F7D7CE00F7CFC600F7CFC600FFE7D600FFE7D600F7D7
      CE00F7E7D600FFFFF700C6BEB5009C968C0000000000000000009CA69C00CED7
      D6008C9694000000000000000000000000000000000000000000000000008C96
      9400ADAEB5008C8E940000000000000000000000000000000000DEDBDE00DEDF
      DE00EFEFEF00EFEFEF00F7F3F700E7E7E700E7E7E700F7F7F700F7F7F700F7F7
      F700E7E3E700DEDBDE0000000000000000000000000000000000000000000000
      000000000000000000006396CE00ADD7FF00ADD7FF00638ECE00000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00DED7CE008C867B00CEC7B500FFFFF700F7E7DE00F7E7DE00EFE7DE00FFFF
      F700FFFFFF00F7EFEF009C969C00C6C7CE000000000000000000DEDFD600B5B6
      B500BDBEB500BDB6B50000000000000000000000000000000000ADA6A500B5AE
      AD0094969400DED7DE0000000000000000000000000000000000E7E3E700E7E3
      E700DEDBDE00D6D3D600DEDFDE00DEDBDE00DEDFDE00DEDFDE00D6D3D600DEDB
      DE00DEDFDE00E7E3E70000000000000000000000000000000000000000000000
      0000000000000000000084AEEF0094BEFF008CB6F700739EDE00000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00C6BEB5009C8E8400E7D7CE00FFEFE700FFFFF700FFF7EF00FFFF
      FF00FFFFFF00948E8C00ADAEAD00FFFFFF00000000000000000000000000BDBE
      BD00CECFC600B5AEAD00BDBEB500948E8C0094968C00ADA6A500ADA6A500ADA6
      A500ADA6A500000000000000000000000000000000000000000000000000F7F3
      F700E7E3E700CECFCE00D6D7D600CECFCE00D6D7D600DEDBDE00D6D3D600E7E3
      E700F7F3F7000000000000000000000000000000000000000000000000000000
      00000000000000000000D6D7FF00949EBD00A5AECE00C6CFF700000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF009CA69C00A5AE9C00A5AEA500E7EFE700E7E7E700ADB6
      B5009CA6AD009CA6AD00FFFFFF00FFFFFF00000000000000000000000000E7E7
      E700B5BEB500BDBEBD00BDBEBD00DEDFD600DED7D600C6BEBD00B5B6B500A59E
      9C00E7E7E7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000848EAD007B86AD0000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00C6C7BD00ADB6A5007B867300848E8C00ADB6
      B500B5BEC600FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      000000000000D6D7D600ADA6A500BDBEBD00ADA6A500CEC7C600C6C7C6000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000F00F000000000000E007000000000000
      C003000000000000800100000000000000C000000000000000E0000000000000
      007000000000000008300000000000000C000000000000000E00000000000000
      070000000000000003000000000000008001000000000000C003000000000000
      E007000000000000F00F000000000000FFFFE7E780008001C003E3C700008001
      8001E007000080018011E007000080018001F00F00008001C003F00F00008001
      C003E00700008001C003C00300008001C003000000008001C003000000008001
      C00300000000C7E3C003F81F0000C7E3C003FC3F0000C3C3C003FC3F0000E007
      E007FC3F0000E007FFFFFE7F0000F81F00000000000000000000000000000000
      000000000000}
  end
  object POPUPMENU_SERVERLISTEDITOR: TPopupMenu
    Left = 336
    Top = 408
    object MENUITEM_POPUP_SERVERLISTEDITOR_REMOVE: TMenuItem
      Caption = 'Remove'
      OnClick = MENUITEM_POPUP_SERVERLISTEDITOR_REMOVEClick
    end
  end
  object ImageList2: TImageList
    Left = 272
    Top = 408
    Bitmap = {
      494C010108000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A5420000AD420000A5420000A542
      0000A5420000ADB5B500A5A5A500A5A5A500ADADA5000818BD000010BD000010
      BD000010B50000009C000000000000000000CE6B1000CE6B0800CE6B0800CE6B
      0800CE6B0800CE630800C6630800C6630800BD5A0800BD5A0800BD520800B552
      0800B5520800A542100000000000000000001039F7001039F7001039EF001039
      EF001039E7001031E7001031DE001031DE001029D6001029CE000821CE000818
      C6000818C6000810AD0000000000000000000029E7001031E7000831DE000831
      DE000829D6000829D6000821CE000821CE000821C6000018C6000018BD000010
      BD000010BD0000009C000000000000000000B5520000DE730000D6730000D66B
      0000D6730000DEE7E700DEDEDE00D6D6D600E7E7D600104AFF000842FF000842
      FF000842FF000010BD000000000000000000D66B0800F78C0000F78C0000F794
      0000FF940000FF940000F7940000F78C0000EF840000E7840000E77B0000DE73
      0000D6730000AD4A000000000000000000001042F7003163FF003163FF003163
      FF00396BFF00396BFF003163FF003163FF00295AFF002152FF00184AFF001042
      FF000842FF000018BD0000000000000000001039EF004273FF00396BFF00396B
      FF00396BFF003163FF002963FF00295AFF002152FF00184AFF00104AFF000842
      FF000039FF000010BD000000000000000000BD520000DE730000DE730000DE73
      0000D6730000DEE7EF00DEDEDE00DEDEDE00E7E7DE00184AFF00104AFF001042
      FF001042FF000018C6000000000000000000D6730800F78C0000F78C0000FF94
      0000FF940000FF940000F78C0000EF8C0000EF840000E7840000DE7B0000DE73
      0000D6730000B54A000000000000000000001042FF003163FF003163FF00396B
      FF00396BFF00396BFF00396BFF003163FF00295AFF002152FF001852FF001042
      FF000842FF000818BD0000000000000000001039F7004273FF004273FF004273
      FF00396BFF003163FF00295AFF00215AFF002152FF00184AFF001042FF000842
      FF000039FF000010BD000000000000000000BD520000E77B0000DE7B0000DE7B
      0000DE7B0000E7EFF700E7E7E700E7E7E700EFEFDE002152FF002152FF001852
      FF001852FF000818C6000000000000000000D66B0800F7840000F78C0000FF8C
      0000FF940000FF8C0000F78C0000EF840000EF7B0000E77B0000DE730000DE6B
      0000D66B0000B54A000000000000000000001042FF003163FF00396BFF00426B
      FF004273FF004273FF00396BFF003163FF002963FF00295AFF001852FF00104A
      FF000842FF000818C60000000000000000000039FF003973FF003973FF003973
      FF00316BFF002963FF00215AFF00185AFF001052FF00084AFF000842FF000039
      FF000039FF000010CE000000000000000000C65A0000EF840000E77B0000E77B
      0000E77B0000EFF7FF00EFEFEF00E7E7E700F7F7E700295AFF00295AFF002952
      FF00215AFF000821CE000000000000000000D6BDAD00EFDEC600EFDEC600F7E7
      CE00F7E7CE00F7E7CE00F7DECE00EFDEC600EFD6C600E7D6BD00DECEBD00D6C6
      B500D6C6B500AD948C0000000000000000001042FF003163FF00396BFF004273
      FF004A73FF004273FF00396BFF003163FF00295AFF00295AFF002152FF00104A
      FF000842FF000818C6000000000000000000A55A3100D6842900D6842900D684
      2900D6842900D6842900CE842900CE7B2900C67B2900C6732900BD6B2900B56B
      2900B5632900843921000000000000000000C65A0000EF840000EF840000EF84
      0000E7840000EFF7FF00EFEFEF00EFEFEF00F7F7EF003163FF00295AFF00295A
      FF00295AFF000821CE000000000000000000D6D6D600EFF7F700F7F7F700F7F7
      FF00F7F7FF00F7F7FF00F7F7F700F7F7F700EFEFEF00E7E7EF00DEE7E700DEDE
      DE00D6D6DE00ADADAD0000000000000000000839FF00295AFF002963FF003163
      FF00396BFF00396BFF003163FF00295AFF002152FF001852FF00104AFF000842
      FF000039FF000810CE000000000000000000D66B0000F78C0000F78C0000FF94
      0000FF940000FF940000F78C0000F78C0000EF840000EF840000E77B0000DE73
      0000DE6B0000AD4200000000000000000000C6630000F78C0000EF8C0000EF84
      0000EF840000F7FFFF00F7F7F700F7F7F700FFF7EF00396BFF003163FF003163
      FF003163FF000829D6000000000000000000DED6D600F7F7EF00FFF7F700FFF7
      F700FFF7F700FFF7F700FFFFF700F7F7F700F7EFEF00EFEFE700E7E7E700DEDE
      DE00DEDED600B5ADAD000000000000000000D6D6C600F7F7EF00FFF7EF00FFF7
      EF00FFFFEF00FFFFEF00FFF7EF00F7F7EF00F7F7E700F7EFE700EFE7DE00E7E7
      D600E7DED600BDB5AD000000000000000000D66B0000F78C0000F78C0000FF94
      0000FF940000FF940000F78C0000EF8C0000EF840000E77B0000DE7B0000DE73
      0000D66B0000AD4200000000000000000000CE630000F7940000F78C0000F78C
      0000EF8C0000F7FFFF00F7F7F700F7F7F700FFFFEF004273FF00396BFF00396B
      FF00316BFF000829DE000000000000000000ADB5DE00C6CEF700C6CEF700CED6
      FF00CED6FF00CED6FF00C6D6F700C6CEF700BDC6EF00B5C6EF00ADBDE700ADB5
      E700A5B5DE008C8CB5000000000000000000CECECE00EFEFEF00F7F7EF00F7F7
      F700F7F7F700F7F7F700F7F7F700EFEFEF00EFEFEF00E7E7E700DEDEDE00DEDE
      DE00D6D6D600B5B5AD000000000000000000D67B2900EFA53900F7A53900F7AD
      3900F7AD3900F7AD3900F7A53900EFA53900EF9C3100E79C3100DE943100DE8C
      3100D6843100AD5A21000000000000000000D66B0000FF940000FF940000F78C
      0000EF8C0000F7FFFF00F7F7F700F7F7F700FFFFF7004A73FF004273FF00396B
      FF00396BFF000831DE0000000000000000000839FF00215AFF00295AFF003163
      FF003163FF003163FF00295AFF00295AFF002152FF00184AFF001042FF000039
      FF000031FF000008BD000000000000000000CECECE00F7F7F700F7F7F700F7F7
      F700FFFFFF00FFFFFF00F7F7F700EFEFEF00EFEFEF00E7E7E700E7E7E700DEDE
      DE00D6D6D600B5B5B5000000000000000000CED6DE00EFF7FF00F7F7FF00F7FF
      FF00F7FFFF00F7FFFF00F7FFFF00EFF7FF00EFEFF700E7EFF700DEE7EF00DEDE
      E700D6DEE700ADADB5000000000000000000D66B0000FF9C0000FF940000F78C
      0000F78C0000F7FFFF00F7F7F700F7F7F700FFFFEF004A73FF004273FF00426B
      FF00396BFF000831E70000000000000000001042FF003163FF00396BFF00426B
      FF004273FF004273FF00396BFF003163FF00295AFF00215AFF001852FF001042
      FF000842FF000818C6000000000000000000D6D6D600F7F7F700F7F7F700FFFF
      FF00FFFFFF00FFFFFF00F7F7F700F7F7F700EFEFEF00E7E7E700E7E7E700DEDE
      DE00DEDEDE00B5B5B5000000000000000000CECECE00EFEFEF00F7F7F700FFFF
      FF00FFFFFF00FFFFFF00F7F7F700EFEFEF00EFEFEF00E7E7E700DEDEDE00DEDE
      DE00D6D6D600ADADAD000000000000000000D66B0000FF9C0000FF940000F78C
      0000F78C0800F7FFFF00F7F7F700F7F7F700FFFFEF004A73FF004273FF00396B
      FF00396BFF000831E70000000000000000001042FF00316BFF00396BFF004273
      FF004A7BFF004A73FF004273FF00396BFF003163FF00295AFF002152FF00104A
      FF000842FF000818C6000000000000000000D6D6D600F7F7F700F7F7F700FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00F7F7F700EFEFEF00EFEFEF00E7E7E700DEDE
      DE00DEDEDE00BDBDBD000000000000000000D6D6D600F7F7F700F7F7F700FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00F7F7F700EFEFEF00EFEFEF00E7E7E700DEDE
      DE00DEDEDE00ADADAD000000000000000000CE630000D6730000D66B0000D66B
      0000D66B0000D6DEE700D6D6D600D6D6D600DED6CE001042F7000839F7000839
      F7000839F7000029EF0000000000000000001039FF001039F7001039F7001039
      EF001039EF001031E7001031E7001029DE000829DE000821D6000821CE000818
      C6000018C6000810B5000000000000000000CECECE00D6D6D600D6D6D600D6D6
      D600CECECE00CECECE00CECECE00CECECE00C6C6C600C6C6C600C6C6C600BDBD
      BD00BDBDBD00B5B5B5000000000000000000CECECE00D6D6D600CECECE00CECE
      CE00CECECE00CECECE00C6C6C600C6C6C600C6C6C600BDBDBD00BDBDBD00B5B5
      B500B5B5B500ADADAD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00E7E7E700DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00E7E7E700FFFFFF00FFFFFF00E7E7E700DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00E7E7E700FFFFFF00FFFFFF00E7E7E700DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00E7E7E700FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7E7E70094949400737373007373
      7300737373007373730073737300737373007373730073737300737373007373
      7300737373007373730094949400E7E7E700E7E7E70094949400737373007373
      7300737373007373730073737300737373007373730073737300737373007373
      7300737373007373730094949400E7E7E700E7E7E70094949400737373007373
      7300737373007373730073737300737373007373730073737300737373007373
      7300737373007373730094949400E7E7E7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001021DE001029DE001029D6001029
      D6001021D6001021CE001021CE001021CE001021CE000818C6000818C6000818
      C6000818C6001018B50073737300DEDEDE00424AD6000839FF001039FF001039
      F7001039F7001039EF001031EF001031E7001029DE001029DE000821D6000818
      D6000818CE000810BD0073737300DEDEDE0018C6F70021CEF70021C6EF0029C6
      EF0029C6EF0029C6EF0021C6E70021BDE70021BDE70018B5DE0018B5DE0010AD
      DE0010ADDE00109CCE0073737300DEDEDE00B55208009C523900BD520000BD52
      0000BD4A0000B58C6B000018CE000018CE009C7B7B00AD420000AD420000AD42
      00008C4A42009439080000000000000000000829E7002152FF002152FF00215A
      FF00215AFF00215AFF002152FF002152FF001852FF00184AFF00104AFF000842
      FF000839FF000821CE0073737300DEDEDE00CE5A0800A57352002963FF003163
      FF00396BFF00396BFF003163FF003163FF00295AFF002152FF00184AFF001042
      FF000842FF000818CE0073737300DEDEDE0021D6F7006BF7FF007BF7FF0084F7
      FF0084FFFF0084FFFF007BF7FF006BF7FF005AEFFF0052E7FF0039E7FF0029DE
      FF0010D6FF0008ADDE0073737300DEDEDE00C67B390094BDFF00A5949C00EF7B
      0000EF7B0000EFBD8C001052FF00104AFF00CEB5A500E7730000E7730000A594
      9C0084ADFF00AD63420000000000000000001029EF00215AFF00295AFF00295A
      FF00295AFF00295AFF00295AFF002152FF002152FF001852FF00184AFF001042
      FF000842FF000821CE0073737300DEDEDE00C65A1000EF7B0000BD733100316B
      FF00396BFF00396BFF00396BFF003163FF00295AFF002152FF001852FF001042
      FF000842FF000818CE0073737300DEDEDE0021D6FF006BF7FF007BF7FF0084FF
      FF008CFFFF008CFFFF007BF7FF006BEFFF005AEFFF004AE7FF0039DEFF0029DE
      FF0010D6FF0008ADDE0073737300DEDEDE00C6520000EFBD7B00A5C6FF009C94
      B500F7840000EFBD84001852FF001852FF00CEB5A500EF730000AD9CAD008CAD
      FF00E7BD8400A539000000000000000000001031EF00295AFF00295AFF00295A
      FF00295AFF00295AFF00295AFF00295AFF00215AFF002152FF00184AFF00104A
      FF001042FF001021D60073737300DEDEDE00C6631000E77B0000E77B0000CE73
      18004A73F7003973FF00396BFF003163FF002963FF00295AFF001852FF00104A
      FF000842FF000818CE0073737300DEDEDE0021DEFF0073FFFF007BFFFF008CFF
      FF009CFFFF008CFFFF0084FFFF0073FFFF0063F7FF0052EFFF0042EFFF0029E7
      FF0010E7FF0008B5E70073737300DEDEDE00C65A0000EF7B0000F7AD5200B5CE
      FF008C8CBD00F7C684002152FF002152FF00D6BDA500A59CAD0094B5FF00E7AD
      6B00DE6B0000AD42000000000000000000001039F7003163FF003163FF003163
      FF003163FF003163FF003163FF00295AFF00295AFF002952FF002152FF00184A
      FF00104AFF001029D60073737300DEDEDE00CE631000E7840000E77B0000E77B
      0000DE7300005A73E700396BFF003163FF00295AFF00295AFF002152FF00104A
      FF000842FF000818CE0073737300DEDEDE00105AFF003973FF00397BFF004284
      FF004284FF004284FF00397BFF00397BFF003173FF00296BFF002163FF00105A
      FF000852FF000031C60073737300DEDEDE00CE9C6B00F7C67B00FFBD6B00FFE7
      BD00CEDEFF00E7EFF700295AFF00215AFF00D6D6F700ADBDF700F7E7C600EFAD
      6300E7B57300B5845A0000000000000000001039F7003163FF003163FF003963
      FF00398CFF00396BFF003163FF003163FF002963FF00295AFF002152FF00184A
      FF00104AFF001029DE0073737300DEDEDE00CE6B1000EF840000E77B0000E77B
      0000E77B0000E77B0000636BB500295AFF00215AFF001852FF00104AFF000842
      FF000039FF000810D60073737300DEDEDE001042FF003163FF003163FF00396B
      FF00426BFF00426BFF00396BFF003163FF00295AFF002152FF00184AFF001042
      FF000839FF000810BD0073737300DEDEDE000831F700215AFF002963FF002963
      FF003163FF003163FF003163FF003163FF00215AFF002152FF00184AFF00104A
      FF000842FF000010C60000000000000000001039FF00396BFF00396BFF00396B
      FF00427BFF003984FF00396BFF003963FF003163FF00295AFF002152FF002152
      FF00184AFF001029E70073737300DEDEDE00DE731000EF8C0000EF840000E784
      0000E77B0000E77B0000F7E7C600F7F7EF00F7F7E700EFEFE700EFE7DE00E7E7
      D600E7DED600C6BDB50073737300DEDEDE001042FF003163FF00396BFF004273
      FF004A73FF004273FF00396BFF003163FF00295AFF00215AFF001852FF001042
      FF000842FF000818BD0073737300DEDEDE000831F7002963FF002963FF003163
      FF00316BFF00316BFF00396BFF003163FF00295AFF002152FF00184AFF00104A
      FF000842FF000010CE0000000000000000001042FF003973FF00396BFF00397B
      FF004273FF00427BFF00396BFF00396BFF003163FF00295AFF00215AFF002152
      FF00184AFF001031E70073737300DEDEDE00DE731000F78C0000EF840000EF84
      0000EF8C1000F7EFEF00F7F7FF00EFEFEF00EFEFEF00E7E7E700DEDEDE00DEDE
      DE00D6D6D600BDBDBD0073737300DEDEDE001842D6003963D6004263D600426B
      D6004A6BD600426BD6004263D600395AD600315AD6002952D600214AD6001842
      CE001039D60008189C0073737300DEDEDE00C6A58400EFC69400F7C68400FFEF
      D600C6D6FF00DEE7FF00316BFF003163FF00CED6F700A5B5FF00EFE7D600DEAD
      7B00DEB58400AD846B0000000000000000001042FF00396BFF0039E7FF0039A5
      FF004A73FF004273FF004294FF00396BFF003163FF00295AFF00295AFF002152
      FF00184AFF001031EF0073737300DEDEDE00E77B1000F78C0000F7840000EF9C
      2900F7F7F700F7F7F700F7F7F700EFEFEF00EFEFEF00E7E7E700E7E7E700DEDE
      DE00D6D6D600BDBDBD0073737300DEDEDE00423931005A5A52005A5A52005A5A
      52005A5A52005A5A520052524A0052524A004A4A42004A4A4200424239004239
      3100393931001818080073737300DEDEDE00CE630000F7840000FFC66300B5CE
      FF009C9CC600FFDE9400316BFF002963FF00DEC6A500AD9CA50094B5FF00EFBD
      7300E76B0000B54A000000000000000000001042FF004A9CFF0052E7FF0042BD
      FF004273FF004273FF00426BFF003963FF003163FF00295AFF00215AFF002152
      FF00184AFF001031EF0073737300DEDEDE00E77B0800FF8C0000F7AD4A00F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700EFEFEF00E7E7E700E7E7E700DEDE
      DE00DEDEDE00BDBDBD0073737300DEDEDE00424242005A5A5A00636363006363
      6300636363005A5A5A0052525200525252004A4A4A004A4A4A00424242003939
      3900393939001818180073737300DEDEDE00CE630000FFD69400A5C6FF00ADA5
      B500FF940000FFCE8C003163FF002963FF00D6BDAD00F7840000B59C9C008CAD
      FF00EFC68C00B54A000000000000000000001042FF003163FF004A94FF00396B
      FF00426BFF00429CFF00396BFF00396BFF003163FF00295AFF00215AFF002152
      FF00184AFF001039F70094949400E7E7E700EF7B0800FFC66B00F7FFFF00F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700EFEFEF00EFEFEF00E7E7E700DEDE
      DE00DEDEDE00C6C6C60094949400E7E7E7004242420063636300636363006363
      6300636363005A5A5A005A5A5A0052525200525252004A4A4A00424242004242
      4200393939001818180094949400E7E7E700D68C4A008CB5FF00B59C9400FF94
      0000FF8C0000FFCE94002963FF002963FF00D6BDAD00EF840000EF7B0000B594
      84007BA5FF00BD7B420000000000000000000842FF001042FF001042FF001042
      FF001042FF001042FF001042FF001042FF001039FF001039FF001039FF000839
      FF000831FF001039FF00E7E7E700FFFFFF00EFDEC600E7E7EF00DEE7E700DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00D6D6D600D6D6D600D6D6D600CECE
      CE00CECECE00CECECE00E7E7E700FFFFFF003939390039393900393939003939
      3900313131003131310029292900292929002929290029292900212121001818
      18001818180018181800E7E7E700F7F7F700C66B0800AD633100D6630000CE63
      0000CE630000C6A57B000831EF000831E700AD949400C65A0000BD5A0000C652
      0000A5522900AD4A080000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
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
end
