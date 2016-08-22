#define LED_CAPSLOCK          (1 << 1)
#define KEY_R                 21
#define KEY_3                 32
const int ledPin            = 13;
uint8_t keyBuffer[8]        = { 0, 0, 0, 0, 0, 0, 0 };
const uint8_t KEYBOARD_LED  = LED_CAPSLOCK; 
uint8_t lastState           = 0, currentState = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

uint8_t readLedStatus(){
  uint8_t keyBuffer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };  
  uint8_t ledStatus;
  Serial.write(keyBuffer, 8);
  while (Serial.available() > 0) {
  ledStatus = Serial.read();
  }
  return ledStatus;
}

boolean buttonPressed(){
  uint8_t ledStatus;
  ledStatus = readLedStatus();
  lastState = currentState;
  currentState = ledStatus & KEYBOARD_LED;  
  if (ledStatus & KEYBOARD_LED){
    digitalWrite(ledPin, HIGH);    
  }else{
    digitalWrite(ledPin, LOW);
  }        
  return (currentState != lastState);
}

void pressR(){
  keyBuffer[2] = KEY_R;
  Serial.write(keyBuffer, 8);
  keyBuffer[2] = 0;
  Serial.write(keyBuffer, 8);
}

void press3(){
  keyBuffer[2] = KEY_3;
  Serial.write(keyBuffer, 8);
  keyBuffer[2] = 0;
  Serial.write(keyBuffer, 8);
}

void loop(){
  int counter = 0;
  if (buttonPressed()) counter = counter +1;
  while (counter == 1) {
    pressR();
    delay(200);
    if(buttonPressed()){
      counter = 0;
      break;
    }
    pressR();
    delay(200);
    if(buttonPressed()){
      counter = 0;
      break;
    }
    press3();
    delay(200);
    if(buttonPressed()){
      counter = 0;
      break;
    }
  }
}
