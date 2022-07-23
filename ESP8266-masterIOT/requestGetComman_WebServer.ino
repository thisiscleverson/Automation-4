


void request(String command){        
        if(command.indexOf("GET /ESPIOT?r") >= 0){
            int pos1 = command.indexOf('r'); //red
            int pos2 = command.indexOf('g'); // green
            int pos3 = command.indexOf('b'); // blue
            int pos4 = command.indexOf('&');

            int red   = command.substring(pos1+1, pos2).toInt();
            int green = command.substring(pos2+1, pos3).toInt();
            int blue  = command.substring(pos3+1, pos4).toInt();

            setColor(red,green,blue,1);            
        }

        else if(command.indexOf("GET /ESPIOT?") >= 0){
            int pos = command.indexOf('?');
            int finally = command.indexOf('&');

            String command2 = command.substring(pos+1,finally); //to commands
            
            //////////////////////////////////////////////////////////////////////////

            if(command2 == "RainbowON"){ // turn on rainbow mode
                setColor(0,0,0,2);
            }   
            else if(command2 == "Light"){ // turn on or off the light
                Serial.write("L");
                delay(100);
            }
            else if(command2 == "airConditioning"){ //turn on air conditioning
                SendIR(0);
            }
        } 
}
