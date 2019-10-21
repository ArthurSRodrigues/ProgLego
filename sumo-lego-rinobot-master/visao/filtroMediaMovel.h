#define numSonares 3
#define freqAmostragem 26

float intervaloAmostragem[4] = {77/2, 77/2, 77/2, 26/2};

void FiltrarSensor(int Sensor, bool Simulado){
	Tempo = time1[T1];
	intervaloAtual[Sensor] = Tempo - UltimaLeitura[Sensor];
	if(Sensor != Acelerometro && Simulado == false){
		NovoValor = SensorValue[Sensor];
	}
	if(intervaloAtual[Sensor] >= intervaloAmostragem){
		UltimaLeitura[Sensor] = Tempo;
		somaAmostras[Sensor] -= amostrasSensor[Sensor][0];
		somaAmostras[Sensor] += NovoValor;
		for(int i = 0; i < numAmostras-1; i++){
			amostrasSensor[Sensor][i] = amostrasSensor[Sensor][i+1];
			//print("%d ",amostrasSensor[Sensor][i]);
		}
		//amostrasSensor[Sensor][numAmostras-1] = (NovoValor + amostrasSensor[Sensor][numAmostras-2])*0.5;
		amostrasSensor[Sensor][numAmostras-1] = NovoValor;
		//print("%d\n", amostrasSensor[Sensor][numAmostras-1]);
		ValorSensor[Sensor] = (float)somaAmostras[Sensor]/numAmostras;
		//if(Sensor == SonarDireito){
		//	print("%f, %f, %f\n", ValorSensor[SonarEsquerdo],  NovoValor, ValorSensor[SonarDireito]);
		//	//print("%d %d %d\n",ValorSensor[SonarEsquerdo], ValorSensor[Sensor], ValorSensor[SonarDireito]);
		//}
	}
}
