#include <Arduino.h>
#include <AudioOutputI2S.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorFLAC.h>

#include "sample.h"
#include "BluetoothSerial.h"

//Definition required for bluetooth connection
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Declaration of BT and audio export objects
BluetoothSerial SerialBT;
AudioOutputI2S *out;
AudioFileSourcePROGMEM *file;
AudioGeneratorFLAC *flac;

//Declaration of ports for sensors and reset pin
const int sens1Pin = 34;
const int sens2Pin = 35;
const int sens3Pin = 32;  
const int resetPin = 19;

//Storage for sensors value
int sens1Value = 0;
int sens2Value = 0;
int sens3Value = 0;

String message = "";      //Stores message passed by BT
bool loundry = false;     //True if one of three sensors gets desired effect
bool isPlaying = false;   //For looping sound while alarm

//Disable/Enable sensors
bool input1 = true;
bool input2 = false;
bool input3 = false;
bool ShowData = false;  //True - Print sensors values on BT console


/*SETUP*/
void setup()
{
    Serial.begin(115200);
    pinMode(resetPin, INPUT_PULLUP);    // sets the digital pin 7 as input
    delay(100);

    //Audio objects configuration
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( sample_flac, sizeof(sample_flac) );
    out = new AudioOutputI2S();
    out->SetGain(0.2);
    flac = new AudioGeneratorFLAC();
    flac->begin(file, out);

    //Define BT name
    SerialBT.begin("Washing machine detector");
    Serial.println("Setup done");  
}


/*LOOP*/
void loop()
{ 
   if(!flac->loop()){
    flac->stop();
    isPlaying = false;
   }


  //Reset button reaction 
  if(!digitalRead(resetPin)) {

    //Recreate sound managment object for reset
    delete file;
    delete out;
    delete flac;
    file = new AudioFileSourcePROGMEM( sample_flac, sizeof(sample_flac) );
    out = new AudioOutputI2S();
    out->SetGain(0.2);
    flac = new AudioGeneratorFLAC();
    flac->begin(file, out);

    //Clear all bool variables
    input1 = false;
    input2 = false;
    input3 = false;
    isPlaying = false;
    loundry = false; 
  }


  //Reading from Bluetooth (if avaible)
  if (SerialBT.available()){

    //Save input
    char incomingChar = SerialBT.read();

    //Convert to string variable if input exists
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }

    
  // Check received message and control output accordingly
  //Turn of sensor 1 (/input1)
  if (message == "input1"){
      if(input1){
        input1 = false;
        SerialBT.println("Sensor 1 off!");
      }
      else{
        input1= true;
        SerialBT.println("Sensor 1 on!");
      }
  }
  
  //Turn of sensor 2 (/input2)
  else if(message == "input2"){
    if(input2){
      input2 = false;
      SerialBT.println("Sensor 2 off!");
    }
    else{
      input2= true;
      SerialBT.println("Sensor 2 on!");
    }
  }

  //Turn of sensor 3 (/input3)
  else if(message == "input3"){
    if(input3){
      input3 = false;
      SerialBT.println("Sensor 3 off!");
    }
    else{
      input3= true;
      SerialBT.println("Sensor 3 on!");
    }
  }

  //Respond on stop input when no alarm 
  else if(message == "stop"){
    SerialBT.println("No alarm to finish!");
  }

  //Show current data of sensors (/ShowData)
  else if(message == "ShowData"){
      ShowData = true;
  }


  //Respond to alarm (loops sound)
  if(loundry){

    //If no sound executed, play again
    if(!isPlaying){
      //Set playing on true
      isPlaying = true;

      //Recreate sound object for reset (I could have place this in outer function)
      delete file;
      delete out;
      delete flac;
      file = new AudioFileSourcePROGMEM( sample_flac, sizeof(sample_flac) );
      out = new AudioOutputI2S();
      out->SetGain(0.2);
      flac = new AudioGeneratorFLAC();
      flac->begin(file, out);
    }

    //Reading from Bluetooth (if avaible)
    if (SerialBT.available()){
      
      //Save input
      char incomingChar = SerialBT.read();
      
      //Convert to string variable if input exists
      if (incomingChar != '\n'){
        message += String(incomingChar);
      }
      else{
        message = "";
      }
      Serial.write(incomingChar);  
    }

    // Stop alarm and clear bool variables
    if (message =="stop"){
      SerialBT.println("Alarm turned off!");
      SerialBT.println("Sensor 1 off!");
      SerialBT.println("Sensor 2 off!");
      SerialBT.println("Sensor 3 off!");
      loundry = false;
      input1 = false;
      input2 = false;
      input3 = false;
    }
    delay(20);
  }


  /*SENSOR 1*/
  sens1Value = analogRead(sens1Pin);  //Get sensor data
  
  //Value over limit -> no sensor
  if(sens1Value > 4090){  
    Serial.println("Sensor 1: No Sensor!!!");
    if(ShowData) {SerialBT.println("Sensor 1: No Sensor!!!");}
  }

  //Value under 1500 -> led has been turned on, react...
  else if(sens1Value < 1500){
        //printing info on console and bt console
        Serial.println("Sensor 1: "+String(sens1Value));
        if(ShowData) {SerialBT.println("Sensor 1: "+String(sens1Value));}

        //...but only if this sensor is avaible
        if(!loundry && input1)
        {
          loundry = true;
          SerialBT.println("Task done! (1)");
        }
  }
  //Rest of scenerios that aren't necessery right now
  else{
     Serial.println("Sensor 1: "+String(sens1Value));
     if(ShowData) {SerialBT.println("Sensor 1: "+String(sens1Value));}
  }
  
  //Print in Bt console if sensor is on or off
  if(ShowData){
   if(input1){
      SerialBT.println("Sensor 1: On");
    }
   else{
      SerialBT.println("Sensor 1: Off");
    }
  }


  /*SENSOR 2*/
  sens2Value = analogRead(sens2Pin);  //Get sensor data
  
  //Value over limit -> no sensor
  if(sens2Value > 4090){  
      Serial.println("Sensor 2: No Sensor!!!");
      if(ShowData) {SerialBT.println("Sensor 2: No Sensor!!!");}
  }
  
  //Value between 4090 and 3000 to detect lack of light...
  else if(sens2Value > 3000){
        //printing info on console and bt console
        Serial.println("Sensor 2: "+String(sens2Value));
        if(ShowData) {SerialBT.println("Sensor 2: "+String(sens2Value));}

        //...but only if this sensor is avaible
        if(!loundry && input2)
        {
          loundry = true;
          SerialBT.println("Task done! (2)");
        }
  }
  
  //Rest of scenerios that aren't necessery right now
  else{ 
    Serial.println("Sensor 2: "+String(sens2Value));
    if(ShowData) {SerialBT.println("Sensor 2: "+String(sens2Value));}
  }

  //Print in Bt console if sensor is on or off
  if(ShowData){
   if(input2){
      SerialBT.println("Sensor 2: On");
    }
   else{
      SerialBT.println("Sensor 2: Off");
    }
  }


  /*SENSOR3 (not configured)*/ 
  sens3Value = analogRead(sens3Pin);   //Get sensor data

  //Value over limit -> no sensor
  if(sens3Value > 4090)  
  {
    Serial.println("Sensor 3: No Sensor!!!");
    if(ShowData) {SerialBT.println("Sensor 3: No Sensor!!!");}
  }
  else 
  {
    Serial.println("Sensor 3: "+String(sens3Value));
    if(ShowData) {SerialBT.println("Sensor 3: "+String(sens3Value));}
  }

  //Print in Bt console if sensor is on or off
  if(ShowData){
   if(input3){
      SerialBT.println("Sensor 3: On");
    }
   else{
      SerialBT.println("Sensor 3: Off");
    }
  }
  
  Serial.println("-------------------------");
  ShowData = false; //Clear show data variable after printing on Bt console
}
