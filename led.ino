#include<Adafruit_NeoPixel.h>

#define PIN 3 // Output led pin number
#define BUTTONPIN 2 // Input button pin number
#define NUMPIXELS 90 // Number of leds on strip
#define TEST_STATUS 1

bool crawled = false; 
bool cleaned = false; // To check if button is pressed while inside loop
int ledState = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialise the neopixel library
  pixels.begin();

  // Initialise pushbutton pin as an input
  pinMode(BUTTONPIN, INPUT);
  
}


void loop() {
  // put your main code here, to run repeatedly:

  // Read the state of the pushbutton
  //buttonState = digitalRead(BUTTONPIN);

  // Check if button is pressed
  if (digitalRead(BUTTONPIN) == HIGH)
  {
    if (ledState == 0)
    {
      ledState++;
    }
    else
    {
      ledState = 0;
    }
    crawled = false; 

    for(int j=0; j<NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
      pixels.show();
    }
  }
  
  // Scenario 1 - Successful
  if (ledState == 0)
  {
    // Full crawl
    if (crawled == false)
    {
      crawled = true;
      for(int i=0; i<NUMPIXELS; i++)
      {
        //Check button status
        if (digitalRead(BUTTONPIN) == HIGH)
        {
          ledState = 1;
          crawled = false;
          for(int j=0; j<NUMPIXELS; j++)
          {
            pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
            pixels.show();
          }
          break;
        }
        pixels.setPixelColor(i, pixels.Color(0,5,0)); // Set leds to green
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
      }
    }
    
    // Light up all green leds
    else
    {
      for(int j=0; j<NUMPIXELS; j++)
      {
        pixels.setPixelColor(j, pixels.Color(0,5,0)); // Set leds to red
        pixels.show();
      }
    }
  }

  // Scenario 2 - Ram failed
  if (ledState == 1)
  {
    // Half crawl
    if (crawled == false)
    {
      crawled = true;
      for(int i=0; i<(NUMPIXELS/2); i++)
      {      
        //Check button status
        if (digitalRead(BUTTONPIN) == HIGH)
        {
          ledState = 0;
          crawled = false;
          for(int j=0; j<NUMPIXELS; j++)
          {
            pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
            pixels.show();
          }
          break;
        }

        // Start crawling
        pixels.setPixelColor(i, pixels.Color(0,5,0)); // Set leds to red
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
      }
    }
    
    // Blink red leds
    else
    {        
      for(int j=0; j<NUMPIXELS; j++)
      { 
        // Turns on blank leds
        pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
        pixels.show();
      }
      
      delay(1000);
      
      for(int k=0; k<NUMPIXELS; k++)
      {      
        // Turn on red leds
        pixels.setPixelColor(k, pixels.Color(5,0,0)); // Set leds to red
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

