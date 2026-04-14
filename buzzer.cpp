#include "Buzzer.h"

#define BUZZER_PIN 13
#define REST 0

// =======================
// SONGS
// =======================
int melody1[] = {
  659,8, 587,8, 370,4, 415,4,
  554,8, 494,8, 294,4, 330,4,
  494,8, 440,8, 277,4, 330,4,
  440,2
};

int tempo1 = 180;
int notes1 = sizeof(melody1) / sizeof(melody1[0]) / 2;
int wholenote1;

int melody2[] = {
  REST,2, 294,4,
  392,-4, 466,8, 440,4,
  392,2, 587,4,
  523,-2
};

int tempo2 = 144;
int notes2 = sizeof(melody2) / sizeof(melody2[0]) / 2;
int wholenote2;

// =======================
// STATE
// =======================
int currentSong = 1;
bool isPlaying = false;

int currentNote = 0;
unsigned long lastNoteTime = 0;
int noteDuration = 0;

bool initialized = false;

// =======================
// INTERNAL UPDATE
// =======================
void updateBuzzer() {
  if (!isPlaying) return;

  unsigned long now = millis();

  int* melody;
  int notes;
  int wholenote;

  if (currentSong == 1) {
    melody = melody1;
    notes = notes1;
    wholenote = wholenote1;
  } else {
    melody = melody2;
    notes = notes2;
    wholenote = wholenote2;
  }

  if (currentNote < notes * 2 && now - lastNoteTime >= noteDuration) {

    int divider = melody[currentNote + 1];

    if (divider > 0)
      noteDuration = wholenote / divider;
    else
      noteDuration = (wholenote / abs(divider)) * 1.5;

    int pitch = melody[currentNote];

    if (pitch == REST)
      noTone(BUZZER_PIN);
    else
      tone(BUZZER_PIN, pitch, noteDuration * 0.9);

    lastNoteTime = now;
    currentNote += 2;
  }

  if (currentNote >= notes * 2) {
    currentNote = 0;
  }
}

// =======================
// MAIN ENTRY POINT
// =======================
void buzzerTask(String cmd) {

  if (!initialized) {
    pinMode(BUZZER_PIN, OUTPUT);

    wholenote1 = (60000 * 4) / tempo1;
    wholenote2 = (60000 * 4) / tempo2;

    initialized = true;
  }
  cmd.toLowerCase();
  cmd.trim();

  if (cmd == "play") {
    isPlaying = true;
    currentNote = 0;
  }
  else if (cmd == "stop") {
    isPlaying = false;
    noTone(BUZZER_PIN);
  }
  else if (cmd == "switch") {
    currentSong = (currentSong == 1) ? 2 : 1;
    currentNote = 0;
  }
  updateBuzzer();
}