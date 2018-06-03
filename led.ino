#include<Adafruit_NeoPixel.h>

#define PIN 3 // Output to led pin
#define NUMPIXELS 90 // Number of leds on strip
#define TEST_STATUS 0
bool crawled = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialise the neopixel library
  pixels.begin();

  
}

void loop() {
  // put your main code here, to run repeatedly:

  // sucessful scenario
  if (TEST_STATUS == 1)
  {
    // full crawl
    for(int i=0; i<NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,100,0)); // Set leds to green
      pixels.show(); // Light up leds
      delay(100); // Led on speed 
    }

    // Light up all leds
    pixels.show();    
  }

  // ram failed scenario
  if (TEST_STATUS == 0)
  {
    // full crawl
    if(crawled == false)
    {
      for(int i=0; i<(NUMPIXELS/2); i++)
      {
        pixels.setPixelColor(i, pixels.Color(100,0,0)); // Set leds to red
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
      }
      crawled = true;
    }
    
    // Light up all leds
    else
    {
      for(int j=0; j<NUMPIXELS; j++)
      {
        pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to red
        pixels.show();
      }
      
      delay(1000);
      
      for(int k=0; k<NUMPIXELS; k++)
      {
        pixels.setPixelColor(k, pixels.Color(100,0,0)); // Set leds to red
        pixels.show();
      }
    }
  }
}


// Scenario1

//success
// -crawl full way(90 leds)
// -light up the whole outer with green


//fail
// -crawl half way (45 leds)
// -blinks red


