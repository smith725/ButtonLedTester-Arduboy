/*
Button & LED Tester
June 28, 2016
Copyright (C) 2016 Chris Smith
All rights reserved.

Simple test program to show proper operation of each button.

Can also turn on RGB led, and control brightness of each component

Provides a model value for "backwards LED"
*/

#include "Arduboy.h"

Arduboy arduboy;

// globals needed every pass through loop

uint8_t lastinput;
uint8_t ledR;
uint8_t ledG;
uint8_t ledB;
uint8_t ledON;

uint8_t hex[]="0123456789abcdef";

// runs once
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // set the framerate to 15
  arduboy.setFrameRate(15);

  // last button press was nothing
  lastinput = 0;

  // LED is off
  ledON = 0;

  // first we clear our screen to black
  arduboy.clear();
}

// main loop
void loop() {

  // loop variables

  uint8_t buttons;
  uint8_t ledRbw;
  uint8_t ledGbw;
  uint8_t ledBbw;

  // wait for the next frame time
  if (!(arduboy.nextFrame()))
    return;

  // fetch all buttons up/down
  buttons = arduboy.buttonsState();

  // left,up,right alone always ups the LED values, but only visible if LED on

  if (!lastinput) {
    if (buttons == LEFT_BUTTON ) { ledR++; }
    if (buttons == UP_BUTTON   ) { ledG++; }
    if (buttons == RIGHT_BUTTON) { ledB++; }

    // A is special - turns LED off, and flushes display
    if (buttons == A_BUTTON && !lastinput) {
      arduboy.clear();
      arduboy.setRGBled(0,0,0);
      ledON = 0;
      }

    // B is special - turns LED on and randoms the setting
    if (buttons == B_BUTTON) {
      arduboy.clear();
      ledR = random(0,255);
      ledG = random(0,255);
      ledB = random(0,255);
      ledON = 1;
      }
    }

  // if lastinput was DOWN by itself, treat as a shift key

  if (lastinput == DOWN_BUTTON) {  
    if (buttons == (LEFT_BUTTON+DOWN_BUTTON))  { ledR+=16; }
    if (buttons == (UP_BUTTON+DOWN_BUTTON))    { ledG+=16; }
    if (buttons == (RIGHT_BUTTON+DOWN_BUTTON)) { ledB+=16; }
    }

  // calculate backward LED apparent brightness based on RGB settings
  // R >> Bbw, and B >> Rbw; any value 1 to 255 attempts to give full brightness
  // value is moderated by G; as G rises to 255, Rbe and Bbw get cut off
  // Gbw is always off

  ledGbw = 0;
  if (!ledB) { ledRbw = 0; } else { ledRbw = 255-ledG; };
  if (!ledR) { ledBbw = 0; } else { ledBbw = 255-ledG; };
  
  // title display is after clear so it should never blink
  arduboy.setCursor(7, 3);
  arduboy.print(F("Button & LED Tester"));

  // show all button statuses
  arduboy.setCursor( 10,15); if (buttons & LEFT_BUTTON ) {arduboy.print(F("\x11" "L" "\x10"));} else  {arduboy.print(F(" L "));};
  arduboy.setCursor( 28,15); if (buttons & UP_BUTTON   ) {arduboy.print(F("\x11" "U" "\x10"));} else  {arduboy.print(F(" U "));};
  arduboy.setCursor( 46,15); if (buttons & RIGHT_BUTTON) {arduboy.print(F("\x11" "R" "\x10"));} else  {arduboy.print(F(" R "));};
  arduboy.setCursor( 64,15); if (buttons & DOWN_BUTTON ) {arduboy.print(F("\x11" "D" "\x10"));} else  {arduboy.print(F(" D "));};
  arduboy.setCursor( 82,15); if (buttons & A_BUTTON    ) {arduboy.print(F("\x11" "A" "\x10"));} else  {arduboy.print(F(" A "));};
  arduboy.setCursor(100,15); if (buttons & B_BUTTON    ) {arduboy.print(F("\x11" "B" "\x10"));} else  {arduboy.print(F(" B "));};

  // show LED values and LEDbw values
  if (!ledON) {
    arduboy.setCursor(0,29);
    arduboy.print(F("LED: B rand+on, A off"));
    }
  else {
    arduboy.setCursor(0,29);
    arduboy.print(F("RGB: L/U/R+1, w/D+16"));

    arduboy.setCursor(0,39);
    arduboy.print(F("#"));
    arduboy.write(hex[ledR>>4]); arduboy.write(hex[ledR&15]);
    arduboy.write(hex[ledG>>4]); arduboy.write(hex[ledG&15]);
    arduboy.write(hex[ledB>>4]); arduboy.write(hex[ledB&15]);
    arduboy.print(F(" <<LED right"));


    arduboy.setCursor(0,49);
    arduboy.print(F("#"));
    arduboy.write(hex[ledBbw>>4]); arduboy.write(hex[ledBbw&15]);
    arduboy.write(hex[ledGbw>>4]); arduboy.write(hex[ledGbw&15]);
    arduboy.write(hex[ledRbw>>4]); arduboy.write(hex[ledRbw&15]);
    arduboy.print(F(" <<LED wrong"));

    arduboy.setRGBled( ledR, ledG, ledB );
    }

  // show all that screen effort
  arduboy.display();

  // remember what was pressed last time
  lastinput = buttons;
}
