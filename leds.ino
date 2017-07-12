bool ControleLed(int corLed) {
  if (!button.estado(pinobuttonEnter))   t_butEnter   = true;          //Botão Up pressionado? Seta flag
    
  while (t_butEnter ? 1 : 0) {
    if (button.estado(pinobuttonEnter) && t_butEnter) {                  //Botão Up solto e flag setada?
      t_butEnter = false;
      lcd.limpaTela();
      
      ledE = !ledE;
      digitalWrite(pinoLed_Vermelho, ledE ? HIGH : LOW);

      buz.beepSimples(pinoBuzzer, temp_beep);
      lcd.limpaTela();
    }
  }
  return ledE;
}

