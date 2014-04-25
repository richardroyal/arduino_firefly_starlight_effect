/**
 *  Fades LEDs at different rates and max brightnesses relying heavily
 *  on random number generator to randomize pulses length and delays. 
 */

#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;

// Max brightness range for a pulse. Min value should be 
// smallest value that will show light given hardware constraints. 
const int MAX_BRIGHT = 4059;
const int MIN_BRIGHT = ceil( (1/2) * MAX_BRIGHT );
//const int MIN_BRIGHT = 0;

// Range for pulse length.
const int MIN_PULSE_LENGTH = 1;
const int MAX_PULSE_LENGTH = 1;

// Delay range for consecutive pulses on same channel.
const unsigned int MIN_DELAY = 30;
const unsigned int MAX_DELAY = 35;

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
    
    init_channel_state( states[i], (i+1) );
  } 
  
}

/** 
 *  State Array for each channel contains:
 *    
 *      [0]: channel/LED number,
 *      [1]: current brightness of channel,
 *      [2]: pulse length
 *      [3]: delay before next pulse (changes after each pulse).
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
  if( channel_state[3] < 1 ){
    channel_state[3] = 0;
  
    // Reset channel when pulse length completes.
    if( channel_state[2] < 1 ){
    
      init_channel_state( channel_state, channel_state[0] );
    }

    Tlc.set( channel_state[0], channel_state[1] );
    
    // Decrement pulse length timer
    channel_state[2] -= 1;

  } else {
  
    // Decrement delay timer for next pulse.
    channel_state[3] -= 1;
  }
  
}


int on[TOTAL_CHANNELS];


boolean do_stuff(){
  
  if( random(1, 500) % 500 == 1 ){
    
    return true;
    
  } else {
    
    return false;
  }
}


/**
 * Main loop for Arduino, flashes LED with random delay and random pulse width.
 */
void loop(){
 
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    //update_channel( states[i] );
  }
  // Tlc.update();
   
  /*  TESTING ALL LEDs  */
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    
    if( do_stuff() ){  
      
      int brightness = random( 0, MAX_BRIGHT );    
      on[i] == 1;
      
      Tlc.set( (i+1), 0 );
      Tlc.update();
      tlc_addFade( (i+1), 0, random( MIN_BRIGHT, MAX_BRIGHT ), 0, 500 );
    }
  }
  
  
  
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){    

    if( tlc_isFading( (i+1) ) == 0 && on[i] == 1 ){

      tlc_addFade( (i+1), MIN_BRIGHT, 0, 0, 500 );
      on[i] == 0;

    }
    
  }


  tlc_updateFades();
  delay(3); //  min 10
}
