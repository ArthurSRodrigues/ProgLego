#define VelocidadeMax 100
#define velocidadeLenta 20
#define velocidadeMedia 30

#define MotorDireito motor[D]
#define MotorEsquerdo motor[E]
#define MotorCentro motor[A]

float velocidade;
float precisaoAlta = 0.6, precisaoBaixa = precisaoAlta*1.2;
float periodoAmostragem = 0.077;
int distancia;

void fazerCurva(int turnRatio, int lado){
	if(lado == Direita){
		nSyncedMotors = synchBC;
		nSyncedTurnRatio = turnRatio;
		MotorEsquerdo = VelocidadeMax;
		MotorCentro = 0.5*turnRatio + 50;
	}
	else if(lado == Esquerda){
		nSyncedMotors = synchCB;
		nSyncedTurnRatio = turnRatio;
		MotorDireito = VelocidadeMax;
		MotorCentro = 0.5*turnRatio + 50;
	}
}

task Movimentacao (){
	velocidade = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35);
	while(true){
		if(StatusMotor == Frente){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = 100;
			if(SensorValue[SonarCentro] < 25){
				MotorEsquerdo = VelocidadeMax;
				MotorCentro = VelocidadeMax;
			}
			else{
				MotorEsquerdo = VelocidadeMax*0.7;
				MotorCentro = VelocidadeMax*0.7;
			}
		}
		else if(StatusMotor == Direita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			distancia = ValorSensor[SonarDireito];
			if(distancia < 60){
				velocidade = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				//print("Velocidade = %f, Distancia = %d\n",velocidade, distancia);
			}
			MotorEsquerdo =  velocidade;
			MotorCentro = 0;
		}
		else if(StatusMotor == Esquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			distancia = ValorSensor[SonarEsquerdo];
			if(distancia < 60){
				velocidade = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				//print("Velocidade = %f, Distancia = %d\n",velocidade, distancia);
			}
			MotorDireito =  velocidade;
			MotorCentro = 0;
		}
		else if(StatusMotor == DireitaParcial){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			distancia = ValorSensor[SonarDireito];
			if(distancia < 60){
				velocidade = kVelocidade*57.3*precisaoBaixa/(periodoAmostragem*distancia);
				//print("Velocidade = %f, Distancia = %d\n",velocidade, distancia);
			}
			MotorEsquerdo =  velocidade;
			MotorCentro = 0;
		}
		else if(StatusMotor == EsquerdaParcial){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			distancia = ValorSensor[SonarEsquerdo];
			if(distancia < 60){
				velocidade = kVelocidade*57.3*precisaoBaixa/(periodoAmostragem*distancia);
				//print("Velocidade = %f, Distancia = %d\n",velocidade, distancia);
			}
			MotorDireito =  velocidade;
			MotorCentro = 0;
		}
		else if(StatusMotor == ProcurarDireita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			MotorEsquerdo =  velocidade*1.5;
			MotorCentro = 0;
		}
		else if(StatusMotor == ProcurarEsquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			MotorDireito = velocidade*1.5;
			MotorCentro = 0;
		}
		else if(StatusMotor == ParaTras){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = 100;
			MotorEsquerdo = -VelocidadeMax;
			MotorCentro = -VelocidadeMax;
		}
		else if(StatusMotor == Parado){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = 100;
			MotorEsquerdo = 0;
			MotorCentro = 0;
		}
	}
}

int encoder[3];
int velocidadeReal[3];
task velocidadeMotor(){
	encoder[0] = nMotorEncoder[motorA];
	encoder[1] = nMotorEncoder[motorB];
	encoder[2] = nMotorEncoder[motorC];
	wait1Msec(100);
	velocidadeReal[0] = (nMotorEncoder[motorA] - encoder[0])*10;
	velocidadeReal[1] = (nMotorEncoder[motorB] - encoder[1])*10;
	velocidadeReal[2] = (nMotorEncoder[motorC] - encoder[2])*10;
	print("velocidade = %d\n", velocidadeReal[0]);
}
