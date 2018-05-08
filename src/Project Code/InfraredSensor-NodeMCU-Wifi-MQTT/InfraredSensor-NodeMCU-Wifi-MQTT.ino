// This is a minimal example on MQTT publish and subscribe from an ESP8266 board
// to an MQTT broker (I have used a local Mosquitto running on a Raspberry Pi)
// This example uses the PubSub client library (https://github.com/knolleary/pubsubclient)
// Install it in the Arduino IDE before compiling the sketch

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#define WLAN_SSID  "G4_6402" // The SSID of your local LAN where a MQTT-broker is running
#define WLAN_PASS  "lalalala" // The WIFI password for your local lan
#define BROKER_IP  "192.168.43.224" // The IP of the machine where the broker is running
#define BROKER_PORT 1883

#define CLIENT_NAME "ESP8266_1" // just a name to identify this client
WiFiClient wifiClient;
PubSubClient mqttClient(BROKER_IP,BROKER_PORT,wifiClient);

const char* lokasi;
float maxHeight;
float area;
bool isOn;

#define trigPin 5 //D1
#define echoPin 4 //D2

void setup() 
{
  Serial.begin(9600);
  
  //mqttClient.setCallback(callback);

  //WiFi.begin(WLAN_SSID, WLAN_PASS);

  //connectToWiFiAndBroker();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop() 
{
  //if (!mqttClient.connected()) 
  // {
  //  connectToWiFiAndBroker();
  // }

  //mqttClient.loop();

  ultrasonic();
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.println("Message received: ");
  Serial.println(topic);
  if(topic=="AttributeAssign/1")
  {
    const size_t bufferSize = JSON_OBJECT_SIZE(4) + 80;
    DynamicJsonBuffer jsonBuffer(bufferSize);
    String json= String((char*)payload);

    JsonObject& root = jsonBuffer.parseObject(json);
    
    const char* lokasi = root["lokasi"]; 
    float maxHeight = root["maxHeight"]; 
    float area = root["area"];
    bool isOn = root["isOn"]; 

  }
  Serial.println("Done");
  
}

void connectToWiFiAndBroker() 
{
  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WIFI!");

  Serial.println("Connecting to broker");
  while (!mqttClient.connect(CLIENT_NAME)) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to broker!");

  mqttClient.subscribe("AttributeAssign");
}

void ultrasonic(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500);
  
}
