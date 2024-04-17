#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>

#define FLAME_SENSOR_PIN 4 
#define BUZZER_PIN 2 // Definisikan pin untuk buzzer, ganti dengan pin yang sesuai

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi objek lcd dengan alamat I2C 0x27, 16 kolom, dan 2 baris

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  
  pinMode(FLAME_SENSOR_PIN, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT); // Atur pin buzzer sebagai output
  
  Wire.begin();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Baca nilai dari sensor api
  int flameState = digitalRead(FLAME_SENSOR_PIN);

  // Cek apakah api terdeteksi atau tidak
  if (flameState == HIGH) {
    Serial.println("Api terdeteksi => Terdeteksi kebakaran!");
    // Aktifkan buzzer jika api terdeteksi
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000); // Tambahkan delay 1000 ms
  } else {
    Serial.println("Tidak ada api => Tidak terdeteksi kebakaran");
    // Matikan buzzer jika tidak ada api
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Menampilkan nilai sensor pada LCD
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Sensor Api: ");
  lcd.setCursor(0, 1); 
  lcd.print(flameState == HIGH ? "Terdeteksi" : "Tidak Terdeteksi"); 

  delay(1000); 
}
