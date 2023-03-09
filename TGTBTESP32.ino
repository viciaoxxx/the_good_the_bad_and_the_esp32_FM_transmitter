#include "AiEsp32RotaryEncoder.h"
#include "sample.h"
#include <TFT_eSPI.h>
#define ROTARY_ENCODER_A_PIN 25
#define ROTARY_ENCODER_B_PIN 26
#define ROTARY_ENCODER_BUTTON_PIN 27
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
#define sen 1500
#define outputPin 33
#define PWMchannel 0

// int samples[128192]; // where N is the number of elements in the array
bool loopEnabled = false;
/*
FM radio tunner is suposed to set frequency between 88.0 MHz and 104.0 MHz by 0.1MHz steps
Rotary encoder works with integers so we will map 88.0 to 166 and then divide by 10 to get 0.1 steps
frequency = rotaryValue * 2;
*/

int getFrequency()
{
    return rotaryEncoder.readEncoder();
}

void rotary_onButtonClick()
{
    static unsigned long lastTimePressed = 0;
    if (millis() - lastTimePressed < 200)
    {
        return;
    }
    lastTimePressed = millis();

    Serial.print("Radio station set to ");
    Serial.print(getFrequency());
    Serial.println(" MHz ");
}

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

void setup()
{
    Serial.begin(115200);
      tft.init();
  tft.setRotation(0);
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
  ledcSetup(PWMchannel, rotaryEncoder.readEncoder(), 2);
  ledcAttachPin(outputPin, PWMchannel);
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(7000000, 15000000, true); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    rotaryEncoder.setAcceleration(1000000);
    rotaryEncoder.setEncoderValue(12080000); //set default to 92.1 MHz
    Serial.println("FM Radio");
    Serial.print("Radio station initially set to ");
    Serial.print(getFrequency());
    pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{

    if (rotaryEncoder.isEncoderButtonClicked()) {
    // toggle loop state
    loopEnabled = !loopEnabled;
                Serial.println("loopEnabled");
  }
    if (loopEnabled) {
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 0);
      tft.println("MUERTE FM");
      tft.println(getFrequency());
      for(int i = 0; i < 100100; i += 3){
      ledcSetup(PWMchannel, (rotaryEncoder.readEncoder() + (samples[i] * sen)), 2);
      ledcWrite(PWMchannel, 2);
      delayMicroseconds(1000000 / sampleRate);
      }
        } 
      if (rotaryEncoder.encoderChanged())
        {
            Serial.print(rotaryEncoder.readEncoder());
            Serial.println(" ");

        }
  if (!loopEnabled) {
      tft.fillScreen(TFT_YELLOW);
      tft.setCursor(0, 0);
      tft.println("MUERTE FM ELSE");
      ledcSetup(PWMchannel, 0, 1);
      ledcWrite(PWMchannel, 0);
      delay(100);
      }
  

}