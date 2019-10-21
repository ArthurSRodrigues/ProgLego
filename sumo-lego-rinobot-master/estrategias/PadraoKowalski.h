task EstrategiaPadrao(){
	UltimoLado = Esquerda;
	while(true){
		if(StatusSonar == Frente){
			StatusMotor = Frente;
		}
		else if(StatusSonar == Direita){
			//StatusMotor = Direita;
			StatusMotor = Frente;
		}
		else if(StatusSonar == Esquerda){
			//StatusMotor = Esquerda;
			StatusMotor = Frente;
		}
		else if(StatusSonar == DireitaParcial){
			//StatusMotor = DireitaParcial;
			StatusMotor = DireitaNoTalo;
		}
		else if(StatusSonar == EsquerdaParcial){
			//StatusMotor = EsquerdaParcial;
			StatusMotor = EsquerdaNoTalo;
		}
		else if(StatusSonar == ProcurarDireita){
			StatusMotor = ProcurarDireita;
		}
		else if(StatusSonar ==ProcurarEsquerda){
			StatusMotor = ProcurarEsquerda;
		}
		else if(StatusSonar == EsquerdaNoTalo){
			StatusMotor = EsquerdaNoTalo;
		}
		else if(StatusSonar == DireitaNoTalo){
			StatusMotor = DireitaNoTalo;
		}
	}
}

void iniciarEstrategia(){
StartTask(EstrategiaPadrao);
}

void configurarEstrategias(){
}
