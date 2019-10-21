#define Perto 120
#define Longe 120

void ProcessarAcelerometro(){
	NovoValor = SensorValue[Acelerometro];
	if(NovoValor > 0 && NovoValor < 200){
		NovoValor = -NovoValor;
	}
	else if(NovoValor > 800 && NovoValor < 1000){
		NovoValor = -(NovoValor - 1000);
	}
	FiltrarSensor(Acelerometro, false);
}

task TratarSensores(){
	while(true){
		if(ValorSensor[SonarEsquerdo] < Perto && ValorSensor[SonarEsquerdo] < ValorSensor[SonarDireito]){
			UltimoLado = Esquerda;
		}
		else if(ValorSensor[SonarDireito] < Perto && ValorSensor[SonarDireito] < ValorSensor[SonarEsquerdo]){
			UltimoLado = Direita;
		}
		if(ValorSensor[SonarCentro] < Perto){
			if(ValorSensor[SonarDireito] < Perto){
				if(ValorSensor[SonarEsquerdo] < Perto){
					StatusSonar = Frente;
				}
				else if(ValorSensor[SonarEsquerdo] > Longe){
					if(ValorSensor[SonarDireito] < ValorSensor[SonarCentro]){
						StatusSonar = Direita;
					}
					else if(ValorSensor[SonarCentro] < ValorSensor[SonarDireito]){
						StatusSonar = Frente;
					}
				}
			}
			else if(ValorSensor[SonarDireito] > Longe){
				if(ValorSensor[SonarEsquerdo] < Perto){
					if(ValorSensor[SonarEsquerdo] < ValorSensor[SonarCentro]){
						StatusSonar = Esquerda;
					}
					else if(ValorSensor[SonarCentro] < ValorSensor[SonarEsquerdo]){
						StatusSonar = Frente;
					}
				}
				else if(ValorSensor[SonarEsquerdo] > Longe){
					StatusSonar = Frente;
				}
			}
		}
		else if(ValorSensor[SonarCentro] > Longe){
			if(ValorSensor[SonarEsquerdo] < Perto){
				if(ValorSensor[SonarDireito] < Perto){
					StatusSonar = Frente;
				}
				else if(ValorSensor[SonarDireito] > Longe){
					StatusSonar = EsquerdaParcial;
				}
			}
			else if(ValorSensor[SonarEsquerdo] > Longe){
				if(ValorSensor[SonarDireito] < Perto){
					StatusSonar = DireitaParcial;
				}
				else if(ValorSensor[SonarDireito] > Longe){
					if(UltimoLado == Esquerda){
						StatusSonar = ProcurarEsquerda;
					}
					else if(UltimoLado == Direita){
						StatusSonar = ProcurarDireita;
					}
				}
			}
		}
		if(Acelerometro > 10){
			Inclinacao = Direita;
		}
		else if(Acelerometro < -10){
			Inclinacao = Esquerda;
		}
	}
}
