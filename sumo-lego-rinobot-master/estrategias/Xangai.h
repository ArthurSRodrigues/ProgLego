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

//---------Estrategia Padrao------------//

void gira90Graus(short lado){
	if(lado == Esquerda){
		nSyncedMotors = synchNone;
		nMotorEncoder[D] = 0;
		nSyncedMotors = synchCB;
		//nMotorEncoderTarget[D] = (int)90*kVelocidade;
		nSyncedTurnRatio = -100;
		MotorCentro = 0;
		MotorDireito = VelocidadeMax;
		while(nMotorEncoder[D] < 90*kVelocidade){
			print("TA GIRANU\n");
			wait10Msec(5);
			//if(ValorSensor[SonarCentro] < 25 || ValorSensor[SonarDireito] < 25 ||ValorSensor[SonarEsquerdo] < 25){
			//	MotorDireito = 0;
			//}
		}
	}
	else if(lado == Direita){
		nSyncedMotors = synchNone;
		nMotorEncoder[E] = 0;
		nSyncedMotors = synchBC;
		//nMotorEncoderTarget[E] = (int)90*kVelocidade;
		nSyncedTurnRatio = -100;
		MotorCentro = 0;
		MotorEsquerdo = VelocidadeMax;
		while(nMotorEncoder[E] < 90*kVelocidade){
			print("TA GIRANU\n");
			wait10Msec(5);
			//if(ValorSensor[SonarCentro] < 25 || ValorSensor[SonarDireito] < 25 ||ValorSensor[SonarEsquerdo] < 25){
			//	MotorEsquerdo = 0;
			//}
		}
		print("PARO DI GIRA");
	}
}

void fazerCurvaDireita(){
	nSyncedMotors = synchNone;
	nMotorEncoder[E] = 0;
	//nMotorEncoderTarget[E] = 360*kVelocidade;
	turnRatio = 50;
	fazerCurva(turnRatio, Direita);
	while(nMotorEncoder[E] < 360*kVelocidade){}
}

void fazerCurvaEsquerda(){
	nSyncedMotors = synchNone;
	nMotorEncoder[D] = 0;
	//nMotorEncoderTarget[D] = 360*kVelocidade;
	turnRatio = 50;
	fazerCurva(turnRatio, Esquerda);
	while(nMotorEncoder[D] < 360*kVelocidade){}
}

void EstrategiaCurva(int lado){
	if(lado == Direita){
		fazerCurvaEsquerda();
	}
	else if(lado == Esquerda){
		fazerCurvaDireita();
	}
	else{
		if(ladoInicial == Direita){
			fazerCurvaDireita();
		}
		else if(ladoInicial == Esquerda){
			fazerCurvaEsquerda();
		}
		else{
			if(UltimoLado == Direita){
				fazerCurvaDireita();
			}
			else if(UltimoLado == Esquerda){
				fazerCurvaEsquerda();
			}
		}
		StartTask(EstrategiaPadrao);
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
	EstrategiaCurva(ladoInicial);
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
	StartTask(EstrategiaPadrao);
}

void iniciarEstrategia(){
	if(EstrategiaSelecionada == Padrao){
		StartTask(EstrategiaPadrao);
	}
	else if(EstrategiaSelecionada == EstrategiaInversa){
		EstrategiaInversao();
	}
	else if(EstrategiaSelecionada == Curva){
		EstrategiaCurva(-1);
	}
	else if(EstrategiaSelecionada == inverterCurva){
		EstrategiaInverterCurva();
	}
}
