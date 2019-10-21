#define NumSensores 4
const short numAmostras = 6;
#define NumMenus 3

#define Esquerda 0
#define Direita 1
#define Frente 2
#define ProcurarDireita 3
#define ProcurarEsquerda 4
#define DireitaParcial 5
#define EsquerdaParcial 6
#define ParaTras 7
#define Inclinado 8
#define Parado 9
#define NaoInclinado 10

#define Acelerometro 3
#define SonarEsquerdo 0
#define SonarDireito 1
#define SonarCentro 2

#define NumEstrategias 4
#define numMoves 8
#define Estrategias 0
#define Esperar5s 1
#define movInicial 2
#define MenuAcelerometro 3

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
bool AcelerometroCair = 0;
int StatusAcel = 0;

int somaAmostras[NumSensores];

string StatusDisplay[8];
string ConfigMenu[2];
string Menus[NumMenus][numMoves+1];
void configurarTextos();

void ConfigurarVariaveis(){
	configurarTextos();
	for(int i = 0; i < NumSensores; i++){
		intervaloAtual[i] = 0;
		UltimaLeitura[i] = 77*0.5;
		somaAmostras[i] = 255*numAmostras;
		if(i == Acelerometro){
			somaAmostras[i] = 0;
			for(int j = 0; j < 3; j++){
				amostrasSensor[i][j] = 0;
			}
			ValorAnterior[i] = 0;
			ValorSensor[i] = 0;
		}
		else{
			ValorAnterior[i] = 255;
			ValorSensor[i] = 255;
			for(int j = 0; j < numAmostras; j++){
				amostrasSensor[i][j] = 255;
			}
		}
	}
}

//void configurarEstrategias();
void configurarMovimentacaoInicial();

void configurarTextos(){
	StatusDisplay[Frente] = "Frente";
	StatusDisplay[Direita] = "Direita";
	StatusDisplay[Esquerda] = "Esquerda";
	StatusDisplay[ProcurarDireita] = "Procurar Direita";
	StatusDisplay[ProcurarEsquerda] = "Procurar Esquerda";
	StatusDisplay[DireitaParcial] = "Direita Parcial";
	StatusDisplay[EsquerdaParcial] = "Esquerda Parcial";

	ConfigMenu[1] = "->";
	ConfigMenu[0] = "  ";

	configurarMovimentacaoInicial();
	//configurarEstrategias();

	Menus[Esperar5s][0] = "Esperar 5s?";
	Menus[Esperar5s][1] = "Nao";
	Menus[Esperar5s][2] = "Sim";
}
