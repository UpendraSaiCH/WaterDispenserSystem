#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

const int rs = 2, en = 7, d4 = 5, d5 = 6, d6 = 8, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define SS_PIN 10
#define RST_PIN 9
const int mot=3;
const int user0=0;
const int user1=1;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
void setup() 
{
 lcd.begin(16, 2);
 Serial.begin(9600); // Initiate a serial communication
 SPI.begin(); // Initiate SPI bus
 mfrc522.PCD_Init(); // Initiate MFRC522
 Serial.println("Approximate your card to the reader...");
 Serial.println();
 pinMode(mot,LOW);
 pinMode(user0,OUTPUT);
 pinMode(user1,OUTPUT);

}
void loop() 
{


 // Look for new cards 
 if (! mfrc522.PICC_IsNewCardPresent()) 
 {
  lcd.setCursor(0, 0);
 lcd.println("     Welcome    ");
//  lcd.setCursor(0, 1);
// lcd.println("Dispencer");
 delay(3000);
  lcd.setCursor(0, 0);
 lcd.println("Place the card  ");
 lcd.setCursor(0, 1);
 lcd.println("                 ");
 delay(3000);
 }


 if ( ! mfrc522.PICC_ReadCardSerial())
 {
  return;
 }




 //Show UID on serial monitor
 Serial.print("UID tag :");
 String content= "";
 byte letter;
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 {
 Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
 Serial.print(mfrc522.uid.uidByte[i], HEX);
 content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 content.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 Serial.println();
 Serial.print("Message : ");
 content.toUpperCase();
 if ((content.substring(1) == "20 D2 55 2F")||(content.substring(1) == "61 4D F4 0B")||(content.substring(1) == "61 E5 D5 0A")||(content.substring(1) == "61 18 52 0A")) //change here the UID of the card/cards that you want to give access
 {
 Serial.println("Authorized access");
 Serial.println();
 lcd.setCursor(0, 0);

 // print the number of seconds since reset:
 lcd.print("Access authorised");
 digitalWrite(mot,HIGH);
 if((content.substring(1) == "20 D2 55 2F")){
    pinMode(user0,HIGH);
 }
  if((content.substring(1) == "61 4D F4 0B")){
    pinMode(user1,HIGH);
 }
 delay(10000);
 digitalWrite(mot,LOW);
 delay(3000);
 }
 else {
 Serial.println(" Access denied");
 lcd.setCursor(0, 0);
 // print the number of seconds since reset:
 lcd.print("Access denied!!!");
 digitalWrite(mot,LOW);
 delay(3000);
 }
}
