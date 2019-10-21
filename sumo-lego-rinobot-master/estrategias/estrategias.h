#define Padrao 0
#define Vira90 1
#define Contorna 2
#define estrategia3 3

short movimentacaoInicial;

void configurarMovimentacaoInicial(){
	Menus[movInicial][0] = "Mov. Inicial";
	Menus[movInicial][1] = "Nada";
	Menus[movInicial][2] = "Vira90";
	Menus[movInicial][3] = "Contornar";
	Menus[movInicial][4] = "Vira90/Contornar";
}

void configurarEstrategias(){
	Menus[Estrategias][0] = "Estrategia";
	Menus[Estrategias][1] = "Padrao";
	Menus[Estrategias][2] = "Vira90";
	Menus[Estrategias][3] = "Contornar";
	Menus[Estrategias][4] = "ReDireita";
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

//Vira 90 graus na direcao do robo adversario independente do posicionamento.

void EstrategiaVira90(){
	if(UltimoLado == Esquerda){
		nSyncedMotors = synchBC;
		nMotorEncoderTarget[E] = (int)(90*kVelocidade);
		nSyncedTurnRatio = -100;
		motor[E] = -100;
		while(nMotorRunState[motorB] != runStateIdle){
		}
	}
	else if(UltimoLado == Direita){
		nSyncedMotors = synchCB;
		nMotorEncoderTarget[D] = (int)(90*kVelocidade);
		nSyncedTurnRatio = -100;
		motor[D] = -100;
		while(nMotorRunState[motorC] != runStateIdle){
		}
	}
	StartTask(EstrategiaPadrao);
}

// Contorna a dojo e depois procura independente do posicionamento.

void EstrategiaContornar(){
	if(UltimoLado == Direita){
		nSyncedMotors = synchBC;
		nMotorEncoderTarget[E] = (int)(520*kVelocidade);
		nSyncedTurnRatio = 74;
		motor[E] = 100;
		while(nMotorRunState[E] != runStateIdle){
			if((ValorSensor[SonarCentro] <= 20) || (ValorSensor[SonarDireito] <= 20) || (ValorSensor[SonarEsquerdo] <= 20)){
				MotorEsquerdo = 0;
			}
		}
	}
	else if(UltimoLado == Esquerda){
		nSyncedMotors = synchCB;
		nMotorEncoderTarget[D] = (int)(520*kVelocidade);
		nSyncedTurnRatio = 74;
		motor[D] = 100;
		while(nMotorRunState[D] != runStateIdle){
			if((ValorSensor[SonarCentro] <= 20) || (ValorSensor[SonarDireito] <= 20) || (ValorSensor[SonarEsquerdo] <= 20)){
				MotorDireito = 0;
			}
		}
		StartTask(EstrategiaPadrao);
	}
}

void iniciarEstrategia(){
	if(EstrategiaSelecionada == Padrao){
		StartTask(EstrategiaPadrao);
	}
	else if(EstrategiaSelecionada == Vira90){
		EstrategiaVira90();
	}
	else if(EstrategiaSelecionada == Contorna){
		EstrategiaContornar();
	}
	else if(EstrategiaSelecionada == estrategia3){
		//	EstrategiaFrente();
	}
}

void iniciarMovimentacaoInicial(){
	if(movimentacaoInicial == Padrao){
		StartTask(EstrategiaPadrao);
	}
	else if(movimentacaoInicial == Vira90){
		EstrategiaVira90();
	}
	else if(movimentacaoInicial == Contorna){
		EstrategiaContornar();
	}
	else if(movimentacaoInicial == estrategia3){
		//	EstrategiaFrente();
	}
}
