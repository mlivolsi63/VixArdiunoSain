//========================================================================================
// Program : Mega Master
// Author  : Mike LiVolsi
//
// Purpose:  This is the guy who will be attached to the computer (be it a pi or windows)
//           if there are more than 52 channels being passed, then we hand those off to the next
//           mega.
//
//========================================================================================
#include <string.h>
#include <stdlib.h>

// On the mega, There are about 52 workable channels. On the uno, it's 12 (if you don't want to use pins 0 and 1)
const unsigned int maxChannels = 102;                 // set this to the number of channels in vixen serial interface
const unsigned int mega1Channels = 52;                // set this to the max number of channels on the Arduino mega
const unsigned int mega2Channels = 52;                // set this to the max number of channels on the Arduino Mega
const unsigned int mega3Channels = 52;                // set this to the max number of channels on the Arduino Mega
const unsigned int BAUD_RATE = 57600;                 // set this to the number of channels in vixen serial interface
const unsigned int DEBUG_PIN = 13;


unsigned int totalCodes = 36;

//----------------
//original codes
//---------------
unsigned int irCodeLow[18][35] = {
 /* off   */ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620,  480, 1620, 1620,  480, 1620, 480, 480, 480, 1620,  480,  480, 1560,  480, 1560, 1620, 1620, 40000, 2100 },
 /* on    */ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620, 1620, 1620,  480,  480,  480, 480, 480, 480,  480,  480, 1620, 1620, 1620, 1620, 1620, 1620, 40000, 2100 },
 /* red   */ { 4320, 540, 480, 480, 540, 480, 480, 540, 480, 1560, 1560, 1620, 1560, 480, 1560, 1560, 1620,  480,  540, 1560,  540,  480, 480, 540, 480, 1560, 1560,  540, 1560, 1620, 1560, 1560, 1620, 40000, 2100 },
 /* green */ { 4320, 480, 480, 540, 480, 480, 540, 480, 480, 1620, 1560, 1560, 1620, 480, 1620, 1560, 1620, 1620,  480, 1620,  480,  540, 480, 480, 540,  480, 1560,  480, 1560, 1560, 1620, 1560, 1560, 40000, 2100 },
 /* blue  */ { 4320, 540, 480, 480, 540, 480, 480, 540, 480, 1620, 1620, 1620, 1560, 480, 1620, 1560, 1560,  540, 1560, 1620,  480,  480, 480, 480, 480, 1620,  540,  480, 1560, 1560, 1620, 1560, 1560, 40000, 2100 },
 /* white */ { 4320, 480, 480, 480, 480, 480, 480, 540, 480, 1560, 1620, 1620, 1560, 480, 1560, 1620, 1620, 1560, 1560, 1620,  480,  540, 480, 480, 540,  480,  480,  540, 1560, 1620, 1560, 1620, 1620, 40000, 2100 },
 /* peach */ { 4320, 540, 480, 480, 540, 480, 480, 540, 480, 1560, 1560, 1620, 1560, 480, 1560, 1560, 1620,  480,  540,  480, 1560,  480, 480, 540, 480, 1560, 1560, 1620,  480, 1620, 1560, 1560, 1620, 40000, 2100 },
 /* orgng */ { 4320, 480, 480, 480, 540, 480, 480, 540, 480, 1560, 1620, 1620, 1560, 480, 1560, 1560, 1620,  480,  540, 1560, 1620,  480, 540, 480, 480, 1620, 1560,  480,  480, 1620, 1560, 1620, 1620, 40000, 2100 },
 /* lorng */ { 4320, 480, 540, 480, 480, 540, 480, 480, 540, 1560, 1620, 1560, 1560, 540, 1620, 1620, 1620,  480,  480,  540,  480, 1560, 480, 480, 540, 1620, 1560, 1560, 1620,  540, 1620, 1620, 1560, 40000, 2100 },
 /* yello */ { 4320, 480, 540, 480, 480, 540, 480, 480, 540, 1560, 1620, 1560, 1560, 540, 1560, 1620, 1560,  480,  480, 1620,  480, 1620, 480, 520, 480, 1620, 1620,  540, 1620,  540, 1620, 1620, 1620, 40000, 2100 },
 /* lgreen*/ { 4320, 540, 480, 480, 540, 480, 480, 540, 480, 1560, 1560, 1620, 1560, 540, 1560, 1620, 1620, 1620,  480,  480, 1620,  480, 540, 480, 480,  480, 1620, 1620,  480, 1620, 1620, 1620, 1620, 40000, 2100 },
 /* babybl*/ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1560, 1560, 1620, 1560, 480, 1560, 1560, 1620, 1560,  480, 1560, 1560,  480, 480, 480, 480,  480, 1560,  540,  540, 1560, 1560, 1620, 1560, 40000, 2100 },
 /* aqblue*/ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1560, 1560, 1620, 1560, 480, 1560, 1560, 1620, 1560,  480,  480,  480, 1560, 480, 480, 480,  480, 1560, 1620, 1560,  480, 1560, 1560, 1620, 40000, 2100 },
 /* aqua  */ { 4320, 480, 480, 540, 480, 480, 540, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620, 1620,  480, 1620,  480, 1620, 480, 480, 480,  480, 1620,  480, 1620,  480, 1620, 1620, 1620, 40000, 2100 },
 /* lblue */ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620,  480, 1620,  480, 1620,  480, 480, 480, 480, 1620,  480, 1620,  480, 1620, 1620, 1620, 1620, 40000, 2100 },
 /* barney*/ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620,  480, 1620, 1620, 1620,  480, 480, 480, 480, 1620,  480,  480,  480, 1620, 1620, 1620, 1620, 40000, 2100 },
 /* lbanrn*/ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1620, 1620, 1620, 1620, 480, 1620, 1620, 1620,  480, 1620,  480,  480, 1620, 480, 480, 480, 1620,  480, 1620, 1620,  480, 1620, 1620, 1620, 40000, 2100 },
 /* pink  */ { 4320, 480, 480, 480, 480, 480, 480, 480, 480, 1560, 1560, 1620, 1560, 480, 1560, 1560, 1620,  480, 1620, 1560,  480, 1560, 480, 480, 480, 1620,  480,  480, 1620,  480, 1560, 1620, 1620, 40000, 2100 },

};

unsigned int irCodeHigh[18][36] = {
 /* off   */ { 8840, 540, 600, 600, 540, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  540,  600,  600,  600, 600, 600, 540,  600,  540,  600,  600,  600,  600,  600,  540,   600, 8840, 600 },
 /* on    */ { 8840, 600, 600, 600, 540, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  600,  540,  600,  600, 540, 600, 600,  540,  600,  600,  600,  540,  600,  600,  540,   600, 8840, 600 },
 /* red   */ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  600, 600, 600, 600,  600,  600,  600,  600,  600,  600,  600,  600,   600, 8840, 600 },
 /* green */ { 8840, 600, 600, 540, 600, 600, 540, 600, 600,  600,  600,  600,  540, 600,  540,  600,  600,  540,  600,  540,  600,  540, 600, 600, 540,  600,  600,  600,  600,  600,  540,  600,  600,   540, 8840, 600 },
 /* blue  */ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  540,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  600, 600, 600, 540,  600,  600,  600,  600,  600,  600,  600,  600,   600, 8840, 600 },
 /* white */ { 8840, 600, 600, 600, 600, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  600,  540,  600,  540, 600, 600, 540,  600,  600,  540,  600,  540,  600,  600,  540,   600, 8840, 600 },
 /* peach */ { 8840, 600, 600, 600, 540, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  540,  600,  600,  600, 600, 540, 600,  600,  600,  540,  600,  600,  600,  600,  540,   600, 8840, 600 },
 /* orange*/ { 8840, 600, 600, 600, 600, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  540,  600,  540,  600, 540, 600, 600,  540,  600,  600,  600,  540,  600,  600,  540,   600, 8840, 600 },
 /* lorgn */ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  540,  600,  600,  540,  600,  600,  540,  600, 540, 600, 600,  540,  600,  600,  540,  600,  540,  600,  600,   540, 8840, 600 },
 /* yellow*/ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  600, 600, 600, 600,  600,  600,  600,  600,  600,  600,  600,  600,   600, 8840, 600 },
 /* lgreen*/ { 8840, 600, 540, 600, 600, 540, 600, 600, 540,  600,  540,  600,  600, 540,  600,  540,  600,  600,  540,  600,  600,  600, 600, 540, 600,  600,  600,  600,  600,  600,  600,  540,  600,   600, 8840, 600 },
 /* babybl*/ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 540,  600,  540,  540,  600,  540,  600,  540,  540, 540, 600, 540,  540,  600,  540,  540,  600,  600,  540,  600,   600, 8840, 600 },
 /* aquabl*/ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  600, 600, 600, 600,  600,  600,  600,  600,  600,  600,  600,  600,   600, 8840, 600 },
 /* aqua  */ { 8840, 600, 600, 540, 600, 600, 540, 600, 600,  540,  600,  600,  540, 600,  540,  600,  600,  540,  600,  540,  600,  540, 600, 540, 600,  600,  540,  600,  540,  600,  600,  600,  600,   540, 8840, 600 },
 /* lblue */ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  600, 600, 600, 600,  600,  600,  600,  600,  600,  600,  600,  600,   600, 8840, 600 },
 /* barney*/ { 8840, 600, 600, 600, 600, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  600,  600,  600,  600, 600, 600, 540,  600,  540,  600,  600,  540,  600,  600,  540,   600, 8840, 600 },
 /* lbarn */ { 8840, 600, 600, 600, 600, 600, 600, 600, 600,  600,  600,  600,  600, 600,  600,  600,  600,  600,  600,  600,  600,  540, 600, 540, 600,  600,  600,  600,  600,  600,  600,  540,  600,   600, 8840, 600 },
 /* pink  */ { 8840, 600, 600, 600, 540, 600, 600, 540, 600,  600,  600,  540,  600, 600,  600,  600,  540,  600,  540,  600,  600,  600, 600, 600, 540,  600,  540,  600,  600,  600,  600,  600,  540,   600, 8840, 600 },
};

//========================================================================================
// THis is the master script.
// Read in from vixen the string for each time event.. ie. let'say channel 1 is 0, channel 2 is 1.. Vixen will send "< 1 0 >"
// Then, any channel less than 52 is processed here and sent to it's respective controller
// Channels 52-103 can be sent to Arduino 2
// .. and, if needed, 104 to 155 could be sent to Arduino 3 (and so on)
//
// For each cell in Vixen, it sends 1 byte (0-255 or hex 0-FF) in the stream
// 0 means nothing sent (or off), and 255 means on...
// However, values between 0 and 255 are used for dimming in LED land..
//
// NOTE: Pins 2-13 are          PWM (Led Range)
//       Pins 44,45,46 are also PWM
//
//========================================================================================

//---------------------------------------------------------------------
// Strings state from Vixen
//---------------------------------------------------------------------
const short VIX_WAIT = 0;   // we are in the state of waiting for a '<'
const short VIX_READ = 1;   // we are in the state of reading until we  encounter a footer
const short VIX_PROC = 2;   // we're in the middle of processing and spitting out to the relays


int   byteArray[maxChannels + 8];        // 52 values, plus the header and footer (+2), plus null terminator (+1), plus round to nearest word
int   readFlag = VIX_WAIT;    // -1 garbage bytes | 0 reading in header bytes | 1 header set, read in instructions | 2 done reading in


//------------------------------------------
// setup the pins/ inputs & outputs
//------------------------------------------
void setup() {
  Serial.begin(BAUD_RATE);                      // set up Serial at 38400 bps
  Serial1.begin(BAUD_RATE);

  unsigned int i = 0;
  for (i = 2; i <= maxChannels; i++) {            // start with pin '2' (0 and 1 are rx/tx)  and end at pin 'maxChannels'
    pinMode(i,  OUTPUT);
  }

}

//------------------------------------------
// Debug Pin
//------------------------------------------
void blinkIt(int inCount) {

  unsigned int i = 0;
  for (i = 0; i < inCount; i++) {
    digitalWrite(DEBUG_PIN, HIGH);
    delay(250);
    digitalWrite(DEBUG_PIN, LOW);
    delay(250);
  }
}

//-------------------------------------------------------------------------------------
// Hex value from Vixen (sent to this routine which has already been divided by 10)
//  0 - off
// 10 - on
// 20 - red
// 30 - green
// 40 - blue
// 50 - white
// 60 - peach
// 70 - orange
// 80 - light orange
// 90 - yellow
// 100 - light green
// 110 - baby blue
// 120 - aqua blue
// 130 - aqua
// 140 - light blue
// 150 - Barney
// 160 - Light barney
// 170 - Pink
//
// note: You pulse on/off real quick.. thats the "high" (though it includes 'lows')
//       then, you sleep for a few hundred microseconds (that's a low signal)
//-------------------------------------------------------------------------------------

void pulseIR(int IRledPin, int inColor) {

  long microsecs = 0;
  // we'll count down from the number of microseconds we are told to wait
  cli(); // this turns off any background interrupts
  for (int i = 0; i < totalCodes; i++) {
    microsecs = irCodeHigh[inColor][i];
    while (microsecs > 0) {
      // 38 kHz is about 13 microseconds high and 13 microseconds low
      digitalWrite(IRledPin, HIGH);   // this takes about 3 microseconds to happen
      delayMicroseconds(7);           // hang out for 10 microseconds, you can also change this to 9 if its not working
      digitalWrite(IRledPin, LOW);    // this also takes about 3 microseconds
      delayMicroseconds(7);           // hang out for 10 microseconds, you can also change this to 9 if its not working
      // so 26 microseconds altogether
      microsecs -= 26;
    }
    if(i < (totalCodes - 1) ) delayMicroseconds(irCodeLow[inColor][i]);        // low period 
  }
  sei(); // this turns them back
}


//--------------------------------------------------------------------------------------------
// Routine: writeOutBuffer
//
// Purpose: The first 52 positions (minus whatever pins are dead or we are avoiding)
//          go out to their respective box (mosfets are 0-15, with the last three physically
//          mapped to the last pins on the board.
//          Everything in the range of 52-103   are written to Arduino #2 (if available )
//          Everything in the range of 104-155  are written to Arduino #3 (also, if available)
//
//--------------------------------------------------------------------------------------------

void writeOutBuffer() {
  unsigned int vixChannel = 0; // output looper

  readFlag = VIX_WAIT;
  //----------------------------------------------------------------------------------------
  // send out to the pins
  // THe way we wired the mega (some dead pins), we'll have to adjust here in the code
  // we are avoiding pins 0 and 1 on the Mega
  // and avoiding pin 13 which we will use for debugging
  //
  // If vix channels: 10, 11, 12  maps to 44, 45, 46 (pwm pins)
  //           array:  9, 10, 11
  //
  //
  // Since we are eating those pins, we'll have to do some fancy work for movement
  //----------------------------------------------------------------------------------------
  for (vixChannel = 0; vixChannel < mega1Channels; vixChannel++) {
    if (vixChannel <= 12) {
      if (vixChannel == 12 ) blinkIt(10);                                       // The debug channel
      else {
        if (vixChannel <= 8)  analogWrite(vixChannel +  2, byteArray[vixChannel]);
        else                 analogWrite(vixChannel + 35, byteArray[vixChannel]);  // write to the pwm's that are in the 40's
      }
    }
    else {
      if (vixChannel <= 41) digitalWrite(vixChannel + 2, byteArray[vixChannel]);
      else {
        if (vixChannel >= 49 ) {
          switch (vixChannel) {
            case 49:
              digitalWrite(11, byteArray[vixChannel]);
              break;
            case 50:
              digitalWrite(12, byteArray[vixChannel]);
              break;
            case 51:
              pulseIR(14, byteArray[vixChannel]/10);
              break;
          }
        }
        else digitalWrite(vixChannel + 5, byteArray[vixChannel]); // ie. if array pos 42, then pin 47
      }
    }
  }

  //-------------------------------------
  // write to Arduino # 2
  //-------------------------------------
  if ( Serial1.available() ) {
    Serial1.write('<');
    for (vixChannel = mega1Channels; vixChannel < (mega1Channels + mega2Channels); vixChannel++) {
      Serial1.write(byteArray[vixChannel]);                         // The values will be converted automatically to an ascii byte
    }
    Serial1.write('>');
  }

  //-------------------------------------------------------------------
  // write to Arduino # 3
  // Un-comment out if hooking up another arduino Mega to this master
  //-------------------------------------------------------------------
  //if( Serial2.available() ) {
  //    Serial2.write('<');
  //    for(vixChannel=(mega1Channels+mega2Channels); vixChannel < (mega1Channels + mega2Channels + mega3Channels); vixChannel++) {
  //        Serial2.write(byteArray[vixChannel]);
  //    }
  //    Serial2.write('>');
  //}
}

//---------------------------------------------------------------------------------------------------
// Routine: Loop
//
// Purpose: Read in the string of bytes coming in from Vixen. Then once we get our EOL indicator '>'
//          take the buffer and write that out to whatever target is appropriate for that range
//          in this case, first 15 go to LED string, the next up to 51 go to SSD relays
//          52-102   go to Arduino 2 (51 pins are usable)
//          104-155  go to Arduino 3
//
//---------------------------------------------------------------------------------------------------
int byteCount = 0;
int inByte;

void loop() {

  unsigned int i = 0; // loop counter
  unsigned int k = 0; // debugger

  while ( Serial.available() > 0 ) {                                  // bytes in the buffer
    inByte = Serial.read();                                         // if the process state flag hasn't been set

    switch (readFlag) {

      case VIX_WAIT:                                              // looking for start of header
        if ( inByte == '<' ) {                                  // start of header found
          readFlag = VIX_READ;                                // set flag to start reading data
          byteCount = 0;                                      // set byte count to 0
          for (i = 0; i < maxChannels; i++) {                 // wipe out the array
            byteArray[i] = 0;
          }
        }
        break;

      case VIX_READ:

        if (inByte == '>' ) {                                   // footer
          if ( byteCount < maxChannels ) {                    // we missed some bytes
            readFlag = VIX_WAIT;                            // start re-reading
          }
          else {
            readFlag = VIX_PROC;                            // set the flag that we're ready to use our buffer
          }
        }
        else {
          byteArray[byteCount] = inByte;                      // set the byte in the array
          byteCount++;
        }                                                      // increment our byte count
        break;
    }                                                                // end switch

    if (readFlag == VIX_PROC) {                                      // our buffer is full and ready to process
      writeOutBuffer();
    }
  }                                                                   // end serial.available();
}                                                                      // end loop
