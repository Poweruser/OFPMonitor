object WINDOW_UPDATE: TWINDOW_UPDATE
  Left = 234
  Top = 189
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'ArmaMonitor Updater'
  ClientHeight = 297
  ClientWidth = 409
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object LABEL_UPDATE_CURRENTFILE: TLabel
    Left = 4
    Top = 6
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
    Max = 100
    Smooth = True
    Step = 1
    TabOrder = 0
  end
  object MEMO_UPDATE_LOG: TMemo
    Left = 0
    Top = 64
    Width = 409
    Height = 233
    ReadOnly = True
    TabOrder = 1
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 376
  end
end
