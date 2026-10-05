//---------------------------------------------------------------------------
#ifndef uDisplayFileH
#define uDisplayFileH

#include "uPoligono.h"
#include "uObjeto3D.h"
#include "UJanela.h"
#include <vector>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class DisplayFile{
	public:
	  std::vector <Poligono> poligonos;
	  std::vector <Objeto3D> objetos3D;
	  int tipoProjecao3D;      // 0: Ortografica, 1: Perspectiva, 2: Cavaleira
	  double distPerspectiva;  // Distancia do observador para perspectiva

	  DisplayFile();
	  void desenha(TCanvas *canvas, Janela mundo,
				   Janela vp, int tipoReta);
	  void mostra(TListBox *listbox);
};

#endif
