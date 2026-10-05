//---------------------------------------------------------------------------
#pragma hdrstop
#include "uDisplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void DisplayFile::desenha(TCanvas *canvas,Janela mundo,Janela vp, int tipoReta){    // Limpa o Canvas e redesenha todos os polígonos da cena
  canvas->Brush->Color = clSilver;
  canvas->FillRect(Rect(0,0,500,500));

  canvas->Pen->Color = clBlack;
  canvas->Pen->Width = 3;

  for(int i = 0; i < poligonos.size(); i++){
	poligonos[i].desenha(canvas, mundo, vp, tipoReta);    
  }
}

void DisplayFile::mostra(TListBox *listbox){    // Atualiza a lista visual do formulário com o resumo de cada polígono da cena
  listbox->Items->Clear();
  for (int i = 0; i < poligonos.size(); i++) {
	  poligonos[i].mostra(listbox);
  }
}

