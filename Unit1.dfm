object Form1: TForm1
  Left = 203
  Top = 122
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 470
  ClientWidth = 659
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
  object Label15: TLabel
    Left = 384
    Top = 108
    Width = 3
    Height = 13
    Visible = False
  end
  object Button3: TButton
    Left = 238
    Top = 7
    Width = 132
    Height = 24
    Caption = 'Copy address to clipboard'
    TabOrder = 4
    OnClick = Button3Click
  end
  object StringGrid1: TStringGrid
    Left = 3
    Top = 202
    Width = 654
    Height = 241
    ColCount = 7
    DefaultColWidth = 101
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 2
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goRowSelect]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    OnMouseDown = StringGrid1MouseDown
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
  object Button2: TButton
    Left = 238
    Top = 30
    Width = 132
    Height = 24
    Caption = 'Get new Server list'
    TabOrder = 1
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 3
    Top = 77
    Width = 366
    Height = 121
    Caption = '  Filters  '
    TabOrder = 2
    object Label6: TLabel
      Left = 120
      Top = 74
      Width = 67
      Height = 13
      Caption = 'Mission name:'
    end
    object Label7: TLabel
      Left = 8
      Top = 74
      Width = 63
      Height = 13
      Caption = 'Server name:'
    end
    object Label14: TLabel
      Left = 8
      Top = 53
      Width = 49
      Height = 13
      Caption = 'Password:'
    end
    object Label19: TLabel
      Left = 230
      Top = 52
      Width = 59
      Height = 13
      Caption = 'min. Players:'
    end
    object Label16: TLabel
      Left = 232
      Top = 72
      Width = 61
      Height = 13
      Caption = 'Player name:'
    end
    object Label5: TLabel
      Left = 8
      Top = 16
      Width = 33
      Height = 13
      Caption = 'Status:'
    end
    object CheckBox1: TCheckBox
      Left = 72
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Playing'
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Left = 154
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Waiting'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = CheckBox2Click
    end
    object CheckBox3: TCheckBox
      Left = 228
      Top = 16
      Width = 65
      Height = 17
      Caption = 'Creating'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = CheckBox3Click
    end
    object CheckBox4: TCheckBox
      Left = 154
      Top = 32
      Width = 57
      Height = 17
      Caption = 'Briefing'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = CheckBox4Click
    end
    object CheckBox5: TCheckBox
      Left = 228
      Top = 32
      Width = 73
      Height = 17
      Caption = 'Debriefing'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = CheckBox5Click
    end
    object Edit1: TEdit
      Left = 120
      Top = 88
      Width = 110
      Height = 21
      TabOrder = 5
      OnChange = Edit1Change
    end
    object Edit2: TEdit
      Left = 8
      Top = 88
      Width = 110
      Height = 21
      TabOrder = 6
      OnChange = Edit2Change
    end
    object CheckBox6: TCheckBox
      Left = 72
      Top = 51
      Width = 73
      Height = 17
      Caption = 'With'
      TabOrder = 7
      OnClick = CheckBox6Click
    end
    object CheckBox7: TCheckBox
      Left = 154
      Top = 51
      Width = 65
      Height = 17
      Caption = 'Without'
      Checked = True
      State = cbChecked
      TabOrder = 8
      OnClick = CheckBox7Click
    end
    object UpDown1: TUpDown
      Left = 337
      Top = 50
      Width = 15
      Height = 21
      Associate = Edit3
      Min = 0
      Position = 1
      TabOrder = 9
      Wrap = False
      OnClick = UpDown1Click
    end
    object Edit3: TEdit
      Left = 296
      Top = 50
      Width = 41
      Height = 21
      TabOrder = 10
      Text = '1'
      OnChange = Edit3Change
    end
    object Edit4: TEdit
      Left = 232
      Top = 88
      Width = 110
      Height = 21
      TabOrder = 11
      OnChange = Edit4Change
    end
    object CheckBox8: TCheckBox
      Left = 72
      Top = 32
      Width = 73
      Height = 17
      Caption = 'Setting up'
      Checked = True
      State = cbChecked
      TabOrder = 12
      OnClick = CheckBox8Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 3
    Top = 2
    Width = 230
    Height = 75
    Caption = '  Server Info  '
    TabOrder = 3
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 13
      Height = 13
      Caption = 'IP:'
    end
    object Label2: TLabel
      Left = 32
      Top = 16
      Width = 33
      Height = 13
      Caption = '           '
    end
    object Label3: TLabel
      Left = 8
      Top = 32
      Width = 22
      Height = 13
      Caption = 'Port:'
    end
    object Label4: TLabel
      Left = 64
      Top = 32
      Width = 45
      Height = 13
      Caption = '               '
    end
    object Label8: TLabel
      Left = 120
      Top = 16
      Width = 41
      Height = 13
      Caption = 'Platform:'
    end
    object Label9: TLabel
      Left = 184
      Top = 16
      Width = 24
      Height = 13
      Caption = '        '
    end
    object Label10: TLabel
      Left = 120
      Top = 48
      Width = 49
      Height = 13
      Caption = 'Password:'
    end
    object Label11: TLabel
      Left = 184
      Top = 48
      Width = 30
      Height = 13
      Caption = '          '
    end
    object Label12: TLabel
      Left = 8
      Top = 48
      Width = 38
      Height = 13
      Caption = 'Version:'
    end
    object Label13: TLabel
      Left = 64
      Top = 48
      Width = 30
      Height = 13
      Caption = '          '
    end
    object Label17: TLabel
      Left = 120
      Top = 32
      Width = 22
      Height = 13
      Caption = 'Impl:'
    end
    object Label18: TLabel
      Left = 184
      Top = 32
      Width = 12
      Height = 13
      Caption = '    '
    end
  end
  object StringGrid2: TStringGrid
    Left = 376
    Top = 6
    Width = 281
    Height = 190
    ColCount = 4
    DefaultColWidth = 50
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 50
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goRowSelect]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 5
    OnMouseDown = StringGrid2MouseDown
    ColWidths = (
      100
      38
      43
      75)
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 446
    Width = 659
    Height = 24
    Panels = <
      item
        Text = 'Listed: '
        Width = 75
      end
      item
        Text = 'Online: '
        Width = 75
      end
      item
        Width = 75
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object Button1: TButton
    Left = 238
    Top = 53
    Width = 132
    Height = 24
    Caption = 'Settings'
    TabOrder = 7
    OnClick = Button1Click
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 208
    Top = 32
  end
  object NMUDP1: TNMUDP
    RemotePort = 0
    LocalPort = 0
    ReportLevel = 5
    OnDataReceived = NMUDP1DataReceived
    OnDataSend = NMUDP1DataSend
    Left = 208
    Top = 8
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer3Timer
    Left = 208
    Top = 56
  end
  object PopupMenu1: TPopupMenu
    OnPopup = PopupMenu1Popup
    Left = 184
    Top = 56
    object Join1: TMenuItem
      Caption = 'Join'
      Enabled = False
      object N01: TMenuItem
        Caption = '0'
      end
      object N11: TMenuItem
        Caption = '1'
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
    object Mods1: TMenuItem
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
  end
end
