//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MaseMac.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)
// user libraries
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//find the equivalence class of a in mod m, return a mod m as
int TForm1::mod(int a, int m){

	try {
		if (m == 0) {
			throw (System::UnicodeString) "Modulo by zero.";
		}
		while(a < 0) {a = a + m;}
		return a%m;
	} catch (System::UnicodeString msg) {
		errorMssg->Text = msg;
		return -1;
	}
}

//determine if m is prime, return true or false
bool TForm1::isPrime(int m) {
	bool result = true;
	for(int i = 2; i < m; i = i+1) {
		if(m%i == 0) {
			result = false;
		}
	}
	return(result);
}
//modular addition with ints a and b in mod m
int TForm1::addMod(int a, int b, int m) {
    int result = mod(a+b,m);
	return result;
}

//modular subtraction of b from a in mod m
int TForm1::subtractMod(int a, int b, int m) {
    int result = mod(a-b,m);
    return result;
}

//negate int a in mod m by subtracting m from a
int TForm1::negation(int a, int m) {
    return subtractMod(m, a, m);
}

//modular mutliplication of ints a and b in mod m, get the mod of
//the result when incrementing factor k until b
int TForm1::multiplyMod(int a, int b, int m) {
	return mod(a*b,m);
}


//find the inverse of a in mod m
//use Euclidian algorithm for greatest common divisor to determine Bezout coefficients
//one the last coefficients is equal to the inverse since the other one is 0
int TForm1::inverseMod(int a, int m) {

    try {
		if (a == 0) {
			 throw (System::UnicodeString) "Division by zero.";
		}
		vector<int> A, M, Q, R;
		int row = -1;
		A.push_back(m);
		M.push_back(a);
		while(row<0 || M[row]!=0) {
			row++;
			if(row!=0) {
				A.push_back(M[row-1]);
				M.push_back(R[row-1]);
			}

			//store remainders in R and quotients in Q
			if(M[row]==0) {
				R.push_back(0);
				Q.push_back(0);
			} else {
				R.push_back(A[row]%M[row]);
				Q.push_back((A[row]-R[row])/M[row]);
			}
		}

		if(A[row]==1) {
			vector<int> S, T;
			//fill S and T with 'row' number of zeros
			//last Bezout coefficients are going to correspond to S[0] and T[0]
			for (int k = 0; k <= row; k++) {
				S.push_back(0);
				T.push_back(0);
			}
			for (int k = row; k >= 0; k--) {
				if (k == row) {
					S[k] = A[k];
					T[k] = 0;
				} else {
					S[k] = T[k + 1];
					T[k] = S[k + 1] - Q[k] * T[k + 1];
				}
			}
			return mod(T[0],m);
		} else {
			if (m == 0) {
				throw (System::UnicodeString) "Modulo by zero.";
				}else{
					throw (System::UnicodeString) "a is not divisible by b.";
				}
		}
		} catch (System::UnicodeString msg){
			errorMssg->Text = msg;
			return -1;
		}
}


int TForm1::exponentiate(int a, int b, int m) {
	try {
		if (m == 0) {
			throw (System::UnicodeString) "Modulo by zero.";
		}
		int result;
		if(b == 0) {
			result = 1;
		} else {
			if(b < 0) {
				a = inverseMod(a,m);
				if(a == -1) {
					return -1;
				}
				b *= -1;
			}
			result = 1;
			for(int i = 1; i <= b; i++) {
				result = multiplyMod(result, a, m);
			}
		}
	return result;
	} catch (System::UnicodeString msg) {
		errorMssg->Text = msg;
		return -1;
	}

}

//modular division of int a by int b in mod m
int TForm1::divideMod(int a, int b, int m) {
	a = mod(a, m);
	b = mod(b, m);

    //determine if a is divisible by b, else return -1.
	if(inverseMod(b,m) == -1) {
		return -1;
    }
    // if a is divisible, multiply a with the inverse of b in
	// mod m, return the mod m of the result
    else {
        return multiplyMod(a, inverseMod(b, m), m);
    }
}




void __fastcall TForm1::addClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = addMod(a,b,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::subtractClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = subtractMod(a,b,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::multiplyClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = multiplyMod(a,b,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::divideClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = divideMod(a,b,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::inverseClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = inverseMod(a,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::negateClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = negation(a,m);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sqrClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
//	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = multiplyMod(a,a,m);
}


//---------------------------------------------------------------------------
void __fastcall TForm1::expClick(TObject *Sender)
{
	errorMssg->Text = "";
	int a = StrToInt(a_input->Text);
	int b = StrToInt(b_input->Text);
	int m = (int) m_input->Value;
	answer_box->Text = exponentiate(a, b, m);
}

//---------------------------------------------------------------------------



