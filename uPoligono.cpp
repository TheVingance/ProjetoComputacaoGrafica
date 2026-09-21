//---------------------------------------------------------------------------
#pragma hdrstop

#include "uPoligono.h"
#include "Unit1.h"
#include "Uprincipal.h"
#include "UJanela.h"
#include "CG1PCH1.h"
#include "uPoligono.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define SIGN(x) ((x) < 0 ? (-1): (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((x) < 0 ? ( (x) - (int)(x) != 0 ? ((int)(x) - 1) : ((int)(x))) : (int)(x))

// Algoritmo DDA (Digital Differential Analyzer) para traçado de retas
void Poligono::desenharDDA(Ponto p1, Ponto p2, Janela mundo, Janela vp,TCanvas
				*canvas){

	int x2, x1, y2, y1;

	int length, i;
	double deltax, deltay, x, y;

	x1 = p1.xW2Vp(mundo, vp);
	x2 = p2.xW2Vp(mundo, vp);
	y1 = p1.yW2Vp(mundo, vp);
	y2 = p2.yW2Vp(mundo, vp);

	if	(ABS((x2 - x1)) >= ABS((y2 - y1)))
		length = ABS((x2 - x1));
	else
		length = ABS( (y2 - y1) );
		deltax = (float) (x2- x1) / (float) length;
		deltay = (float) (y2- y1) / (float) length;

	x = x1 + 0.5 * SIGN (deltax);
	y = y1 + 0.5 * SIGN (deltay);

	for (i = 0; i < length; i++) {
		//setPixel( FLOOR(x), FLOOR(y));
		canvas->Pixels[FLOOR(x)][FLOOR(y)] = clBlue;
		x += deltax;
		y += deltay;
	}
}

#define FALSE 0
#define TRUE 1

// Algoritmo de Bresenham para traçado de retas (aritmetica inteira)
void Poligono::desenharBRESENHAM(Ponto p1, Ponto p2, Janela mundo, Janela vp,
			TCanvas *canvas){

	int x2, x1, y2, y1;

	bool interchange;
	int deltax, deltay, x, y, tmp;
	int signaly, signalx, erro;

	x1 = p1.xW2Vp(mundo, vp);
	x2 = p2.xW2Vp(mundo, vp);
	y1 = p1.yW2Vp(mundo, vp);
	y2 = p2.yW2Vp(mundo, vp);


	deltax = ABS ((x2 - x1));
	deltay = ABS ((y2 - y1));
	signalx = SIGN ((x2 - x1));
	signaly = SIGN ((y2 - y1));

	x = x1;
	y = y1;

	if (signalx < 0)
		x -=1;
	if (signaly < 0 )
		y -= 1;

	// trocar deltax com deltay dependendo da inclinacao da reta
	interchange = FALSE;
	if ( deltay > deltax) {
		tmp = deltax;
		deltax = deltay;
		deltay = tmp;
		interchange = TRUE;
	}
	erro = 2 * deltay - deltax;

	int i;
	for (i = 0; i < deltax; i++) {
		//setPixel( x, y);
		canvas->Pixels[x][y] = clRed;

		while (erro >= 0) {

			if (interchange)
				x = x + signalx;
			else
				y = y + signaly;
				erro = erro - 2 * deltax;

		} // while

		if (interchange)
			y = y + signaly;
		else
			x = x + signalx;
			erro = erro + 2 * deltay;

	} // for

}

// Algoritmo de Ponto Medio (Bresenham) para circunferencias
void Poligono::DesenhaCircunferencia (int xc, int yc, int r){

	int x, y, p;
	x = 0;
	y = r;
	DesenhaPontoCircunferencia(xc, yc, x, y);
	p = 1 - y;
	while (x < y) {
		if (p < 0) {
			x++;
		} else {
			x++;
			y--;
		}
		if (p < 0) {
			p += 2 * x + 1;
		} else {
			p += 2 * (x - y) + 1;
		}
		DesenhaPontoCircunferencia(xc, yc, x, y);
	}

}


// Plota os pontos nos 8 octantes simétricos da circunferência
void Poligono::DesenhaPontoCircunferencia(int xc, int yc, int x, int y){
  pontos.push_back(Ponto(xc+x, yc+y));
  pontos.push_back(Ponto(xc-x, yc+y));
  pontos.push_back(Ponto(xc-y, yc+x));
  pontos.push_back(Ponto(xc-y, yc-x));
  pontos.push_back(Ponto(xc-x, yc-y));
  pontos.push_back(Ponto(xc+x, yc-y));
  pontos.push_back(Ponto(xc+y, yc-x));
  pontos.push_back(Ponto(xc+y, yc+x));

}


void Poligono::desenha(TCanvas *canvas, Janela mundo, Janela vp, int TipoReta){
			Ponto p1,p2;

	if(tipo == 'C'){  // Circunferência: desenha pixels individuais na tela
			int xvp, yvp;
			for(int i = 0; i < pontos.size(); i++){
				xvp = pontos[i].xW2Vp(mundo, vp);
				yvp = pontos[i].yW2Vp(mundo, vp);
				canvas->Pixels[xvp][yvp] = clBlack;

			}
	} else {
		switch(TipoReta){
		case 0:   // Reta Padrão do Windows (MoveTo / LineTo nativo do Canvas)
			int xvp, yvp;
			for(int i = 0; i < pontos.size(); i++){
				xvp = pontos[i].xW2Vp(mundo, vp);
				yvp = pontos[i].yW2Vp(mundo, vp);
			if(i == 0)
				canvas->MoveTo(xvp, yvp);
			else
				canvas->LineTo(xvp, yvp);

			}
			break;

		case 1: // DDA
			for(int i = 0; i < pontos.size()-1; i++){
				p1 = pontos[i];
				p2 = pontos[i+1];

				desenharDDA(p1,p2,mundo,vp,canvas);

			}
			break;

		case 2: // BRESENHAM
			for(int i = 0; i < pontos.size()-1; i++){
				p1 = pontos[i];
				p2 = pontos[i+1];
				desenharBRESENHAM(p1, p2, mundo, vp, canvas);
			}
			break;

		}
	}

}

void Poligono::mostra(TListBox *listbox){
	listbox->Items->Add(IntToStr(id) + " - " + tipo + " - " +
	IntToStr((int)pontos.size()) + " pontos");

}

void Poligono::mostraPontos(TListBox *listbox){
  listbox->Items->Clear();
  for(int i = 0; i < pontos.size(); i++){
	 listbox->Items->Add(pontos[i].mostra());
  }

}

void Poligono::translacao(double dx, double dy){    // Transformação 2D: Translação (deslocamento nos eixos X e Y)
	for(int i = 0; i < pontos.size(); i++){
		pontos[i].translacao(dx, dy);
	}
}

void Poligono::escalonamento(double dx, double dy){  // Transformação 2D: Escalonamento (altera a escala em X e Y)
	for(int i = 0; i < pontos.size(); i++){
		pontos[i].escalonamento(dx, dy);
	}
}

void Poligono::rotacao(double graus){  // Transformação 2D: Rotação simples em torno da origem (0, 0)
	for(int i = 0; i < pontos.size(); i++){
		pontos[i].rotacao(graus);
	}
}

Ponto Poligono::pontoMedio(){  // Calcula o ponto médio (centroide) do polígono para rotação homogênea

	double somaX = 0, somaY = 0;
	for (int i = 0; i < pontos.size(); i++) {
		somaX += pontos[i].x;
		somaY += pontos[i].y;
	}

	double pontoMedioX = somaX / pontos.size();
	double pontoMedioY = somaY / pontos.size();
	return (Ponto(pontoMedioX, pontoMedioY));
}

// Transformação 2D: Rotação Homogênea em torno do centro do polígono (Matrizes 3x3)
void Poligono::rotacaoHomogenea(double graus){

	Ponto central = pontoMedio();

	double rad = graus * (M_PI/180);

	double matriz1[3][3] = {{1, 0, 0}, {0, 1, 0}, {-central.x, -central.y, 1}};
	double matriz2[3][3] = {{cos(rad), sin(rad), 0}, {-sin(rad), cos(rad), 0}, {0, 0, 1}};
	double matriz3[3][3] = {{1, 0, 0}, {0, 1, 0}, {central.x, central.y, 1}};


	double res1[3][3], res2[3][3];

	// matriz1 e matriz2
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			res1[i][j] = 0;
			for(int k = 0; k < 3; k++){
				res1[i][j] += matriz1[i][k] * matriz2[k][j];
			}
		}
	}

	// res1 e matriz3
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			res2[i][j] = 0;
			for(int k = 0; k < 3; k++){
				res2[i][j] += res1[i][k] * matriz3[k][j];
			}
		}
	}

	for (int i = 0; i < pontos.size(); i++) {
		double x = pontos[i].x;
		double y = pontos[i].y;

		pontos[i].x = x * res2[0][0] + y * res2[1][0] + res2[2][0];
		pontos[i].y = x * res2[0][1] + y * res2[1][1] + res2[2][1];
	}
}

void Poligono::reflexaoEixoX() { // Transformação 2D: Reflexão no eixo X
	for (int i = 0; i < pontos.size(); i++) {
		pontos[i].x = -pontos[i].x;
	}
}

void Poligono::reflexaoEixoY() {  // Transformação 2D: Reflexão no eixo Y
	for (int i = 0; i < pontos.size(); i++) {
		pontos[i].y = -pontos[i].y;
	}
}

void Poligono::reflexaoEixoXY() { // Transformação 2D: Reflexão simultânea em ambos os eixos (origem)
	for (int i = 0; i < pontos.size(); i++) {
		pontos[i].x = -pontos[i].x;
		pontos[i].y = -pontos[i].y;
	}
}

// Curva de Bézier: Algoritmo de de Casteljau (ponto inicial)
void Poligono::casteljau(Ponto p0, Ponto p1, Ponto p2) {
	pontos.push_back(p0);
	casteljauRecursivo(p0, p1, p2);
}

// Subdivisão recursiva de Casteljau
void Poligono::casteljauRecursivo(Ponto p0, Ponto p1, Ponto p2) {
	double distancia = sqrt((p2.x - p0.x) * (p2.x - p0.x) + (p2.y - p0.y) * (p2.y - p0.y));

	if (distancia <= 1) {
		pontos.push_back(p2);
	} else {
		Ponto A, B, C;

		A.x = (p0.x + p1.x) / 2;
		A.y = (p0.y + p1.y) / 2;
		C.x = (p1.x + p2.x) / 2;
		C.y = (p1.y + p2.y) / 2;
		B.x = (A.x + C.x) /  2;
		B.y = (A.y + C.y) / 2;

		casteljauRecursivo(p0, A, B);
		casteljauRecursivo(B, C, p2);
	}
}

// Curva de Hermite (cálculo de vetores tangentes e polinômios cúbicos)
void Poligono::hermite(Ponto p1, Ponto p2, Ponto p3, Ponto p4) {
	Ponto r1, r4;
	r1.x = p2.x - p1.x;
	r1.y = p2.y - p1.y;

	r4.x = p4.x - p3.x;
	r4.y = p4.y - p3.y;

	double ghx[] = {p1.x, p4.x, r1.x, r4.x};
	double ghy[] = {p1.y, p4.y, r1.y, r4.y};

	for (double t = 0; t <= 1; t += 0.01) {
		double xT = 0;
		double yT = 0;

		double t2 = t * t;
		double t3 = t2 * t;

		xT = ghx[0] * (2 * t3 - 3 * t2 + 1) + ghx[1] * (-2 * t3 + 3 * t2) +
			 ghx[2] * (t3 - 2 * t2 + t) + ghx[3] * (t3 - t2);
		yT = ghy[0] * (2 * t3 - 3 * t2 + 1) + ghy[1] * (-2 * t3 + 3 * t2) +
			 ghy[2] * (t3 - 2 * t2 + t) + ghy[3] * (t3 - t2);

		this->pontos.push_back(Ponto(xT, yT));
	}
}

// Curva de Bézier cúbica via polinômios de Bernstein
void Poligono::bezier(Ponto p1, Ponto p2, Ponto p3, Ponto p4) {
	for (double t = 0; t < 1; t += 0.01) {
		double x = 0;
		double y = 0;

		double t2 = t * t;
		double t3 = t2 * t;
		double mt = 1 - t;
		double mt2 = mt * mt;
		double mt3 = mt2 * mt;

		x = mt3 * p1.x + 3 * mt2 * t * p2.x + 3 * mt * t2 * p3.x + t3 * p4.x;
		y = mt3 * p1.y + 3 * mt2 * t * p2.y + 3 * mt * t2 * p3.y + t3 * p4.y;

		this->pontos.push_back({x, y});
	}
}

// Curva B-Spline Cúbica Uniforme (multiplicação pela matriz base M)
void Poligono::bSpline(Ponto p1, Ponto p2, Ponto p3, Ponto p4) {
	double M[4][4] = {{-1/6.0, 3/6.0, -3/6.0, 1/6.0},
					  {3/6.0, -6/6.0, 3/6.0, 0/6.0},
					  {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
					  {1/6.0, 4/6.0, 1/6.0, 0/6.0}};

	double Gx[] = {p1.x, p2.x, p3.x, p4.x};
	double Gy[] = {p1.y, p2.y, p3.y, p4.y};

	double Cx[4] = {0};
	double Cy[4] = {0};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			Cx[i] += M[i][j] * Gx[j];
			Cy[i] += M[i][j] * Gy[j];
		}
	}

	for (double t = 0; t <= 1; t += 0.01) {
		double xT = 0;
		double yT = 0;
		double t3 = t*t*t;
		double t2 = t*t;
		xT = Cx[0]*t3 + Cx[1]*t2 + Cx[2]*t + Cx[3];
		yT = Cy[0]*t3 + Cy[1]*t2 + Cy[2]*t + Cy[3];

		this->pontos.push_back(Ponto(xT, yT));
	}
}

// Curva B-Spline calculada pelo método de Diferenças Progressivas (Forward Differences)
void Poligono::fwdDifferences(Ponto p1, Ponto p2, Ponto p3, Ponto p4) {
	double M[4][4] = {{-1/6.0, 3/6.0, -3/6.0, 1/6.0},
					  {3/6.0, -6/6.0, 3/6.0, 0/6.0},
					  {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
					  {1/6.0, 4/6.0, 1/6.0, 0/6.0}};

	double Gx[] = {p1.x, p2.x, p3.x, p4.x};
	double Gy[] = {p1.y, p2.y, p3.y, p4.y};

	double Cx[4] = {0};
	double Cy[4] = {0};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			Cx[i] += M[i][j] * Gx[j];
			Cy[i] += M[i][j] * Gy[j];
		}
	}

	double t = 0.01;
	double x       = Cx[3];
	double deltaX  = Cx[0]*t*t*t + Cx[1]*t*t + Cx[2]*t;
	double delta2X = 6*Cx[0]*t*t*t + 2*Cx[1]*t*t;
	double delta3X = 6*Cx[0]*t*t*t;

	double y       = Cy[3];
	double deltaY  = Cy[0]*t*t*t + Cy[1]*t*t + Cy[2]*t;
	double delta2Y = 6*Cy[0]*t*t*t + 2*Cy[1]*t*t;
	double delta3Y = 6*Cy[0]*t*t*t;

	int i = 0;
	pontos.push_back(Ponto(x, y));
	while(i<101){
	   i++;
	   x       += deltaX;
	   deltaX  += delta2X;
	   delta2X += delta3X;
	   y       += deltaY;
	   deltaY  += delta2Y;
	   delta2Y += delta3Y;
	   pontos.push_back(Ponto(x, y));
	}
}

Ponto Poligono::novoPonto(Ponto aux, double x, double y){
	Ponto ponto = aux;
	ponto.x = x;
	ponto.y = y;
	return ponto;
}

// Algoritmo de Cohen-Sutherland para recorte de retas contra a janela de clipping
Poligono Poligono::clipping(Janela clip){
	Poligono poligono;
	Ponto auxPon;
	int clipPonto1, clipPonto2;
	double inclinacao, tang, yEsq, yDir, xTopo, xFundo;
	for (int i = 1; i < pontos.size(); i++) {
		Ponto aux;
		clipPonto1 = pontos[i - 1].cohen(clip);
		clipPonto2 = pontos[i].cohen(clip);
		tang = (pontos[i].y - pontos[i - 1].y) /
			   ((pontos[i].x - pontos[i - 1].x) == 0 ? (double)0.01 : (pontos[i].x - pontos[i - 1].x));
		if (tang == 0) {
			inclinacao = (double)0.001;
		} else {
			inclinacao = tang;
		}
		if (((clipPonto1 == 0) || (clipPonto2 == 0)) &&
			clipPonto1 != clipPonto2) {
			int ind = clipPonto1 < clipPonto2 ? i : i - 1;
			yEsq = inclinacao * (clip.xMin - pontos[ind].x) + pontos[ind].y;
			yDir = inclinacao * (clip.xMax - pontos[ind].x) + pontos[ind].y;
			xTopo = pontos[ind].x +
					1 / (inclinacao == 0 ? (double)0.01 : inclinacao) *
						(clip.yMax - pontos[ind].y);
			xFundo = pontos[ind].x +
					1 / (inclinacao == 0 ? (double)0.01 : inclinacao) * (clip.yMin - pontos[ind].y);
			switch (clipPonto1 < clipPonto2 ? clipPonto2 : clipPonto1) {
				case 1:
					aux = novoPonto(aux, clip.xMin, yEsq);
					break;
				case 2:
					aux = novoPonto(aux, clip.xMax, yDir);
					break;
				case 4:
					aux = novoPonto(aux, xFundo, clip.yMin);
					break;
				case 5:
					aux = yEsq > clip.yMin ? novoPonto(aux, clip.xMin, yEsq)
										   : novoPonto(aux, xFundo, clip.yMin);
					break;
				case 6:
					aux = xFundo < clip.xMax ? novoPonto(aux, xFundo, clip.yMin)
											 : novoPonto(aux, clip.xMax, yDir);
					break;
				case 8:
					aux = novoPonto(aux, xTopo, clip.yMax);
					break;
				case 9:
					aux = yEsq < clip.yMax ? novoPonto(aux, clip.xMin, yEsq)
										   : novoPonto(aux, xTopo, clip.yMax);
					break;
				case 10:
					aux = yDir < clip.yMax ? novoPonto(aux, clip.xMax, yDir)
										   : novoPonto(aux, xTopo, clip.yMax);
					break;
			}
			if (clipPonto1 < clipPonto2) {
				poligono.pontos.push_back(
					Ponto(pontos[i - 1].x - 1, pontos[i - 1].y - 1));
				poligono.pontos.push_back(Ponto(aux.x - 1, aux.y - 1));
			} else {
				poligono.pontos.push_back(Ponto(aux.x - 1, aux.y - 1));
				poligono.pontos.push_back(
					Ponto(pontos[i].x - 1, pontos[i].y - 1));
			}
		} else if ((clipPonto1 == clipPonto2) && clipPonto2 == 0) {
			poligono.pontos.push_back(
				Ponto(pontos[i - 1].x - 1, pontos[i - 1].y - 1));
			poligono.pontos.push_back(Ponto(pontos[i].x - 1, pontos[i].y - 1));
		}
		// Parcialmente
		else if ((clipPonto1 != clipPonto2) && ((clipPonto1 & clipPonto2) == 0))
		{
			Ponto aux;
			for (int j = i - 1; j <= i; j++) {
				// Calculo de Intersecoes
				yEsq = inclinacao * (clip.xMin - pontos[j].x) + pontos[j].y;
				yDir = inclinacao * (clip.xMax - pontos[j].x) + pontos[j].y;
				xTopo =
					pontos[j].x + 1 / inclinacao * (clip.yMax - pontos[j].y);
				xFundo =
					pontos[j].x + 1 / inclinacao * (clip.yMin - pontos[j].y);
				switch (j == i ? clipPonto2 : clipPonto1) {
					case 1:    // Intersecao com a borda esquerda (xMin)
						if (yEsq >= clip.yMin && yEsq <= clip.yMax)
							aux = novoPonto(aux, clip.xMin, yEsq);
						break;
					case 2:  // Intersecao com a borda direita (xMax)
						if (yDir >= clip.yMin && yDir <= clip.yMax)
							aux = novoPonto(aux, clip.xMax, yDir);
						break;
					case 4:  // Intersecao com a borda inferior (yMin)
						if (xFundo >= clip.xMin && xFundo <= clip.xMax)
							aux = novoPonto(aux, xFundo, clip.yMin);
						break;
					case 5:   // Canto inferior esquerdo (xMin, yMin)
						if (xFundo >= clip.xMin && xFundo <= clip.xMax)
							aux = novoPonto(aux, xFundo, clip.yMin);
						else if (yEsq >= clip.yMin && yEsq <= clip.yMax)
							aux = novoPonto(aux, clip.xMin, yEsq);
						break;
					case 6:  // Canto inferior direito (xMax, yMin)
						if (xFundo >= clip.xMin && xFundo <= clip.xMax)
							aux = novoPonto(aux, xFundo, clip.yMin);
						else if (yDir >= clip.yMin && yDir <= clip.yMax)
							aux = novoPonto(aux, clip.xMax, yDir);
						break;
					case 8:  // Intersecao com a borda superior (yMax)
						if (xTopo >= clip.xMin && xTopo <= clip.xMax)
							aux = novoPonto(aux, xTopo, clip.yMax);
						break;
					case 9:  // Canto superior esquerdo (xMin, yMax)
						if (xTopo >= clip.xMin && xTopo <= clip.xMax)
							aux = novoPonto(aux, xTopo, clip.yMax);
						else if (yEsq >= clip.yMin && yEsq <= clip.yMax)
							aux = novoPonto(aux, clip.xMin, yEsq);
						break;
					case 10:  // Canto superior direito (xMax, yMax)
						if (xTopo >= clip.xMin && xTopo <= clip.xMax)
							aux = novoPonto(aux, xTopo, clip.yMax);
						else if (yDir >= clip.yMin && yDir <= clip.yMax)
							aux = novoPonto(aux, clip.xMax, yDir);
						break;
				}
				if (aux.x == aux.y && aux.x == 0)
					break;
                else
                    poligono.pontos.push_back(aux);
            }
        }
    }
    return poligono;
}

