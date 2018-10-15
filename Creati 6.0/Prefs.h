//---------------------------------------------------------------------------
#ifndef PrefsH
#define PrefsH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\FileCtrl.hpp>
#include <vcl\ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TPreferences : public TForm
{
__published:	// IDE-managed Components
        TButton *ClosePrefsBtn;
        TSaveDialog *SaveLog;
        TPageControl *PageControl1;
        TTabSheet *General;
        TTabSheet *Batch;
        TTabSheet *LogFile;
        TCheckBox *ModifyCheckBox;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TEdit *Edit1;
        TButton *Button2;
        TTabSheet *Language;
        TCheckBox *TipsCheckBox;
        TCheckBox *LogCheckBox;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ClosePrefsBtnClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall LogCheckBoxClick(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TPreferences(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPreferences *Preferences;
//---------------------------------------------------------------------------
#endif
