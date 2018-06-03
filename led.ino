#include<Adafruit_NeoPixel.h>

#define PIN 3 // Output led pin number
#define BUTTONPIN 2 // Input button pin number
#define NUMPIXELS 90 // Number of leds on strip 

bool crawled = false; // To check crawling status
int ledState = 0; // Keep track of which scenario we in

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialise the neopixel library
  pixels.begin();

  // Initialise pushbutton pin as an input
  pinMode(BUTTONPIN, INPUT);
  
}


void loop() {
  
  // Check button status
  if (digitalRead(BUTTONPIN) == HIGH) // Button pressed
  {
    if (ledState == 0) // If is in scenario 1
    {
      ledState++; // Set to scenario 2
    }
    else
    {
      ledState = 0; // Set to scenario 1
    }
    crawled = false; // Reset crawl since moving to new state

    // Clean all leds
    for(int j=0; j<NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to blank colour
      pixels.show(); // Light led to set colour
    }
  }
  
  // Scenario 1 - Successful, Full crawl
  if (ledState == 0)
  {
    // Check crawling status
    if (crawled == false) // Not crawled yet
    {
      crawled = true; // Set crawling to true since starting to crawl

      // Loop through all leds
      for(int i=0; i<NUMPIXELS; i++)
      {
        //Check button status
        if (digitalRead(BUTTONPIN) == HIGH) // Button is pressed
        {
          ledState = 1; // Change to ram failed scenario
          crawled = false; // Reset crawl since new scenario
          
          // Clean all leds
          for(int j=0; j<NUMPIXELS; j++)
          {
            pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to blank colour
            pixels.show(); // Light led to set colour
          }
          break; // Break out of loop
        }

        // Light up if button is not pressed
        pixels.setPixelColor(i, pixels.Color(0,5,0)); // Set leds to green
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
      }
    }

    // Check crawling status
    else // Crawled already
    {
      // Light all leds
      for(int j=0; j<NUMPIXELS; j++)
      {
        pixels.setPixelColor(j, pixels.Color(0,5,0)); // Set leds to Green
        pixels.show(); // Light led to set colour
      }
    }
  }

  // Scenario 2 - Ram failed, Half crawl
  if (ledState == 1)
  {
    // Check crawling status
    if (crawled == false) // Not crawled yet
    {
      crawled = true; // Set crawling to true since starting to crawl

      // Loop through half the number of leds
      for(int i=0; i<(NUMPIXELS/2); i++)
      {      
        //Check button status
        if (digitalRead(BUTTONPIN) == HIGH) // Button is pressed
        {
          ledState = 0; // Change to the other scenario
          crawled = false; // Reset crawl since moving to new scenario

          // Clean up all leds
          for(int j=0; j<NUMPIXELS; j++)
          {
            pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to blank colour
            pixels.show(); // Light leds to set colour
          }
          break; // Break out of loop
        }

        // Start crawling if button is not pressed
        pixels.setPixelColor(i, pixels.Color(0,5,0)); // Set leds to red
        pixels.show(); // Light up leds
        delay(100); // Led speed 
      }
    }
    
    // Blink red leds
    else // Crawled already
    {    
      // Loop on to turns on blank leds    
      for(int j=0; j<NUMPIXELS; j++)
      { 
        pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
        pixels.show(); // Light up leds
      }
      
      delay(1000); // Delay between blinks

      // Loop through to turn on red leds
      for(int k=0; k<NUMPIXELS; k++)
      {       
        pixels.setPixelColor(k, pixels.Color(5,0,0)); // Set leds to red
        pixels.show(); // Light up leds
      }
    }
  }
}
