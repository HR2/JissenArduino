#include "pitches.h"

const int speakerPin = 8;
const int LEDPin[] = {3, 5, 6};

const int micPin = A0;
const int photoRefPin[] = {A1, A2, A3};

const int mic_threshold = 800;
const int photoRef_threshold = 500;

bool prepareFlag = true;

int melody[] = {
  NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_C5,
  NOTE_B4, 0, NOTE_G4,

  NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_G4,
  NOTE_G5, NOTE_E5, NOTE_C5,

  NOTE_B4, NOTE_A4, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_D5,
  NOTE_C5
};

int noteDurations[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2 };

void setup() {
  Serial.begin(9600);
  for ( int i = 0; i < 3; i++) {
    pinMode( LEDPin[i], OUTPUT);
  }
}

void loop() {
  int micValue = analogRead( micPin );
  int photoRefValue[3];
  for ( int i = 0; i < 3; i++) {
    photoRefValue[i] = analogRead( photoRefPin[i] );
  }

  Serial.println( String(micValue) + "/" + String(photoRefValue[0]) + "/" + String(photoRefValue[1]) + "/" + String(photoRefValue[2]) );

  bool photoRefState[] = {false, false, false};
  for ( int i = 0; i < 3; i++) {
    if ( photoRefValue[i] > photoRef_threshold ) {
      photoRefState[i] = true;
    }
  }

  if ( !photoRefState[0] && !photoRefState[1] && !photoRefState[2] ) {
    prepareFlag = true;
  }

  if (prepareFlag) {
    for ( int i = 0; i < 3; i++) {
      if (photoRefState[i]) {
        analogWrite( LEDPin[i], random(127, 255) );
      } else {
        digitalWrite( LEDPin[i], LOW );
      }
    }

    if ( (micValue > mic_threshold) && photoRefState[0] && photoRefState[1] && photoRefState[2] ) {
      prepareFlag = false;
      for ( int i = 0; i < 3; i++) {
        digitalWrite( LEDPin[i] , LOW);
      }
      playMelody();
    }
  }

  delay(20);
}

void playMelody() {
  int noteNum = sizeof melody / sizeof(int);
  for (int thisNote = 0; thisNote < noteNum ; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote] * 1.5;
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
