//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Ponto::Ponto(){    // Construtor padrão: inicializa as coordenadas na origem (0, 0)
 x = y = 0;
}

Ponto::Ponto(double nx, double ny){    // Construtor parametrizado: inicializa o ponto com coordenadas (nx, ny)
 x = nx;
 y = ny;
}

int Ponto::xW2Vp(Janela mundo, Janela Vp){    // Mapeamento de coordenadas (World to Viewport): converte X de mundo para pixel na tela
	return  ((x  - mundo.xMin) / (mundo.xMax - mundo.xMin)) *
	(Vp.xMax - Vp.xMin);
}

int Ponto::yW2Vp(Janela mundo, Janela Vp){    // Mapeamento de coordenadas (World to Viewport): converte Y de mundo para pixel na tela (com inversão do eixo Y)
	return (1-((y - mundo.yMin) / (mundo.yMax - mundo.yMin))) *
	(Vp.yMax - Vp.yMin);
}

String Ponto::mostra(){    // Retorna a representação formatada do ponto em texto: ( x; y )
  if (!this) return "()";
  try {
    return "( " + FloatToStr(x) + "; " + FloatToStr(y) + " )";
  } catch (...) {
    return "( 0; 0 )";
  }
}

void Ponto::translacao(double dx, double dy){    // Deslocamento 2D: translada o ponto somando os incrementos dx e dy
	x += dx;
	y += dy;
}

void Ponto::escalonamento(double dx, double dy){    // Escalonamento 2D: multiplica as coordenadas do ponto pelos fatores dx e dy
	x *= dx;
	y *= dy;
}

void Ponto::rotacao(double graus){    // Rotação 2D: rotaciona o ponto em torno da origem pelo ângulo em graus
	double xTemp = x;
	double theta = graus * (M_PI / 180.0);
	x = (xTemp) * cos(theta) - y  * sin(theta);
	y = (xTemp) * sin(theta) + y * cos(theta);
}

void Ponto::rotacaoHomogenea(double graus){    // Rotação 2D Homogênea: calcula novas coordenadas trigonométricas
	double xTemp = x;
	double theta = graus * (M_PI / 180.0);
	x = (xTemp) * cos(theta) - y  * sin(theta);
	y = (xTemp) * sin(theta) + y * cos(theta);
}

int Ponto::cohen(Janela clipping){    // Algoritmo de Cohen-Sutherland: calcula o código de região (Outcode de 4 bits)
	int regionCode = 0;

	if (x < clipping.xMin)
		regionCode += 1;
	if (x > clipping.xMax)
		regionCode += 2;
	if (y < clipping.yMin)
		regionCode += 4;
	if (y > clipping.yMax)
		regionCode += 8;

	return regionCode;
}

