unit r_classes;

interface

uses Windows, SysUtils, Messages, Classes, Graphics, Controls,
  StdCtrls, ExtCtrls, Forms, QuickRpt, QRCtrls;

type
  TqrClasses = class(TQuickRep)
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
    QRShape9: TQRShape;
    QRLabel19: TQRLabel;
    procedure QuickRepNeedData(Sender: TObject; var MoreData: Boolean);
    procedure QuickRepBeforePrint(Sender: TCustomQuickRep;
      var PrintReport: Boolean);
  private
    year, cls: Integer;
    Week: Integer;
  public

  end;

var
  qrClasses: TqrClasses;

implementation

uses Global;

{$R *.DFM}

procedure TqrClasses.QuickRepBeforePrint(Sender: TCustomQuickRep;
  var PrintReport: Boolean);
begin
    year := 1;
    cls  := 1;
    Week := MON;
    QRLabel19.Caption := '¿ù';
end;

procedure TqrClasses.QuickRepNeedData(Sender: TObject;
  var MoreData: Boolean);
var
    i, t: Integer;
    tt: PTeacherData;
    ts: PScheduleData;
    TempNum, TempNum2, TempYear: word;
    TempType: byte;
    TempStr: string;

begin
    if (week <= SAT) then begin
      if (year > 3) then begin
        QRLabel19.Caption := WeekStr[week];
        Self.NewColumn();
        year := 1;
      end;

      QRLabel1.Caption := Format('%d-%d', [year, cls] );

      for t := 1 to 8 do begin
            TempStr := '';

            for i := 1 to gSchool.SPC_Count do begin
              if ((gSchool.SPC[i].Years and SPC_CLASSES[year]) <> 0) and
                 (gSchool.SPC[i].Pos[year].w = week) and (gSchool.SPC[i].Pos[year].t = t) then begin
                TempStr := gSchool.SPC[i].Name;
                break;
              end;
            end;

            if TempStr = '' then begin
              ts := pSchedules;
              tt := pTeachers;
              for i := 1 to TeacherCount do begin
                if (ts^[week, t].ClassNo = year * 100 + cls) or
                   (ts^[week, t].ClassNo2 = year * 100 + cls) then
                  TempStr := tt^.Subject[year, ts^[week, t].ClassInfo mod 10].Name;

                inc( ts );
                inc( tt );
              end;
            end;
        case t of
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

      inc( cls );
      if (cls > gSchool.ClassCount[year]) then begin
        cls := 1;
        inc( year );
        if year > 3 then begin
          inc( Week );
        end;
        if Week <= SAT then begin
//          Self.NewPage();
//          Self.NewColumn();
        end else begin
//          MoreData := false;
//          Exit;
        end;
      end;
      MoreData := true;
    end else begin
      MoreData := false;
    end;
end;

end.
