#define Nada 0
#define Curva 1
#define Vira90 2
#define Diagonal 3

short movimentacaoInicial;
bool cancelarMovimentacao = false;

task detectarCancelamento(){
	cancelarMovimentacao = false;
	if(rampaCaiu == false){
		while(true){
			if(rampaCaiu){
				wait1Msec(100);
				break;
			}
		}
	}

	while((ValorSensor[SonarEsquerdoFrente] > 20) && (ValorSensor[SonarDireitoFrente] > 20) && (ValorSensor[SonarDireito] > 20) && (ValorSensor[SonarEsquerdo] > 20)){
	}
	cancelarMovimentacao = true;
	PlaySound(soundBeepBeep);
}

void configurarMovimentacaoInicial(){
	Menus[movInicial][0] = "Mov. Inicial";
	Menus[movInicial][1] = "Nada";
	//inverte o lado
	Menus[movInicial][2] = "Curva";
	Menus[movInicial][3] = "Vira90";
	//triturador
	Menus[movInicial][4] = "Diagonal";
}

//Vira 90 graus na direcao do robo adversario independente do posicionamento.

void gira90Graus(short lado){
	if(lado == Esquerda){
		nSyncedMotors = synchCB;
		//nMotorEncoderTarget[E] = (int)(90*kVelocidade);
		nSyncedTurnRatio = -100;
		nMotorEncoder[D] = 0;
		MotorDireito = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 90*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
	}
	else if(lado == Direita){
		nSyncedMotors = synchBC;
		//nMotorEncoderTarget[D] = (int)(90*kVelocidade);
		nSyncedTurnRatio = -100;
		nMotorEncoder[E] = 0;
		MotorEsquerdo = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[E] < 90*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
	}
}

void EstrategiaVira90(){
	if(ladoInicial == Esquerda){
		gira90Graus(Esquerda);
	}
	else if(ladoInicial == Direita){
		gira90Graus(Direita);
	}
	else{
		if(UltimoLado == Esquerda){
			gira90Graus(Esquerda);
		}
		else if(UltimoLado == Direita){
			gira90Graus(Direita);
		}
	}
}

// Contorna a dojo e depois procura independente do posicionamento.

void fazerCurva(short lado){
	if(lado == Direita){
		nSyncedMotors = synchBC;
		//nMotorEncoderTarget[E] = (int)(520*kVelocidade);
		nSyncedTurnRatio = 74;
		nMotorEncoder[E] = 0;
		motor[E] = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[E] < 520*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
	}
	else if(lado == Esquerda){
		nSyncedMotors = synchCB;
		//nMotorEncoderTarget[D] = (int)(520*kVelocidade);
		nSyncedTurnRatio = 74;
		nMotorEncoder[D] = 0;
		motor[D] = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 520*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
	}
}

void EstrategiaCurva(){
	if(ladoInicial == Esquerda){
		fazerCurva(Esquerda);
	}
	else if(ladoInicial == Direita){
		fazerCurva(Direita);
	}
	else{
		if(UltimoLado == Esquerda){
			fazerCurva(Esquerda);
		}
		else if(UltimoLado == Direita){
			fazerCurva(Direita);
		}
	}
}

//Anda reto na diagonal depois gira na direcao do adversario

void fazerDiagonal(short lado){
	if(lado == Direita){
		nMotorEncoder[D] = 0;
		nSyncedMotors = synchCB;
		//nMotorEncoderTarget[E] = (int)(200*kVelocidade);
		nSyncedTurnRatio = 100;
		//nao jogar valor negativo
		MotorDireito = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 180*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
		nSyncedMotors = synchCB;
		nMotorEncoder[D] = 0;
		nSyncedTurnRatio = -100;
		MotorDireito = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 70*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
		StatusMotor = ProcurarDireita;
		UltimoLado = Direita;
	}
	else if(lado == Esquerda){
		nSyncedMotors = synchCB;
		//nMotorEncoderTarget[E] = (int)(200*kVelocidade);
		nSyncedTurnRatio = 100;
		nMotorEncoder[D] = 0;
		MotorDireito = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 180*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
		nSyncedTurnRatio = -100;
		nMotorEncoder[D] = 0;
		MotorDireito = 100;
		StartTask(detectarCancelamento);
		while(nMotorEncoder[D] < 70*kVelocidade){
			if(cancelarMovimentacao){
				break;
			}
		}
		StopTask(detectarCancelamento);
		StatusMotor = ProcurarEsquerda;
		UltimoLado = Esquerda;
	}
}

void EstrategiaDiagonal(){
	if(ladoInicial != -1){
		fazerDiagonal(ladoInicial);
	}
	else{
		fazerDiagonal(UltimoLado);
	}
}



void iniciarMovimentacaoInicial(){
	if(movimentacaoInicial == Nada){
		//StartTask(EstrategiaPadrao);
	}
	else if(movimentacaoInicial == Curva){
		EstrategiaCurva();
	}
	else if(movimentacaoInicial == Vira90){
		EstrategiaVira90();
	}
	else if(movimentacaoInicial == Diagonal){
		EstrategiaDiagonal();
	}
}
