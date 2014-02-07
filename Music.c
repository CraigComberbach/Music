#include "p24FJ256GA106.h"

//Magic Numbers
#define Hz      	*1			//Makes defining frequencies and periods a little easier
#define kHz     	*1000		//Makes defining frequencies and periods a little easier
#define MHz     	*1000000	//Makes defining frequencies and periods a little easier
#define mS      	*1000000	//Makes defining frequencies and periods a little easier
#define uS      	*1000		//Makes defining frequencies and periods a little easier
#define nS      	*1			//Makes defining frequencies and periods a little easier
#define FOSC		8000000
#define PRESCALER	1
#define BUZZER		1

#if FOSC > 65536000000  //65.536 GHz
    #error "FOSC is too fast for this code to remain unmodified"
#endif

//Notes in Hz - Reference from http://www.phy.mtu.edu/~suits/notefreqs.html
#define REST		0
#define C0      	16
#define C0_SHARP	17
#define D0_FLAT		17
#define D0			18
#define D0_SHARP	19
#define E0_FLAT		19
#define E0			21
#define F0			22
#define F0_SHARP	23
#define G0_FLAT		23
#define G0			25
#define G0_SHARP	26
#define A0_FLAT		26
#define A0			28
#define A0_SHARP	29
#define B0_FLAT		29
#define B0			31
#define C1      	33
#define C1_SHARP   	35
#define D1_FLAT    	35
#define D1	    	37
#define D1_SHARP   	39
#define E1_FLAT   	39
#define E1		   	41
#define F1		   	44
#define F1_SHARP   	46
#define G1_FLAT	   	46
#define G1		   	49
#define G1_SHARP   	52
#define A1_FLAT   	52
#define A1			55
#define A1_SHARP	58
#define B1_FLAT		58
#define B1			61
#define C2      	65
#define C2_SHARP	69
#define D2_FLAT		69
#define D2      	73
#define D2_SHARP	78
#define E2_FLAT		78
#define E2      	82
#define F2      	87
#define F2_SHARP	93
#define G2_FLAT		93
#define G2      	98
#define G2_SHARP	104
#define A2_FLAT		104
#define A2      	110
#define A2_SHARP	117
#define B2_FLAT		117
#define B2      	123
#define C3      	131
#define C3_SHARP	139
#define D3_FLAT		139
#define	D3      	147
#define	D3_SHARP	156
#define	E3_FLAT		156
#define	E3	    	165
#define	F3	    	175
#define	F3_SHARP	185
#define	G3_FLAT		185
#define	G3	    	196
#define	G3_SHARP	208
#define	A3_FLAT		208
#define	A3	    	220
#define	A3_SHARP	233
#define	B3_FLAT		233
#define	B3	    	247
#define	C4	    	262	//Middle C
#define	C4_SHARP	277
#define	D4_FLAT		277
#define	D4	    	294
#define	D4_SHARP	311
#define	E4_FLAT		311
#define	E4	    	330
#define	F4	    	349
#define	F4_SHARP	370
#define	G4_FLAT		370
#define	G4	    	392
#define	G4_SHARP 	415
#define	A4_FLAT 	415
#define	A4	    	440
#define	A4_SHARP	466
#define	B4_FLAT		466
#define	B4	    	494
#define	C5	    	523
#define	C5_SHARP 	554
#define	D5_FLAT		554
#define	D5	    	587
#define	D5_SHARP 	622
#define	E5_FLAT		622
#define	E5	    	659
#define	F5	    	698
#define	F5_SHARP 	740
#define	G5_FLAT		740
#define	G5	    	784
#define	G5_SHARP	831
#define	A5_FLAT		831
#define	A5	    	880
#define	A5_SHARP	932
#define	B5_FLAT		932
#define	B5	    	988
#define	C6	    	1047
#define	C6_SHARP	1109
#define	D6_FLAT		1109
#define	D6	    	1175
#define	D6_SHARP	1245
#define	E6_FLAT		1245
#define	E6	    	1319
#define	F6  		1397
#define	F6_SHARP	1480
#define	G6_FLAT		1480
#define	G6	    	1568
#define	G6_SHARP 	1661
#define	A6_FLAT 	1661
#define	A6			1760
#define	A6_SHARP 	1865
#define	B6_FLAT 	1865
#define	B6		 	1976
#define	C7	    	2093
#define	C7_SHARP	2217
#define	D7_FLAT		2217
#define	D7			2349
#define	D7_SHARP	2489
#define	E7_FLAT		2489
#define	E7			2637
#define	F7			2794
#define	F7_SHARP	2960
#define	G7_FLAT		2960
#define	G7			3136
#define	G7_SHARP	3322
#define	A7_FLAT		3322
#define	A7			3520
#define	A7_SHARP	3729
#define	B7_FLAT		3729
#define	B7			3951
#define	C8	  	  	4186
#define	C8_SHARP	4435
#define	D8_FLAT		4435
#define	D8			4698
#define	D8_SHARP	4978
#define	E8_FLAT		4978

//Tempo and other global defines
#define EIGHTH	     	100
#define QUARTER     	250
#define HALF			500
#define THREE_QUARTER	750
#define ONE				1000

#define HAPPY_BIRTHDAY
//#define SUPER_MARIO_BROS

#if defined HAPPY_BIRTHDAY
	#define TEMPO   		150
#elif defined SUPER_MARIO_BROS
	#define TEMPO   		EIGHTH	//Super Mario Bros.
#endif

//Function Prototypes
void Music_Routine();
char Set_PWM_Frequency(int frequency, int PWM);
char Set_PWM_Period(int period, int PWM);
char Set_PWM_Duty_Cycle(int dutyCycle, int PWM);

//Global Variables
#if defined HAPPY_BIRTHDAY
const int song[] = {D4,REST,D4,REST,					E4,REST,D4,REST,G4,REST,			F4,REST,REST,REST,D4,REST,D4,REST,
					E4,REST,D4,REST,A5,REST,			G4,REST,REST,REST,D4,REST,D4,REST,
					D5,REST,B5,REST,G4,REST,			F4,REST,E4,REST,C5,REST,C5,REST,
					B5,REST,G4,REST,A5,REST,			G4,REST,REST,REST,REST
					};
#elif defined SUPER_MARIO_BROS
const int song[] = {E5,E5,REST,E5,		REST,C5,E5,REST,	G5,REST,REST,REST,	G4,REST,REST,REST,
					C5,REST,REST,G4,	REST,REST,E4,REST,	REST,A5,REST,B5,	REST,B5_FLAT,A5,REST,
					G4,E5,G5,			B6,REST,F5,G5,		REST,E5,REST,C5,	D5,B5,REST,REST,
					C5,REST,REST,G4,	REST,REST,E4,REST,	REST,A5,REST,B5,	REST,B5_FLAT,A5,REST,
					G4,E5,G5,			B6,REST,F5,G5,		REST,E5,REST,C5,	D5,B5,REST,REST,
					};
#endif

//#warning "Make a sweep function to go from one freq to another (startFreq, endFreq, length) then it will calculte the size of each division and change it once every loop until it has reached its end frequency"
//This function assumes that it is run once every mS
void Music_Routine()
{
    static int  noteCounter = 0,
                currentNote = 0;

    if(++noteCounter >= TEMPO)
    {
        noteCounter = 0;
        if(currentNote < (sizeof(song)/2))
        	++currentNote;
        else
		{
			Set_PWM_Frequency(REST, BUZZER);
			return;
		}
    }

    Set_PWM_Frequency(song[currentNote], BUZZER);

    return;
}

//Send frequency in Hz (use the #define Hz, kHz and Mhz for code readability)
//Returns the module written to, 0 upon failure
//If the frequency sent is too fast, it will default to its absolute maximum frequency (instead of not oscillating at all)
char Set_PWM_Frequency(int frequency, int PWM)
{
    int registerValue;

    //Do some MatheMagic™ to come up with the register value
    registerValue = FOSC / (2 * PRESCALER * frequency) - 1;

	if(frequency == 0)
		registerValue = 0;

    //If the frequency specified is greater than what we can do, set to maxiumum possible frequency!
    if(registerValue == 0)
       registerValue = 1;

    //Assign it to the proper register
    switch(PWM)
    {
        case 1:
            OC1RS = registerValue;
			OC1R = OC1RS/256;
//#warning I need to flush this out somehow! Maybe set it to call the Duty cycle setting function
            return 1;
        case 2:
            OC2RS = registerValue;
            return 2;
        case 3:
            OC3RS = registerValue;
            return 3;
        case 4:
            OC4RS = registerValue;
            return 4;
        case 5:
            OC5RS = registerValue;
            return 5;
        case 6:
            OC6RS = registerValue;
            return 6;
        case 7:
            OC7RS = registerValue;
            return 7;
        case 8:
            OC8RS = registerValue;
            return 8;
        case 9:
        	OC9RS = registerValue;
        	return 9;
        default:
            return 0;
    }
}

//Send the period in nS (use the #defines of nS, uS and mS for code readability)
//Returns the module written to, 0 upon failure
//If the period sent is too short, it will default to its absolute minimum period (instead of not oscillating at all)
char Set_PWM_Period(int period, int PWM)
{
    unsigned int    registerValue;

    //Do some MatheMagic™ to come up with the register value
    registerValue = FOSC / 1000000;//Precondition FOSC so it isn't too big to multiply
    registerValue *= period / (2 * PRESCALER);//Make the conversion
    registerValue /= 1000;//Finish conditioning
    registerValue--;//Finish the conversion

    //If the period specified is less than what we can do, set to maxiumum possible frequency!
    if(registerValue == 0)
       registerValue = 1;

    //Assign it to the proper register
    switch(PWM)
    {
        case 1:
            OC1RS = period;
            return 1;
        case 2:
            OC2RS = period;
            return 2;
        case 3:
            OC3RS = period;
            return 3;
        case 4:
            OC4RS = period;
            return 4;
        case 5:
            OC5RS = period;
            return 5;
        case 6:
            OC6RS = period;
            return 6;
        case 7:
            OC7RS = period;
            return 7;
        case 8:
            OC8RS = period;
            return 8;
        case 9:
            OC9RS = period;
            return 9;
        default:
            return 0;
    }
}


char Set_PWM_Duty_Cycle(int dutyCycle, int PWM)
{
/*    unsigned int registerValue;
#error "what format should dutyCycle be in? percent, decacent? millicent? PPM? other?"
#error "I lose accuracy the lower the period register is...."

    //Do some MatheMagic™ to come up with the register value
    Do something here

    switch(PWM)
    {
        case 1:
            OC1R = registerValue;
            return 1;
        case 2:
            OC2R = registerValue;
            return 2;
        case 3:
            OC3R = registerValue;
            return 3;
        case 4:
            OC4R = registerValue;
            return 4;
        case 5:
            OC5R = registerValue;
            return 5;
        case 6:
            OC6R = registerValue;
            return 6;
        case 7:
            OC7R = registerValue;
            return 7;
        case 8:
            OC8R = registerValue;
            return 8;
        case 9:
            OC9R = registerValue;
            return 9;
        default:
            return 0;
    }*/
    return 0;
}

/********************Generic Output Compare Initialize Routine********************
//It is setup so that a find/replace on "REPLACE_ME" with the name of the peripheral (as defined in "Peripherals Definitions.h") will setup the
//module for generic use. Changing the definition in "Peripherals Definitions.h" will automagically change over the PWM module with zero problems

//Include the PIC header
#include "p24f256ga106"

//Define generic pin swapping
#if REPLACE_ME == 1
    #define OCxCON1.OCSIDL      OC1CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC1CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC1CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC1CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC1CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC1CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC1CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC1CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC1CON1.TRIGMODE
    #define OCxCON1.OCM         OC1CON1.OCM
    #define OCxCON2.FLTMD       OC1CON2.FLTMD
    #define OCxCON2.FLTOUT      OC1CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC1CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC1CON2.OCINV
    #define OCxCON2.DCB         OC1CON2.DCB
    #define OCxCON2.OC32        OC1CON2.OC32
    #define OCxCON2.OCTRIG      OC1CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC1CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC1CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC1CON2.SYNCSEL
    #define OCxR.OCRB           OC1R.OCRB
    #define OCxRS.OCRSB         OC1RS.OCRSB
    #define OCxTMR.TMRB         OC1TMR.TMRB
#elif REPLACE_ME == 2
    #define OCxCON1.OCSIDL      OC2CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC2CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC2CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC2CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC2CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC2CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC2CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC2CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC2CON1.TRIGMODE
    #define OCxCON1.OCM         OC2CON1.OCM
    #define OCxCON2.FLTMD       OC2CON2.FLTMD
    #define OCxCON2.FLTOUT      OC2CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC2CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC2CON2.OCINV
    #define OCxCON2.DCB         OC2CON2.DCB
    #define OCxCON2.OC32        OC2CON2.OC32
    #define OCxCON2.OCTRIG      OC2CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC2CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC2CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC2CON2.SYNCSEL
    #define OCxR.OCRB           OC2R.OCRB
    #define OCxRS.OCRSB         OC2RS.OCRSB
    #define OCxTMR.TMRB         OC2TMR.TMRB
#elif REPLACE_ME == 3
    #define OCxCON1.OCSIDL      OC3CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC3CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC3CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC3CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC3CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC3CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC3CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC3CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC3CON1.TRIGMODE
    #define OCxCON1.OCM         OC3CON1.OCM
    #define OCxCON2.FLTMD       OC3CON2.FLTMD
    #define OCxCON2.FLTOUT      OC3CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC3CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC3CON2.OCINV
    #define OCxCON2.DCB         OC3CON2.DCB
    #define OCxCON2.OC32        OC3CON2.OC32
    #define OCxCON2.OCTRIG      OC3CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC3CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC3CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC3CON2.SYNCSEL
    #define OCxR.OCRB           OC3R.OCRB
    #define OCxRS.OCRSB         OC3RS.OCRSB
    #define OCxTMR.TMRB         OC3TMR.TMRB
#elif REPLACE_ME == 4
    #define OCxCON1.OCSIDL      OC4CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC4CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC4CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC4CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC4CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC4CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC4CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC4CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC4CON1.TRIGMODE
    #define OCxCON1.OCM         OC4CON1.OCM
    #define OCxCON2.FLTMD       OC4CON2.FLTMD
    #define OCxCON2.FLTOUT      OC4CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC4CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC4CON2.OCINV
    #define OCxCON2.DCB         OC4CON2.DCB
    #define OCxCON2.OC32        OC4CON2.OC32
    #define OCxCON2.OCTRIG      OC4CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC4CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC4CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC4CON2.SYNCSEL
    #define OCxR.OCRB           OC4R.OCRB
    #define OCxRS.OCRSB         OC4RS.OCRSB
    #define OCxTMR.TMRB         OC4TMR.TMRB
#elif REPLACE_ME ==
    #define OCxCON1.OCSIDL      OC5CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC5CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC5CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC5CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC5CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC5CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC5CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC5CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC5CON1.TRIGMODE
    #define OCxCON1.OCM         OC5CON1.OCM
    #define OCxCON2.FLTMD       OC5CON2.FLTMD
    #define OCxCON2.FLTOUT      OC5CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC5CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC5CON2.OCINV
    #define OCxCON2.DCB         OC5CON2.DCB
    #define OCxCON2.OC32        OC5CON2.OC32
    #define OCxCON2.OCTRIG      OC5CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC5CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC5CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC5CON2.SYNCSEL
    #define OCxR.OCRB           OC5R.OCRB
    #define OCxRS.OCRSB         OC5RS.OCRSB
    #define OCxTMR.TMRB         OC5TMR.TMRB
#elif REPLACE_ME == 6
    #define OCxCON1.OCSIDL      OC6CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC6CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC6CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC6CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC6CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC6CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC6CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC6CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC6CON1.TRIGMODE
    #define OCxCON1.OCM         OC6CON1.OCM
    #define OCxCON2.FLTMD       OC6CON2.FLTMD
    #define OCxCON2.FLTOUT      OC6CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC6CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC6CON2.OCINV
    #define OCxCON2.DCB         OC6CON2.DCB
    #define OCxCON2.OC32        OC6CON2.OC32
    #define OCxCON2.OCTRIG      OC6CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC6CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC6CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC6CON2.SYNCSEL
    #define OCxR.OCRB           OC6R.OCRB
    #define OCxRS.OCRSB         OC6RS.OCRSB
    #define OCxTMR.TMRB         OC6TMR.TMRB
#elif REPLACE_ME == 7
    #define OCxCON1.OCSIDL      OC7CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC7CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC7CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC7CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC7CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC7CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC7CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC7CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC7CON1.TRIGMODE
    #define OCxCON1.OCM         OC7CON1.OCM
    #define OCxCON2.FLTMD       OC7CON2.FLTMD
    #define OCxCON2.FLTOUT      OC7CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC7CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC7CON2.OCINV
    #define OCxCON2.DCB         OC7CON2.DCB
    #define OCxCON2.OC32        OC7CON2.OC32
    #define OCxCON2.OCTRIG      OC7CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC7CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC7CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC7CON2.SYNCSEL
    #define OCxR.OCRB           OC7R.OCRB
    #define OCxRS.OCRSB         OC7RS.OCRSB
    #define OCxTMR.TMRB         OC7TMR.TMRB
#elif REPLACE_ME == 8
    #define OCxCON1.OCSIDL      OC8CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC8CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC8CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC8CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC8CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC8CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC8CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC8CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC8CON1.TRIGMODE
    #define OCxCON1.OCM         OC8CON1.OCM
    #define OCxCON2.FLTMD       OC8CON2.FLTMD
    #define OCxCON2.FLTOUT      OC8CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC8CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC8CON2.OCINV
    #define OCxCON2.DCB         OC8CON2.DCB
    #define OCxCON2.OC32        OC8CON2.OC32
    #define OCxCON2.OCTRIG      OC8CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC8CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC8CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC8CON2.SYNCSEL
    #define OCxR.OCRB           OC8R.OCRB
    #define OCxRS.OCRSB         OC8RS.OCRSB
    #define OCxTMR.TMRB         OC8TMR.TMRB
#elif REPLACE_ME == 9
    #define OCxCON1.OCSIDL      OC9CON1.OCSIDL
    #define OCxCON1.OCTSEL      OC9CON1.OCTSEL
    #define OCxCON1.ENFLT2      OC9CON1.ENFLT2
    #define OCxCON1.ENFLT1      OC9CON1.ENFLT1
    #define OCxCON1.ENFLT0      OC9CON1.ENFLT0
    #define OCxCON1.OCFLT2      OC9CON1.OCFLT2
    #define OCxCON1.OCFLT1      OC9CON1.OCFLT1
    #define OCxCON1.OCFLT0      OC9CON1.OCFLT0
    #define OCxCON1.TRIGMODE    OC9CON1.TRIGMODE
    #define OCxCON1.OCM         OC9CON1.OCM
    #define OCxCON2.FLTMD       OC9CON2.FLTMD
    #define OCxCON2.FLTOUT      OC9CON2.FLTOUT
    #define OCxCON2.FLTTRIEN    OC9CON2.FLTTRIEN
    #define OCxCON2.OCINV       OC9CON2.OCINV
    #define OCxCON2.DCB         OC9CON2.DCB
    #define OCxCON2.OC32        OC9CON2.OC32
    #define OCxCON2.OCTRIG      OC9CON2.OCTRIG
    #define OCxCON2.TRIGSTAT    OC9CON2.TRIGSTAT
    #define OCxCON2.OCTRIS      OC9CON2.OCTRIS
    #define OCxCON2.SYNCSEL     OC9CON2.SYNCSEL
    #define OCxR.OCRB           OC9R.OCRB
    #define OCxRS.OCRSB         OC9RS.OCRSB
    #define OCxTMR.TMRB         OC9TMR.TMRB
#endif
void initialize_REPLACE_ME()
{
    //Assign to a specific pin (or pins)
     //Unlock remappable pins
     //Assigned remappable pin
     //Lock remappable pins

    //Output Compare Control Register 1
    OCxCON1.OCSIDL = ;      //
    OCxCON1.OCTSEL = ;      //
    OCxCON1.ENFLT2 = ;      //
    OCxCON1.ENFLT1 = ;      //
    OCxCON1.ENFLT0 = ;      //
    OCxCON1.OCFLT2 = ;      //
    OCxCON1.OCFLT1 = ;      //
    OCxCON1.OCFLT0 = ;      //
    OCxCON1.TRIGMODE = ;    //
    OCxCON1.OCM = ;         //

    //Output Compare Control Register 2
    OCxCON2.FLTMD = ;       //
    OCxCON2.FLTOUT = ;      //
    OCxCON2.FLTTRIEN = ;    //
    OCxCON2.OCINV = ;       //
    OCxCON2.DCB = ;         //
    OCxCON2.OC32 = ;        //
    OCxCON2.OCTRIG = ;      //
    OCxCON2.TRIGSTAT = ;    //
    OCxCON2.OCTRIS = ;      //
    OCxCON2.SYNCSEL = ;     //

    //Compare Register
    OCxR.OCRB = ;           //

    //Secondary Compare Register
    OCxRS.OCRSB = ;         //

    //Timer Register
    OCxTMR.TMRB = ;         //

	//Unlock
	__builtin_write_OSCCONL(OSCCON & 0xBF);
	
	//Assign remappable output pins
	
	//Lock
	__builtin_write_OSCCONL(OSCCON | 0x40);
	
}
**********************************************************************************/
