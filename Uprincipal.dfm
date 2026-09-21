object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Computacao Grafica'
  ClientHeight = 581
  ClientWidth = 889
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
    Left = 685
    Top = 99
    Width = 53
    Height = 15
    Caption = 'Poligonos'
  end
  object lbPonto: TLabel
    Left = 558
    Top = 99
    Width = 37
    Height = 15
    Caption = 'Pontos'
  end
  object lbZoom: TLabel
    Left = 774
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
    Left = 685
    Top = 120
    Width = 121
    Height = 97
    ItemHeight = 15
    TabOrder = 1
    OnClick = lbPoligonosClick
  end
  object lbPontos: TListBox
    Left = 558
    Top = 120
    Width = 121
    Height = 97
    ItemHeight = 15
    TabOrder = 2
  end
  object btIniciar: TButton
    Left = 595
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Iniciar'
    TabOrder = 3
    OnClick = btIniciarClick
  end
  object btLimpar: TButton
    Left = 676
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Limpar'
    TabOrder = 12
    OnClick = btLimparClick
  end
  object btBaixo: TButton
    Left = 612
    Top = 70
    Width = 42
    Height = 25
    Caption = #11107
    TabOrder = 4
    OnClick = btBaixoClick
  end
  object btCima: TButton
    Left = 612
    Top = 39
    Width = 42
    Height = 25
    Caption = ' '#11105
    TabOrder = 5
    OnClick = btCimaClick
  end
  object btEsquerda: TButton
    Left = 564
    Top = 70
    Width = 42
    Height = 25
    Caption = #11104
    TabOrder = 6
    OnClick = btEsquerdaClick
  end
  object btDireita: TButton
    Left = 660
    Top = 70
    Width = 42
    Height = 25
    Caption = #11106
    TabOrder = 7
    OnClick = btDireitaClick
  end
  object btZoomOut: TButton
    Left = 771
    Top = 29
    Width = 22
    Height = 25
    Caption = '+'
    TabOrder = 8
    OnClick = btZoomOutClick
  end
  object btZoomIn: TButton
    Left = 799
    Top = 29
    Width = 22
    Height = 25
    Caption = '-'
    TabOrder = 9
    OnClick = btZoomInClick
  end
  object componentes: TPageControl
    Left = 556
    Top = 239
    Width = 269
    Height = 202
    ActivePage = TabSheet1
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
        Left = 19
        Top = 32
        Width = 38
        Height = 23
        TabOrder = 0
        TextHint = '   T'
      end
      object edTranslacaoY: TEdit
        Left = 19
        Top = 82
        Width = 38
        Height = 23
        ImeName = 'etTranslacaoY'
        TabOrder = 1
        TextHint = '    T'
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
        Left = 104
        Top = 32
        Width = 41
        Height = 23
        TabOrder = 3
        TextHint = '   E'
      end
      object edEscalonamentoY: TEdit
        Left = 104
        Top = 82
        Width = 41
        Height = 23
        TabOrder = 4
        TextHint = '   E'
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
        Left = 200
        Top = 82
        Width = 41
        Height = 23
        TabOrder = 6
        TextHint = '   R'
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
        Caption = 'Homonegear'
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
  end
  object Circulo: TButton
    Left = 556
    Top = 447
    Width = 61
    Height = 25
    Caption = 'Circulo '#9679
    TabOrder = 11
    OnClick = CirculoClick
  end
  object btClipping: TButton
    Left = 704
    Top = 447
    Width = 122
    Height = 25
    Caption = 'Clipping '#9608
    TabOrder = 12
    OnClick = btClippingClick
  end
end
