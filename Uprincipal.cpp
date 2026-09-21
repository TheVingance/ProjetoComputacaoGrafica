//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Uprincipal.h"
#include "uPoligono.h"
#include "uDisplay.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

Poligono pol;
TForm1 *Form1;
Ponto aux;
DisplayFile display;
Janela mundo(-250, -250, 250, 250); 		// Construtor: Limites da Janela Mundo (universo virtual)
Janela vp(0, 0, 500, 500);           		// Construtor: Limites da Viewport (em pixels na tela)
Janela clipping(-100, -100, 100, 100);      // Construtor: Janela de Clipping (região de corte)

int contId = 0;
bool inicia = false;

double xVp2Mundo(int x, Janela mundo, Janela vp){
	return ((x - vp.xMin) / (vp.xMax - vp.xMin)) * (mundo.xMax - mundo.xMin) + mundo.xMin;
}

double yVp2Mundo(int y, Janela Mundo, Janela vp){
	return (1-((y - vp.yMin) / (vp.yMax - vp.yMin))) * (mundo.yMax - mundo.yMin) + mundo.yMin;
}

//---------------------------------------------------------------------------
// Construtor do Formulario: inicializa os eixos X e Y e o retangulo de clipping

__fastcall TForm1::TForm1(TComponent* Owner) :TForm(Owner){

  componentes->ActivePage = TabSheet2; // Abre na aba Transformacoes

  // Eixo vertical (Y)
  pol.id = contId++;
  pol.tipo = 'E';
  pol.pontos.push_back(Ponto(0, mundo.yMax));
  pol.pontos.push_back(Ponto(0, mundo.yMin));
  display.poligonos.push_back(pol);
  pol.pontos.clear();

  // Eixo horizontal (X)
  pol.id = contId++;
  pol.tipo = 'E';
  pol.pontos.push_back(Ponto(mundo.xMin, 0));
  pol.pontos.push_back(Ponto(mundo.xMax, 0));
  display.poligonos.push_back(pol);
  pol.pontos.clear();

  // Retângulo de clipping
  pol.id = contId++;
  pol.tipo = 'E';
  pol.pontos.push_back(Ponto(clipping.xMin, clipping.yMin));
  pol.pontos.push_back(Ponto(clipping.xMax, clipping.yMin));
  pol.pontos.push_back(Ponto(clipping.xMax, clipping.yMax));
  pol.pontos.push_back(Ponto(clipping.xMin, clipping.yMax));
  pol.pontos.push_back(Ponto(clipping.xMin, clipping.yMin));
  display.poligonos.push_back(pol);
  pol.pontos.clear();

  display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
  display.mostra(Form1->lbPoligonos);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	lbVp->Caption = "( " + IntToStr(X) + ", " + IntToStr(Y) + ")";

	double x, y;
	x = xVp2Mundo(X, mundo, vp);
	y = yVp2Mundo(Y, mundo, vp);
	lbMundo->Caption = " ( " + FloatToStr(x) + ", " + FloatToStr(y) + ")";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::lbPoligonosClick(TObject *Sender)
{
  display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}

//---------------------------------------------------------------------------
// Botao Limpar: limpa poligonos mantendo eixos coordenados e clipping
void __fastcall TForm1::btLimparClick(TObject *Sender)
{
	inicia = false;
	pol.pontos.clear();

	// Mantem os 3 objetos iniciais (Eixo Y, Eixo X e Janela de Clipping)
	// e remove todos os poligonos adicionados pelo usuario
	if (display.poligonos.size() > 3) {
		display.poligonos.erase(display.poligonos.begin() + 3, display.poligonos.end());
	}

	lbPontos->Items->Clear();

	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(Form1->lbPoligonos);
}

//---------------------------------------------------------------------------
// Botao Iniciar: habilita o clique do mouse para desenhar novos poligonos
void __fastcall TForm1::btIniciarClick(TObject *Sender)
{
	inicia = true;
}

//---------------------------------------------------------------------------
// Clique no Canvas: Botao Esquerdo insere vertices; Botao Direito fecha o poligono
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y)
{
	double xW, yW;
	if(inicia == true){
		if(Button == mbLeft) {
			xW = xVp2Mundo(X, mundo, vp);
			yW = yVp2Mundo(Y, mundo, vp);
			pol.pontos.push_back(Ponto(xW, yW));
			pol.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
		} else {
			if (Button == mbRight) {
				pol.id = contId++;
				pol.tipo = 'N';
				display.poligonos.push_back(pol);
				pol.pontos.clear();
				inicia = false;
				display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
				display.mostra(Form1->lbPoligonos);
			}
		}
	}
}

//---------------------------------------------------------------------------
void TForm1::atualizaMundo(Janela mundo){
  edYMin->Text = FloatToStr(mundo.yMin);
  edYmax->Text = FloatToStr(mundo.yMax);
  edXMin->Text = FloatToStr(mundo.xMin);
  edXMax->Text = FloatToStr(mundo.xMax);

  display.poligonos[0].pontos[0].y = mundo.yMax;
  display.poligonos[0].pontos[1].y = mundo.yMin;
  display.poligonos[1].pontos[0].x = mundo.xMin;
  display.poligonos[1].pontos[1].x = mundo.xMax;

  display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

  double xW, yW;
  int X = 0, Y = 0;

  lbVp->Caption = "( " + IntToStr(X) + ", " + IntToStr(Y) + ")";
  xW = xVp2Mundo(X, mundo, vp);
  yW = yVp2Mundo(Y, mundo, vp);
  lbMundo->Caption = "( " + FloatToStr(xW) + ", " + FloatToStr(yW) + ")";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btAtualizarMundoClick(TObject *Sender){
	mundo.xMin = StrToFloat(edXMin->Text);
	mundo.xMax = StrToFloat(edXMax->Text);
	mundo.yMin = StrToFloat(edYMin->Text);
	mundo.yMax = StrToFloat(edYmax->Text);

	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btCimaClick(TObject *Sender){
	mundo.yMin -= 10;
	mundo.yMax -= 10;
	atualizaMundo(mundo);
}

void __fastcall TForm1::btBaixoClick(TObject *Sender){
	mundo.yMin += 10;
	mundo.yMax += 10;
	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btEsquerdaClick(TObject *Sender){
	mundo.xMin += 10;
	mundo.xMax += 10;
	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btDireitaClick(TObject *Sender){
	mundo.xMin -= 10;
	mundo.xMax -= 10;
	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btZoomOutClick(TObject *Sender){
	mundo.xMin -= 10;
	mundo.xMax += 10;
	mundo.yMin -= 10;
	mundo.yMax += 10;
	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btZoomInClick(TObject *Sender){
	mundo.xMin += 10;
	mundo.xMax -= 10;
	mundo.yMin += 10;
	mundo.yMax -= 10;
	atualizaMundo(mundo);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btTranslornarClick(TObject *Sender){
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	if (edTranslacaoX->Text.Trim().IsEmpty() || edTranslacaoY->Text.Trim().IsEmpty()) {
		ShowMessage("Preencha os campos 'translacaoX' e 'translacaoY' com valores numericos!");
		return;
	}

	double dx = StrToFloatDef(edTranslacaoX->Text, 0);
	double dy = StrToFloatDef(edTranslacaoY->Text, 0);

	display.poligonos[lbPoligonos->ItemIndex].translacao(dx, dy);
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}

//---------------------------------------------------------------------------
// Botao Circunferencia: solicita o raio via caixa de dialogo e gera os pontos
void __fastcall TForm1::CirculoClick(TObject *Sender)
{
	UnicodeString valor = "100"; // valor padrao sugerido

	// Abre o popup solicitando o raio. Se o usuario clicar em "Cancelar", nada e feito.
	if (!InputQuery("Circunferencia", "Informe o raio da circunferencia:", valor)) {
		return;
	}

	int raio = valor.ToIntDef(0);
	if (raio <= 0) {
		ShowMessage("Por favor, insira um raio valido maior que zero.");
		return;
	}

	// Gera a circunferencia com centro (0, 0) e o raio informado
	pol.DesenhaCircunferencia(0, 0, raio);
	pol.id = contId++;
	pol.tipo = 'C';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(Form1->lbPoligonos);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btEscalonarClick(TObject *Sender){
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	if (edEscalonamentoX->Text.Trim().IsEmpty() || edEscalonamentoY->Text.Trim().IsEmpty()) {
		ShowMessage("Preencha os campos 'escalonamentoX' e 'escalonamentoY' com valores numericos (ex: 2 para dobrar, 0.5 para reduzir)!");
		return;
	}

	double dx = StrToFloatDef(edEscalonamentoX->Text, 1);
	double dy = StrToFloatDef(edEscalonamentoY->Text, 1);

	display.poligonos[lbPoligonos->ItemIndex].escalonamento(dx, dy);
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btRotacionarClick(TObject *Sender){
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	if (edRotacaoX->Text.Trim().IsEmpty()) {
		ShowMessage("Digite o angulo em graus no campo 'rotacaoX'!");
		return;
	}

	double graus = StrToFloatDef(edRotacaoX->Text, 0);

	display.poligonos[lbPoligonos->ItemIndex].rotacao(graus);
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btHomoRotacaoClick(TObject *Sender){
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	if (edRotacaoX->Text.Trim().IsEmpty()) {
		ShowMessage("Digite o angulo em graus no campo 'rotacaoX' acima do botao!");
		return;
	}

	double graus = StrToFloatDef(edRotacaoX->Text, 0);

	display.poligonos[lbPoligonos->ItemIndex].rotacaoHomogenea(graus);
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btReflexaoEixoXClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	display.poligonos[lbPoligonos->ItemIndex].reflexaoEixoX();
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::YClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	display.poligonos[lbPoligonos->ItemIndex].reflexaoEixoY();
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btEixoXYClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	display.poligonos[lbPoligonos->ItemIndex].reflexaoEixoXY();
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btCurvaCasteljauClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}

	Poligono polaux = display.poligonos[lbPoligonos->ItemIndex];
	if (polaux.pontos.size() < 3) {
		ShowMessage("O poligono selecionado precisa ter pelo menos 3 pontos para criar a curva de Casteljau.");
		return;
	}

	Ponto p0 = polaux.pontos[0];
	Ponto p1 = polaux.pontos[1];
	Ponto p2 = polaux.pontos[2];

	pol.casteljau(p0, p1, p2);
	pol.id = contId++;
	pol.tipo = 'c';
	display.poligonos.push_back(pol);
	pol.pontos.clear();
	display.desenha(Form1->Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(Form1->lbPoligonos);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btHermiteClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}

	Poligono poligonoSelecionado = display.poligonos[lbPoligonos->ItemIndex];
	if (poligonoSelecionado.pontos.size() < 4) {
		ShowMessage("O poligono selecionado precisa ter pelo menos 4 pontos para criar a curva de Hermite.");
		return;
	}

	Ponto p1 = poligonoSelecionado.pontos[0];
	Ponto p2 = poligonoSelecionado.pontos[1];
	Ponto p3 = poligonoSelecionado.pontos[2];
	Ponto p4 = poligonoSelecionado.pontos[3];

	pol.hermite(p1, p2, p3, p4);

	pol.id = contId++;
	pol.tipo = 'H';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btBezierClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}

	Poligono poligonoSelecionado = display.poligonos[lbPoligonos->ItemIndex];
	if (poligonoSelecionado.pontos.size() < 4) {
		ShowMessage("O poligono selecionado precisa ter pelo menos 4 pontos para criar a curva de Bezier.");
		return;
	}

	Ponto p1 = poligonoSelecionado.pontos[0];
	Ponto p2 = poligonoSelecionado.pontos[1];
	Ponto p3 = poligonoSelecionado.pontos[2];
	Ponto p4 = poligonoSelecionado.pontos[3];

	pol.bezier(p1, p2, p3, p4);

	pol.id = contId++;
	pol.tipo = 'B';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btBSsplineClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}

	Poligono poligonoSelecionado = display.poligonos[lbPoligonos->ItemIndex];
	if (poligonoSelecionado.pontos.size() < 4) {
		ShowMessage("O poligono selecionado precisa ter pelo menos 4 pontos para criar a curva B-Spline.");
		return;
	}

	Ponto p1 = poligonoSelecionado.pontos[0];
	Ponto p2 = poligonoSelecionado.pontos[1];
	Ponto p3 = poligonoSelecionado.pontos[2];
	Ponto p4 = poligonoSelecionado.pontos[3];

	pol.bSpline(p1, p2, p3, p4);

	pol.id = contId++;
	pol.tipo = 'B';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btSplineDifferenceClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}
	Poligono polaux = display.poligonos[lbPoligonos->ItemIndex];
	if (polaux.pontos.size() < 4) {
		ShowMessage("O poligono selecionado precisa ter pelo menos 4 pontos.");
		return;
	}

	pol.fwdDifferences(polaux.pontos[0], polaux.pontos[1], polaux.pontos[2], polaux.pontos[3]);
	pol.id = contId++;
	pol.tipo = 'F';
	display.poligonos.push_back(pol);
	pol.pontos.clear();
	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------
// Botao Clipping: executa o recorte de Cohen-Sutherland no poligono selecionado
void __fastcall TForm1::btClippingClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex < 0 || lbPoligonos->ItemIndex >= (int)display.poligonos.size()) {
		ShowMessage("Selecione um poligono na lista 'Poligonos' primeiro!");
		return;
	}

	pol = display.poligonos[lbPoligonos->ItemIndex].clipping(clipping);
	pol.id = contId++;
	pol.tipo = 'R';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------

