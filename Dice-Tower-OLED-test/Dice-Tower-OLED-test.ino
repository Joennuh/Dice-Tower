/***********************************************************************************************************
 * DICE TOWER
 * Author                 : The Big Site / Jeroen Maathuis (Joennuh)
 * E-mail                 : j [dot] maathuis [at] gmail [dot] com / software [at] thebigsite [dot] nl)
 * Intitial creation date : October 9th, 2019
 * Github                 : https://github.com/Joennuh/Dice-Tower
 * Wiki                   : https://github.com/Joennuh/Dice-Tower/wiki
 * 
 * This sketch is meant for a Dice Tower. It is a sketch for a Wemos D1 mini or a MH-ET LIVE MiniKit ESP32.
 * It drives 2 red leds for the eyes of a skull and 3 leds for a campfire. Also there is 1 button to
 * initiate blinking eyes and 1 button to toggle between steady or flickering / blinking lights.
 * Although it is developed for WiFi capable Arduino boards the WiFi capabilities aren't used.
 * On the MH-ET LIVE MiniKit ESP32 there are extra functionalities like an monochrome OLED display.
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
 * Hardware configuration (after the slash are the GPIO pins on MH-ET LIVE MiniKit ESP32):
 * - Wemos D1 mini / MH-ET LIVE MiniKit ESP32
 * - 3 yellow leds (each attached with 100R resistor to D6, D7 and D8 / 19, 23 and 5)
 * - 2 red leds (each attached with 100R resistor to D1 and D2 / 22 and 21)
 * - 1 button (attached with external 4,7K pull-up resistor to D5 / 18)
 * - 1 any kind of switch to trigger blinking eyes (attached to D3 / 17)
 * 
 * On the MH-ET LIVE MiniKit ESP32 there is extra hardware to be added:
 * - SSD1306 I2C 128x64 monochrome OLED display (SCK to GPIO 27, SDA to GPIO 25, software driven)
 * - 3 additional tactile pushbuttons with 3 4.7K external pull-up resistor
 *    - Up-button on GPIO 32
 *    - Select / enter / back /edit button on GPIO 12
 *    - Down-button on GPIO 4
************************************************************************************************************/
// Sketch metadata. Please do not change the following lines unless you plan to release an fork. In that case please add some information about you to these lines.
#define PROG_NAME "Dice Tower"
#define PROG_VERSION "0.1.0000"
#define PROG_MANUFACTURER "The Big Site"

// == INCLUDES ============================================================================================
// Button2: button debounce handler
#include <Button2.h>

// The following will only be included on a MH-ET LIVE MiniKit ESP32
#ifdef ESP32
// ArduinoMenu: menu interface
#include <menu.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialIO.h>
#include <menuIO/stringIn.h>

// Images
#include "images.h"
#endif

// == DEFINES =============================================================================================
// You can change the values of this defines but it is advisable to not do this.

#ifdef ESP32
// Define pin assignment for MH-ET LIVE MiniKit ESP32
#define LED_CONFIG 26
#define LED_EYE1 22
#define LED_EYE2 21
#define LED_FIRE1 19
#define LED_FIRE2 23
#define LED_FIRE3 5
#define BTN_TRIGGER 17
#define BTN_CONFIG 18
#define ANALOG_RANDOMSEED 36 // Leave this pin unconnected, the noise of this pin is used for the random creator

// Additional configuration for MH-ET LIVE MiniKit ESP32
#define SCREEN_SCK 27
#define SCREEN_SDA 25
#define BTN_UP 35
#define BTN_SELECT 33
#define BTN_DOWN 34
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
// Setting PWM properties (only for MH-ET LIVE MiniKit ESP32)
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
// Define PWM channel for MH-ET LIVE MiniKit ESP32
const int pwmEyesChannel = 0;
#endif

// FIRE LEDS
const int fireMinIntensity = 0; // Minimum intensity for campfire flickering on a scale of 0 - 255.
const int fireMaxIntensity = 255; // Maximum intensity for campfire flickering on a scale of 0 - 255
const unsigned long fireFlickeringSpeed = 75; // Interval in milliseconds before a new random intensity will be set for a campfire led.


#ifdef ESP32
// Define PWM channel for for MH-ET LIVE MiniKit ESP32
const int pwmFire1Channel = 1;
const int pwmFire2Channel = 2;
const int pwmFire3Channel = 3;
#endif

// CONFIGURATION LED
const int configLedSingleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on after a single click on the configuration button.
const int configLedLongClickDurationOn = 1000; // How long in milliseconds should the configuration led stay on after a long click on the configuration button.
const int configLedDoubleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on in the on state of blinking after a double click on the configuration button.
const int configLedDoubleClickDurationOff = 200; // How long in milliseconds should the configuration led stay on in the on state of blinking after a double click on the configuration button.

#ifdef ESP32
// Only applicable to OLED screen on MH-ET LIVE MiniKit ESP32
int screenContrast = 255; // OLED screen contrast 
#endif

// == CONFIGURATION =======================================================================================
// These settings are needed to let the sketch work correctly but should not be changed!

// -- BUTTONS ----------------------------------------------------------------------------------------------
Button2 btnTrigger(BTN_TRIGGER, INPUT_PULLUP,1); // Activate internal pull-up resistor of Wemos D1 mini pin D3 / MH-ET LIVE MiniKit ESP32 pin 17
Button2 btnConfig(BTN_CONFIG); // Uses external 4,7K pull-up resistor

#ifdef ESP32
// Button configuration only for MH-ET LIVE MiniKit ESP32
Button2 btnUp(BTN_UP); // Uses external 4,7K pull-up resistor
Button2 btnSelect(BTN_SELECT); // Uses external 4,7K pull-up resistor
Button2 btnDown(BTN_DOWN); // Uses external 4,7K pull-up resistor
#endif

// -- SEVERAL STATE VALUES --------------------------------------------------------------------------------
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

// -- SCREEN ---------------------------------------------------------------------------------------------
#ifdef ESP32
#define MAX_DEPTH 5
#define fontName u8g2_font_7x13_mf
#define fontX 7
#define fontY 16
#define offsetX 3
#define offsetY 0
#define U8_Width 128
#define U8_Height 64
U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, SCREEN_SCK, SCREEN_SDA);
#endif

// == MENU (ONLY ON MH-ET LIVE MINIKIT ESP32) =============================================================
#ifdef ESP32
constText* constMEM textFilter MEMMODE=" .0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTWXYZ";
constText* constMEM textMask[] MEMMODE={textFilter};//this mask will repear till the end of the field
char deviceName[]="           ";//<-- menu will edit this text

// define menu colors --------------------------------------------------------
//each color is in the format:
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
// this is a monochromatic color table
const colorDef<uint8_t> colors[] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,1},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{1,1},{1,0,0}},//titleColor
};

result doAlert(eventMask e, prompt &item);

result showEvent(eventMask e) {
  Serial.print("event: ");
  Serial.println(e);
  return proceed;
}

int test=55;

result action1(eventMask e,navNode& nav, prompt &item) {
  Serial.print("action1 event:");
  Serial.println(e);
  Serial.flush();
  return proceed;
}

result action2(eventMask e) {
  Serial.print("action2 event:");
  Serial.println(e);
  Serial.flush();
  return quit;
}

int selTest=0;
SELECT(selTest,selMenu,"Select",doNothing,noEvent,wrapStyle
  ,VALUE("Zero",0,doNothing,noEvent)
  ,VALUE("One",1,doNothing,noEvent)
  ,VALUE("Two",2,doNothing,noEvent)
);

int chooseTest=-1;
CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,wrapStyle
  ,VALUE("First",1,doNothing,noEvent)
  ,VALUE("Second",2,doNothing,noEvent)
  ,VALUE("Third",3,doNothing,noEvent)
  ,VALUE("Last",-1,doNothing,noEvent)
);

//customizing a prompt look!
//by extending the prompt class
class altPrompt:public prompt {
public:
  altPrompt(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    return out.printRaw(F("special prompt!"),len);;
  }
};

MENU(subMenu,"Sub-Menu",doNothing,anyEvent,wrapStyle
  ,OP("Sub1",showEvent,enterEvent)
  ,OP("Sub2",showEvent,enterEvent)
  ,OP("Sub3",showEvent,enterEvent)
  ,altOP(altPrompt,"",showEvent,enterEvent)
  ,EXIT("<Back")
);

MENU(screenMenu,"Screen",doNothing,anyEvent,wrapStyle
  ,FIELD(screenContrast,"Contrast","",5,255,10,5,doNothing,noEvent,wrapStyle)
  ,EXIT("<Back")
);

MENU(deviceMenu,"Device",doNothing,anyEvent,wrapStyle
  ,SUBMENU(screenMenu)
  ,EDIT("Name",deviceName,textMask,doNothing,noEvent,noStyle)
  ,EXIT("<Back")
);

uint16_t hrs=0;
uint16_t mins=0;

//define a pad style menu (single line menu)
//here with a set of fields to enter a date in YYYY/MM/DD format
altMENU(menu,menuTime,"Time",doNothing,noEvent,noStyle,(systemStyles)(_asPad|Menu::_menuData|Menu::_canNav|_parentDraw)
  ,FIELD(hrs,"",":",0,23,1,0,doNothing,noEvent,noStyle)
  ,FIELD(mins,"","",0,59,10,1,doNothing,noEvent,wrapStyle)
);

char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,OP("Op1",action1,anyEvent)
  ,OP("Op2",action2,enterEvent)
  ,SUBMENU(menuTime)
  ,SUBMENU(deviceMenu)
  ,SUBMENU(subMenu)
  ,SUBMENU(selMenu)
  ,SUBMENU(chooseMenu)
  ,OP("Alert test",doAlert,enterEvent)
  ,EXIT("<Back")
);

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
  ,SERIAL_OUT(Serial)
  //must have 2 items at least
);

stringIn<0> strIn;//buffer size: 2^5 = 32 bytes, eventually use 0 for a single byte
serialIn serial(Serial);
// use this commented lines if you want your stringIn object to be used as part or normal menu input
// menuIn* inputsList[]={&serial,&strIn};
// chainStream<sizeof(inputsList)> in(inputsList);
// NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);
NAVROOT(nav,mainMenu,MAX_DEPTH,serial,out);

result alert(menuOut& o,idleEvent e) {
  if (e==idling) {
    o.setCursor(0,0);
    o.print("alert test");
    o.setCursor(0,1);
    o.print("[select] to continue...");
  }
  return proceed;
}

result doAlert(eventMask e, prompt &item) {
  nav.idleOn(alert);
  return proceed;
}

//when menu is suspended
result idle(menuOut& o,idleEvent e) {
  o.clear();
  switch(e) {
    case idleStart:o.println("suspending menu!");break;
    case idling:o.println("suspended...");break;
    case idleEnd:o.println("resuming menu.");break;
  }
  return proceed;
}
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

#ifdef ESP32
    // Menu navigation for MH-ET LIVE MiniKit ESP32
    btnSelect.setLongClickHandler([](Button2 & b) {
        // Select
        unsigned int time = b.wasPressedFor();
        if (time >= 1000) {
           Serial.println("Button: escape");
           nav.doNav(escCmd);
        }
    });
    
    btnSelect.setClickHandler([](Button2 & b) {
       Serial.println("Button: enter");
       nav.doNav(enterCmd);
    });

    btnUp.setClickHandler([](Button2 & b) {
       Serial.println("Button: up (downCmd)");
       nav.doNav(downCmd);
    });

    btnDown.setClickHandler([](Button2 & b) {
      Serial.println("Button: down (upCmd)");
       nav.doNav(upCmd);
    });
#endif
}

// The following functions handles the button presses
void button_loop()
{
    btnTrigger.loop();
    btnConfig.loop();
    btnSelect.loop();
    btnUp.loop();
    btnDown.loop();
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

// -- SCREEN (ONLY ON MH-ET LIVE MINIKIT ESP32) ----------------------------------------------------------
#ifdef ESP32
  Serial.print("Setting up U8G2 display... ");
  u8g2.begin();
  u8g2.setFont(fontName);
  Serial.println("DONE");

  Serial.print("Sending image to display... ");
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, 128, 64, logoDiceTower);
  } while ( u8g2.nextPage() );
  Serial.println("DONE");
  nav.idleTask=idle;//point a function to be used when menu is suspended
#endif

// -- BUTTONS ---------------------------------------------------------------------------------------------
  Serial.print("Initializing buttons... ");
  // Intialize buttons
  button_init();
  Serial.println("DONE");

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

  // -- ARDUINOMENU (ONLY ON MH-ET LIVE MINIKIT ESP32) ----------------------------------------------------
#ifdef ESP32
   //if stringIn is a regular input then we should write to it here, before poll
  // strIn.write(...);//just put the character you want to send
  // nav.poll();//also do serial or stringIn input
  // or deal with charater input directly... (if you have your own input driver)
  if (Serial.available()) {
    //of course menu can read from Serial or even stringIn (se above how to use stringIn as a regular menu input)
    //but here we demonstrate the use of stringIn in direct call, by writing the data to stream and then call doInput with that stream
    if (strIn.write(Serial.read()))//so we just transfer data from serial to strIn
      nav.doInput(strIn);//and then let target parse input
  }
  //nav.doOutput();//if not doing poll the we need to do output "manualy"
  if (nav.changed(0)) {//only draw if menu changed for gfx device
    //change checking leaves more time for other tasks
    u8g2.firstPage();
    do{
      nav.doOutput();
      u8g2.setContrast(screenContrast);
    } while( u8g2.nextPage() );
  }
#endif

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
