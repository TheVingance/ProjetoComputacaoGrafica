//---------------------------------------------------------------------------
#ifndef uPonto3DH
#define uPonto3DH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include "Unit1.h"

// Classe que representa um ponto no espaço tridimensional (x, y, z)
// e executa transformações geométricas 3D (translação, escalonamento e rotações).
class Ponto3D {
public:
    double x;
    double y;
    double z;

    // Construtores
    Ponto3D();
    Ponto3D(double nx, double ny, double nz);

    // As 3 transformações geométricas básicas em 3D:
    // 1. Translação 3D
    void translacao(double dx, double dy, double dz);

    // 2. Escalonamento 3D (em relação à origem)
    void escalonamento(double sx, double sy, double sz);

    // 3. Rotações em torno dos eixos cartesianos principais (ângulos em graus)
    void rotacaoX(double graus);
    void rotacaoY(double graus);
    void rotacaoZ(double graus);

    // Rotação em torno de um eixo arbitrário no espaço definido por dois pontos P1 e P2
    // Utiliza a fórmula de Rodrigues para rotação no espaço 3D
    void rotacaoEixoArbitrario(Ponto3D p1, Ponto3D p2, double graus);

    // Métodos de projeção 3D -> 2D (retornam uma instância de Ponto 2D)
    Ponto projetaOrtografica() const;
    Ponto projetaPerspectiva(double d = 500.0) const;
    Ponto projetaCavaleira(double angGraus = 45.0, double fator = 0.5) const;

    // Representação em texto para exibição
    String mostra() const;
};

#endif
