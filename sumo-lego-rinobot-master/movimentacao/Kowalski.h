#define MotorDireito motor[D]
#define MotorEsquerdo motor[E]

float precisaoAlta = 0.4;
float precisaoMedia = precisaoAlta*1.5;
float periodoAmostragem = 0.077;

float velocidadeMotor;
float velocidadeProcura;
int distancia;

void calcularVelocidade(int dist){
	if(dist < 25){
		velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*25);
	}
	else if(dist < 35){
		velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*dist);
	}
	else{
		velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35)
	}
}

void calcularVelocidadeLado(int dist){
	if(dist > 35){
		velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35);
	}
	else{
		velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*dist);
	}
}

task Movimentacao (){
	//velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*40);
	while(true)
	{
		if(StatusMotor == Frente){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = 100;
			MotorEsquerdo = VelocidadeMax;
		}
		else if(StatusMotor == Direita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			//distancia = SensorValue[SonarDireitoFrente];
			calcularVelocidade(SensorValue[SonarDireitoFrente]);
			MotorEsquerdo =  velocidadeMotor;
		}
		else if(StatusMotor == Esquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			calcularVelocidade(SensorValue[SonarEsquerdoFrente]);
			MotorDireito =  velocidadeMotor;
		}
		else if(StatusMotor == DireitaParcial){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			calcularVelocidade(SensorValue[SonarDireitoFrente]);
			MotorEsquerdo =  velocidadeMotor;
		}
		else if(StatusMotor == EsquerdaParcial){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			calcularVelocidade(SensorValue[SonarEsquerdoFrente]);
			MotorDireito =  velocidadeMotor;
		}
		else if(StatusMotor == ProcurarDireita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			//velocidadeProcura = 1.2*velocidadeMotor;
			MotorEsquerdo = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35);
		}
		else if(StatusMotor == ProcurarEsquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			//velocidadeProcura = 1.2*velocidadeMotor;
			MotorDireito = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35);
		}
		else if(StatusMotor == EsquerdaNoTalo){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			calcularVelocidadeLado(SensorValue[SonarEsquerdo]);
			//velocidadeProcura = 1.2*velocidadeMotor;
			//MotorDireito = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*45)
			MotorDireito = velocidadeMotor*1.2;
		}
		else if(StatusMotor == DireitaNoTalo){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			calcularVelocidadeLado(SensorValue[SonarDireito]);
			//velocidadeProcura = 1.2*velocidadeMotor;
			MotorEsquerdo = velocidadeMotor*1.2;
		}
	}
}
