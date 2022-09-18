#include <Adafruit_NeoPixel.h>
#include <string.h>

#define PIN 13             // Neopixel Dignital Pin
#define NUMPIXELS 30       // Number of Neopixel

char cmd;
int brightness = 255;

int R = 255;   // default warm color
int G = 100;
int B = 18;

char data[6];  // char arr for recieved data

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // create strip object

void setup() {

    Serial.begin(9600);                 // Serial Communication Init (boadrate: 9600)
    strip.setBrightness(brightness);    // Set Brightness
    strip.begin();                      // Init Neopixel
    colorWipe(strip.Color(R, G, B));    // Set pixel initial Color
    strip.show();                       // Show Neopixel

}


void loop() {
    
    if(Serial.available()){              // check serial data is available
      for(int i=0; i<6; i++){            // recieve 6 dight hexdemical code
        if(Serial.available()){
          cmd = Serial.read();
        }
        data[i] = cmd;
      }
      sscanf(data, "%02x%02x%02x", &R, &G, &B);  // convert hex code to RGB code
      colorWipe(strip.Color(R, G, B));           // change color
      delay(100);   
    }
}



void colorWipe(uint32_t c){    //  Set All pixel one color

    for(uint16_t i=0; i<strip.numPixels(); i++){
        strip.setPixelColor(i,c);
    }
    strip.show();
}