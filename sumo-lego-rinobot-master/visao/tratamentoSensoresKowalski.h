#define Perto 120
#define Longe 200

task TratarSensores(){
	while(true){
		if((ValorSensor[SonarEsquerdo] < ValorSensor[SonarDireito]) ||(ValorSensor[SonarEsquerdoFrente] < ValorSensor[SonarDireitoFrente]) ){
			UltimoLado = Esquerda;
		}
		else if((ValorSensor[SonarDireito] < ValorSensor[SonarEsquerdo]) ||(ValorSensor[SonarDireitoFrente] < ValorSensor[SonarEsquerdoFrente]) ){
			UltimoLado = Direita;
		}
		if(ValorSensor[SonarDireitoFrente] < Perto){
			if(ValorSensor[SonarEsquerdoFrente] < Perto){
				StatusSonar = Frente;
			}
			else if(ValorSensor[SonarEsquerdoFrente] > Longe){
				if(ValorSensor[SonarEsquerdo] < Perto){
				}
				else if(ValorSensor[SonarEsquerdo] > Longe){
					if(ValorSensor[SonarDireito] < Perto){
						StatusSonar = DireitaParcial;
					}
					else if(ValorSensor[SonarDireito] > Longe){
						StatusSonar = Direita;
					}
				}
			}
		}
		else if(ValorSensor[SonarDireitoFrente] > Longe){
			if(ValorSensor[SonarEsquerdoFrente] < Perto){
				if(ValorSensor[SonarDireito] < Perto){
				}
				else if(ValorSensor[SonarDireito] > Longe){
					if(ValorSensor[SonarEsquerdo] < Perto){
						StatusSonar = EsquerdaParcial;
					}
					else if(ValorSensor[SonarEsquerdo] > Longe){
						StatusSonar = Esquerda;
					}
				}
			}
			else if(ValorSensor[SonarEsquerdoFrente] > Longe){
				if(ValorSensor[SonarEsquerdo] < Perto){
					if(ValorSensor[SonarDireito] < Perto){
					}
					else if(ValorSensor[SonarDireito] > Longe){
						StatusSonar = EsquerdaNoTalo;
					}
				}
				else if(ValorSensor[SonarEsquerdo] > Longe){
					if(ValorSensor[SonarDireito] < Perto){
						StatusSonar = DireitaNoTalo;
					}
					else if(ValorSensor[SonarDireito] > Longe){
						if(UltimoLado == Direita){
							StatusSonar = ProcurarDireita;
						}
						else if(UltimoLado == Esquerda){
							StatusSonar = ProcurarEsquerda;
						}
					}
				}
			}
		}
	}
}
