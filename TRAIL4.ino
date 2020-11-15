#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;


char bookid1[] = "E9:8F:87:6D";
char bookid2[] = "7B:C9:81:22";

int issue1 = 0 ;
int issue2 = 0;

int issue3 = 0 ;
int issue4 = 0;

int issue5 = 0 ;
int issue6 = 0;

int issue7 = 0 ;
int issue8 = 0;

#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("\n\tLIBRARY MANAGEMENT SYSTEM");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("\t-------------------------");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("!!PLEASE CONFIRM THE BOOK AGAIN BEFORE ISSUE OR RETURN!!!");
  Serial.println("\n\nBIO-METRIC AUTHENTICATION REQUIRED ");
}

void loop()                     // run over and over again
{

  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("\nAUTHENTICATION SUCCESS"); Serial.print(finger.fingerID);
  Serial.print(" MATCH "); Serial.println(finger.confidence, "%");

  return bookissuedornot();
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("\nAUTHENTICATION SUCCESS   FINGER ID: 03012"); Serial.print(finger.fingerID);
  Serial.print("\tMATCH:"); Serial.println(finger.confidence);
  return bookissuedornot();
}








int bookissuedornot()
{

  if (finger.fingerID == 1)
  {


    Serial.print("HELLO GIRI SHANKAR , SHOW YOUR BOOK");
    //delay(5000);

repeat:
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {

      String strID = "";

      for (byte i = 0; i < 4; i++)
      {
        strID +=
          (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
          String(rfid.uid.uidByte[i], HEX) +
          (i != 3 ? ":" : "");
      }


      strID.toUpperCase();;


      if (strID == NULL)
      {
        Serial.print("\n\nBOOKS NOT FOUND");
      }
      else
      {
        if (strID == bookid1)
        {
          Serial.println("BOOK NO;345");
          Serial.println("CLASSMATES");
          if ( issue1 == 0)
          {
            Serial.println("issued");
            issue1 = 1;
            delay(5000);
          }

          else if (issue1 == 1)
          {
            Serial.println("returned");
            issue1 = 0;
            delay(5000);
          }
        }
        else if (strID == bookid2)
        {
          Serial.println("BOOK NO;346");
          Serial.println("WINGS OF FIRE");
          if ( issue2 == 0)
          {
            Serial.println("issued");
            issue2 = 1;
            delay(5000);
          }

          else if (issue2 == 1)
          {
            Serial.println("returned");
            issue2 = 0;
            delay(5000);
          }

        }


      }
    }
    else
    {
      goto repeat;
    }


  }




  else if (finger.fingerID == 2)
  {
    Serial.print("HELLO GIRI SHANKAR , SHOW YOUR BOOK");
    delay(5000);


    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {

      String strID = "";

      for (byte i = 0; i < 4; i++)
      {
        strID +=
          (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
          String(rfid.uid.uidByte[i], HEX) +
          (i != 3 ? ":" : "");
      }


      strID.toUpperCase();;


      if (strID == NULL)
      {
        Serial.print("\n\nBOOKS NOT FOUND");
      }
      else
      {
        if (strID == bookid1)
        {
          Serial.println("BOOK NO;345");
          Serial.println("CLASSMATES");
          if ( issue3 == 0)
          {
            Serial.println("issued");
            issue3 = 1;
            delay(5000);
          }

          else if (issue3 == 1)
          {
            Serial.println("returned");
            issue3 = 0;
            delay(5000);
          }
        }
        else if (strID == bookid2)
        {
          Serial.println("BOOK NO;346");
          Serial.println("WINGS OF FIRE");
          if ( issue4 == 0)
          {
            Serial.println("issued");
            issue4 = 1;

          }
          else if (issue4 == 1)
          {
            Serial.println("returned");
            issue4 = 0;
          }

        }


      }
    }
    else
    {
      goto repeat;
    }
  }



  else if (finger.fingerID == 3)
  {
    Serial.print("HELLO GIRI SANKAR , SHOW YOUR BOOK");
    delay(5000);


    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {

      String strID = "";

      for (byte i = 0; i < 4; i++)
      {
        strID +=
          (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
          String(rfid.uid.uidByte[i], HEX) +
          (i != 3 ? ":" : "");
      }


      strID.toUpperCase();;


      if (strID == NULL)
      {
        Serial.print("\n\nBOOKS NOT FOUND");
      }
      else
      {
        if (strID == bookid1)
        {
          Serial.println("BOOK NO;345");
          Serial.println("CLASSMATES");
          if ( issue5 == 0)
          {
            Serial.println("issued");
            issue5 = 1;
            delay(5000);
          }

          else if (issue5 == 1)
          {
            Serial.println("returned");
            issue5 = 0;
            delay(5000);
          }
        }
        else if (strID == bookid2)
        {
          Serial.println("BOOK NO;346");
          Serial.println("WINGS OF FIRE");
          if ( issue6 == 0)
          {
            Serial.println("issued");
            issue6 = 1;

          }
          else if (issue6 == 1)
          {
            Serial.println("returned");
            issue6 = 0;
          }

        }


      }
    }
    else
    {
      goto repeat;
    }
  }


  else if (finger.fingerID == 4)
  {
    Serial.print("HELLO GIRI SHANKAR , SHOW YOUR BOOK");
    delay(5000);


    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {

      String strID = "";

      for (byte i = 0; i < 4; i++)
      {
        strID +=
          (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
          String(rfid.uid.uidByte[i], HEX) +
          (i != 3 ? ":" : "");
      }

      strID.toUpperCase();


      if (strID == NULL )
      {
        Serial.print("\n\nBOOKS NOT FOUND");
      }
      else
      {
        if (strID == bookid1)
        {
          Serial.println("BOOK NO;345");
          Serial.println("CLASSMATES");
          if ( issue7 == 0)
          {
            Serial.println("issued");
            issue7 = 1;
            delay(5000);
          }

          else if (issue7 == 1)
          {
            Serial.println("returned");
            issue7 = 0;
            delay(5000);
          }
        }
        else if (strID == bookid2)
        {
          Serial.println("BOOK NO;346");
          Serial.println("WINGS OF FIRE");
          if ( issue8 == 0)
          {
            Serial.println("issued");
            issue8 = 1111;

          }
          else if (issue8 == 1)
          {
            Serial.println("returned");
            issue8 = 0;
          }

        }


      }
    }
    else
    {
      goto repeat;
    }
  }
  else
  {
    finger.getTemplateCount();
  }

  Serial.print(issue1);
  Serial.print(issue2);
  Serial.print(issue3);
  Serial.print(issue4);

  return finger.getTemplateCount();
}
