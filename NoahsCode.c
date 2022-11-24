const int STRUMMING_POWER = 30;
const int FRET_SPEED = -100;
const int TIME_UNIT = 2000;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int FRET_TIMING = 1000;


void pluck(int direction)
{
        motor[motorA] = direction * STRUMMING_POWER;


        nMotorEncoder[motorA] = 0;


        while(abs(nMotorEncoder[motorA]) < 90)
        {}


        motor[motorA] = 0;
}


void setAndPlayFret(int fret, int prevFret, int time, int direction)
{
        int angleToRotate = abs(FRET_CLICKS*(fret - prevFret));

        if(fret > prevFret)
                angleToRotate = FULL_ROTATION - angleToRotate;


        time1[T1] = 0;
        motor[motorD] = FRET_SPEED;
        while(abs(nMotorEncoder[motorD]) < angleToRotate)
        {}
        motor[motorD] = 0;


        while(time1[T1] < time * TIME_UNIT - FRET_TIMING)
        {}


        pluck(direction);


        wait1Msec(FRET_TIMING);


        nMotorEncoder[motorD] = 0;
}


int playNotes(int *fret, int *hold, int length)
{
        int direction = 1;
        int prevFret = 1;


        for(int note = 0; note < length; note++)
        {
                setAndPlayFret(fret[note], prevFret, hold[note], direction);


                prevFret = fret[note];
                direction *= -1;
        }
        return direction;
}


task main()
{
        int fret[10] = {10, 7, 5, 3, 2, 2, 3, 5, 7, 10};
        int hold[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


        playNotes(fret, hold, 10);
}
