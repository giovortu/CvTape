//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TDebug : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TDebug(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TDebug *Debug;
//---------------------------------------------------------------------------
#endif
