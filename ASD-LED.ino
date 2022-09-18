#include <Adafruit_NeoPixel.h>
#include <string.h>
#include <stdbool.h>

#define PIN 13                     // Neopixel Pin
#define NUMPIXELS 30             // Number of Neopixel

char cmd;
int brightness = 255;

int R = 255;
int G = 100;
int B = 18;
char data[6];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

    Serial.begin(9600);                 // Serial Communication Init (boadrate: 9600)
    strip.setBrightness(brightness);    // Set Brightness
    strip.begin();                      // Init Neopixel
    colorWipe(strip.Color(R, G, B));    // Set pixel initial Color
    strip.show();                       // Show Neopixel

}


void loop() {
    
    if(Serial.available()){
      for(int i=0; i<6; i++){
        if(Serial.available()){
          cmd = Serial.read();
        }
        data[i] = cmd;
        Serial.println(data[i]);
      }
      sscanf(data, "%02x%02x%02x", &R, &G, &B);
      colorWipe(strip.Color(R, G, B)); 
      delay(100);
        
        // char *ptr = strtok(cmd, ":");
        
        
        
        
    }
}



void colorWipe(uint32_t c){    //  Set All pixel one color

    for(uint16_t i=0; i<strip.numPixels(); i++){

        strip.setPixelColor(i,c);
        

    }
    strip.show();

}