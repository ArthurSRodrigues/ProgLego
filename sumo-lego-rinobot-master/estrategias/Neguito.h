#define EstPadrao 0
#define LevantarRampa 1
#define Viradinha 2
//#define Contornar 3

void configurarEstrategias(){
	Menus[Estrategias][0] = "Estrategia";
	Menus[Estrategias][1] = "Padrao";
	Menus[Estrategias][2] = "LevantarRampa";
	Menus[Estrategias][3] = "Viradinha";
	Menus[Estrategias][4] = "Nao tem";
}

//se fizer estrategias separadas (inicio do movimento e estrategia durante o movimento)
//da pra fazer duas etrategias MaoSensor diferentes
//se nao, criar dois menus igual foi criado para o negoney para escolher as estrategias antes e depois

task EstrategiaPadrao(){

	UltimoLado = Esquerda;
	while(true)
	{
		if(StatusSonar == Frente)
		{
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

task EstrategiaSoltarRampa()
{
	int indoPraFrente = 0;
	UltimoLado = Esquerda;
	ClearTimer(T2);
	while(true){
		if(StatusSonar == Frente){

			if(indoPraFrente == 0 && SensorValue[SonarCentro]<16)
			{
				ClearTimer(T2);
				indoPraFrente =1;
			}
			if(indoPraFrente==1 && time1[T2]>=5000)
			{
				StatusMotor=Frente;
				nMotorEncoder[A]=0;
				nMotorEncoderTarget[A]=90;
				ClearTimer(T3);
				motor[A]= 100;
				while(motor[A]!=runStateIdle && (600-time1[T3])>0 ){}
				motor[A]= -100;
				wait1Msec(200);
				motor[A]= -50;
				indoPraFrente=0;

			}
			else
			{
				StatusMotor=Frente;
			}
		}
		else if(StatusSonar == Direita){
			StatusMotor = Direita;
			indoPraFrente=0;
		}
		else if(StatusSonar == Esquerda){
			StatusMotor = Esquerda;
			indoPraFrente=0;
		}
		else if(StatusSonar == DireitaParcial){
			StatusMotor = DireitaParcial;
			indoPraFrente=0;
		}
		else if(StatusSonar == EsquerdaParcial){
			StatusMotor = EsquerdaParcial;
			indoPraFrente=0;
		}
		else if(StatusSonar == ProcurarDireita){
			StatusMotor = ProcurarDireita;
			indoPraFrente=0;
		}
		else if(StatusSonar ==ProcurarEsquerda){
			StatusMotor = ProcurarEsquerda;
			indoPraFrente=0;
		}
	}
}

void ViradinhaSt(){
	nSyncedMotors = synchBC;
	nMotorEncoder[E]=0;
	nMotorEncoderTarget[E] =(int)(kVelocidade*45);
	nSyncedTurnRatio = -100;
	MotorEsquerdo = VelocidadeMax;
	while(nMotorRunState[motorB] != runStateIdle)
	{
	}
	nSyncedMotors = synchCB;
	nMotorEncoder[D]=0;
	nMotorEncoderTarget[D] = (int)(kVelocidade*45);
	nSyncedTurnRatio = -100;
	MotorDireito = VelocidadeMax;
	while(nMotorRunState[motorC] != runStateIdle)
	{
	}
}

task EstrategiaViradinha()
{
	int indoPraFrente = 0;
	UltimoLado = Esquerda;
	while(true)
	{
		if(StatusSonar == Frente)
		{

			if( indoPraFrente == 0 && SensorValue[SonarCentro] < 25)
			{
				ClearTimer(T2);
				indoPraFrente=1;
			}

			if(indoPraFrente==1 && time1[T2]>=5000)
			{
				StopTask(Movimentacao);
				ViradinhaSt();
				StartTask(Movimentacao);
				indoPraFrente=0;
				wait1Msec(100);

			}
			else
			{
				StatusMotor=Frente;
			}
		}
		else if(StatusSonar == Direita)
		{
			StatusMotor = Direita;
			indoPraFrente = 0;
		}
		else if(StatusSonar == Esquerda){
			StatusMotor = Esquerda;
			indoPraFrente = 0;
		}
		else if(StatusSonar == DireitaParcial){
			StatusMotor = DireitaParcial;
			indoPraFrente = 0;
		}
		else if(StatusSonar == EsquerdaParcial){
			StatusMotor = EsquerdaParcial;
			indoPraFrente = 0;
		}
		else if(StatusSonar == ProcurarDireita){
			StatusMotor = ProcurarDireita;
			indoPraFrente = 0;
		}
		else if(StatusSonar ==ProcurarEsquerda){
			StatusMotor = ProcurarEsquerda;
			indoPraFrente = 0;
		}
	}
}

void iniciarEstrategia(){
	if(EstrategiaSelecionada == EstPadrao){
		StartTask(EstrategiaPadrao);
	}
	else if(EstrategiaSelecionada == LevantarRampa){
		StartTask(EstrategiaSoltarRampa);
	}
	else if(EstrategiaSelecionada == Viradinha){
		StartTask(EstrategiaViradinha);
	}
	//else if(EstrategiaSelecionada == Contornar){
	//	EstrategiaContornar();
	//}
}
