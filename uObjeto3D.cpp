//---------------------------------------------------------------------------
#pragma hdrstop
#include "uObjeto3D.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>

//---------------------------------------------------------------------------
#pragma package(smart_init)

// =========================================================================
// Segmento3D
// =========================================================================

Segmento3D::Segmento3D() {
}

Segmento3D::Segmento3D(Ponto3D np1, Ponto3D np2) {
    p1 = np1;
    p2 = np2;
}

void Segmento3D::translacao(double dx, double dy, double dz) {
    p1.translacao(dx, dy, dz);
    p2.translacao(dx, dy, dz);
}

void Segmento3D::escalonamento(double sx, double sy, double sz) {
    p1.escalonamento(sx, sy, sz);
    p2.escalonamento(sx, sy, sz);
}

void Segmento3D::rotacaoX(double graus) {
    p1.rotacaoX(graus);
    p2.rotacaoX(graus);
}

void Segmento3D::rotacaoY(double graus) {
    p1.rotacaoY(graus);
    p2.rotacaoY(graus);
}

void Segmento3D::rotacaoZ(double graus) {
    p1.rotacaoZ(graus);
    p2.rotacaoZ(graus);
}

void Segmento3D::rotacaoEixoArbitrario(Ponto3D ax1, Ponto3D ax2, double graus) {
    p1.rotacaoEixoArbitrario(ax1, ax2, graus);
    p2.rotacaoEixoArbitrario(ax1, ax2, graus);
}

// =========================================================================
// Objeto3D (Modelo de Arame)
// =========================================================================

Objeto3D::Objeto3D() {
    id = 0;
    nome = "Objeto3D";
    cor = clBlue;
}

Objeto3D::Objeto3D(int novoId, String novoNome) {
    id = novoId;
    nome = novoNome;
    cor = clBlue;
}

// 1. Translação 3D de todas as arestas do objeto
void Objeto3D::translacao(double dx, double dy, double dz) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].translacao(dx, dy, dz);
    }
}

// 2. Escalonamento 3D em relação à origem
void Objeto3D::escalonamento(double sx, double sy, double sz) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].escalonamento(sx, sy, sz);
    }
}

// Escalonamento 3D em relação ao baricentro do objeto (mantém posição na tela)
void Objeto3D::escalonamentoNoCentro(double sx, double sy, double sz) {
    Ponto3D c = centro();
    translacao(-c.x, -c.y, -c.z);
    escalonamento(sx, sy, sz);
    translacao(c.x, c.y, c.z);
}

// 3. Rotação em torno do eixo X
void Objeto3D::rotacaoX(double graus) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].rotacaoX(graus);
    }
}

// 3. Rotação em torno do eixo Y
void Objeto3D::rotacaoY(double graus) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].rotacaoY(graus);
    }
}

// 3. Rotação em torno do eixo Z
void Objeto3D::rotacaoZ(double graus) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].rotacaoZ(graus);
    }
}

// Rotação em torno do centro do próprio objeto nos 3 eixos
void Objeto3D::rotacaoNoCentro(double angX, double angY, double angZ) {
    Ponto3D c = centro();
    translacao(-c.x, -c.y, -c.z);
    if (angX != 0.0) rotacaoX(angX);
    if (angY != 0.0) rotacaoY(angY);
    if (angZ != 0.0) rotacaoZ(angZ);
    translacao(c.x, c.y, c.z);
}

// Rotação em torno de um eixo arbitrário definido por dois pontos (p1 e p2)
void Objeto3D::rotacaoEixoArbitrario(Ponto3D p1, Ponto3D p2, double graus) {
    for (size_t i = 0; i < segmentos.size(); i++) {
        segmentos[i].rotacaoEixoArbitrario(p1, p2, graus);
    }
}

// Calcula o baricentro (centro médio) de todos os vértices do modelo de arame
Ponto3D Objeto3D::centro() const {
    if (segmentos.empty()) {
        return Ponto3D(0, 0, 0);
    }

    double somaX = 0, somaY = 0, somaZ = 0;
    int totalPontos = 0;

    for (size_t i = 0; i < segmentos.size(); i++) {
        somaX += segmentos[i].p1.x + segmentos[i].p2.x;
        somaY += segmentos[i].p1.y + segmentos[i].p2.y;
        somaZ += segmentos[i].p1.z + segmentos[i].p2.z;
        totalPontos += 2;
    }

    return Ponto3D(somaX / totalPontos, somaY / totalPontos, somaZ / totalPontos);
}

// Criação de um Cubo 3D de arame padrão com 8 vértices e 12 arestas
void Objeto3D::criarCubo(double tamanho, double centroX, double centroY, double centroZ) {
    segmentos.clear();
    double h = tamanho / 2.0;

    // 8 Vértices do cubo
    Ponto3D v[8] = {
        Ponto3D(centroX - h, centroY - h, centroZ - h), // 0
        Ponto3D(centroX + h, centroY - h, centroZ - h), // 1
        Ponto3D(centroX + h, centroY + h, centroZ - h), // 2
        Ponto3D(centroX - h, centroY + h, centroZ - h), // 3
        Ponto3D(centroX - h, centroY - h, centroZ + h), // 4
        Ponto3D(centroX + h, centroY - h, centroZ + h), // 5
        Ponto3D(centroX + h, centroY + h, centroZ + h), // 6
        Ponto3D(centroX - h, centroY + h, centroZ + h)  // 7
    };

    // 12 Arestas do cubo
    // Base frontal (Z - h)
    segmentos.push_back(Segmento3D(v[0], v[1]));
    segmentos.push_back(Segmento3D(v[1], v[2]));
    segmentos.push_back(Segmento3D(v[2], v[3]));
    segmentos.push_back(Segmento3D(v[3], v[0]));

    // Base traseira (Z + h)
    segmentos.push_back(Segmento3D(v[4], v[5]));
    segmentos.push_back(Segmento3D(v[5], v[6]));
    segmentos.push_back(Segmento3D(v[6], v[7]));
    segmentos.push_back(Segmento3D(v[7], v[4]));

    // Conexões laterais entre as bases
    segmentos.push_back(Segmento3D(v[0], v[4]));
    segmentos.push_back(Segmento3D(v[1], v[5]));
    segmentos.push_back(Segmento3D(v[2], v[6]));
    segmentos.push_back(Segmento3D(v[3], v[7]));
}

// Criação de uma Pirâmide 3D de base quadrada (5 vértices e 8 arestas)
void Objeto3D::criarPiramide(double base, double altura, double centroX, double centroY, double centroZ) {
    segmentos.clear();
    double h = base / 2.0;

    Ponto3D base0(centroX - h, centroY - altura / 2.0, centroZ - h);
    Ponto3D base1(centroX + h, centroY - altura / 2.0, centroZ - h);
    Ponto3D base2(centroX + h, centroY - altura / 2.0, centroZ + h);
    Ponto3D base3(centroX - h, centroY - altura / 2.0, centroZ + h);
    Ponto3D apice(centroX, centroY + altura / 2.0, centroZ);

    // 4 arestas da base
    segmentos.push_back(Segmento3D(base0, base1));
    segmentos.push_back(Segmento3D(base1, base2));
    segmentos.push_back(Segmento3D(base2, base3));
    segmentos.push_back(Segmento3D(base3, base0));

    // 4 arestas laterais subindo ao ápice
    segmentos.push_back(Segmento3D(base0, apice));
    segmentos.push_back(Segmento3D(base1, apice));
    segmentos.push_back(Segmento3D(base2, apice));
    segmentos.push_back(Segmento3D(base3, apice));
}

// Leitura de arquivo texto com as coordenadas de um objeto 3D
// Suporta:
// 1) Linhas com 6 valores: x1 y1 z1 x2 y2 z2 (lista de segmentos de arame)
// 2) Formato de Vértices e Arestas: 'VERTICES N', linhas x y z, 'ARESTAS M', linhas v1 v2
// 3) Formato Wavefront .obj simples: 'v x y z' e 'l v1 v2' ou faces 'f ...'
bool Objeto3D::carregarDeArquivo(String caminhoArquivo) {
    std::string path = AnsiString(caminhoArquivo).c_str();
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        return false;
    }

    std::vector<Segmento3D> novosSegmentos;
    std::vector<Ponto3D> verticesLidos;

    std::string line;
    bool formatoVerticesArestas = false;
    int qtdVertices = 0;
    int qtdArestas = 0;
    bool lendoArestas = false;

    while (std::getline(file, line)) {
        // Remove espaços em branco nas extremidades
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        line = line.substr(start);

        // Ignora comentários
        if (line[0] == '#' || (line.size() >= 2 && line[0] == '/' && line[1] == '/')) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        ss >> token;

        // Caso 1: OBJ Wavefront ('v' para vértice, 'l' para linha/aresta, 'f' para face)
        if (token == "v") {
            double x, y, z;
            if (ss >> x >> y >> z) {
                verticesLidos.push_back(Ponto3D(x, y, z));
            }
            continue;
        } else if (token == "l") {
            int i1, i2;
            if (ss >> i1 >> i2) {
                // Índices em OBJ são 1-based
                int idx1 = (i1 > 0) ? (i1 - 1) : (int)verticesLidos.size() + i1;
                int idx2 = (i2 > 0) ? (i2 - 1) : (int)verticesLidos.size() + i2;
                if (idx1 >= 0 && idx1 < (int)verticesLidos.size() &&
                    idx2 >= 0 && idx2 < (int)verticesLidos.size()) {
                    novosSegmentos.push_back(Segmento3D(verticesLidos[idx1], verticesLidos[idx2]));
                }
            }
            continue;
        } else if (token == "f") {
            std::vector<int> faceIndices;
            std::string vertRef;
            while (ss >> vertRef) {
                // Remove partes de textura/normal (ex: "1/1/1" -> 1)
                size_t slash = vertRef.find('/');
                if (slash != std::string::npos) {
                    vertRef = vertRef.substr(0, slash);
                }
                int idx = std::atoi(vertRef.c_str());
                int mapped = (idx > 0) ? (idx - 1) : (int)verticesLidos.size() + idx;
                if (mapped >= 0 && mapped < (int)verticesLidos.size()) {
                    faceIndices.push_back(mapped);
                }
            }
            for (size_t k = 0; k < faceIndices.size(); k++) {
                int a = faceIndices[k];
                int b = faceIndices[(k + 1) % faceIndices.size()];
                novosSegmentos.push_back(Segmento3D(verticesLidos[a], verticesLidos[b]));
            }
            continue;
        }

        // Caso 2: Cabeçalhos VERTICES ou ARESTAS
        if (token == "VERTICES" || token == "V") {
            formatoVerticesArestas = true;
            lendoArestas = false;
            ss >> qtdVertices;
            continue;
        }
        if (token == "ARESTAS" || token == "A" || token == "EDGES" || token == "E") {
            formatoVerticesArestas = true;
            lendoArestas = true;
            ss >> qtdArestas;
            continue;
        }

        // Caso 3: Linha numérica
        // Se estamos lendo arestas do formato V/A
        if (formatoVerticesArestas) {
            if (lendoArestas) {
                int i1 = std::atoi(token.c_str());
                int i2;
                if (ss >> i2) {
                    // Trata 0-based ou 1-based automaticamente
                    int minIdx = (i1 < i2) ? i1 : i2;
                    int maxIdx = (i1 > i2) ? i1 : i2;
                    if (minIdx == 0 || maxIdx < (int)verticesLidos.size()) {
                        // 0-based
                        if (i1 >= 0 && i1 < (int)verticesLidos.size() &&
                            i2 >= 0 && i2 < (int)verticesLidos.size()) {
                            novosSegmentos.push_back(Segmento3D(verticesLidos[i1], verticesLidos[i2]));
                        }
                    } else if (i1 > 0 && i1 <= (int)verticesLidos.size() &&
                               i2 > 0 && i2 <= (int)verticesLidos.size()) {
                        // 1-based
                        novosSegmentos.push_back(Segmento3D(verticesLidos[i1 - 1], verticesLidos[i2 - 1]));
                    }
                }
            } else {
                // Lendo vértice x y z
                double x = std::atof(token.c_str());
                double y, z;
                if (ss >> y >> z) {
                    verticesLidos.push_back(Ponto3D(x, y, z));
                }
            }
            continue;
        }

        // Caso 4: Formato direto de Segmento (6 números: x1 y1 z1 x2 y2 z2)
        // Se a primeira palavra for "SEGMENTO" ou "S", consome
        double x1;
        if (token == "SEGMENTO" || token == "SEGMENTOS" || token == "S") {
            if (!(ss >> x1)) continue;
        } else {
            x1 = std::atof(token.c_str());
        }

        double y1, z1, x2, y2, z2;
        if (ss >> y1 >> z1 >> x2 >> y2 >> z2) {
            novosSegmentos.push_back(Segmento3D(Ponto3D(x1, y1, z1), Ponto3D(x2, y2, z2)));
        } else {
            // Pode ser um vértice solto
            double y, z;
            std::stringstream ssVert(line);
            if (ssVert >> x1 >> y >> z) {
                verticesLidos.push_back(Ponto3D(x1, y, z));
            }
        }
    }

    file.close();

    // Se foram lidos vértices avulsos (como no formato ensinado pelo professor no quadro com 3 vértices por face):
    if (novosSegmentos.empty() && !verticesLidos.empty()) {
        auto temSegmento = [&](const Ponto3D& a, const Ponto3D& b) {
            for (size_t k = 0; k < novosSegmentos.size(); k++) {
                const Segmento3D& s = novosSegmentos[k];
                bool direto = (fabs(s.p1.x - a.x) < 1e-4 && fabs(s.p1.y - a.y) < 1e-4 && fabs(s.p1.z - a.z) < 1e-4) &&
                              (fabs(s.p2.x - b.x) < 1e-4 && fabs(s.p2.y - b.y) < 1e-4 && fabs(s.p2.z - b.z) < 1e-4);
                bool inverso = (fabs(s.p1.x - b.x) < 1e-4 && fabs(s.p1.y - b.y) < 1e-4 && fabs(s.p1.z - b.z) < 1e-4) &&
                               (fabs(s.p2.x - a.x) < 1e-4 && fabs(s.p2.y - a.y) < 1e-4 && fabs(s.p2.z - a.z) < 1e-4);
                if (direto || inverso) return true;
            }
            return false;
        };

        if (verticesLidos.size() % 3 == 0) {
            // Formato de aula do professor: grupos de 3 vértices definindo faces triangulares
            for (size_t i = 0; i < verticesLidos.size(); i += 3) {
                Ponto3D p0 = verticesLidos[i];
                Ponto3D p1 = verticesLidos[i + 1];
                Ponto3D p2 = verticesLidos[i + 2];
                if (!temSegmento(p0, p1)) novosSegmentos.push_back(Segmento3D(p0, p1));
                if (!temSegmento(p1, p2)) novosSegmentos.push_back(Segmento3D(p1, p2));
                if (!temSegmento(p2, p0)) novosSegmentos.push_back(Segmento3D(p2, p0));
            }
        } else if (verticesLidos.size() % 2 == 0) {
            // Pares de vértices definindo segmentos de reta
            for (size_t i = 0; i < verticesLidos.size(); i += 2) {
                novosSegmentos.push_back(Segmento3D(verticesLidos[i], verticesLidos[i + 1]));
            }
        } else {
            // Polígono contínuo fechado
            for (size_t i = 0; i < verticesLidos.size(); i++) {
                novosSegmentos.push_back(Segmento3D(verticesLidos[i], verticesLidos[(i + 1) % verticesLidos.size()]));
            }
        }
    }

    if (novosSegmentos.empty()) {
        return false;
    }

    segmentos = novosSegmentos;
    return true;
}

// Grava as coordenadas do objeto 3D em formato texto de segmentos
bool Objeto3D::salvarParaArquivo(String caminhoArquivo) {
    std::string path = AnsiString(caminhoArquivo).c_str();
    std::ofstream file(path.c_str());
    if (!file.is_open()) {
        return false;
    }

    file << "# Modelo 3D de Arame (Wireframe)\n";
    file << "# Quantidade de segmentos: " << segmentos.size() << "\n";
    file << "# Formato: x1 y1 z1 x2 y2 z2\n";
    file << "SEGMENTOS " << segmentos.size() << "\n";

    for (size_t i = 0; i < segmentos.size(); i++) {
        file << segmentos[i].p1.x << " " << segmentos[i].p1.y << " " << segmentos[i].p1.z << " "
             << segmentos[i].p2.x << " " << segmentos[i].p2.y << " " << segmentos[i].p2.z << "\n";
    }

    file.close();
    return true;
}

// Projeção e desenho dos segmentos 3D diretamente no TCanvas do formulário
void Objeto3D::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta, int tipoProjecao, double dPerspectiva) {
    if (segmentos.empty() || !canvas) {
        return;
    }

    TPenStyle estiloAntigo = canvas->Pen->Style;
    TColor corAntiga = canvas->Pen->Color;
    int larguraAntiga = canvas->Pen->Width;

    canvas->Pen->Color = cor;
    canvas->Pen->Width = 2;

    for (size_t i = 0; i < segmentos.size(); i++) {
        Ponto p2d1, p2d2;

        switch (tipoProjecao) {
            case PROJECAO_ORTOGRAFICA:
                p2d1 = segmentos[i].p1.projetaOrtografica();
                p2d2 = segmentos[i].p2.projetaOrtografica();
                break;
            case PROJECAO_CAVALEIRA:
                p2d1 = segmentos[i].p1.projetaCavaleira();
                p2d2 = segmentos[i].p2.projetaCavaleira();
                break;
            case PROJECAO_PERSPECTIVA:
            default:
                p2d1 = segmentos[i].p1.projetaPerspectiva(dPerspectiva);
                p2d2 = segmentos[i].p2.projetaPerspectiva(dPerspectiva);
                break;
        }

        switch (tipoReta) {
            case 0: { // Padrão MoveTo / LineTo
                int x1 = p2d1.xW2Vp(mundo, vp);
                int y1 = p2d1.yW2Vp(mundo, vp);
                int x2 = p2d2.xW2Vp(mundo, vp);
                int y2 = p2d2.yW2Vp(mundo, vp);
                canvas->MoveTo(x1, y1);
                canvas->LineTo(x2, y2);
                break;
            }
            case 1: { // DDA
                Poligono polyAux;
                polyAux.desenharDDA(p2d1, p2d2, mundo, vp, canvas);
                break;
            }
            case 2: { // Bresenham
                Poligono polyAux;
                polyAux.desenharBRESENHAM(p2d1, p2d2, mundo, vp, canvas);
                break;
            }
        }
    }

    canvas->Pen->Style = estiloAntigo;
    canvas->Pen->Color = corAntiga;
    canvas->Pen->Width = larguraAntiga;
}

// Converte os segmentos 3D projetados em polígonos 2D para integração com o DisplayFile
std::vector<Poligono> Objeto3D::gerarPoligonos2D(int idInicial, int tipoProjecao, double dPerspectiva) {
    std::vector<Poligono> lista;
    int currId = idInicial;

    for (size_t i = 0; i < segmentos.size(); i++) {
        Poligono p;
        p.id = currId++;
        p.tipo = '3'; // Tipo 3D Wireframe

        Ponto p2d1, p2d2;
        switch (tipoProjecao) {
            case PROJECAO_ORTOGRAFICA:
                p2d1 = segmentos[i].p1.projetaOrtografica();
                p2d2 = segmentos[i].p2.projetaOrtografica();
                break;
            case PROJECAO_CAVALEIRA:
                p2d1 = segmentos[i].p1.projetaCavaleira();
                p2d2 = segmentos[i].p2.projetaCavaleira();
                break;
            case PROJECAO_PERSPECTIVA:
            default:
                p2d1 = segmentos[i].p1.projetaPerspectiva(dPerspectiva);
                p2d2 = segmentos[i].p2.projetaPerspectiva(dPerspectiva);
                break;
        }

        p.pontos.push_back(p2d1);
        p.pontos.push_back(p2d2);
        lista.push_back(p);
    }

    return lista;
}

// Exibe resumo do Objeto3D no TListBox
void Objeto3D::mostra(TListBox *listbox) {
    if (!listbox) return;
    listbox->Items->Add(IntToStr(id) + " - 3D: " + nome + " (" +
                        IntToStr((int)segmentos.size()) + " arestas)");
}

// Exibe as coordenadas 3D de todas as arestas no TListBox de detalhes
void Objeto3D::mostraSegmentos(TListBox *listbox) {
    if (!listbox) return;
    listbox->Items->Clear();
    for (size_t i = 0; i < segmentos.size(); i++) {
        listbox->Items->Add("S" + IntToStr((int)i) + ": " +
                            segmentos[i].p1.mostra() + " -> " +
                            segmentos[i].p2.mostra());
    }
}
