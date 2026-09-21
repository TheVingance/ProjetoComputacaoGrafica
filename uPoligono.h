//---------------------------------------------------------------------------
#ifndef uPoligonoH
#define uPoligonoH
#include "Unit1.h"
#include <vector>
//---------------------------------------------------------------------------
class Poligono{
	public:
	  int id;
	  char tipo;
	  std::vector<Ponto>pontos;

	  void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);
	  void mostra(TListBox *listbox);
	  void mostraPontos(TListBox *listbox);
	  void translacao(double dx, double dy);
	  void escalonamento(double dx, double dy);
	  void rotacao(double graus);
	  void rotacaoHomogenea(double graus);
	  void desenharDDA(Ponto p1,Ponto p2,Janela mundo,Janela vp,
	  TCanvas *canvas);
	  void desenharBRESENHAM(Ponto p1,Ponto p2,Janela mundo,Janela vp,
	  TCanvas *canvas);
	  void DesenhaCircunferencia (int xc, int yc, int r);
	  void DesenhaPontoCircunferencia(int xc, int yc, int x, int y);
	  Ponto pontoMedio();
	  void reflexaoEixoX();
	  void reflexaoEixoY();
	  void reflexaoEixoXY();
	  void casteljau(Ponto p0, Ponto p1, Ponto p2);
	  void casteljauRecursivo(Ponto p0, Ponto p1, Ponto p2);
	  void hermite(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
	  void bezier(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
	  void bSpline(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
	  void fwdDifferences(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
	  Ponto novoPonto(Ponto aux, double x, double y);
	  Poligono clipping(Janela clip);
};

#endif


