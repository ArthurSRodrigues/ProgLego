#define NumSensores 4
const short numAmostras = 6;
#define NumMenus 3

#define Esquerda 0
#define Direita 1
#define Frente 2
#define ProcurarDireita 3
#define ProcurarEsquerda 4
#define ParaTras 5
#define EsquerdaParcial 6
#define DireitaParcial 7
#define DireitaNoTalo 8
#define EsquerdaNoTalo 9

//#define Acelerometro 3
#define SonarEsquerdoFrente 0
#define SonarDireitoFrente 1
#define SonarEsquerdo 2
#define SonarDireito 3

#define NumEstrategias 4
#define Estrategias 0
#define Esperar5s 1
#define movInicial 2

#define print writeDebugStream

float ValorAnterior[NumSensores];
float ValorSensor[NumSensores];
short amostrasSensor[NumSensores][numAmostras];
int intervaloAtual[NumSensores];
float UltimaLeitura[NumSensores];
int UltimoLado = -1;
int StatusMotor = -1;
int Inclinacao = 0;
int NovoValor = 0;
float Tempo = 0;
int EstrategiaSelecionada = -1;
int Esperar = 0;
int StatusSonar = 0;
bool EnviarSensores = false;
bool rampaCaiu = true;



int somaAmostras[NumSensores];

string StatusDisplay[10];
string ConfigMenu[2];
string Menus[NumMenus][5];
void configurarTextos();

void ConfigurarVariaveis(){
	configurarTextos();
	for(int i = 0; i < NumSensores; i++){
		intervaloAtual[i] = 0;
		UltimaLeitura[i] = 77*0.5;
		somaAmostras[i] = 255*numAmostras;
		ValorAnterior[i] = 255;
		ValorSensor[i] = 255;
		for(int j = 0; j < numAmostras; j++){
			amostrasSensor[i][j] = 255;

		}
	}
}

void configurarEstrategias();
void configurarMovimentacaoInicial();

void configurarTextos(){
	StatusDisplay[Frente] = "Frente";
	StatusDisplay[Direita] = "Direita";
	StatusDisplay[Esquerda] = "Esquerda";
	StatusDisplay[ProcurarDireita] = "Procurar Direita";
	StatusDisplay[ProcurarEsquerda] = "Procurar Esquerda";
	StatusDisplay[DireitaParcial] = "Direita Parcial";
	StatusDisplay[EsquerdaParcial] = "Esquerda Parcial";
	StatusDisplay[EsquerdaNoTalo] = "EsquerdaNoTalo";
	StatusDisplay[DireitaNoTalo] = "DireitaNoTalo";


	ConfigMenu[1] = "->";
	ConfigMenu[0] = "  ";

	configurarMovimentacaoInicial();
	configurarEstrategias();

	Menus[Esperar5s][0] = "Esperar 5s?";
	Menus[Esperar5s][1] = "Nao";
	Menus[Esperar5s][2] = "Sim";
}
