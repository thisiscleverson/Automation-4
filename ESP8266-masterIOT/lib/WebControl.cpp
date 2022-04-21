//library
#include <FS.h>


String header; // variable to store the HTTP req uest
String webPage = "";

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


String WebServer(){
	  
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
        header = "";
                          
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
                      
                      //request(); // verific the commands
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
        
        //header = ""; // clear the header variable

        //Close the connection
        client.stop();
        //Serial.println("Client Disconnected\n\n"); 

    }//end if Client

    return header; 

}

void clearHeader(){
    header = "";
}

            
