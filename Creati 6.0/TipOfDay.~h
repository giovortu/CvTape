//---------------------------------------------------------------------------

#ifndef TipOfDayH
#define TipOfDayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#define ROW 7
//---------------------------------------------------------------------------
class TTips : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TMemo *Memo1;
        TButton *CloseTipsBtn;
        TButton *NextTipBtn;
        TImage *Image1;
        TStaticText *StaticText1;
        TComboBox *ComboBox1;
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall NextTipBtnClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CloseTipsBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTips(TComponent* Owner);
        bool ShowTips;
        AnsiString File;
        TStringList *St;

};
//---------------------------------------------------------------------------
extern PACKAGE TTips *Tips;
//---------------------------------------------------------------------------
#endif
