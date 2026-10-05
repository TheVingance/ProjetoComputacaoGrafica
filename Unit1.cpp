//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Ponto::Ponto(){

 x = y = 0;
}

Ponto::Ponto(double nx, double ny){
 x = nx;
 y = ny;

}

int Ponto::xW2Vp(Janela mundo, Janela Vp){
	return  ((x  - mundo.xMin) / (mundo.xMax - mundo.xMin)) *
	(Vp.xMax - Vp.xMin);
}

int Ponto::yW2Vp(Janela mundo, Janela Vp){

	return (1-((y - mundo.yMin) / (mundo.yMax - mundo.yMin))) *
	(Vp.yMax - Vp.yMin);
}

String Ponto::mostra(){
  if (!this) return "()";
  try {
    return "( " + FloatToStr(x) + "; " + FloatToStr(y) + " )";
  } catch (...) {
    return "( 0; 0 )";
  }
}

void Ponto::translacao(double dx, double dy){
	x += dx;
	y += dy;
}

void Ponto::escalonamento(double dx, double dy){
	x *= dx;
	y *= dy;

}

void Ponto::rotacao(double graus){
	double xTemp = x;
	double theta = graus * (M_PI / 180.0);
	x = (xTemp) * cos(theta) - y  * sin(theta);
	y = (xTemp) * sin(theta) + y * cos(theta);

}

void Ponto::rotacaoHomogenea(double graus){
	double xTemp = x;
	double theta = graus * (M_PI / 180.0);
	x = (xTemp) * cos(theta) - y  * sin(theta);
	y = (xTemp) * sin(theta) + y * cos(theta);

}

int Ponto::cohen(Janela clipping){
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

