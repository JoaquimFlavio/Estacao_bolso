void inicializacao(void){  
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Guarabots");
  lcd.setCursor(0,1);
  lcd.print("estacao de bolso");
   
  beepSimples(pinoBuzzer, temp_beep);
  
  //while(estado_Botao(pinobuttonEnter)!=0);

  beepSimples(pinoBuzzer, temp_beep);
  
  lcd.clear();
}

