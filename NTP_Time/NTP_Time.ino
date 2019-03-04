#include <odroid_go.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

int currentHour = 0;
int currentMinutes = 0;
int currentSeconds = 0;

int ntpHour = 0;
int ntpMinutes = 0;
int ntpSeconds = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  GO.begin();

  GO.lcd.println("Hello, ODROID-GO");

  wifiMulti.addAP("OdroidGo", "password");
  wifiMulti.addAP("ssid_from_AP", "your_password_for_AP");
  Serial.print("Connecting Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.update();
  Serial.println();
  Serial.print("Time is now: ");
  Serial.println(timeClient.getFormattedTime());

  ntpHour, currentHour = timeClient.getHours();
  ntpMinutes, currentMinutes = timeClient.getMinutes();
  ntpSeconds = timeClient.getSeconds();

}

void displayGO() {
  GO.lcd.clearDisplay();

  GO.lcd.setCursor(40, 60);

  GO.lcd.setTextSize(2);

  GO.lcd.println("Time from internet is: ");
  GO.lcd.setCursor(140, 100);
  GO.lcd.println(String(currentHour) + ":" + String(currentMinutes));
}

void loop() {
  timeClient.update();
  ntpHour = timeClient.getHours();
  ntpMinutes   = timeClient.getMinutes();
  ntpSeconds = timeClient.getSeconds();

  if (currentMinutes != ntpMinutes) {
    if (currentHour != ntpHour) {
      currentHour = ntpHour;
      Serial.println("Hours changed!");
      Serial.println("Now is " + String(currentHour) + " hours");
    } else {
      Serial.println("Hours not changed.");
    }
    if (currentMinutes != ntpMinutes) {
      currentMinutes = ntpMinutes;
      Serial.println("Minutes changed!");
      Serial.println("Now is " + String(currentMinutes) + " minutes");
    } else {
      Serial.println("Minutes not changed.");
    }
    Serial.println();

    displayGO();
  }
}
