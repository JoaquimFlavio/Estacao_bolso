void timeDisplay(void) {
  static unsigned long auxIntervalo = 0;

  if (!estado_Botao(pinobuttonUp) || !estado_Botao(pinobuttonDown) || !estado_Botao(pinobuttonEnter)) {
    auxIntervalo = millis();
    digitalWrite(pinoLedDisplay, HIGH);
    lcd.display();
  }else{
    if ((millis() - auxIntervalo) >= intervalo_lcd) {
      digitalWrite(pinoLedDisplay, LOW);
      lcd.noDisplay();
    }
  }

  if ((millis() - auxIntervalo) >= 20000) {
    auxIntervalo = millis();
  }
}
//--------------------------------------------------------------------------------------------------------------------------------

int Sistema_UP_or_Down(int varContol, char control){
  static bool t_butA = false, t_butD = false;
  
  if(!estado_Botao(pinobuttonUp))   t_butA = true;
  if(!estado_Botao(pinobuttonDown)) t_butD = true;

  if(estado_Botao(pinobuttonUp) && t_butA == true && t_butD == false){
     varContol--; 
     lcd.clear();
     control == 'C' ? controleContraste(varContol) : controleBrilho(varContol);
     t_butA = false;
  }
  if(estado_Botao(pinobuttonDown) && t_butA == false && t_butD == true){
     varContol++;
     lcd.clear();
     control == 'C' ? controleContraste(varContol) : controleBrilho(varContol);
     t_butD = false;
  }

  if(varContol <= 0)
    varContol = 0;
  else if(varContol >= 10)
    varContol = 10;

    return varContol;
}

//--------------------------------------------------------------------------------------------------------------------------------
void controleContraste(int contraste){
  analogWrite(pinoContrasteDisplay, map(contraste, 0, 10, 0, 255));
}

void controleBrilho(int brilho){
  analogWrite(pinoLedDisplay, map(brilho, 0, 10, 0, 255));
}
