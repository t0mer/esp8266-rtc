# esp8266-rtc

An ESP8266 real-time clock. At startup it gets the time from an NTP server over Wi-Fi, stores it in a DS1307 RTC module, and then shows the date and time from the RTC on a 16×2 I²C LCD.

## Features

* Sets the DS1307 RTC from NTP (`3.il.pool.ntp.org`) on every boot.
* Displays `Date: DD/MM/YYYY` on the first line and `Time: HH:MM:SS` on the second, refreshed every second.
* Shows a `Real Time Clock` splash screen for 3 seconds at startup.

## Hardware

* An ESP8266 board (for example a NodeMCU or Wemos D1 mini).
* A DS1307 RTC module.
* A 16×2 character LCD with an I²C backpack at address **0x3F**.

Both modules share the I²C bus: connect SDA and SCL to the ESP8266's default I²C pins (GPIO 4 = SDA / D2 and GPIO 5 = SCL / D1 on NodeMCU-style boards), plus power and ground.

## Software

* [Arduino IDE](https://www.arduino.cc/en/software) with ESP8266 board support.
* Libraries (from the Arduino Library Manager):
  * [RTClib](https://github.com/adafruit/RTClib) by Adafruit
  * [NTPClient](https://github.com/arduino-libraries/NTPClient)
  * [LiquidCrystal I2C](https://github.com/johnrickman/LiquidCrystal_I2C) by Frank de Brabander (it is marked for AVR only, so the Arduino IDE may warn that it is incompatible with ESP8266)

## Configuration

Edit these values in [`RTC/RTC.ino`](RTC/RTC.ino):

| Setting | Default | Description |
|---------|---------|-------------|
| `ssid`, `password` | *(empty)* | Wi-Fi credentials |
| `utcOffsetInSeconds` | `10800` | Time zone offset from UTC in seconds (10800 = UTC+3). It is fixed, so there is no automatic daylight-saving change. |
| NTP server | `3.il.pool.ntp.org` | Set in the `NTPClient` constructor |
| LCD address and size | `0x3F`, 16×2 | Set in the `LiquidCrystal_I2C` constructor; many backpacks use `0x27` instead |

## Usage

1. Fill in the Wi-Fi credentials and your UTC offset.
2. Select your ESP8266 board and port, then upload.
3. The serial monitor (at **57600** baud) shows `Connecting to WiFi...` until the board joins the network, then `Time and date set`.

## Limitations

* Wi-Fi is required at every boot: the sketch waits for it forever before showing the time, so the RTC is not used as a fallback when there is no network.
* The time is requested from NTP only once, at startup, and the result is not checked. If the request fails (about a 1-second timeout), the RTC is set to an invalid date that stays until the next successful boot.

## License

[GNU General Public License v3.0](LICENSE)
