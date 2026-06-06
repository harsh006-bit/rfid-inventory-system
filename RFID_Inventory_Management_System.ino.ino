#RST_PIN D0

#define GREEN_LED D4
#define RED_LED D1
#define BUZZER D2

MFRC522 mfrc522(SS_PIN, RSTinclude <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define _PIN);

String validUID = "13 19 DA 2C";

void setup() {
  Serial.begin(115200);

  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("RFID Inventory System Ready 1");
  Serial.println("Scan RFID Tag...");
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent())
    return;

  if (!mfrc522.PICC_ReadCardSerial())
    return;

  String tagID = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10)
      tagID += "0";

    tagID += String(mfrc522.uid.uidByte[i], HEX);
    tagID += " ";
  }

  tagID.trim();
  tagID.toUpperCase();

  Serial.print("UID: ");
  Serial.println(tagID);

  if (tagID == validUID) {

    Serial.println("ITEM FOUND");

    digitalWrite(GREEN_LED, HIGH);

    tone(BUZZER, 1000);
    delay(300);
    noTone(BUZZER);

    delay(1000);

    digitalWrite(GREEN_LED, LOW);

  } else {

    Serial.println("UNKNOWN ITEM");

    digitalWrite(RED_LED, HIGH);

    for (int i = 0; i < 3; i++) {
      tone(BUZZER, 3000);
      delay(500);
      noTone(BUZZER);
    }

    digitalWrite(RED_LED, LOW);
  }

  Serial.println("------------------");

  mfrc522.PICC_HaltA();
}