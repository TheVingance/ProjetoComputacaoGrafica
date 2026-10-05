//---------------------------------------------------------------------------
#pragma hdrstop
#include "uPonto3D.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Construtor padrão: inicializa ponto 3D na origem (0, 0, 0)
Ponto3D::Ponto3D() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

// Construtor parametrizado: inicializa ponto com coordenadas (nx, ny, nz)
Ponto3D::Ponto3D(double nx, double ny, double nz) {
    x = nx;
    y = ny;
    z = nz;
}

// 1. Translação 3D: desloca o ponto somando incrementos aos 3 eixos
// [x', y', z', 1] = [x, y, z, 1] * T(dx, dy, dz)
void Ponto3D::translacao(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}

// 2. Escalonamento 3D: multiplica as coordenadas pelos fatores sx, sy, sz
// [x', y', z', 1] = [x, y, z, 1] * S(sx, sy, sz)
void Ponto3D::escalonamento(double sx, double sy, double sz) {
    x *= sx;
    y *= sy;
    z *= sz;
}

// 3. Rotação 3D em torno do eixo X (ângulo em graus)
// Matriz de Rotação Rx(theta):
// x' = x
// y' = y*cos(theta) - z*sin(theta)
// z' = y*sin(theta) + z*cos(theta)
void Ponto3D::rotacaoX(double graus) {
    double rad = graus * (M_PI / 180.0);
    double c = cos(rad);
    double s = sin(rad);

    double novoY = y * c - z * s;
    double novoZ = y * s + z * c;

    y = novoY;
    z = novoZ;
}

// 3. Rotação 3D em torno do eixo Y (ângulo em graus)
// Matriz de Rotação Ry(theta):
// x' =  x*cos(theta) + z*sin(theta)
// y' =  y
// z' = -x*sin(theta) + z*cos(theta)
void Ponto3D::rotacaoY(double graus) {
    double rad = graus * (M_PI / 180.0);
    double c = cos(rad);
    double s = sin(rad);

    double novoX =  x * c + z * s;
    double novoZ = -x * s + z * c;

    x = novoX;
    z = novoZ;
}

// 3. Rotação 3D em torno do eixo Z (ângulo em graus)
// Matriz de Rotação Rz(theta):
// x' = x*cos(theta) - y*sin(theta)
// y' = x*sin(theta) + y*cos(theta)
// z' = z
void Ponto3D::rotacaoZ(double graus) {
    double rad = graus * (M_PI / 180.0);
    double c = cos(rad);
    double s = sin(rad);

    double novoX = x * c - y * s;
    double novoY = x * s + y * c;

    x = novoX;
    y = novoY;
}

// Rotação em torno de um eixo arbitrário A que passa pelo ponto P1 (Slides 20 a 29 da Aula 6):
// 1. Translação T do sistema objeto/eixo de uma distância vetorial -D de forma que algum ponto P sobre o eixo fique sobre a origem.
// 2. Rotação Rx em torno do eixo x por thetaX de forma a trazer o eixo A sobre o plano xy.
// 3. Rotação Rz em torno do eixo z por thetaZ de forma a alinhar o eixo A com o eixo y.
// 4. Rotação Ry em torno do eixo y pelo ângulo desejado theta_original.
// 5. Rotação Rz^-1 em torno do eixo z por -thetaZ de forma a desfazer (3).
// 6. Rotação Rx^-1 em torno do eixo x por -thetaX de forma a desfazer (2).
// 7. Translação T^-1 de uma distância D para desfazer (1).
void Ponto3D::rotacaoEixoArbitrario(Ponto3D p1, Ponto3D p2, double graus) {
    // Vetor diretor do eixo A
    double ax = p2.x - p1.x;
    double ay = p2.y - p1.y;
    double az = p2.z - p1.z;

    double comprimento = sqrt(ax * ax + ay * ay + az * az);
    if (comprimento < 1e-9) {
        return; // Eixo degenerado (p1 == p2)
    }

    // 1. Translação T(-D) para levar P1 à origem (Slide 22)
    translacao(-p1.x, -p1.y, -p1.z);

    // 2. Rotação Rx em torno do eixo X para trazer o eixo A sobre o plano XY (Slide 23)
    double dYZ = sqrt(ay * ay + az * az);
    double thetaX_rad = 0.0;
    if (dYZ > 1e-9) {
        thetaX_rad = -atan2(az, ay);
        double thetaX_graus = thetaX_rad * (180.0 / M_PI);
        rotacaoX(thetaX_graus);
    }

    // 3. Rotação Rz em torno do eixo Z para alinhar o eixo A com o eixo Y (Slide 24)
    double thetaZ_rad = -atan2(ax, dYZ);
    double thetaZ_graus = thetaZ_rad * (180.0 / M_PI);
    rotacaoZ(thetaZ_graus);

    // 4. Rotação Ry em torno do eixo Y pelo ângulo desejado theta_original (Slides 25 e 26)
    rotacaoY(graus);

    // 5. Rotação Rz^-1 em torno do eixo Z por -thetaZ para desfazer (3) (Slide 27)
    rotacaoZ(-thetaZ_graus);

    // 6. Rotação Rx^-1 em torno do eixo X por -thetaX para desfazer (2) (Slide 28)
    if (dYZ > 1e-9) {
        double thetaX_graus = thetaX_rad * (180.0 / M_PI);
        rotacaoX(-thetaX_graus);
    }

    // 7. Translação T^-1(+D) para desfazer a translação (1) (Slide 29)
    translacao(p1.x, p1.y, p1.z);
}

// Projeção Ortográfica simples no plano XY: descarta a coordenada Z
Ponto Ponto3D::projetaOrtografica() const {
    return Ponto(x, y);
}

// Projeção em Perspectiva com centro de projeção em (0, 0, d)
// X2D = x * d / (d - z), Y2D = y * d / (d - z)
Ponto Ponto3D::projetaPerspectiva(double d) const {
    double denom = d - z;
    if (fabs(denom) < 1e-5) {
        denom = (denom >= 0) ? 1e-5 : -1e-5;
    }
    double fator = d / denom;
    return Ponto(x * fator, y * fator);
}

// Projeção Cavaleira / Oblíqua: projeta considerando profundidade Z em ângulo inclinado
Ponto Ponto3D::projetaCavaleira(double angGraus, double fator) const {
    double rad = angGraus * (M_PI / 180.0);
    double x2d = x + z * cos(rad) * fator;
    double y2d = y + z * sin(rad) * fator;
    return Ponto(x2d, y2d);
}

// Retorna representação textual das coordenadas 3D formatadas
String Ponto3D::mostra() const {
    return "( " + FloatToStrF(x, ffFixed, 7, 2) + "; " +
                  FloatToStrF(y, ffFixed, 7, 2) + "; " +
                  FloatToStrF(z, ffFixed, 7, 2) + " )";
}
