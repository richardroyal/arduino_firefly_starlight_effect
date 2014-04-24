/**
 *  Fades LEDs at different rates and max brightnesses relying heavily
 *  on random number generator to randomize pulses length and delays. 
 */

#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;

// Max brightness range for a pulse. Min value should be 
// smallest value that will show light given hardware constraints. 
//const int MAX_BRIGHT = 4059;
const int MAX_BRIGHT = 255;
const int MIN_BRIGHT = ceil( (1/2) * MAX_BRIGHT );

// Range for pulse length.
const int MIN_PULSE_LENGTH = 1;
const int MAX_PULSE_LENGTH = 5;

// Delay range for consecutive pulses on same channel.
const int MIN_DELAY = 1;
const int MAX_DELAY = 1000 * MIN_DELAY ; //200 * MIN_DELAY;

// Channels per Tlc5940. Cannot skip addresses, for example:
// 16 channels means LEDs 1-16, 4 channels means LEDs 1-4. 
const int TOTAL_CHANNELS = 1;

int states[TOTAL_CHANNELS][6];


// Setup initial conditions for LED channels.
void setup(){
  
  setup_channel_states();
  //Tlc.init(0);  
}

void setup_channel_states(){

  for( int i = 0; i < TOTAL_CHANNELS; i++ ){
    
    init_channel_state( states[i], (i+1) );
  } 
  
}

/** 
 *  State Array for each channel contains:
 *    
 *      [0]: channel/LED number,
 *      [1]: current brightness of channel,
 *      [2]: max brightness for current pulse,
 *      [3]: pulse length
 *      [4]: delay before next pulse (changes after each pulse).
 */
void init_channel_state( int *channel_state, int channel_number ){
  
  channel_state[0] = channel_number;
  channel_state[1] = random( MIN_BRIGHT, MAX_BRIGHT );    
  channel_state[2] = random( MIN_PULSE_LENGTH, MAX_PULSE_LENGTH );
  channel_state[3] = random( MIN_DELAY, MAX_DELAY );    
  
}


/**
 *  Increment channel state, then send channels values to Tlc lib
 */
void update_channel( int *channel_state ){
  
  // Update state or decrement delay timer
  if( channel_state[3] == 0 ){
  
    // Reset channel when pulse length completes.
    if( channel_state[2] < 1 ){
    
      init_channel_state( channel_state, channel_state[0] );
    }


    //Tlc.set( channel_state[0], channel_state[1] );
    analogWrite( 13, channel_state[1] );  
    
    // Decrement pulse length timer
    channel_state[2] -= 1;

  } else {
  
    // Decrement delay timer for next pulse.
    channel_state[3] -= 1;
  }
  
}


/**
 * Main loop for Arduino, flashes LED with random delay and random pulse width.
 */
void loop(){
   
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    update_channel( states[i] );
  }
 
  delay(1);
}
