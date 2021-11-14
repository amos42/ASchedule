//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_THR_SBJ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmTeacherSubject *frmTeacherSubject;

#include "A_Util.h"
#include "Global.h"

//---------------------------------------------------------------------------
__fastcall TfrmTeacherSubject::TfrmTeacherSubject(TComponent* Owner)
        : TForm(Owner)
{
    teacher_no = -1;
    subject_idx = 0;
}
//---------------------------------------------------------------------------
void TfrmTeacherSubject::SetTeacherSubjectNo( int teacher_no, int subject_idx )
{
    this->teacher_no = teacher_no;
    this->subject_idx = subject_idx;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::FormCreate(TObject *Sender)
{
    int i;

    for( i = atCLASS_1; i <= atCLASS_MAX; i ++ )
        chkClasses[i-atCLASS_BASE] = dynamic_cast<TCheckBox*>(this->FindComponent(Format("chkClass%d",ARRAYOFCONST((i)))));

    for( i = 0; i < 7; i ++ )
        chkWeeks[i] = dynamic_cast<TCheckBox*>(this->FindComponent(Format("chkWeek%d",ARRAYOFCONST((i+1)))));

    for( i = 0; i < 8; i ++ )
        chkLessons[i] = dynamic_cast<TCheckBox*>(this->FindComponent(Format("chkLesson%d",ARRAYOFCONST((i+1)))));
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::FormShow(TObject *Sender)
{
    int i;
    TSubject *sbj;

    if( teacher_no < 0 ) return;
    TTeacherSubject *tsbj = GetTeacherSubject( teacher_no, subject_idx );

    cboSubject->Clear();
    for( i = 0; i < g_iSubjectCount; i++ ){
      sbj = GetSubject( i );
      cboSubject->Items->Add( (String)sbj->FullName + " (S:" + sbj->ShortName + ")" );

      if( tsbj->SubjectCode == sbj->SubjectCode ) cboSubject->ItemIndex = i;
    }

    cbYear->ItemIndex = tsbj->Classes.Part.Year - atYEAR_BASE;
    edtTimes->Text = IntToStr( tsbj->Times );
    chkMoveLesson->Checked = ( tsbj->Attr & 0x01 );

    for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
       chkClasses[i-atCLASS_BASE]->Checked = IS_CLASSES_IN(i, tsbj->Classes.Part.Classes);
    }

    if( (tsbj->LimitWeeks & 0x8000) || (tsbj->LimitLessons & 0x8000) ){
      rbLimitWeek1->Checked = true;
      pnlLimitWeeks->Visible = true;
    } else {
      rbLimitWeek0->Checked = true;
      pnlLimitWeeks->Visible = false;
    }

    if( tsbj->LimitWeeks & 0x8000 ){
      for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
         chkWeeks[i-atWEEK_BASE]->Checked = IS_WEEKS_IN(i, tsbj->LimitWeeks);
      }
    } else {
      for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
         chkWeeks[i-atWEEK_BASE]->Checked = false;
      }
    }

    if( tsbj->LimitLessons & 0x8000 ){
      for( i = atLESSON_1; i <= atLESSON_MAX; i++ ){
         chkLessons[i-atLESSON_BASE]->Checked = IS_LESSONS_IN(i, tsbj->LimitLessons);
      }
    } else {
      for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
         chkLessons[i-atLESSON_BASE]->Checked = false;
      }
    }

    cbYearClick(cbYear);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::btnOKClick(TObject *Sender)
{
    int i;
    int lesson_count, cnt1, cnt2, cnt3;

    lesson_count = StrToInt( edtTimes->Text );
    if( rbLimitWeek1->Checked ){
      cnt1 = cnt2 = cnt3 = 0;

      for( i = atCLASS_1; i <= atCLASS_MAX; i++ )
        if( chkClasses[i-atCLASS_BASE]->Checked ) cnt1++;
      for( i = atWEEK_MON; i <= atWEEK_MAX; i++ )
        if( chkWeeks[i-atWEEK_BASE]->Checked ) cnt2++;
      for( i = atLESSON_1; i <= atLESSON_MAX; i++ )
        if( chkLessons[i-atLESSON_BASE]->Checked ) cnt3++;

      if( (lesson_count*cnt1) > (cnt2*cnt3) ){
        MessageDlg2( "배치 제한된 시수가 너무 적습니다.", "경고", mtWarning, TMsgDlgButtons() << mbOK, 0 );
        ModalResult = mrNone;
        return;
      }
    }

    if( teacher_no < 0 ) return;
    TTeacherSubject *tsbj = GetTeacherSubject( teacher_no, subject_idx );

    tsbj->SubjectCode = GetSubject(cboSubject->ItemIndex)->SubjectCode;
    tsbj->Times = lesson_count;
    tsbj->Attr = 0;
    if( chkMoveLesson->Checked ) tsbj->Attr |= 0x01;

    tsbj->Classes.Part.Year = cbYear->ItemIndex + atYEAR_BASE;
    tsbj->Classes.Part.Classes = 0;
    for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
      if( chkClasses[i-atCLASS_BASE]->Checked )
        tsbj->Classes.Part.Classes |= (1 << (i-atCLASS_BASE));
    }

    if( rbLimitWeek1->Checked ){
      tsbj->LimitWeeks = 0x0000;
      for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
        if( chkWeeks[i-atWEEK_BASE]->Checked )
          tsbj->LimitWeeks |= (1 << (i-atWEEK_BASE));
      }
      if( tsbj->LimitWeeks != 0 ) tsbj->LimitWeeks |= 0x8000;

      tsbj->LimitLessons = 0x0000;
      for( i = atLESSON_1; i <= atLESSON_MAX; i++ ){
        if( chkLessons[i-atLESSON_BASE]->Checked )
          tsbj->LimitLessons |= (1 << (i-atLESSON_BASE));
      }
      if( tsbj->LimitLessons != 0 ) tsbj->LimitLessons |= 0x8000;
    } else {
      tsbj->LimitWeeks = 0x0000;
      tsbj->LimitLessons = 0x0000;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::rbLimitWeek0Click(TObject *Sender)
{
    pnlLimitWeeks->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::rbLimitWeek1Click(TObject *Sender)
{
    pnlLimitWeeks->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacherSubject::cbYearClick(TObject *Sender)
{
    int i, y, cnt;

    y = cbYear->ItemIndex + atYEAR_BASE;
    cnt = GetLimitClass(y);
    for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
       if( i <= cnt ){
         chkClasses[i-atCLASS_BASE]->Enabled = true;
       } else {
         chkClasses[i-atCLASS_BASE]->Enabled = false;
         chkClasses[i-atCLASS_BASE]->Checked = false;
       }
    }
}
//---------------------------------------------------------------------------

