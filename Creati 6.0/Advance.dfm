object Status: TStatus
  Left = 350
  Top = 271
  Cursor = crAppStart
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Status'
  ClientHeight = 79
  ClientWidth = 400
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 128
    Top = 54
    Width = 195
    Height = 13
    Cursor = crAppStart
    Caption = 'Working, press cancel at any time to stop'
  end
  object ProgressBar1: TCGauge
    Left = 8
    Top = 24
    Width = 385
    Height = 17
    ForeColor = clBlue
  end
  object Label2: TLabel
    Left = 8
    Top = 6
    Width = 385
    Height = 13
    Cursor = crAppStart
    Caption = 'Nome del file'
  end
  object Button1: TButton
    Left = 336
    Top = 48
    Width = 59
    Height = 25
    Cursor = crAppStart
    Caption = '&Cancel'
    TabOrder = 0
    OnClick = Button1Click
  end
end
