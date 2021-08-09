/*
   Project: Smart_Room_Controller
   Description: Smart Toy Box
   Author: Vanessa Benavidez
   Date: June 29-21
*/

#include <Adafruit_NeoPixel.h>
#include <colors.h>
#include <OneButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ethernet.h>
#include <mac.h>
#include <SPI.h>
#include <SPI.h>
#include <hue.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
const int PIXELPIN = 17;
const int PIXELCOUNT = 14;
const int BUTTONPIN = 23;
const int bri = 15;
int pixelOn = true;
int i;
bool buttonState;
bool stateChange;
OneButton button1(BUTTONPIN, false);

Adafruit_NeoPixel pixel(PIXELCOUNT, PIXELPIN, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
EthernetClient Wemoclient;
int wemoPort = 49153;
bool status;


void setup() {
  pixel.begin();
  pixel.show();
  button1.attachClick (click1);
  button1.attachDoubleClick (doubleclick1);
  Serial.begin(9600);
  buttonState = false;

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  pinMode (BUTTONPIN, INPUT);
  Ethernet.begin(mac);
  delay(200);          //ensure Serial Monitor is up and running
  //printIP();
  Serial.printf("LinkStatus: %i  \n", Ethernet.linkStatus());
}

void loop() {
  if (buttonState == true)
    for (i = 0; i < 14 ; i++) {
      pixel.fill(0xFF0000, i, 14);
      //delay(100);
      pixel.setBrightness(bri);
      pixel.show();
    }
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("TIME TO CLEAN UP MAX "));
  display.clearDisplay();


  setHue(2, true, HueBlue, 255, 255);


}

void click1 () {
  buttonState = !buttonState;
  Serial.println ("Hi, my name is Vanessa single click");
}


void doubleclick1 () {
  stateChange = !stateChange;
  Serial.println ("Hi, my name is Vanessa double click");
}
