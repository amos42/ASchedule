//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_Teacher.h"
#include "f_Thr_sbj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmTeacher *frmTeacher;

#include "Global.h"
#include "A_Util.h"
#include "filefmt/SCD_Files.h"

//---------------------------------------------------------------------------
__fastcall TfrmTeacher::TfrmTeacher(TComponent* Owner)
        : TForm(Owner)
{
    curListColor = cl3DLight;
    IsChange = false;
}
//---------------------------------------------------------------------------

void TfrmTeacher::EnableTeacherList( bool tf )
{
    TColor tc;

    pnlTeachers->Enabled = tf;
    btnItemUp->Enabled = tf;
    btnItemDown->Enabled = tf;

    if( tf )
      tc = clWindow;
    else
      tc = clBtnFace;

    lstTeacher->Color = tc;
}

void TfrmTeacher::EnableTeacherItems( bool tf )
{
    int i, j;
    TColor tc;

    pnlTeacherInfo->Enabled = tf;
//    btnAdd->Enabled = !tf;
//    btnDelete->Enabled = !tf;

    if( tf ){
      btnNewSubject->Enabled = true;
      btnDeleteSubject->Enabled = false;
      btnModifySubject->Enabled = false;
    } else {
      btnNewSubject->Enabled = false;
      btnDeleteSubject->Enabled = false;
      btnModifySubject->Enabled = false;
      lvSubjects->ItemIndex = -1;
    }

    if( tf )
      tc = clWindow;
    else
      tc = clBtnFace;

    edtTeacher->Color = tc;

    curListColor = (tf)? clWindow : cl3DLight;
    lvSubjects->Color = curListColor;
}

void TfrmTeacher::ClearTeacherItems(void)
{
    edtTeacher->Text = "";

    lvSubjects->Clear();

    pnlTeacherNo->Caption = "0 / " + IntToStr(g_iTeacherCount);
    pnlTotal->Caption = "0";
}

//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::FormCreate(TObject *Sender)
{
    IsChange = false;
    curListColor = clWindow;
}

//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::FormClose(TObject *Sender,
      TCloseAction &Action)
{
//
}

//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::FormShow(TObject *Sender)
{
  int i, j;
  PTeacherData tt;

    // 교사 데이터
    lstTeacher->Items->EndUpdate();
    lstTeacher->Clear();
    for( i = 0; i < g_iTeacherCount; i++ ){
      tt = GetTeacherData(i);
      lstTeacher->Items->Add(tt->TeacherName);
    }
    lstTeacher->Items->EndUpdate();

    btnAdd->Enabled = True;
/*
    if( g_iTeacherCount > 0 ){
      btnDelete->Enabled = True;
      btnModify->Enabled = True;
    } else {
      btnDelete->Enabled = False;
      btnModify->Enabled = False;
    }
*/
    btnModify->Caption = "편집";
    btnModify->Tag = 0;
    btnCancel->Visible = false;
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

     pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );
    pnlTotalClass->Caption = IntToStr( GetTotalClassTimes() );

    pnlTeacherNo->Caption = "0 / " + IntToStr(g_iTeacherCount);

    EnableTeacherList( g_iTeacherCount > 0 );
    ClearTeacherItems();
    EnableTeacherItems( false );

    IsChange = false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::lvSubjectsCustomDrawSubItem(
      TCustomListView *Sender, TListItem *Item, int SubItem,
      TCustomDrawState State, bool &DefaultDraw)
{
    TListView *lv = dynamic_cast<TListView *>(Sender);
    TCanvas *cnv = lv->Canvas;

    int y = StrToInt( Item->Caption );
    if( (y < atYEAR_1) || (y > atYEAR_MAX) ) return;
    int cnt = GetLimitClass(y) - atCLASS_BASE + 2;

    if( (SubItem > cnt) && (SubItem < 22) ){
       cnv->Brush->Color = clLtGray;
    } else if( (SubItem >= 22) && (SubItem <= 24) ){
       cnv->Brush->Color = clWhite;
    } else {
       cnv->Brush->Color = curListColor;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnAddClick(TObject *Sender)
{
    // 교사 하나 추가
    ReallocTeacherData( g_iTeacherCount + 1 );

    ClearTeacherData( g_iTeacherCount - 1 );

    lstTeacher->Items->Add("");
    lstTeacher->ItemIndex = g_iTeacherCount-1;
    lstTeacherClick(lstTeacher);

    pnlTeacherNo->Caption = IntToStr(g_iTeacherCount) + " / " + IntToStr(g_iTeacherCount);

    btnModify->Click();

    IsChange = true;
}

//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnDeleteClick(TObject *Sender)
{
    int i, j;
    PTeacherData ptr, tt, tt2;

    if( lstTeacher->ItemIndex < 0 ) return;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      return;
    }

    i = lstTeacher->ItemIndex;

    ptr = (PTeacherData)malloc( sizeof(TTeacherData) * (g_iTeacherCount-1) );

    tt = g_pTeachers;
    CopyMemory( ptr, tt, i*sizeof(TTeacherData) );
    tt += i + 1;
    tt2 = ptr;
    tt2 += i;
    CopyMemory( tt2, tt, (g_iTeacherCount-1-i)*sizeof(TTeacherData) );

    free( g_pTeachers );
    g_pTeachers = ptr;

    g_iTeacherCount--;

    lstTeacher->DeleteSelected();

    ClearTeacherItems();
    btnModify->Enabled = false;
    btnDelete->Enabled = false;

    pnlTeacherNo->Caption = IntToStr(0) + " / " + IntToStr(g_iTeacherCount);
    pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );

    IsChange = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::btnItemUpClick(TObject *Sender)
{
    int i;
    PTeacherData tt, tt2;
    TTeacherData tmp;
    String ss;

    if( lstTeacher->ItemIndex < 0 ) return;

    i = lstTeacher->ItemIndex;
    if( i <= 0 ) return;

    tt = &g_pTeachers[i];
    tt2 = &g_pTeachers[i-1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstTeacher->Items->Strings[i];
    lstTeacher->Items->Strings[i] = lstTeacher->Items->Strings[i-1];
    lstTeacher->Items->Strings[i-1] = ss;

    lstTeacher->ItemIndex --;

    IsChange = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::btnItemDownClick(TObject *Sender)
{
    int i;
    PTeacherData tt, tt2;
    TTeacherData tmp;
    String ss;

    if( lstTeacher->ItemIndex < 0 ) return;

    i = lstTeacher->ItemIndex;
    if( i >= lstTeacher->Items->Count-1 ) return;

    tt = &g_pTeachers[i];
    tt2 = &g_pTeachers[i+1];

    tmp = *tt;
    *tt = *tt2;
    *tt2 = tmp;

    ss = lstTeacher->Items->Strings[i];
    lstTeacher->Items->Strings[i] = lstTeacher->Items->Strings[i+1];
    lstTeacher->Items->Strings[i+1] = ss;

    lstTeacher->ItemIndex ++;

    IsChange = true;
}


//---------------------------------------------------------------------------
void __fastcall TfrmTeacher::btnModifyClick(TObject *Sender)
{
  int i, j;
  PTeacherData tt;
  long Total;

    if( btnModify->Tag == 0 ){
//      pnlTeachers->Enabled = false;
//      lstTeacher->Color = clBtnFace;
//      btnAdd->Enabled = false;
//      btnDelete->Enabled = false;
      EnableTeacherList( false );
      EnableTeacherItems( true );

      btnModify->Caption = "갱신";
      btnModify->Tag = 1;
      btnCancel->Visible = true;
    } else {
      tt = GetTeacherData( lstTeacher->ItemIndex );

      strncpy(tt->TeacherName, edtTeacher->Text.c_str(), TEACHER_NAME_SIZE);
      tt->TeacherName[TEACHER_NAME_SIZE] = '\0';

      pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );

      lstTeacher->Items->Strings[lstTeacher->ItemIndex] = edtTeacher->Text;

      EnableTeacherList( true );
      EnableTeacherItems( false );

//      pnlTeachers->Enabled = true;
//      lstTeacher->Color = clWindow;
//      btnAdd->Enabled = true;
//      btnDelete->Enabled = true;
//      EnableItems( false );

      btnModify->Caption = "편집";
      btnModify->Tag = 0;
      btnCancel->Visible = false;

//    IsChange = true;
    }
}

void __fastcall TfrmTeacher::btnCancelClick(TObject *Sender)
{
      lstTeacherClick(lstTeacher);

      EnableTeacherList( true );
      EnableTeacherItems( false );

      btnModify->Caption = "편집";
      btnModify->Tag = 0;
      btnCancel->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::lstTeacherClick(TObject *Sender)
{
    int i, j;
    PTeacherData tt;
    TSubject *sbj;
    TListItem *li;
    int y, c, y_max;

    if( lstTeacher->ItemIndex >= 0 ){
      tt = GetTeacherData( lstTeacher->ItemIndex );

      edtTeacher->Text = tt->TeacherName;

      TListView *lv = lvSubjects;
      lv->Clear();

      for( j = 0; j < MAX_TEACHER_SUBJECT; j++ ){
        TTeacherSubject *tsbj = GetTeacherSubject( lstTeacher->ItemIndex, j );
        if( (String)tsbj->SubjectCode == 0 ) continue;

        TListItem *li = lv->Items->Add();
        li->Caption = IntToStr(tsbj->Classes.Part.Year);
        sbj = FindSubjectByCode(tsbj->SubjectCode);
        li->SubItems->Add( (sbj)?sbj->ShortName:"<<null>>" );

        for( c = atCLASS_1; c <= atCLASS_MAX; c ++ ) {
          if( IS_CLASSES_IN( c, tsbj->Classes.Part.Classes ) )
            li->SubItems->Add("√");
          else
            li->SubItems->Add("");
        }
        li->SubItems->Add( IntToStr(tsbj->Times) );
        li->SubItems->Add( ((tsbj->LimitWeeks & 0x8000) || (tsbj->LimitLessons & 0x8000))? "●":"×" );
        li->SubItems->Add( (tsbj->Attr & 0x01)? "●":"" );
      }

      pnlTeacherNo->Caption = IntToStr(lstTeacher->ItemIndex+1) + " / " + IntToStr(g_iTeacherCount);
      pnlTotal->Caption = IntToStr( GetTeacherTimes( lstTeacher->ItemIndex, true ) );

      btnDelete->Enabled = True;
      btnModify->Enabled = True;
      btnItemUp->Enabled = True;
      btnItemDown->Enabled = True;
    } else {
      btnDelete->Enabled = False;
      btnModify->Enabled = False;
      btnItemUp->Enabled = False;
      btnItemDown->Enabled = False;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::lvSubjectsSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
    btnModifySubject->Enabled = Selected;
    btnDeleteSubject->Enabled = Selected;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnNewSubjectClick(TObject *Sender)
{
    int idx = GetTeacherSubjectCount( lstTeacher->ItemIndex );
    if( idx >= MAX_TEACHER_SUBJECT ) return;

    TTeacherSubject *sbj = GetTeacherSubject( lstTeacher->ItemIndex, idx );
    memset( sbj, 0, sizeof(TTeacherSubject) );
    frmTeacherSubject->SetTeacherSubjectNo( lstTeacher->ItemIndex, idx );

    if( frmTeacherSubject->ShowModal() == mrOk ){
      pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );
      lstTeacherClick(lstTeacher);
      IsChange = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnModifySubjectClick(TObject *Sender)
{
    if( lvSubjects->Selected == NULL ) return;

    frmTeacherSubject->SetTeacherSubjectNo( lstTeacher->ItemIndex, lvSubjects->Selected->Index );

    if( frmTeacherSubject->ShowModal() == mrOk ){
      pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );
      lstTeacherClick(lstTeacher);
      IsChange = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnDeleteSubjectClick(TObject *Sender)
{
    if( lvSubjects->Selected == NULL ) return;

    if( MessageDlg2( "정말 삭제하시겠습니까?", "삭제 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes ){
      TTeacherSubject *sbj = GetTeacherSubject( lstTeacher->ItemIndex, lvSubjects->Selected->Index );
      memset( sbj, 0, sizeof(TTeacherSubject) );
      PackTeacherSubject( lstTeacher->ItemIndex );

      pnlTotalAll->Caption = IntToStr( GetTotalTeacherTimes() );
      lstTeacherClick(lstTeacher);
      IsChange = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTeacher::btnImportClick(TObject *Sender)
{
    if( dlgOpen->Execute() ){
      if( ! LoadTeacherData( dlgOpen->FileName.c_str() ) ){
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

void __fastcall TfrmTeacher::btnExportClick(TObject *Sender)
{
    if( dlgSave->Execute() ){
      SaveTeacherData( dlgSave->FileName.c_str() );
      MessageDlg2( "저장되었습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
   }
}
//---------------------------------------------------------------------------

