 #include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipeOut = 0xE9E8F0F0E1LL;   
RF24 radio(9,8); 
struct Signal {
byte throttle;
byte pitch;
byte roll;
byte yaw;
};
Signal data;
void ResetData() 
{
data.throttle = 127;
data.pitch = 127;
data.roll = 127;
data.yaw = 127;
}
void setup()
{

radio.begin();
radio.openWritingPipe(pipeOut);
radio.stopListening();  
ResetData();
}
 
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
val = constrain(val, lower, upper);
if ( val < middle )
val = map(val, lower, middle, 0, 128);
else
val = map(val, middle, upper, 128, 255);
return ( reverse ? 255 - val : val );
}
void loop()
{
 
data.throttle = mapJoystickValues( analogRead(A3), 12, 524, 1020, true );
data.roll = mapJoystickValues( analogRead(A4), 12, 524, 1020, true );      
data.pitch = mapJoystickValues( analogRead(A5), 12, 524, 1020, true );     
data.yaw = mapJoystickValues( analogRead(A6), 12, 524, 1020, true );       
radio.write(&data, sizeof(Signal));
}
