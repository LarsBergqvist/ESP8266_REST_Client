//
// An example on REST calls from an ESP8266 to a REST API
// Uses the RestClient library https://github.com/fabianofranca/ESP8266RestClient
//

#include "RestClient.h"

// Set the IP and the port of the REST API
RestClient client = RestClient("192.168.1.16",1010);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Connecting to WiFi network");
  client.begin("SSID", "PASSWORD");
  Serial.println("Connected to WiFi network");
}

int buttonPressCount=0;
void loop()
{  
  // Simulate a count of button presses detected via a GPIO pin
  buttonPressCount++;
  sendButtonPressCount();

  getStateForLed1();

  delay(1000);
}

void sendButtonPressCount()
{
  Serial.println("Sends a PUT request to the API for updating the button press counter");

  // Format JSON data to send
  char buffer[20];
  String putData = String("{  \"count\":\"") + buttonPressCount + String("\"}");
  putData.toCharArray(buffer,20);
  
  client.setContentType("application/json");
  String response = "";

  int statusCode = client.put("/api/ButtonPressCount/1", buffer, &response);
  
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  if (statusCode == 200)
  {
    Serial.print("Response body from server: ");
    Serial.println(response);    
  }
  else
  {
    Serial.print("No valid response from server");
  }
}

void getStateForLed1()
{  
  Serial.println("Sends a GET request to the API for getting the desired state of led number 1");

  client.setContentType("application/json");
  String response = "";

  int statusCode = client.get("/api/LedState/1", &response);
  
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  if (statusCode == 200)
  {
    Serial.print("Response body from server: ");
    Serial.println(response);    
  }
  else
  {
    Serial.print("No valid response from server");
  }
}

