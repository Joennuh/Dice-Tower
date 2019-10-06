/***********************************************************************************************************
 * DICE TOWER
 * Author                 : The Big Site / Jeroen Maathuis (Joennuh)
 * E-mail                 : j [dot] maathuis [at] gmail [dot] com / software [at] thebigsite [dot] nl)
 * Intitial creation date : September 24th, 2019
 * Github                 : https://github.com/Joennuh/Dice-Tower
 * Wiki                   : https://github.com/Joennuh/Dice-Tower/wiki
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
// Sketch metadata. Please do not change the following lines unless you plan to release an fork. In that case please add some information about you to these lines.
#define PROG_NAME "Dice Tower"
#define PROG_VERSION "0.1.0000"
#define PROG_MANUFACTURER "The Big Site"

// == INCLUDES ============================================================================================
#include <Button2.h>

// == DEFINES =============================================================================================
// You can change the values of this defines but it is advisable to not do this.

#ifdef ESP32
// Define pin assignment for MH TK LIVE MiniKit ESP32
#define LED_CONFIG 26
#define LED_EYE1 22
#define LED_EYE2 21
#define LED_FIRE1 19
#define LED_FIRE2 23
#define LED_FIRE3 5
#define BTN_TRIGGER 17
#define BTN_CONFIG 18
#define ANALOG_RANDOMSEED 36 // Leave this pin unconnected, the noise of this pin is used for the random creator
#else
// Define pin assignment for Wemos D1 mini
#define LED_CONFIG D0
#define LED_EYE1 D1
#define LED_EYE2 D2
#define LED_FIRE1 D6
#define LED_FIRE2 D7
#define LED_FIRE3 D8
#define BTN_TRIGGER D3
#define BTN_CONFIG D5
#define ANALOG_RANDOMSEED A0 // Leave this pin unconnected, the noise of this pin is used for the random creator
#endif

// == SETTINGS ============================================================================================
// These settings can be change to your own needs.

#ifdef ESP32
// Setting PWM properties (only for MH TK LIVE MiniKit ESP32)
const int pwmFreq = 5000;
const int pwmResolution = 8;
#endif

// EYE LEDS
const int eyeIdleIntensity = 20; // Idle intensity for the eyes on a scale of 0 to 255
const int eyeActiveIntensity = 255; // Active intensity for the eyes on a scale of 0 to 255
const int eyeActiveDuration = 3000; // How long the eyes should stay active on a detected dice. In milliseconds.

const int eyeBlinkShortOn = 100; // Duration of the on state while blinking. In milliseconds.
const int eyeBlinkShortOff = 100; // Duration of the off state while blinking. In milliseconds.
const int eyeBlinkAmount = 3; // How much blinks of the eyes during the blink state on a detected dice.

#ifdef ESP32
// Define PWM channel for MH TK LIVE MiniKit ESP32
const int pwmEyesChannel = 0;
#endif

// FIRE LEDS
const int fireMinIntensity = 0; // Minimum intensity for campfire flickering on a scale of 0 - 255.
const int fireMaxIntensity = 255; // Maximum intensity for campfire flickering on a scale of 0 - 255
const unsigned long fireFlickeringSpeed = 75; // Interval in milliseconds before a new random intensity will be set for a campfire led.


#ifdef ESP32
// Define PWM channel for for MH TK LIVE MiniKit ESP32
const int pwmFire1Channel = 1;
const int pwmFire2Channel = 2;
const int pwmFire3Channel = 3;
#endif

// CONFIGURATION LED
const int configLedSingleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on after a single click on the configuration button.
const int configLedLongClickDurationOn = 1000; // How long in milliseconds should the configuration led stay on after a long click on the configuration button.
const int configLedDoubleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on in the on state of blinking after a double click on the configuration button.
const int configLedDoubleClickDurationOff = 200; // How long in milliseconds should the configuration led stay on in the on state of blinking after a double click on the configuration button.

// == CONFIGURATION =======================================================================================
// These settings are needed to let the sketch work correctly but should not be changed!

Button2 btnTrigger(BTN_TRIGGER, INPUT_PULLUP,1); // Activate internal pull-up resistor of Wemos D1 mini pin D3
Button2 btnConfig(BTN_CONFIG); // Uses external 4,7K pull-up resistor

bool eyesOn = false; // Trigger for within the loop to turn the eyes on.
unsigned long eyesStartTimestamp = millis(); // Record default timestamp for eyes logic.
unsigned long blinkShortTimestamp = millis(); // Record default timestamp for eyes blink logic.
int eyeBlinkCount = eyeBlinkAmount; // Set the counter (which got decreased) to the value set for amount of blinks of the eyes.
int eyeBlinkShortState = 1; // Set the initial state for the blinking eyes logic. In this case the blink starts with the on (1) state.

bool stableLight = false; // Boolean to detect whter all lights may blink or should be lit permamently. False = blink. True = permanently lid.

unsigned long fireTimestamp = millis(); // Record default timestamp for fire logic.

bool configLedOn = false; // Trigger for within the loop to turn the configuration led on.
int configLedType = 0; // The sequence how the configuration led should turn on. 0 = none, 1 = single click, 2 = long click, 3 = double click
unsigned long configLedTimestamp = millis(); // Record default timestamp for the configuration led logic.
int configLedDoubleClickstate = 0; // Set the initial state for the blinking configuration led logic. In this case the blink starts with the off (0) state.
int configLedDoubleClickCount = 2; // Set the counter (which got decreased) for the amount of blinks for the configuration led after a double click.

// Set active states for LED_BUILTIN. On ESP8266 the led is active on LOW, but on ESP32 it is active on HIGH.
#ifdef ESP32
#define ONBOARD_ON HIGH
#define ONBOARD_OFF LOW
#else
#define ONBOARD_ON LOW
#define ONBOARD_OFF HIGH
#endif

// == BUTTON HANDLING =====================================================================================
// The following function sets the handlers for all button presses.
void button_init()
{
    btnTrigger.setChangedHandler([](Button2 & b) { // Only press or release would maybe not get triggered correctly so we chose both (change).
       eyesStartTimestamp = millis();
       blinkShortTimestamp = millis();

       eyesOn = true;
       eyeBlinkCount = eyeBlinkAmount; // Reset eyes blink counter
       eyeBlinkShortState = 1; // Reset eyes blink state
       
       Serial.print("Trigger activated! Activating eyes. Timestamp: ");
       Serial.println(eyesStartTimestamp);
    });

//    btnTrigger.setReleasedHandler([](Button2 & b) {
//       eyesOn = false;
//    });
    
    btnConfig.setLongClickHandler([](Button2 & b) {
        // Select
        unsigned int time = b.wasPressedFor();
        if (time >= 1000) {
           configLedTimestamp = millis();
           configLedOn = true;
           configLedType = 2;
           configLedDoubleClickstate = 1;
           configLedDoubleClickCount = 2;
           Serial.print("Config long click activated! Timestamp: ");
           Serial.println(configLedTimestamp);

           if(stableLight==false)
           {
              stableLight=true;
           }
           else
           {
              stableLight=false;
           }
        }
    });

     btnConfig.setDoubleClickHandler([](Button2 & b) {
       configLedTimestamp = millis();
       configLedOn = true;
       configLedType = 3;
       configLedDoubleClickstate = 1;
       configLedDoubleClickCount = 2;
       Serial.print("Config double click activated! Timestamp: ");
       Serial.println(configLedTimestamp);
    });
    
    btnConfig.setClickHandler([](Button2 & b) {
       configLedTimestamp = millis();
       configLedOn = true;
       configLedType = 1;
       configLedDoubleClickstate = 0;
       configLedDoubleClickCount = 2;
       
       Serial.print("Config single click activated! Timestamp: ");
       Serial.println(configLedTimestamp);

       eyesStartTimestamp = millis();
       blinkShortTimestamp = millis();

       eyesOn = true;
       eyeBlinkCount = eyeBlinkAmount; // Reset blink counter
       eyeBlinkShortState = 1; // Reset blink state
       
       Serial.print("Manual rigger activated! Activating eyes. Timestamp: ");
       Serial.println(eyesStartTimestamp);
    });
}

// The following functions handles the button presses
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

// -- ONBOARD LED -----------------------------------------------------------------------------------------
  // Initialize onboard led, test it and leave it on until fully booted
  Serial.print("Configure onboard led... ");
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning onboard led on...");
  digitalWrite(LED_BUILTIN,ONBOARD_ON);
  Serial.println("DONE");
  delay(500);

// -- CONFIG LED ------------------------------------------------------------------------------------------
   // Initialize config led, test it and turn it off
  Serial.print("Configure config led... ");
  pinMode(LED_CONFIG, OUTPUT);
  Serial.println("DONE");
  Serial.print("Turning config led on... ");
  digitalWrite(LED_CONFIG, HIGH);
  Serial.println("DONE");
  delay(500);
  Serial.print("Turning config led off... ");
  digitalWrite(LED_CONFIG, LOW);
  Serial.println("DONE");

// -- EYE LEDS --------------------------------------------------------------------------------------------
#ifdef ESP32
  // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
  Serial.print("Configure PWM channel for leds for eyes... ");
  ledcSetup(pwmEyesChannel, pwmFreq, pwmResolution);
  Serial.println("DONE");
  
  Serial.print("Attach led eye 1 to PWM channel for eyes... ");
  ledcAttachPin(LED_EYE1, pwmEyesChannel);
  Serial.println("DONE");
  
  Serial.print("Attach led eye 2 to PWM channel for eyes... ");
  ledcAttachPin(LED_EYE2, pwmEyesChannel);
  Serial.println("DONE");

  Serial.print("Turning both eye leds on... ");
  ledcWrite(pwmEyesChannel, 255);
  Serial.println("DONE");

  delay(500);

  Serial.print("Turning both eyes off... ");
  ledcWrite(pwmEyesChannel, 0);
  Serial.println("DONE");
#else
  // For Wemos D1 mini we can use analogWrite()
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
#endif

// -- FIRE 1 LED ------------------------------------------------------------------------------------------
#ifdef ESP32
  // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
  Serial.print("Configure PWM channel for led fire 1... ");
  ledcSetup(pwmFire1Channel, pwmFreq, pwmResolution);
  Serial.println("DONE");
  
  Serial.print("Attach led fire 1 to PWM channel for eyes... ");
  ledcAttachPin(LED_FIRE1, pwmFire1Channel);
  Serial.println("DONE");

  Serial.print("Turning led fire 1 on... ");
  ledcWrite(pwmFire1Channel, 255);
  Serial.println("DONE");

  delay(500);

  Serial.print("Turning led fire 1 off... ");
  ledcWrite(pwmFire1Channel, 0);
  Serial.println("DONE");
  
#else
  // For Wemos D1 mini we can use analogWrite()
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
#endif

// -- FIRE 2 LED ------------------------------------------------------------------------------------------
#ifdef ESP32
  // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
  Serial.print("Configure PWM channel for led fire 2... ");
  ledcSetup(pwmFire2Channel, pwmFreq, pwmResolution);
  Serial.println("DONE");
  
  Serial.print("Attach led fire 2 to PWM channel for eyes... ");
  ledcAttachPin(LED_FIRE2, pwmFire2Channel);
  Serial.println("DONE");

  Serial.print("Turning led fire 2 on... ");
  ledcWrite(pwmFire2Channel, 255);
  Serial.println("DONE");

  delay(500);

  Serial.print("Turning led fire 2 off... ");
  ledcWrite(pwmFire2Channel, 0);
  Serial.println("DONE");
  
#else
  // For Wemos D1 mini we can use analogWrite()
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
#endif

// -- FIRE 3 LED ------------------------------------------------------------------------------------------
#ifdef ESP32
  // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
  Serial.print("Configure PWM channel for led fire 3... ");
  ledcSetup(pwmFire3Channel, pwmFreq, pwmResolution);
  Serial.println("DONE");
  
  Serial.print("Attach led fire 3 to PWM channel for eyes... ");
  ledcAttachPin(LED_FIRE3, pwmFire3Channel);
  Serial.println("DONE");

  Serial.print("Turning led fire 3 on... ");
  ledcWrite(pwmFire3Channel, 255);
  Serial.println("DONE");

  delay(500);

  Serial.print("Turning led fire 3 off... ");
  ledcWrite(pwmFire3Channel, 0);
  Serial.println("DONE");
  
#else
  // For Wemos D1 mini we can use analogWrite()
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
#endif

// -- RANDOM CREATOR --------------------------------------------------------------------------------------
  // Feeding randomSeed with random analog noise of unconnected analog pin... 
  Serial.print("Feeding randomSeed with random analog noise of unconnected analog pin... ");
  randomSeed(analogRead(ANALOG_RANDOMSEED));
  Serial.println("DONE");

// -- TURNING ONBOARD LED OFF -----------------------------------------------------------------------------
  // Turning onboard led off
  Serial.print("Turning onboard led off... ");
  digitalWrite(LED_BUILTIN,ONBOARD_OFF);
  Serial.println("DONE");

  Serial.println("- READY -");
}

void loop() {
  button_loop(); // Poll button states

  // Configuration led
  if(configLedOn == true)
  {
    // Single click
    if(configLedType == 1){
        if(millis()- configLedTimestamp <= configLedSingleClickDurationOn)
        {
            digitalWrite(LED_CONFIG, HIGH);
        }
        else
        {
            digitalWrite(LED_CONFIG, LOW);
            configLedTimestamp = millis();
            configLedOn = false;
            configLedType = 0;
        }
    }
    // Long click
    else if(configLedType == 2){
        if(millis()- configLedTimestamp <= configLedLongClickDurationOn)
        {
            digitalWrite(LED_CONFIG, HIGH);
        }
        else
        {
            digitalWrite(LED_CONFIG, LOW);
            configLedTimestamp = millis();
            configLedOn = false;
            configLedType = 0;
        }
    }
    // Double click
    else if(configLedType == 3){
        if(configLedDoubleClickCount > 0)
        {
          Serial.print("millis(): ");
          Serial.print(millis());
          Serial.print(", configLedTimestamp: ");
          Serial.println(configLedTimestamp);
          
          // Led on
          if(configLedDoubleClickstate == 1){
              Serial.println("configLedDoubleClickstate == 1");
              if(millis() - configLedTimestamp <= configLedDoubleClickDurationOn)
              {
                  Serial.println("configLedTimestamp <= configLedDoubleClickDurationOn");
                  digitalWrite(LED_CONFIG,HIGH);
              }
              else{
                  Serial.println("configLedTimestamp > configLedDoubleClickDurationOn >> Set configLedDoubleClickstate to 0 and reset timestamp");
                  configLedTimestamp = millis();
                  configLedDoubleClickstate = 0; // Set blink state to off
              }
          }
          // Led off
          else if(configLedDoubleClickstate == 0){
              Serial.println("configLedDoubleClickstate == 0");
              if(millis() - configLedTimestamp <= configLedDoubleClickDurationOff)
              {
                  Serial.println("configLedTimestamp <= configLedDoubleClickDurationOff");
                  digitalWrite(LED_CONFIG,LOW);
              }
              else{
                  Serial.println("configLedTimestamp > configLedDoubleClickDurationOff >> Set configLedDoubleClickstate to 1, decrease configLedDoubleClickCount and reset timestamp");
                  configLedTimestamp = millis();
                  configLedDoubleClickstate = 1; // Set blink state to on
                  configLedDoubleClickCount--;
              }
          }
        }
    }
  }

  // Permamently lit fire
  if(stableLight == true)
  {
#ifdef ESP32
    // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
    ledcWrite(pwmFire1Channel, fireMaxIntensity);
    ledcWrite(pwmFire2Channel, fireMaxIntensity);
    ledcWrite(pwmFire3Channel, fireMaxIntensity);
#else
    // For Wemos D1 mini we can use analogWrite()
    analogWrite(LED_FIRE1, fireMaxIntensity);
    analogWrite(LED_FIRE2, fireMaxIntensity);
    analogWrite(LED_FIRE3, fireMaxIntensity);
#endif
  }
  // Flickering fire
  else
  {
    if(millis()-fireTimestamp > fireFlickeringSpeed)
    {
      int randFire1 = random(fireMinIntensity,fireMaxIntensity);
      int randFire2 = random(fireMinIntensity,fireMaxIntensity);
      int randFire3 = random(fireMinIntensity,fireMaxIntensity);
#ifdef ESP32
      // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
      ledcWrite(pwmFire1Channel, randFire1);
      ledcWrite(pwmFire2Channel, randFire2);
      ledcWrite(pwmFire3Channel, randFire3);
#else
      // For Wemos D1 mini we can use analogWrite()
      analogWrite(LED_FIRE1, randFire1);
      analogWrite(LED_FIRE2, randFire2);
      analogWrite(LED_FIRE3, randFire3);
#endif
      fireTimestamp = millis();
    }
  }
  
  // Eyes
  if(eyesOn == true)
  {
    // Within duration set in the settings
    if(millis() - eyesStartTimestamp < eyeActiveDuration)
    {
        digitalWrite(LED_BUILTIN,ONBOARD_ON);

        // Permamently lit eyes
        if(stableLight==true)
        {
          Serial.println("Stable light is activated so not blinking. Just stable lit eyes.");
#ifdef ESP32
          // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
          ledcWrite(pwmEyesChannel, eyeActiveIntensity);
#else
          // For Wemos D1 mini we can use analogWrite()
          analogWrite(LED_EYE1,eyeActiveIntensity);
          analogWrite(LED_EYE2,eyeActiveIntensity);
#endif
        }
        // Blinking eyes
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

                // Blinking eyes: on
                if(eyeBlinkShortState == 1){
                    Serial.println("eyeBlinkShortState == 1");
                    if(millis() - blinkShortTimestamp <= eyeBlinkShortOn)
                    {
                        Serial.println("blinkShortTimestamp <= eyeBlinkShortOn");
#ifdef ESP32
                        // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
                        ledcWrite(pwmEyesChannel, eyeActiveIntensity);
#else
                        // For Wemos D1 mini we can use analogWrite()
                        analogWrite(LED_EYE1,eyeActiveIntensity);
                        analogWrite(LED_EYE2,eyeActiveIntensity);
#endif
                    }
                    else{
                        Serial.println("blinkShortTimestamp > eyeBlinkShortOn >> Set eyeBlinkShortState to 0 and reset timestamp");
                        blinkShortTimestamp = millis();
                        eyeBlinkShortState = 0; // Set blink state to off
                    }
                }
                // Blinking eyes: off
                else if(eyeBlinkShortState == 0){
                    Serial.println("eyeBlinkShortState == 0");
                    if(millis() - blinkShortTimestamp <= eyeBlinkShortOff)
                    {
                        Serial.println("blinkShortTimestamp <= eyeBlinkShortOff");
#ifdef ESP32
                        // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
                        ledcWrite(pwmEyesChannel, eyeIdleIntensity);
#else
                        // For Wemos D1 mini we can use analogWrite()
                        analogWrite(LED_EYE1,eyeIdleIntensity);
                        analogWrite(LED_EYE2,eyeIdleIntensity);
#endif
                    }
                    else{
                        Serial.println("blinkShortTimestamp > eyeBlinkShortOff >> Set eyeBlinkShortState to 1, decrease eyeBlinkCount and reset timestamp");
                        blinkShortTimestamp = millis();
                        eyeBlinkShortState = 1; // Set blink state to on
                        eyeBlinkCount--;
                    }
                }
            }
            // Blink count reached amount of blinks set. Turning the eyes permamently on for dthe duration set to keep eyes on detection of a dice.
            else
            {
                Serial.println("Eyes continously on");
#ifdef ESP32
                // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
                ledcWrite(pwmEyesChannel, eyeActiveIntensity);
#else
                // For Wemos D1 mini we can use analogWrite()
                analogWrite(LED_EYE1,eyeActiveIntensity);
                analogWrite(LED_EYE2,eyeActiveIntensity);
#endif
            }
        }      
    }
    // End of eyes duration reached.
    else
    {
      eyesOn = false;
      Serial.print("Deactivating eyes. Timestamp: ");
      Serial.println(millis());
    }
  }
  // No dice detected. Keeping eyes dim.
  else
  {
    digitalWrite(LED_BUILTIN,ONBOARD_OFF);
#ifdef ESP32
    // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
    ledcWrite(pwmEyesChannel, eyeIdleIntensity);
#else
    // For Wemos D1 mini we can use analogWrite()
    analogWrite(LED_EYE1,eyeIdleIntensity);
    analogWrite(LED_EYE2,eyeIdleIntensity);
#endif
  }
}
