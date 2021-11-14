unit r_schdule;

interface

uses Windows, SysUtils, Messages, Classes, Graphics, Controls,
  StdCtrls, ExtCtrls, Forms, QuickRpt, QRCtrls;

type
  TqrSchedules = class(TQuickRep)
    PageHeaderBand1: TQRBand;
    DetailBand1: TQRBand;
    PageFooterBand1: TQRBand;
    QRLabel1: TQRLabel;
    qrlSubject1_1: TQRLabel;
    qrlSubject2_1: TQRLabel;
    qrlSubject3_1: TQRLabel;
    qrlSubject4_1: TQRLabel;
    qrlSubject5_1: TQRLabel;
    qrlSubject6_1: TQRLabel;
    QRShape9: TQRShape;
    QRShape1: TQRShape;
    QRShape2: TQRShape;
    QRShape3: TQRShape;
    QRShape4: TQRShape;
    QRShape5: TQRShape;
    QRShape6: TQRShape;
    QRLabel11: TQRLabel;
    QRLabel12: TQRLabel;
    QRLabel13: TQRLabel;
    QRLabel14: TQRLabel;
    QRLabel16: TQRLabel;
    QRLabel17: TQRLabel;
    qrlClass: TQRLabel;
    QRShape7: TQRShape;
    QRShape8: TQRShape;
    QRLabel8: TQRLabel;
    qrlSubject1_2: TQRLabel;
    qrlSubject2_2: TQRLabel;
    qrlSubject3_2: TQRLabel;
    qrlSubject4_2: TQRLabel;
    qrlSubject5_2: TQRLabel;
    qrlSubject6_2: TQRLabel;
    QRShape10: TQRShape;
    QRLabel22: TQRLabel;
    qrlSubject1_3: TQRLabel;
    qrlSubject2_3: TQRLabel;
    qrlSubject3_3: TQRLabel;
    qrlSubject4_3: TQRLabel;
    qrlSubject5_3: TQRLabel;
    qrlSubject6_3: TQRLabel;
    QRShape11: TQRShape;
    QRLabel29: TQRLabel;
    qrlSubject1_4: TQRLabel;
    qrlSubject2_4: TQRLabel;
    qrlSubject3_4: TQRLabel;
    qrlSubject4_4: TQRLabel;
    qrlSubject5_4: TQRLabel;
    qrlSubject6_4: TQRLabel;
    QRShape12: TQRShape;
    QRLabel36: TQRLabel;
    qrlSubject1_5: TQRLabel;
    qrlSubject2_5: TQRLabel;
    qrlSubject3_5: TQRLabel;
    qrlSubject4_5: TQRLabel;
    qrlSubject5_5: TQRLabel;
    qrlSubject6_5: TQRLabel;
    QRShape13: TQRShape;
    QRLabel43: TQRLabel;
    qrlSubject1_6: TQRLabel;
    qrlSubject2_6: TQRLabel;
    qrlSubject3_6: TQRLabel;
    qrlSubject4_6: TQRLabel;
    qrlSubject5_6: TQRLabel;
    qrlSubject6_6: TQRLabel;
    QRShape14: TQRShape;
    QRLabel50: TQRLabel;
    qrlSubject1_7: TQRLabel;
    qrlSubject2_7: TQRLabel;
    qrlSubject3_7: TQRLabel;
    qrlSubject4_7: TQRLabel;
    qrlSubject5_7: TQRLabel;
    qrlSubject6_7: TQRLabel;
    QRShape15: TQRShape;
    QRLabel57: TQRLabel;
    qrlSubject1_8: TQRLabel;
    qrlSubject2_8: TQRLabel;
    qrlSubject3_8: TQRLabel;
    qrlSubject4_8: TQRLabel;
    qrlSubject5_8: TQRLabel;
    qrlSubject6_8: TQRLabel;
    QRShape16: TQRShape;
    QRShape17: TQRShape;
    procedure QuickRepNeedData(Sender: TObject; var MoreData: Boolean);
    procedure QuickRepBeforePrint(Sender: TCustomQuickRep;
      var PrintReport: Boolean);
  private
    year, cls: Integer;
  public

  end;

var
  qrSchedules: TqrSchedules;

implementation

uses Global,
Dialogs;
{$R *.DFM}

procedure TqrSchedules.QuickRepBeforePrint(Sender: TCustomQuickRep;
  var PrintReport: Boolean);
begin
    year := 1;
    cls  := 1;
end;

procedure TqrSchedules.QuickRepNeedData(Sender: TObject;
  var MoreData: Boolean);
var
    i, w, t: Integer;
    tt: PTeacherData;
    ts: PScheduleData;
    TempNum, TempNum2, TempYear: word;
    TempType: byte;
    TempStr: string;
    lbl: TQRLabel;
    ViewClass: Integer;

begin
    if (year <= 3) then begin
      if cls > gSchool.ClassCount[year] then begin
        Self.NewPage();
        cls := 1;
      end;

      qrlClass.Caption := Format('%d-%d', [year, cls] );

  ViewClass := year * 100 + cls;

  for w := MON to SAT do begin
    for t := 1 to gSchool.WeekLimit[year, w] do begin
      ts := PSchedules;
      tt := PTeachers;
      for i := 1 to TeacherCount do begin
        if (ts^[w, t].ClassNo = ViewClass) or (ts^[w, t].ClassNo2 = ViewClass) then begin
          tempStr := tt^.Subject[year, ts^[w, t].ClassInfo mod 10].Name;
          break;
        end;
        inc( ts );
        inc( tt );
      end;
      lbl := TQRLabel( Self.FindComponent(Format('qrlSubject%d_%d',[w,t])) );
      lbl.Caption := tempStr;
    end;
    for t := gSchool.WeekLimit[year, w] + 1 to 8 do begin
      lbl := TQRLabel( Self.FindComponent(Format('qrlSubject%d_%d',[w,t])) );
      lbl.Caption := '';
    end;
  end;

  for i := 1 to gSchool.SPC_Count do begin
    if (gSchool.SPC[i].Years and SPC_CLASSES[year]) <> 0 then begin
      w := gSchool.SPC[i].Pos[year].w;
      t := gSchool.SPC[i].Pos[year].t;
      lbl := TQRLabel( Self.FindComponent(Format('qrlSubject%d_%d',[w,t])) );
      lbl.Caption := gSchool.SPC[i].Name;
    end;
  end;

      inc( cls );
      if (cls > gSchool.ClassCount[year]) then begin
        cls := 1;
        inc( year );
      end;
      MoreData := true;
    end else begin
      MoreData := false;
    end;
end;

end.
