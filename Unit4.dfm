object WINDOW_INFO: TWINDOW_INFO
  Left = 456
  Top = 224
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'WINDOW_INFO'
  ClientHeight = 185
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 321
    Height = 185
    HideSelection = False
    Lines.Strings = (
      ''
      ''
      'Programmed by Poweruser'
      'Email:  poweruser.rs@hotmail.com'
      ''
      
        'Several other people of the current OFP community contributed by' +
        ' '
      '  -  testing this program'
      '  -  suggesting new features or changes'
      '  -  creating language files'
      ''
      'The source code of this program is available at'
      'http://github.com/Poweruser/OFPMonitor')
    ReadOnly = True
    TabOrder = 0
    WordWrap = False
  end
end
