#include <Wire.h>
#include<SoftwareSerial.h>
#include<Adafruit_GPS.h>
#include <SD.h>
#include <SPI.h>

File dataFile;

const int chipsel=4;
boolean SetData = false;
SoftwareSerial gps(3,2);
Adafruit_GPS GPS(&gps);



int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
long gyro_x_cal, gyro_y_cal;
int gyro_x, gyro_y; 

float Acceleration_angle[3];
float Gyro_angle[3];
float Total_angle[3];

float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;

void setup() {
  Wire.begin(); 
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);

  time = millis(); 
  gps.begin(9600);
  setup_mpu_6050_registers();
  readGyro();
  calbiGyro();

  if(!SD.begin(4)) {
    Serial.println("Data_Recorder_Not_Responding!!!!!");
    while (1);
  }
  Serial.println("Data_Recorder_Intialized");
  
}

void loop() {
    
    timePrev = time;  
    time = millis(); 
    elapsedTime = (time - timePrev) / 1000; 
    
    File dataFile = SD.open("datalog_imu.txt", FILE_WRITE);
    
    readAcc();
    Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
    Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
    
    readGyro();
    
    
    Gyro_angle[0] = gyro_x/65.5; 
    Gyro_angle[1] = gyro_y/65.5;
    
    
    Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
    Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
    
    
    Serial.print(Total_angle[0]);
    Serial.print('\t');
    dataFile.print(Total_angle[0]);
    dataFile.print(',');
    dataFile.print('\t');
    Serial.print(Total_angle[1]);
    dataFile.print(Total_angle[1]);
    dataFile.println();
    Serial.println();
    dataFile.close();
}

void calbiGyro(){
  
 

   for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                  
                                             
    gyro_x_cal += Gyr_rawX;                                             
    gyro_y_cal += Gyr_rawY;                                             
                                                
    delay(3);                                                          
  }

    gyro_x_cal /= 2000;                                                  
    gyro_y_cal /= 2000;     

    gyro_x -= gyro_x_cal;
    gyro_y -= gyro_y_cal;
   
  
}

void readAcc(){

     Wire.beginTransmission(0x68);
     Wire.write(0x3B);
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true); 
    
     Acc_rawX=Wire.read()<<8|Wire.read(); 
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();
  
}

void readGyro(){

   Wire.beginTransmission(0x68);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true);
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); 
   Gyr_rawY=Wire.read()<<8|Wire.read();
  
}

void setup_mpu_6050_registers(){
  
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x6B);                                                    
  Wire.write(0x00);                                                    
  Wire.endTransmission();                                              
  
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x1C);                                                    
  Wire.write(0x10);                                                    
  Wire.endTransmission();                                              
 
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x1B);                                                    
  Wire.write(0x08);                                                    
  Wire.endTransmission();                                              
}
