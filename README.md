# Projeto de Computação Gráfica 2D

Sistema gráfico 2D interativo desenvolvido em **C++ Builder** utilizando o framework **VCL** e compilador moderno baseado em Clang (`bcc64x`, suporte a **C++23**).

O projeto implementa o pipeline gráfico bidimensional clássico, abordando desde o sistema de coordenadas de mundo e transformações de viewport até algoritmos de rasterização em baixo nível, transformações geométricas e recorte de primitivas.

---

## 📌 Estrutura de Branches do Repositório

O repositório está organizado em duas branches principais:

* **`main`**: Versão alinhada ao cronograma de aulas da disciplina. Contém:
  * Sistema de coordenadas e mapeamento Window-to-Viewport.
  * Rasterização de retas (Padrão, DDA, Bresenham) e circunferências (Ponto Médio).
  * Transformações geométricas 2D (Translação, Escalonamento, Rotação e Rotação Homogênea).
  * Reflexões nos eixos X, Y e XY.
  * Recorte de linhas pelo algoritmo de Cohen-Sutherland.
  * Câmera virtual 2D (Pan e Zoom).
* **`completo`**: Versão estendida que inclui adicionalmente todas as implementações de **Curvas Paramétricas e Splines**:
  * Algoritmo de De Casteljau (Bézier recursivo).
  * Curva de Hermite cúbica com controle por vetores tangentes.
  * Curva de Bézier cúbica via polinômios de Bernstein.
  * B-Spline cúbica uniforme (composição matricial).
  * B-Spline via método de Diferenças Progressivas (*Forward Differences*).

---

## 🚀 Funcionalidades Detalhadas

### 1. Mapeamento de Coordenadas (Window-to-Viewport)
Permite a visualização de coordenadas cartesianas contínuas do **Mundo** na grade de pixels discretos da **Viewport (Tela)**:
* **Mundo $\rightarrow$ Viewport**:
  $$X_{vp} = \frac{X_w - X_{wMin}}{X_{wMax} - X_{wMin}} \cdot (X_{vpMax} - X_{vpMin})$$
  $$Y_{vp} = \left(1 - \frac{Y_w - Y_{wMin}}{Y_{wMax} - Y_{wMin}}\right) \cdot (Y_{vpMax} - Y_{vpMin})$$
* **Viewport $\rightarrow$ Mundo**:
  Cálculo inverso realizado ao interagir com o mouse sobre a área de desenho (`Image1MouseMove` e `Image1MouseDown`), mapeando o clique de pixels para coordenadas reais de mundo.

### 2. Algoritmos de Rasterização 2D
O sistema permite desenhar geometrias utilizando diferentes estratégias de traçado selecionáveis via interface (`TRadioGroup`):
* **Reta Padrão do Windows**: Utiliza as funções nativas de desenho do canvas (`MoveTo` / `LineTo`).
* **Algoritmo DDA (Digital Differential Analyzer)**: Calcula variações incrementais $\Delta x$ e $\Delta y$ em ponto flutuante com base na maior dimensão do segmento.
* **Algoritmo de Bresenham para Retas**: Algoritmo incremental otimizado operando exclusivamente com **aritmética inteira** e variável de erro acumulado, cobrindo todos os octantes do plano cartesiano.
* **Algoritmo de Bresenham / Ponto Médio para Circunferências**: Rasteriza círculos utilizando cálculo incremental no primeiro octante e replicação simétrica nos 8 octantes simultaneamente.

### 3. Transformações Geométricas 2D
Operações aplicadas diretamente aos vértices do polígono selecionado no Display File:
* **Translação**: Deslocamento espacial adicionando os fatores $\Delta x$ e $\Delta y$ a cada vértice.
* **Escalonamento**: Redimensionamento proporcional ou diferencial multiplicando as coordenadas pelos fatores $S_x$ e $S_y$.
* **Rotação Simples**: Rotação trigonométrica dos pontos em torno da origem $(0, 0)$ por um ângulo $\theta$ informado em graus:
  $$x' = x \cos\theta - y \sin\theta$$
  $$y' = x \sin\theta + y \cos\theta$$
* **Rotação Homogênea (em torno do próprio centro)**:
  1. Calcula o centroide / ponto médio do polígono: $P_m = (\bar{x}, \bar{y})$.
  2. Constrói as matrizes homogêneas $3 \times 3$:
     $$M_1 = T(-P_m) \quad \text{(translada centro para a origem)}$$
     $$M_2 = R(\theta) \quad \text{(rotaciona na origem)}$$
     $$M_3 = T(P_m) \quad \text{(retorna o centro à posição original)}$$
  3. Multiplica $M_{res} = M_1 \cdot M_2 \cdot M_3$ e transforma as coordenadas homogêneas $[x, y, 1]$ de cada vértice.
* **Reflexões 2D**:
  * **Eixo X**: Inverte o sinal das coordenadas horizontais ($x' = -x$).
  * **Eixo Y**: Inverte o sinal das coordenadas verticais ($y' = -y$).
  * **Eixo X e Y**: Inverte o sinal de ambos os eixos simultaneamente (reflexão em torno da origem).

### 4. Recorte de Linhas (Clipping) - Cohen-Sutherland
Implementação do clássico algoritmo de recorte contra uma janela retangular vermelha definida em mundo ($[-100, -100]$ a $[100, 100]$):
* **Classificação de Regiões (Outcodes de 4 bits)**:
  * Bit 0 (`1`): À esquerda ($x < x_{min}$)
  * Bit 1 (`2`): À direita ($x > x_{max}$)
  * Bit 2 (`4`): Abaixo ($y < y_{min}$)
  * Bit 3 (`8`): Acima ($y > y_{max}$)
* **Aceitação e Rejeição Trivial**:
  * Se $(c_1 \mid c_2) == 0$: Segmento inteiramente contido na janela (aceito sem alterações).
  * Se $(c_1 \ \& \ c_2) \neq 0$: Ambos os pontos compartilham uma mesma região externa (rejeitado por completo).
* **Interseção Linear**: Quando parcialmente contido, calcula os pontos de interseção lineares exatos com as bordas da janela e gera um novo polígono recortado (tipo `'R'`).

### 5. Câmera Virtual 2D (Pan & Zoom)
* **Pan (Cima, Baixo, Esquerda, Direita)**: Move os limites da janela de mundo em incrementos de 10 unidades, recalculando e redesenhando a cena.
* **Zoom (+ e -)**: Contrai ou expande a janela de visualização do mundo, aproximando ou afastando os objetos.
* **Inspetor de Coordenadas**: Exibe na barra de status a posição instantânea do mouse convertida para coordenadas de tela (pixels) e coordenadas do mundo real.

### 6. Display File e Gerenciamento da Cena
* **Display File (`uDisplay.cpp` / `.h`)**: Mantém a lista dinâmica de todos os objetos gráficos da cena (`std::vector<Poligono>`).
* **Cena Inicial**: Carrega automaticamente os eixos coordenados $Y$ (ID 0) e $X$ (ID 1) em cinza e a janela de recorte (ID 2) em vermelho.
* **Inspeção de Vértices**: Ao selecionar um polígono no `TListBox`, todos os seus vértices são listados em tempo real na lista secundária.
* **Desenho Interativo**:
  * Botão esquerdo do mouse: Adiciona vértices em sequência.
  * Botão direito do mouse: Finaliza a criação do polígono e o registra no Display File.
* **Limpar Cena**: Remove os objetos criados pelo usuário preservando os 3 elementos estruturais iniciais.

---

## 📂 Organização dos Arquivos

| Arquivo | Descrição |
| :--- | :--- |
| `Uprincipal.cpp` / `.h` / `.dfm` | Formulário principal, eventos de interface VCL, menus, botões e captura de eventos do mouse. |
| `uPoligono.cpp` / `.h` | Implementação matemática das geometrias: DDA, Bresenham de retas e círculos, transformações 2D, reflexão e recorte Cohen-Sutherland (e curvas na branch `completo`). |
| `Unit1.cpp` / `.h` | Estrutura de `Ponto` $(x, y)$, mapeamento de coordenadas e funções de ponto individual. |
| `UJanela.cpp` / `.h` | Definição da estrutura retangular de limites $(x_{min}, y_{min}, x_{max}, y_{max})$. |
| `uDisplay.cpp` / `.h` | Estrutura do Display File responsável pelo redesenho de todos os polígonos no canvas. |
| `CG1.cbproj` | Arquivo de projeto do Embarcadero C++ Builder. |
| `.gitignore` | Configuração de exclusão de artefatos de compilação (`Win64x/`, `Win32/`), caches do IDE (`__astcache/`, `__history/`) e configurações locais. |

---

## 🛠️ Como Compilar e Executar

1. Abra o **Embarcadero C++ Builder** (ou RAD Studio).
2. Acesse o menu **File $\rightarrow$ Open Project...** e selecione o arquivo `CG1.cbproj`.
3. Certifique-se de que o alvo de compilação está definido como **Win64x** (ou Win32).
4. Pressione **F9** (Run) ou **Shift + F9** (Build).
5. O compilador gerará automaticamente os diretórios de saída e executará a aplicação.
