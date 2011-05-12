object WINDOW_SETTINGS: TWINDOW_SETTINGS
  Left = 526
  Top = 162
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Settings'
  ClientHeight = 537
  ClientWidth = 433
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
  object GROUPBOX_OFPEXECUTABLE: TGroupBox
    Left = 0
    Top = 0
    Width = 431
    Height = 48
    Caption = 'OFP:R Executable '
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 18
      Width = 310
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object BUTTON_OFPEXECUTABLE_BROWSE: TButton
      Left = 324
      Top = 12
      Width = 102
      Height = 29
      Caption = 'Browse ...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = BUTTON_OFPEXECUTABLE_BROWSEClick
    end
  end
  object GROUPBOX_NEWCONFIGURATION: TGroupBox
    Left = 0
    Top = 344
    Width = 433
    Height = 193
    Caption = 'New configuration'
    TabOrder = 3
    object LABEL_NEWCONFIGURATION_PASSWORD: TLabel
      Left = 264
      Top = 84
      Width = 49
      Height = 13
      Caption = 'Password:'
    end
    object LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS: TLabel
      Left = 264
      Top = 130
      Width = 104
      Height = 13
      Caption = 'Additional parameters:'
    end
    object LABEL_NEWCONFIGURATION_MODFOLDERS: TLabel
      Left = 8
      Top = 16
      Width = 55
      Height = 13
      Caption = 'Modfolders:'
    end
    object LABEL_NEWCONFIGURATION_LABEL: TLabel
      Left = 264
      Top = 42
      Width = 29
      Height = 13
      Caption = 'Label:'
    end
    object BUTTON_EDITCONFIGURATION_OK: TButton
      Left = 264
      Top = 8
      Width = 83
      Height = 31
      Caption = 'OK'
      Enabled = False
      TabOrder = 13
      Visible = False
      OnClick = BUTTON_EDITCONFIGURATION_OKClick
    end
    object Edit3: TEdit
      Left = 265
      Top = 98
      Width = 160
      Height = 21
      TabOrder = 7
    end
    object ListBox2: TListBox
      Left = 8
      Top = 40
      Width = 121
      Height = 145
      ItemHeight = 13
      MultiSelect = True
      Sorted = True
      TabOrder = 0
    end
    object CHECKBOX_NEWCONFIGURATION_NOSPLASH: TCheckBox
      Left = 264
      Top = 168
      Width = 73
      Height = 17
      Caption = ' -nosplash'
      Checked = True
      State = cbChecked
      TabOrder = 9
    end
    object CHECKBOX_NEWCONFIGURATION_NOMAP: TCheckBox
      Left = 344
      Top = 168
      Width = 65
      Height = 17
      Caption = ' -nomap'
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object Edit4: TEdit
      Left = 265
      Top = 144
      Width = 160
      Height = 21
      TabOrder = 8
    end
    object BUTTON_NEWCONFIGURATION_ADD: TButton
      Left = 264
      Top = 8
      Width = 83
      Height = 31
      Caption = 'Add'
      TabOrder = 11
      OnClick = BUTTON_NEWCONFIGURATION_ADDClick
    end
    object ListBox3: TListBox
      Left = 136
      Top = 40
      Width = 121
      Height = 145
      ItemHeight = 13
      TabOrder = 3
    end
    object Button6: TButton
      Left = 136
      Top = 16
      Width = 33
      Height = 25
      Caption = '<'
      TabOrder = 2
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 96
      Top = 16
      Width = 33
      Height = 25
      Caption = '>'
      TabOrder = 1
      OnClick = Button7Click
    end
    object BUTTON_NEWCONFIGURATION_UP: TButton
      Left = 168
      Top = 16
      Width = 45
      Height = 25
      Caption = 'Up'
      TabOrder = 4
      OnClick = BUTTON_NEWCONFIGURATION_UPClick
    end
    object BUTTON_NEWCONFIGURATION_DOWN: TButton
      Left = 212
      Top = 16
      Width = 45
      Height = 25
      Caption = 'Down'
      TabOrder = 5
      OnClick = BUTTON_NEWCONFIGURATION_DOWNClick
    end
    object Edit6: TEdit
      Left = 264
      Top = 58
      Width = 161
      Height = 21
      TabOrder = 6
    end
    object BUTTON_EDITCONFIGURATION_CANCEL: TButton
      Left = 346
      Top = 8
      Width = 83
      Height = 31
      Caption = 'Cancel'
      Enabled = False
      TabOrder = 14
      Visible = False
      OnClick = BUTTON_EDITCONFIGURATION_CANCELClick
    end
    object BUTTON_NEWCONFIGURATION_CLEAR: TButton
      Left = 346
      Top = 8
      Width = 83
      Height = 31
      Caption = 'Clear'
      TabOrder = 12
      OnClick = BUTTON_NEWCONFIGURATION_CLEARClick
    end
  end
  object GROUPBOX_SERVERLIST: TGroupBox
    Left = 0
    Top = 94
    Width = 201
    Height = 45
    Caption = 'Server list '
    TabOrder = 1
    object LABEL_SERVERLIST_INTERVAL: TLabel
      Left = 5
      Top = 20
      Width = 102
      Height = 13
      Caption = 'Update-Interval (sec):'
    end
    object Edit5: TEdit
      Left = 144
      Top = 15
      Width = 33
      Height = 21
      TabOrder = 0
      Text = '2'
      OnChange = Edit5Change
    end
    object UpDown1: TUpDown
      Left = 177
      Top = 15
      Width = 15
      Height = 21
      Associate = Edit5
      Min = 1
      Max = 60
      Position = 2
      TabOrder = 1
      Wrap = False
      OnClick = UpDown1Click
    end
  end
  object GROUPBOX_LANGUAGE: TGroupBox
    Left = 208
    Top = 94
    Width = 223
    Height = 45
    Caption = 'Language '
    TabOrder = 2
    object ComboBox1: TComboBox
      Left = 8
      Top = 16
      Width = 208
      Height = 21
      AutoDropDown = True
      ImeMode = imDisable
      ItemHeight = 13
      TabOrder = 0
      OnChange = ComboBox1Change
    end
  end
  object GROUPBOX_PROFILE: TGroupBox
    Left = 0
    Top = 48
    Width = 431
    Height = 45
    Caption = 'Player name'
    TabOrder = 4
    object COMBOBOX_PROFILE: TComboBox
      Left = 8
      Top = 16
      Width = 417
      Height = 21
      AutoDropDown = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 0
      OnChange = COMBOBOX_PROFILEChange
    end
  end
  object GROUPBOX_CONFIGURATIONS: TGroupBox
    Left = 0
    Top = 144
    Width = 433
    Height = 196
    Caption = 'List of configurations'
    TabOrder = 5
    object BUTTON_EDITCONFIGURATION_COPY: TButton
      Left = 150
      Top = 164
      Width = 94
      Height = 25
      Caption = 'Copy'
      TabOrder = 5
      OnClick = BUTTON_EDITCONFIGURATION_COPYClick
    end
    object ListBox1: TListBox
      Left = 4
      Top = 16
      Width = 425
      Height = 145
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
    end
    object BUTTON_EDITCONFIGURATION_UP: TButton
      Left = 4
      Top = 164
      Width = 50
      Height = 25
      Caption = 'Up'
      TabOrder = 1
      OnClick = BUTTON_EDITCONFIGURATION_UPClick
    end
    object BUTTON_EDITCONFIGURATION_EDIT: TButton
      Left = 243
      Top = 164
      Width = 94
      Height = 25
      Caption = 'Edit'
      Enabled = False
      TabOrder = 2
      OnClick = BUTTON_EDITCONFIGURATION_EDITClick
    end
    object BUTTON_EDITCONFIGURATION_DOWN: TButton
      Left = 53
      Top = 164
      Width = 50
      Height = 25
      Caption = 'Down'
      TabOrder = 3
      OnClick = BUTTON_EDITCONFIGURATION_DOWNClick
    end
    object BUTTON_CONFIGURATION_REMOVE: TButton
      Left = 336
      Top = 164
      Width = 94
      Height = 25
      Caption = 'Remove'
      TabOrder = 4
      OnClick = BUTTON_CONFIGURATION_REMOVEClick
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'OFP:R (FLASHPOINTRESISTANCE.EXE)|FLASHPOINTRESISTANCE.EXE'
    Options = [ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofDontAddToRecent]
    OptionsEx = [ofExNoPlacesBar]
    OnCanClose = OpenDialog1CanClose
    Left = 224
  end
end
