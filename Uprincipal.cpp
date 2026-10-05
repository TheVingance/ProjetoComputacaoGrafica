//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Uprincipal.h"
#include "uPoligono.h"
#include "uDisplay.h"
#include <sstream>

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

  // Valores padrão fixos na aba de Transformações
  edTranslacaoX->Text = "10";
  edTranslacaoY->Text = "10";
  edEscalonamentoX->Text = "1.25";
  edEscalonamentoY->Text = "1.25";
  edRotacaoX->Text = "30";

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

  display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
  display.mostra(lbPoligonos);
}

//---------------------------------------------------------------------------
// Evento MouseMove: atualiza na barra de status as coordenadas do mouse (viewport e mundo)
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	lbVp->Caption = "( " + IntToStr(X) + ", " + IntToStr(Y) + ")";

	double x, y;
	x = xVp2Mundo(X, mundo, vp);
	y = yVp2Mundo(Y, mundo, vp);
	lbMundo->Caption = " ( " + FloatToStr(x) + ", " + FloatToStr(y) + ")";
}

//---------------------------------------------------------------------------
// Clique na lista de poligonos: exibe os vertices ou segmentos do objeto selecionado em lbPontos
void __fastcall TForm1::lbPoligonosClick(TObject *Sender)
{
	if (!lbPontos) return;
	lbPontos->Items->Clear();

	int idx = lbPoligonos->ItemIndex;
	if (idx < 0) return;

	if (idx < (int)display.poligonos.size()) {
		display.poligonos[idx].mostraPontos(lbPontos);
	} else if (idx < (int)(display.poligonos.size() + display.objetos3D.size())) {
		int idx3D = idx - (int)display.poligonos.size();
		display.objetos3D[idx3D].mostraSegmentos(lbPontos);
	}
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

// Converte texto numérico aceitando tanto ponto (.) quanto vírgula (,) como separador decimal
static double converteNumero(String str, double defVal = 0.0) {
	String s = str.Trim();
	if (s.IsEmpty()) return defVal;
	s = StringReplace(s, ".", FormatSettings.DecimalSeparator, TReplaceFlags() << rfReplaceAll);
	s = StringReplace(s, ",", FormatSettings.DecimalSeparator, TReplaceFlags() << rfReplaceAll);
	return StrToFloatDef(s, defVal);
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

	double dx = converteNumero(edTranslacaoX->Text, 10.0);
	double dy = converteNumero(edTranslacaoY->Text, 10.0);

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

	double dx = converteNumero(edEscalonamentoX->Text, 1.25);
	double dy = converteNumero(edEscalonamentoY->Text, 1.25);

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

	double graus = converteNumero(edRotacaoX->Text, 30.0);

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

	double graus = converteNumero(edRotacaoX->Text, 30.0);

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
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------
// Botao Curva Casteljau: gera curva de Bezier por subdivisao recursiva (minimo 3 pontos)
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
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------
// Botao Hermite: interpola curva cubica de Hermite baseada em vetores tangentes (minimo 4 pontos)
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
// Botao Bezier: avalia curva cubica de Bezier via polinomios de Bernstein (minimo 4 pontos)
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
// Botao B-Spline: gera curva B-Spline uniforme cubica via multiplicacao matricial (minimo 4 pontos)
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
// Botao B-Spline Diferencas Progressivas: tracado rapido por diferencas finitas (minimo 4 pontos)
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
// Botao Clipping: executa o recorte de Cohen-Sutherland em todos os poligonos do mundo
// Mantem os poligonos originais e adiciona novos poligonos com tipo 'R'
void __fastcall TForm1::btClippingClick(TObject *Sender)
{
	// Verifica se ha poligonos no mundo alem dos eixos e retangulo de clipping
	if (display.poligonos.size() <= 3) {
		ShowMessage("Nenhum poligono no mundo para recortar!");
		return;
	}

	std::vector<Poligono> novosRecortados;
	size_t qtdAtual = display.poligonos.size();

	// Percorre todos os poligonos do usuario existentes no mundo
	for (size_t i = 3; i < qtdAtual; i++) {
		// Ignora eixos/janela de clipping e poligonos que ja sao recortados ('R')
		if (display.poligonos[i].tipo == 'E' || display.poligonos[i].tipo == 'R') {
			continue;
		}

		if (display.poligonos[i].tipo == 'C') {
			// Circunferencia: filtra pontos dentro dos limites de clipping
			Poligono circClip;
			for (size_t p = 0; p < display.poligonos[i].pontos.size(); p++) {
				double px = display.poligonos[i].pontos[p].x;
				double py = display.poligonos[i].pontos[p].y;
				if (px >= clipping.xMin && px <= clipping.xMax &&
					py >= clipping.yMin && py <= clipping.yMax) {
					circClip.pontos.push_back(display.poligonos[i].pontos[p]);
				}
			}
			if (!circClip.pontos.empty()) {
				circClip.id = contId++;
				circClip.tipo = 'R';
				novosRecortados.push_back(circClip);
			}
		} else {
			// Poligono de retas: aplica o algoritmo de Cohen-Sutherland
			Poligono polClip = display.poligonos[i].clipping(clipping);
			// So adiciona se tiver pontos (evita criar poligono com 0 pontos)
			if (!polClip.pontos.empty()) {
				polClip.id = contId++;
				polClip.tipo = 'R';
				novosRecortados.push_back(polClip);
			}
		}
	}

	if (novosRecortados.empty()) {
		ShowMessage("Nenhum poligono possui partes dentro da regiao de clipping!");
		return;
	}

	// Adiciona os novos poligonos recortados na lista do Display File
	for (size_t i = 0; i < novosRecortados.size(); i++) {
		display.poligonos.push_back(novosRecortados[i]);
	}

	pol.pontos.clear();
	display.mostra(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}

//---------------------------------------------------------------------------
// Atualiza todo o display (polígonos 2D e objetos 3D) e as listas da interface
void TForm1::atualizaCena() {
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}

// Retorna o ponteiro para o Objeto3D atualmente selecionado na lista ou o último adicionado
Objeto3D* TForm1::getObjeto3DSelecionado() {
	if (display.objetos3D.empty()) {
		return nullptr;
	}

	int idx = lbPoligonos->ItemIndex;
	int inicio3D = (int)display.poligonos.size();
	int total = inicio3D + (int)display.objetos3D.size();

	if (idx >= inicio3D && idx < total) {
		return &display.objetos3D[idx - inicio3D];
	}

	// Se nenhum 3D estiver selecionado, seleciona o último da lista
	lbPoligonos->ItemIndex = total - 1;
	return &display.objetos3D.back();
}

//---------------------------------------------------------------------------
// Botão Criar Cubo 3D Padrão
void __fastcall TForm1::btCriarCubo3DClick(TObject *Sender) {
	Objeto3D obj(contId++, "Cubo 3D");
	obj.criarCubo(80.0);
	obj.rotacaoX(20.0);
	obj.rotacaoY(30.0);
	display.objetos3D.push_back(obj);
	atualizaCena();
	lbPoligonos->ItemIndex = (int)(display.poligonos.size() + display.objetos3D.size() - 1);
	lbPoligonosClick(this);
}

// Botão Criar Pirâmide 3D Padrão
void __fastcall TForm1::btCriarPiramide3DClick(TObject *Sender) {
	Objeto3D obj(contId++, "Piramide 3D");
	obj.criarPiramide(80.0, 100.0);
	obj.rotacaoX(20.0);
	obj.rotacaoY(30.0);
	display.objetos3D.push_back(obj);
	atualizaCena();
	lbPoligonos->ItemIndex = (int)(display.poligonos.size() + display.objetos3D.size() - 1);
	lbPoligonosClick(this);
}

// Botão Limpar 3D
void __fastcall TForm1::btLimpar3DClick(TObject *Sender) {
	display.objetos3D.clear();
	if (lbPontos) lbPontos->Items->Clear();
	atualizaCena();
}

// Seleção do Tipo de Projeção 3D (Ortográfica, Perspectiva ou Cavaleira)
void __fastcall TForm1::rgProjecao3DClick(TObject *Sender) {
	display.tipoProjecao3D = rgProjecao3D->ItemIndex;
	atualizaCena();
}

// Rotações nos eixos coordenados principais (X, Y, Z)
void __fastcall TForm1::btRotXMaisClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(15.0, 0, 0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btRotXMenosClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(-15.0, 0, 0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btRotYMaisClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(0, 15.0, 0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btRotYMenosClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(0, -15.0, 0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btRotZMaisClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(0, 0, 15.0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btRotZMenosClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->rotacaoNoCentro(0, 0, -15.0);
	atualizaCena();
	lbPoligonosClick(this);
}

// Escalonamento 3D
void __fastcall TForm1::btEscalaMais3DClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->escalonamentoNoCentro(1.15, 1.15, 1.15);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btEscalaMenos3DClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->escalonamentoNoCentro(0.85, 0.85, 0.85);
	atualizaCena();
	lbPoligonosClick(this);
}

// Translação no eixo Z (profundidade)
void __fastcall TForm1::btTransZMaisClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->translacao(0, 0, 20.0);
	atualizaCena();
	lbPoligonosClick(this);
}

void __fastcall TForm1::btTransZMenosClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}
	obj->translacao(0, 0, -20.0);
	atualizaCena();
	lbPoligonosClick(this);
}

// Reset da posição do Objeto 3D (reposiciona baricentro na origem)
void __fastcall TForm1::btReset3DClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) return;
	Ponto3D c = obj->centro();
	obj->translacao(-c.x, -c.y, -c.z);
	atualizaCena();
	lbPoligonosClick(this);
}

// Rotação em torno de um Eixo Arbitrário definido por P1(x, y, z) e P2(x, y, z)
void __fastcall TForm1::btRotEixoArbitrarioClick(TObject *Sender) {
	Objeto3D *obj = getObjeto3DSelecionado();
	if (!obj) {
		ShowMessage("Nenhum Objeto 3D ativo na cena!");
		return;
	}

	String entrada = InputBox("Rotacao em Eixo Arbitrario",
		"Informe: x1 y1 z1  x2 y2 z2  angulo_graus",
		"0 0 0  1 1 1  30");

	if (entrada.Trim().IsEmpty()) {
		return;
	}

	std::stringstream ss(AnsiString(entrada).c_str());
	double x1, y1, z1, x2, y2, z2, angulo;
	if (ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> angulo) {
		Ponto3D p1(x1, y1, z1);
		Ponto3D p2(x2, y2, z2);
		obj->rotacaoEixoArbitrario(p1, p2, angulo);
		atualizaCena();
		lbPoligonosClick(this);
		ShowMessage("Rotacao de " + FloatToStr(angulo) + " graus aplicada em torno do eixo (" +
					FloatToStr(x1) + "," + FloatToStr(y1) + "," + FloatToStr(z1) + ") -> (" +
					FloatToStr(x2) + "," + FloatToStr(y2) + "," + FloatToStr(z2) + ")");
	} else {
		ShowMessage("Parametros invalidos! Digite 7 numeros separados por espaco:\nx1 y1 z1  x2 y2 z2  angulo");
	}
}


