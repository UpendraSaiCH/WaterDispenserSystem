#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid = "XXXXXX";  //wifi User
const char* password =  "XXXXX"; // wifi password
const int user0=0;
const int user1=1;

void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");

  pinMode(user0,INPUT);
  pinMode(user1,INPUT);
  
}
  
void loop() {
  if((digitalRead(user0))==HIGH ||(digitalRead(user0))==HIGH){
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;

  if((digitalRead(user0))==HIGH){
   http.begin("");  //Specify destination for HTTP request           //Specify content-type header
  }
  if((digitalRead(user1))==HIGH){
   http.begin("");  //Specify destination for HTTP request           //Specify content-type header
  }
   int httpResponseCode = http.POST("POSTING from ESP32");   //Send the actual POST request
  
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(600000);  //Send a request every 10 seconds

  } 
}
