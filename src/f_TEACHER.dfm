object frmTeacher: TfrmTeacher
  Left = 358
  Top = 131
  BorderStyle = bsDialog
  Caption = #44368#49324' '#44592#52488#51088#47308' '#44288#47532
  ClientHeight = 454
  ClientWidth = 883
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
    Left = 264
    Top = 408
    Width = 73
    Height = 33
    Caption = #44368#49324' '#52628#44032
    OnClick = btnAddClick
  end
  object btnDelete: TSpeedButton
    Left = 336
    Top = 408
    Width = 73
    Height = 33
    Caption = #44368#49324' '#49325#51228
    OnClick = btnDeleteClick
  end
  object btnModify: TSpeedButton
    Left = 144
    Top = 408
    Width = 73
    Height = 33
    Caption = #44368#49324' '#54200#51665
    OnClick = btnModifyClick
  end
  object btnImport: TSpeedButton
    Left = 504
    Top = 408
    Width = 73
    Height = 33
    Caption = #44032#51256#50724#44592'..'
    OnClick = btnImportClick
  end
  object btnExport: TSpeedButton
    Left = 576
    Top = 408
    Width = 73
    Height = 33
    Caption = #45236#48372#45236#44592'..'
    OnClick = btnExportClick
  end
  object btnClose: TBitBtn
    Left = 792
    Top = 408
    Width = 81
    Height = 33
    TabOrder = 0
    Kind = bkClose
  end
  object pnlTeacherInfo: TPanel
    Left = 144
    Top = 16
    Width = 729
    Height = 377
    Enabled = False
    TabOrder = 1
    object Label38: TLabel
      Left = 111
      Top = 22
      Width = 44
      Height = 12
      Caption = #44368#49324#47749' :'
    end
    object Label37: TLabel
      Left = 574
      Top = 347
      Width = 60
      Height = 12
      Caption = #51452#45817' '#49884#49688' :'
    end
    object btnNewSubject: TSpeedButton
      Left = 8
      Top = 336
      Width = 25
      Height = 22
      Hint = #53945#48324#49688#50629' '#52628#44032
      Caption = '+'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnNewSubjectClick
    end
    object btnDeleteSubject: TSpeedButton
      Left = 40
      Top = 336
      Width = 25
      Height = 22
      Hint = #53945#48324#49688#50629' '#49325#51228
      Caption = '-'
      Enabled = False
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnDeleteSubjectClick
    end
    object btnModifySubject: TSpeedButton
      Left = 72
      Top = 336
      Width = 25
      Height = 22
      Hint = #53945#48324#49688#50629' '#54200#51665
      Caption = '...'
      Enabled = False
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnModifySubjectClick
    end
    object Label39: TLabel
      Left = 383
      Top = 14
      Width = 243
      Height = 13
      Caption = #51204#44368#49324' '#51452#45817' '#52509' '#49884#49688' ('#51060#46041#49688#50629' '#51228#50808') :'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 490
      Top = 46
      Width = 137
      Height = 13
      Caption = #51204#54617#44553' '#51452#45817' '#52509' '#49884#49688' :'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtTeacher: TEdit
      Left = 160
      Top = 16
      Width = 161
      Height = 24
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ImeName = #54620#44397#50612'('#54620#44544') (MS-IME98)'
      MaxLength = 12
      ParentFont = False
      TabOrder = 0
    end
    object pnlTotal: TPanel
      Left = 640
      Top = 344
      Width = 81
      Height = 17
      BevelOuter = bvLowered
      Caption = '0'
      TabOrder = 1
    end
    object pnlTeacherNo: TPanel
      Left = 8
      Top = 16
      Width = 81
      Height = 25
      BevelOuter = bvLowered
      Caption = '0 / 0'
      TabOrder = 2
    end
    object lvSubjects: TListView
      Left = 8
      Top = 176
      Width = 713
      Height = 153
      BiDiMode = bdLeftToRight
      BorderWidth = 1
      Color = cl3DLight
      Columns = <
        item
          Caption = #54617#45380
          Width = 36
        end
        item
          Alignment = taCenter
          Caption = #44284#47785#47749
          Width = 72
        end
        item
          Alignment = taCenter
          Caption = '1'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '2'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '3'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '4'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '5'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '6'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '7'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '8'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '9'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '10'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '11'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '12'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '13'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '14'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '15'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '16'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '17'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '18'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '19'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = '20'
          Width = 24
        end
        item
          Alignment = taCenter
          Caption = #49884#49688
          Width = 36
        end
        item
          Alignment = taCenter
          Caption = #51228#54620
          Width = 36
        end
        item
          Alignment = taCenter
          Caption = #51060#46041
          Width = 36
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      ParentBiDiMode = False
      TabOrder = 3
      ViewStyle = vsReport
      OnCustomDrawSubItem = lvSubjectsCustomDrawSubItem
      OnSelectItem = lvSubjectsSelectItem
    end
    object pnlTotalAll: TPanel
      Left = 632
      Top = 8
      Width = 89
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
      TabOrder = 4
    end
    object Panel1: TPanel
      Left = 8
      Top = 72
      Width = 713
      Height = 97
      BevelOuter = bvLowered
      TabOrder = 5
      object Label1: TLabel
        Left = 440
        Top = 20
        Width = 206
        Height = 12
        Caption = #49828#53944#47112#49828#50836#51064'1 : 1'#51068' 5'#44368#49884' '#51060#49345' '#48176#52824' :'
      end
      object Label2: TLabel
        Left = 440
        Top = 44
        Width = 184
        Height = 12
        Caption = #49828#53944#47112#49828#50836#51064'2 : 3'#44368#49884' '#50672#49549' '#48176#52824' :'
      end
      object Label3: TLabel
        Left = 440
        Top = 68
        Width = 202
        Height = 12
        Caption = #49828#53944#47112#49828#50836#51064'3 : '#51216#49900#49884#44036' '#51204#54980' '#48176#52824' :'
      end
      object cbCharge: TCheckBox
        Left = 16
        Top = 8
        Width = 73
        Height = 25
        Caption = #45812#51076' '#50668#48512
        Enabled = False
        TabOrder = 0
      end
      object edtCharge: TEdit
        Left = 16
        Top = 32
        Width = 73
        Height = 20
        Enabled = False
        ImeName = 'Microsoft IME 2003'
        TabOrder = 1
      end
      object cbStress1: TComboBox
        Left = 648
        Top = 16
        Width = 57
        Height = 20
        Style = csDropDownList
        Enabled = False
        ImeName = 'Microsoft IME 2003'
        ItemHeight = 12
        ItemIndex = 0
        TabOrder = 2
        Text = '0 %'
        Items.Strings = (
          '0 %'
          '25 %'
          '50 %'
          '75 %'
          '100 %')
      end
      object cbStress2: TComboBox
        Left = 648
        Top = 40
        Width = 57
        Height = 20
        Style = csDropDownList
        Enabled = False
        ImeName = 'Microsoft IME 2003'
        ItemHeight = 12
        ItemIndex = 0
        TabOrder = 3
        Text = '0 %'
        Items.Strings = (
          '0 %'
          '25 %'
          '50 %'
          '75 %'
          '100 %')
      end
      object cbStress3: TComboBox
        Left = 648
        Top = 64
        Width = 57
        Height = 20
        Style = csDropDownList
        Enabled = False
        ImeName = 'Microsoft IME 2003'
        ItemHeight = 12
        ItemIndex = 0
        TabOrder = 4
        Text = '0 %'
        Items.Strings = (
          '0 %'
          '25 %'
          '50 %'
          '75 %'
          '100 %')
      end
    end
    object pnlTotalClass: TPanel
      Left = 632
      Top = 40
      Width = 89
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
      TabOrder = 6
    end
  end
  object pnlTeachers: TPanel
    Left = 8
    Top = 8
    Width = 129
    Height = 441
    Caption = 'pnlTeachers'
    TabOrder = 2
    object btnItemUp: TSpeedButton
      Left = 8
      Top = 416
      Width = 57
      Height = 17
      Caption = #9650
      OnClick = btnItemUpClick
    end
    object btnItemDown: TSpeedButton
      Left = 64
      Top = 416
      Width = 57
      Height = 17
      Caption = #9660
      OnClick = btnItemDownClick
    end
    object lstTeacher: TListBox
      Left = 8
      Top = 8
      Width = 113
      Height = 401
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 16
      ParentFont = False
      TabOrder = 0
      OnClick = lstTeacherClick
    end
  end
  object btnCancel: TButton
    Left = 216
    Top = 408
    Width = 33
    Height = 33
    Caption = #52712#49548
    TabOrder = 3
    Visible = False
    OnClick = btnCancelClick
  end
  object dlgSave: TSaveDialog
    DefaultExt = 'STC'
    FileName = 'UNTITLED.STC'
    Filter = #44368#49324' '#54028#51068'(*.STC)|*.STC|'#47784#46304' '#54028#51068'(*.*)|*.*'
    Options = [ofOverwritePrompt, ofNoValidate]
    Title = #44368#49324' '#45936#51060#53552' '#51200#51109
    Left = 465
    Top = 409
  end
  object dlgOpen: TOpenDialog
    DefaultExt = 'STC'
    Filter = #44368#49324' '#54028#51068'(*.STC)|*.STC|'#47784#46304' '#54028#51068'(*.*)|*.*'
    Options = [ofNoValidate]
    Title = #44368#49324' '#45936#51060#53552' '#51069#44592
    Left = 425
    Top = 409
  end
end
