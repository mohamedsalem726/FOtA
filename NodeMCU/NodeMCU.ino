#include <FirebaseESP8266.h>  
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>


/* States */
#define  WAIT_NEW_UPADTE   0
#define  Upload    1


/* Pins */
#define RESET_PIN  D1

FirebaseData fbdo;

SoftwareSerial mySerial   (D6, D5);  // rx- tx

const char* ssid = "ENG";
const char* password = "17271620HFMS";
int new_flag ;
int state   ; 

#define FIREBASE_HOST "test-8f3d6-default-rtdb.firebaseio.com"             // the project name address from firebase id
#define FIREBASE_AUTH "Q4WFYaZsuVUm1Sf1TKIqtv78TAAE2uJ6E3yLjM55"              // the secret key generated from firebase

const char* FIRMWARE_HOST = "mohamedsalem.pythonanywhere.com" ;
const char* Fingerprint = "1E 18 9A EB D8 99 C2 0F 00 34 5E 7F 44 55 72 C9 25 5C 8F 33" ;

void setup()
{
  // define pin modes for tx, rx
  pinMode(14, INPUT);
  pinMode(12, OUTPUT);
  /* Intitialize Serial Communication */
  Serial.begin(9600);
  mySerial.begin(9600);

  /* Configure pin as output to reset rhe stm  */
  pinMode (RESET_PIN , OUTPUT);
  digitalWrite (RESET_PIN , HIGH);
     
  
  /* Connect to Wifi */
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wifi.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  /* Connect to Firebase */
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH) ;
  Serial.println(" "); 
}

  void loop() {

  Serial.println("Checking State....");
  Serial.println();
   if(Firebase.getInt(fbdo , "/App/State"))
      {
        if(fbdo.dataType() == "int")
        {
          state = fbdo.intData();
        }
      }

  switch (state){
    /************* Check for new Update ***************/
    case WAIT_NEW_UPADTE :
    Serial.println ("Waiting New Update");
    
      if(Firebase.getInt(fbdo , "/App/Flag"))
      {
        if(fbdo.dataType() == "int")
        {
          new_flag = fbdo.intData();
        }
      }
      if (new_flag == 1 || new_flag == 2){
        if(Firebase.setInt(fbdo,"/App/State" ,Upload))
        {
          Serial.println("Uploading....");
        }
        }  
      break ;


   
      
    /************* Download the new update ***************/
    case Upload : 
      int download_check = 1 ;
      while (download_check){
        Serial.println("Uploading");
        download_check = Download_Firmware();
        }
        
      Firebase.setInt(fbdo, "/App/State" ,WAIT_NEW_UPADTE );
      Firebase.setInt(fbdo, "/App/State" ,0 );
      
      break ;

    }
}


int Download_Firmware() {

  digitalWrite (RESET_PIN , LOW);
  delay(1000);
  digitalWrite (RESET_PIN , HIGH);
  delay(2000);
  
  int error_code = 0 ;
  WiFiClientSecure httpsClient;
  httpsClient.setFingerprint(Fingerprint);
  httpsClient.setTimeout(15000);
  delay(1000);
  Serial.print("HTTPS Connecting  ");
  int r=0; //retry counter
  while((!httpsClient.connect(FIRMWARE_HOST, 443)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  String Link ;
  if(new_flag == 1){
 Link = "/code1";
 }
 else if(new_flag == 2)
 {
  Link = "/code2";
 }


  Serial.print("requesting URL: ");
  Serial.println(FIRMWARE_HOST+Link);

  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + FIRMWARE_HOST + "\r\n" +               
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n'); //Read Line by Line
    send_Line(line);
    Serial.println(line); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");
 
  Firebase.setInt(fbdo, "/App/Flag" ,0 );
  
  
   return error_code ;
}

void send_Line(String Line)
{
  Serial.println("Sending..");

  long int Length = Line.length(); 
  int i;
  char y = 0;
  for(i=0 ; i<Length ; i++)
  {
         
        mySerial.write(Line[i]);
        
          
   }
   mySerial.write("\r\n");
   do
    {
     
          while(mySerial.available()== 0);
          y = mySerial.read();
          
          Serial.println(y);
          if( y == 'k')
          {
            Serial.println("Line Sending Completed.");
            break;
          }
    }while(1);
     
      
   }


  
