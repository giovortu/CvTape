object Select: TSelect
  Left = 540
  Top = 253
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Output directory'
  ClientHeight = 174
  ClientWidth = 206
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 8
    Width = 193
    Height = 19
    DirList = DirectoryListBox1
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 40
    Width = 193
    Height = 97
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 1
  end
  object Button1: TButton
    Left = 72
    Top = 144
    Width = 75
    Height = 25
    Caption = '&Ok'
    TabOrder = 2
    OnClick = Button1Click
  end
end
