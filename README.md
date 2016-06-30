# ButtonLedTester-Arduboy
Button &amp; LED Tester for Arduboy

Displays a single screen, with letters LURD (Left Up Right Down) and A B (fire buttons)

The status of each button pressed is shown with character frames around each letter.

The B button turns on the RGB LED, and sets it randomly. The A button turns it off.

While the LED is on, L U R increase the R G B components by 1, each button for a color component.
If the D button is pressed, it is treated as a shift, and the increase is 16.

Using the buttons, any specific LED RGB value can be created.

A "backward LED estimate" is also shown for those Arduboys (the majority) which have the backward installed LED.

Note that a library issue involving tunes prevents proper operation of the PWM dimming features of the LED.
Colors as indicated will be inaccurate while this issue remains uncorrected.
