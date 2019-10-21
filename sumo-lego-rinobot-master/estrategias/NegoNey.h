//#define Padrao 0
#define Padrao 0
#define EstrategiaInversa 1
#define Curva 2
#define inverterCurva 3

int turnRatio;

void configurarMovimentacaoInicial(){
	Menus[Estrategias][0] = "Estrategia";
	Menus[Estrategias][1] = "Padrao";
	Menus[Estrategias][2] = "Inverter";
	Menus[Estrategias][3] = "Curva";
	Menus[Estrategias][4] = "Inverter/Curva";
}

//SEM ACELEROMETRO
task EstrategiaPadrao(){
	UltimoLado = Esquerda;
	while(true){
		if(StatusSonar == Frente){
			StatusMotor = Frente;
		}
		else if(StatusSonar == Direita){
			StatusMotor = Direita;
		}
		else if(StatusSonar == Esquerda){
			StatusMotor = Esquerda;
		}
		else if(StatusSonar == DireitaParcial){
			StatusMotor = DireitaParcial;
		}
		else if(StatusSonar == EsquerdaParcial){
			StatusMotor = EsquerdaParcial;
		}
		else if(StatusSonar == ProcurarDireita){
			StatusMotor = ProcurarDireita;
		}
		else if(StatusSonar ==ProcurarEsquerda){
			StatusMotor = ProcurarEsquerda;
		}
	}
}

//--------------------------------
void cair1(int TempoCaida){
	StatusMotor = Frente;
	wait1Msec(TempoCaida);
	StatusMotor = ParaTras;
	wait1Msec(450);
}

void cair2(int TempoCaida){
	StatusMotor = Frente;
	wait1Msec(TempoCaida);
	StatusMotor = ParaTras;
	wait1Msec(375);
}

task medirTempo (){
	ClearTimer(T4);
	print("Comecou a contar\n");
	while(SensorValue[Acelerometro] > 50 && SensorValue[Acelerometro] < 500){
		writeDebugStream("Tempo = %d\n" , time1[T4]);
		wait1Msec(6);
	}
	print("CAIU\n");
}
//-------------------------------

//COM ACELEROMETRO
task EstrategiaAcelerometro(){
	UltimoLado = Esquerda;
	while(true){
		if(StatusAcel == Inclinado){
			cair2(80);
		}
		else{
			if(StatusSonar == Frente){
				StatusMotor = Frente;
			}
			else if(StatusSonar == Direita){
				StatusMotor = Direita;
			}
			else if(StatusSonar == Esquerda){
				StatusMotor = Esquerda;
			}
			else if(StatusSonar == DireitaParcial){
				StatusMotor = DireitaParcial;
			}
			else if(StatusSonar == EsquerdaParcial){
				StatusMotor = EsquerdaParcial;
			}
			else if(StatusSonar == ProcurarDireita){
				StatusMotor = ProcurarDireita;
			}
			else if(StatusSonar ==ProcurarEsquerda){
				StatusMotor = ProcurarEsquerda;
			}

		}
	}
}


void IniciarEstrategiaPadrao(){
	if(AcelerometroCair == true){
		StartTask(EstrategiaAcelerometro);
	}
	else
		StartTask(EstrategiaPadrao);
}

//---------Estrategia Padrao------------//

void gira90Graus(short lado){
	if(lado == Esquerda){
		nSyncedMotors = synchNone;
		nMotorEncoder[D] = 0;
		nSyncedMotors = synchCB;
		nMotorEncoderTarget[D] = 90*kVelocidade;
		nSyncedTurnRatio = -100;
		MotorCentro = 0;
		MotorDireito = VelocidadeMax;
		while(nMotorRunState[D]!=runStateIdle){
			//if(ValorSensor[SonarCentro] < 25 || ValorSensor[SonarDireito] < 25 ||ValorSensor[SonarEsquerdo] < 25){
			//	MotorDireito = 0;
			//}
		}
	}
	else if(lado == Direita){
		nSyncedMotors = synchNone;
		nMotorEncoder[E] = 0;
		nSyncedMotors = synchBC;
		nMotorEncoderTarget[E] = 90*kVelocidade;
		nSyncedTurnRatio = -100;
		MotorCentro = 0;
		MotorEsquerdo = VelocidadeMax;
		while(nMotorRunState[E]!=runStateIdle){
			//if(ValorSensor[SonarCentro] < 25 || ValorSensor[SonarDireito] < 25 ||ValorSensor[SonarEsquerdo] < 25){
			//	MotorEsquerdo = 0;
			//}
		}
	}
}

void EstrategiaCurva(){
	if(UltimoLado == Direita){
		nSyncedMotors = synchNone;
		nMotorEncoder[E] = 0;
		nMotorEncoderTarget[E] = 360*kVelocidade;
		turnRatio = 50;
		fazerCurva(turnRatio, Direita);
		while(nMotorRunState[E]!=runStateIdle){}
		IniciarEstrategiaPadrao();
	}
	else if(UltimoLado == Esquerda){
		nSyncedMotors = synchNone;
		nMotorEncoder[D] = 0;
		nMotorEncoderTarget[D] = 360*kVelocidade;
		turnRatio = 50;
		fazerCurva(turnRatio, Esquerda);
		while(nMotorRunState[D]!=runStateIdle){}
		IniciarEstrategiaPadrao();
	}
}

void EstrategiaInverterCurva(){
	if(ladoInicial == Direita){
		gira90Graus(Direita);
	}
	else if(ladoInicial == Esquerda){
		gira90Graus(Esquerda);
	}
	else{
		if(UltimoLado == Esquerda){
			gira90Graus(Esquerda);
		}
		else if(UltimoLado == Direita){
			gira90Graus(Direita);
		}
	}
	EstrategiaCurva();
}

void EstrategiaInversao(){
	if(ladoInicial == Direita){
		gira90Graus(Direita);
	}
	else if(ladoInicial == Esquerda){
		gira90Graus(Esquerda);
	}
	else{
		if(UltimoLado == Esquerda){
			gira90Graus(Esquerda);
		}
		else if(UltimoLado == Direita){
			gira90Graus(Direita);
		}
	}
	IniciarEstrategiaPadrao();
}

void iniciarEstrategia(){
	StartTask(Movimentacao);
	cair2(80);
	StopTask(Movimentacao);
	if(EstrategiaSelecionada == Padrao){
		IniciarEstrategiaPadrao();
	}
	else if(EstrategiaSelecionada == EstrategiaInversa){
		EstrategiaInversao();
	}
	else if(EstrategiaSelecionada == Curva){
		EstrategiaCurva();
	}
	else if(EstrategiaSelecionada == inverterCurva){
		EstrategiaInverterCurva();
	}
}

void configurarEstrategias(){
}
