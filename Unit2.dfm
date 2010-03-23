object Form2: TForm2
  Left = 382
  Top = 219
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Settings'
  ClientHeight = 411
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
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 0
    Top = 50
    Width = 100
    Height = 13
    Caption = 'List of configurations:'
  end
  object ListBox1: TListBox
    Left = 0
    Top = 66
    Width = 430
    Height = 113
    ItemHeight = 13
    MultiSelect = True
    TabOrder = 0
  end
  object Button2: TButton
    Left = 330
    Top = 152
    Width = 85
    Height = 25
    Caption = 'Remove'
    TabOrder = 1
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 425
    Height = 48
    Caption = 'OFP Executable'
    TabOrder = 2
    object Edit1: TEdit
      Left = 8
      Top = 18
      Width = 345
      Height = 21
      TabOrder = 0
      Text = 'Edit1'
    end
    object Button1: TButton
      Left = 360
      Top = 14
      Width = 57
      Height = 29
      Caption = 'Browse'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 186
    Width = 433
    Height = 225
    Caption = 'New configuration'
    TabOrder = 3
    object Label2: TLabel
      Left = 264
      Top = 50
      Width = 61
      Height = 13
      Caption = 'Player name:'
    end
    object Label4: TLabel
      Left = 264
      Top = 92
      Width = 49
      Height = 13
      Caption = 'Password:'
    end
    object Label5: TLabel
      Left = 264
      Top = 130
      Width = 104
      Height = 13
      Caption = 'Additional parameters:'
    end
    object Label6: TLabel
      Left = 8
      Top = 16
      Width = 55
      Height = 13
      Caption = 'Modfolders:'
    end
    object Label7: TLabel
      Left = 264
      Top = 10
      Width = 29
      Height = 13
      Caption = 'Label:'
    end
    object Edit3: TEdit
      Left = 265
      Top = 106
      Width = 104
      Height = 21
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 265
      Top = 66
      Width = 104
      Height = 21
      Hint = 'Leave blank to use the current OFP setting'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
    end
    object ListBox2: TListBox
      Left = 8
      Top = 32
      Width = 121
      Height = 185
      ItemHeight = 13
      MultiSelect = True
      Sorted = True
      TabOrder = 2
    end
    object CheckBox1: TCheckBox
      Left = 264
      Top = 166
      Width = 97
      Height = 17
      Caption = ' -nosplash'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object CheckBox2: TCheckBox
      Left = 344
      Top = 166
      Width = 65
      Height = 17
      Caption = ' -nomap'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object Edit4: TEdit
      Left = 265
      Top = 144
      Width = 104
      Height = 21
      TabOrder = 5
    end
    object Button3: TButton
      Left = 376
      Top = 58
      Width = 49
      Height = 31
      Caption = 'Add'
      TabOrder = 6
      OnClick = Button3Click
    end
    object ListBox3: TListBox
      Left = 136
      Top = 32
      Width = 121
      Height = 185
      ItemHeight = 13
      TabOrder = 7
    end
    object Button6: TButton
      Left = 136
      Top = 8
      Width = 33
      Height = 25
      Caption = '<'
      TabOrder = 8
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 96
      Top = 8
      Width = 33
      Height = 25
      Caption = '>'
      TabOrder = 9
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 168
      Top = 8
      Width = 41
      Height = 25
      Caption = 'Up'
      TabOrder = 10
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 208
      Top = 8
      Width = 49
      Height = 25
      Caption = 'Down'
      TabOrder = 11
      OnClick = Button9Click
    end
    object Edit6: TEdit
      Left = 264
      Top = 26
      Width = 161
      Height = 21
      TabOrder = 12
    end
    object Button4: TButton
      Left = 376
      Top = 88
      Width = 49
      Height = 33
      Caption = 'Clear'
      TabOrder = 13
      OnClick = Button4Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 264
    Top = 370
    Width = 169
    Height = 41
    Caption = 'Server list'
    TabOrder = 4
    object Label1: TLabel
      Left = 5
      Top = 20
      Width = 102
      Height = 13
      Caption = 'Update-Interval (sec):'
    end
    object Edit5: TEdit
      Left = 112
      Top = 12
      Width = 33
      Height = 21
      TabOrder = 0
      Text = '1'
      OnChange = Edit5Change
    end
    object UpDown1: TUpDown
      Left = 145
      Top = 12
      Width = 15
      Height = 21
      Associate = Edit5
      Min = 1
      Max = 600
      Position = 1
      TabOrder = 1
      Wrap = False
      OnClick = UpDown1Click
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'Any OFP-Executable|FLASHPOINTRESISTANCE.EXE;OperationFlashpoint.' +
      'exe'
    Options = [ofPathMustExist, ofFileMustExist, ofNoTestFileCreate, ofNoNetworkButton, ofDontAddToRecent]
    OptionsEx = [ofExNoPlacesBar]
    OnCanClose = OpenDialog1CanClose
    Left = 224
  end
end
