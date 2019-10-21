string Espaco[2];

void DarEspaco(float *ValorSensor, int Sensor, int aux){
	if(ValorSensor[Sensor] < 100){
		Espaco[aux] = " ";
	}
	else{
		Espaco[aux] = "";
	}
}

task AtualizarDisplay(){
	EnviarSensores = true;
	while(true){
		nxtDisplayCenteredBigTextLine(0, "#GoRino");
		nxtDisplayCenteredTextLine(3, "Status Sonar:");
		nxtDisplayCenteredTextLine(4, "%s", StatusDisplay[StatusSonar]);
		nxtDisplayCenteredTextLine(5, "Center");
		DarEspaco(ValorSensor, SonarEsquerdoFrente, 0);
		nxtDisplayTextLine(6, "Left %s%d,%d Right", Espaco[0], ValorSensor[SonarEsquerdoFrente], ValorSensor[SonarDireitoFrente]);
		DarEspaco(ValorSensor, SonarEsquerdo, 0);
		DarEspaco(ValorSensor, SonarDireito, 1);
		nxtDisplayTextLine(7, "%s%d          %s%d", Espaco[0], ValorSensor[SonarEsquerdo], Espaco[1],
		ValorSensor[SonarDireito]);
		wait10Msec(5);
	}
}
