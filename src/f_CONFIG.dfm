object frmConfig: TfrmConfig
  Left = 423
  Top = 263
  BorderStyle = bsDialog
  Caption = #54872#44221' '#49444#51221
  ClientHeight = 256
  ClientWidth = 425
  Color = clBtnFace
  Font.Charset = HANGEUL_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object btnOk: TBitBtn
    Left = 232
    Top = 224
    Width = 89
    Height = 25
    Caption = #54869#51064
    TabOrder = 0
    OnClick = btnOkClick
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 328
    Top = 224
    Width = 89
    Height = 25
    Caption = #52712#49548
    TabOrder = 1
    Kind = bkCancel
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 409
    Height = 209
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = #49472' '#48148#44984#44592
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 385
        Height = 49
        Caption = #48148#44984#44592
        TabOrder = 0
        object edtMaxChangeCount: TLabeledEdit
          Left = 112
          Top = 16
          Width = 65
          Height = 20
          EditLabel.Width = 92
          EditLabel.Height = 12
          EditLabel.Caption = #52572#45824' '#48320#44221' '#54943#49688' : '
          ImeName = #54620#44397#50612'('#54620#44544') (MS-IME98)'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 0
          Text = '6'
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 64
        Width = 385
        Height = 113
        Caption = #44552#52825#52376#47532
        Enabled = False
        TabOrder = 1
        object CheckBox1: TCheckBox
          Left = 16
          Top = 16
          Width = 289
          Height = 17
          Caption = #54616#47336#50640' '#44057#51008#48152' '#49688#50629' '#51473#48373' '#48176#52824' '#44552#51648
          TabOrder = 0
        end
        object CheckBox2: TCheckBox
          Left = 16
          Top = 40
          Width = 289
          Height = 17
          Caption = #51216#49900' '#49884#44036' '#51204#54980#47196' '#51064#51217#54616#50668' '#48176#52824' '#44552#51648
          TabOrder = 1
        end
        object CheckBox3: TCheckBox
          Left = 16
          Top = 64
          Width = 289
          Height = 17
          Caption = #54616#47336' '#50672#49549' 3'#49884#44036' '#49688#50629' '#48176#52824' '#44552#51648
          TabOrder = 2
        end
        object CheckBox4: TCheckBox
          Left = 16
          Top = 88
          Width = 289
          Height = 17
          Caption = #54616#47336' 5'#49884#44036' '#51060#49345' '#48176#52824' '#44552#51648
          TabOrder = 3
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #49353#49345
      ImageIndex = 1
      object GroupBox3: TGroupBox
        Left = 8
        Top = 8
        Width = 385
        Height = 169
        Caption = #49353#49345' '#49444#51221
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 20
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #44544#50472' '#49353' :'
        end
        object Label2: TLabel
          Left = 8
          Top = 44
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #49472' '#48176#44221#49353' :'
        end
        object Label3: TLabel
          Left = 200
          Top = 44
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #53945#48324' '#49688#50629' :'
        end
        object Label4: TLabel
          Left = 8
          Top = 116
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #44256#51221' '#49472' :'
        end
        object Label5: TLabel
          Left = 8
          Top = 140
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #54252#52964#49828' '#49472' :'
        end
        object Label6: TLabel
          Left = 8
          Top = 92
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #44536#47112#51060' '#49472' :'
        end
        object Label7: TLabel
          Left = 200
          Top = 20
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #51216#49900' '#49884#44036' :'
        end
        object Label8: TLabel
          Left = 8
          Top = 68
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #44536#47532#46300' '#49440' :'
        end
        object Label9: TLabel
          Left = 200
          Top = 68
          Width = 81
          Height = 17
          Alignment = taRightJustify
          AutoSize = False
          Caption = #51060#46041' '#49688#50629' :'
        end
        object colCellBackground: TColorBox
          Left = 96
          Top = 40
          Width = 89
          Height = 22
          Selected = clWhite
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 0
        end
        object colSpecialLesson: TColorBox
          Left = 288
          Top = 40
          Width = 89
          Height = 22
          Selected = clLime
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 1
        end
        object colFixedCell: TColorBox
          Left = 96
          Top = 112
          Width = 89
          Height = 22
          Selected = clYellow
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 2
        end
        object colFocusCell: TColorBox
          Left = 96
          Top = 136
          Width = 89
          Height = 22
          Selected = clRed
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 3
        end
        object colCellText: TColorBox
          Left = 96
          Top = 16
          Width = 89
          Height = 22
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 4
        end
        object colGrayCell: TColorBox
          Left = 96
          Top = 88
          Width = 89
          Height = 22
          Selected = clSilver
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 5
        end
        object colLunchTime: TColorBox
          Left = 288
          Top = 16
          Width = 89
          Height = 22
          Selected = clRed
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 6
        end
        object colGridLine: TColorBox
          Left = 96
          Top = 64
          Width = 89
          Height = 22
          Selected = clGray
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 7
        end
        object colMoveLesson: TColorBox
          Left = 288
          Top = 64
          Width = 89
          Height = 22
          Selected = clFuchsia
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames]
          ItemHeight = 16
          TabOrder = 8
        end
      end
    end
  end
end
