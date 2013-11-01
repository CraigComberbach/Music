#ifndef MUSIC_H
#define	MUSIC_H

/************* Semantic Versioning***************/
#define MUSIC_LIBRARY
#define MUSIC_MAJOR	0
#define MUSIC_MINOR	0
#define MUSIC_PATCH	0

/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
/***********State Machine Definitions************/
/*************Function  Prototypes***************/
void Music_Routine(void);
char Set_PWM_Frequency(int frequency, int PWM);
char Set_PWM_Period(int period, int PWM);
char Set_PWM_Duty_Cycle(int dutyCycle, int PWM);

#endif	/* MUSIC_H */
