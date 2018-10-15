//---------------------------------------------------------------------------

#ifndef Easter2H
#define Easter2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TPhoto : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TLabel *Label1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPhoto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPhoto *Photo;
//---------------------------------------------------------------------------
#endif
