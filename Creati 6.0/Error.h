//---------------------------------------------------------------------------
#ifndef ErrorH
#define ErrorH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TError1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *Button1;
	TLabel *Label1;
	void __fastcall Button1Click(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TError1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TError1 *Error1;
//---------------------------------------------------------------------------
#endif
