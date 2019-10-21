#define IntervaloMaxSonar 78

void FiltrarSensor(int Sensor, bool Simulado){
	if(Sensor != Acelerometro && Simulado == false){
		NovoValor = SensorValue[Sensor];
	}
	Tempo = time1[T1];
	intervaloAtual[Sensor] = Tempo - UltimaLeitura[Sensor];
	if(intervaloAtual[Sensor] >= IntervaloMaxSonar || NovoValor != ValorAnterior[Sensor]){
		UltimaLeitura[Sensor] = Tempo;
		amostrasSensor[Sensor][2] = amostrasSensor[Sensor][1];
		amostrasSensor[Sensor][1] = amostrasSensor[Sensor][0];
		amostrasSensor[Sensor][0] = NovoValor;
		amostrasSensor[Sensor][0] = (amostrasSensor[Sensor][0] + amostrasSensor[Sensor][1])/2;
		ValorSensor[Sensor] = (amostrasSensor[Sensor][0] + amostrasSensor[Sensor][1] + amostrasSensor[Sensor][2])/3;
		if(Sensor == SonarDireito){
			//writeDebugStream(" %d %d\n ",ValorSensor[SonarEsquerdo],ValorSensor[SonarDireito]);
		}
		if(Tempo >= 30000){
			for(int i = 0; i < NumSensores; i++){
				UltimaLeitura[i] = UltimaLeitura[i] - 30000;
			}
			ClearTimer(T1);
		}
		ValorAnterior[Sensor] = NovoValor;
	}
}
