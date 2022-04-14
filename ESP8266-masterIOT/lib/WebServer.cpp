//library
#include <FS.h>


//variable
int red   = 0; 
int green = 0;
int blue  = 0;

String header; // variable to store the HTTP req uest
String webPage = "";

//set finction
void request();
void command(String command);


//function
void readFilesHTML(){
  
  //Read files HTML
  File rFile = SPIFFS.open("/index.html","r");
  webPage = rFile.readString();

 /*while(rFile.available()) {
    String line = rFile.readStringUntil('\n');
    webPage += line;
 }*/
  
  //Serial.println(webPage);
  rFile.close();  
}


void WebServer(){
	  
    WiFiClient client = server.available(); // client wifi

    /////////////////////////////////////
      static unsigned long currentTime  = millis();
      static unsigned long previousTime = 0;
      static const long    timeoutTime  = 1000; //(1000ms = 1s)
    /////////////////////////////////////
    

    if(client){
        currentTime  = millis();
        previousTime = currentTime;
        //Serial.println("New Client connecting.");
        String currentLine = "";
                          
        while(client.connected() && currentTime - previousTime <= timeoutTime){
            currentTime = millis();

            if(client.available()){
               char c = client.read();
                Serial.write(c);
                header += c;

                if(c == '\n'){
                   if(currentLine.length() == 0){
                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-type:text/html");
                      client.println("Connection: close");
                      client.println();
                   
                      // Display the HTML web page                      
                      client.println(webPage); 
                      client.println();
                      
                      request(); //function to request of client
                      break;                                                                    
        			} 
                    else{
                      currentLine = "";
                    }

               }
               else if(c != '\r'){
                    currentLine += c;                
                }//end else                  
            }
        }
        
        header = ""; // clear the header variable

        //Close the connection
        client.stop();
        //Serial.println("Client Disconnected\n\n"); 

    }//end if Client
}


void request(){

	if(header.indexOf("GET /ESPIOT?r") >= 0){
        int pos1 = header.indexOf('r'); //red
        int pos2 = header.indexOf('g'); // green
        int pos3 = header.indexOf('b'); // blue
        int pos4 = header.indexOf('&');

        red   = header.substring(pos1+1, pos2).toInt();
        green = header.substring(pos2+1, pos3).toInt();
        blue  = header.substring(pos3+1, pos4).toInt();

        //setColor(red,green,blue,0);

    }
    else if(header.indexOf("GET /ESPIOT?") >= 0){
        int pos = header.indexOf('?');
        int finally = header.indexOf('&');

        command(header.substring(pos+1,finally)); // function to commands

    }                  
}


void command(String command){

	if(command == "RainbowON"){
		Serial.println("Rainbow ON");
	}
	else if(command == ""){

	}
	else if(command == ""){

	}
}