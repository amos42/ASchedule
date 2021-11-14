object frmTeacherSubject: TfrmTeacherSubject
  Left = 508
  Top = 267
  BorderStyle = bsDialog
  Caption = #44284#47785' '#51221#48372' '#51077#47141
  ClientHeight = 312
  ClientWidth = 502
  Color = clBtnFace
  Font.Charset = HANGEUL_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548
  Font.Style = []
  OldCreateOrder = True
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object btnCancel: TBitBtn
    Left = 408
    Top = 280
    Width = 81
    Height = 25
    TabOrder = 0
    Kind = bkCancel
  end
  object pnlTeacherInfo: TPanel
    Left = 8
    Top = 8
    Width = 484
    Height = 65
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 17
      Width = 44
      Height = 12
      Caption = #44284#47785#47749' :'
    end
    object Label2: TLabel
      Left = 400
      Top = 17
      Width = 32
      Height = 12
      Caption = #49884#49688' :'
    end
    object Label3: TLabel
      Left = 216
      Top = 17
      Width = 32
      Height = 12
      Caption = #54617#45380' :'
    end
    object edtTimes: TEdit
      Left = 440
      Top = 12
      Width = 33
      Height = 20
      AutoSize = False
      ImeName = #54620#44397#50612'('#54620#44544')'
      MaxLength = 2
      TabOrder = 0
    end
    object cbYear: TComboBox
      Left = 256
      Top = 11
      Width = 57
      Height = 20
      Style = csDropDownList
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 12
      TabOrder = 1
      OnClick = cbYearClick
      Items.Strings = (
        '1'#54617#45380
        '2'#54617#45380
        '3'#54617#45380)
    end
    object chkMoveLesson: TCheckBox
      Left = 384
      Top = 40
      Width = 89
      Height = 17
      Caption = #8251' '#51060#46041' '#49688#50629
      TabOrder = 2
    end
    object cboSubject: TComboBox
      Left = 56
      Top = 10
      Width = 153
      Height = 20
      Style = csDropDownList
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 12
      TabOrder = 3
    end
  end
  object btnOK: TBitBtn
    Left = 320
    Top = 280
    Width = 81
    Height = 25
    TabOrder = 2
    OnClick = btnOKClick
    Kind = bkOK
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 80
    Width = 485
    Height = 73
    Caption = #45824#49345' '#48152' '#47785#47197
    TabOrder = 3
    object Label4: TLabel
      Left = 8
      Top = 24
      Width = 6
      Height = 12
      Caption = '1'
    end
    object Label5: TLabel
      Left = 32
      Top = 24
      Width = 6
      Height = 12
      Caption = '2'
    end
    object Label7: TLabel
      Left = 56
      Top = 24
      Width = 6
      Height = 12
      Caption = '3'
    end
    object Label8: TLabel
      Left = 80
      Top = 24
      Width = 6
      Height = 12
      Caption = '4'
    end
    object Label9: TLabel
      Left = 104
      Top = 24
      Width = 6
      Height = 12
      Caption = '5'
    end
    object Label10: TLabel
      Left = 128
      Top = 24
      Width = 6
      Height = 12
      Caption = '6'
    end
    object Label11: TLabel
      Left = 152
      Top = 24
      Width = 6
      Height = 12
      Caption = '7'
    end
    object Label12: TLabel
      Left = 176
      Top = 24
      Width = 6
      Height = 12
      Caption = '8'
    end
    object Label13: TLabel
      Left = 200
      Top = 24
      Width = 6
      Height = 12
      Caption = '9'
    end
    object Label14: TLabel
      Left = 224
      Top = 24
      Width = 12
      Height = 12
      Caption = '10'
    end
    object Label15: TLabel
      Left = 248
      Top = 24
      Width = 12
      Height = 12
      Caption = '11'
    end
    object Label16: TLabel
      Left = 272
      Top = 24
      Width = 12
      Height = 12
      Caption = '12'
    end
    object Label17: TLabel
      Left = 296
      Top = 24
      Width = 12
      Height = 12
      Caption = '13'
    end
    object Label18: TLabel
      Left = 320
      Top = 24
      Width = 12
      Height = 12
      Caption = '14'
    end
    object Label19: TLabel
      Left = 344
      Top = 24
      Width = 12
      Height = 12
      Caption = '15'
    end
    object Label20: TLabel
      Left = 368
      Top = 24
      Width = 12
      Height = 12
      Caption = '16'
    end
    object Label21: TLabel
      Left = 392
      Top = 24
      Width = 12
      Height = 12
      Caption = '17'
    end
    object Label22: TLabel
      Left = 416
      Top = 24
      Width = 12
      Height = 12
      Caption = '18'
    end
    object Label38: TLabel
      Left = 440
      Top = 24
      Width = 12
      Height = 12
      Caption = '19'
    end
    object Label39: TLabel
      Left = 464
      Top = 24
      Width = 12
      Height = 12
      Caption = '20'
    end
    object chkClass1: TCheckBox
      Left = 8
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 0
    end
    object chkClass2: TCheckBox
      Left = 32
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 1
    end
    object chkClass3: TCheckBox
      Left = 56
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 2
    end
    object chkClass4: TCheckBox
      Left = 80
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 3
    end
    object chkClass5: TCheckBox
      Left = 104
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 4
    end
    object chkClass6: TCheckBox
      Left = 128
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 5
    end
    object chkClass7: TCheckBox
      Left = 152
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 6
    end
    object chkClass8: TCheckBox
      Left = 176
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 7
    end
    object chkClass9: TCheckBox
      Left = 200
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 8
    end
    object chkClass10: TCheckBox
      Left = 224
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 9
    end
    object chkClass11: TCheckBox
      Left = 248
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 10
    end
    object chkClass12: TCheckBox
      Left = 272
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 11
    end
    object chkClass13: TCheckBox
      Left = 296
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 12
    end
    object chkClass14: TCheckBox
      Left = 320
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 13
    end
    object chkClass15: TCheckBox
      Left = 344
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 14
    end
    object chkClass16: TCheckBox
      Left = 368
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 15
    end
    object chkClass17: TCheckBox
      Left = 392
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 16
    end
    object chkClass18: TCheckBox
      Left = 416
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 17
    end
    object chkClass19: TCheckBox
      Left = 440
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 18
    end
    object chkClass20: TCheckBox
      Left = 464
      Top = 40
      Width = 17
      Height = 25
      TabOrder = 19
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 160
    Width = 485
    Height = 113
    Caption = #50836#51068' '#51228#54620' '#48176#52824
    TabOrder = 4
    object rbLimitWeek0: TRadioButton
      Left = 8
      Top = 24
      Width = 177
      Height = 17
      Caption = #48176#52824' '#50836#51068' '#51228#54620' '#50630#51020' ('#44592#48376')'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = rbLimitWeek0Click
    end
    object rbLimitWeek1: TRadioButton
      Left = 8
      Top = 48
      Width = 177
      Height = 17
      Caption = #53945#51221' '#50836#51068#50640' '#51228#54620#54616#50668' '#48176#52824
      TabOrder = 1
      OnClick = rbLimitWeek1Click
    end
    object pnlLimitWeeks: TPanel
      Left = 296
      Top = 13
      Width = 177
      Height = 92
      BevelOuter = bvLowered
      TabOrder = 2
      object Label25: TLabel
        Left = 128
        Top = 8
        Width = 12
        Height = 12
        Caption = #53664
      end
      object Label26: TLabel
        Left = 104
        Top = 8
        Width = 12
        Height = 12
        Caption = #44552
      end
      object Label27: TLabel
        Left = 80
        Top = 8
        Width = 12
        Height = 12
        Caption = #47785
      end
      object Label28: TLabel
        Left = 56
        Top = 8
        Width = 12
        Height = 12
        Caption = #49688
      end
      object Label29: TLabel
        Left = 32
        Top = 8
        Width = 12
        Height = 12
        Caption = #54868
      end
      object Label30: TLabel
        Left = 8
        Top = 8
        Width = 12
        Height = 12
        Caption = #50900
      end
      object Label31: TLabel
        Left = 152
        Top = 8
        Width = 12
        Height = 12
        Caption = #51068
        Enabled = False
      end
      object Label23: TLabel
        Left = 112
        Top = 51
        Width = 6
        Height = 12
        Caption = '6'
      end
      object Label24: TLabel
        Left = 92
        Top = 51
        Width = 6
        Height = 12
        Caption = '5'
      end
      object Label32: TLabel
        Left = 72
        Top = 51
        Width = 6
        Height = 12
        Caption = '4'
      end
      object Label33: TLabel
        Left = 51
        Top = 51
        Width = 6
        Height = 12
        Caption = '3'
      end
      object Label34: TLabel
        Left = 28
        Top = 51
        Width = 6
        Height = 12
        Caption = '2'
      end
      object Label35: TLabel
        Left = 8
        Top = 51
        Width = 6
        Height = 12
        Caption = '1'
      end
      object Label36: TLabel
        Left = 135
        Top = 51
        Width = 6
        Height = 12
        Caption = '7'
      end
      object Label37: TLabel
        Left = 157
        Top = 51
        Width = 6
        Height = 12
        Caption = '8'
      end
      object chkWeek1: TCheckBox
        Left = 8
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 0
      end
      object chkWeek2: TCheckBox
        Left = 32
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 1
      end
      object chkWeek3: TCheckBox
        Left = 56
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 2
      end
      object chkWeek4: TCheckBox
        Left = 80
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 3
      end
      object chkWeek5: TCheckBox
        Left = 104
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 4
      end
      object chkWeek6: TCheckBox
        Left = 128
        Top = 21
        Width = 17
        Height = 25
        TabOrder = 5
      end
      object chkWeek7: TCheckBox
        Left = 152
        Top = 21
        Width = 17
        Height = 25
        Enabled = False
        TabOrder = 6
      end
      object chkLesson1: TCheckBox
        Left = 8
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 7
      end
      object chkLesson2: TCheckBox
        Left = 27
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 8
      end
      object chkLesson3: TCheckBox
        Left = 48
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 9
      end
      object chkLesson4: TCheckBox
        Left = 68
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 10
      end
      object chkLesson5: TCheckBox
        Left = 88
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 11
      end
      object chkLesson6: TCheckBox
        Left = 108
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 12
      end
      object chkLesson7: TCheckBox
        Left = 132
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 13
      end
      object chkLesson8: TCheckBox
        Left = 154
        Top = 62
        Width = 17
        Height = 25
        TabOrder = 14
      end
    end
  end
end
