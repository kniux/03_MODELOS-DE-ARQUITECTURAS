/*
 * Name: SET ONE LED RGB CLASSIC
 * created: 24/08/2021
 * Author: Edgar Cano
 * Ver: 1.0
 * Rev: 18/04/2024
 */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//--- RGB&Buzzer PINS----------------------------------------------------------------------------------
int redPin = 22;      //Define el pin del arduino en que estará conectado el pin del led RGB rojo.
int greenPin = 23;    //Define el pin del arduino en que estará conectado el pin del led RGB verde.
int bluePin = 24;     //Define el pin del arduino en que estará conectado el pin  del led RGB azul.
int ledPin = 13;     //Define el pin del led del arduino.

//---------------------DEFINIENDO BOTONES --------------------------------------------------------------
#define BTN_MENU  0
#define BTN_UP    1
#define BTN_DOWN  2
#define BTN_EXIT  3

// Este arreglo contiene los pines utilizados para los botones
uint8_t button[4] = {
  5,
  4,
  3,
  2
};

// Este arreglo contiene el último state conocido de cada línea
uint8_t button_state[4];

/********************************* Globales *********************************/
// state de nuestro autómata
#define S_HOME  0
#define S_SET_R 1
#define S_SET_G 2
#define S_SET_B 3
uint8_t state = S_HOME;

// Información de color RGB
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 
/*---------------------------------------------------------------------------------------------*/
/*                               Control_Subsystem
/*---------------------------------------------------------------------------------------------*/
void setup() {
  // Configurar como PULL-UP para ahorrar resistencias
  pinMode(button[BTN_MENU], INPUT_PULLUP);
  pinMode(button[BTN_EXIT], INPUT_PULLUP);
  pinMode(button[BTN_UP], INPUT_PULLUP);
  pinMode(button[BTN_DOWN], INPUT_PULLUP);

  // Se asume que el state inicial es HIGH
  button_state[0] = HIGH;
  button_state[1] = HIGH;
  button_state[2] = HIGH;
  button_state[3] = HIGH;
  
  lcd.init();
  lcd.backlight();
  delay(500);

  LCD_screenHOME();  
  LCD_RGBcount();
}

// Facilita la detección de flancos de subidan en los pines
// monitoreados. Asume la existencia de un arreglo button
// con la asignación actual de pines y un arreglo button_state
// con los valores de línea
uint8_t Rising_edge(int btn) {
  uint8_t newValue = digitalRead(button[btn]);
  uint8_t result = button_state[btn]!=newValue && newValue == 1;
  button_state[btn] = newValue;
  return result;
}
void RGB_setColor() {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
/******************* DRAW_Management ****************************/
void LCD_screenHOME(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MENU[] Set RGB");
  LCD_RGBcount();
}
void LCD_screenRED(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set RED");
  LCD_RGBcount();
}
void LCD_screenGREEN(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set GREEN");
  LCD_RGBcount();
}
void LCD_screenBLUE(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set BLUE");
  LCD_RGBcount();
}
void LCD_RGBcount(){
  lcd.setCursor(0,1);
  lcd.print("RGB: "); 
  lcd.print(r, DEC);
  lcd.print(" ");
  lcd.print(g, DEC);
  lcd.print(" ");
  lcd.print(b, DEC);
}

// Máquina de estados
void loop() {
  switch(state) {
    case S_HOME: /*** INICIO state S_HOME ***/
      if(Rising_edge(BTN_MENU)) { // Transición BTN_MENU
        state = S_SET_R;
        LCD_screenRED();
        break;
      }
      break; /*** FIN state S_HOME ***/
    case S_SET_R: /*** INICIO state S_SET_R ***/
      if(Rising_edge(BTN_MENU)) { // Transición BTN_MENU
        state = S_SET_G;
        LCD_screenGREEN();
        break;
      }
      if(Rising_edge(BTN_EXIT)) { // Transición BTN_EXIT
        state = S_HOME;
        LCD_screenHOME();
        break;
      }
      if(Rising_edge(BTN_UP)) { // Transición BTN_UP
        if(r<255) {
          r++;
        } else {
          r = 0;
        }
        RGB_setColor();
        LCD_screenRED();
        break;
      }
      if(Rising_edge(BTN_DOWN)) { // Transición BTN_DWN
        if(r>0) {
          r--;
        } else {
          r = 255;
        }
        RGB_setColor();
        LCD_screenRED();
        break;
      }
      break; /*** FIN state S_SET_R ***/
    case S_SET_G: /*** INICIA state S_SET_G ***/
      if(Rising_edge(BTN_MENU)) { // Transición BTN_MENU
        state = S_SET_B;
        LCD_screenBLUE();
        break;
      }
      if(Rising_edge(BTN_EXIT)) { // Transición BTN_EXIT
        state = S_HOME;
        LCD_screenHOME();
        break;
      }
      if(Rising_edge(BTN_UP)) { // Transición BTN_UP
        if(g<255) {
          g++;
        } else {
          g = 0;
        }
        RGB_setColor();
        LCD_screenGREEN();
        break;
      }
      if(Rising_edge(BTN_DOWN)) {
        if(g>0) {
          g--;
        } else {
          g = 255;
        }
        RGB_setColor();
        LCD_screenGREEN();
        break;
      }
      break; /*** FIN state S_SET_R ***/
    case S_SET_B: /*** INICIA state S_SET_B ***/
      if(Rising_edge(BTN_MENU)) { // Transición BTN_MENU
        state = S_SET_R;
        LCD_screenRED();
        break;
      }
      if(Rising_edge(BTN_EXIT)) { // Transición BTN_EXIT
        state = S_HOME;
        LCD_screenHOME();
        break;
      }
      if(Rising_edge(BTN_UP)) { // Transición BTN_UP
        if(b<255) {
          b++;
        } else {
          b = 0;
        }
        RGB_setColor();
        LCD_screenBLUE();
        break;
      }
      if(Rising_edge(BTN_DOWN)) { // Transición BTN_DWN
        if(b>0) {
          b--;
        } else {
          b = 255;
        }
        RGB_setColor();
        LCD_screenBLUE();
        break;
      }
      break; /*** FIN state S_SET_R ***/
  };
}
