#define MotorDireito motor[D]
#define MotorEsquerdo motor[E]

float precisaoAlta = 0.4;
float precisaoMedia = precisaoAlta*1.5;
float periodoAmostragem = 0.077;

float velocidadeMotor;
float velocidadeProcura;
int distancia;

task Movimentacao (){
	//velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*35);
	while(true)
	{
		if(StatusMotor == Frente){
			nSyncedMotors = synchNone;
			MotorEsquerdo = VelocidadeMax;
			MotorDireito = VelocidadeMax;
		}
		else if(StatusMotor == Direita){
			nSyncedMotors = synchNone;
			MotorEsquerdo = 0;
			MotorDireito = -VelocidadeMax;
		}
		else if(StatusMotor == Esquerda){
			nSyncedMotors = synchNone;
			MotorDireito = 0;
			MotorEsquerdo = -VelocidadeMax;
		}
		else if(StatusMotor == DireitaParcial){
			nSyncedMotors = synchNone;
			MotorEsquerdo = 0;
			MotorDireito = -VelocidadeMax;
		}
		else if(StatusMotor == EsquerdaParcial){
			nSyncedMotors = synchNone;
			MotorDireito = 0;
			MotorEsquerdo = -VelocidadeMax;
		}
		else if(StatusMotor == ProcurarDireita){
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*20);
			MotorEsquerdo = velocidadeMotor;
			//MotorDireito = -VelocidadeMax;
		}
		else if(StatusMotor == ProcurarEsquerda){
			nSyncedMotors = synchCB;
			nSyncedTurnRatio = -100;
			velocidadeMotor = kVelocidade*57.3*precisaoAlta/(periodoAmostragem*20);
			MotorDireito = velocidadeMotor;
			//MotorEsquerdo = -VelocidadeMax;
		}
	}
}
