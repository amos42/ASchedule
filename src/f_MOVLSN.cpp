//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_MOVLSN.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMoveLesson *frmMoveLesson;

#include "Global.h"
#include "A_Util.h"
#include "SCD_Files.h"

//---------------------------------------------------------------------------
__fastcall TfrmMoveLesson::TfrmMoveLesson(TComponent* Owner)
        : TForm(Owner)
{
    IsChange = false;
}
//---------------------------------------------------------------------------

void TfrmMoveLesson::EnableLessonList( bool tf )
{
    TColor tc;

    pnlTeachers->Enabled = tf;
    btnItemUp->Enabled = tf;
    btnItemDown->Enabled = tf;

    if( tf )
      tc = clWindow;
    else
      tc = clBtnFace;

    lstLesson->Color = tc;
}

void TfrmMoveLesson::EnableLessonItems( bool tf )
{
    int i, j;
    TColor tc;

    pnlLessonInfo->Enabled = tf;
//    btnAdd->Enabled = !tf;
//    btnDelete->Enabled = !tf;

    if( tf )
      tc = clWindow;
    else
      tc = clBtnFace;

    edtLessonName->Color = tc;
    edtShortName->Color = tc;
    cboSubject->Color = tc;

    grdSchedule->Color = tc;

    lstClass->Color = tc;
    lstTeacher->Color = tc;
}

void TfrmMoveLesson::ClearLessonItems( void )
{
    edtLessonName->Text = "";
    edtShortName->Text = "";
    cboSubject->ItemIndex = -1;

    btnYear1->AllowAllUp = true;
    btnYear2->AllowAllUp = true;
    btnYear3->AllowAllUp = true;
    btnYear1->Down = false;
    btnYear2->Down = false;
    btnYear3->Down = false;
    btnYear1->AllowAllUp = false;
    btnYear2->AllowAllUp = false;
    btnYear3->AllowAllUp = false;

    for( int w = 0; w < 6; w++ )
      for( int n = 0; n < 8; n++ )
        grdSchedule->Cells[1+w][1+n] = "";

    curYear = 0;

    lstClass->Clear();
    lstTeacher->Clear();
}

void __fastcall TfrmMoveLesson::FormCreate(TObject *Sender)
{
  int y, w, n;

  for( y = atYEAR_1; y <= atYEAR_MAX; y++ ){
    for( n = atLESSON_1; n <= atLESSON_MAX; n++ )
      grdSchedule->Cells[0][1+n-atLESSON_BASE] = IntToStr(n-atLESSON_1+1);

    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ )
      grdSchedule->Cells[1+w-atWEEK_BASE][0] = GetWeekStr(w);
  }

  curYear = 0;
}


void __fastcall TfrmMoveLesson::FormShow(TObject *Sender)
{
    int i, j;
    TSubject *sbj;
    TMoveLessonData *ml;
    TColor tc;

    // 과목 데이터
    cboSubject->Clear();
    for( i = 0; i < g_iSubjectCount; i++ ){
      sbj = GetSubject( i );
      cboSubject->Items->Add( sbj->FullName );
    }

    // 교사 데이터
    lstLesson->Items->EndUpdate();
    lstLesson->Clear();
    for( i = 0; i < g_iMoveLessonCount; i++ ){
      ml = &g_pMoveLesson[i];
      lstLesson->Items->Add(ml->LessonName);
    }
    lstLesson->Items->EndUpdate();

    btnAdd->Enabled = true;
    btnModify->Tag = 0;
    btnCancel->Visible = false;
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

    EnableLessonList( g_iMoveLessonCount > 0 );
    EnableLessonItems( false );
    ClearLessonItems();

    pnlTotalClass->Caption = IntToStr(GetTotalMoveLessonTimes());

    IsChange = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::grdScheduleDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    TCanvas *cnv;

    if( curYear < atYEAR_1 ) return;
    if( ACol <= 0 ) return;
    if( ARow <= 0 ) return;

    cnv = dynamic_cast<TStringGrid *>(Sender)->Canvas;

    if( (ARow-1 + atLESSON_BASE) > GetWeekLimit(curYear, ACol-1 + atWEEK_BASE) ){
      FillRect( cnv->Handle, &Rect, GetStockObject(GRAY_BRUSH) );
    }

    if( grdSchedule->Cells[ACol][ARow] == "X" ){
      HBRUSH hBr = CreateSolidBrush( clRed );
      FillRect( cnv->Handle, &Rect, hBr );
      DeleteObject( hBr );
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMoveLesson::grdScheduleClick(TObject *Sender)
{
//    int i, j, x, y;

    if( grdSchedule->Cells[grdSchedule->Col][grdSchedule->Row] == "" )
      grdSchedule->Cells[grdSchedule->Col][grdSchedule->Row] = "X";
    else
      grdSchedule->Cells[grdSchedule->Col][grdSchedule->Row] = "";

    grdSchedule->Refresh();
}

void __fastcall TfrmMoveLesson::BitBtn1Click(TObject *Sender)
{
    Close();
}

void __fastcall TfrmMoveLesson::btnSpcDelClick(TObject *Sender)
{
    int i, j;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }
}


void __fastcall TfrmMoveLesson::btnYearClick(TObject *Sender)
{
  TSpeedButton *btn = dynamic_cast<TSpeedButton*>(Sender);
  curYear = btn->Tag + atYEAR_BASE;

  lstClass->Clear();
  for( int i = atCLASS_1; i <= GetLimitClass(curYear); i++ )
    lstClass->Items->Add( IntToStr(i) );
  lstClass->ItemIndex = 0;

  grdSchedule->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::lstTeacherClickCheck(TObject *Sender)
{
/*
String ss = lstTeacher->Items->Strings[lstTeacher->ItemIndex];
String tn = ss.SubString(1,3);

    int t = lstTeacher->ItemIndex;
if( !lstTeacher->Checked[t] ) return;

t = StrToInt(tn);

    TTeacherData *tt = GetTeacherData( t );

    int cnt = GetTeacherSubjectCount( t );
PopupTeacherSubject->Items->Clear();
for( int i = 0; i < cnt; i++ ){
TMenuItem *mi = new TMenuItem(PopupTeacherSubject);
mi->Caption = (String)GetTeacherSubject( t, i )->Name;
mi->Checked = true;
PopupTeacherSubject->Items->Add(mi);
}

TPoint p;
GetCursorPos( &p );
PopupTeacherSubject->Popup( p.x, p.y );
*/
}
//---------------------------------------------------------------------------


void __fastcall TfrmMoveLesson::lstClassClickCheck(TObject *Sender)
{
//String sbjname = edtSubjectName->Text;
TSubject *sbj = GetSubject(cboSubject->ItemIndex);
if( !sbj ) return;

int sbjcode = sbj->SubjectCode;

    TTeacherData *tt;

TClasses cls;
cls.Part.Year = curYear;
cls.Part.Classes = 0;
for( int c = 0; c < lstClass->Count; c++ ){
  if( lstClass->Checked[c] ) cls.Part.Classes |= (1 << (c+atCLASS_BASE-1));
}


//    lstTeacher->Items->BeginUpdate();
    lstTeacher->Clear();
    for( int t = 0; t < g_iTeacherCount; t++ ){
      tt = GetTeacherData(t);
      int cnt = GetTeacherSubjectCount(t);
      for( int i = 0; i < cnt; i++ ){
        TTeacherSubject *tsbj = GetTeacherSubject( t, i );
        if( (tsbj->Attr & 0x01) && (tsbj->SubjectCode == sbjcode) &&
          ((tsbj->Classes.FullValue & cls.FullValue) == cls.FullValue) ){
          lstTeacher->Items->Add( Format("%03d: %s",ARRAYOFCONST((t, tt->TeacherName))) );
          break;
        }
      }
    }
//    lstTeacher->Items->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnAddClick(TObject *Sender)
{
    // 이동수업 하나 추가
    ReallocMoveLessonData( g_iMoveLessonCount + 1 );

    ClearLessonItems();

    lstLesson->Items->Add("");
    lstLesson->ItemIndex = g_iMoveLessonCount-1;

    lstLessonClick(lstLesson);

    btnModify->Enabled = true;
    btnModify->Click();

    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnDeleteClick(TObject *Sender)
{
    int i, j;
    TMoveLessonData *ptr, *tt, *tt2;

    if( lstLesson->ItemIndex < 0 ) return;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }

    i = lstLesson->ItemIndex;

    ptr = (TMoveLessonData *)malloc( sizeof(TMoveLessonData) * (g_iMoveLessonCount-1) );

    tt = g_pMoveLesson;
    CopyMemory( ptr, tt, i*sizeof(TMoveLessonData) );
    tt += i + 1;
    tt2 = ptr;
    tt2 += i;
    CopyMemory( tt2, tt, (g_iMoveLessonCount-1-i)*sizeof(TMoveLessonData) );

    free( g_pMoveLesson );
    g_pMoveLesson = ptr;

    g_iMoveLessonCount--;

    lstLesson->DeleteSelected();

    ClearLessonItems();
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

    pnlTotalClass->Caption = IntToStr(GetTotalMoveLessonTimes());

    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnModifyClick(TObject *Sender)
{
  int i, j;
  TSubject *sbj;
  TMoveLessonData *ml;
  long Total;

    if( btnModify->Tag == 0 ){
      EnableLessonList( false );
      EnableLessonItems( true );

      btnModify->Caption = "갱신";
      btnModify->Tag = 1;
      btnCancel->Visible = true;
    } else {

int cnt1 = 0;
for( int c = 0; c < lstClass->Count; c++ )
  if( lstClass->Checked[c] ) cnt1++;
int cnt2 = 0;
for( int t = 0; t < lstTeacher->Count; t++ )
  if( lstTeacher->Checked[t] ) cnt2++;
if( cnt1 != cnt2 )
{
    MessageDlg2( "선택된 수업과 교사의 수가 맞지 않습니다.", "경고", mtWarning, TMsgDlgButtons() << mbOK, 0 );
    return;
}

      sbj = GetSubject(cboSubject->ItemIndex);
if( !sbj )
{
    MessageDlg2( "과목이 올바르지 않습니다.", "경고", mtWarning, TMsgDlgButtons() << mbOK, 0 );
    return;
}

      ml = &g_pMoveLesson[ lstLesson->ItemIndex ];

      strncpy(ml->LessonName, edtLessonName->Text.c_str(), MOVELESSON_NAME_SIZE);
      ml->LessonName[MOVELESSON_NAME_SIZE] = '\0';
      strncpy(ml->ShortName, edtShortName->Text.c_str(), MOVELESSON_SHORTNAME_SIZE);
      ml->ShortName[MOVELESSON_SHORTNAME_SIZE] = '\0';

      ml->SubjectCode = sbj->SubjectCode;

int i = 0;
for( int w = 0; w < 6; w++ )
  for( int n = 0; n < 8; n++ )
    if( grdSchedule->Cells[1+w][1+n] == "X" ){
      ml->pos[i].week = w+atWEEK_BASE;
      ml->pos[i].lesson = n+atLESSON_BASE;
      i++;
    }
ml->Times = i;

ml->Classes.Part.Year = curYear;
ml->Classes.Part.Classes = 0;
for( int c = 0; c < lstClass->Count; c++ ){
  if( lstClass->Checked[c] ) ml->Classes.Part.Classes |= (1 << (c+atCLASS_BASE-1));
}
ml->TeacherCount = 0;
for( int t = 0; t < lstTeacher->Count; t++ ){
  if( lstTeacher->Checked[t] ){
   String ss = lstTeacher->Items->Strings[t];
   String tn = ss.SubString(1,3);
   ml->Teachers[ml->TeacherCount++] = StrToInt(tn);
  }
}

      lstLesson->Items->Strings[lstLesson->ItemIndex] = edtLessonName->Text;

      EnableLessonList( true );
      EnableLessonItems( false );

      btnModify->Caption = "편집";
      btnModify->Tag = 0;
      btnCancel->Visible = false;

      pnlTotalClass->Caption = IntToStr(GetTotalMoveLessonTimes());

      IsChange = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnCancelClick(TObject *Sender)
{
    lstLessonClick(lstLesson);

    EnableLessonList( true );
    EnableLessonItems( false );

    btnModify->Caption = "편집";
    btnModify->Tag = 0;
    btnCancel->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::lstLessonClick(TObject *Sender)
{
    int i, j;
    TMoveLessonData *ml;
    int y, c, y_max;

    if( lstLesson->ItemIndex >= 0 ){
      ml = &g_pMoveLesson[ lstLesson->ItemIndex ];

      edtLessonName->Text = ml->LessonName;
      edtShortName->Text = ml->ShortName;

      cboSubject->ItemIndex = -1;
	  for( i = 0; i < g_iSubjectCount; i++ ){
		TSubject *sbj = &g_pSubjects[i];
		if( sbj->SubjectCode == ml->SubjectCode ){
          cboSubject->ItemIndex = i;
		  break;
		}
 	  }

      curYear = ml->Classes.Part.Year;

for( int w = 0; w < 6; w++ )
  for( int n = 0; n < 8; n++ )
    grdSchedule->Cells[1+w][1+n] = "";
for( i = 0; i < ml->Times; i++ ){
    grdSchedule->Cells[1+ml->pos[i].week-atWEEK_BASE][1+ml->pos[i].lesson-atLESSON_BASE] = "X";
}

      grdSchedule->Refresh();

      switch( curYear ){
        case atYEAR_1 : btnYear1->Down = true; btnYearClick(btnYear1); break;
        case atYEAR_2 : btnYear2->Down = true; btnYearClick(btnYear2); break;
        case atYEAR_3 : btnYear3->Down = true; btnYearClick(btnYear3); break;
//        default :
//             atYEAR_1 : btnYear1->Down = true; btnYearClick(btnYear1); break;
      }
      for( c = atCLASS_1; c <= GetLimitClass(curYear); c++ ){
        if( IS_CLASSES_IN(c, ml->Classes.Part.Classes) ) lstClass->Checked[c-atCLASS_BASE] = true;
      }
      lstClassClickCheck(lstClass);

for( int t = 0; t < ml->TeacherCount; t++ ){
for( int t2 = 0; t2 < lstTeacher->Count; t2++ ){
   String ss = lstTeacher->Items->Strings[t2];
   String stn = ss.SubString(1,3);
   int tn = StrToInt(stn);
   if( ml->Teachers[t] == tn ){
     lstTeacher->Checked[t2] = true;
     break;
   }
}
}

      btnDelete->Enabled = True;
      btnModify->Enabled = True;
      btnItemUp->Enabled = True;
      btnItemDown->Enabled = True;
    } else {
      btnDelete->Enabled = False;
      btnModify->Enabled = False;
      btnItemUp->Enabled = False;
      btnItemDown->Enabled = False;
      btnCancel->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnItemUpClick(TObject *Sender)
{
    int i;
    TMoveLessonData *tt, *tt2;
    TMoveLessonData tmp;
    String ss;

    if( lstLesson->ItemIndex < 0 ) return;

    i = lstLesson->ItemIndex;
    if( i <= 0 ) return;

    tt = &g_pMoveLesson[i];
    tt2 = &g_pMoveLesson[i-1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstLesson->Items->Strings[i];
    lstLesson->Items->Strings[i] = lstLesson->Items->Strings[i-1];
    lstLesson->Items->Strings[i-1] = ss;

    lstLesson->ItemIndex --;

    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMoveLesson::btnItemDownClick(TObject *Sender)
{
    int i;
    TMoveLessonData *tt, *tt2;
    TMoveLessonData tmp;
    String ss;

    if( lstLesson->ItemIndex < 0 ) return;

    i = lstLesson->ItemIndex;
    if( i >= lstLesson->Items->Count-1 ) return;

    tt = &g_pMoveLesson[i];
    tt2 = &g_pMoveLesson[i+1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstLesson->Items->Strings[i];
    lstLesson->Items->Strings[i] = lstLesson->Items->Strings[i+1];
    lstLesson->Items->Strings[i+1] = ss;

    lstLesson->ItemIndex ++;

    IsChange = true;
}
//---------------------------------------------------------------------------

