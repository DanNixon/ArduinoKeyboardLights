ArduinoKeyboardLights
================================

Uses an Arduino and MAX7219 to drive an LED strip which lights keyboard keys in response to notes delivered over MIDI.

An Instructable for this project available [here](http://www.instructables.com/id/Arduino-Keyboard-Learning-Lights-Attachment/).

A demo is available on YouTube [here](http://www.youtube.com/watch?v=LfwVIxyaxYY).

Configuration
-------------
The following code changes must be made boefre using this code:
- Button pin configuration (lines 4 and 5)
  
  Set these to the pin which is connected to your transpose buttons, these pins are pulled high by the Arduino and should be pulled to ground by the buttons.
- MAX7219 pin configuration (lines 6 to 9)
  
  Set these to the respective pins on the MAX7219: DATA_PIN should connect to pin 1 of the MAX IC, CLOCK_PIN to 13 and LOAD_PIN to 12.
- Transpose settings
  
  First set the transposeMax and transposeMin to their correct values, this is the number of valid times you can transpose the keyboard in each direction (e.g. my M-Audio keyboard lets me transpose +/- 4 octaves) (note transposeMax must be positive or 0 and transposeMin must be negative or 0).
  
  Secondly set the midiStartPoints to match your transpose settings, this is an array of integers corresponding to the MIDI note which is produced by the leftmost key at each transpose setting (note this array must be of size transposeMax-transposeMin+1).
- LED indexes
  
  This is an array which defines the row and column for each LED, ordered by keys from left to right (note the size of this array must be equal to the number of keys on your keyboard and each element must be an array of size 2).
- MIDI channel
  
  By default the Arduino is set to pick up note messages on all channels, however you may change channel used to listen on on line 100 of the sketch.
