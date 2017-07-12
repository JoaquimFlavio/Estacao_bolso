void timeDisplay(void) {
  static unsigned long auxIntervalo = 0;

  if (!button.estado(pinobuttonUp) || !button.estado(pinobuttonDown) || !button.estado(pinobuttonEnter)) {
    auxIntervalo = millis();
    digitalWrite(pinoLedDisplay, HIGH);
    lcd.estadoLigado();
  }else{
    if ((millis() - auxIntervalo) >= intervalo_lcd) {
      digitalWrite(pinoLedDisplay, LOW);
      lcd.estadoDesligado();
    }
  }

  if ((millis() - auxIntervalo) >= 20000) {
    auxIntervalo = millis();
  }
}

int contraste(void) {
  static bool t_butA = false, t_butD = false;
  
  if(!button.estado(pinobuttonUp))   t_butA = true;
  if(!button.estado(pinobuttonDown)) t_butD = true;

  if(button.estado(pinobuttonUp) && t_butA == true && t_butD == false){
     CONTRASTE--; 
     lcd.limpaTela();
     controleContraste(CONTRASTE);
     t_butA = false;
  }
  if(button.estado(pinobuttonDown) && t_butA == false && t_butD == true){
     CONTRASTE++;
     lcd.limpaTela();
     controleContraste(CONTRASTE);
     t_butD = false;
  }

  if(CONTRASTE <= 0)
    CONTRASTE = 0;
  else if(CONTRASTE >= 10)
    CONTRASTE = 10;
}

int brilho(void) {
  static bool t_butA = false, t_butD = false;
  
  if(!button.estado(pinobuttonUp))   t_butA = true;
  if(!button.estado(pinobuttonDown)) t_butD = true;

  if(button.estado(pinobuttonUp) && t_butA == true && t_butD == false){
     BRILHO--; 
     lcd.limpaTela();
     controleBrilho(BRILHO);
     t_butA = false;
  }
  if(button.estado(pinobuttonDown) && t_butA == false && t_butD == true){
     BRILHO++;
     lcd.limpaTela();
     controleBrilho(BRILHO);
     t_butD = false;
  }
  
  if(BRILHO <= 0)
    BRILHO = 0;
  else if(BRILHO >= 10)
    BRILHO = 10;
}
//-------------------------------------------------------------------
void controleContraste(int contraste){
  analogWrite(pinoLedDisplay, map(contraste, 0, 10, 0, 255));
}

void controleBrilho(int brilho){
  analogWrite(pinoLedDisplay, map(brilho, 0, 10, 0, 255));
}
