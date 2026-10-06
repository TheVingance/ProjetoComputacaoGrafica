object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Computacao Grafica'
  ClientHeight = 581
  ClientWidth = 1044
  Color = clBtnHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object lbMundo: TLabel
    Left = 500
    Top = 495
    Width = 49
    Height = 15
    Caption = 'lbMundo'
  end
  object lbVp: TLabel
    Left = 48
    Top = 495
    Width = 24
    Height = 15
    Caption = 'lbVp'
  end
  object lbPoligono: TLabel
    Left = 778
    Top = 99
    Width = 53
    Height = 15
    Caption = 'Poligonos'
  end
  object lbPonto: TLabel
    Left = 626
    Top = 99
    Width = 37
    Height = 15
    Caption = 'Pontos'
  end
  object lbZoom: TLabel
    Left = 934
    Top = 8
    Width = 47
    Height = 15
    Caption = 'Zoom '#55357#56589
  end
  object Panel1: TPanel
    Left = 48
    Top = 8
    Width = 502
    Height = 481
    TabOrder = 0
    object Image1: TImage
      Left = 1
      Top = 1
      Width = 500
      Height = 479
      Align = alClient
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      ExplicitLeft = -15
      ExplicitTop = -7
    end
  end
  object lbPoligonos: TListBox
    Left = 774
    Top = 120
    Width = 142
    Height = 151
    ItemHeight = 15
    TabOrder = 1
    OnClick = lbPoligonosClick
  end
  object lbPontos: TListBox
    Left = 626
    Top = 120
    Width = 142
    Height = 151
    ItemHeight = 15
    TabOrder = 2
  end
  object btIniciar: TButton
    Left = 579
    Top = 29
    Width = 75
    Height = 25
    Caption = 'Iniciar'
    TabOrder = 3
    OnClick = btIniciarClick
  end
  object btLimpar: TButton
    Left = 660
    Top = 29
    Width = 75
    Height = 25
    Caption = 'Limpar'
    TabOrder = 13
    OnClick = btLimparClick
  end
  object btBaixo: TButton
    Left = 814
    Top = 60
    Width = 42
    Height = 25
    Caption = #11107
    TabOrder = 4
    OnClick = btBaixoClick
  end
  object btCima: TButton
    Left = 814
    Top = 29
    Width = 42
    Height = 25
    Caption = ' '#11105
    TabOrder = 5
    OnClick = btCimaClick
  end
  object btEsquerda: TButton
    Left = 766
    Top = 60
    Width = 42
    Height = 25
    Caption = #11104
    TabOrder = 6
    OnClick = btEsquerdaClick
  end
  object btDireita: TButton
    Left = 862
    Top = 60
    Width = 42
    Height = 25
    Caption = #11106
    TabOrder = 7
    OnClick = btDireitaClick
  end
  object btZoomOut: TButton
    Left = 931
    Top = 29
    Width = 22
    Height = 25
    Caption = '+'
    TabOrder = 8
    OnClick = btZoomOutClick
  end
  object btZoomIn: TButton
    Left = 959
    Top = 29
    Width = 22
    Height = 25
    Caption = '-'
    TabOrder = 9
    OnClick = btZoomInClick
  end
  object componentes: TPageControl
    Left = 580
    Top = 277
    Width = 437
    Height = 202
    ActivePage = TabSheet3D
    TabOrder = 10
    object TabSheet1: TTabSheet
      Caption = 'Mundo'
      object lbXMinimo: TLabel
        Left = 81
        Top = 27
        Width = 49
        Height = 15
        Caption = 'Xminimo'
      end
      object lbYMinimo: TLabel
        Left = 136
        Top = 27
        Width = 48
        Height = 15
        Caption = 'Yminimo'
      end
      object lbXMaximo: TLabel
        Left = 79
        Top = 77
        Width = 50
        Height = 15
        Caption = 'Xmaximo'
      end
      object lbYMaximo: TLabel
        Left = 136
        Top = 77
        Width = 49
        Height = 15
        Caption = 'Ymaximo'
      end
      object edXMin: TEdit
        Left = 85
        Top = 48
        Width = 45
        Height = 23
        TabOrder = 0
        TextHint = '-250'
      end
      object edXMax: TEdit
        Left = 85
        Top = 98
        Width = 45
        Height = 23
        TabOrder = 1
        TextHint = '250'
      end
      object edYMin: TEdit
        Left = 136
        Top = 48
        Width = 45
        Height = 23
        TabOrder = 2
        TextHint = '-250'
      end
      object edYmax: TEdit
        Left = 136
        Top = 98
        Width = 49
        Height = 23
        TabOrder = 3
        TextHint = '250'
      end
      object btAtualizarMundo: TButton
        Left = 80
        Top = 127
        Width = 113
        Height = 25
        Caption = 'Atualizar Mundo'
        TabOrder = 4
        OnClick = btAtualizarMundoClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Transforma'#231#245'es'
      ImageIndex = 1
      object tansalacaoX: TLabel
        Left = 3
        Top = 11
        Width = 61
        Height = 15
        Caption = 'translacaoX'
      end
      object transalacaoY: TLabel
        Left = 3
        Top = 61
        Width = 61
        Height = 15
        Caption = 'translacaoY'
      end
      object escalonamentoX: TLabel
        Left = 86
        Top = 11
        Width = 88
        Height = 15
        Caption = 'escalonamentoX'
      end
      object EscalonamentoY: TLabel
        Left = 86
        Top = 61
        Width = 88
        Height = 15
        Caption = 'escalonamentoY'
      end
      object RotacaoX: TLabel
        Left = 192
        Top = 61
        Width = 52
        Height = 15
        Caption = 'rotacaoX'#176
      end
      object edTranslacaoX: TEdit
        Left = 16
        Top = 32
        Width = 48
        Height = 23
        TabOrder = 0
        Text = '10'
      end
      object edTranslacaoY: TEdit
        Left = 16
        Top = 82
        Width = 48
        Height = 23
        ImeName = 'etTranslacaoY'
        TabOrder = 1
        Text = '10'
      end
      object btTranslornar: TButton
        Left = 3
        Top = 111
        Width = 75
        Height = 25
        Caption = 'Translornar'
        TabOrder = 2
        OnClick = btTranslornarClick
      end
      object edEscalonamentoX: TEdit
        Left = 100
        Top = 32
        Width = 48
        Height = 23
        TabOrder = 3
        Text = '1.25'
      end
      object edEscalonamentoY: TEdit
        Left = 100
        Top = 82
        Width = 48
        Height = 23
        TabOrder = 4
        Text = '1.25'
      end
      object btEscalonar: TButton
        Left = 92
        Top = 111
        Width = 75
        Height = 25
        Caption = 'Escalonar'
        DisabledImageName = 'escalonar'
        TabOrder = 5
        OnClick = btEscalonarClick
      end
      object edRotacaoX: TEdit
        Left = 196
        Top = 82
        Width = 48
        Height = 23
        TabOrder = 6
        Text = '30'
      end
      object btRotacionar: TButton
        Left = 183
        Top = 111
        Width = 75
        Height = 25
        Caption = 'Rotacionar'
        TabOrder = 7
        OnClick = btRotacionarClick
      end
      object btHomoRotacao: TButton
        Left = 183
        Top = 142
        Width = 75
        Height = 25
        Caption = 'Homogenear'
        DisabledImageName = 'btHomoRotacao'
        TabOrder = 8
        OnClick = btHomoRotacaoClick
      end
    end
    object TipoReta: TTabSheet
      Caption = 'TipoReta'
      ImageIndex = 2
      object rgTipoReta: TRadioGroup
        Left = 60
        Top = 35
        Width = 158
        Height = 89
        Caption = 'Tipo De Reta'
        ItemIndex = 0
        Items.Strings = (
          'LineTo'
          'DDA'
          'Bresenham')
        TabOrder = 0
      end
    end
    object Reflexoes: TTabSheet
      Caption = 'Reflex'#245'es'
      ImageIndex = 3
      object btReflexaoEixoX: TButton
        Left = 65
        Top = 25
        Width = 140
        Height = 32
        Caption = 'Eixo X'
        DisabledImageName = 'ReflexionarEixoX'
        TabOrder = 0
        OnClick = btReflexaoEixoXClick
      end
      object Y: TButton
        Left = 65
        Top = 72
        Width = 140
        Height = 32
        Caption = 'Eixo Y'
        TabOrder = 1
        OnClick = YClick
      end
      object btEixoXY: TButton
        Left = 65
        Top = 119
        Width = 140
        Height = 32
        Caption = 'Eixo X e Y'
        TabOrder = 2
        OnClick = btEixoXYClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Curvas'
      ImageIndex = 4
      object btHermite: TButton
        Left = 15
        Top = 88
        Width = 98
        Height = 25
        Caption = 'Hemite'
        DisabledImageName = 'btHermite'
        TabOrder = 0
        OnClick = btHermiteClick
      end
      object btCurvaCasteljau: TButton
        Left = 15
        Top = 35
        Width = 98
        Height = 25
        Caption = 'Casteljau'
        TabOrder = 1
        OnClick = btCurvaCasteljauClick
      end
      object btBezier: TButton
        Left = 144
        Top = 35
        Width = 97
        Height = 25
        Caption = 'Bezier'
        DisabledImageName = 'btBezier'
        TabOrder = 2
        OnClick = btBezierClick
      end
      object btBSspline: TButton
        Left = 144
        Top = 88
        Width = 97
        Height = 25
        Caption = 'B-Spline'
        DisabledImageName = 'btBSpline'
        TabOrder = 3
        OnClick = btBSsplineClick
      end
      object btSplineDifference: TButton
        Left = 48
        Top = 136
        Width = 161
        Height = 25
        Caption = 'bSpline - fwd Difference'
        TabOrder = 4
        OnClick = btSplineDifferenceClick
      end
    end
    object TabSheet3D: TTabSheet
      Caption = 'Objeto 3D'
      ImageIndex = 5
      object btCriarCubo3D: TButton
        Left = 6
        Top = 6
        Width = 64
        Height = 25
        Caption = 'Cubo 3D'
        TabOrder = 0
        OnClick = btCriarCubo3DClick
      end
      object btCriarPiramide3D: TButton
        Left = 73
        Top = 6
        Width = 70
        Height = 25
        Caption = 'Pir'#226'mide'
        TabOrder = 1
        OnClick = btCriarPiramide3DClick
      end
      object btCarregarPiramideTxt: TButton
        Left = 146
        Top = 6
        Width = 100
        Height = 25
        Caption = 'Pir'#226'mide (TXT)'
        TabOrder = 2
        OnClick = btCarregarPiramideTxtClick
      end
      object btLimpar3D: TButton
        Left = 249
        Top = 6
        Width = 74
        Height = 25
        Caption = 'Limpar 3D'
        TabOrder = 3
        OnClick = btLimpar3DClick
      end
      object rgProjecao3D: TRadioGroup
        Left = 6
        Top = 35
        Width = 318
        Height = 42
        Caption = 'Proje'#231#227'o 3D'
        Columns = 3
        ItemIndex = 1
        Items.Strings = (
          'Ortogr'#225'fica'
          'Perspectiva'
          'Cavaleira')
        TabOrder = 3
        OnClick = rgProjecao3DClick
      end
      object btRotXMais: TButton
        Left = 6
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Rx +15'#176
        TabOrder = 4
        OnClick = btRotXMaisClick
      end
      object btRotXMenos: TButton
        Left = 58
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Rx -15'#176
        TabOrder = 5
        OnClick = btRotXMenosClick
      end
      object btRotYMais: TButton
        Left = 114
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Ry +15'#176
        TabOrder = 6
        OnClick = btRotYMaisClick
      end
      object btRotYMenos: TButton
        Left = 166
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Ry -15'#176
        TabOrder = 7
        OnClick = btRotYMenosClick
      end
      object btRotZMais: TButton
        Left = 222
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Rz +15'#176
        TabOrder = 8
        OnClick = btRotZMaisClick
      end
      object btRotZMenos: TButton
        Left = 274
        Top = 80
        Width = 50
        Height = 24
        Caption = 'Rz -15'#176
        TabOrder = 9
        OnClick = btRotZMenosClick
      end
      object btEscalaMais3D: TButton
        Left = 6
        Top = 107
        Width = 68
        Height = 24
        Caption = 'Esc +15%'
        TabOrder = 10
        OnClick = btEscalaMais3DClick
      end
      object btEscalaMenos3D: TButton
        Left = 76
        Top = 107
        Width = 68
        Height = 24
        Caption = 'Esc -15%'
        TabOrder = 11
        OnClick = btEscalaMenos3DClick
      end
      object btTransZMais: TButton
        Left = 146
        Top = 107
        Width = 56
        Height = 24
        Caption = 'Tz +20'
        TabOrder = 12
        OnClick = btTransZMaisClick
      end
      object btTransZMenos: TButton
        Left = 204
        Top = 107
        Width = 56
        Height = 24
        Caption = 'Tz -20'
        TabOrder = 13
        OnClick = btTransZMenosClick
      end
      object btReset3D: TButton
        Left = 262
        Top = 107
        Width = 62
        Height = 24
        Caption = 'Reset'
        TabOrder = 15
        OnClick = btReset3DClick
      end
      object btRotEixoArbitrario: TButton
        Left = 6
        Top = 134
        Width = 318
        Height = 26
        Caption = 'Girar em Eixo Arbitr'#225'rio (P1 '#8594' P2)...'
        TabOrder = 14
        OnClick = btRotEixoArbitrarioClick
      end
    end
  end
  object Circulo: TButton
    Left = 580
    Top = 485
    Width = 61
    Height = 25
    Caption = 'Circulo '#9679
    TabOrder = 11
    OnClick = CirculoClick
  end
  object btClipping: TButton
    Left = 728
    Top = 485
    Width = 122
    Height = 25
    Caption = 'Clipping '#9608
    TabOrder = 12
    OnClick = btClippingClick
  end
end
