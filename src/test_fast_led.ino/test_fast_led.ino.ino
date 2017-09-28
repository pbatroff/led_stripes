#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    20
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

uint8_t index = 0;
uint8_t brightness = 200;
uint8_t fade_amount = 5;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // debug 
    Serial.begin(57600);
}


void loop()
{    
//    index += 1; /* motion speed */

    Serial.println(index);
    
    FillLEDsFromPaletteColors( index);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    if(brightness == 200 || brightness == 255)
    {
//      fade_amount =- fade_amount ; 
    }        
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
//        brightness = brightness + fade_amount;
        // reverse the direction of the fading at the ends of the fade: 
//        colorIndex += 3;
    }
}

