#ifndef BUZZER_DEFINES_H
#define BUZZER_DEFINES_H

// note list for alarm sound
#define C2 65
#define Db2 69
#define D2 73
#define Eb2 78
#define E2 82
#define F2 87
#define Gb2 93
#define G2 98
#define Ab2 104
#define AA2 110
#define Bb2 117
#define B2 123
#define C3 131
#define Db3 139
#define D3 147
#define Eb3 156
#define E3 165
#define F3 175
#define Gb3 185
#define G3 196
#define Ab3 208
#define AA3 220
#define Bb3 233
#define B3 247
#define C4 262
#define Db4 277
#define D4 294
#define Eb4 311
#define E4 330
#define F4 349
#define Gb4 370
#define G4 392
#define Ab4 415
#define AA4 440
#define Bb4 466
#define B4 494
#define C5 523
#define Db5 554
#define D5 587
#define Eb5 622
#define E5 659
#define F5 698
#define Gb5 740
#define G5 784
#define Ab5 831
#define AA5 880
#define Bb5 932
#define B5 988
#define C6 1047
#define Db6 1109
#define D6 1175
#define Eb6 1245
#define E6 1319
#define F6 1397
#define Gb6 1480
#define G6 1568
#define Ab6 1661
#define AA6 1760
#define Bb6 1865
#define B6 1976

// custom type for alarm

typedef struct 
{
    int note;
    int duration;
} sound_t;

#endif