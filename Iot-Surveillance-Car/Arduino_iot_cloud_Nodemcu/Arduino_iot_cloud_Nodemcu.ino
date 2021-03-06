#include "arduino_secrets.h"
/*
  Sketch generated by the Arduino IoT Cloud Thing "Esp test"
  https://create.arduino.cc/cloud/things/3375144a-eb31-4a42-a880-df1b550b8a34

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  int distance;
  bool left;
  bool backward;
  bool forward;
  bool led;
  bool right;
  int motor;
  CloudLocation gps;
  int servo;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/
#define RMF 3
#define LMF 1
#define RMB 0
#define LMB 2
#include "thingProperties.h"
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
SoftwareSerial S1(13, 15);
float latitude, longitude;
const unsigned int MAX_MESSAGE_LENGTH = 30;
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  S1.begin(9600);
  delay(1500);
  myservo.attach(12);
  pinMode(1, FUNCTION_3);
  pinMode(3, FUNCTION_3);
  pinMode(16, FUNCTION_3);
  pinMode(12, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);
   pinMode(14,OUTPUT);
  // pinMode(12,OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
  digitalWrite(3, LOW);
  // digitalWrite(12,LOW);
  // digitalWrite(14,LOW);
  digitalWrite(16, LOW);
  digitalWrite(0, LOW);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  //  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  static char message[MAX_MESSAGE_LENGTH];
  while (S1.available() > 0)
  {
    //Create a place to hold the incoming message

    static unsigned int message_pos = 0;

    //Read the next available byte in the serial receive buffer
    char inByte = S1.read();

    //Message coming in (check not terminating character) and guard for over message size
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
    {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received...
    else
    {
      //Add null character to string
      message[message_pos] = '\0';

      //Print the message (or do other things)
       Serial.println(message);

      //Reset for the next message
      message_pos = 0;
    }
  }
  static char lat[10], lon[10], dist[10];
  int i = 0;
  char *check = ",";
  int count = 0;
  int count1 = 0;
  for (int k = 0; k <= 10; k++) {
    if (!strchr(check, message[k])) {
      count++;
    }
    else break;
  }
  count1 = count + 1;
  for (int k = count1; k <= 20; k++) {
    if (!strchr(check, message[k])) {
      count1++;
    }
    else break;
  }
  for (int i = 0; i < count; i++) {
    lat[i] = message[i];
  }
  int j = 0;
  for (int i = count + 1; i < count1; i++) {
    lon[j] = message[i];
    j++;
  }
  j = 0;
  for (int i = count1 + 1; i <= count1 + 5; i++) {
    dist[j] = message[i];
    j++;
  }
  latitude = atof(lat);
  longitude = atof(lon);
  distance = atoi(dist);
  // Serial.println(latitude,6);
  // Serial.println(longitude,6);
  // Serial.println(distance);
  if(latitude==0 && longitude==0){
    gps = Location(19.045116,72.8417);
  //gps = Location(latitude, longitude);
  }
  else{
  gps = Location(latitude, longitude);}
  //  pinMode(2,HIGH);

}




/*
  Since Distance is READ_WRITE variable, onDistanceChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDistanceChange()  {
  // Add your code here to act upon Distance change
}





/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  if (led == 1)
  {
    /*digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(1,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(14,HIGH);
      digitalWrite(0,HIGH);*/
    digitalWrite(16, HIGH);
  }
  else
  {
    /*digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(1,LOW);
      digitalWrite(12,LOW);
      digitalWrite(14,LOW);
      digitalWrite(0,LOW);*/
    digitalWrite(16, LOW);
  }
  // Add your code here to act upon Led change
}


/*
  Since Forward is READ_WRITE variable, onForwardChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onForwardChange()  {
  if (forward == 1) {

    digitalWrite(LMF, HIGH);
    digitalWrite(RMF, HIGH);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
    delay(500);
  }
  else {
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, LOW);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
  }
  // Add your code here to act upon Forward change
}

/*
  Since Backward is READ_WRITE variable, onBackwardChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBackwardChange()  {
  if (backward == 1) {
    digitalWrite(LMB, HIGH);
    digitalWrite(RMB, HIGH);
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, LOW);
    delay(500);
  }
  else {
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, LOW);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
  }
  // Add your code here to act upon Backward change
}

/*
  Since Right is READ_WRITE variable, onRightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRightChange()  {
  if (right == 1) {
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, HIGH);
    digitalWrite(LMB, HIGH);
    digitalWrite(RMB, LOW);
    delay(500);
  }
  else {
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, LOW);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
  }
  // Add your code here to act upon Right change
}

/*
  Since Left is READ_WRITE variable, onLeftChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLeftChange()  {
  if (left == 1) {
    digitalWrite(LMF, HIGH);
    digitalWrite(RMF, LOW);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, HIGH);
    delay(500);
  }
  else {
    digitalWrite(LMF, LOW);
    digitalWrite(RMF, LOW);
    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
  }
  // Add your code here to act upon Left change
}

/*
  Since Motor is READ_WRITE variable, onMotorChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMotorChange()  {
  analogWrite(14, motor);
  // Add your code here to act upon Motor change
}


/*
  Since Servo is READ_WRITE variable, onServoChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onServoChange()  {
  myservo.write(servo);              // tell servo to go to position in variable 'pos'
  delay(50);             
  
  // Add your code here to act upon Servo change
}
