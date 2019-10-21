#define intervaloAmostragem 77*0.5
#define numSonares 3
#define freqAmostragem 26
#define N 12 //ORDEM DO FILTRO -> ( N ) AMOSTRAS

int somaAmostras = 0;
float filtroFIR[N] = {0.0132890365448496,	0.0254191652653905,	0.0579583212656355,	0.100575552426198,	0.139740188972564,	0.163017735525362,	0.163017735525362,	0.139740188972564,	0.100575552426198,	0.0579583212656355,	0.0254191652653905,	0.0132890365448496};

void FiltrarSensor(int Sensor, bool Simulado){
	Tempo = time1[T1];
	intervaloAtual[Sensor] = Tempo - UltimaLeitura[Sensor];
	//print("%d\n",intervaloAtual[Sensor]);
	if(Sensor != Acelerometro && Simulado == false){
		NovoValor = SensorValue[Sensor];
	}
	if(intervaloAtual[Sensor] >= intervaloAmostragem){
		UltimaLeitura[Sensor] = Tempo;
		somaAmostras -= amostrasSensor[Sensor][0];
		somaAmostras += NovoValor;
		for(int i = 0; i < numAmostras-1; i++){
			amostrasSensor[Sensor][i] = amostrasSensor[Sensor][i+1];
			//print("%d ",amostrasSensor[Sensor][i]);
		}
		amostrasSensor[Sensor][numAmostras-1] = NovoValor;
		//print("%d\n", amostrasSensor[Sensor][numAmostras-1]);
		//amostrasSensor[Sensor][numAmostras-1] = (NovoValor + amostrasSensor[Sensor][numAmostras-2])*0.5;
		ValorSensor[Sensor] = 0;

		for (int j = 0;j<N;j++)
		{
		ValorSensor[Sensor] += (amostrasSensor[Sensor][j]*filtroFIR[j]);
		}

		//ValorSensor[Sensor] = amostrasSensor[Sensor][numAmostras-1];
		if(Sensor == SonarCentro){
			print("%f, %d\n",ValorSensor[Sensor], NovoValor);
		}
		if(Tempo >= 30000){
			for(int i = 0; i < NumSensores; i++){
				UltimaLeitura[i] = UltimaLeitura[i] - 30000;
			}
			ClearTimer(T1);
		}
	}
}
