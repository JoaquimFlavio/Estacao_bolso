void iniciaSD(void) {
  #if Activation_serial == 1
    Serial.print("Inicializa o SD card...");
  #endif
  if (!SD.begin(pinoCS)) {
    #if Activation_serial == 1
      Serial.println("Nao inicializado. Veja no texto adiante sobre isso.");
    #endif
    return;
  }
  #if Activation_serial == 1
    Serial.println("Beleza! Seguindo...");
  #endif
}
//-------------------------------------------------------------------

void set_in_file(uint8_t opc, int value){
  SD.remove(opc == 0 ? fileContraste : fileBrilho);
  myFile = SD.open(opc == 0 ? fileContraste : fileBrilho, FILE_WRITE);
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    myFile.println(value);
    myFile.close();// Terminou de escrever, fecha-se o arquivo:
    #if Activation_serial == 1
      Serial.println("Ok!!! Contraste");
    #endif
  }
  #if Activation_serial == 1
    else{Serial.println("Error!!! Contraste");}
  #endif
}

int get_in_file(uint8_t opc){
  char h[3];
  i = 0;
  myFile = SD.open(opc == 0 ? fileContraste : fileBrilho);
  if (myFile) {
    // Le todo o arquivo...
    while (myFile.available()) {
      h[i] = myFile.read();
      i++;
    }
    myFile.close();//Finalizado, fecha-se o arquivo
    #if Activation_serial == 1
      Serial.println("Ok!!! Brilho");
    #endif
  }
  #if Activation_serial == 1
    else{Serial.println("Error!!! Brilho");}
  #endif
  return atoi(h);
}

//Grava todos os dados__________________________________________________________________

void gravaDados(){
  myFile = SD.open(fileDados, FILE_WRITE);
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    myFile.print(sensorAr.readTemperature());
    myFile.print(';');
    myFile.print(sensorAr.readHumidity());
    myFile.print(';');
    myFile.print(leitura_SensorAgua(pinoSensorUmidadeSolo));
    myFile.print(';');
    myFile.print("\n");
    
    myFile.close();// Terminou de escrever, fecha-se o arquivo:
    #if Activation_serial == 1
      Serial.println("Ok!!! todos os dados");
    #endif
  }
  #if Activation_serial == 1
    else{Serial.println("Error!!! todos os dados");}
  #endif
}

