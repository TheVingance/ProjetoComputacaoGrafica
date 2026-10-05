//---------------------------------------------------------------------------
#pragma hdrstop
#include "uDisplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DisplayFile::DisplayFile() {
  tipoProjecao3D = 1;      // Perspectiva por padrão
  distPerspectiva = 400.0; // Distância focal padrão
}

void DisplayFile::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta) { // Limpa o Canvas e redesenha todos os polígonos e objetos 3D da cena
  canvas->Brush->Color = clSilver;
  canvas->FillRect(Rect(0, 0, 500, 500));

  canvas->Pen->Color = clBlack;
  canvas->Pen->Width = 3;

  // Desenha polígonos 2D
  for (size_t i = 0; i < poligonos.size(); i++) {
    poligonos[i].desenha(canvas, mundo, vp, tipoReta);
  }

  // Desenha modelos de arame 3D com a projeção selecionada
  for (size_t i = 0; i < objetos3D.size(); i++) {
    objetos3D[i].desenha(canvas, mundo, vp, tipoReta, tipoProjecao3D, distPerspectiva);
  }
}

void DisplayFile::mostra(TListBox *listbox) { // Atualiza a lista visual do formulário com polígonos e objetos 3D
  listbox->Items->Clear();
  for (size_t i = 0; i < poligonos.size(); i++) {
    poligonos[i].mostra(listbox);
  }
  for (size_t i = 0; i < objetos3D.size(); i++) {
    objetos3D[i].mostra(listbox);
  }
}
