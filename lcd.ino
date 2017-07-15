void timeDisplay(void) {
  static unsigned long auxIntervalo = 0;

  if (!estado_Botao(pinobuttonUp) || !estado_Botao(pinobuttonDown) || !estado_Botao(pinobuttonEnter)) {
    auxIntervalo = millis();
    estado_Led(pinoLedDisplay, true);
    lcd.display();
  }else{
    if ((millis() - auxIntervalo) >= intervalo_lcd) {
      estado_Led(pinoLedDisplay, false);
      lcd.noDisplay();
    }
  }

  if ((millis() - auxIntervalo) >= 20000) {
    auxIntervalo = millis();
  }
}
//--------------------------------------------------------------------------------------------------------------------------------

int Sistema_UP_or_Down(){
  static bool t_butA = false, t_butD = false;
  
  if(!estado_Botao(pinobuttonUp))   t_butA = true;
  if(!estado_Botao(pinobuttonDown)) t_butD = true;

  if(estado_Botao(pinobuttonUp) && t_butA == true && t_butD == false){
     CONTRASTE--;
     controleContraste();
     t_butA = false; 
     lcd.clear();
  }
  if(estado_Botao(pinobuttonDown) && t_butA == false && t_butD == true){
     CONTRASTE++;
     controleContraste();
     t_butD = false;
     lcd.clear();
  }

  if(CONTRASTE <= 0)
    CONTRASTE = 0;
  else if(CONTRASTE >= 10)
    CONTRASTE = 10;
}

//--------------------------------------------------------------------------------------------------------------------------------
void controleContraste(){
  analogWrite(pinoContrasteDisplay, map(CONTRASTE, 0, 10, 0, 255));
}
