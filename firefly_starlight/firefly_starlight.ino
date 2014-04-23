/*
    Fades LEDs at different rates and max brightnesses relying heavily
    on random number generator to random pulses 
    
    create a pulse for a channel and then
    create a new pulse with differen
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

// Channels per Tlc5940. Cannot skip addresses, for example:
// 16 channels means LEDs 1-16, 4 channels means LEDs 1-4. 
const TOTAL_CHANNELS = 16

int states = [TOTAL_CHANNELS];


// Setup initial conditions for LED channels.
void setup(){
  
  setup_channel_states();
  Tlc.init(0);
  
}

void setup_channel_states(){

  for( int i = 0; i < TOTAL_CHANNELS; i++ ){
  
    /* 
      State Array for each channel contains:
      
           channel/LED number,
           current brightness of channel,
           max brightness for current pulse,
           speed of current pulse,
           direction of current pulse,
           delay before next pulse (changes after each pulse).
    */
    int pulse_to = random( MIN_BRIGHT, MAX_BRIGHT );
    int step_interval = random( MIN_STEP_SPEED, MAN_STEP_SPEED );
    int channel_delay = random( MIN_DELAY, MAX_DELAY ); 

    states[i] = { i + 1, 0, pulse_to, step_interval, 1, channel_delay };
  } 
  
}


/**
 * Increment channel state, then send channels values to Tlc lib
 */
void update_channel( chan ){
  
  Tlc.set( ch[0], 1023);

}


// Main loop for Arduino, updates each channel brightness after incrementing state.
void loop(){
   
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    update_channel( state[i] );
  }
 
  delay(1000);
}
