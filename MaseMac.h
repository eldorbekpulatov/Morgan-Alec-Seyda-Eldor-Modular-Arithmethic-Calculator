//---------------------------------------------------------------------------

#ifndef MaseMacH
#define MaseMacH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Header.hpp>
#include <FMX.Objects.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
// user libraries
#include <iostream>
#include <vector>
#include <deque>
using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *a_label;
	TLabel *b_label;
	TLabel *m_label;
	THeader *header;
	THeaderItem *title;
	TPanel *actionButtons;
	TButton *add;
	TButton *subtract;
	TButton *multiply;
	TButton *divide;
	TButton *inverse;
	TButton *sqr;
	TButton *exp;
	TButton *negate;
	TPanel *inputs;
	TPanel *answer_panel;
	TEdit *answer_box;
	TLabel *answer_label;
	TLabel *errorMssg;
	TEdit *a_input;
	TEdit *b_input;
	TNumberBox *m_input;
	TPanel *mssg_panel;

	bool __fastcall isPrime(int m);
	int __fastcall mod(int a, int m);

	int __fastcall addMod(int a, int b, int m);
	int __fastcall subtractMod(int a, int b, int m);
	int __fastcall multiplyMod(int a, int b, int m);
	int __fastcall divideMod(int a, int b, int m);
	int __fastcall negation(int a, int m);
	int __fastcall inverseMod(int a, int m);
	int __fastcall exponentiate(int a, int b, int m);


	void __fastcall addClick(TObject *Sender);
	void __fastcall subtractClick(TObject *Sender);
	void __fastcall multiplyClick(TObject *Sender);
	void __fastcall divideClick(TObject *Sender);
	void __fastcall negateClick(TObject *Sender);
	void __fastcall inverseClick(TObject *Sender);
	void __fastcall sqrClick(TObject *Sender);
	void __fastcall expClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

