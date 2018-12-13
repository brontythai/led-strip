#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 95 // Number of leds on strip 


Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  pixel.begin();
  pixel.show(); // Initialize all pixels to 'off'
}


void loop() {
  // phase 1 lighting
  colorWipe(pixel.Color(5, 0, 0), 50, 29, 30); // Red

  // phase 2 lighting
  colorWipe(pixel.Color(255, 0, 0), 50, 40, 60); // Red

  // phase 3 lighting
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, uint8_t pixelStart, uint8_t pixelEnd) {
  for(uint16_t i=pixelStart; i<pixelEnd; i++) {
    pixel.setPixelColor(i, c);
    pixel.show();
    delay(wait);
  }
}
