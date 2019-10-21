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

void iniciarEstrategia(){
	StartTask(EstrategiaPadrao);
}

void configurarEstrategias(){
}
