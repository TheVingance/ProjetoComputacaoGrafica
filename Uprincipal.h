//---------------------------------------------------------------------------

#ifndef UprincipalH
#define UprincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "UJanela.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *lbMundo;
	TLabel *lbVp;
	TListBox *lbPoligonos;
	TListBox *lbPontos;
	TLabel *lbPoligono;
	TLabel *lbPonto;
	TImage *Image1;
	TButton *btIniciar;
	TButton *btLimpar;
	TButton *btBaixo;
	TButton *btCima;
	TButton *btEsquerda;
	TButton *btDireita;
	TLabel *lbZoom;
	TButton *btZoomOut;
	TButton *btZoomIn;
	TPageControl *componentes;
	TTabSheet *TabSheet1;
	TLabel *lbXMinimo;
	TLabel *lbYMinimo;
	TLabel *lbXMaximo;
	TLabel *lbYMaximo;
	TEdit *edXMin;
	TEdit *edXMax;
	TEdit *edYMin;
	TEdit *edYmax;
	TButton *btAtualizarMundo;
	TTabSheet *TabSheet2;
	TLabel *tansalacaoX;
	TLabel *transalacaoY;
	TEdit *edTranslacaoX;
	TEdit *edTranslacaoY;
	TButton *btTranslornar;
	TTabSheet *TipoReta;
	TRadioGroup *rgTipoReta;
	TButton *Circulo;
	TLabel *escalonamentoX;
	TLabel *EscalonamentoY;
	TEdit *edEscalonamentoY;
	TEdit *edEscalonamentoX;
	TButton *btEscalonar;
	TLabel *RotacaoX;
	TEdit *edRotacaoX;
	TButton *btRotacionar;
	TButton *btHomoRotacao;
	TTabSheet *Reflexoes;
	TButton *btReflexaoEixoX;
	TButton *Y;
	TButton *btEixoXY;
	TTabSheet *TabSheet3;
	TButton *btHermite;
	TButton *btCurvaCasteljau;
	TButton *btBezier;
	TButton *btBSspline;
	TButton *btSplineDifference;
	TButton *btClipping;
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall lbPoligonosClick(TObject *Sender);
	void __fastcall btIniciarClick(TObject *Sender);
	void __fastcall btLimparClick(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall btCimaClick(TObject *Sender);
	void __fastcall btAtualizarMundoClick(TObject *Sender);
	void __fastcall btBaixoClick(TObject *Sender);
	void __fastcall btEsquerdaClick(TObject *Sender);
	void __fastcall btDireitaClick(TObject *Sender);
	void __fastcall btZoomOutClick(TObject *Sender);
	void __fastcall btZoomInClick(TObject *Sender);
	void __fastcall btTranslornarClick(TObject *Sender);
	void __fastcall CirculoClick(TObject *Sender);
	void __fastcall btEscalonarClick(TObject *Sender);
	void __fastcall btRotacionarClick(TObject *Sender);
	void __fastcall btHomoRotacaoClick(TObject *Sender);
	void __fastcall btReflexaoEixoXClick(TObject *Sender);
	void __fastcall YClick(TObject *Sender);
	void __fastcall btEixoXYClick(TObject *Sender);
	void __fastcall btCurvaCasteljauClick(TObject *Sender);
	void __fastcall btBezierClick(TObject *Sender);
	void __fastcall btHermiteClick(TObject *Sender);
	void __fastcall btBSsplineClick(TObject *Sender);
	void __fastcall btSplineDifferenceClick(TObject *Sender);
	void __fastcall btClippingClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void atualizaMundo(Janela mundo);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
