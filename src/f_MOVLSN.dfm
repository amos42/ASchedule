object frmMoveLesson: TfrmMoveLesson
  Left = 265
  Top = 155
  BorderStyle = bsDialog
  Caption = #51060#46041#49688#50629' '#49444#51221
  ClientHeight = 361
  ClientWidth = 672
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
  object btnAdd: TSpeedButton
    Left = 280
    Top = 320
    Width = 73
    Height = 33
    Caption = #49688#50629' '#52628#44032
    OnClick = btnAddClick
  end
  object btnDelete: TSpeedButton
    Left = 352
    Top = 320
    Width = 73
    Height = 33
    Caption = #49688#50629' '#49325#51228
    OnClick = btnDeleteClick
  end
  object btnModify: TSpeedButton
    Left = 144
    Top = 320
    Width = 73
    Height = 33
    Caption = #49688#50629' '#54200#51665
    OnClick = btnModifyClick
  end
  object Label5: TLabel
    Left = 410
    Top = 14
    Width = 151
    Height = 13
    Caption = #51060#46041#49688#50629' '#51452#45817' '#52509' '#49884#49688' :'
    Font.Charset = HANGEUL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #44404#47548
    Font.Style = [fsBold]
    ParentFont = False
  end
  object BitBtn1: TBitBtn
    Left = 576
    Top = 320
    Width = 89
    Height = 33
    Caption = '&Close'
    TabOrder = 0
    OnClick = BitBtn1Click
    Glyph.Data = {
      CE070000424DCE07000000000000360000002800000024000000120000000100
      1800000000009807000000000000000000000000000000000000007F7F7F7F7F
      7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7FBFBFBFBFBFBFFFFF
      FFBFBFBFFFFFFFBFBFBF7F7F7FBFBFBFFFFFFF7F7F7F7F7F7F7F7F7F7F7F7F7F
      7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F007F7F007F7F007F7F007F7F007F7F
      007F7FFFFFFF7F00007F00007F00007F00007F00000000000000007F7F7F7F7F
      7F7F7F7FFFFFFFFFFFFFFFFFFF7F00007F00007F00007F00007F00007F7F7F7F
      7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7FFFFFFF007F7F
      007F7F007F7FFFFFFFFFFFFF7F7F7FFFFFFF007F7F007F7F007F7F007F7F7F00
      00FF00FF7F007F000000000000BFBFBFFFFFFFFFFFFFFFFFFF7F0000007F7F00
      7F7F007F7F007F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F
      7F7F7F7F7F7F007F7F007F7F007F7F7F7F7F7F7F7F7F7F7F7F7F7FFFFFFF007F
      7F007F7F007F7F007F7F7F00007F007FFF00FF7F007F000000FFFFFFFFFFFFFF
      FFFFFFFFFF7F0000007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F
      7F7F7FFFFFFF7F7F7F7F7F7F7F7F7FFFFFFF007F7F007F7F007F7F7F7F7FFFFF
      FF007F7F007F7FFFFFFF007F7F007F7F007F7F007F7F7F0000FF00FF7F007FFF
      00FF000000FFFFFFFFFFFFFFFFFFFFFFFF7F0000007F7F007F7F007F7F007F7F
      007F7F007F7F007F7F007F7F7F7F7F7F7F7FBFBFBF7F7F7F7F7F7FFFFFFF007F
      7F007F7F007F7F7F7F7FFFFFFF007F7F007F7FFFFFFF007F7F007F7F007F7F00
      7F7F7F00007F007FFF00FF7F007F000000FFFFFFFFFF00FFFFFFFFFF007F0000
      007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F7F7F7FFFFFFF7F7F
      7FBFBFBF7F7F7FFFFFFF007F7F007F7F007F7F7F7F7FFFFFFF007F7F007F7FFF
      FFFF007F7F007F7F007F7F007F7F7F0000FF00FF7F007FFF00FF000000FFFFFF
      FFFFFFFFFFFFFFFFFF7F0000007F7F007F7F007F7F007F7F007F7F007F7F007F
      7F007F7F7F7F7F7F7F7FBFBFBF7F7F7F7F7F7FFFFFFF007F7F007F7F007F7F7F
      7F7FFFFFFF007F7F007F7FFFFFFF007F7F007F7F007F7F007F7F7F00007F007F
      FF00FF7F007F000000FFFFFFFFFF00FFFFFFFFFF007F0000007F7F007F7F007F
      7F007F7F007F7F007F7F007F7F007F7F7F7F7FFFFFFF7F7F7FBFBFBF7F7F7FFF
      FFFF007F7F007F7F007F7F7F7F7FFFFFFF007F7F007F7FFFFFFF007F7F007F7F
      007F7F007F7F7F0000FF00FF7F007FFF00FF000000FFFFFFFFFFFFFFFFFFFFFF
      FF7F0000007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F7F7F7F7F
      7F7FBFBFBF7F7F7F7F7F7FFFFFFF007F7F007F7F007F7F7F7F7FFFFFFF007F7F
      007F7FFFFFFF007F7F007F7F007F7F007F7F7F00007F007FFF00FF7F007F0000
      00FFFFFFFFFF00FFFFFFFFFF007F0000007F7F007F7F007F7F007F7F007F7F00
      7F7F007F7F007F7F7F7F7FFFFFFF7F7F7FBFBFBF7F7F7FFFFFFF007F7F007F7F
      007F7F7F7F7FFFFFFF007F7F007F7FFFFFFF007F7F007F7F007F7F007F7F7F00
      00FF00FF7F007FFF00FF000000FFFF00FFFFFFFFFF00FFFFFF7F0000007F7F00
      7F7F007F7F007F7F007F7F007F7F007F7F007F7F7F7F7F7F7F7FBFBFBF7F7F7F
      7F7F7FFFFFFF007F7F007F7F007F7F7F7F7FFFFFFF007F7F007F7FFFFFFF007F
      7F007F7F007F7F007F7F7F00007F007FFF00FF7F007F000000FFFFFFFFFF00FF
      FFFFFFFF007F0000007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F
      7F7F7FFFFFFF7F7F7FBFBFBF7F7F7FFFFFFF007F7F007F7F007F7F7F7F7FFFFF
      FF007F7F007F7FFFFFFF007F7F007F7F007F7F007F7F7F0000FF00FF7F007FFF
      00FF000000FFFF00FFFFFFFFFF00FFFFFF7F0000007F7F007F7F007F7F007F7F
      007F7F007F7F007F7F007F7F7F7F7F7F7F7FBFBFBF7F7F7F7F7F7FFFFFFF007F
      7F007F7F007F7F7F7F7FFFFFFF007F7F007F7FFFFFFF007F7F007F7F007F7F00
      7F7F7F00007F00007F00007F00007F00007F00007F00007F00007F00007F0000
      007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F7F7F7FFFFFFF7F7F
      7FFFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF007F7F007F7FFF
      FFFF007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F
      007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F
      7F007F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F
      7F7F007F7F007F7F007F7FFFFFFF007F7F007F7F007F7F007F7F007F7F007F7F
      000000000000000000000000000000000000007F7F007F7F007F7F007F7F007F
      7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7FFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF007F7F007F7F007F7F007F7FFFFFFF007F7F007F7F
      007F7F007F7F007F7F007F7F00000000FF0000FF0000FF0000FF00000000007F
      7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F007F7F00
      7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7FFFFFFF007F7F007F7F007F7F
      007F7FFFFFFF007F7F007F7F007F7F007F7F007F7F007F7F0000000000000000
      00000000000000000000007F7F007F7F007F7F007F7F007F7F007F7F007F7F00
      7F7F007F7F007F7F007F7F007F7F7F7F7FFFFFFFFFFFFFFFFFFFFFFFFF7F7F7F
      FFFFFF007F7F007F7F007F7F007F7FFFFFFF}
    NumGlyphs = 2
  end
  object pnlLessonInfo: TPanel
    Left = 144
    Top = 40
    Width = 521
    Height = 273
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 20
      Width = 72
      Height = 12
      Caption = #51060#46041' '#49688#50629#47749' :'
    end
    object Label3: TLabel
      Left = 21
      Top = 44
      Width = 60
      Height = 12
      Caption = #45824#49345' '#44284#47785' :'
    end
    object grdSchedule: TStringGrid
      Left = 24
      Top = 72
      Width = 236
      Height = 193
      ColCount = 7
      DefaultColWidth = 32
      DefaultRowHeight = 20
      RowCount = 9
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548#52404
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ParentFont = False
      ScrollBars = ssNone
      TabOrder = 0
      OnClick = grdScheduleClick
      OnDrawCell = grdScheduleDrawCell
    end
    object Panel2: TPanel
      Left = 280
      Top = 8
      Width = 97
      Height = 257
      TabOrder = 1
      object btnYear1: TSpeedButton
        Left = 8
        Top = 24
        Width = 25
        Height = 25
        GroupIndex = 1
        Caption = '1'
        OnClick = btnYearClick
      end
      object btnYear2: TSpeedButton
        Tag = 1
        Left = 8
        Top = 48
        Width = 25
        Height = 25
        GroupIndex = 1
        Caption = '2'
        OnClick = btnYearClick
      end
      object btnYear3: TSpeedButton
        Tag = 2
        Left = 8
        Top = 72
        Width = 25
        Height = 25
        GroupIndex = 1
        Caption = '3'
        OnClick = btnYearClick
      end
      object Label1: TLabel
        Left = 17
        Top = 4
        Width = 58
        Height = 12
        Caption = #54617#45380'  /  '#48152
      end
      object lstClass: TCheckListBox
        Left = 32
        Top = 24
        Width = 57
        Height = 225
        OnClickCheck = lstClassClickCheck
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #44404#47548
        Font.Style = [fsBold]
        ImeName = 'Microsoft IME 2003'
        ItemHeight = 13
        ParentFont = False
        TabOrder = 0
      end
    end
    object Panel3: TPanel
      Left = 384
      Top = 8
      Width = 129
      Height = 17
      Caption = #45824#49345#44368#49324
      TabOrder = 2
    end
    object edtLessonName: TEdit
      Left = 88
      Top = 16
      Width = 113
      Height = 20
      ImeName = 'Microsoft IME 2003'
      TabOrder = 3
    end
    object lstTeacher: TCheckListBox
      Left = 384
      Top = 24
      Width = 129
      Height = 241
      OnClickCheck = lstTeacherClickCheck
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #44404#47548
      Font.Style = []
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 13
      ParentFont = False
      PopupMenu = PopupTeacherSubject
      TabOrder = 4
    end
    object cboSubject: TComboBox
      Left = 88
      Top = 40
      Width = 169
      Height = 20
      Style = csDropDownList
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 12
      TabOrder = 5
    end
    object edtShortName: TEdit
      Left = 208
      Top = 16
      Width = 49
      Height = 20
      ImeName = 'Microsoft IME 2003'
      TabOrder = 6
    end
  end
  object pnlTeachers: TPanel
    Left = 8
    Top = 8
    Width = 129
    Height = 345
    Caption = 'pnlTeachers'
    TabOrder = 2
    object btnItemUp: TSpeedButton
      Left = 8
      Top = 320
      Width = 57
      Height = 17
      Caption = #9650
      OnClick = btnItemUpClick
    end
    object btnItemDown: TSpeedButton
      Left = 64
      Top = 320
      Width = 57
      Height = 17
      Caption = #9660
      OnClick = btnItemDownClick
    end
    object lstLesson: TListBox
      Left = 8
      Top = 8
      Width = 113
      Height = 313
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ImeName = 'Microsoft IME 2003'
      ItemHeight = 16
      ParentFont = False
      TabOrder = 0
      OnClick = lstLessonClick
    end
  end
  object btnCancel: TButton
    Left = 216
    Top = 320
    Width = 33
    Height = 33
    Caption = #52712#49548
    TabOrder = 3
    Visible = False
    OnClick = btnCancelClick
  end
  object pnlTotalClass: TPanel
    Left = 569
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
  object PopupTeacherSubject: TPopupMenu
    AutoHotkeys = maManual
    AutoPopup = False
    Left = 504
    Top = 40
    object qqq1: TMenuItem
      Caption = 'qqq'
    end
  end
end
