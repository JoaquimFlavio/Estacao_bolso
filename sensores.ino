void getValues(void) {
  static unsigned long int aux = 0;

  if ((millis() - aux) > 5000) {
    aux = millis();

    values[0] = sensorAr.leitura_temperatura();
    values[1] = sensorAr.leitura_umidade();
    values[2] = sensorSolo.leitura(pinoSensorUmidadeSolo);
  }
}
