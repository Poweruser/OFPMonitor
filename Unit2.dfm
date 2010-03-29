object Form2: TForm2
  Left = 599
  Top = 143
  Hint = 'SETTINGS_WINDOW'
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Settings'
  ClientHeight = 468
  ClientWidth = 433
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LABEL_CONFIGURATIONS_LISTOFCONFIGURATIONS: TLabel
    Left = 0
    Top = 98
    Width = 100
    Height = 13
    Caption = 'List of configurations:'
  end
  object ListBox1: TListBox
    Left = 0
    Top = 114
    Width = 430
    Height = 111
    ItemHeight = 13
    TabOrder = 3
  end
  object BUTTON_CONFIGURATION_REMOVE: TButton
    Left = 330
    Top = 200
    Width = 85
    Height = 25
    Caption = 'Remove'
    TabOrder = 4
    OnClick = BUTTON_CONFIGURATION_REMOVEClick
  end
  object GROUPBOX_OFPEXECUTABLE: TGroupBox
    Left = 0
    Top = 0
    Width = 433
    Height = 48
    Caption = 'OFP Executable '
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 18
      Width = 313
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object BUTTON_OFPEXECUTABLE_BROWSE: TButton
      Left = 328
      Top = 12
      Width = 97
      Height = 29
      Caption = 'Browse'
      TabOrder = 1
      OnClick = BUTTON_OFPEXECUTABLE_BROWSEClick
    end
  end
  object GROUPBOX_NEWCONFIGURATION: TGroupBox
    Left = 0
    Top = 234
    Width = 433
    Height = 231
    Caption = 'New configuration'
    TabOrder = 5
    object LABEL_NEWCONFIGURATION_PLAYERNAME: TLabel
      Left = 264
      Top = 90
      Width = 61
      Height = 13
      Caption = 'Player name:'
    end
    object LABEL_NEWCONFIGURATION_PASSWORD: TLabel
      Left = 264
      Top = 132
      Width = 49
      Height = 13
      Caption = 'Password:'
    end
    object LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS: TLabel
      Left = 264
      Top = 170
      Width = 104
      Height = 13
      Caption = 'Additional parameters:'
    end
    object LABEL_NEWCONFIGURATION_MODFOLDERS: TLabel
      Left = 8
      Top = 24
      Width = 55
      Height = 13
      Caption = 'Modfolders:'
    end
    object LABEL_NEWCONFIGURATION_LABEL: TLabel
      Left = 264
      Top = 50
      Width = 29
      Height = 13
      Caption = 'Label:'
    end
    object Edit3: TEdit
      Left = 265
      Top = 146
      Width = 160
      Height = 21
      TabOrder = 8
    end
    object Edit2: TEdit
      Left = 265
      Top = 106
      Width = 160
      Height = 21
      Hint = 'Leave blank to use the current OFP setting'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
    end
    object ListBox2: TListBox
      Left = 8
      Top = 40
      Width = 121
      Height = 185
      ItemHeight = 13
      MultiSelect = True
      Sorted = True
      TabOrder = 0
    end
    object CHECKBOX_NEWCONFIGURATION_NOSPLASH: TCheckBox
      Left = 264
      Top = 208
      Width = 73
      Height = 17
      Caption = ' -nosplash'
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object CHECKBOX_NEWCONFIGURATION_NOMAP: TCheckBox
      Left = 344
      Top = 208
      Width = 65
      Height = 17
      Caption = ' -nomap'
      Checked = True
      State = cbChecked
      TabOrder = 11
    end
    object Edit4: TEdit
      Left = 265
      Top = 184
      Width = 160
      Height = 21
      TabOrder = 9
    end
    object BUTTON_NEWCONFIGURATION_ADD: TButton
      Left = 264
      Top = 16
      Width = 83
      Height = 31
      Caption = 'Add'
      TabOrder = 12
      OnClick = BUTTON_NEWCONFIGURATION_ADDClick
    end
    object ListBox3: TListBox
      Left = 136
      Top = 40
      Width = 121
      Height = 185
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
      Top = 66
      Width = 161
      Height = 21
      TabOrder = 6
    end
    object BUTTON_NEWCONFIGURATION_CLEAR: TButton
      Left = 346
      Top = 16
      Width = 83
      Height = 31
      Caption = 'Clear'
      TabOrder = 13
      OnClick = BUTTON_NEWCONFIGURATION_CLEARClick
    end
  end
  object GROUPBOX_SERVERLIST: TGroupBox
    Left = 0
    Top = 50
    Width = 169
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
      Left = 112
      Top = 15
      Width = 33
      Height = 21
      TabOrder = 0
      Text = '2'
      OnChange = Edit5Change
    end
    object UpDown1: TUpDown
      Left = 145
      Top = 15
      Width = 15
      Height = 21
      Associate = Edit5
      Min = 1
      Max = 600
      Position = 2
      TabOrder = 1
      Wrap = False
      OnClick = UpDown1Click
    end
  end
  object GROUPBOX_LANGUAGE: TGroupBox
    Left = 176
    Top = 50
    Width = 257
    Height = 45
    Caption = 'Language '
    TabOrder = 2
    object ComboBox1: TComboBox
      Left = 8
      Top = 16
      Width = 240
      Height = 21
      ImeMode = imDisable
      ItemHeight = 13
      TabOrder = 0
      Text = 'ComboBox1'
      OnChange = ComboBox1Change
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'Any OFP-Executable|FLASHPOINTRESISTANCE.EXE;OperationFlashpoint.' +
      'exe'
    Options = [ofPathMustExist, ofFileMustExist, ofNoNetworkButton, ofDontAddToRecent]
    OptionsEx = [ofExNoPlacesBar]
    OnCanClose = OpenDialog1CanClose
    Left = 224
  end
end
