object frmClass: TfrmClass
  Left = 250
  Top = 199
  BorderStyle = bsDialog
  Caption = #54617#44553' '#49884#44036#54364
  ClientHeight = 253
  ClientWidth = 295
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'System'
  Font.Style = []
  OldCreateOrder = True
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel3: TPanel
    Left = 7
    Top = 7
    Width = 183
    Height = 210
    BevelOuter = bvLowered
    TabOrder = 0
    object pntTeacher: TPaintBox
      Left = 1
      Top = 1
      Width = 181
      Height = 208
      Align = alClient
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      OnMouseDown = pntTeacherMouseDown
      OnPaint = pntTeacherPaint
    end
  end
  object Panel1: TPanel
    Left = 200
    Top = 8
    Width = 89
    Height = 209
    TabOrder = 1
    object btnYear1: TSpeedButton
      Left = 8
      Top = 8
      Width = 25
      Height = 25
      GroupIndex = 1
      Caption = '1'
      OnClick = btnYear1Click
    end
    object btnYear2: TSpeedButton
      Left = 8
      Top = 32
      Width = 25
      Height = 25
      GroupIndex = 1
      Caption = '2'
      OnClick = btnYear2Click
    end
    object btnYear3: TSpeedButton
      Left = 8
      Top = 56
      Width = 25
      Height = 25
      GroupIndex = 1
      Caption = '3'
      OnClick = btnYear3Click
    end
    object lstClass: TListBox
      Left = 40
      Top = 6
      Width = 41
      Height = 197
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ImeName = #54620#44397#50612'('#54620#44544')'
      ItemHeight = 16
      ParentFont = False
      TabOrder = 0
      OnClick = lstClassClick
    end
  end
  object pnlInfo: TPanel
    Left = 0
    Top = 225
    Width = 295
    Height = 28
    Align = alBottom
    Caption = 'pnlInfo'
    TabOrder = 2
    object edtInfo: TEdit
      Left = 9
      Top = 4
      Width = 240
      Height = 21
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #46027#50880#52404
      Font.Style = [fsBold]
      ImeName = #54620#44397#50612'('#54620#44544')'
      ParentFont = False
      TabOrder = 0
    end
  end
end
