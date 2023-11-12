#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 40
#define PIXEL_PIN 12  // Change this to the digital pin where you connect the NeoPixels
#define COLOR_SWITCH_PIN 14  // Digital pin for the color switch

// Define the pins for the 10 difficulty switches
int difficultySwitchPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  // Set the color control switch pin as an input with a pull-up resistor
  pinMode(COLOR_SWITCH_PIN, INPUT_PULLUP);

  // Set the difficulty switch pins as inputs with pull-up resistors
  for (int i = 0; i < 10; i++) {
    pinMode(difficultySwitchPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Read color control switch
  int colorControl = digitalRead(COLOR_SWITCH_PIN);

  // Set the color based on the color control switch
  uint32_t color = (colorControl == HIGH) ? strip.Color(0, 255, 0) : strip.Color(255, 0, 0);

  // Read difficulty levels from individual difficulty pins
  for (int i = 0; i < 10; i++) {
    int difficultyLevel = digitalRead(difficultySwitchPins[i]);

    // Calculate the starting pixel for this difficulty level
    int startPixel = i * (NUM_PIXELS / 10);

    // Calculate the number of pixels to light up based on difficulty level
    int pixelsToLight = map(difficultyLevel, 0, 1, 0, NUM_PIXELS / 10);

    // Light up the pixels for this difficulty level
    for (int j = startPixel; j < startPixel + pixelsToLight; j++) {
      strip.setPixelColor(j, color);
    }
  }

  strip.show();
}
