#define MotorDireito motor[D]
#define MotorEsquerdo motor[E]

float precisaoAlta = 0.4;
float precisaoMedia = precisaoAlta*1.5;
float periodoAmostragem = 0.077;

float velocidadeMotor;
int distancia;

task Movimentacao (){
	velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*40);
	while(true)
	{
		if(StatusMotor == Frente){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = 100;
			if(SensorValue[SonarCentro]<20)
			{
				MotorEsquerdo = VelocidadeMax;
			}
			else
			{
				MotorEsquerdo = VelocidadeMax*1;
			}
		}
		else if(StatusMotor == Direita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			distancia = SensorValue[SonarDireito];
			if(distancia< 60){
				if(distancia>30){
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				}
				else{
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*30);
				}

			}
			MotorEsquerdo =  velocidadeMotor;
		}
		else if(StatusMotor == Esquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			distancia = SensorValue[SonarEsquerdo];
			if(distancia< 60){
				if(distancia>30){
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				}
				else{
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*30);
				}
			}
			MotorDireito =  velocidadeMotor;
		}
		else if(StatusMotor == DireitaParcial){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			distancia = SensorValue[SonarDireito];
			if(distancia< 60){
				if(distancia>30){
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				}
				else{
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*30);
				}
			}
			MotorEsquerdo =  velocidadeMotor;
		}
		else if(StatusMotor == EsquerdaParcial){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			distancia = SensorValue[SonarEsquerdo];
			if(distancia< 60){
				if(distancia>30){
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*distancia);
				}
				else{
					velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*30);
				}
			}
			MotorDireito =  velocidadeMotor;
		}
		else if(StatusMotor == ProcurarDireita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			//velocidadeProcura = 1.2*velocidadeMotor;
			MotorEsquerdo = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*45);
		}
		else if(StatusMotor == ProcurarEsquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			//velocidadeProcura = 1.2*velocidadeMotor;
			MotorDireito = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*45);
		}
	}
}
