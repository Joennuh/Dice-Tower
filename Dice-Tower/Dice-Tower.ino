/***********************************************************************************************************
 * DICE TOWER
 * Author                 : The Big Site / Jeroen Maathuis (Joennuh)
 * E-mail                 : j [dot] maathuis [at] gmail [dot] com / software [at] thebigsite [dot] nl)
 * Intitial creation date : September 24th, 2019
 * 
 * This sketch is meant for a Dice Tower. It is a sketch for a Wemos D1 mini. It drives 2 red leds for
 * the eyes of a skull and 3 leds for a campfire. Also there is 1 button to initiate blinking eyes and
 * 1 button to toggle between steady or flickering / blinking lights.
 * Although it is developed for a WiFi capable Arduino board the WiFi capabilities aren't used.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * This software is based on example sketches from several sources. Mostly the examples come from library's
 * being used in this sketch.
 * Sources:
 * -  Button2: https://github.com/LennartHennigs/Button2
 * And probably I've forgotten to mention sources. In that case: I'm sorry for that.
 * 
 * Hardware configuration:
 * - Wemos D1 mini
 * - 3 yellow leds (each attached with 100R resistor to D6, D7 and D8)
 * - 2 red leds (each attached with 100R resistor to D1 and D2)
 * - 1 button (attached with external 4,7K pull-up resistor to D5)
 * - 1 any kind of switch to trigger blinking eyes (attached to D3)
************************************************************************************************************/

// == INCLUDES ============================================================================================
#include <Button2.h>

// == DEFINES =============================================================================================
#define LED_EYE1 D1
#define LED_EYE2 D2
#define LED_FIRE1 D6
#define LED_FIRE2 D7
#define LED_FIRE3 D8
#define BTN_TRIGGER D3
#define BTN_CONFIG D5
#define PROG_NAME "Dice Tower"
#define PROG_VERSION "0.1.0000"
#define PROG_MANUFACTURER "The Big Site"

// == SETTINGS ============================================================================================
const int eyeIdleIntensity = 20; // Idle intensity for eyes
const int eyeActiveIntensity = 255; // Active intensity for eyes
const int eyeActiveDuration = 3000; // In milliseconds

const int eyeBlinkShortOn = 100;
const int eyeBlinkShortOff = 100;
const int eyeBlinkAmount = 3;

const int fireMinIntensity = 0; // Minimum intensity for campfire flickering
const int fireMaxIntensity = 255; // Maximum intensity for campfire flickering


const unsigned long fireFlickeringSpeed = 75; // Interval in milliseconds

// == CONFIGURATION =======================================================================================
Button2 btnTrigger(BTN_TRIGGER, INPUT_PULLUP,1); // Activate internal pull-up resistor of Wemos D1 mini pin D3
Button2 btnConfig(BTN_CONFIG); // Uses external 4,7K pull-up resistor

bool eyesOn = false;
unsigned long eyesStartTimestamp = millis();
unsigned long blinkShortTimestamp = millis();
int eyeBlinkCount = eyeBlinkAmount;
int eyeBlinkShortState = 1;

bool stableLight = false;

// == BUTTON HANDLING =====================================================================================
void button_init()
{
    btnTrigger.setChangedHandler([](Button2 & b) {
       eyesOn = true;
       eyesStartTimestamp = millis();
       blinkShortTimestamp = millis();
       eyeBlinkCount = eyeBlinkAmount; // Reset blink counter
       eyeBlinkShortState = 1; // Reset blink state
       Serial.print("Trigger activated! Activating eyes. Timestamp: ");
       Serial.println(eyesStartTimestamp);
    });

//    btnTrigger.setReleasedHandler([](Button2 & b) {
//       eyesOn = false;
//    });
    
    btnConfig.setLongClickHandler([](Button2 & b) {
//        // Select
//        unsigned int time = b.wasPressedFor();
//        if (time >= 1000) {
//          if(checkIdling()==false)
//          {
//            nav.doNav(enterCmd);
//          }
//          else
//          {
//            toggleTorch();
//          }          
//        }
    });
    
    btnConfig.setClickHandler([](Button2 & b) {
       if(stableLight==false)
       {
          stableLight=true;
       }
       else
       {
          stableLight=false;
       }
    });
}

void button_loop()
{
    btnTrigger.loop();
    btnConfig.loop();
}

// == SETUP() =============================================================================================
void setup() {
  // Initialize Serial data and print program metadata
  Serial.begin(115200);
  while(!Serial);
  Serial.flush();
  Serial.println();
  Serial.print(PROG_MANUFACTURER);
  Serial.print(" ");
  Serial.println(PROG_NAME);
  Serial.print("SW ");
  Serial.println(PROG_VERSION);
  Serial.println("BOOT OK");

  // Intialize buttons
  button_init();

  // Initialize onboard led, test it and leave it on until fully booted
  Serial.print("Configure onboard led... ");
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning onboard led on...");
  digitalWrite(LED_BUILTIN,LOW); // Onboard led is active low
  Serial.println("DONE");
  delay(500);

  // Initialize eye 1, test it and turn it off
  Serial.print("Configure led eye 1... ");
  pinMode(LED_EYE1, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning led eye 1 on... ");
  analogWrite(LED_EYE1, 255);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning led eye 1 off... ");
  analogWrite(LED_EYE1, 0);
  Serial.println("DONE");

  // Initialize eye 2, test it and turn it off
  Serial.print("Configure led eye 2... ");
  pinMode(LED_EYE2, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning led eye 2 on... ");
  analogWrite(LED_EYE2, 255);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning led eye 2 off... ");
  analogWrite(LED_EYE2, 0);
  Serial.println("DONE");

  // Initialize fire 1, test it and turn it off
  Serial.print("Configure led fire 1... ");
  pinMode(LED_FIRE1, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning led fire 1 on... ");
  analogWrite(LED_FIRE1, 255);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning led fire 1 off... ");
  analogWrite(LED_FIRE1, 0);
  Serial.println("DONE");

  // Initialize fire 2, test it and turn it off
  Serial.print("Configure led fire 2... ");
  pinMode(LED_FIRE2, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning led fire 2 on... ");
  analogWrite(LED_FIRE2, 255);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning led fire 2 off... ");
  analogWrite(LED_FIRE2, 0);
  Serial.println("DONE");

  // Initialize fire 3, test it and turn it off
  Serial.print("Configure led fire 3... ");
  pinMode(LED_FIRE3, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning led fire 3 on... ");
  analogWrite(LED_FIRE3, 255);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning led fire 3 off... ");
  analogWrite(LED_FIRE3, 0);
  Serial.println("DONE");

  // Feeding randomSeed with random analog noise of unconnected analog pin... 
  Serial.print("Feeding randomSeed with random analog noise of unconnected analog pin... ");
  randomSeed(analogRead(A0));
  Serial.println("DONE");

  // Turning onboard led off
  Serial.print("Turning onboard led off... ");
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("DONE");

  Serial.println("- READY -");
}

// Set starting timestamp
unsigned long lastTimestamp = millis();

void loop() {
  button_loop(); // Poll button states

  if(stableLight==true)
  {
    analogWrite(LED_FIRE1, fireMaxIntensity);
    analogWrite(LED_FIRE2, fireMaxIntensity);
    analogWrite(LED_FIRE3, fireMaxIntensity);
  }
  else
  {
    if(millis()-lastTimestamp > fireFlickeringSpeed)
    {
      int randFire1 = random(fireMinIntensity,fireMaxIntensity);
      int randFire2 = random(fireMinIntensity,fireMaxIntensity);
      int randFire3 = random(fireMinIntensity,fireMaxIntensity);
      analogWrite(LED_FIRE1, randFire1);
      analogWrite(LED_FIRE2, randFire2);
      analogWrite(LED_FIRE3, randFire3);
      lastTimestamp = millis();
    }
  }
  if(eyesOn == true)
  {
    if(millis() - eyesStartTimestamp < eyeActiveDuration)
    {
        digitalWrite(LED_BUILTIN,LOW);

//      analogWrite(LED_EYE1,eyeActiveIntensity);
//      analogWrite(LED_EYE2,eyeActiveIntensity);

        if(stableLight==true)
        {
          Serial.println("Stable light is activated so not blinking. Just stable lit eyes.");
          analogWrite(LED_EYE1,eyeActiveIntensity);
          analogWrite(LED_EYE2,eyeActiveIntensity);
        }
        else
        {       
            Serial.print("eyeBlinkCount: ");
            Serial.print(eyeBlinkCount);
            Serial.print(", eyeBlinkAmount: ");
            Serial.println(eyeBlinkAmount);
            if(eyeBlinkCount > 0)
            {
                Serial.println("eyeBlinkCount > 0");
                Serial.print("millis(): ");
                Serial.print(millis());
                Serial.print(", blinkShortTimestamp: ");
                Serial.print(blinkShortTimestamp);
                Serial.print(", eyeBlinkShortOn: ");
                Serial.print(eyeBlinkShortOn);
                Serial.print(", eyeBlinkShortOff: ");
                Serial.print(eyeBlinkShortOff);
                Serial.print(", eyeBlinkShortState: ");
                Serial.println(eyeBlinkShortState);
                if(eyeBlinkShortState == 1){
                    Serial.println("eyeBlinkShortState == 1");
                    if(millis() - blinkShortTimestamp <= eyeBlinkShortOn)
                    {
                        Serial.println("blinkShortTimestamp <= eyeBlinkShortOn");
                        analogWrite(LED_EYE1,eyeActiveIntensity);
                        analogWrite(LED_EYE2,eyeActiveIntensity);
                    }
                    else{
                        Serial.println("blinkShortTimestamp > eyeBlinkShortOn >> Set eyeBlinkShortState to 0 and reset timestamp");
                        blinkShortTimestamp = millis();
                        eyeBlinkShortState = 0; // Set blink state to off
                    }
                }
                else if(eyeBlinkShortState == 0){
                    Serial.println("eyeBlinkShortState == 0");
                    if(millis() - blinkShortTimestamp <= eyeBlinkShortOff)
                    {
                        Serial.println("blinkShortTimestamp <= eyeBlinkShortOff");
                        analogWrite(LED_EYE1,eyeIdleIntensity);
                        analogWrite(LED_EYE2,eyeIdleIntensity);
                    }
                    else{
                        Serial.println("blinkShortTimestamp > eyeBlinkShortOff >> Set eyeBlinkShortState to 1, decrease eyeBlinkCount and reset timestamp");
                        blinkShortTimestamp = millis();
                        eyeBlinkShortState = 1; // Set blink state to on
                        eyeBlinkCount--;
                    }
                }
            }
            else
            {
                // Turn light continuously on
                Serial.println("Eyes continously on");
                analogWrite(LED_EYE1,eyeActiveIntensity);
                analogWrite(LED_EYE2,eyeActiveIntensity);
            }
        }      
    }
    else
    {
      eyesOn = false;
      Serial.print("Deactivating eyes. Timestamp: ");
      Serial.println(millis());
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN,HIGH);
    analogWrite(LED_EYE1,eyeIdleIntensity);
    analogWrite(LED_EYE2,eyeIdleIntensity);
  }
}
