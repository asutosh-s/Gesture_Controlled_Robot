#include <VirtualWire.h>  //Library Required

int RX_PIN = 11;// Tell Arduino on which pin you would like to receive data NOTE should be a PWM Pin
int RX_ID = 3;// Recever ID address 
int TX_ID;
//Define enable pins of the Motors
const int enbA = 8;
const int enbB = 9;

//Define control pins of the Motors
//If the motors rotate in the opposite direction, you can change the positions of the following pin numbers
const int IN1 = 2;    //Right Motor (-)
const int IN2 = 4;    //Right Motor (+)
const int IN3 = 7;    //Left Motor (+)
const int IN4 = 6;    //Right Motor (-)

//Define variable for the motors speeds
//I have defined a variable for each of the two motors 
//This way you can synchronize the rotation speed difference between the two motors
int RightSpd = 130;
int LeftSpd = 150;

typedef struct roverRemoteData //Data Structure 
{
int    TX_ID;      // Initialize a storage place for the incoming TX ID  
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Receive 
};

void setup() {
              //Define the motor pins as output
              pinMode(enbA, OUTPUT);
              pinMode(enbB, OUTPUT);
              pinMode(IN1, OUTPUT);
              pinMode(IN2, OUTPUT);
              pinMode(IN3, OUTPUT);
              pinMode(IN4, OUTPUT);
              Serial.begin(9600);// Begin Serial port at a Buad speed of 9600bps 
              vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
              vw_set_rx_pin(RX_PIN);// Set RX Pin 
              vw_rx_start(); 
                   
              }  
void loop()
{
      struct roverRemoteData receivedData;
      uint8_t rcvdSize = sizeof(receivedData);//Incoming data size 
      vw_wait_rx();// Start to Receive data now 

if (vw_get_message((uint8_t *)&receivedData, &rcvdSize)) // Check if data is available 
{
  if (receivedData.TX_ID == RX_ID) //Check if the radio signal recieved matches the ID of the Reciever
    { 
      // If data was Recieved print it to the serial monitor.
         Serial.println("------------------------New MSG-----------------------");
         Serial.print("TX ID:");
         Serial.println(TX_ID);
         Serial.print("Sensor1Data:");
         Serial.println(receivedData.Sensor1Data);
        
         Serial.println("-----------------------End of MSG--------------------");

         
         if(receivedData.Sensor1Data > 0 &&  receivedData.Sensor1Data < 10){
            //forward            
//            analogWrite(enbA, RightSpd);
//            analogWrite(enbB, LeftSpd);
            digitalWrite(enbA, HIGH);
            digitalWrite(enbB, HIGH);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
          }

          if(receivedData.Sensor1Data > 10 &&  receivedData.Sensor1Data < 20){
            //forward            
//            analogWrite(enbA, RightSpd);
//            analogWrite(enbB, LeftSpd);
            digitalWrite(enbA, HIGH);
            digitalWrite(enbB, HIGH);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
          }
      
          if(receivedData.Sensor1Data > 20){
            //stop car
//            analogWrite(enbA, 0);
//            analogWrite(enbB, 0);
            digitalWrite(enbA, LOW);
            digitalWrite(enbB, LOW);
          }
        } 
      else
        { 
Serial.println(" ID Does not match waiting for next transmission ");
        } 
      } 
    }
