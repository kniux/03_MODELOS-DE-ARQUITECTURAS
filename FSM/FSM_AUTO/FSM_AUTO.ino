/*
 * Name: Weather Station
 * created: 24/08/2020
 * Author: Edgar Cano
 * Ver: 1.0
 * Rev: 18/04/2024
 */
#include <DHT.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPin  2
#define DHTType DHT11

/* Definiendo FSM*/
int currentState = 0;
#define nullState 0
#define state1    1  
#define state2    2
#define state3    3

/* Definiendo pantalla activa de datos*/
int displayWindow = 0;
#define lcdWelcome  0
#define lcdDateHour 1  
#define lcdDht11    2

int temp = 0;
int Hum = 0;
float tempDS = 0;

unsigned long previousMillisState1 = 0;
long intervalState1 = 500;     

unsigned long previousMillisState2 = 0;
long intervalState2 = 2000;     

unsigned long previousMillisState3 = 0;
long intervalState3 = 5000;     

LiquidCrystal_I2C lcd(0x27, 16, 2); 
RTC_DS3231 rtc;
DHT dht11(DHTPin, DHTType);

/*Control de tiempos de los estados ***************************************************************/
void TimeControlStates(){
   
 unsigned long currentMillis = millis();
 /* STATE 1 (Refresh Screen) - Cada 0.5 seg*/
  if (((currentMillis - previousMillisState1) >= intervalState1) && (currentState == nullState)){
    previousMillisState1 = currentMillis;
    currentState = state1; 
  }
 /* STATE 2 (Read Sensors) - Cada 2.0 seg*/
  if (((currentMillis - previousMillisState2) >= intervalState2) && (currentState == nullState)){
    previousMillisState2 = currentMillis;
    currentState = state2;
  }
 /* STATE 3 (Switching Screen) - Cada 5.0 seg*/ 
  if (((currentMillis - previousMillisState3) >= intervalState3) && (currentState == nullState)){
    previousMillisState3 = currentMillis;
    currentState = state3;
  }  
}
/*Máquina de estados********************************************************************************/
void MachineStates(){
  switch(currentState){
    case nullState:
    break;
    case state1:
      stateOne();
    break;
    case state2:
      stateTwo();
    break;
    case state3:
      stateThree();
    break;
    default:
    break;
  }
  // Regresando el estado actual al estado por defecto IDLE (nullstae)
  if(currentState !=  nullState) currentState =  nullState;
}
/* STATE 1 : Refrezca las pantallas cada 0.5seg*/
void stateOne(){
  switch(displayWindow){
    /*pantalla bienvenida (solo se visualiza la primera vez)*/
    case lcdWelcome:
      displayWelcome();
    break;
    /*pantalla Fecha y hora (el refrezco se nota al cambiar los seg)*/
    case lcdDateHour:
      displayDate();
      displayHour();
    break;
    /*pantalla temperatura y humedad (cambia si un parametro se actualiza dentro de 2 seg)*/
    case lcdDht11:
      displayDHT11();
    break;
    default:
    break;
  }
}
/* STATE 2 : Lee los sensores*/
void stateTwo(){
  temp = dht11.readTemperature();
  Hum = dht11.readHumidity();
  tempDS = rtc.getTemperature();
  /*temp del DS3231*/
}
/* STATE 3 : cambia y borra la pantalla según el estado actual*/
void stateThree(){
  switch(displayWindow){
    case lcdWelcome:
      cleanDisplay();
      displayWindow = lcdDateHour;
    break;
    case lcdDateHour:
      cleanDisplay();
      displayWindow = lcdDht11;
    break;
    case lcdDht11:
      cleanDisplay();
      displayWindow = lcdDateHour;
    break;
    default:
    break;
  }
}

/*PANTALLAS**********************************************************************/
void displayWelcome(){
  lcd.setCursor(2, 1);     
  lcd.print("WEATHER STATION");
  lcd.setCursor(7, 2);     
  lcd.print("TEST");  
}
void displayDate(){  
  DateTime now = rtc.now();
  char _bufferFecha[12];
  lcd.setCursor(0, 0);  
  formatoFecha(_bufferFecha, now.day(), now.month(), now.year() );
  lcd.print(_bufferFecha);
}
void displayHour(){
  DateTime now = rtc.now();
  char _bufferHora[10];
  lcd.setCursor(0, 1);  
  formatoHora( _bufferHora, now.hour(), now.minute(), now.second() );
  lcd.print(_bufferHora);
}
void formatoFecha(char bufferFecha[12], int numDia, int numMes, int numA){
  sprintf(bufferFecha, "%02d/%02d/%04d", numDia, numMes, numA);
}
void formatoHora(char bufferHora[10], int hora, int minu, int seg){
  sprintf(bufferHora, "%02d:%02d:%02d", hora, minu, seg);
}

void displayDHT11(){
    char symbol = 223;
    lcd.setCursor(0, 0);   
    lcd.print("DH:");    
    lcd.print(temp);
    lcd.print(symbol);    
    lcd.print(" DS:");
    lcd.print(tempDS);
    lcd.print(symbol);    
    lcd.setCursor(0, 1);  
    lcd.print("HUM: ");    
    lcd.print(Hum);
    lcd.print("%");
}
void cleanDisplay(){
   lcd.clear();
}
// subsystema principal
void setup() {
  Serial.begin(9600);
  dht11.begin();
  rtc.begin(); 
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  lcd.init();
  lcd.backlight();                  
  delay(500);
}
void loop() {
  TimeControlStates();
  MachineStates(); 
}
// END Code
