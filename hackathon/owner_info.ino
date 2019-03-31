void Owner_Info(){
  

  File dataFile = SD.open("datalog_owner_info.txt", FILE_WRITE);
  
  if (dataFile) {
    
  Serial.println("Enter Owner Name");
  String Owner_Name =  getData();
  dataFile.println("Owner_Name");
  
  Serial.println("Enter Owner Number");
  String Owner_Number =  getData();
  dataFile.println("Owner_Number");
  
  Serial.println("Enter Owner Date of Birth");
  String Date_of_Birth =  getData();
  dataFile.println("Date_of_Birth");
  
  Serial.println("Enter Owner Address");
  String Owner_Address =  getData();
  dataFile.println("Owner_Address");
  
  Serial.println("Enter Driver Licence Numer");
  String Driver_Licence_Numer =  getData();
  dataFile.println("Driver_Licence_Numer");
  
  Serial.println("Enter Vehicle Name");
  String Vehicle_Name =  getData();
  dataFile.println("Vehicle_Name");
  
  Serial.println("Enter Vehicle Number");
  String Vehicle_Number =  getData();
  dataFile.println("Vehicle_Number");
  
  Serial.println("Enter Emergency Contact 1");
  String Emergency_Contact_1 =  getData();
  dataFile.println("Emergency_Contact_1");
  
  Serial.println("Enter Emergency Contact 2");
  String Emergency_Contact_2 =  getData();
  dataFile.println("Emergency_Contact_2");
  
  Serial.println("Enter Emergency Contact 3");
  String Emergency_Contact_3 =  getData();
  dataFile.println("Emergency_Contact_3");
}
dataFile.close();
SetData = true;
}

String getData(){
  
  String data="";
  char ch=' ';
  if(Serial.available()){
    
    while(Serial.available()){
      ch = Serial.read();

      if(ch != '\n'){
        data += ch;
      }
    }
  }
  return data;
}
