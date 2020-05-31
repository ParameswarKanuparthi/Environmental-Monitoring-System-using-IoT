#define MUX_A D4
#define MUX_B D3
#define MUX_C D2
#define ANALOG_INPUT A0
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
//#define ANALOGPIN A0
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Param";
const char* password = "87654321";
WiFiClient client;
unsigned long myChannelNumber = 886968;
const char * myWriteAPIKey = "RXGT044P2J19G5CE";
uint8_t temperature, humidity, k=0, l=0, gas, soil, r=0, p=0, q=0;
void setup()
{
 Serial.begin(115200);
 dht.begin();
 delay(10); 
 // Connect to WiFi network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println(WiFi.localIP());
 ThingSpeak.begin(client);
 pinMode(MUX_A, OUTPUT);
 pinMode(MUX_B, OUTPUT);
 pinMode(MUX_C, OUTPUT);
}
void loop()
{
 float value;
 changeMux(LOW, LOW, LOW);
 value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
 changeMux(LOW, LOW, HIGH);
 value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
 changeMux(LOW, HIGH, LOW);
 value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
changeMux(LOW, HIGH, HIGH);
 value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 3 pin of Mux
changeMux(HIGH, LOW, LOW);
 //Value of the sensor connected Option 4 pin of Mux
changeMux(HIGH, LOW, HIGH);
value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 5 pin of Mux
 changeMux(HIGH, HIGH, LOW);
 int gas = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 6 pin of Mux
 changeMux(HIGH, HIGH, HIGH);
 value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 7 pin of

 static boolean data_state = false;
 temperature = dht.readTemperature();
 humidity = dht.readHumidity(); 
 Serial.print("Temperature Value is :");
 Serial.print(temperature);
 Serial.println("C");
 Serial.print("Humidity Value is :");
 Serial.print(humidity);
 Serial.println("%");
 Serial.print("gas quality: ");
 Serial.print(gas);
 Serial.println("");
 // Write to ThingSpeak.
 if(temperature < 255)
 {
 k=temperature;
 }
 if(humidity < 255)
 {
 l=humidity;
 }
 if(gas < 355)
 {
 r=gas;
 }


 ThingSpeak.writeField(myChannelNumber, 1, k, myWriteAPIKey);
 data_state = false;
 delay(10000) ;
 ThingSpeak.writeField(myChannelNumber, 2, l, myWriteAPIKey);
 data_state = true;
 delay(10000) ;
 ThingSpeak.writeField(myChannelNumber, 3, r, myWriteAPIKey);
 data_state = false;
 delay(10000) ;


 // ThingSpeak will only accept updates every 15 seconds.
}
void changeMux(int c, int b, int a) {
 digitalWrite(MUX_A, a);
 digitalWrite(MUX_B, b);
 digitalWrite(MUX_C, c);
}
