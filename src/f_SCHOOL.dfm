object frmSchool: TfrmSchool
  Left = 265
  Top = 155
  BorderStyle = bsDialog
  Caption = #54617#44368' '#51221#48372
  ClientHeight = 410
  ClientWidth = 465
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
  object Label4: TLabel
    Left = 296
    Top = 336
    Width = 36
    Height = 12
    Caption = #52509#49884#49688
  end
  object Label7: TLabel
    Left = 16
    Top = 10
    Width = 36
    Height = 12
    Caption = #54617#44368#47749
  end
  object btnImport: TSpeedButton
    Left = 208
    Top = 368
    Width = 73
    Height = 33
    Caption = #44032#51256#50724#44592'..'
    OnClick = btnImportClick
  end
  object btnExport: TSpeedButton
    Left = 288
    Top = 368
    Width = 73
    Height = 33
    Caption = #45236#48372#45236#44592'..'
    OnClick = btnExportClick
  end
  object BitBtn1: TBitBtn
    Left = 368
    Top = 368
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
  object tabYear: TTabbedNotebook
    Left = 7
    Top = 48
    Width = 258
    Height = 265
    Font.Charset = HANGEUL_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #44404#47548#52404
    Font.Style = []
    TabFont.Charset = DEFAULT_CHARSET
    TabFont.Color = clBtnText
    TabFont.Height = -11
    TabFont.Name = 'MS Sans Serif'
    TabFont.Style = []
    TabOrder = 1
    OnChange = tabYearChange
    object TTabPage
      Left = 4
      Top = 23
      Caption = '1'#54617#45380
      object Label19: TLabel
        Left = 8
        Top = 12
        Width = 36
        Height = 12
        Caption = #54617#44553#49688
      end
      object Label20: TLabel
        Left = 112
        Top = 13
        Width = 54
        Height = 12
        Caption = #51216#49900#49884#44036':'
      end
      object Label21: TLabel
        Left = 198
        Top = 13
        Width = 48
        Height = 12
        Caption = #44368#49884#51060#54980
      end
      object edtCC1: TMaskEdit
        Left = 48
        Top = 8
        Width = 33
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 1
        OnChange = edtCC1Change
      end
      object mskLunch1: TMaskEdit
        Left = 169
        Top = 9
        Width = 24
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 2
        OnChange = mskLunchChange
      end
      object grdSchedule1: TStringGrid
        Left = 8
        Top = 40
        Width = 236
        Height = 193
        ColCount = 7
        DefaultColWidth = 32
        DefaultRowHeight = 20
        RowCount = 9
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ScrollBars = ssNone
        TabOrder = 0
        OnClick = grdScheduleClick
        OnDrawCell = grdScheduleDrawCell
      end
    end
    object TTabPage
      Left = 4
      Top = 23
      Caption = '2'#54617#45380
      object Label2: TLabel
        Left = 8
        Top = 12
        Width = 36
        Height = 12
        Caption = #54617#44553#49688
      end
      object Label9: TLabel
        Left = 112
        Top = 13
        Width = 54
        Height = 12
        Caption = #51216#49900#49884#44036':'
      end
      object Label8: TLabel
        Left = 198
        Top = 13
        Width = 48
        Height = 12
        Caption = #44368#49884#51060#54980
      end
      object edtCC2: TMaskEdit
        Left = 48
        Top = 8
        Width = 33
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 1
        OnChange = edtCC2Change
      end
      object mskLunch2: TMaskEdit
        Tag = 1
        Left = 169
        Top = 9
        Width = 24
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 2
        OnChange = mskLunchChange
      end
      object grdSchedule2: TStringGrid
        Left = 8
        Top = 40
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
    end
    object TTabPage
      Left = 4
      Top = 23
      Caption = '3'#54617#45380
      object Label1: TLabel
        Left = 8
        Top = 12
        Width = 36
        Height = 12
        Caption = #54617#44553#49688
      end
      object Label3: TLabel
        Left = 112
        Top = 13
        Width = 54
        Height = 12
        Caption = #51216#49900#49884#44036':'
      end
      object Label5: TLabel
        Left = 198
        Top = 13
        Width = 48
        Height = 12
        Caption = #44368#49884#51060#54980
      end
      object grdSchedule3: TStringGrid
        Left = 8
        Top = 40
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
      object edtCC3: TMaskEdit
        Left = 48
        Top = 8
        Width = 32
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 1
        OnChange = edtCC3Change
      end
      object mskLunch3: TMaskEdit
        Tag = 2
        Left = 169
        Top = 9
        Width = 24
        Height = 20
        EditMask = '99;0;_'
        ImeName = 'Microsoft IME 2003'
        MaxLength = 2
        TabOrder = 2
        OnChange = mskLunchChange
      end
    end
  end
  object Panel1: TPanel
    Left = 8
    Top = 312
    Width = 257
    Height = 41
    TabOrder = 2
    object spnWeek1: TUpDown
      Tag = 1
      Left = 53
      Top = 8
      Width = 17
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 0
      Wrap = False
      OnClick = spnWeekClick
    end
    object spnWeek2: TUpDown
      Tag = 1
      Left = 86
      Top = 8
      Width = 20
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 1
      Wrap = False
      OnClick = spnWeekClick
    end
    object spnWeek3: TUpDown
      Tag = 1
      Left = 119
      Top = 8
      Width = 20
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 2
      Wrap = False
      OnClick = spnWeekClick
    end
    object spnWeek4: TUpDown
      Tag = 1
      Left = 152
      Top = 8
      Width = 20
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 3
      Wrap = False
      OnClick = spnWeekClick
    end
    object spnWeek5: TUpDown
      Tag = 1
      Left = 185
      Top = 8
      Width = 20
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 4
      Wrap = False
      OnClick = spnWeekClick
    end
    object spnWeek6: TUpDown
      Tag = 1
      Left = 218
      Top = 8
      Width = 20
      Height = 25
      Min = -10000
      Max = 10000
      Position = 0
      TabOrder = 5
      Wrap = False
      OnClick = spnWeekClick
    end
  end
  object pnlTotal: TPanel
    Left = 344
    Top = 328
    Width = 113
    Height = 25
    Caption = '0'
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 272
    Top = 48
    Width = 185
    Height = 209
    Caption = #53945#48324' '#49688#50629
    TabOrder = 4
    object btnSpcAdd: TSpeedButton
      Left = 152
      Top = 16
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
      OnClick = btnSpcAddClick
    end
    object btnSpcDel: TSpeedButton
      Left = 152
      Top = 40
      Width = 25
      Height = 22
      Hint = #53945#48324#49688#50629' '#49325#51228
      Caption = '-'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnSpcDelClick
    end
    object btnSpcEdit: TSpeedButton
      Left = 152
      Top = 168
      Width = 25
      Height = 22
      Hint = #53945#48324#49688#50629' '#54200#51665
      Caption = '...'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnSpcEditClick
    end
    object lvSpecial: TListView
      Left = 8
      Top = 16
      Width = 137
      Height = 177
      Columns = <
        item
          Caption = #49688#50629
        end
        item
          Alignment = taCenter
          Caption = '1'
          Width = 22
        end
        item
          Alignment = taCenter
          Caption = '2'
          Width = 22
        end
        item
          Alignment = taCenter
          Caption = '3'
          Width = 22
        end>
      ColumnClick = False
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnMouseDown = lvSpecialMouseDown
    end
  end
  object edtSchoolName: TEdit
    Left = 64
    Top = 8
    Width = 377
    Height = 20
    ImeName = 'Microsoft IME 2003'
    TabOrder = 5
    OnChange = edtSchoolNameChange
  end
  object dlgSave: TSaveDialog
    DefaultExt = 'SSC'
    FileName = 'UNTITLED.SSC'
    Filter = #54617#44368#51221#48372' '#54028#51068'(*.SSC)|*.SSC|'#47784#46304' '#54028#51068'(*.*)|*.*'
    Options = [ofOverwritePrompt, ofNoValidate]
    Title = #54617#44368#51221#48372' '#45936#51060#53552' '#51200#51109
    Left = 145
    Top = 361
  end
  object dlgOpen: TOpenDialog
    DefaultExt = 'SSC'
    Filter = #54617#44368#51221#48372' '#54028#51068'(*.SSC)|*.SSC|'#47784#46304' '#54028#51068'(*.*)|*.*'
    Options = [ofNoValidate]
    Title = #54617#44368#51221#48372' '#45936#51060#53552' '#51069#44592
    Left = 105
    Top = 361
  end
end
