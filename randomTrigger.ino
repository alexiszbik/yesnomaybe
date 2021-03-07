
#define CLOCK_IN 0

#define LED_OUT_START 2
#define POT_START 1

#define LED_COUNT 5

const byte outputCount = 5;
bool state = false;

void setup() {
  
  Serial.begin(9600);

  for (byte i = 0; i < LED_COUNT; i++) {
    byte pinPosition = LED_OUT_START + i*2;
    pinMode(pinPosition, OUTPUT);
    pinMode(pinPosition  +1, OUTPUT);
  }
  
  randomSeed(analogRead(7));
}

void loop() {


  int clockIn = analogRead(CLOCK_IN);
  bool clockInState = (clockIn > 200);

  if (clockInState != state) {
    
    state = clockInState;
    
    if (clockInState) {

      for (byte i = 0; i < LED_COUNT; i++) {
        long randomValue = random(1024);

        long potValue = analogRead(POT_START + i);

        bool state = potValue >= randomValue;

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
