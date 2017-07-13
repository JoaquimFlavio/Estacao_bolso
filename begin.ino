void inicializacao(void){
  /*for(i=0; i<=255; i++){
    analogWrite(pinoLedDisplay, i);
  }*/
  
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Guarabots");
  lcd.setCursor(0,1);
  lcd.print("estacao de bolso");
   
  digitalWrite(pinoBuzzer, HIGH);
  delay(150);
  digitalWrite(pinoBuzzer, LOW);
  
  while(estado_Botao(pinobuttonEnter) != 0);

  digitalWrite(pinoBuzzer, HIGH);
  delay(150);
  digitalWrite(pinoBuzzer, LOW);
  
  lcd.clear();
}

