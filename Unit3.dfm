object WINDOW_LOCALGAME: TWINDOW_LOCALGAME
  Left = 336
  Top = 420
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Local Game'
  ClientHeight = 157
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LABEL_GAME: TLabel
    Left = 8
    Top = 8
    Width = 31
    Height = 13
    Caption = 'Game:'
    Transparent = True
  end
  object LABEL_MOD: TLabel
    Left = 8
    Top = 56
    Width = 88
    Height = 13
    Caption = 'Mod configuration:'
    Transparent = True
  end
  object COMBOBOX_LOCALGAMES: TComboBox
    Left = 8
    Top = 28
    Width = 405
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = COMBOBOX_LOCALGAMESChange
  end
  object COMBOBOX_LOCALMODS: TComboBox
    Left = 8
    Top = 76
    Width = 405
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object BUTTON_LOCALGAME_START: TButton
    Left = 8
    Top = 108
    Width = 135
    Height = 41
    Caption = 'Start'
    TabOrder = 2
    OnClick = BUTTON_LOCALGAME_STARTClick
  end
  object CHECKBOX_MULTIPLAYER: TCheckBox
    Left = 150
    Top = 110
    Width = 225
    Height = 17
    Caption = 'Multiplayer'
    TabOrder = 3
  end
end
