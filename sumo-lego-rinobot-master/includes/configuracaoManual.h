#define BotaoDireito 1
#define BotaoEsquerdo 2
#define BotaoLaranja 3

#define Botoes 1
#define Display1 2
#define Display2 3

bool SensorToque = false;
short ladoInicial = -1;

void EnviarBotao(int Botao, int Posicao){
	//sendMessageWithParm(Botoes, Botao, 0);
	print("%d\n",Botao);
	//nVolume = 4;
	if(Botao == BotaoLaranja){
		PlaySound(soundFastUpwardTones);
	}
	else{
		//for(int i = -1; i < Posicao; i++){
		PlaySound(soundShortBlip);
		//wait1Msec(200);
	}
	//wait10Msec(5);
}
//}

void FuncaoEsperar(){
	ClearTimer(T4);
	int Segundos = 0;
	int Decimos = 0;
	while(time1[T4] < 5000){
		Segundos = time100[T4]/10;
		Decimos = time100[T4] - Segundos*10;
		nxtDisplayCenteredBigTextLine( 0, "#GoRino");
		nxtDisplayCenteredTextLine(2, "%d,%d", Segundos, Decimos);
		wait10Msec(10);
	}
	eraseDisplay();
}

void PressioneStart(){
	nxtDisplayCenteredBigTextLine(0, "#GoRino");
	nxtDisplayCenteredTextLine(4, "Pressione");
	nxtDisplayCenteredBigTextLine(5, "[START]");
	while(nNxtButtonPressed != BotaoLaranja){
		if(nNxtButtonPressed == BotaoEsquerdo){
			ladoInicial = Esquerda;
			nxtDisplayCenteredTextLine(7, "Esquerda");
		}
		else if(nNxtButtonPressed == BotaoDireito){
			ladoInicial = Direita;
			nxtDisplayCenteredTextLine(7, "Direita");
		}
	}
	EnviarBotao(BotaoLaranja, false);
	eraseDisplay();
}

int GerarMenu(int TipoMenu, int NumOpcoes){
	bool PrimeiraVez = true;
	int Botao = -1;
	int Posicao = 0;
	bool ColocarSeta = 0;
	bool PularLinha = false;
	int ajusteLinha = 4;
	if(TipoMenu == movInicial){
		ajusteLinha = 0;
	}
	if(NumOpcoes == 2){
		PularLinha = true;
	}
	while(true){
		Botao = nNxtButtonPressed;
		if(Botao != -1 || PrimeiraVez == true || SensorToque == true){
			PrimeiraVez = false;
			if(Botao == BotaoLaranja || SensorToque == true){
				while(nNxtButtonPressed != -1){};
				while(SensorToque != false){};
				eraseDisplay();
				EnviarBotao(Botao, Posicao);
				while(nNxtButtonPressed != -1){};
				while(SensorToque != false){};
				return Posicao;
			}
			else if(Botao == BotaoDireito){
				Posicao++;
				if(Posicao >= NumOpcoes){
					Posicao = 0;
				}
				EnviarBotao(Botao, Posicao);
			}
			else if(Botao == BotaoEsquerdo){
				Posicao--;
				if(Posicao < 0){
					Posicao = NumOpcoes - 1;
				}
				EnviarBotao(Botao, Posicao);
			}
			eraseDisplay();
			if(TipoMenu != movInicial){
				nxtDisplayCenteredBigTextLine(0, "#GoRino");
				nxtDisplayTextLine(3, "%s:", Menus[TipoMenu][0]);
			}
			for(int Linha = 0; Linha < NumOpcoes; Linha++){
				if(Posicao == Linha){
					ColocarSeta = true;
				}
				else{
					ColocarSeta = false;
				}
				nxtDisplayTextLine(Linha + ajusteLinha + PularLinha, "%s%s", ConfigMenu[ColocarSeta], Menus[TipoMenu][Linha + 1]);
			}
			while(nNxtButtonPressed != -1){};
		}
	}
}
