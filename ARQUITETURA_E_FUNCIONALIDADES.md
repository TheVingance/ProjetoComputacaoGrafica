# Documentação do Sistema Gráfico 2D - Computação Gráfica

Este documento descreve a arquitetura, conceitos matemáticos e algoritmos implementados no projeto atual, com referências diretas aos arquivos e funcionalidades ativas.

---

## 1. Visão Geral da Arquitetura

O projeto é construído em **C++ Builder** utilizando o framework **VCL** e compilado com o compilador moderno baseado em Clang (`bcc64x`, C++23).

A aplicação opera seguindo a arquitetura clássica de um pipeline gráfico 2D interativo:
1. **Entrada do Usuário**: Coleta de cliques de mouse e parâmetros da interface.
2. **Espaço de Modelo / Mundo**: Coordenadas matemáticas contínuas em ponto flutuante ($x_W, y_W$).
3. **Display File**: Lista de objetos da cena (`std::vector<Poligono>`).
4. **Mapeamento de Coordenadas (Window-to-Viewport)**: Conversão das coordenadas de mundo para pixels da tela.
5. **Rasterização**: Algoritmos clássicos de traçado de retas (LineTo, DDA, Bresenham) e circunferências (Ponto Médio / Simetria de 8 Octantes).

---

## 2. Estrutura dos Arquivos do Projeto

| Arquivo | Responsabilidade Principal |
| :--- | :--- |
| [`Uprincipal.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.cpp) / [`.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.h) / [`.dfm`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.dfm) | Formulário principal, eventos de botões, interação com o mouse, Pan/Zoom e orquestração da cena. |
| [`Unit1.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Unit1.cpp) / [`.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Unit1.h) | Classe `Ponto` $(x, y)$, mapeamento para viewport, operações de ponto e cálculo de outcode para clipping (`cohen`). |
| [`UJanela.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/UJanela.cpp) / [`.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/UJanela.h) | Classe `Janela`, define limites retangulares ($x_{min}, y_{min}, x_{max}, y_{max}$) para Mundo, Viewport e Janela de Clipping. |
| [`uPoligono.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.cpp) / [`.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.h) | Núcleo dos algoritmos geométricos: rasterização (DDA, Bresenham, Círculo), transformações 2D e Recorte de Linhas (Cohen-Sutherland). |
| [`uDisplay.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uDisplay.cpp) / [`.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uDisplay.h) | Classe `DisplayFile`, gerencia a lista de polígonos da cena e redesenho total do canvas. |

---

## 3. Mapeamento de Coordenadas (Window-to-Viewport Transformation)

Converte entre o sistema cartesiano do **Mundo** (com origem $(0,0)$ central e números reais) e o sistema da **Viewport / Tela** (com origem no canto superior esquerdo e números inteiros em pixels).

### A. Mundo $\rightarrow$ Viewport (Tela)
* **Localização no código**: [`Unit1.cpp:L21-L30`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Unit1.cpp#L21-L30)
* **Funções**:
  * `int Ponto::xW2Vp(Janela mundo, Janela Vp)`:
    $$X_{vp} = \frac{X_w - X_{wMin}}{X_{wMax} - X_{wMin}} \cdot (X_{vpMax} - X_{vpMin})$$
  * `int Ponto::yW2Vp(Janela mundo, Janela Vp)`:
    $$Y_{vp} = \left(1 - \frac{Y_w - Y_{wMin}}{Y_{wMax} - Y_{wMin}}\right) \cdot (Y_{vpMax} - Y_{vpMin})$$

### B. Viewport (Tela) $\rightarrow$ Mundo
* **Localização no código**: [`Uprincipal.cpp:L24-L30`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.cpp#L24-L30)
* **Funções**:
  * `double xVp2Mundo(int x, Janela mundo, Janela vp)`: Calcula a inversa de $X$ ao clicar com o mouse.
  * `double yVp2Mundo(int y, Janela Mundo, Janela vp)`: Calcula a inversa de $Y$ (invertendo o eixo vertical da tela).

---

## 4. Display File e Gerenciamento da Cena

O **Display File** armazena todas as geometrias ativas da cena em um vetor dinâmico (`std::vector<Poligono> poligonos`).

* **Inicialização da Cena (Eixos Cartesianos e Janela de Clipping)**:
  * Cria o Eixo $Y$ (ID 0, cinza), Eixo $X$ (ID 1, cinza) e o Retângulo da Janela de Clipping (ID 2, vermelho, $[-100, -100]$ a $[100, 100]$).
* **Varredura e Redesenho do Canvas**:
  * Limpa o canvas preenchendo com fundo prata (`clSilver`) e chama o método `desenha()` de cada polígono.
* **Listagem dos Objetos na UI**:
  * Atualiza o `TListBox` com o formato `ID - Tipo - N pontos`.
* **Interação de Desenho com o Mouse**:
  * **Botão Esquerdo**: Adiciona vértice ao polígono corrente.
  * **Botão Direito**: Finaliza o polígono, define `tipo = 'N'` e salva no Display File.
* **Limpar Viewport**:
  * Mantém os 3 objetos coordenados iniciais (Eixo Y, Eixo X e Retângulo de Clipping) e apaga polígonos criados pelo usuário.

---

## 5. Algoritmos de Rasterização 2D

### A. Algoritmo DDA (Digital Differential Analyzer)
* **Arquivo e Linhas**: [`uPoligono.cpp:L20-L52`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.cpp#L20-L52)
* **Função**: `void Poligono::desenharDDA(...)`
* **Conceito**: Calcula os incrementos $\Delta x$ e $\Delta y$ baseados no maior lado (`length`) e soma valores fracionários a cada passo.

### B. Algoritmo de Bresenham para Retas
* **Arquivo e Linhas**: [`uPoligono.cpp:L54-L115`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.cpp#L54-L115)
* **Função**: `void Poligono::desenharBRESENHAM(...)`
* **Conceito**: Traça retas usando apenas **aritmética inteira** e variável de erro acumulado, tratando todos os octantes com `s1`, `s2` e troca de eixos.

### C. Algoritmo de Bresenham / Ponto Médio para Circunferências
* **Arquivo e Linhas**: [`uPoligono.cpp:L117-L152`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.cpp#L117-L152)
* **Funções**:
  * `Poligono::DesenhaCircunferencia(int xc, int yc, int r)`
  * `Poligono::DesenhaPontoCircunferencia(int xc, int yc, int x, int y)`
* **Conceito**: Traça o círculo utilizando cálculo incremental no primeiro octante e simetria óctupla (8 pontos simétricos por iteração).

---

## 6. Transformações Geométricas 2D

Todas as transformações operam sobre as coordenadas dos vértices do polígono selecionado.

| Transformação | Função no Modelo (`uPoligono.cpp`) | Manipulador de Evento (`Uprincipal.cpp`) |
| :--- | :--- | :--- |
| **Translação** | `Poligono::translacao(dx, dy)` | `btTranslornarClick` |
| **Escalonamento** | `Poligono::escalonamento(dx, dy)` | `btEscalonarClick` |
| **Rotação Simples** | `Poligono::rotacao(graus)` | `btRotacionarClick` |
| **Cálculo do Ponto Médio** | `Poligono::pontoMedio()` | Utilizado na Rotação Homogênea |
| **Rotação Homogênea** | `Poligono::rotacaoHomogenea(graus)` | `btHomoRotacaoClick` |
| **Reflexão Eixo X** | `Poligono::reflexaoEixoX()` | `btReflexaoEixoXClick` |
| **Reflexão Eixo Y** | `Poligono::reflexaoEixoY()` | `YClick` |
| **Reflexão Eixo XY** | `Poligono::reflexaoEixoXY()` | `btEixoXYClick` |

### Notas Didáticas sobre Erros Conhecidos Inseridos

> [!NOTE]
> Para fins pedagógicos e alinhamento com a fase atual da disciplina:
> 1. **Erro Conhecido na Translação (`Unit1.cpp`)**:
>    A operação calcula $y = y - dy$ (sinal negativo) em vez de $y + dy$. Representa a confusão típica entre a orientação do eixo Y da tela (cresce para baixo) e o eixo Y cartesiano do mundo (cresce para cima). Ao tentar transladar um objeto para cima com valor positivo, ele se move para baixo.
> 2. **Erro Conhecido no Escalonamento (`Unit1.cpp`)**:
>    A operação calcula $y = y \cdot dx$ (usando o fator horizontal $dx$ para ambos os eixos). Representa o erro comum de copy-paste em código de computação gráfica, ignorando o fator $dy$ inserido na interface.

---

## 7. Câmera 2D: Pan e Zoom

* **Pan (Cima, Baixo, Esquerda, Direita)**: Move os limites da janela mundo somando ou subtraindo 10 unidades.
* **Zoom (+ e -)**: Amplia ou reduz os limites do mundo.
* **Coordenadas do Mouse**: Converte dinamicamente no `OnMouseMove` do Canvas para Viewport e Mundo.

---

## 8. Recorte de Linhas 2D: Algoritmo de Cohen-Sutherland

* **Arquivos e Funções**:
  * [`Unit1.cpp:L32-L41`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Unit1.cpp#L32-L41): `int Ponto::cohen(Janela clipping)`
  * [`uPoligono.cpp:L250-L315`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPoligono.cpp#L250-L315): `Poligono Poligono::clipping(Janela clip)`
  * [`Uprincipal.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.cpp): `btClippingClick(TObject *Sender)`

### A. Regiões e Códigos de Saída (Outcodes)
O espaço 2D é dividido em 9 regiões pela janela de clipping ($x_{min}, y_{min}, x_{max}, y_{max}$). Cada ponto recebe um código binário de 4 bits (`TBRL` ou `LRBT`):
* **Bit 0 (1)**: À esquerda ($x < x_{min}$)
* **Bit 1 (2)**: À direita ($x > x_{max}$)
* **Bit 2 (4)**: Abaixo ($y < y_{min}$)
* **Bit 3 (8)**: Acima ($y > y_{max}$)

### B. Classificação e Decisão Trivial
Para cada segmento de reta entre $P_1$ e $P_2$, calculam-se os outcodes $c_1 = \text{cohen}(P_1)$ e $c_2 = \text{cohen}(P_2)$:
1. **Aceitação Trivial**: Se $(c_1 \mid c_2) == 0$, ambos os pontos estão estritamente dentro da janela; o segmento é mantido integralmente.
2. **Rejeição Trivial**: Se $(c_1 \ \& \ c_2) \neq 0$, ambos os pontos compartilham uma mesma região externa (ex: ambos à esquerda); o segmento é completamente descartado.
3. **Cálculo de Interseção**: Se nenhuma condição acima for satisfeita, o segmento cruza pelo menos uma borda. Escolhe-se um ponto com código diferente de zero e calcula-se a interseção linear com a borda correspondente:
   $$x = x_1 + (x_2 - x_1) \cdot \frac{y_{\text{borda}} - y_1}{y_2 - y_1}$$
   $$y = y_1 + (y_2 - y_1) \cdot \frac{x_{\text{borda}} - x_1}{x_2 - x_1}$$
   O ponto externo é substituído pelo ponto de interseção e o processo é repetido até haver aceitação ou rejeição trivial.

### C. Comportamento na Aplicação
Ao selecionar um polígono no `TListBox` e clicar no botão **Clipping █** (`btClipping`), o sistema executa o recorte de todas as arestas do polígono em relação à janela retangular vermelha definida em mundo ($[-100, -100]$ a $[100, 100]$) e atualiza a cena em tempo real.

---

## 9. Modelagem e Transformações 3D (Modelo de Arame)

Módulo implementado para manipulação e visualização de objetos tridimensionais representados por modelos de arame (*wireframe*).

### A. Classe `Ponto3D` ([`uPonto3D.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPonto3D.h) / [`uPonto3D.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uPonto3D.cpp))
Representa um ponto no espaço euclidiano contínuo $(x, y, z)$ e realiza as operações fundamentais:
1. **Translação 3D**:
   $$x' = x + dx, \quad y' = y + dy, \quad z' = z + dz$$
2. **Escalonamento 3D**:
   $$x' = x \cdot sx, \quad y' = y \cdot sy, \quad z' = z \cdot sz$$
3. **Rotações nos Eixos Cartesianos**:
   * **Eixo X**:
     $$y' = y\cos\theta - z\sin\theta, \quad z' = y\sin\theta + z\cos\theta$$
   * **Eixo Y**:
     $$x' = x\cos\theta + z\sin\theta, \quad z' = -x\sin\theta + z\cos\theta$$
   * **Eixo Z**:
     $$x' = x\cos\theta - y\sin\theta, \quad y' = x\sin\theta + y\cos\theta$$
4. **Rotação em Torno de um Eixo Arbitrário**:
   Implementada seguindo o método dos **7 passos de alinhamento com os eixos coordenados** (Slides 20 a 29 da Aula 6 do Prof. Aldo von Wangenheim):
   1. **Translação $T(-D)$**: Translada o sistema para que o ponto inicial $P_1$ do eixo fique sobre a origem ($T(-x_1, -y_1, -z_1)$).
   2. **Rotação $R_x(\theta_x)$**: Rotação em torno do eixo $X$ para trazer o vetor diretor do eixo sobre o plano $XY$ ($z = 0$).
   3. **Rotação $R_z(\theta_z)$**: Rotação em torno do eixo $Z$ para alinhar o eixo perfeitamente com o eixo $Y$.
   4. **Rotação $R_y(\theta_{\text{original}})$**: Rotação em torno do eixo $Y$ pelo ângulo desejado.
   5. **Rotação $R_z^{-1}(-\theta_z)$**: Rotação inversa em torno de $Z$ para desfazer o passo 3.
   6. **Rotação $R_x^{-1}(-\theta_x)$**: Rotação inversa em torno de $X$ para desfazer o passo 2.
   7. **Translação $T^{-1}(+D)$**: Translação inversa de retorno para desfazer o passo 1.
5. **Projeções 3D $\rightarrow$ 2D**:
   * **Ortográfica**: descarta a coordenada $z$ ($X_{2D} = x, Y_{2D} = y$).
   * **Perspectiva**: com observador a uma distância focal $d$ ($X_{2D} = \frac{x \cdot d}{d - z}, Y_{2D} = \frac{y \cdot d}{d - z}$).
   * **Cavaleira**: projeção oblíqua preservando a escala frontal com recuo inclinado em $45^\circ$.

### B. Classe `Objeto3D` ([`uObjeto3D.h`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uObjeto3D.h) / [`uObjeto3D.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uObjeto3D.cpp))
Representa um **Modelo de Arame** (*Wireframe*) composto por:
* `std::vector<Segmento3D> segmentos;` (onde cada `Segmento3D` possui um par `Ponto3D p1` e `Ponto3D p2`).
* Executa translações, escalonamentos (na origem e no baricentro), rotações $X, Y, Z$ e rotação em torno de eixo arbitrário aplicando as transformações a todos os segmentos.

### C. Leitura de Arquivo Texto e Formato da Pirâmide ([`piramide.txt`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/piramide.txt))
O método `Objeto3D::carregarDeArquivo(caminhoArquivo)` suporta múltiplos formatos e processa nativamente o **formato da aula prática (anotado no quadro)**:
* **Formato de Faces Triangulares (Quadro da Aula 6)**:
  Contém 12 linhas com coordenadas inteiras $x, y, z$, correspondentes às 4 faces triangulares vistas de cima que convergem no ápice $(0, 0, 50)$:
  ```text
  -50 -50 0    # Face 1 (Vértices 1, 2, 5)
  -50 50 0
  0 0 50
  -50 -50 0    # Face 2 (Vértices 1, 4, 5)
  50 -50 0
  0 0 50
  -50 50 0     # Face 3 (Vértices 2, 3, 5)
  50 50 0
  0 0 50
  50 50 0      # Face 4 (Vértices 3, 4, 5)
  50 -50 0
  0 0 50
  ```
* **Processamento e Deduplicação de Arestas**:
  O método lê as 4 faces triangulares, extrai os segmentos $(P_0, P_1)$, $(P_1, P_2)$ e $(P_2, P_0)$ e descarta arestas compartilhadas duplicadas, gerando com exatidão as **8 arestas do modelo de arame da pirâmide**:
  * 4 arestas da base quadrada: $[(-50,-50) \to (-50,50)]$, $[(-50,50) \to (50,50)]$, $[(50,50) \to (50,-50)]$, $[(50,-50) \to (-50,-50)]$.
  * 4 arestas laterais subindo ao ápice: dos 4 cantos da base até $(0, 0, 50)$.
* **Outros formatos suportados**:
  * Lista de segmentos diretos: linhas com `x1 y1 z1 x2 y2 z2`.
  * Formato com blocos `VERTICES N` e `ARESTAS M`.
  * Formato Wavefront .obj simples (`v` e `l`/`f`).

---

## 10. Pipeline Completo: Do Arquivo TXT à Tela 2D

O fluxo do modelo tridimensional é estruturado em 3 etapas desacopladas:

```
[piramide.txt] 
      │
      ▼
1. Uprincipal.cpp (btCarregarPiramideTxtClick) ──► Localiza o arquivo na pasta e aciona o carregamento
      │
      ▼
2. uObjeto3D.cpp (carregarDeArquivo) ───────────► Parse linha a linha (ifstream), extrai vértices e monta os segmentos
      │
      ▼
3. uDisplay.cpp (DisplayFile::desenha) ─────────► Percorre display.objetos3D chamando desenha()
      │
      ▼
4. uObjeto3D.cpp (Objeto3D::desenha) ───────────► Projeta 3D->2D (Perspectiva/Ortográfica/Cavaleira), mapeia para Viewport e rasteriza no TCanvas
```

1. **Disparo da Ação**:
   * O botão **`Pirâmide (TXT)`** em [`Uprincipal.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/Uprincipal.cpp#L635) busca automaticamente `piramide.txt` na pasta do projeto/executável (sem necessidade de abrir o explorer) e instancia `Objeto3D obj`.
2. **Construção Geométrica**:
   * `obj.carregarDeArquivo()` popula o vetor `std::vector<Segmento3D> segmentos` e adiciona ao vetor de cena `display.objetos3D`.
3. **Exibição Inicial**:
   * O objeto é inserido na **vista de cima pura** ($z=0$ na base e $z=50$ no ápice), idêntico ao desenho no quadro.
4. **Projeção e Renderização**:
   * Em [`uObjeto3D.cpp`](file:///c:/Users/triches/Documents/Embarcadero/Studio/Projects/projetoComputacaoGrafica/projetoComputacaoGrafica/computacaoGrafica/uObjeto3D.cpp#L400), cada extremidade 3D dos segmentos é projetada para coordenadas de mundo 2D (`projetaPerspectiva()`, `projetaOrtografica()` ou `projetaCavaleira()`), mapeada para pixels da Viewport (`xW2Vp`, `yW2Vp`) e traçada no Canvas pelo algoritmo ativo (LineTo, DDA ou Bresenham).
5. **Transformações Interativas**:
   * Botões `Rx ±15°`, `Ry ±15°` e `Rz ±15°` giram a pirâmide no próprio centro (`rotacaoNoCentro`), revelando a altura do ápice e a profundidade 3D em perspectiva.



