void inicializacao(void){
  for(int i=0; i<=255; i++){
    analogWrite(pinoLedDisplay, i);
  }
  
  CONTRASTE = 4;
  BRILHO = 5;
  controleContraste(CONTRASTE);
  
  lcd.limpaTela();
  lcd.posicaoCursor(3,0);
  lcd.print("Guarabots");
  lcd.posicaoCursor(0,1);
  lcd.print("estacao de bolso");
   
  buz.beepSimples(pinoBuzzer, temp_beep);
  
  while(button.estado(pinobuttonEnter) != 0);

  buz.beepSimples(pinoBuzzer, temp_beep);
  lcd.limpaTela();
}

