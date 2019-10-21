#define intervaloAmostragem 77*0.5
#define numSonares 3
#define freqAmostragem 26
#define N 6 //ORDEM DO FILTRO -> ( N ) AMOSTRAS

int somaAmostras = 0;
float filtroFIR[N] = { 0.0240172231708160,    0.137772476484704,    0.338210300344480,    0.338210300344480,    0.137772476484704,	0.0240172231708160};

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
		ValorSensor[Sensor] += amostrasSensor[Sensor][j]*filtroFIR[j];
		}

		//ValorSensor[Sensor] = amostrasSensor[Sensor][numAmostras-1];
		if(Sensor == SonarCentro){
			print("%d, %d\n",ValorSensor[Sensor], NovoValor);
		}
		if(Tempo >= 30000){
			for(int i = 0; i < NumSensores; i++){
				UltimaLeitura[i] = UltimaLeitura[i] - 30000;
			}
			ClearTimer(T1);
		}
	}
}
