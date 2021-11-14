//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("f_ABOUT.cpp", frmAbout);
USEFORM("f_MAIN.cpp", frmMain);
USEFORM("f_CHANGE.cpp", frmChange);
USEFORM("f_CONFIG.cpp", frmConfig);
USEFORM("f_SCDINFO.cpp", frmScheduleInfo);
USEFORM("f_SCHOOL.cpp", frmSchool);
USEFORM("f_SBJ.cpp", frmSubject);
USEFORM("f_TEACHER.cpp", frmTeacher);
USEFORM("f_THR_SBJ.cpp", frmTeacherSubject);
USEFORM("f_MOVLSN.cpp", frmMoveLesson);
USEFORM("f_PERSONAL.cpp", frmPersonal);
USEFORM("f_Sclass.cpp", frmClass);
USEFORM("f_SPLASH.cpp", frmSplash);
USEFORM("f_Sview.cpp", frmView);
USEFORM("r_teacher.cpp", qrTeachers); /* TQuickRep: File Type */
USEFORM("r_schdule.cpp", qrSchedules);
USEFORM("r_classes.cpp", qrClasses); /* TQuickRep: File Type */
//---------------------------------------------------------------------------
#include "f_splash.h"
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
         Application->Initialize();
         Application->Title = "ASchedule";

          // Splash À©µµ¿ì
         frmSplash = new TfrmSplash((TComponent *)Application);
         frmSplash->Show();
         frmSplash->Update();

         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmSplash), &frmSplash);
         Application->CreateForm(__classid(TfrmAbout), &frmAbout);
         Application->CreateForm(__classid(TfrmChange), &frmChange);
         Application->CreateForm(__classid(TfrmConfig), &frmConfig);
         Application->CreateForm(__classid(TfrmScheduleInfo), &frmScheduleInfo);
         Application->CreateForm(__classid(TfrmPersonal), &frmPersonal);
         Application->CreateForm(__classid(TfrmClass), &frmClass);
         Application->CreateForm(__classid(TfrmTeacher), &frmTeacher);
         Application->CreateForm(__classid(TfrmTeacherSubject), &frmTeacherSubject);
         Application->CreateForm(__classid(TqrTeachers), &qrTeachers);
         Application->CreateForm(__classid(TqrSchedules), &qrSchedules);
         Application->CreateForm(__classid(TqrClasses), &qrClasses);
         Application->CreateForm(__classid(TfrmSubject), &frmSubject);
         Application->CreateForm(__classid(TfrmSchool), &frmSchool);
         Application->CreateForm(__classid(TfrmMoveLesson), &frmMoveLesson);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
