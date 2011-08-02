object WINDOW_SETTINGS: TWINDOW_SETTINGS
  Left = 368
  Top = 162
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
          Left = 176
          Top = 17
          Width = 41
          Height = 21
          TabOrder = 0
          Text = '2'
          OnChange = EDIT_SERVERLIST_UPDATEChange
        end
        object UPDOWN_SERVERLIST_UPDATE: TUpDown
          Left = 217
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
        object ComboBox1: TComboBox
          Left = 16
          Top = 20
          Width = 449
          Height = 21
          AutoDropDown = True
          Style = csDropDownList
          ImeMode = imDisable
          ItemHeight = 13
          TabOrder = 0
          OnChange = ComboBox1Change
        end
      end
      object GROUPBOX_NOTIFICATIONS: TGroupBox
        Left = 8
        Top = 120
        Width = 249
        Height = 49
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
        Top = 62
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
        Top = 176
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
            Left = 365
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
            Left = 365
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
            Left = 365
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
        ItemHeight = 0
        TabOrder = 0
        OnChange = ComboBox2Change
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
end
