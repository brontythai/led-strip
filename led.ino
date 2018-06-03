#include<Adafruit_NeoPixel.h>

#define PIN 3 // Output led pin number
#define BUTTONPIN 2 // Input button pin number
#define NUMPIXELS 90 // Number of leds on strip
#define TEST_STATUS 1

bool crawled = false; 
bool cleaned = false; // To check if button is pressed while inside loop
int buttonState = 0;
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
  }
  
  // sucessful scenario
  if (ledState == 0)
  {
    // full crawl
    if (crawled == false)
    {
      cleaned = false; // Reset cleaned
      
      for(int i=0; i<NUMPIXELS; i++)
      {
        // Check if button is pressed
        if (digitalRead(BUTTONPIN) == HIGH)
        {
          cleanup(); // Wipe clear all leds
          break; // Break out of loop
        }
        pixels.setPixelColor(i, pixels.Color(0,5,0)); // Set leds to green
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
        
      }
      crawled = true;
    }
    
  
    // Light up all leds
    else if (cleaned == false)
    {
      for(int j=0; j<NUMPIXELS; j++)
      {
        pixels.setPixelColor(j, pixels.Color(0,5,0)); // Set leds to red
        pixels.show();
      }
    }
  }

  // ram failed scenario
  if (ledState == 1)
  {
    // half crawl
    if(crawled == false)
    {
      cleaned = false; // Reset cleaned

      for(int i=0; i<(NUMPIXELS/2); i++)
      {        
        pixels.setPixelColor(i, pixels.Color(100,0,0)); // Set leds to red
        pixels.show(); // Light up leds
        delay(100); // Led on speed 
      }
      crawled = true;
    }
    
    // Blinks
    else
    {
      for(int j=0; j<NUMPIXELS; j++)
      {
        pixels.setPixelColor(j, pixels.Color(0,0,0)); // Set leds to nothing
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


void cleanup()
{
  for(int j=0; j<NUMPIXELS; j++)
  {
    pixels.setPixelColor(j, pixels.Color(0,0,10)); // Set leds to nothing
    pixels.show();
  }
  cleaned = true; // Cleaned
  crawled = false; 
  
  if (ledState == 0)
  {
    ledState++;
  }
  else
  {
    ledState = 0;
  }

}

// Scenario1

//success
// -crawl full way(90 leds)
// -light up the whole outer with green


//fail
// -crawl half way (45 leds)
// -blinks red


