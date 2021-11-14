//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_SBJ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmSubject *frmSubject;

#include "Global.h"
#include "A_Util.h"
#include "filefmt/SCD_Files.h"

//---------------------------------------------------------------------------
__fastcall TfrmSubject::TfrmSubject(TComponent* Owner)
        : TForm(Owner)
{
    IsChange = false;
}
//---------------------------------------------------------------------------

void TfrmSubject::EnableSubjectList( bool tf )
{
    TColor tc;

    pnlSubjects->Enabled = tf;
    btnItemUp->Enabled = tf;
    btnItemDown->Enabled = tf;

    if( tf )
      tc = clWindow;
    else
      tc = clBtnFace;

    lstSubject->Color = tc;
}

void TfrmSubject::EnableSubjectItems( bool tf )
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

    edtSubjectCode->Color = tc;
    edtName->Color = tc;
    edtSubName->Color = tc;
}

void TfrmSubject::ClearSubjectItems( void )
{
    edtSubjectCode->Text = "";
    edtName->Text = "";
    edtSubName->Text = "";

    chkYear1->Checked = false;
    chkYear2->Checked = false;
    chkYear3->Checked = false;
}

void __fastcall TfrmSubject::FormCreate(TObject *Sender)
{
//
}


void __fastcall TfrmSubject::FormShow(TObject *Sender)
{
    int i, j;
    TSubject *sbj;
    TColor tc;

    // 교사 데이터
    lstSubject->Items->EndUpdate();
    lstSubject->Clear();
    for( i = 0; i < g_iSubjectCount; i++ ){
      sbj = &g_pSubjects[i];
      lstSubject->Items->Add(sbj->FullName);
    }
    lstSubject->Items->EndUpdate();

    btnAdd->Enabled = true;
    btnModify->Tag = 0;
    btnCancel->Visible = false;
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

    EnableSubjectList( g_iSubjectCount > 0 );
    EnableSubjectItems( false );
    ClearSubjectItems();

    IsChange = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSubject::BitBtn1Click(TObject *Sender)
{
    Close();
}

void __fastcall TfrmSubject::btnSpcDelClick(TObject *Sender)
{
    int i, j;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }
}


void __fastcall TfrmSubject::btnAddClick(TObject *Sender)
{
    // 과목 하나 추가
    ReallocSubjectData( g_iSubjectCount + 1 );

    lstSubject->Items->Add("");
    lstSubject->ItemIndex = g_iSubjectCount-1;

    lstSubjectClick(lstSubject);

    btnModify->Enabled = true;
    btnModify->Click();

    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnDeleteClick(TObject *Sender)
{
    int i, j;
    TSubject *ptr, *tt, *tt2;

    if( lstSubject->ItemIndex < 0 ) return;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }

    i = lstSubject->ItemIndex;

    ptr = (TSubject *)malloc( sizeof(TSubject) * (g_iSubjectCount-1) );

    tt = g_pSubjects;
    CopyMemory( ptr, tt, i*sizeof(TSubject) );
    tt += i + 1;
    tt2 = ptr;
    tt2 += i;
    CopyMemory( tt2, tt, (g_iSubjectCount-1-i)*sizeof(TSubject) );

    free( g_pSubjects );
    g_pSubjects = ptr;

    g_iSubjectCount--;

    lstSubject->DeleteSelected();

    ClearSubjectItems();
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnModifyClick(TObject *Sender)
{
  int i, j;
  TSubject *sbj;
  long code;

    if( btnModify->Tag == 0 ){
      EnableSubjectList( false );
      EnableSubjectItems( true );

      btnModify->Caption = "갱신";
      btnModify->Tag = 1;
      btnCancel->Visible = true;
    } else {
      // 교사 데이터
      code = StrToInt(edtSubjectCode->Text);
      for( i = 0; i < g_iSubjectCount; i++ ){
        sbj = &g_pSubjects[i];
        if( code == sbj->SubjectCode ){
          MessageDlg2( "과목 코드가 중복되었습니다.", "에러", mtWarning, TMsgDlgButtons() << mbOK, 0 );
          return;
        }
      }

      sbj = &g_pSubjects[ lstSubject->ItemIndex ];

      sbj->SubjectCode = code;
      strncpy(sbj->FullName, edtName->Text.c_str(), SUBJECT_NAME_SIZE);
      sbj->FullName[SUBJECT_NAME_SIZE] = '\0';
      strncpy(sbj->ShortName, edtSubName->Text.c_str(), SUBJECT_SHORTNAME_SIZE);
      sbj->ShortName[SUBJECT_SHORTNAME_SIZE] = '\0';

      lstSubject->Items->Strings[lstSubject->ItemIndex] = edtName->Text;

      EnableSubjectList( true );
      EnableSubjectItems( false );

      btnModify->Caption = "편집";
      btnModify->Tag = 0;
      btnCancel->Visible = false;

      IsChange = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnCancelClick(TObject *Sender)
{
    lstSubjectClick(lstSubject);

    EnableSubjectList( true );
    EnableSubjectItems( false );

    btnModify->Caption = "편집";
    btnModify->Tag = 0;
    btnCancel->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::lstSubjectClick(TObject *Sender)
{
    int i, j;
    TSubject *sbj;
    int y, c, y_max;

    if( lstSubject->ItemIndex >= 0 ){
      sbj = &g_pSubjects[ lstSubject->ItemIndex ];

      edtSubjectCode->Text = IntToStr(sbj->SubjectCode);
      edtName->Text = sbj->FullName;
      edtSubName->Text = sbj->ShortName;

/*
      curYear = ml->Classes.Part.Year;

      switch( curYear ){
        case atYEAR_1 : btnYear1->Down = true; btnYearClick(btnYear1); break;
        case atYEAR_2 : btnYear2->Down = true; btnYearClick(btnYear2); break;
        case atYEAR_3 : btnYear3->Down = true; btnYearClick(btnYear3); break;
      }
      for( c = atCLASS_1; c <= GetLimitClass(curYear); c++ ){
        if( IS_CLASSES_IN(c, ml->Classes.Part.Classes) ) lstClass->Checked[c-atCLASS_BASE] = true;
      }
*/

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

void __fastcall TfrmSubject::btnItemUpClick(TObject *Sender)
{
    int i;
    TSubject *tt, *tt2;
    TSubject tmp;
    String ss;

    if( lstSubject->ItemIndex < 0 ) return;

    i = lstSubject->ItemIndex;
    if( i <= 0 ) return;

    tt = &g_pSubjects[i];
    tt2 = &g_pSubjects[i-1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstSubject->Items->Strings[i];
    lstSubject->Items->Strings[i] = lstSubject->Items->Strings[i-1];
    lstSubject->Items->Strings[i-1] = ss;

    lstSubject->ItemIndex --;

//    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnItemDownClick(TObject *Sender)
{
    int i;
    TSubject *tt, *tt2;
    TSubject tmp;
    String ss;

    if( lstSubject->ItemIndex < 0 ) return;

    i = lstSubject->ItemIndex;
    if( i >= lstSubject->Items->Count-1 ) return;

    tt = &g_pSubjects[i];
    tt2 = &g_pSubjects[i+1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstSubject->Items->Strings[i];
    lstSubject->Items->Strings[i] = lstSubject->Items->Strings[i+1];
    lstSubject->Items->Strings[i+1] = ss;

    lstSubject->ItemIndex ++;

//    IsChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnImportClick(TObject *Sender)
{
    if( dlgOpen->Execute() ){
      if( ! LoadSubjectData( dlgOpen->FileName.c_str() ) ){
        MessageDlg2( "파일 열기에 실패했습니다.\n\n"
                    "잘못된 파일이거나 구버전 파일 형식입니다.", "메시지",
                    mtWarning, TMsgDlgButtons() << mbOK, 0 );
        return;
      }

      FormShow(this);
    }

    IsChange = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::btnExportClick(TObject *Sender)
{
    if( dlgSave->Execute() ){
      SaveSubjectData( dlgSave->FileName.c_str() );
      MessageDlg2( "저장되었습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSubject::SpeedButton1Click(TObject *Sender)
{
    TSubject *sbj;
    int i, maxcode;

    // 교사 데이터
    maxcode = 1;
    for( i = 0; i < g_iSubjectCount; i++ ){
      sbj = &g_pSubjects[i];
      if( maxcode == sbj->SubjectCode ){
        maxcode++;
        i = 0;  // 처음부터 다시
      }
    }

    edtSubjectCode->Text = IntToStr(maxcode);
}
//---------------------------------------------------------------------------

