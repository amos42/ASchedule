object frmTeacher: TfrmTeacher
  Left = 396
  Top = 181
  BorderStyle = bsDialog
  Caption = #44368#49324' '#44592#52488#51088#47308' '#44288#47532
  ClientHeight = 456
  ClientWidth = 422
  Color = clBtnFace
  Font.Charset = HANGEUL_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548
  Font.Style = []
  OldCreateOrder = True
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object btnAdd: TSpeedButton
    Left = 128
    Top = 416
    Width = 49
    Height = 33
    Caption = #52628#44032
    OnClick = btnAddClick
  end
  object btnDelete: TSpeedButton
    Left = 184
    Top = 416
    Width = 49
    Height = 33
    Caption = #49325#51228
    OnClick = btnDeleteClick
  end
  object btnModify: TSpeedButton
    Left = 240
    Top = 416
    Width = 49
    Height = 33
    Caption = #54200#51665
    OnClick = btnModifyClick
  end
  object Label39: TLabel
    Left = 226
    Top = 389
    Width = 90
    Height = 13
    Caption = #51452#45817' '#52509' '#49884#49688' :'
    Font.Charset = HANGEUL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #44404#47548
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnClose: TBitBtn
    Left = 336
    Top = 416
    Width = 81
    Height = 33
    TabOrder = 1
    Kind = bkClose
  end
  object pnlTotalAll: TPanel
    Left = 320
    Top = 384
    Width = 97
    Height = 25
    BevelInner = bvLowered
    BevelWidth = 2
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = #46027#50880#52404
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object pnlTeacherInfo: TPanel
    Left = 120
    Top = 8
    Width = 297
    Height = 369
    Enabled = False
    TabOrder = 2
    object Label38: TLabel
      Left = 151
      Top = 11
      Width = 44
      Height = 12
      Caption = #44368#49324#47749' :'
    end
    object Label37: TLabel
      Left = 134
      Top = 347
      Width = 60
      Height = 12
      Caption = #51452#45817' '#49884#49688' :'
    end
    object edtTeacher: TEdit
      Left = 200
      Top = 8
      Width = 89
      Height = 20
      ImeName = #54620#44397#50612'('#54620#44544') (MS-IME98)'
      MaxLength = 8
      TabOrder = 0
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 32
      Width = 281
      Height = 97
      Caption = '1 '#54617#45380
      TabOrder = 1
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 38
        Height = 12
        Caption = #44284#47785'1 :'
      end
      object Label2: TLabel
        Left = 8
        Top = 37
        Width = 38
        Height = 12
        Caption = #44284#47785'2 :'
      end
      object Label3: TLabel
        Left = 8
        Top = 57
        Width = 38
        Height = 12
        Caption = #44284#47785'3 :'
      end
      object Label4: TLabel
        Left = 144
        Top = 17
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label5: TLabel
        Left = 192
        Top = 17
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label6: TLabel
        Left = 248
        Top = 17
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label10: TLabel
        Left = 144
        Top = 57
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label11: TLabel
        Left = 192
        Top = 57
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label12: TLabel
        Left = 247
        Top = 57
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label7: TLabel
        Left = 144
        Top = 37
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label8: TLabel
        Left = 192
        Top = 37
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label9: TLabel
        Left = 247
        Top = 37
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label40: TLabel
        Left = 8
        Top = 77
        Width = 38
        Height = 12
        Caption = #44284#47785'4 :'
      end
      object Label41: TLabel
        Left = 144
        Top = 77
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label42: TLabel
        Left = 192
        Top = 77
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label43: TLabel
        Left = 247
        Top = 77
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object edtSubject1_1: TEdit
        Left = 56
        Top = 12
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 0
        OnChange = DBEditChange
      end
      object edtStart1_1: TEdit
        Left = 112
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 1
        OnChange = DBEditChange
      end
      object edtSubject1_2: TEdit
        Left = 56
        Top = 32
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 2
        OnChange = DBEditChange
      end
      object edtStart1_2: TEdit
        Left = 112
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 3
        OnChange = DBEditChange
      end
      object edtSubject1_3: TEdit
        Left = 56
        Top = 52
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 4
        OnChange = DBEditChange
      end
      object edtStart1_3: TEdit
        Left = 112
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 5
        OnChange = DBEditChange
      end
      object edtEnd1_1: TEdit
        Left = 160
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 6
        OnChange = DBEditChange
      end
      object edtEnd1_2: TEdit
        Left = 160
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 7
        OnChange = DBEditChange
      end
      object edtEnd1_3: TEdit
        Left = 160
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 8
        OnChange = DBEditChange
      end
      object edtTimes1_1: TEdit
        Left = 216
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 9
        OnChange = DBEditChange
      end
      object edtTimes1_2: TEdit
        Left = 216
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 10
        OnChange = DBEditChange
      end
      object edtTimes1_3: TEdit
        Left = 216
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 11
        OnChange = DBEditChange
      end
      object edtSubject1_4: TEdit
        Left = 56
        Top = 72
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 12
        OnChange = DBEditChange
      end
      object edtStart1_4: TEdit
        Left = 112
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 13
        OnChange = DBEditChange
      end
      object edtEnd1_4: TEdit
        Left = 160
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 14
        OnChange = DBEditChange
      end
      object edtTimes1_4: TEdit
        Left = 216
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 15
        OnChange = DBEditChange
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 136
      Width = 281
      Height = 97
      Caption = '2 '#54617#45380
      TabOrder = 2
      object Label13: TLabel
        Left = 8
        Top = 17
        Width = 38
        Height = 12
        Caption = #44284#47785'1 :'
      end
      object Label14: TLabel
        Left = 144
        Top = 20
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label15: TLabel
        Left = 192
        Top = 17
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label16: TLabel
        Left = 248
        Top = 17
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label17: TLabel
        Left = 8
        Top = 37
        Width = 38
        Height = 12
        Caption = #44284#47785'2 :'
      end
      object Label18: TLabel
        Left = 144
        Top = 40
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label19: TLabel
        Left = 192
        Top = 37
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label20: TLabel
        Left = 247
        Top = 37
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label21: TLabel
        Left = 8
        Top = 57
        Width = 38
        Height = 12
        Caption = #44284#47785'3 :'
      end
      object Label22: TLabel
        Left = 144
        Top = 60
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label23: TLabel
        Left = 192
        Top = 57
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label24: TLabel
        Left = 247
        Top = 57
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label44: TLabel
        Left = 8
        Top = 77
        Width = 38
        Height = 12
        Caption = #44284#47785'4 :'
      end
      object Label45: TLabel
        Left = 144
        Top = 80
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label46: TLabel
        Left = 192
        Top = 77
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label47: TLabel
        Left = 247
        Top = 77
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object edtSubject2_1: TEdit
        Left = 56
        Top = 12
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 0
        OnChange = DBEditChange
      end
      object edtStart2_1: TEdit
        Left = 112
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 1
        OnChange = DBEditChange
      end
      object edtSubject2_2: TEdit
        Left = 56
        Top = 32
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 2
        OnChange = DBEditChange
      end
      object edtStart2_2: TEdit
        Left = 112
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 3
        OnChange = DBEditChange
      end
      object edtSubject2_3: TEdit
        Left = 56
        Top = 52
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 4
        OnChange = DBEditChange
      end
      object edtStart2_3: TEdit
        Left = 112
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 5
        OnChange = DBEditChange
      end
      object edtEnd2_1: TEdit
        Left = 160
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 6
        OnChange = DBEditChange
      end
      object edtEnd2_2: TEdit
        Left = 160
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 7
        OnChange = DBEditChange
      end
      object edtEnd2_3: TEdit
        Left = 160
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 8
        OnChange = DBEditChange
      end
      object edtTimes2_1: TEdit
        Left = 216
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 9
        OnChange = DBEditChange
      end
      object edtTimes2_2: TEdit
        Left = 216
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 10
        OnChange = DBEditChange
      end
      object edtTimes2_3: TEdit
        Left = 216
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 11
        OnChange = DBEditChange
      end
      object edtSubject2_4: TEdit
        Left = 56
        Top = 72
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 12
        OnChange = DBEditChange
      end
      object edtStart2_4: TEdit
        Left = 112
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 13
        OnChange = DBEditChange
      end
      object edtEnd2_4: TEdit
        Left = 160
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 14
        OnChange = DBEditChange
      end
      object edtTimes2_4: TEdit
        Left = 216
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 15
        OnChange = DBEditChange
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 240
      Width = 281
      Height = 97
      Caption = '3 '#54617#45380
      TabOrder = 3
      object Label25: TLabel
        Left = 8
        Top = 17
        Width = 38
        Height = 12
        Caption = #44284#47785'1 :'
      end
      object Label26: TLabel
        Left = 144
        Top = 17
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label27: TLabel
        Left = 192
        Top = 17
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label28: TLabel
        Left = 248
        Top = 17
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label29: TLabel
        Left = 8
        Top = 37
        Width = 38
        Height = 12
        Caption = #44284#47785'2 :'
      end
      object Label30: TLabel
        Left = 144
        Top = 37
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label31: TLabel
        Left = 192
        Top = 37
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label32: TLabel
        Left = 247
        Top = 37
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label33: TLabel
        Left = 8
        Top = 57
        Width = 38
        Height = 12
        Caption = #44284#47785'3 :'
      end
      object Label34: TLabel
        Left = 144
        Top = 57
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label35: TLabel
        Left = 192
        Top = 57
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label36: TLabel
        Left = 247
        Top = 57
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object Label48: TLabel
        Left = 8
        Top = 77
        Width = 38
        Height = 12
        Caption = #44284#47785'4 :'
      end
      object Label49: TLabel
        Left = 144
        Top = 77
        Width = 9
        Height = 12
        Caption = '~'
      end
      object Label50: TLabel
        Left = 192
        Top = 77
        Width = 12
        Height = 12
        Caption = #48152
      end
      object Label51: TLabel
        Left = 247
        Top = 77
        Width = 24
        Height = 12
        Caption = #49884#44036
      end
      object edtSubject3_1: TEdit
        Left = 56
        Top = 12
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 0
        OnChange = DBEditChange
      end
      object edtStart3_1: TEdit
        Left = 112
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 1
        OnChange = DBEditChange
      end
      object edtSubject3_2: TEdit
        Left = 56
        Top = 32
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 2
        OnChange = DBEditChange
      end
      object edtStart3_2: TEdit
        Left = 112
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 3
        OnChange = DBEditChange
      end
      object edtSubject3_3: TEdit
        Left = 56
        Top = 52
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 4
        OnChange = DBEditChange
      end
      object edtStart3_3: TEdit
        Left = 112
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 5
        OnChange = DBEditChange
      end
      object edtEnd3_1: TEdit
        Left = 160
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 6
        OnChange = DBEditChange
      end
      object edtEnd3_2: TEdit
        Left = 160
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 7
        OnChange = DBEditChange
      end
      object edtEnd3_3: TEdit
        Left = 160
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 8
        OnChange = DBEditChange
      end
      object edtTimes3_1: TEdit
        Left = 216
        Top = 12
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 9
        OnChange = DBEditChange
      end
      object edtTimes3_2: TEdit
        Left = 216
        Top = 32
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 10
        OnChange = DBEditChange
      end
      object edtTimes3_3: TEdit
        Left = 216
        Top = 52
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 11
        OnChange = DBEditChange
      end
      object edtSubject3_4: TEdit
        Left = 56
        Top = 72
        Width = 41
        Height = 20
        ImeName = #54620#44397#50612'('#54620#44544')'
        MaxLength = 4
        TabOrder = 12
        OnChange = DBEditChange
      end
      object edtStart3_4: TEdit
        Left = 112
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 13
        OnChange = DBEditChange
      end
      object edtEnd3_4: TEdit
        Left = 160
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 14
        OnChange = DBEditChange
      end
      object edtTimes3_4: TEdit
        Left = 216
        Top = 72
        Width = 25
        Height = 20
        AutoSize = False
        ImeName = #54620#44397#50612'('#54620#44544')'
        TabOrder = 15
        OnChange = DBEditChange
      end
    end
    object pnlTotal: TPanel
      Left = 200
      Top = 344
      Width = 89
      Height = 17
      BevelOuter = bvLowered
      Caption = '0'
      TabOrder = 4
    end
    object pnlTeacherNo: TPanel
      Left = 8
      Top = 8
      Width = 81
      Height = 17
      BevelOuter = bvLowered
      Caption = '0 / 0'
      TabOrder = 5
    end
  end
  object pnlTeachers: TPanel
    Left = 8
    Top = 8
    Width = 105
    Height = 441
    Caption = 'pnlTeachers'
    TabOrder = 3
    object btnItemUp: TSpeedButton
      Left = 8
      Top = 416
      Width = 41
      Height = 17
      Caption = #9650
      OnClick = btnItemUpClick
    end
    object btnItemDown: TSpeedButton
      Left = 56
      Top = 416
      Width = 41
      Height = 17
      Caption = #9660
      OnClick = btnItemDownClick
    end
    object lvTeachers: TListView
      Left = 8
      Top = 8
      Width = 89
      Height = 401
      Columns = <
        item
          Caption = #44368#49324#47749
          Width = 70
        end>
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
      OnSelectItem = lvTeachersSelectItem
    end
  end
end
