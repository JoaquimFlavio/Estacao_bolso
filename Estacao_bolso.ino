#define funcao Hardware
#include <GuaraTeca.h>
#include <SPI.h>
#include <SD.h>

#define Activation_serial       0

//Definimos os pinos dos componentes da estação metereologica________________________
#define pinoDB7                 2
#define pinoDB6                 3//PWM
#define pinoDB5                 4
#define pinoDB4                 5//PWM
#define pinoLedDisplay          6//PWM
#define pinoBuzzer              7
#define pinoRS                  8
#define pinoEnable              9//PWM
#define pinoCS                  10//PWM
#define pinoMOSI                11//PWM
#define pinoMISO                12
#define pinoCLK                 13

#define pinobuttonUp            A0
#define pinobuttonEnter         A1
#define pinobuttonDown          A2
#define pinoSensorTempUmidadeAr A3
#define pinoSensorUmidadeSolo   A4
#define pinoContrasteDisplay    A5
#define pinoLed_Vermelho        A6


//Definicao de constantes de controle do codigo_____________________________________
#define Colunas 16
#define Linhas  2
#define Quant_menus   7
#define intervalo_lcd 15000
#define temp_beep     150
#define fileContraste "CTRS.txt"
#define fileBrilho    "BRl.txt"

//Funcoes/Rotinas do codigo________________________________________________________
void inicializacao(void);
void timeDisplay  (void);
int contraste     (void);
int brilho        (void);
bool ControleLed  (int corLed);
void changeMenu   (void);
void dispMenu     (void);
void getValues    (void);

//Variaveis auxiliares_____________________________________________________________
char menu = 1;
bool t_butUp, t_butDown, t_butEnter, t_butBack;

int values[3];
unsigned long int values_m[3];
bool ledE = 0;

int CONTRASTE, BRILHO;

//Criamos os objetos do projeto____________________________________________________
Buzzer buz;
SensorDHT sensorAr(pinoSensorTempUmidadeAr);
SensorAgua sensorSolo;
Botao button;
TelaCristalLiquido lcd(pinoRS, pinoEnable, pinoDB4, pinoDB5, pinoDB6, pinoDB7);

File myFile;//Cria um ponteiro para arquivo

void setup() {
  #if Activation_serial == 1
    Serial.begin(9600);
  #endif
  
  buz.iniciaBuzzer(pinoBuzzer);
  sensorSolo.iniciaSensorAgua(pinoSensorUmidadeSolo);
  lcd.iniciaTelaCristalLiquido(Colunas, Linhas);
  button.iniciaBotao(pinobuttonUp);
  button.iniciaBotao(pinobuttonDown);
  button.iniciaBotao(pinobuttonEnter);
  pinMode(pinoLed_Vermelho, OUTPUT);
  pinMode(pinoLedDisplay, OUTPUT);
  
  pinMode(pinoCS, OUTPUT);//Configura saída para Chip Select

  t_butUp = t_butDown = t_butEnter = t_butBack = false;

  //iniciaSD();
  
  inicializacao();
}

void loop() {
  changeMenu();
  dispMenu();
  timeDisplay();
  #if Activation_serial == 1
    Serial.print("temperatura_AR: ");
    Serial.print(sensorAr.leitura_temperatura());
    Serial.print(" | umidade_AR: ");
    Serial.print(sensorAr.leitura_umidade());
    Serial.print(" | umidade_SOLO: ");
    Serial.print(sensorSolo.leitura(pinoSensorUmidadeSolo));
    Serial.print(" | Ctrst: ");
    Serial.println(contraste());
  #endif
}
