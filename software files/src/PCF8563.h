#ifndef PCF8563_H
#define PCF8563_H

#include <Arduino.h>
#include <Wire.h>

// PCF8563 Register Definitions (Datasheet Referansı)
#define CTRL_STATUS_1     0x00  // Control/Status Register 1
#define CTRL_STATUS_2     0x01  // Control/Status Register 2
#define VL_SECONDS        0x02  // VL (Voltage Low) & Seconds (BCD format)
#define MINUTES           0x03  // Minutes Register (BCD format)
#define HOURS             0x04  // Hours Register (BCD format)
#define DAYS              0x05  // Days Register (BCD format)
#define WEEKDAYS          0x06  // Weekdays Register (0-6)
#define CENTURY_MONTHS    0x07  // Century Flag & Months Register (BCD format)
#define YEARS             0x08  // Years Register (BCD format)
#define MINUTE_ALARM      0x09  // Minute Alarm Register (BCD format)
#define HOUR_ALARM        0x0A  // Hour Alarm Register (BCD format)
#define DAY_ALARM         0x0B  // Day Alarm Register (BCD format)
#define WEEKDAY_ALARM     0x0C  // Weekday Alarm Register (0-6)
#define CLKOUT_CTRL       0x0D  // Clock Output Control Register
#define TIMER_CTRL        0x0E  // Timer Control Register
#define TIMER             0x0F  // Timer Register
#define ADDRESS           0x51  // Address register

// Yapıyı tarih ve zaman bilgilerini saklamak için tanımlıyoruz.
struct DateTime {
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t day;
  uint8_t weekday;  // 0: Pazar, 1: Pazartesi, ...
  uint8_t month;
  uint16_t year;
};

class PCF8563 {
public:
  PCF8563();

  // Varsayılan olarak Wire kullanılarak başlatır.
  bool begin(TwoWire &wirePort = Wire);

  // Zamanı ayarlar. Örnek: 2023, 4, 3, 12, 34, 56
  bool setTime(uint16_t year, uint8_t month, uint8_t day,
               uint8_t hour, uint8_t minute, uint8_t second);

  // Zamanı okur ve DateTime yapısına doldurur.
  bool getTime(DateTime &dt);

  bool isTimeValid();

private:
  TwoWire *wire;

  // Yardımcı: Decimal ↔ BCD dönüşüm fonksiyonları.
  uint8_t dec2bcd(uint8_t val);
  uint8_t bcd2dec(uint8_t val);

  // Yardımcı: Belirli register’a yazma ve okuma işlemleri.
  bool writeRegister(uint8_t reg, uint8_t data);
  bool readRegisters(uint8_t reg, uint8_t *buffer, uint8_t len);
};

#endif // PCF8563_H
