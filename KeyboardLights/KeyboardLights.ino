#include <MIDI.h>
#include <LedControl.h>

#define TRANS_UP_PIN 7
#define TRANS_DOWN_PIN 6
#define DATA_PIN 4
#define CLOCK_PIN 3
#define LOAD_PIN 2

static const int ledPosition[][2] = { {0,0},
                                      {1,0},
                                      {2,0},
                                      {3,0},
                                      {4,0},
                                      {5,0},
                                      {6,0},
                                      {7,0},
                                      {0,1},
                                      {1,1},
                                      {2,1},
                                      {3,1},
                                      {4,1},
                                      {5,1},
                                      {6,1},
                                      {7,1},
                                      {0,3},
                                      {0,2},
                                      {7,2},
                                      {1,2},
                                      {2,2},
                                      {3,2},
                                      {4,2},
                                      {5,2},
                                      {6,2}
                                   };
static const int midiStartPoints[] = {0, 12, 24, 36, 48, 60, 72, 84, 96};
static const int transposeMin = -4;
static const int transposeMax = 4;
boolean noteStateMatrix[121] = { false };
int transUpSwLast;
int transDownSwLast;
int transpose = 0;
LedControl lc = LedControl(DATA_PIN, CLOCK_PIN, LOAD_PIN, 1);

void transposeUp()
{
  if(transpose < transposeMax)
  {
    transpose++;
    transposeDone();
  }
}

void transposeDown()
{
  if(transpose > transposeMin)
  {
    transpose--;
    transposeDone();
  }
}

void transposeDone()
{
  int led = 12 + transpose;
  for(int i = 0; i < 25; i++)
  lc.clearDisplay(0);
  setLED(led, true);
  delay(50);
  refreshLights();
}

void HandleNoteOn(byte channel, byte pitch, byte velocity)
{
  noteStateMatrix[pitch] = (velocity > 0);
  refreshLights();
}

void refreshLights()
{
  int bank = transpose - transposeMin;
  int note = midiStartPoints[bank];
  for(int i = 0; i < 25; i++)
  {
    setLED(i, noteStateMatrix[note]);
    note++;
  }
}

void setLED(int led, boolean lit)
{
  int row = ledPosition[led][0];
  int col = ledPosition[led][1];
  lc.setLed(0, row, col, lit);
}

void setup()
{
  //Serial.begin(115200);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOn);
  pinMode(13, OUTPUT);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(TRANS_UP_PIN, INPUT);
  pinMode(TRANS_DOWN_PIN, INPUT);
  digitalWrite(TRANS_UP_PIN, HIGH);
  digitalWrite(TRANS_DOWN_PIN, HIGH);
  transUpSwLast = digitalRead(TRANS_UP_PIN);
  transDownSwLast = digitalRead(TRANS_DOWN_PIN);
  digitalWrite(13, LOW);
}

void loop()
{
  MIDI.read();
  int transDownSwState = digitalRead(TRANS_DOWN_PIN);
  if((transDownSwState != transDownSwLast) && (transDownSwState == LOW))
  {
    transposeDown();
  }
  transDownSwLast = transDownSwState;
  int transUpSwState = digitalRead(TRANS_UP_PIN);
  if((transUpSwState != transUpSwLast) && (transUpSwState == LOW))
  {
    transposeUp();
  }
  transUpSwLast = transUpSwState;
}
