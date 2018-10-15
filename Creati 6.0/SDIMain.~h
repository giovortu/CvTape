//----------------------------------------------------------------------------
#ifndef SDIMainH
#define SDIMainH
//----------------------------------------------------------------------------


#include "Trayicon.h"
#include <Classes.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>


class CreatiDecode;

//----------------------------------------------------------------------------
class TSDIAppForm : public TForm
{
__published:
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TStatusBar *StatusBar;
	TMemo *Memo1;
	TImage *Image1;
	TLabel *Label1;
	TBevel *Bevel3;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TUpDown *UpDown1;
        TImageList *ImageList1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox1;
        TGroupBox *GroupBox4;
        TImage *LeftCh;
        TOpenDialog *OpenMulti;
        TSaveDialog *SaveMulti;
        TPrintDialog *PrintDialog1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Edit2;
        TMenuItem *Help1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TMenuItem *Preferences1;
        TMenuItem *Copy1;
        TMenuItem *Cut1;
        TMenuItem *Paste1;
        TMenuItem *N2;
        TMenuItem *About1;
        TMenuItem *N3;
        TMenuItem *Contents1;
        TMenuItem *Gallery1;
        TToolBar *ToolBar1;
        TToolButton *OpenButton;
        TToolButton *SaveButton;
        TToolButton *InfoButton;
        TToolButton *DecodeButton;
        TToolButton *ToolButton5;
        TToolButton *PrefsButton;
        TToolButton *GalleryButton;
        TToolButton *ToolButton8;
        TToolButton *HelpButton;
        TToolButton *AboutButton;
        TToolButton *PrintButton;
        TToolButton *BatchButton;
        TToolButton *ToolButton13;
        TToolButton *ToolButton14;
        TMenuItem *View1;
        TMenuItem *WaveInfo1;
        TMenuItem *Preview1;
        TMenuItem *N4;
        TMenuItem *CreatiVemuHomepage1;
        TMenuItem *GoSoftware1;
        TMenuItem *MadrigalHandheld1;
        TMenuItem *Print1;
        TMenuItem *N5;
        TToolButton *CopyButton;
        TToolButton *PasteButton;
        TToolButton *CutButton;
        TToolButton *ToolButton18;
        TMenuItem *Onlinesupport1;
        TMenuItem *N6;
        TMenuItem *Decode1;
        TMenuItem *Batchconversion1;
        TRadioGroup *RadioGroup1;
        TRadioButton *AmButton;
        TRadioButton *FmButton;
        TMenuItem *N7;
        TMenuItem *Tipoftheday1;
        TImage *RightCh;
        TRadioButton *LeftChRadio;
        TRadioButton *RightChRadio;
        TBevel *Bevel1;
        TBevel *Bevel2;
	void __fastcall ShowHint(TObject *Sender);
	void __fastcall ExitItemClick(TObject *Sender);
	void __fastcall OpenItemClick(TObject *Sender);
	void __fastcall SaveItemClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall Setpreferences1Click(TObject *Sender);
	void __fastcall DecodeClick(TObject *Sender);
	void __fastcall Contents1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall OpenDialogClose(TObject *Sender);
        void __fastcall HomePageClick(TObject *Sender);
        void __fastcall CveHomeClick(TObject *Sender);
        void __fastcall MadHomeClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PrintClick(TObject *Sender);
        void __fastcall Image1DblClick(TObject *Sender);
        void __fastcall BatchClick(TObject *Sender);
        void __fastcall WaveInfo1Click(TObject *Sender);
        void __fastcall AmButtonClick(TObject *Sender);
        void __fastcall FmButtonClick(TObject *Sender);
        void __fastcall Tipoftheday1Click(TObject *Sender);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall DecodeButtonClick(TObject *Sender);
private:

protected:
public:
	virtual __fastcall TSDIAppForm(TComponent *AOwner);
    bool IsSaved,IsLoaded,AutoTreshold,MRUOpen;
    bool WaveInfoFormVisible;
    int  WaveInfoPosX;
    int  WaveInfoPosY;    
    bool CanModify,SaveLog,ProgressiveName,Canc,ShowTips;
    bool Fm;
    int  ProgressiveCount;
    AnsiString ManualTreshold;
    AnsiString AppPath,HelpDir,GalleryDir;
    AnsiString LogFile;
    AnsiString TipFile;
    int Channel;

    AnsiString FileName,BatchDir;
    Graphics::TBitmap *Buffer;
    CreatiDecode *CvTape;

};
//----------------------------------------------------------------------------
extern TSDIAppForm *SDIAppForm;
//----------------------------------------------------------------------------
#endif
