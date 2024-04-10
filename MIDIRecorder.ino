
// CONSTANT DEFINTIONS

const int clock_pin = 13;
const int clock_inhibit = 14;
const int shift_load = 15;
const int q_h = 16;
const long shift_interval = 250;  // Function will be called once a millisecond

// VARIABLE DECLARATIONS

int i = 0;
int k = 0;
unsigned int keyPress = 0;
unsigned int shift_register_1 = 0;
unsigned int shift_register_2 = 0;
unsigned int shift_register_3 = 0;
unsigned int shift_register_4 = 0;
unsigned int shift_register_5 = 0;
unsigned int shift_register_6 = 0;
unsigned int shift_register_7 = 0;
unsigned int shift_register_8 = 0;
unsigned int shift_register_9 = 0;
unsigned int shift_register_10 = 0;
unsigned int shift_register_11 = 0;

unsigned long previous_time = 0;




void setup() {
    Serial.begin(115200);
    pinMode(clock_pin, OUTPUT);
    pinMode(clock_inhibit, OUTPUT);
    pinMode(shift_load, OUTPUT);
    pinMode(q_h, INPUT);
}

void loop() {
  unsigned long current_time = millis();

  if (current_time - previous_time >= shift_interval)
  {
    previous_time = current_time;
    readSR();

    Serial.print(shift_register_1, BIN);
    //Serial.print(" ");
    //Serial.print(shift_register_2, BIN);
  Serial.println();
  }

}


unsigned int receiveSR ( void ) {
    unsigned int shift_register = 0;

    for (i = 0; i < 8; i++) {
        if (digitalRead(q_h) == HIGH) {
            shift_register = (shift_register << 1) | 1;  // Load output into variable
        } else {
        shift_register = (shift_register << 1) | 0;  // Load output into variable
    }
    

    // Clock toggle
        digitalWrite(clock_pin, HIGH);
        digitalWrite(clock_pin, LOW);
    }

    return shift_register;
}

void readSR( void ) {
    shift_register_1 = 0;
    shift_register_2 = 0;
  //shift_register_3 = 0;
  //shift_register_4 = 0;
  //shift_register_5 = 0;
  //shift_register_6 = 0;
  //shift_register_7 = 0;
  //shift_register_8 = 0;
  //shift_register_9 = 0;
  //shift_register_10 = 0;
  //shift_register_11 = 0;

    digitalWrite(shift_load, LOW); // Load the registers
    digitalWrite(shift_load, HIGH); // Prepare to shift
    digitalWrite(clock_inhibit, LOW); // Clock can now be used

    shift_register_1 = receiveSR();
    //shift_register_2 = receiveSR();
  //shift_register_3 = receiveSR();
  //shift_register_4 = receiveSR();
  //shift_register_5 = receiveSR();
  //shift_register_6 = receiveSR();
  //shift_register_7 = receiveSR();
  //shift_register_8 = receiveSR();
  //shift_register_9 = receiveSR();
  //shift_register_10 = receiveSR();
  //shift_register_11 = receiveSR();

    digitalWrite(clock_inhibit, HIGH); // Disable the clock

    return;
}
