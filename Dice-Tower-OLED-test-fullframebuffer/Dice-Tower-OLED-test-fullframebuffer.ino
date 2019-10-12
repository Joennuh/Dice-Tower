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

#include <plugin/barField.h>

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
#define LED_DISPLAY_INDICATOR 14 // 32
#define SCREEN_SCK 27
#define SCREEN_SDA 25
#define BTN_UP 35 // With external pull-up since GPIO 34 - 39 don't have internal pull-up. See https://desire.giesecke.tk/index.php/2018/07/06/reserved-gpios/
#define BTN_SELECT 33 // Has internal pull-up
#define BTN_DOWN 34 // With external pull-up since GPIO 34 - 39 don't have internal pull-up. See https://desire.giesecke.tk/index.php/2018/07/06/reserved-gpios/
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
int eyeIdleIntensity = 20; // Idle intensity for the eyes on a scale of 0 to 255
int eyeActiveIntensity = 255; // Active intensity for the eyes on a scale of 0 to 255
int eyeActiveDuration = 3000; // How long the eyes should stay active on a detected dice. In milliseconds.

int eyeBlinkShortOn = 100; // Duration of the on state while blinking. In milliseconds.
int eyeBlinkShortOff = 100; // Duration of the off state while blinking. In milliseconds.
int eyeBlinkAmount = 3; // How much blinks of the eyes during the blink state on a detected dice.

#ifdef ESP32
// Define PWM channel for MH-ET LIVE MiniKit ESP32
const int pwmEyesChannel = 0;
#endif

// FIRE LEDS
int fireMinIntensity = 0; // Minimum intensity for campfire flickering on a scale of 0 - 255.
int fireMaxIntensity = 255; // Maximum intensity for campfire flickering on a scale of 0 - 255
unsigned long fireFlickeringSpeed = 75; // Interval in milliseconds before a new random intensity will be set for a campfire led.


#ifdef ESP32
// Define PWM channel for for MH-ET LIVE MiniKit ESP32
const int pwmFire1Channel = 1;
const int pwmFire2Channel = 2;
const int pwmFire3Channel = 3;
#endif

// CONFIGURATION LED
int configLedSingleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on after a single click on the configuration button.
int configLedLongClickDurationOn = 1000; // How long in milliseconds should the configuration led stay on after a long click on the configuration button.
int configLedDoubleClickDurationOn = 200; // How long in milliseconds should the configuration led stay on in the on state of blinking after a double click on the configuration button.
int configLedDoubleClickDurationOff = 200; // How long in milliseconds should the configuration led stay off in the on state of blinking after a double click on the configuration button.

/********************************************************************************************************* 
 *  THE FOLLOWING SETTINGS ARE ONLY APPLICABLE TO THE MH-ET LIVE MINIKIT ESP32!
*********************************************************************************************************/
#ifdef ESP32
//  SCREEN SETTINGS
int screenContrast = 255; // OLED screen contrast
unsigned long screenI2CBusSpeed = 0; // Adjust I2C bus speed. Set to 0 to use defaults. Described on https://github.com/olikraus/u8g2/wiki/u8g2reference#setbusclock
int screenMode = 0; // 0 = Dice detection, 1 = Virtual dice

// DISPLAY INDICATOR LED
int diLedMode = 0; // 0 = Reply to button presses, 1 = continous on, 2 = off
int diLedIdleIntensity = 255; // Idle intensity of display indicator led
int diLedActiveIntensity = 10; // Active intensity of display indicator led
int diLedSingleClickDurationOff = 300; // How long in milliseconds should the display indicator led stay off after a single click on one of the buttons on the display module.
int diLedLongClickDurationOff = 1000; // How long in milliseconds should the display indicator led stay off after a long click on one of the buttons on the display module.
int diLedDoubleClickDurationOff = 200; // How long in milliseconds should the display indicator led stay off in the on state of blinking after a double click on one of the buttons on the display module.
int diLedDoubleClickDurationOn = 200; // How long in milliseconds should the display indicator led stay on in the on state of blinking after a double click on one of the buttons on the display module.
const int pwmDilChannel = 15;

// VIRTUAL DICE SETTINGS
int selectedDiceType = 2;
// 0 = Cube
// 1 = Octahedron
// 2 = Mansions of madness
// 3 = Dodecahedron
// 4 = Icosahedron 1 - 10
// 5 = Icosahedron 1 - 20

int selectedAmountOfDices = 4;
// It is shifted with 1 downwards, so:
// 0 = 1 dice (minimum)
// 1 = 2 dices
// (...)
// 6 = 7 dices (maximum)
#endif

// == CONFIGURATION =======================================================================================
// These settings are needed to let the sketch work correctly but should not be changed!

// -- BUTTONS ----------------------------------------------------------------------------------------------
Button2 btnTrigger(BTN_TRIGGER, INPUT_PULLUP,1); // Activate internal pull-up resistor of Wemos D1 mini pin D3 / MH-ET LIVE MiniKit ESP32 pin 17
Button2 btnConfig(BTN_CONFIG); // Uses external 4,7K pull-up resistor

#ifdef ESP32
// Button configuration only for MH-ET LIVE MiniKit ESP32
Button2 btnUp(BTN_UP, INPUT, 10); // Use external pull-up
Button2 btnSelect(BTN_SELECT, INPUT_PULLUP, 10); // Use internal pull-up
Button2 btnDown(BTN_DOWN, INPUT, 10); // Use external pull-up
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

bool diLedOff = false; // Trigger for within the loop to turn the display indicator led off.
int diLedType = 0; // The sequence how the display indicator led should turn off. 0 = none, 1 = single click, 2 = long click, 3 = double click
unsigned long diLedTimestamp = millis(); // Record default timestamp for thedisplay indicator led logic.
int diLedDoubleClickstate = 0; // Set the initial state for the blinking display indicator led logic. In this case the blink starts with the on (0) state.
int diLedDoubleClickCount = 2; // Set the counter (which got decreased) for the amount of blinks for the display indicator led after a double click.

// Set active states for LED_BUILTIN. On ESP8266 the led is active on LOW, but on ESP32 it is active on HIGH.
#ifdef ESP32
#define ONBOARD_ON HIGH
#define ONBOARD_OFF LOW
#else
#define ONBOARD_ON LOW
#define ONBOARD_OFF HIGH
#endif

// -- SCREEN ---------------------------------------------------------------------------------------------
bool idleActivated = false;

#ifdef ESP32
#define MAX_DEPTH 5
#define fontName u8g2_font_7x13_mf
#define fontX 7
#define fontY 16
#define offsetX 3
#define offsetY 0
#define U8_Width 128
#define U8_Height 64
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCREEN_SCK, SCREEN_SDA);
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

// -- Main menu - Screen mode --------------------------------------------------------------------
CHOOSE(screenMode,screenModeMenu,"Mode: ",doNothing,noEvent,noStyle
  ,VALUE("Dice detect",0,doNothing,noEvent)
  ,VALUE("Virtual dice",1,doNothing,noEvent)
);

// -- Settings - screen --------------------------------------------------------------------------
MENU(screenMenu,"Screen",doNothing,anyEvent,wrapStyle
  ,BARFIELD(screenContrast,"Contrast","",5,255,10,1,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

// -- Settings - eyes ----------------------------------------------------------------------------
MENU(eyesIntensityMenu,"Intensity",doNothing,anyEvent,wrapStyle
  ,BARFIELD(eyeIdleIntensity,"Idle: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,BARFIELD(eyeActiveIntensity,"Active: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(eyesDiceDetectionAdvancedMenu,"Advanced - blink",doNothing,anyEvent,wrapStyle
  ,FIELD(eyeBlinkShortOn,"On: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,FIELD(eyeBlinkShortOff,"Off: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(eyesDiceDetectionMenu,"Dice detection",doNothing,anyEvent,wrapStyle
  ,FIELD(eyeActiveDuration,"Active: ","ms",0,10000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(eyeBlinkAmount,"Blinks: ","",0,10,2,1,doNothing,noEvent,wrapStyle)
  ,SUBMENU(eyesDiceDetectionAdvancedMenu)
  ,EXIT("< Back")
);

MENU(eyesMenu,"Eyes",doNothing,anyEvent,wrapStyle
  ,SUBMENU(eyesIntensityMenu)
  ,SUBMENU(eyesDiceDetectionMenu)
  ,EXIT("< Back")
);

// -- Settings - Campfire ------------------------------------------------------------------------
MENU(campfireIntensityMenu,"Intensity",doNothing,anyEvent,wrapStyle
  ,BARFIELD(fireMinIntensity,"Min: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,BARFIELD(fireMaxIntensity,"Max: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(campfireAdvancedMenu,"Advanced",doNothing,anyEvent,wrapStyle
  ,FIELD(fireFlickeringSpeed,"Speed: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(campfireMenu,"Campfire",doNothing,anyEvent,wrapStyle
  ,SUBMENU(campfireIntensityMenu)
  ,SUBMENU(campfireAdvancedMenu)
  ,EXIT("< Back")
);

// -- Settings - Configuration led ---------------------------------------------------------------
MENU(cfgAdvancedSingleClickMenu,"Single click",doNothing,anyEvent,wrapStyle
  ,FIELD(configLedSingleClickDurationOn,"On: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(cfgAdvancedLongClickMenu,"Long click",doNothing,anyEvent,wrapStyle
  ,FIELD(configLedLongClickDurationOn,"On: ","ms",0,3000,100,10,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(cfgAdvancedDoubleClickMenu,"Double click",doNothing,anyEvent,wrapStyle
  ,FIELD(configLedDoubleClickDurationOn,"On: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,FIELD(configLedDoubleClickDurationOff,"Off: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(cfgLedAdvancedMenu,"Advanced",doNothing,anyEvent,wrapStyle
  ,SUBMENU(cfgAdvancedSingleClickMenu)
  ,SUBMENU(cfgAdvancedLongClickMenu)
  ,SUBMENU(cfgAdvancedDoubleClickMenu)
  ,EXIT("< Back")
);

MENU(cfgLedMenu,"Configuration led",doNothing,anyEvent,wrapStyle
  ,SUBMENU(cfgLedAdvancedMenu)
  ,EXIT("< Back")
);

// -- Settings - Display indicator led -----------------------------------------------------------
MENU(dilAdvancedSingleClickMenu,"Single click",doNothing,anyEvent,wrapStyle
  ,FIELD(diLedSingleClickDurationOff,"Off: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(dilAdvancedLongClickMenu,"Long click",doNothing,anyEvent,wrapStyle
  ,FIELD(diLedLongClickDurationOff,"Off: ","ms",0,3000,100,10,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(dilAdvancedDoubleClickMenu,"Double click",doNothing,anyEvent,wrapStyle
  ,FIELD(diLedDoubleClickDurationOff,"Off: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,FIELD(diLedDoubleClickDurationOn,"On: ","ms",0,1000,50,5,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

MENU(diLedAdvancedMenu,"Advanced",doNothing,anyEvent,wrapStyle
  ,SUBMENU(dilAdvancedSingleClickMenu)
  ,SUBMENU(dilAdvancedLongClickMenu)
  ,SUBMENU(dilAdvancedDoubleClickMenu)
  ,EXIT("< Back")
);

MENU(diLedIntensityMenu,"Intensity",doNothing,anyEvent,wrapStyle
  ,BARFIELD(diLedIdleIntensity,"Idle: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,BARFIELD(diLedActiveIntensity,"Active: ","",0,255,10,1,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

CHOOSE(diLedMode,diLedModeMenu,"Mode: ",doNothing,noEvent,noStyle
  ,VALUE("Re to btn press",0,doNothing,noEvent)
  ,VALUE("Continous on",1,doNothing,noEvent)
  ,VALUE("Continous off",2,doNothing,noEvent)
);

MENU(diLedMenu,"Display ind. led",doNothing,anyEvent,wrapStyle
  ,SUBMENU(diLedModeMenu)
  ,SUBMENU(diLedIntensityMenu)
  ,SUBMENU(diLedAdvancedMenu)
  ,EXIT("< Back")
);

// -- Virtual dice menu ---------------------------------------------------------------------------
CHOOSE(selectedDiceType,virtualDiceTypeMenu,"Type: ",doNothing,noEvent,noStyle
  ,VALUE("Cube",0,doNothing,noEvent)
  ,VALUE("Octahedron",1,doNothing,noEvent)
  ,VALUE("Mansions of madness",2,doNothing,noEvent)
  ,VALUE("Dodecahedron",3,doNothing,noEvent)
  ,VALUE("Icosahedron 1 - 10",4,doNothing,noEvent)
  ,VALUE("Icosahedron 1 - 20",5,doNothing,noEvent)
);

CHOOSE(selectedAmountOfDices,virtualDiceAmountMenu,"Dices: ",doNothing,noEvent,noStyle
  ,VALUE("1",0,doNothing,noEvent)
  ,VALUE("2",1,doNothing,noEvent)
  ,VALUE("3",2,doNothing,noEvent)
  ,VALUE("4",3,doNothing,noEvent)
  ,VALUE("5",4,doNothing,noEvent)
  ,VALUE("6",5,doNothing,noEvent)
  ,VALUE("7",6,doNothing,noEvent)
);

MENU(virtualDiceMenu,"Virtual dice",doNothing,anyEvent,wrapStyle
  ,SUBMENU(virtualDiceTypeMenu)
  ,FIELD(selectedAmountOfDices,"Dices: ","",0,7,2,1,doNothing,noEvent,wrapStyle)
  ,EXIT("< Back")
);

// -- Settings menu -------------------------------------------------------------------------------
MENU(settingsMenu,"Settings",doNothing,anyEvent,wrapStyle
  ,SUBMENU(screenModeMenu)
  ,SUBMENU(eyesMenu)
  ,SUBMENU(campfireMenu)
  ,SUBMENU(cfgLedMenu)
  ,SUBMENU(diLedMenu)
  ,SUBMENU(screenMenu)
  ,EXIT("< Back")
);

char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,SUBMENU(settingsMenu)
  ,SUBMENU(virtualDiceMenu)
  ,OP("Show splash",doNothing,noEvent)
  ,EXIT("< Exit")
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
  if(e == idleStart)
  {
    //o.clear();
    Serial.println("--> idleStart");
    idleActivated=true;
  }
  if(e == idling)
  {
      Serial.println("--> idling");
//    u8g2.firstPage();
//    do{
//      u8g2.drawStr(0,64,"Dice detected!");
//      u8g2.drawRFrame(44,5,40,40,5);
//      //u8g2.drawDisc(49,10,3,U8G2_DRAW_ALL); // x, y, radius, draw everyhing
//    } while( u8g2.nextPage() );
    //nav.idleChanged=true; // Keep on calling the idle function. For documentation see: https://github.com/neu-rah/ArduinoMenu/wiki/Idling
  }
  if(e == idleEnd)
  {
    Serial.println("--> idleEnd");
    idleActivated=false;
    //o.clear();
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
           diLedTimestamp = millis();
           diLedOff = true;
           diLedType = 2;
           diLedDoubleClickstate = 1;
           diLedDoubleClickCount = 2;
           nav.doNav(escCmd);
        }
    });

    btnSelect.setDoubleClickHandler([](Button2 & b) {
       diLedTimestamp = millis();
       diLedOff = true;
       diLedType = 3;
       diLedDoubleClickstate = 1;
       diLedDoubleClickCount = 2;
       Serial.print("Select double click activated! Timestamp: ");
       Serial.println(diLedTimestamp);
    });
    
    btnSelect.setClickHandler([](Button2 & b) {
       Serial.println("Button: enter");
       diLedTimestamp = millis();
       diLedOff = true;
       diLedType = 1;
       diLedDoubleClickstate = 0;
       diLedDoubleClickCount = 2;
       nav.doNav(enterCmd);
    });

    btnUp.setClickHandler([](Button2 & b) {
       Serial.println("Button: up (downCmd)");
       diLedTimestamp = millis();
       diLedOff = true;
       diLedType = 1;
       diLedDoubleClickstate = 0;
       diLedDoubleClickCount = 2;
       nav.doNav(downCmd);
    });

    btnDown.setClickHandler([](Button2 & b) {
       Serial.println("Button: down (upCmd)");
       diLedTimestamp = millis();
       diLedOff = true;
       diLedType = 1;
       diLedDoubleClickstate = 0;
       diLedDoubleClickCount = 2;
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
  if(screenI2CBusSpeed > 0)
  {
    Serial.print("Configuring bus speed at ");
    Serial.print(screenI2CBusSpeed);
    Serial.print(" Hz...");
    u8g2.setBusClock(screenI2CBusSpeed);
    Serial.println("DONE");
  }
  Serial.print("Setting up U8G2 display... ");
  u8g2.begin();
  u8g2.setFont(fontName);
  Serial.println("DONE");

  Serial.print("Sending image to display... ");
  u8g2.clearBuffer();
  u8g2.drawXBMP(0, 0, 128, 64, logoDiceTower);
  u8g2.sendBuffer();
  Serial.println("DONE");
  nav.idleTask=idle;//point a function to be used when menu is suspended
  nav.idleOn(idle); // Directly enable idle screen with dice detector screen
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
  
  Serial.print("Attach led fire 1 to PWM channel for it... ");
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
  
  Serial.print("Attach led fire 2 to PWM channel for it... ");
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
  
  Serial.print("Attach led fire 3 to PWM channel for it... ");
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

// -- DISPLAY INDICATOR LED ------------------------------------------------------------------------------
#ifdef ESP32
  // With the lack of analogWrite() function for ESP32 use PWM with the ledc... functions on MH TH LIVE MiniKit ESP32
  Serial.print("Configure PWM channel for display indiciator led... ");
  ledcSetup(pwmDilChannel, pwmFreq, pwmResolution);
  Serial.println("DONE");
  
  Serial.print("Attach display indiciator led to PWM channel for it... ");
  ledcAttachPin(LED_DISPLAY_INDICATOR, pwmDilChannel);
  Serial.println("DONE");

  Serial.print("Turning display indicator led on... ");
  ledcWrite(pwmDilChannel, 255);
  Serial.println("DONE");

  delay(500);

  Serial.print("Turning display indicator led off... ");
  ledcWrite(pwmDilChannel, diLedIdleIntensity);
  Serial.println("DONE");
  
//  Serial.print("Configure display indicator led... ");
//  pinMode(LED_DISPLAY_INDICATOR,OUTPUT);
//  Serial.println("DONE");
//  Serial.print("Turning display indicator led on...");
//  digitalWrite(LED_DISPLAY_INDICATOR,HIGH);
//  Serial.println("DONE");
//  delay(500);
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

unsigned long updateScreenTimestamp = millis();

void loop() {
  //Serial.print("Loop - millis(): ");
  //Serial.println(millis());
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
    Serial.println("-- Loop: call to nav.changed(0)");
    //change checking leaves more time for other tasks
    u8g2.clearBuffer();
    nav.doOutput();
    u8g2.setContrast(screenContrast);
    u8g2.sendBuffer();
  }
  else if (idleActivated == true){
    //Serial.println("- idleActivated == true");
    if(millis() - updateScreenTimestamp > 500){
      if(eyesOn == true)
      {
          Serial.println("- eyesOn == true");
          u8g2.clearBuffer();
//          u8g2.drawStr(0,64,"Dice detected!");
//          u8g2.drawRFrame(44,5,40,40,5);
//          u8g2.drawDisc(49,10,3,U8G2_DRAW_ALL); // x, y, radius, draw everyhing
          u8g2.drawXBMP(0, 0, 128, 64, imgDiceDetected);
          u8g2.sendBuffer();
      }
      else
      {
          Serial.println("- eyesOn == false");
          u8g2.clearBuffer();
//          u8g2.drawStr(0,64,"Roll a dice");
          u8g2.drawXBMP(0, 0, 128, 64, imgRollADice);
          u8g2.sendBuffer();
      }
      updateScreenTimestamp = millis();
    }
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

#ifdef ESP32
// Display indicator led

  if(diLedMode == 1) // 1 = continous on
  {
    ledcWrite(pwmDilChannel, diLedIdleIntensity);
  }
  else if(diLedMode == 2) // 2 = continous off
  {
    ledcWrite(pwmDilChannel, 0);
  }
  else // 0 or other values = reply to button presses
  {
    if(diLedOff == true)
    {
        Serial.println("loop -> diLedOff == true");
        Serial.print("diLedType: ");
        Serial.println(diLedType);
        // Single click
        if(diLedType == 1){
            Serial.println("diLedType == 1");
            if(millis()- diLedTimestamp <= diLedSingleClickDurationOff)
            {
                Serial.println("millis()- diLedTimestamp <= diLedSingleClickDurationOff");
                ledcWrite(pwmDilChannel, diLedActiveIntensity);
                //digitalWrite(LED_DISPLAY_INDICATOR,LOW);
            }
            else
            {
                Serial.println("millis()- diLedTimestamp > diLedSingleClickDurationOff");
                ledcWrite(pwmDilChannel, diLedIdleIntensity);
                //digitalWrite(LED_DISPLAY_INDICATOR,HIGH);
                diLedTimestamp = millis();
                diLedOff = false;
                diLedType = 0;
            }
        }
        // Long click
        else if(diLedType == 2){
            Serial.println("diLedType == 2");
            if(millis()- diLedTimestamp <= diLedLongClickDurationOff)
            {
                Serial.println("millis()- diLedTimestamp <= diLedLongClickDurationOff");
                ledcWrite(pwmDilChannel, diLedActiveIntensity);
                //digitalWrite(LED_DISPLAY_INDICATOR,LOW);
            }
            else
            {
                Serial.println("millis()- diLedTimestamp > diLedLongClickDurationOff");
                ledcWrite(pwmDilChannel, diLedIdleIntensity);
                //digitalWrite(LED_DISPLAY_INDICATOR,HIGH);
                diLedTimestamp = millis();
                diLedOff = false;
                diLedType = 0;
            }
        }
        // Double click
        else if(diLedType == 3)
        {
            Serial.println("diLedType == 3");
            if(diLedDoubleClickCount > 0)
            {
                Serial.print("millis(): ");
                Serial.print(millis());
                Serial.print(", diLedTimestamp: ");
                Serial.println(diLedTimestamp);
                
                // Led off
                if(diLedDoubleClickstate == 1){
                    Serial.println("diLedDoubleClickstate == 1");
                    if(millis() - diLedTimestamp <= diLedDoubleClickDurationOff)
                    {
                        Serial.println("diLedTimestamp <= diLedDoubleClickDurationOff");
                        ledcWrite(pwmDilChannel, diLedActiveIntensity);
                    }
                    else{
                        Serial.println("diLedTimestamp > diLedDoubleClickDurationOn >> Set diLedDoubleClickstate to 0 and reset timestamp");
                        diLedTimestamp = millis();
                        diLedDoubleClickstate = 0; // Set blink state to off
                    }
                }
                // Led on
                else if(diLedDoubleClickstate == 0){
                    Serial.println("diLedDoubleClickstate == 0");
                    if(millis() - diLedTimestamp <= diLedDoubleClickDurationOn)
                    {
                        Serial.println("diLedTimestamp <= diLedDoubleClickDurationOn");
                        ledcWrite(pwmDilChannel, diLedIdleIntensity);
                    }
                    else{
                        Serial.println("diLedTimestamp > diLedDoubleClickDurationOn >> Set diLedDoubleClickstate to 1, decrease diLedDoubleClickCount and reset timestamp");
                        diLedTimestamp = millis();
                        diLedDoubleClickstate = 1; // Set blink state to on
                        diLedDoubleClickCount--;
                    }
                }
            }
        }
        else
        {
          ledcWrite(pwmDilChannel, diLedIdleIntensity);
        }
    }
    else
    {
      ledcWrite(pwmDilChannel, diLedIdleIntensity);
    }
  }
#endif

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
