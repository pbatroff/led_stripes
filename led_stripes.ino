#define ENABLE_SPEED 0
#include <MD_REncoder.h>
#include <FastLED.h>

#define NUM_LEDS            20
#define BRIGHTNESS          100
#define MAX_BRIGHNTESS_GLOBAL 200     // max 255; better 254
#define LED_TYPE            NEOPIXEL

// LED Array
CRGB leds[NUM_LEDS];

/////////////////////////////
// PINS: 
// LED Stripes
#define STRIPE_PIN_1        5
#define STRIPE_PIN_2        6
#define STRIPE_PIN_3        7
// Poti 1
#define CLK_1               0
#define DT_1                1
// Poti 2
#define CLK_2               2
#define DT_2                3
/////////////////////////////

//#define UPDATES_PER_SECOND 24
#define LOOP_INTERVAL       24

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

uint8_t index               = 0;    // color index, uses rainbow color palette
uint8_t brightness          = 100;  // tracking current brightness
uint8_t max_brightness      = 100;  // max brightness, will be adjusted by poti 2
uint8_t brightness_interval = 60;   // interval, defines min brightness (max - interval)
uint8_t fade_amount         = 2;    // change in brightness

uint8_t motion_speed        = 3;    // increments the color index, defines the speed at which colors are changing
uint8_t brightness_speed    = 3;    // increments the brightness max by this amount

// Potentiometer
// set up encoder object
MD_REncoder poti_1 = MD_REncoder(CLK_1, DT_1);
MD_REncoder poti_2 = MD_REncoder(CLK_2, DT_2);

// internal helper
bool pulsing_direction = true;      // internal switch to determine if increment/decrement brightness
uint8_t interval_counter = 0;       // counter; used to skip loop steps to adjust colors

/**
 * Setup method. Setup LED array with defined PINs, init brightness
 * Color Palette = rainbow
 * setup 2 Potentionmeters
 * activate initial colors
 */
void setup() {

  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_1>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_2>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIPE_PIN_3>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  // initialize Potis
  poti_1.begin();
  poti_2.begin();

  FillLEDsFromPaletteColors(index);
  
  // debug 
  Serial.begin(57600);
}

/**
 * Main loop. Reads out Potis, adjusts LEDs
 * 
 * TODO: send color index to network server
 */
void loop() {

  // reads potentionmeter 1 and adjusts the color index
  poti_set_color_index(poti_1);
  // reads potentionmeter 2 and adjusts brightness 
  poti_set_brightness(poti_2);

  // set brightness --> pulsing effect
  set_brightness();
  // activate settings on the LEDs
  FastLED.show();
//  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

/**
 * reads the poti_1 value, and increases/decreases 
 * the color index on the palette
 */
void poti_set_color_index(MD_REncoder & poti) {
  
  uint8_t x = poti.read();  
  if (x) {
    if (x == DIR_CW) {
      index+=motion_speed;
    } else {
      index-=motion_speed;
    }
    FillLEDsFromPaletteColors(index);
  }
}

/**
 * sets brightness on the LEDs in the parameters of 'max_brightness' and 
 * 'brightness_interval'
 */
void poti_set_brightness(MD_REncoder & poti) {
  
  uint8_t x = poti.read();
  if (x) {
    if (x == DIR_CW) {
      if ((max_brightness + brightness_speed) > MAX_BRIGHNTESS_GLOBAL ){
        max_brightness = MAX_BRIGHNTESS_GLOBAL;
      } else {
        max_brightness+=brightness_speed;
      }
    } else {
      if ((max_brightness < brightness_interval)  ){
        max_brightness = brightness_interval;
      } else {
        max_brightness-=brightness_speed;
      }
    }
    FillLEDsFromPaletteColors(index);
  }  
}

/**
 * Set all LEDs in the Arrays with the given color index 
 * 
 * @index uint8_t colorindex, 0-255, rainbow palette
 */
void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  
//  Serial.println(brightness);  
  for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
      colorIndex += 1;
  }
}

/**
 * Sets the (global) brightness for the LEDs. Uses the LOOP_INTERVSL define
 *  to skip an amount of loops
 *  
 *  Does a pulsing effect on the LEDs, brightness levels are defined by a max value
 *  'max_brightness' and a 'brightness_interval'.
 *  Values cannot b ebigger than 255 or 0, overflows shoulnd't be allowed, since
 *  it isnn't a pulsing effect anymore then.
 */
void set_brightness() {
  
  if (interval_counter < LOOP_INTERVAL) {
    ++interval_counter;
    return;  
  }
  interval_counter = 0;
  if (brightness >= max_brightness) {
    pulsing_direction = false;  
  }
  if (brightness <= (max_brightness - brightness_interval)) {
    pulsing_direction = true;  
  }
  if (pulsing_direction) {
    if ((brightness + fade_amount) <= 255 ){
      brightness+=fade_amount;
    }
  } else {
    if ((brightness - fade_amount ) >= brightness_interval ){
      brightness-=fade_amount;
    }
  }
  FastLED.setBrightness(brightness);
}

