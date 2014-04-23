/*
    Fades groupings of LEDs at different rates and max brightnesses.  
*/

#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;

// Each pulse will reach a brightness between these two.
const MAX_BRIGHT = 4059;
const MIN_BRIGHT = (1/2) * MAX_BRIGHT;

// Each pulse will climb to its max brightness in increments between these two (per loop cycle).
const MIN_STEP_SPEED = (1/1000) * MAX_BRIGHT;
const MAX_STEP_SPEED = (1/100)  * MAX_BRIGHT;

// Delay for consecutive pulses on one pin falls between these two (loop cycles).
const MIN_DELAY = 1000;
const MAX_DELAY = 10000;


const TOTAL_CHANNELS = 16


int states = [TOTAL_CHANNELS];



// Init Arduino and LED Driver lib.
void setup(){
  
  setup_channel_states();
  Tlc.init(0);
  
}


void setup_channel_states(){

  for( int i = 0; i < TOTAL_CHANNELS; i++ ){
  
    // State array contains:
    //    channel/LED number
    //    current brightness of channel
    //    max brightness for current pulse
    //    speed of current pulse
    //    direction of current pulse
    //    delay between pulses, changes after each pulse
    //
    
    int pulse_to = random( MIN_BRIGHT, MAX_BRIGHT );
    int step_speed = random( MIN_STEP_SPEED, MAN_STEP_SPEED );
    int channel_delay = random( MIN_DELAY, MAX_DELAY ); 

    states[i] = { i + 1, 0, pulse_to, , 1, channel_delay };
  } 
  
}


void update_channel_state(){

}


// Main loop for Arduino
/*

 TAKEN FROM EXAMPLE
 
void loop()
{
  for (int i = 0; i < 16; i++)
  {
    Tlc.set(i, 1023);
  }
  Tlc.update();
  delay(1000);
  for (int i = 0; i < 16; i++)
  {
    Tlc.set(i, 2046);
  }
  Tlc.update();
  delay(1000);
  for (int i = 0; i < 16; i++)
  {
    Tlc.set(i, 3069);
  }
  Tlc.update();
  delay(1000);
  for (int i = 0; i < 16; i++)
  {
    Tlc.set(i, 4095);
  }
  Tlc.update();
  delay(1000);
}
