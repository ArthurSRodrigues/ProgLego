#define intervaloAmostragem 77
#define numSonares 3
#define freqAmostragem 26

int somaAmostras = 0;
float filtroFIR[3] = {0.0462 ,   0.9076 ,   0.0462};
float variacaoSensor[NumSensores];

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
			print("%d ",amostrasSensor[Sensor][i]);
		}
		amostrasSensor[Sensor][numAmostras-1] = NovoValor;
		print("%d\n", amostrasSensor[Sensor][numAmostras-1]);
		ValorSensor[Sensor] = amostrasSensor[Sensor][0]*filtroFIR[0] + amostrasSensor[Sensor][1]*filtroFIR[1] + amostrasSensor[Sensor][2]*filtroFIR[2];
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
