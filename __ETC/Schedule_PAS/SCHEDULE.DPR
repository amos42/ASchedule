program SCHEDULE;

uses
  Forms,
  windows,
  Global in 'GLOBAL.PAS',
  f_main in 'F_MAIN.PAS' {frmMain},
  f_splash in 'f_splash.pas' {frmSplash},
  f_about in 'f_about.pas' {frmAbout},
  f_config in 'f_config.pas' {frmConfig},
  f_SINIT in 'f_SINIT.PAS' {frmSInit},
  f_TEACHER in 'f_TEACHER.PAS' {frmTeacher},
  f_PERSONAL in 'F_PERSONAL.PAS' {frmPersonal},
  f_SCLASS in 'f_SCLASS.PAS' {frmClass},
  f_SVIEW in 'f_SVIEW.PAS' {frmView},
  f_CHANGE in 'f_CHANGE.PAS' {frmChange},
  r_schdule in 'r_schdule.pas' {qrSchedules: TQuickRep},
  A_Util in 'A_Util.pas',
  r_teacher in 'r_teacher.pas' {qrTeachers: TQuickRep},
  r_classes in 'r_classes.pas' {qrClasses: TQuickRep};

const
  ctNORMAN = 0;
  ctMULTIPLE = 1;
  ctFIXED = 2;

{$R *.RES}

begin
  Application.Title := 'Amos-Schedule';

  // Splash À©µµ¿ì
  frmSplash := TfrmSplash.Create(Application);
  frmSplash.Show();
  frmSplash.Update();

  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(TfrmSInit, frmSInit);
  Application.CreateForm(TfrmTeacher, frmTeacher);
  Application.CreateForm(TfrmClass, frmClass);
  Application.CreateForm(TfrmAbout, frmAbout);
  Application.CreateForm(TfrmConfig, frmConfig);
  Application.CreateForm(TfrmChange, frmChange);
  Application.CreateForm(TfrmPersonal, frmPersonal);
  Application.CreateForm(TqrSchedules, qrSchedules);
  Application.CreateForm(TqrTeachers, qrTeachers);
  Application.CreateForm(TqrClasses, qrClasses);
  Application.Run;
end.
