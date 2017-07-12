void iniciaSD() {
  #if Activation_serial == 1
    Serial.print("Inicializa o SD card...");
  #endif
  if (!SD.begin(10)) {
    #if Activation_serial == 1
      Serial.println("Nao inicializado. Veja no texto adiante sobre isso.");
    #endif
    return;
  }
  #if Activation_serial == 1
    Serial.println("Beleza! Seguindo...");
  #endif
}
//------------------------------------------------------------------------------
void setContraste(int contraste) {
  SD.remove(fileContraste);
  myFile = SD.open(fileContraste, FILE_WRITE);
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    myFile.println(contraste);
    myFile.close();// Terminou de escrever, fecha-se o arquivo:
  }
}
int getContraste() {
  char h[3];int i = 0;
  myFile = SD.open(fileContraste);
  if (myFile) {
    // Le todo o arquivo...
    while (myFile.available()) {
      h[i] = myFile.read();
      i++;
    }
    myFile.close();//Finalizado, fecha-se o arquivo
  }
  return atoi(h);
}
void setBrilho(int brilho) {
  myFile = SD.open(fileBrilho, FILE_WRITE);
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    myFile.println(brilho);
    myFile.close();// Terminou de escrever, fecha-se o arquivo:
  }
}
int getBrilho() {
  char h[3];int i = 0;
  myFile = SD.open(fileBrilho);
  if (myFile) {
    // Le todo o arquivo...
    while (myFile.available()) {
      h[i] = myFile.read();
      i++;
    }
    myFile.close();//Finalizado, fecha-se o arquivo
  }
  return atoi(h);
}







































/*void configSD(void) {
  if (!SD.begin(10)) {//Testa se o cartão inicializa com sucesso
    Serial.println("Falha no cartao!");
    return;//retorna
  } else {
    Serial.println("Sucesso na inicializacao!");
  }

  myFile = SD.open(nomeTXT, FILE_WRITE);//Abre arquivo para escrita

  if (myFile) { //Arquivo aberto com sucesso?
    Serial.print("Escrevendo em arquivo...");//Escreve no arquivo
    myFile.println("hello SD Card Shield!");//Teste de escrita

    myFile.close();
    Serial.println("Escrita finalizada");
  }
  else {
    Serial.println("Erro ao abrir arquivo");
  }

  myFile = SD.open(nomeTXT);//Abre novamente o arquivo para leitura

  if (myFile) {//Arquivo aberto com sucesso?
    Serial.println(nomeTXT);
    while (myFile.available()) {//Avalia leitura
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else {
    Serial.println("Erro ao abrir arquivo");
  }
  }*/




