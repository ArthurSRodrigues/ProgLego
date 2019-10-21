task Monitoramento(){
	while(true){
		if(EnviarSensores == true){
			while(true){
				sendMessageWithParm(Display1, ValorSensor[SonarEsquerdo], ValorSensor[SonarCentro]);
				wait10Msec(10);
				sendMessageWithParm(Display2, ValorSensor[SonarDireito], StatusSonar);
				wait10Msec(10);
			}
		}
	}
}
