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
const unsigned int MAX_BRIGHT = 255;
const unsigned int MIN_BRIGHT = ceil( (1/2) * MAX_BRIGHT );

// Range for pulse length.
const unsigned int MIN_PULSE_LENGTH = 1;
const unsigned int MAX_PULSE_LENGTH = 2;

// Delay range for consecutive pulses on same channel.
const unsigned int MIN_DELAY = 5;
const unsigned int MAX_DELAY = 10000;

// Channels per Tlc5940. Cannot skip addresses, for example:
// 16 channels means LEDs 1-16, 4 channels means LEDs 1-4. 
const int TOTAL_CHANNELS = 1;

int states[TOTAL_CHANNELS][5];


// Setup initial conditions for LED channels.
void setup(){
  pinMode(13, OUTPUT);   
//  setup_channel_states();
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
 * Main loop for Arduino, flashes LED with random delay and random pulse width.
 */
void loop(){
 
/*  
  for( int i = 0; i < TOTAL_CHANNELS; i++ ){  
    
    // Update state or decrement delay timer
    if( states[i][3] == 0 ){
    
      // Reset channel when pulse length completes.
      if( states[i][2] < 1 ){
      
        //init_channel_state( states[i], states[i][0] );
        states[i][1] = random( MIN_BRIGHT, MAX_BRIGHT );    
        states[i][2] = random( MIN_PULSE_LENGTH, MAX_PULSE_LENGTH );
        states[i][3] = random( MIN_DELAY, MAX_DELAY );    
        
        
      } else {
  
        //Tlc.set( channel_state[0], channel_state[1] );
        analogWrite( 13, states[i][1] );  
        
        // Decrement pulse length timer
        states[i][2] -= 1;
      
      }
  
    } else {
    
      // Decrement delay timer for next pulse.
      states[i][3] -= 1;
    }
    
  }
 */
 
  
 // analogWrite( 13, ceil( 127.5 * (1 + sin( .001 * millis())) ) );
  
//  delay(100);

  for ( int in = 0; in < 6.283; in += 0.00628)
  {
    int out = (1 + sin(in)) * 127.5;
    analogWrite(13,out);

  }
}
