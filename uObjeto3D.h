//---------------------------------------------------------------------------
#ifndef uObjeto3DH
#define uObjeto3DH
//---------------------------------------------------------------------------
#include <vector>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "uPonto3D.h"
#include "uPoligono.h"
#include "UJanela.h"

// Estrutura que representa um segmento de reta 3D formado por um par de Pontos3D
struct Segmento3D {
    Ponto3D p1;
    Ponto3D p2;

    Segmento3D();
    Segmento3D(Ponto3D np1, Ponto3D np2);
    void translacao(double dx, double dy, double dz);
    void escalonamento(double sx, double sy, double sz);
    void rotacaoX(double graus);
    void rotacaoY(double graus);
    void rotacaoZ(double graus);
    void rotacaoEixoArbitrario(Ponto3D ax1, Ponto3D ax2, double graus);
};

// Enumeração para os tipos de projeção 3D -> 2D
enum TipoProjecao3D {
    PROJECAO_ORTOGRAFICA = 0,   // Projeção paralela ortográfica (descarta Z)
    PROJECAO_PERSPECTIVA = 1,   // Projeção com ponto de fuga em perspectiva
    PROJECAO_CAVALEIRA   = 2    // Projeção oblíqua cavaleira
};

// Classe Objeto3D para representar um Modelo de Arame (Wireframe Model) 3D
class Objeto3D {
public:
    int id;
    String nome;
    TColor cor;
    std::vector<Segmento3D> segmentos;

    // Construtores
    Objeto3D();
    Objeto3D(int novoId, String novoNome);

    // As 3 operações geométricas básicas em 3D:
    // 1. Translação 3D (deslocamento nos eixos X, Y e Z)
    void translacao(double dx, double dy, double dz);

    // 2. Escalonamento 3D (em relação à origem ou em relação ao centro do objeto)
    void escalonamento(double sx, double sy, double sz);
    void escalonamentoNoCentro(double sx, double sy, double sz);

    // 3. Rotação em torno dos eixos coordenados X, Y, Z
    void rotacaoX(double graus);
    void rotacaoY(double graus);
    void rotacaoZ(double graus);
    void rotacaoNoCentro(double angX, double angY, double angZ);

    // Rotação em torno de um eixo arbitrário no espaço (passando por p1 e p2)
    void rotacaoEixoArbitrario(Ponto3D p1, Ponto3D p2, double graus);

    // Leitura e gravação de arquivos texto com as coordenadas do modelo
    // Suporta formato de segmentos ("x1 y1 z1 x2 y2 z2"), formato de vértices + arestas e .obj
    bool carregarDeArquivo(String caminhoArquivo);
    bool salvarParaArquivo(String caminhoArquivo);

    // Métodos utilitários de geração de primitivas 3D padrão
    void criarCubo(double tamanho = 80.0, double centroX = 0.0, double centroY = 0.0, double centroZ = 0.0);
    void criarPiramide(double base = 80.0, double altura = 100.0, double centroX = 0.0, double centroY = 0.0, double centroZ = 0.0);

    // Centroide / Baricentro do modelo 3D
    Ponto3D centro() const;

    // Projeção e desenho na Viewport 2D existente
    void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta, int tipoProjecao = PROJECAO_PERSPECTIVA, double dPerspectiva = 400.0);

    // Converte os segmentos 3D projetados em polígonos 2D compatíveis com o DisplayFile
    std::vector<Poligono> gerarPoligonos2D(int idInicial, int tipoProjecao = PROJECAO_PERSPECTIVA, double dPerspectiva = 400.0);

    // Exibição em TListBox da interface
    void mostra(TListBox *listbox);
    void mostraSegmentos(TListBox *listbox);
};

#endif
