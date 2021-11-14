object Form1: TForm1
  Left = 223
  Top = 110
  Width = 533
  Height = 392
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 48
    Width = 78
    Height = 13
    Caption = #44368#49324'  '#51077#47141
  end
  object Label2: TLabel
    Left = 8
    Top = 184
    Width = 81
    Height = 13
    Caption = #49884#44036#54364' '#51077#47141
  end
  object SpeedButton1: TSpeedButton
    Left = 472
    Top = 40
    Width = 33
    Height = 25
    Caption = '...'
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 472
    Top = 184
    Width = 33
    Height = 25
    Caption = '...'
    OnClick = SpeedButton2Click
  end
  object Label3: TLabel
    Left = 8
    Top = 72
    Width = 81
    Height = 13
    Caption = #44368#49324'  '#52636#47141
  end
  object Label4: TLabel
    Left = 8
    Top = 96
    Width = 81
    Height = 13
    Caption = #44284#47785'  '#52636#47141
  end
  object Label5: TLabel
    Left = 8
    Top = 216
    Width = 81
    Height = 13
    Caption = #49884#44036#54364' '#52636#47141
  end
  object edtSTC_SRC: TEdit
    Left = 96
    Top = 40
    Width = 377
    Height = 21
    ImeName = 'Microsoft IME 2003'
    TabOrder = 0
  end
  object edtSCD_SRC: TEdit
    Left = 96
    Top = 184
    Width = 377
    Height = 21
    ImeName = 'Microsoft IME 2003'
    TabOrder = 1
  end
  object Button1: TButton
    Left = 344
    Top = 112
    Width = 129
    Height = 41
    Caption = #44368#49324#48320#54872'(STC, SSB)'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 344
    Top = 232
    Width = 129
    Height = 41
    Caption = #49884#44036#54364' '#48320#54872' (SCD)'
    TabOrder = 3
    OnClick = Button2Click
  end
  object edtSCD_DES: TEdit
    Left = 96
    Top = 208
    Width = 377
    Height = 21
    ImeName = 'Microsoft IME 2003'
    TabOrder = 4
  end
  object edtSTC_DES: TEdit
    Left = 96
    Top = 64
    Width = 377
    Height = 21
    ImeName = 'Microsoft IME 2003'
    TabOrder = 5
  end
  object edtSSB_DES: TEdit
    Left = 96
    Top = 88
    Width = 377
    Height = 21
    ImeName = 'Microsoft IME 2003'
    TabOrder = 6
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'STC'
    Filter = '*.stc|*.stc'
    Left = 128
    Top = 120
  end
  object OpenDialog2: TOpenDialog
    DefaultExt = 'SCD'
    Filter = '*.scd|*.scd'
    Left = 128
    Top = 240
  end
end
