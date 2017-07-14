#include <GuaraTeca_Hardware.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

#define Activation_serial       0

//Definimos os pinos dos componentes da estação metereologica________________________
#define pinoDB7                 2
#define pinoDB6                 3//PWM
#define pinoDB5                 4
#define pinoLedDisplay          5//PWM
#define pinoContrasteDisplay    6//PWM
#define pinoBuzzer              7
#define pinoRS                  8
#define pinoEnable              9//PWM
#define pinoCS                  10//PWM
#define pinoMOSI                11//PWM
#define pinoMISO                12
#define pinoCLK                 13

#define pinobuttonDown          A0
#define pinobuttonUp            A1
#define pinobuttonEnter         A2
#define pinoSensorTempUmidadeAr A3
#define pinoSensorUmidadeSolo   A4
#define pinoDB4                 A5

//Definicao de constantes de controle do codigo_____________________________________
#define Quant_menus   6
#define intervalo_lcd 15000
#define temp_beep     150
#define fileContraste "CTRS.txt"
#define fileBrilho    "BRl.txt"
#define fileDados     "DATA.txt"

//Funcoes/Rotinas do codigo________________________________________________________
int Sistema_UP_or_Down(int varContol, char control);
void set_in_file(uint8_t opc, int value);
void controleContraste(int contraste);
void controleBrilho(int brilho);
int get_in_file(uint8_t opc);
void inicializacao(void);
void timeDisplay(void);
void changeMenu(void);
void iniciaSD(void);
void dispMenu(void);

//Variaveis auxiliares_____________________________________________________________
bool t_butUp, t_butDown, t_butEnter, t_butBack;
uint8_t CONTRASTE, BRILHO;
uint8_t menu = 1;
int i;

//Criamos os objetos do projeto____________________________________________________
LiquidCrystal lcd(pinoRS, pinoEnable, pinoDB4, pinoDB5, pinoDB6, pinoDB7);
File myFile;//Cria um ponteiro para arquivo
DHT sensorAr(pinoSensorTempUmidadeAr, DHT11);

byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};

void setup() {
  #if Activation_serial == 1
    Serial.begin(9600);
  #endif

  //Inicializamos o hardware__________________________________________
  lcd.createChar(0, grau);
  lcd.begin(16, 2);
  inicia_SensorAgua(pinoSensorUmidadeSolo);
  inicia_Buzzer(pinoBuzzer);
  inicia_Botao(pinobuttonUp);
  inicia_Botao(pinobuttonDown);
  inicia_Botao(pinobuttonEnter);
  inicia_Led(pinoLedDisplay);
  pinMode(pinoCS, OUTPUT);//Configura saída para Chip Select
  iniciaSD();

  //Configuraçoes iniciais_________________________________________
  t_butUp = t_butDown = t_butEnter = t_butBack = false;

  CONTRASTE = get_in_file(0);
  BRILHO = get_in_file(1);

  controleContraste(CONTRASTE);
  controleBrilho(BRILHO);

  if(!SD.exists(fileDados)){
    myFile = SD.open(fileDados, FILE_WRITE);
    //Se o arquivo foi aberto com sucesso, escreve nele
    if (myFile) {
      myFile.print("Temperatura_AR (°C)");
      myFile.print(';');
      myFile.print("Humidade_AR (%)");
      myFile.print(';');
      myFile.print("Humidade_Solo (%)");
      myFile.print(';');
      myFile.print("\n");
      
      myFile.close();// Terminou de escrever, fecha-se o arquivo:
      #if Activation_serial == 1
        Serial.println("Ok!!! init todos os dados");
      #endif
    }
    #if Activation_serial == 1
      else{Serial.println("Error!!! init todos os dados");}
    #endif
  }
  
  inicializacao();//Função para fazer o processo visual de inicialização.
}

void loop() {
  changeMenu();
  timeDisplay();
  dispMenu();
  //controleContraste(CONTRASTE);
  //controleBrilho(BRILHO);
  #if Activation_serial == 1
    Serial.print("temperatura_AR: ");
    Serial.print(sensorAr.leitura_temperatura());
    Serial.print(" | umidade_AR: ");
    Serial.print(sensorAr.leitura_umidade());
    Serial.print(" | umidade_SOLO: ");
    Serial.println(sensorSolo.leitura(pinoSensorUmidadeSolo));
  #endif
}
