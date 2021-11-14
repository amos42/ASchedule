//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_SCHOOL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmSchool *frmSchool;

#include "Global.h"
#include "A_Util.h"
#include "filefmt/SCD_Files.h"

//---------------------------------------------------------------------------
__fastcall TfrmSchool::TfrmSchool(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::RecalcTimes(void)
{
    pnlTotal->Caption = IntToStr( GetTotalClassTimes() );
}

void TfrmSchool::PutCellData( int y, int w, int n, String str )
{
    TStringGrid *grd = grdSchedules[y-atYEAR_BASE];

    grd->Cells[ 1 + w-atWEEK_BASE ][ 1 + n-atLESSON_BASE ] = str;
}

void TfrmSchool::PutCurCellData( int w, int n, String str )
{
    PutCellData( g_curYear, w, n, str );
}

void __fastcall TfrmSchool::FormCreate(TObject *Sender)
{
  int y, w, n;

  grdSchedules[0] = grdSchedule1;
  grdSchedules[1] = grdSchedule2;
  grdSchedules[2] = grdSchedule3;

  for( y = atYEAR_1; y <= atYEAR_MAX; y++ ){
    grdSchedule = grdSchedules[y-atYEAR_BASE];

    for( n = atLESSON_1; n <= atLESSON_MAX; n++ )
      grdSchedule->Cells[0][1+n-atLESSON_BASE] = IntToStr(n-atLESSON_1+1);

    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ )
      grdSchedule->Cells[1+w-atWEEK_BASE][0] = GetWeekStr(w);
  }

  grdSchedule = NULL;
  g_curYear = 0;
}


void __fastcall TfrmSchool::FormShow(TObject *Sender)
{
  int i, y, w, n;
  TListItem *li;

  edtSchoolName->Text = g_School.SchoolName;

  lvSpecial->Items->Clear();
  for( i = 0; i < g_School.SPC_Count; i++ ){
    li = lvSpecial->Items->Add();
    li->Caption = g_School.SPC[i].Name;
    if( g_School.SPC[i].Years & SPC_CLASS1_MASK )
      li->SubItems->Add("√");
    else
      li->SubItems->Add("");
    if( g_School.SPC[i].Years & SPC_CLASS2_MASK )
      li->SubItems->Add("√");
    else
      li->SubItems->Add("");
    if( g_School.SPC[i].Years & SPC_CLASS3_MASK )
      li->SubItems->Add("√");
    else
      li->SubItems->Add("");
  }

  for( y = atYEAR_1; y <= atYEAR_MAX; y++ ){
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
      for( n = atLESSON_1; n <= GetWeekLimit(y,w); n++ )
        PutCellData( y, w, n, "" );
      for( n = GetWeekLimit(y,w)+1; n <= atLESSON_MAX; n++ )
        PutCellData( y, w, n, "==" );
    }

    for( i = 0; i < g_School.SPC_Count; i++ ){
      if( g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE] )
        PutCellData( y, g_School.SPC[i].Pos[y-atYEAR_BASE].week, g_School.SPC[i].Pos[y-atYEAR_BASE].lesson, g_School.SPC[i].Name );
    }
  }

  edtCC1->Text = IntToStr(GetLimitClass(atYEAR_1)-atCLASS_BASE + 1);
  edtCC2->Text = IntToStr(GetLimitClass(atYEAR_2)-atCLASS_BASE + 1);
  edtCC3->Text = IntToStr(GetLimitClass(atYEAR_3)-atCLASS_BASE + 1);

  mskLunch1->Text = IntToStr(g_School.LunchTime[0]);
  mskLunch2->Text = IntToStr(g_School.LunchTime[1]);
  mskLunch3->Text = IntToStr(g_School.LunchTime[2]);

  tabYear->PageIndex = 0;
  g_curYear = atYEAR_1;
  grdSchedule = grdSchedule1;

  RecalcTimes();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::grdScheduleDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    TCanvas *cnv;
    int y;

    if( ACol <= 0 ) return;
    if( ARow <= 0 ) return;

    y = tabYear->PageIndex;
    cnv = dynamic_cast<TStringGrid *>(Sender)->Canvas;

    if( (ARow-1 + atLESSON_BASE) > GetWeekLimit(y + atYEAR_BASE, ACol-1 + atWEEK_BASE) ){
      FillRect( cnv->Handle, &Rect, GetStockObject(GRAY_BRUSH) );
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::edtSchoolNameChange(TObject *Sender)
{
    strncpy( g_School.SchoolName, edtSchoolName->Text.c_str(), SCHOOL_NAME_SIZE );
    g_School.SchoolName[SCHOOL_NAME_SIZE] = '\0';
}
//---------------------------------------------------------------------------
void __fastcall TfrmSchool::spnWeekClick(TObject *Sender,
      TUDBtnType Button)
{
    int i, y, w;

    y = tabYear->PageIndex + atYEAR_BASE;
    if(      Sender == spnWeek1 ) w = atWEEK_MON;
    else if( Sender == spnWeek2 ) w = atWEEK_TUE;
    else if( Sender == spnWeek3 ) w = atWEEK_WED;
    else if( Sender == spnWeek4 ) w = atWEEK_THU;
    else if( Sender == spnWeek5 ) w = atWEEK_FRI;
    else if( Sender == spnWeek6 ) w = atWEEK_SAT;

    if( Button == btNext ){
      g_School.WeekLimit[y-atYEAR_BASE][w-atWEEK_BASE]--;
      if( GetWeekLimit(y,w) < atLESSON_1 )
        g_School.WeekLimit[y-atYEAR_BASE][w-atWEEK_BASE] = atLESSON_1;
      else {
        for( i = 0; i < g_School.SPC_Count; i++ ){
          if( (g_School.SPC[i].Pos[y-atYEAR_BASE].week == w) && (g_School.SPC[i].Pos[y-atYEAR_BASE].lesson == GetWeekLimit(y,w)) ){
            g_School.SPC[i].Pos[y-atYEAR_BASE].lesson--;
          }
        }
        if( GetWeekLimit(y,w) < atLESSON_MAX ) PutCurCellData( w, GetWeekLimit(y,w)+1, "==" );
      }
    } else if( Button == btPrev ){
      g_School.WeekLimit[y-atYEAR_BASE][w-atWEEK_BASE]++;
      if( GetWeekLimit(y,w) > atLESSON_MAX )
        g_School.WeekLimit[y-atYEAR_BASE][w-atWEEK_BASE] = atLESSON_MAX;
      else
        if( GetWeekLimit(y,w) >= atLESSON_1 ) PutCurCellData( w, GetWeekLimit(y,w), "" );
    }

    RecalcTimes();
}

void __fastcall TfrmSchool::grdScheduleClick(TObject *Sender)
{
    int i, j, x, y;

    i = tabYear->PageIndex;

    x = grdSchedule->Col;
    y = grdSchedule->Row;

    if( grdSchedule->Cells[x][y] == "" ){
      if( lvSpecial->ItemIndex >= 0 ){
        j = lvSpecial->ItemIndex;

        if( (g_School.SPC[j].Years & SPC_CLASS_MASK_LST[i]) != 0 ){
          PutCurCellData( g_School.SPC[j].Pos[i].week, g_School.SPC[j].Pos[i].lesson, "" );
          g_School.SPC[j].Pos[i].week = x - 1 + atWEEK_BASE;
          g_School.SPC[j].Pos[i].lesson = y - 1 + atLESSON_BASE;
          PutCurCellData( g_School.SPC[j].Pos[i].week, g_School.SPC[j].Pos[i].lesson, g_School.SPC[j].Name );

          RecalcTimes();
        }
      }
    }
}

void __fastcall TfrmSchool::BitBtn1Click(TObject *Sender)
{
    Close();
}

void __fastcall TfrmSchool::tabYearChange(TObject *Sender, int NewTab,
   bool &AllowChange)
{
  grdSchedule = grdSchedules[NewTab];
  g_curYear = NewTab + atYEAR_BASE;
}

void __fastcall TfrmSchool::edtCC1Change(TObject *Sender)
{
    if( edtCC1->Text != "" )
      g_School.ClassCount[atYEAR_1-atYEAR_BASE] = StrToInt(edtCC1->Text);
    else
      g_School.ClassCount[atYEAR_1-atYEAR_BASE] = 0;
    RecalcTimes();
}

void __fastcall TfrmSchool::edtCC2Change(TObject *Sender)
{
    if( edtCC2->Text != "" )
      g_School.ClassCount[atYEAR_2-atYEAR_BASE] = StrToInt(edtCC2->Text);
    else
      g_School.ClassCount[atYEAR_2-atYEAR_BASE] = 0;
    RecalcTimes();
}

void __fastcall TfrmSchool::edtCC3Change(TObject *Sender)
{
    if( edtCC3->Text != "" )
      g_School.ClassCount[atYEAR_3-atYEAR_BASE] = StrToInt(edtCC3->Text);
    else
      g_School.ClassCount[atYEAR_3-atYEAR_BASE] = 0;
    RecalcTimes();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::mskLunchChange(TObject *Sender)
{
    TMaskEdit *msk = dynamic_cast<TMaskEdit *>(Sender);
    int i = msk->Tag;  // 학년

    g_School.LunchTime[i] = StrToInt(msk->Text);
    if( g_School.LunchTime[i] >= 8 ) g_School.LunchTime[i] = 4;
    if( g_School.LunchTime[i] <  0 ) g_School.LunchTime[i] = 4;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::btnSpcAddClick(TObject *Sender)
{
    String str;
    int i;
    TListItem *li;

    if( g_School.SPC_Count >= MAX_SPC_COUNT ) return;

    str = InputBox2("", "특별 수업 명칭을 입력하세요.", "");
    if( str != "" ){
      if( str.Length() > 3 ){
        MessageDlg2("글자수는 영문3자로 제한됩니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
        return;
      }

      li = lvSpecial->Items->Add();
      li->Caption = str;
      li->SubItems->Add("√");
      li->SubItems->Add("√");
      li->SubItems->Add("√");

      i = lvSpecial->Items->Count;
      g_School.SPC_Count = i;
      StrPCopy( g_School.SPC[i-1].Name, str );
      g_School.SPC[i-1].Years = SPC_CLASS1_MASK | SPC_CLASS2_MASK | SPC_CLASS3_MASK;
      g_School.SPC[i-1].Pos[0].week = 0; g_School.SPC[i-1].Pos[0].lesson = 0;
      g_School.SPC[i-1].Pos[1].week = 0; g_School.SPC[i-1].Pos[1].lesson = 0;
      g_School.SPC[i-1].Pos[2].week = 0; g_School.SPC[i-1].Pos[2].lesson = 0;

      RecalcTimes();
    }
}

void __fastcall TfrmSchool::btnSpcDelClick(TObject *Sender)
{
    int i, j;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }

    i = lvSpecial->ItemIndex;
    if( i >= 0 ){
      lvSpecial->Items->Delete( i );
      i = i;

      if( g_School.SPC[i].Years & SPC_CLASS1_MASK )
        PutCellData( atYEAR_1, g_School.SPC[i].Pos[0].week, g_School.SPC[i].Pos[0].lesson, "" );
      if( g_School.SPC[i].Years & SPC_CLASS2_MASK )
        PutCellData( atYEAR_2, g_School.SPC[i].Pos[1].week, g_School.SPC[i].Pos[1].lesson, "" );
      if( g_School.SPC[i].Years & SPC_CLASS3_MASK )
        PutCellData( atYEAR_3, g_School.SPC[i].Pos[2].week, g_School.SPC[i].Pos[2].lesson, "" );

      g_School.SPC_Count = lvSpecial->Items->Count;
      if( g_School.SPC_Count > 0 ){
        for( j = i; j < g_School.SPC_Count; j++ ){
          g_School.SPC[j] = g_School.SPC[j+1];
        }
      }

      RecalcTimes();
    }
}

void __fastcall TfrmSchool::btnSpcEditClick(TObject *Sender)
{
    String str;
    int i, j;

    i = lvSpecial->ItemIndex;
    if( i < 0 ) return;

    str = lvSpecial->Items->Item[i]->Caption;
    str = InputBox2("", "특별 수업 명칭을 입력하세요.", str);
    if( str != "" ){
      if( str.Length() > 3 ){
        MessageDlg2("글자수는 영문3자로 제한됩니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
        return;
      }

      StrPCopy( g_School.SPC[i+1].Name, str );

      lvSpecial->Items->Item[i]->Caption = str;
      i = i + 1;
      PutCellData( atYEAR_1, g_School.SPC[i].Pos[0].week, g_School.SPC[i].Pos[0].lesson, str );
      PutCellData( atYEAR_2, g_School.SPC[i].Pos[1].week, g_School.SPC[i].Pos[1].lesson, str );
      PutCellData( atYEAR_3, g_School.SPC[i].Pos[2].week, g_School.SPC[i].Pos[2].lesson, str );
    }
}

void __fastcall TfrmSchool::lvSpecialMouseDown(TObject* Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TListItem *li;
    int xx, ww;
    int i, si;

    li = lvSpecial->GetItemAt(X,Y);
    if( li == NULL ) return;

    si = -1;
    xx = 2;
    for( i = 0; i < lvSpecial->Columns->Count; i++ ){
      ww = lvSpecial->Columns->Items[i]->Width;
      if( (X > xx) && (X < xx+ww) ){
        si = i-1 + atYEAR_BASE;
        break;
      }
      xx += ww;
    }

    i = 1 + li->Index - atLESSON_BASE;
    if( (si >= atYEAR_1) && (si <= atYEAR_MAX) ){
      if( g_School.SPC[i].Years & SPC_CLASS_MASK_LST[si-atYEAR_BASE] ){
        g_School.SPC[i].Years &= (~SPC_CLASS_MASK_LST[si-atYEAR_BASE]);
        li->SubItems->Strings[si-atYEAR_BASE] = "";
        if( g_School.SPC[i].Pos[si-atYEAR_BASE].week != 0 && g_School.SPC[i].Pos[si-atYEAR_BASE].lesson != 0 )
          PutCellData( si, g_School.SPC[i].Pos[si-atYEAR_BASE].week, g_School.SPC[i].Pos[si-atYEAR_BASE].lesson, "" );
      } else {
        g_School.SPC[i].Years = g_School.SPC[i].Years | SPC_CLASS_MASK_LST[si-atYEAR_BASE];
        g_School.SPC[i].Pos[si-atYEAR_BASE].week = 0; g_School.SPC[i].Pos[si-atYEAR_BASE].lesson = 0;
        li->SubItems->Strings[si-atYEAR_BASE] = "√";
      }

      RecalcTimes();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSchool::btnImportClick(TObject *Sender)
{
    if( dlgOpen->Execute() ){
      if( ! LoadSchoolData( dlgOpen->FileName.c_str() ) ){
        MessageDlg2( "파일 열기에 실패했습니다.\n\n"
                    "잘못된 파일이거나 구버전 파일 형식입니다.", "메시지", 
                    mtWarning, TMsgDlgButtons() << mbOK, 0 );
        return;
      }

      FormShow(this);
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmSchool::btnExportClick(TObject *Sender)
{
    if( dlgSave->Execute() ){
      SaveSchoolData( dlgSave->FileName.c_str() );
      MessageDlg2( "저장되었습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    }
}
//---------------------------------------------------------------------------

