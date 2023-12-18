#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>  // Include the ESP8266WiFi library


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);

RTC_DS1307 RTC;

const char *ssid = "";
const char *password = "";
const long utcOffsetInSeconds = 10800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "3.il.pool.ntp.org",utcOffsetInSeconds);

void setup ()
{
  Serial.begin(57600);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  RTC.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Initialize NTP client
  timeClient.begin();

  // Update RTC with NTP time on startup
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  RTC.adjust(DateTime(epochTime));

  Serial.print("Time and date set");

  lcd.setCursor(0, 0);
  lcd.print("Real Time Clock");
  delay(3000);
  lcd.clear();
}

void loop () {
  // Use RTC time for all subsequent loops
  DateTime now = RTC.now();


  char formattedDate[11];
  char formattedTime[11];
  
  sprintf(formattedTime, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  sprintf(formattedDate, "%02d/%02d/%04d", now.day(), now.month(), now.year());

  String dateLabel = "Date: ";
  String timeLabel = "Time: ";

  lcd.setCursor(0, 0);
  lcd.print(dateLabel + formattedDate);

  lcd.setCursor(0, 1);
  lcd.print(timeLabel + formattedTime);

  delay(1000);
  lcd.clear();
}
