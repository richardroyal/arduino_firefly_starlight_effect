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
const int MAX_BRIGHT = 4059;
const int MIN_BRIGHT = ceil( (1/2) * MAX_BRIGHT );

// Each pulse will climb to its max brightness in increments between these two (per loop cycle).
const int MIN_STEP_SPEED = (1/1000) * MAX_BRIGHT;
const int MAX_STEP_SPEED = ceil( (1/100)  * MAX_BRIGHT );

// Delay for consecutive pulses on one pin falls between these two (loop cycles).
const int MIN_DELAY = 1000;
const int MAX_DELAY = 10000;

// Channels per Tlc5940. Cannot skip addresses, for example:
// 16 channels means LEDs 1-16, 4 channels means LEDs 1-4. 
const int TOTAL_CHANNELS = 16;

int states[TOTAL_CHANNELS][6];


// Setup initial conditions for LED channels.
void setup(){
  
  setup_channel_states();
  Tlc.init(0);
  
}

void setup_channel_states(){

  for( int i = 0; i < TOTAL_CHANNELS; i++ ){
  
    /* 
      State Array for each channel contains:
      
           [0]: channel/LED number,
           [1]: current brightness of channel,
           [2]: max brightness for current pulse,
           [3]: speed step of current pulse,
           [4]: direction of current pulse,
           [5]: delay before next pulse (changes after each pulse).
    */
    states[i][0] = i + 1;
    states[i][1] = 0;
    states[i][2] = random( MIN_BRIGHT, MAX_BRIGHT );    
    states[i][3] = random( MIN_STEP_SPEED, MAX_STEP_SPEED );;
    states[i][4] = 1;
    states[i][5] = random( MIN_DELAY, MAX_DELAY );    
  } 
  
}


/**
 * Increment channel state, then send channels values to Tlc lib
 */
void update_channel( int *channel_state ){
  
  
  // Change direction of pulse when max brightness is hit.
  if( channel_state[2] - channel_state[3] < channel_state[3] ){
    
    channel_step[4] = -1;
    
  } else if( channel_state[4] == -1 && ( channel_state[1] - channel_state[3] < 0 ) ) {
  
    reset_initialize_channel( channel_state );
  }

  // Update brightness
  channel_state[1] += channel[4] * channel_state[3];
  
  
  Tlc.set( channel_state[0], channel_state[1] );
}


// Main loop for Arduino, updates each channel brightness after incrementing state.
void loop(){
   
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    update_channel( states[i] );
  }
 
  delay(1000);
}
