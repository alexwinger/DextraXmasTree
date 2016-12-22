// ///  Programa para navidad
// usa un sensor PIR
// una vil bocina
// un stepper motor


#include "AFMotor.h"

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(48, 2);

#define CONTROL_PIR  A5  // Trigger pin de sensor de presencia
int speakerPin = A4;    // vil cable de bocina (el otro cable a GND) 


int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int tempo = 300;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playSong(void)
{
  int dir = FORWARD;
  
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
      dir = BACKWARD;
    } else {
      playNote(notes[i], beats[i] * tempo);
      
    }
    motor.step(10, dir, SINGLE);
    // pause between notes
    delay(tempo / 2); 
  }
}



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
  pinMode(CONTROL_PIR, INPUT);
  pinMode(speakerPin, OUTPUT);


  motor.setSpeed(100);  // 10 rpm   
  Serial.println("_____ EMPEZANDO ________");
  delay(5000);
}

static long tdelayrand = 0;
static long tstepsrand = 0;

void loop() {
  Serial.println("_____ Loop ________");
  //tdelayrand = random(1000, 3000);
  //tdelayrand = random(180000, 500000);
  //tstepsrand = random(1, 200);
  tdelayrand = 1000;
  tstepsrand = 200;

  if (HIGH == digitalRead(CONTROL_PIR)) {
    #if 0
    Serial.print("Single coil steps, time ms = ");
    Serial.print(tdelayrand);
    Serial.print(" , steps = ");
    Serial.println(tstepsrand);
    motor.step(tstepsrand, FORWARD, SINGLE); 
    delay(tdelayrand);
    motor.step(tstepsrand, BACKWARD, SINGLE);
    #else
    playSong();   /// Music Driven Motion!!!!
    #endif 
  }

#if 0
  Serial.println("Double coil steps");
  motor.step(200, FORWARD, DOUBLE); 
  motor.step(200, BACKWARD, DOUBLE);

  Serial.println("Interleave coil steps");
  motor.step(200, FORWARD, INTERLEAVE); 
  motor.step(200, BACKWARD, INTERLEAVE); 

  Serial.println("Micrsostep steps");
  motor.step(200, FORWARD, MICROSTEP); 
  motor.step(200, BACKWARD, MICROSTEP);
#endif 
}
