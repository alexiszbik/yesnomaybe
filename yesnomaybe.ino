
#define CLOCK_IN 0

#define LED_OUT_START 2
#define POT_START 1

#define LED_COUNT 5

#define MODE_PIN 12

byte patternList[][9] = {
    {1,    1},
    {3,    1,1,0},
    {4,    1,1,0,0},
    {4,    1,1,1,0},
    {5,    1,1,0,0,0},
    {5,    1,0,1,0,0},
    {5,    1,1,1,0,0},
    {5,    1,1,0,1,0},
    {5,    1,1,1,1,0},
    {6,    1,1,0,0,0,0},
    {6,    1,0,1,0,0,0},
    {6,    1,1,1,0,0,0},
    {6,    1,1,0,1,0,0},
    {6,    1,0,1,1,0,0},
    {6,    1,1,1,1,0,0},
    {6,    1,1,1,0,1,0},
    {6,    1,1,1,1,1,0},
    {7,    1,1,0,0,0,0,0},
    {7,    1,0,1,0,0,0,0},
    {7,    1,1,1,0,0,0,0},
    {7,    1,0,0,1,0,0,0},
    {7,    1,1,0,1,0,0,0},
    {7,    1,0,1,1,0,0,0},
    {7,    1,1,1,1,0,0,0},
    {7,    1,1,0,0,1,0,0},
    {7,    1,0,1,0,1,0,0},
    {7,    1,1,1,0,1,0,0},
    {7,    1,1,0,1,1,0,0},
    {7,    1,0,1,1,1,0,0},
    {7,    1,1,1,1,1,0,0},
    {7,    1,1,0,1,0,1,0},
    {7,    1,1,1,1,0,1,0},
    {7,    1,1,1,0,1,1,0},
    {7,    1,1,1,1,1,1,0},
    {8,    1,1,0,0,0,0,0,0},
    {8,    1,0,1,0,0,0,0,0},
    {8,    1,1,1,0,0,0,0,0},
    {8,    1,0,0,1,0,0,0,0},
    {8,    1,1,0,1,0,0,0,0},
    {8,    1,0,1,1,0,0,0,0},
    {8,    1,1,1,1,0,0,0,0},
    {8,    1,1,0,0,1,0,0,0},
    {8,    1,0,1,0,1,0,0,0},
    {8,    1,1,1,0,1,0,0,0},
    {8,    1,0,0,1,1,0,0,0},
    {8,    1,1,0,1,1,0,0,0},
    {8,    1,0,1,1,1,0,0,0},
    {8,    1,1,1,1,1,0,0,0},
    {8,    1,0,1,0,0,1,0,0},
    {8,    1,1,1,0,0,1,0,0},
    {8,    1,1,0,1,0,1,0,0},
    {8,    1,0,1,1,0,1,0,0},
    {8,    1,1,1,1,0,1,0,0},
    {8,    1,0,1,0,1,1,0,0},
    {8,    1,1,1,0,1,1,0,0},
    {8,    1,1,0,1,1,1,0,0},
    {8,    1,0,1,1,1,1,0,0},
    {8,    1,1,1,1,1,1,0,0},
    {8,    1,1,1,0,1,0,1,0},
    {8,    1,1,0,1,1,0,1,0},
    {8,    1,1,1,1,1,0,1,0},
    {8,    1,1,1,1,0,1,1,0},
    {8,    1,1,1,1,1,1,1,0}
};

byte patternCount;

const byte outputCount = 5;
bool state = false;

byte patternSteps[LED_COUNT];

void setup() {

  patternCount = sizeof(patternList)/sizeof(patternList[0]);
  
  Serial.begin(9600);

  for (byte i = 0; i < LED_COUNT; i++) {
    byte pinPosition = LED_OUT_START + i*2;
    pinMode(pinPosition, OUTPUT);
    pinMode(pinPosition  +1, OUTPUT);
    patternSteps[i] = 0;
  }

  pinMode(MODE_PIN, INPUT_PULLUP);
  
  randomSeed(analogRead(7));
}

void loop() {

  int clockIn = analogRead(CLOCK_IN);
  bool clockInState = (clockIn > 200);

  int patternMode = digitalRead(MODE_PIN);
  Serial.println(patternMode);

  if (clockInState != state) {
    
    state = clockInState;
    
    if (clockInState) {

      for (byte i = 0; i < LED_COUNT; i++) {
        bool state = false;

        if (patternMode == LOW) {
          long potIndex = analogRead(POT_START + i); 
          potIndex = map(potIndex, 0, 1024, 0, patternCount);
          
          byte* pattern = patternList[potIndex];

          state = pattern[patternSteps[i] + 1] > 0; // + 1 cause index 0 is for the array length

          patternSteps[i] = (patternSteps[i] + 1) % pattern[0];
        } else {
          long randomValue = random(1024);

          long potValue = analogRead(POT_START + i);

          state = potValue >= randomValue;
        }

        byte pinPosition = LED_OUT_START + i*2;
        digitalWrite(pinPosition, state ? HIGH : LOW);
        digitalWrite(pinPosition + 1, state ? HIGH : LOW);
        
      }
 
    } else {
      for (byte i = 0; i < LED_COUNT; i++) {
        byte pinPosition = LED_OUT_START + i*2;
        digitalWrite(pinPosition, LOW);
        digitalWrite(pinPosition + 1, LOW);
      }
    }
  }

  
}
