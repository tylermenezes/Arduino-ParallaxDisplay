Arduino-ParallaxDisplay
=======================

A library for interfacing a Parallax Display module with Arduino.

To-do
-----

The following is a list of planned but still un-implemented features:

  * Sound
  * Scrolling text
  * Custom characters
  * Centering is broken on strings > 16 characters

Use
===

Getting Started
---------------

Start the module by including the header, and creating an instance of the class passing in a reference
of the serial port (on most Arduinos, this will be `&Serial`, but on the Mega it could be any port):

    #include "ParallaxDisplay.h"
    ParallaxDisplay display(&Serial);

Make sure your display is configured at 19,200 baud; there are some DIP switches on the back.

Writing to the Display
----------------------

You have several ways to write to the display:

  * `write_centered(int,char*)` takes a line number, and the string to write. It clears the line, and writes
    the text centered.
  * `write(char*)` takes a string to write at the current location, and advances the current location
  * `write_at(int,int,char*)` takes a row, column, and string of text to write at that location.
  * `clear()` clears the display
  * `clear_line(int)` clears a line on the display
  * `move_down()`, `move_up()`, `move_left()`, and `move_right()` move the cursor location a single step.
  * `move_to(int,int)` moves the cursor to a specific location.

`write` and `write_at` will wrap, while `write_centered` does not. Support for scrolling text is planned in
a future release. `write` is the only method which moves the cursor after writing.

Configuring the Display
-----------------------

  * `light_on()` and `light_off()` turn on and off the display backlight
  * `cursor_on()` and `cursor_off()` turn on and off the cursor display
  * `blink_on()` and `blink_off()` turn on and off cursor character blinking
  * `screen_on()` and `screen_off()` turn on and off the screen. While the screen is off, you can still
    write to it, but nothing will be displayed until you turn it back on.

Sound
-----

Not yet implemented