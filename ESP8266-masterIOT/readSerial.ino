


void readSerial(){
  String command;
  if(Serial.available()){
     command = Serial.readString();
     //Serial.println(c);

      if(command == "A"){        
        SendIR(0);
        //Serial.println("Commando IR okay!");
      }
  }
}
