object Author: TAuthor
  Left = 701
  Top = 169
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 
    'Welcome to the Creativision World!!!                            ' +
    ' '
  ClientHeight = 311
  ClientWidth = 428
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
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 425
    Height = 273
  end
  object Image1: TImage
    Left = 2
    Top = 3
    Width = 419
    Height = 266
    Hint = 'Creativision console (Courtesy of Fabrizio Pedrazzini)'
    AutoSize = True
    Center = True
    ParentShowHint = False
    ShowHint = True
  end
  object Label3: TLabel
    Left = 120
    Top = 290
    Width = 76
    Height = 13
    Caption = 'coming soon.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 32
    Top = 290
    Width = 77
    Height = 13
    Cursor = crHandPoint
    Caption = '(CreativEmu)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = Label2Click
  end
  object Label1: TLabel
    Left = 48
    Top = 275
    Width = 123
    Height = 13
    Caption = 'Creativision emulator'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Memo1: TMemo
    Left = 192
    Top = 8
    Width = 225
    Height = 257
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    Lines.Strings = (
      'The "creatiVision" was born in 1981 '
      'in the VTech (Video Technology '
      'Limited) '
      'laboratories, Hong Kong.'
      ''
      'It has been distributed in Europe '
      '(Italy, Sweden and Germany for '
      'sure) '
      'and South-Africa using its actual '
      'name, and Australia as the "Dick '
      'Smith '
      'Wizzard", "FunVision" and '
      '"Hanimex Rameses" up to 1984.'
      ''
      'The console was actually a '
      'combined micro-computer/console '
      'system: its '
      'joysticks could be also used as a '
      'standard "qwerty" keyboard by '
      'rotating '
      'them by 90 degrees and then '
      'inserting them into two '
      'compartments of the top '
      'side of the console.'
      ''
      'It could be also expanded with '
      'cassette player, additional rubber '
      'keyboard, '
      'parallel I/O interface, floppy disk '
      'drive, modem '
      '(probably unreleased), generic '
      'Centronics printer and one '
      'memory expansion '
      'module for use with the "Basic" '
      'language cartridge.')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    Visible = False
  end
  object Button1: TButton
    Left = 360
    Top = 280
    Width = 59
    Height = 25
    Caption = '&Gallery >>'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 294
    Top = 280
    Width = 59
    Height = 25
    Caption = '<< &Back'
    TabOrder = 2
    Visible = False
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 232
    Top = 280
    Width = 57
    Height = 25
    Caption = '&Home'
    TabOrder = 3
    Visible = False
    OnClick = Button3Click
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 8
    Top = 8
  end
end
