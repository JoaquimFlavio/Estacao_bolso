void changeMenu(void) {                                                   
  if (!button.estado(pinobuttonUp))   t_butUp   = true;          
  if (!button.estado(pinobuttonDown)) t_butDown = true;        

  if (button.estado(pinobuttonUp) && t_butUp) {                  
    t_butUp = false;                                                 
    menu++;                                                           
    if (menu > Quant_menus) menu = 1;                                           
    lcd.limpaTela();
  } 
  
  if (button.estado(pinobuttonDown) && t_butDown) {             
    t_butDown = false;
    menu--;                                                            
    if (menu < 1) menu = Quant_menus;                                            
    lcd.limpaTela();
  }
}

void dispMenu(void) {                                        
  switch (menu) {
    case 1:
      lcd.posicaoCursor(0,0);
      lcd.print("temperatura");
      lcd.posicaoCursor(2,1);
      //lcd.print(values[0]);
      lcd.print(sensorAr.leitura_temperatura());
    break;
    case 2:
      lcd.posicaoCursor(0,0);
      lcd.print("Umidade do ar");
      lcd.posicaoCursor(2,1);
      //lcd.print(values[1]);
      lcd.print(sensorAr.leitura_umidade());
      lcd.print("%");
    break;
    case 3:
      lcd.posicaoCursor(0,0);
      lcd.print("Umidade do solo");
      lcd.posicaoCursor(2,1);
      //lcd.print(values[2]);
      lcd.print(sensorSolo.leitura(pinoSensorUmidadeSolo));
      lcd.print("%");
    break;
    case 4:
      lcd.posicaoCursor(0,0);
      lcd.print("LED Vermelha____");
      lcd.posicaoCursor(0,1);
      lcd.print(ControleLed(0) ? "->ligado" : "->desligado");
    break;
    case 5:
      lcd.posicaoCursor(0,0);
      lcd.print("Gravar dados");
    break;
    case 6:
      static bool auxContraste = false;

      if(!button.estado(pinobuttonEnter)){
        while(!button.estado(pinobuttonEnter)){
          auxContraste = true;
        }
      }

      lcd.posicaoCursor(0,0);
      lcd.print("Contraste_______");
      lcd.posicaoCursor(0,1);
      lcd.print(CONTRASTE);
      
      while(auxContraste){
        contraste();
        lcd.posicaoCursor(0,0);
        lcd.print("Contraste______|");
        lcd.posicaoCursor(0,1);
        lcd.print(CONTRASTE);
        if(!button.estado(pinobuttonEnter)){
          while(!button.estado(pinobuttonEnter)){
            auxContraste = false;
          }
        }
      }
    break;
    case 7:
      static bool auxBrilho = false;

      if(!button.estado(pinobuttonEnter)){
        while(!button.estado(pinobuttonEnter)){
          auxBrilho = true;
        }
      }

      lcd.posicaoCursor(0,0);
      lcd.print("Brilho___________");
      lcd.posicaoCursor(0,1);
      lcd.print(BRILHO);
      
      while(auxBrilho){
        brilho();
        lcd.posicaoCursor(0,0);
        lcd.print("Brilho_________|");
        lcd.posicaoCursor(0,1);
        lcd.print(BRILHO);
        if(!button.estado(pinobuttonEnter)){
          while(!button.estado(pinobuttonEnter)){
            auxBrilho = false;
          }
        }
      }
    break;
  }
}
