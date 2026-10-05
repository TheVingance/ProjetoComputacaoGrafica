//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#include "UJanela.h"

#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class Ponto{

	public:
	double x;
	double y;

	Ponto();
	Ponto(double nx, double ny);

	int yW2Vp(Janela mundo, Janela Vp);
	int xW2Vp(Janela mundo, Janela Vp);

	String mostra();

	void translacao(double dx, double dy);
	void escalonamento(double dx, double dy);
	void rotacao(double graus);
	void rotacaoHomogenea(double graus);

	int cohen(Janela clipping);
};
#endif
