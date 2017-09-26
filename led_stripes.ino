#include <MD_REncoder.h>
#include <Adafruit_NeoPixel.h>


// LED Stripes
#define STRIPE_PIN_1      5
#define STRIPE_PIN_2      6
#define STRIPE_PIN_3      7

// md encode
// Poti 1
#define CLK_1               0
#define DT_1                1

// Poti 2
#define CLK_2               2
#define DT_2                3

#define N_LEDS              20
 
Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_3, NEO_GRB + NEO_KHZ800);

// Potentiometer
// set up encoder object
MD_REncoder poti_1 = MD_REncoder(CLK_1, DT_1);
MD_REncoder poti_2 = MD_REncoder(CLK_2, DT_2);

int32_t f = 111;

void setup() {

  Serial.begin(57600);
  // put your setup code here, to run once:
//  strip_1.begin();
//  strip_2.begin();
//  strip_3.begin();
//  
//  // init
//  chase(strip_1.Color(255, 0, 0), strip_1); // Red
//  chase(strip_1.Color(0, 255, 0), strip_1); // Green
//  chase(strip_1.Color(0, 0, 255), strip_1); // Blue
//
//  chase(strip_2.Color(255, 0, 0), strip_2); // Red
//  chase(strip_2.Color(0, 255, 0), strip_2); // Green
//  chase(strip_2.Color(0, 0, 255), strip_2); // Blue
//  
//  chase(strip_3.Color(255, 0, 0), strip_3); // Red
//  chase(strip_3.Color(0, 255, 0), strip_3); // Green
//  chase(strip_3.Color(0, 0, 255), strip_3); // Blue

//  poti_1.begin();
//  poti_2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
//  shine_all(strip_2.Color(0, 255, 0));

// Encoder stuff
  uint8_t x_1 = poti_1.read();
 
//  if (x_1)
//  {
//    Serial.print(x_1 == DIR_CW ? "\n+1" : "\n-1");
////    if (x_1 == DIR_CW) {
////      ++f;
////      if (f > 255) {
////        f = 0;  
////      }
////    } else {
////      --f;
////      if (f < 0) {
////        f = 255;  
////      }  
////    }     
//  }
//
//  uint8_t x_2 = poti_2.read();
//  if (x_2)
//  {
//    Serial.print(x_2 == DIR_CW ? "\n+2" : "\n-2");
////    if (x_2 == DIR_CW) {
////      ++f;
////      if (f > 255) {
////        f = 0;  
////      }
////    } else {
////      --f;
////      if (f < 0) {
////        f = 255;  
////      }  
////    }     
//  }
  set_color(strip_2.Color(255, 0, 0), strip_1);
//  set_color(strip_2.Color(0, 255, 0), strip_2);
//  set_color(strip_2.Color(0, 0, 255), strip_3);
}

static void shine_all(uint32_t color) {
  for(uint16_t i=0; i < N_LEDS;++i) {
    strip_1.setPixelColor(i  , color);
    strip_2.setPixelColor(i  , color);
    strip_3.setPixelColor(i  , color);
    strip_1.show();
    strip_2.show();
    strip_3.show();
  }
}

static void set_color(uint32_t color, Adafruit_NeoPixel & strip) {
  for(uint16_t i=0; i < N_LEDS;++i) {
    strip.setPixelColor(i  , color);
    strip.show();
  }
}

static void chase(uint32_t c, Adafruit_NeoPixel & current_strip) {
  for(uint16_t i=0; i<current_strip.numPixels()+4; i++) {
      current_strip.setPixelColor(i  , c); // Draw new pixel
      current_strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      current_strip.show();
      delay(3);
  }
}
