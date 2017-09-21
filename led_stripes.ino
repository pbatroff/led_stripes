#include <Adafruit_NeoPixel.h>

#define STRIPE_PIN_1      5
#define STRIPE_PIN_2      6
#define STRIPE_PIN_3      7

#define N_LEDS 20
 
Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(N_LEDS, STRIPE_PIN_3, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip_1.begin();
  strip_2.begin();
  strip_3.begin();
  
  // init
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
}

void loop() {
  // put your main code here, to run repeatedly:
  shine_all(strip_2.Color(0, 255, 0));
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

static void chase(uint32_t c, Adafruit_NeoPixel & current_strip) {
  for(uint16_t i=0; i<current_strip.numPixels()+4; i++) {
      current_strip.setPixelColor(i  , c); // Draw new pixel
      current_strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      current_strip.show();
      delay(25);
  }
}
