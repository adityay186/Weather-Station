//Aditya Kamlesh Yadav
//B. Tech CSE, 2nd Year

#include <Adafruit_Sensor.h>           //Mandatory to include this module in order to use Adafruit Sensors 
#define BLYNK_PRINT Serial  


//___________________Include Libraries_________________________________________________________

#include <DHT.h>                      //DHT Sensor library
#include <ESP8266WiFi.h>              //ESP8266Wifi library
#include <BlynkSimpleEsp8266.h>       //Blynk library
#include <Wire.h>                     //For making connection between BMP Sensor and NodeMCU
#include <Adafruit_BMP085.h>          //BMP180 Sensor Library

Adafruit_BMP085 bmp;                  //Creating BMP085 sensor object. (BMP085 is equivalent to BMP180)
#define I2C_SCL 12                    //Connect SCL pin of BMP180 to GPIO12(D6) of Nodemcu
#define I2C_SDA 13                    //Connect SDA pin of BMP180 to GPIO13(D7) of Nodemcu

float dst,bt,bp,ba;                   //Defining Variables
char dstmp[20],btmp[20],bprs[20],balt[20];
bool bmp085_present=true;

char auth[] = " _4WuUDD1cS-907yyD7QsZqZUqQ29r3TK";  //This authentication key will be sent to your email address while setting up Blynk App.

//________________________Mention the SSID and Password____________________________________________________

char ssid[] = "Mavericks"; //SSID of the WiFi hotspot available
char pass[] = "Adityay189";  //Password of the WiFi

#define DHTPIN 2                                    //Connect the DHT11 sensor's data pin to GPIO2(D4) of NodeMCU    
#define DHTTYPE DHT11                               //Defining the type of sensor we are using

DHT dht(DHTPIN, DHTTYPE); //Creating DHT Sensor Object
BlynkTimer timer;         //Creating timer object


void sendSensor()   //Function used to send sensor data to Blynk App..
{
    

 
//______________________________Check the working of BMP180 sensor________________________________________
 
          if (!bmp.begin()) 
          {
              Serial.println("Could not find a valid BMP085 sensor, check wiring!");
              while (1) {}
          }
  
//______________________Getting the Humidity and temperature value from DHT11____________________________
  
          float h = dht.readHumidity();
          
          float t = dht.readTemperature();


//______________________________Check the working of DHT11 sensor________________________________________
  
          if (isnan(h) || isnan(t)) 
          {
              Serial.println("Failed to read from DHT sensor!");
              return;
          }

//______________________Reading the value of Pressure, Temperature, Altitude from the BMP180__________________

  
          float bp =  bmp.readPressure()/100; // Division by 100 makes it in millibars
          
          float ba =  bmp.readAltitude();
 
  
 //_______________Printing the valus of the above read value on to the Virtual Pins in the Blynk App(Sending Values to Blynk App)_____________
 
          Blynk.virtualWrite(V5 , 98); //humidity
          Blynk.virtualWrite(V6 , 30); //temperature
          Blynk.virtualWrite(V10, 500); //pressure
          Blynk.virtualWrite(V11, 2); //altitude
             
}


void setup()
{
  
          Serial.begin(9600); //Initializing the Serial Monitor with a Baud Rate of 9600
        
          Blynk.begin(auth, ssid, pass);
        
          dht.begin();  //Initializing the DHT sensor
          
          Wire.begin(I2C_SDA, I2C_SCL); //Initializing the I2C connection
          
          delay(10);
          
          timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
