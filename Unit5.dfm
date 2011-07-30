object WINDOW_UPDATE: TWINDOW_UPDATE
  Left = 234
  Top = 189
  Width = 417
  Height = 324
  AutoSize = True
  BorderIcons = []
  Caption = 'OFPMonitor Updater'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object LABEL_UPDATE_CURRENTFILE: TLabel
    Left = 8
    Top = 0
    Width = 3
    Height = 16
    Transparent = True
    Layout = tlCenter
  end
  object PROGRESSBAR_UPDATE_CURRENTFILE: TProgressBar
    Left = 0
    Top = 28
    Width = 409
    Height = 29
    Min = 0
    Max = 0
    Smooth = True
    Step = 1
    TabOrder = 0
  end
  object PROGRESSBAR_UPDATE_OVERALL: TProgressBar
    Left = 0
    Top = 68
    Width = 409
    Height = 29
    Min = 0
    Max = 0
    Smooth = True
    Step = 1
    TabOrder = 1
  end
  object MEMO_UPDATE_LOG: TMemo
    Left = 0
    Top = 100
    Width = 409
    Height = 197
    ReadOnly = True
    TabOrder = 2
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 376
  end
end
