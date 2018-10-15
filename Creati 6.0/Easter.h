//---------------------------------------------------------------------------

#ifndef EasterH
#define EasterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TAuthor : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TButton *Button1;
        TMemo *Memo1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Button2;
        TButton *Button3;
        TBevel *Bevel1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TAuthor(TComponent* Owner);
        AnsiString Path;
};
//---------------------------------------------------------------------------
extern PACKAGE TAuthor *Author;
//---------------------------------------------------------------------------
#endif

