#include "dht.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);// if your LCD does not display,change it to 0x27 or other address

#define dataPin 8 // Defines pin number to which the sensor is connected
#define RELAY1  33    // Relay - 1  [Humidity control]                  
#define RELAY2  34    // Relay - 2  [cloning - water pump]   
dht DHT; // Creats a DHT object
unsigned long time;

void setup()
{    


  lcd.init();                      // initialize the lcd
  lcd.clear();  // clear
  lcd.backlight();                 // turn ON display


  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT); 
  
  Serial.begin(9600);

  BIOS();
}

 

 void loop()
{
  HumidityControll();
  ClonigPump();
  
  delay(3000); // Delays 30 secods

}


void ClonigPump(){
  int counter = 0;
  unsigned long devider = 600000 ; // 30-mimutes 
  time = millis();
  counter = time/devider;

  Serial.print("Time:");
  Serial.println(time);
  
  if ((counter % 2) == 0)
  { 
    digitalWrite(RELAY2,LOW); 
    lcd.setCursor(0,1); // second line
    lcd.print("pumpClone: ");  
    lcd.print(time/1000/60);
    lcd.print("/");
    lcd.print(devider/60/1000);  

  }else{
    digitalWrite(RELAY2,HIGH);          // Turns Relay Off
    }    
    
}


void HumidityControll(){
  
    int readData = DHT.read22(dataPin); // Reads the data from the sensor
    float t = DHT.temperature; // Gets the values of the temperature
    float h = DHT.humidity; // Gets the values of the humidity
    
    // Printing the results on the serial monitor
    lcd.clear();
    lcd.setCursor(0,0); // first line
    lcd.print("Tmp:"); // print
    lcd.print(t); // print
    lcd.print(" H:"); // print
    lcd.print(h); // print
    if (h<50){
         digitalWrite(RELAY1,LOW);           // Turns ON Relays 1
  
      }
      else{
           digitalWrite(RELAY1,HIGH);          // Turns Relay Off
  
        }
}



void BIOS(){

  lcd.setCursor(0,0); // first line
  lcd.print("Hello World"); // print
  
  StartForFewSeconds(RELAY1);
  StartForFewSeconds(RELAY2);

  }

void StartForFewSeconds(int relay){
  
  digitalWrite(relay,LOW);           // Turns ON Relay
  delay(2000);
  digitalWrite(relay,HIGH);           // Turns OFF Relay
  }
 
