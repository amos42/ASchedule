object frmView: TfrmView
  Left = 353
  Top = 220
  BorderStyle = bsDialog
  Caption = #48120#47532#48372#44592
  ClientHeight = 252
  ClientWidth = 220
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'System'
  Font.Style = []
  OldCreateOrder = True
  Position = poDefaultPosOnly
  Visible = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object pntChange1: TPaintBox
    Left = 168
    Top = 143
    Width = 45
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #46027#50880#52404
    Font.Style = []
    ParentFont = False
    OnPaint = pntChange1Paint
  end
  object pntChange2: TPaintBox
    Left = 168
    Top = 197
    Width = 45
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #46027#50880#52404
    Font.Style = []
    ParentFont = False
    OnPaint = pntChange2Paint
  end
  object Panel3: TPanel
    Left = 3
    Top = 5
    Width = 158
    Height = 242
    BevelOuter = bvLowered
    TabOrder = 0
    object pntTeacher: TPaintBox
      Left = 1
      Top = 1
      Width = 156
      Height = 240
      Align = alClient
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Small Fonts'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      OnPaint = pntTeacherPaint
    end
  end
end
