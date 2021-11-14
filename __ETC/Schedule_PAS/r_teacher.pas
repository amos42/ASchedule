unit r_teacher;

interface

uses Windows, SysUtils, Messages, Classes, Graphics, Controls,
  StdCtrls, ExtCtrls, Forms, QuickRpt, QRCtrls;

type
  TqrTeachers = class(TQuickRep)
    PageHeaderBand1: TQRBand;
    DetailBand1: TQRBand;
    PageFooterBand1: TQRBand;
    QRLabel1: TQRLabel;
    QRLabel2: TQRLabel;
    QRLabel3: TQRLabel;
    QRLabel4: TQRLabel;
    QRLabel5: TQRLabel;
    QRLabel6: TQRLabel;
    QRLabel7: TQRLabel;
    QRLabel8: TQRLabel;
    QRLabel9: TQRLabel;
    ColumnHeaderBand1: TQRBand;
    QRShape1: TQRShape;
    QRShape2: TQRShape;
    QRShape3: TQRShape;
    QRShape4: TQRShape;
    QRShape5: TQRShape;
    QRShape6: TQRShape;
    QRShape7: TQRShape;
    QRShape8: TQRShape;
    QRLabel10: TQRLabel;
    QRLabel11: TQRLabel;
    QRLabel12: TQRLabel;
    QRLabel13: TQRLabel;
    QRLabel14: TQRLabel;
    QRLabel15: TQRLabel;
    QRLabel16: TQRLabel;
    QRLabel17: TQRLabel;
    QRLabel18: TQRLabel;
    QRLabel19: TQRLabel;
    procedure QuickRepNeedData(Sender: TObject; var MoreData: Boolean);
    procedure QuickRepBeforePrint(Sender: TCustomQuickRep;
      var PrintReport: Boolean);
  private
    rc: Integer;
    Week: Integer;
  public

  end;

var
  qrTeachers: TqrTeachers;

implementation

uses Global;

{$R *.DFM}

procedure TqrTeachers.QuickRepBeforePrint(Sender: TCustomQuickRep;
  var PrintReport: Boolean);
begin
    rc := 0;
    Week := MON;
    QRLabel19.Caption := '¿ù';
end;

procedure TqrTeachers.QuickRepNeedData(Sender: TObject;
  var MoreData: Boolean);
var
    i: Integer;
    tt: PTeacherData;
    tp: PScheduleData;
    TempNum, TempNum2, TempYear: word;
    TempType: byte;
    TempStr: string;

begin
    if (week <= SAT) then begin
      if (rc >= TeacherCount) then begin
        QRLabel19.Caption := WeekStr[week];
        Self.NewColumn();
        rc := 0;
      end;

      tt := pTeachers;
      tp := pSchedules;
      inc( tt, rc );
      inc( tp, rc );

      QRLabel1.Caption := tt^.TeacherName;

      for i := 1 to 8 do begin
        TempNum := GetClassNo( rc+1, Week, i );
        TempNum2 := GetClassNo2( rc+1, Week, i );
        TempType := GetClassType( rc+1, Week, i );

        if TempNum > 0 then begin
          TempStr := Format( '%d-%d', [(TempNum div 100), (TempNum mod 100)] );
          if TempNum2 <> 0 then begin
            TempStr := TempStr + Format( ',%d-%d', [(TempNum2 div 100), (TempNum2 mod 100)] );
          end;
        end else begin
          TempStr := '';
        end;
        case i of
            1 : QRLabel2.Caption := TempStr;
            2 : QRLabel3.Caption := TempStr;
            3 : QRLabel4.Caption := TempStr;
            4 : QRLabel5.Caption := TempStr;
            5 : QRLabel6.Caption := TempStr;
            6 : QRLabel7.Caption := TempStr;
            7 : QRLabel8.Caption := TempStr;
            8 : QRLabel9.Caption := TempStr;
        end;
      end;

      inc( rc );
      if (rc >= TeacherCount) then begin
//        rc := 0;
        inc( Week );
        if Week <= SAT then begin
//          Self.NewPage();
//          Self.NewColumn();
        end else begin
          MoreData := false;
          Exit;
        end;
      end;
      MoreData := true;
    end else begin
      MoreData := false;
    end;
end;

end.
