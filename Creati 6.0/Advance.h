//---------------------------------------------------------------------------

#ifndef AdvanceH
#define AdvanceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TStatus : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TButton *Button1;
        TCGauge *ProgressBar1;
        TLabel *Label2;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TStatus(TComponent* Owner);
        bool Canceled;
};
//---------------------------------------------------------------------------
extern PACKAGE TStatus *Status;
//---------------------------------------------------------------------------
#endif
