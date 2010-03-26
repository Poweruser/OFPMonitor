object Form1: TForm1
  Left = 382
  Top = 192
  Width = 668
  Height = 528
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Color = clBtnFace
  Constraints.MinHeight = 526
  Constraints.MinWidth = 666
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 16
  object Label15: TLabel
    Left = 384
    Top = 108
    Width = 4
    Height = 16
    Visible = False
  end
  object StringGrid1: TStringGrid
    Left = 3
    Top = 210
    Width = 654
    Height = 239
    ColCount = 7
    Ctl3D = True
    DefaultColWidth = 101
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 20
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goRowSelect]
    ParentCtl3D = False
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    OnColumnMoved = StringGrid1ColumnMoved
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
  object GroupBox1: TGroupBox
    Left = 3
    Top = 83
    Width = 366
    Height = 123
    Caption = '  Filters  '
    Color = clBtnFace
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 4
    object Label6: TLabel
      Left = 120
      Top = 74
      Width = 85
      Height = 16
      Caption = 'Mission name:'
    end
    object Label7: TLabel
      Left = 8
      Top = 74
      Width = 76
      Height = 16
      Caption = 'Server name:'
    end
    object Label14: TLabel
      Left = 8
      Top = 53
      Width = 61
      Height = 16
      Caption = 'Password:'
    end
    object Label19: TLabel
      Left = 230
      Top = 53
      Width = 77
      Height = 16
      Caption = 'min. Players:'
    end
    object Label16: TLabel
      Left = 232
      Top = 74
      Width = 77
      Height = 16
      Caption = 'Player name:'
    end
    object Label5: TLabel
      Left = 8
      Top = 16
      Width = 42
      Height = 16
      Caption = 'Status:'
    end
    object CheckBox1: TCheckBox
      Left = 72
      Top = 16
      Width = 81
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
      Width = 71
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
      Width = 93
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
      Width = 71
      Height = 17
      Caption = 'Briefing'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = CheckBox4Click
    end
    object CheckBox5: TCheckBox
      Left = 228
      Top = 32
      Width = 93
      Height = 17
      Caption = 'Debriefing'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = CheckBox5Click
    end
    object Edit1: TEdit
      Left = 120
      Top = 92
      Width = 110
      Height = 24
      TabOrder = 11
      OnChange = Edit1Change
    end
    object Edit2: TEdit
      Left = 8
      Top = 92
      Width = 110
      Height = 24
      TabOrder = 10
      OnChange = Edit2Change
    end
    object CheckBox6: TCheckBox
      Left = 72
      Top = 53
      Width = 73
      Height = 17
      Caption = 'With'
      TabOrder = 6
      OnClick = CheckBox6Click
    end
    object CheckBox7: TCheckBox
      Left = 154
      Top = 53
      Width = 65
      Height = 17
      Caption = 'Without'
      Checked = True
      State = cbChecked
      TabOrder = 7
      OnClick = CheckBox7Click
    end
    object UpDown1: TUpDown
      Left = 345
      Top = 48
      Width = 15
      Height = 24
      Associate = Edit3
      Min = 0
      Position = 1
      TabOrder = 9
      Wrap = False
      OnClick = UpDown1Click
    end
    object Edit3: TEdit
      Left = 312
      Top = 48
      Width = 33
      Height = 24
      TabOrder = 8
      Text = '1'
      OnChange = Edit3Change
    end
    object Edit4: TEdit
      Left = 232
      Top = 92
      Width = 126
      Height = 24
      TabOrder = 12
      OnChange = Edit4Change
    end
    object CheckBox8: TCheckBox
      Left = 72
      Top = 32
      Width = 81
      Height = 17
      Caption = 'Setting up'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = CheckBox8Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 3
    Top = 0
    Width = 366
    Height = 84
    Caption = '  Server Info  '
    Color = clBtnFace
    ParentColor = False
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 32
      Width = 16
      Height = 16
      Caption = 'IP:'
    end
    object Label2: TLabel
      Left = 40
      Top = 32
      Width = 64
      Height = 16
      Caption = '                '
    end
    object Label3: TLabel
      Left = 144
      Top = 32
      Width = 28
      Height = 16
      Caption = 'Port:'
    end
    object Label4: TLabel
      Left = 184
      Top = 32
      Width = 40
      Height = 16
      Caption = '          '
    end
    object Label8: TLabel
      Left = 240
      Top = 32
      Width = 52
      Height = 16
      Caption = 'Platform:'
    end
    object Label9: TLabel
      Left = 312
      Top = 32
      Width = 36
      Height = 16
      Caption = '         '
    end
    object Label10: TLabel
      Left = 240
      Top = 48
      Width = 61
      Height = 16
      Caption = 'Password:'
    end
    object Label11: TLabel
      Left = 312
      Top = 48
      Width = 36
      Height = 16
      Caption = '         '
    end
    object Label12: TLabel
      Left = 240
      Top = 64
      Width = 48
      Height = 16
      Caption = 'Version:'
    end
    object Label13: TLabel
      Left = 312
      Top = 64
      Width = 40
      Height = 16
      Caption = '          '
    end
    object Label21: TLabel
      Left = 8
      Top = 16
      Width = 88
      Height = 16
      Caption = '                      '
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Button3: TButton
      Left = 24
      Top = 54
      Width = 185
      Height = 22
      Caption = 'Copy address to clipboard'
      Enabled = False
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button3Click
    end
  end
  object StringGrid2: TStringGrid
    Left = 376
    Top = 6
    Width = 281
    Height = 200
    ColCount = 4
    DefaultColWidth = 50
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 50
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
    OnMouseDown = StringGrid2MouseDown
    OnMouseUp = StringGrid2MouseUp
    ColWidths = (
      100
      38
      43
      75)
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 449
    Width = 660
    Height = 34
    BorderWidth = 1
    DragMode = dmAutomatic
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
    ParentShowHint = False
    ShowHint = False
    SimplePanel = False
    SizeGrip = False
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 448
    Top = 160
  end
  object NMUDP1: TNMUDP
    RemotePort = 0
    LocalPort = 0
    ReportLevel = 5
    OnDataReceived = NMUDP1DataReceived
    OnDataSend = NMUDP1DataSend
    Left = 480
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
    object Watch1: TMenuItem
      Caption = 'Watch'
    end
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 512
    Top = 160
    object Exit1: TMenuItem
      Caption = 'Exit'
      OnClick = Exit1Click
    end
    object Settings1: TMenuItem
      Caption = 'Settings'
      OnClick = Settings1Click
    end
    object Font1: TMenuItem
      Caption = 'Font'
      OnClick = Font1Click
    end
    object GetnewServerlist1: TMenuItem
      Caption = 'Get new Server list'
      OnClick = GetnewServerlist1Click
    end
  end
  object TrayIcon1: TTrayIcon
    Visible = True
    Hide = True
    RestoreOn = imMouseDown
    PopupMenuOn = imNone
    Left = 544
    Top = 160
  end
  object FontDialog1: TFontDialog
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 8
    MaxFontSize = 20
    Options = [fdLimitSize, fdApplyButton]
    OnApply = FontDialog1Apply
    Left = 576
    Top = 160
  end
end
