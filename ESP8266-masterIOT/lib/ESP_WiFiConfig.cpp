#include <Arduino.h>
#include <ESP8266WiFi.h>

// wifi config
#define ssid "Cleverson"
#define password "tesla32020"


//ip config
WiFiServer server(80); // set web port number to 80

IPAddress local_IP(192, 168, 0, 123);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

//////////////////////////////////////////////////////////////

void connect_WiFi(){
	// Print where it will connct
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  }

  Serial.println("\n\n");
  Serial.print("Connecting to: "+String(ssid)+" ");
  
  ////////////////////////////////
  WiFi.begin(ssid,password); // connect in WiFi

  while(WiFi.status() != WL_CONNECTED){
       delay(500);
       Serial.print(".");
    }
    
  //print local IP address and start web server
  Serial.print("\n\nWiFi connected in: "+String(ssid)+"\n\nIP address: ");
  Serial.print(WiFi.localIP());

  server.begin(); 
}