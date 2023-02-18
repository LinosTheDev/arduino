#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); 

// for a led 
int
  lock = 6;

int serrure = 3; 


char st[20];

#include <LiquidCrystal.h>
#define I2C_ADDR

// initialize the library by associating any needed LCD interface
// with the arduino pin number it is connected to
const int rs = A3, en
  = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5,
  d6, d7);
void setup() 
{
  pinMode(lock, OUTPUT);
 
  pinMode (serrure,
  OUTPUT);
 
 
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("Access test via RFID tag");
  Serial.println();
  pinMode(A14,OUTPUT);

  pinMode(A13,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A2,OUTPUT);

  pinMode(A1,OUTPUT);
 digitalWrite(A14,LOW); 
 digitalWrite(A13,HIGH); 

  digitalWrite(A4,LOW); 
  digitalWrite(A0,LOW);
  digitalWrite(A2,LOW);

  digitalWrite(A1,HIGH);
  lcd.begin(16, 2);
}

void loop() 
{

  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:

  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  if ( ! mfrc522.PICC_IsNewCardPresent())
  
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {

    return;
  }
  Serial.print("Tag :");
  String tag= "";
  byte
  caractere;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i]
  < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);

     tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     tag.concat(String(mfrc522.uid.uidByte[i],
  HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  tag.toUpperCase();

  

  
 
 if (tag.substring(1) == "13 3E 9F 0D" || tag.substring(1)
  == "04 1D 87 62 7F 71 81" || tag.substring(1) == "03 02 5E 11")
  {

    digitalWrite(lock, HIGH);
    lcd.print("Access Allowed!!");
    Serial.println("TAG checked - Access allow !");
    Serial.println();
    delay(500);
    digitalWrite(lock,
  LOW);
    
    digitalWrite(serrure, LOW);
    lcd.clear();
    }
  
  else

  
  {
    lcd.clear();
    lcd.print(" Access denied!");
    Serial.println("Unknown tag - Access refused !!!");
    Serial.println();
  
    for (int i= 1;
  i<5 ; i++)
    {
     
      digitalWrite(lock, HIGH);
      delay(200);

      digitalWrite(lock, LOW);
      delay(200);
    }
  }
  delay(500);
  lcd.clear();
}
