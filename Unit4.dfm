object WINDOW_INFO: TWINDOW_INFO
  Left = 498
  Top = 326
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Information'
  ClientHeight = 217
  ClientWidth = 353
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 353
    Height = 217
    HideSelection = False
    Lines.Strings = (
      ''
      ''
      'Programmed by Poweruser ( Email:  poweruser.rs@hotmail.com )'
      ''
      
        'Several other people of the current OFP community contributed by' +
        ' '
      '  -  testing this program'
      '  -  suggesting new features or changes'
      '  -  creating language files'
      ''
      
        'The source code and latest downloads of this program are availab' +
        'le at'
      'https://github.com/Poweruser/OFPMonitor/'
      ''
      
        'This program is using excerpts from the source code of the progr' +
        'am'
      #39'gslist'#39' (Author: Luigi Auriemma, http://aluigi.altervista.org)')
    ReadOnly = True
    TabOrder = 0
    WordWrap = False
    OnKeyDown = Memo1KeyDown
  end
end
