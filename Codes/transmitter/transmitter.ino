#include <VirtualWire.h> // Library Required

int TX_PIN = 11;// Tell Arduino on which pin you would like to Transmit data NOTE should be a PWM Pin
int TX_ID = 3; // Transmitter ID address

typedef struct roverRemoteData// Data Structure 
{
int    TX_ID;      // Initialize a storage place for the outgoing TX ID
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Send 
};

int trig = 4;
int echopin = 2;
int duration ;
unsigned int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
  vw_set_tx_pin(TX_PIN);// Set Tx Pin
  pinMode(trig, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = (duration/2) * 0.034;
  
  Serial.print(distance); Serial.print("CMS"); Serial.print("\n");
  delay(50);
  struct roverRemoteData payload;// In this section is where you would load the data that needs to be sent.
//  
  // If you want to read a analog pin and transmit its value you can do it as follows by removing the "//" 
  payload.TX_ID = TX_ID; // Set the Radio Address 
  payload.Sensor1Data = distance;// analogRead(Sensor1Pin);
//  payload.Sensor2Data = distance2;// analogRead(Sensor2Pin);
//  
  vw_send((uint8_t *)&payload, sizeof(payload)); // Send the data 
  vw_wait_tx();// Wait for all data to be sent
}
