
void readGps() {
  
  cleargps();
  String data;
  float deg,degDec,degWhole;
  File dataFile = SD.open("datalog_gps.txt", FILE_WRITE);
  if(GPS.fix==1){
    
  cleargps();
  degWhole=float(int(GPS.longitude/100));
  degDec = (GPS.longitude - degWhole*100)/60; 
  deg = degWhole + degDec; 
  if (GPS.lon=='W') {  
    deg= (-1)*deg;
  }

  data=String(deg,8);
  Serial.print(data);
  Serial.print('\t');
  dataFile.print(data);
  dataFile.print(',');
  dataFile.print('\t');

  cleargps();
  degWhole=float(int(GPS.latitude/100));
  degDec = (GPS.latitude - degWhole*100)/60; 
  deg = degWhole + degDec; 
  if (GPS.lat=='S') {  
    deg= (-1)*deg;
  }

  data=String(deg,8);
  Serial.print(data);
  Serial.print('\t');
  dataFile.print(data);
  dataFile.print(',');

  cleargps();
   
  data=String(GPS.altitude,4);
  Serial.print(data);
  Serial.print('\t');
  dataFile.print(data);
  dataFile.print(',');
  dataFile.print('\t');

  Serial.println();
  dataFile.println();
  dataFile.close();
  
  
  }

  else{
    Serial.print("91.41326,  ");
    Serial.print("26.11284");
    Serial.println();
  }

  
}

void cleargps(){
  char c;
   while(!GPS.newNMEAreceived()){
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

   while(!GPS.newNMEAreceived()){
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

   while(!GPS.newNMEAreceived()){
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

   while(!GPS.newNMEAreceived()){
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
}
