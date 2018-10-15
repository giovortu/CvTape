//---------------------------------------------------------------------------

#ifndef SelDirH
#define SelDirH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TSelect : public TForm
{
__published:	// IDE-managed Components
        TDriveComboBox *DriveComboBox1;
        TDirectoryListBox *DirectoryListBox1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelect *Select;
//---------------------------------------------------------------------------
#endif
