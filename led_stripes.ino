#define ENABLE_SPEED 0
#include <MD_REncoder.h>
#include <FastLED.h>

#define NUM_LEDS    20
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 5
#define BRIGHTNESS_INTERVAL 0

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

uint8_t index = 0;
uint8_t brightness = 200;
uint8_t fade_amount = 5;

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

 
//Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_LEDS, STRIPE_PIN_1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_LEDS, STRIPE_PIN_2, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_LEDS, STRIPE_PIN_3, NEO_GRB + NEO_KHZ800);

// Potentiometer
// set up encoder object
MD_REncoder poti_1 = MD_REncoder(CLK_1, DT_1);
MD_REncoder poti_2 = MD_REncoder(CLK_2, DT_2);

bool pulsing_direction = true;
// amount of loops to change brightness
uint8_t interval_counter = 0;

void setup() {

  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_2, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_3, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  // initialize Potis
  poti_1.begin();
  poti_2.begin();
  // debug 
  Serial.begin(57600);
}

void loop() {
  index += 2; /* motion speed */
  Serial.println(index);
  
  FillLEDsFromPaletteColors( index);
  
  FastLED.show();
  set_brightness();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {      
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        // reverse the direction of the fading at the ends of the fade: 
        colorIndex += 1;
    }
}

uint8_t set_brightness() {
  if (interval_counter < BRIGHTNESS_INTERVAL) {
    ++interval_counter;
    return;  
  }
  if (brightness == 255) {
    pulsing_direction = false;  
  }
  if (brightness == 200) {
    pulsing_direction = true;  
  }
  if (pulsing_direction) {
    brightness += fade_amount;
  } else {
    brightness -= fade_amount;  
  }
  return brightness;
}

