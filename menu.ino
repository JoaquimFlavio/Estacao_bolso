void changeMenu(void) {                                                   
  if (!estado_Botao(pinobuttonUp))   t_butUp   = true;          
  if (!estado_Botao(pinobuttonDown)) t_butDown = true;        

  if (estado_Botao(pinobuttonUp) && t_butUp) {                  
    t_butUp = false;                                                 
    menu++;                                                           
    if (menu > Quant_menus) menu = 1;                                           
    lcd.clear();
  } 
  
  if (estado_Botao(pinobuttonDown) && t_butDown) {             
    t_butDown = false;
    menu--;                                                            
    if (menu < 1) menu = Quant_menus;                                            
    lcd.clear();
  }
}

void dispMenu(void) {                                        
  switch (menu) {
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Temperatura");
      lcd.setCursor(2,1);
      lcd.print(sensorAr.readTemperature());
      lcd.write((byte)0);
    break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Umidade do ar");
      lcd.setCursor(2,1);
      lcd.print(sensorAr.readHumidity());
      lcd.print("%");
    break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("Umidade do solo");
      lcd.setCursor(2,1);
      lcd.print(leitura_SensorAgua(pinoSensorUmidadeSolo));
      lcd.print("%");
    break;
    case 4:
      static bool auxGravar = false;
      
      if(!estado_Botao(pinobuttonEnter)){
        while(!estado_Botao(pinobuttonEnter)){
          auxGravar = true;
        }
      }else{
        lcd.setCursor(0,0);
        lcd.print("Gravar dados");
      }
      if(!estado_Botao(pinobuttonEnter)){
          gravaDados();
          beepSimples(pinoBuzzer, temp_beep);
          while(!estado_Botao(pinobuttonEnter)){
            auxGravar = false;
          }
        }
        
    break;
    case 5:
      static bool auxContraste = false;
      
      if(!estado_Botao(pinobuttonEnter)){
        while(!estado_Botao(pinobuttonEnter)){
          auxContraste = true;
        }
      }

      lcd.setCursor(0,0);
      lcd.print("Contraste_______");
      lcd.setCursor(0,1);
      lcd.print(CONTRASTE);
      
      while(auxContraste){
        Sistema_UP_or_Down();
        lcd.setCursor(0,0);
        lcd.print("Contraste______|");
        lcd.setCursor(0,1);
        lcd.print(CONTRASTE);
        if(!estado_Botao(pinobuttonEnter)){
          set_in_file();
          while(!estado_Botao(pinobuttonEnter)){
            auxContraste = false;
          }
        }
      }
    break;
  }
}
