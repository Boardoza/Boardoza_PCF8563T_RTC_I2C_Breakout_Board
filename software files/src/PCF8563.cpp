#include "PCF8563.h"

/**
 * @brief Default constructor for PCF8563 class.
 * 
 * Initializes the internal wire pointer to the default Wire instance.
 */
PCF8563::PCF8563() : wire(&Wire) {}

/**
 * @brief Initializes the PCF8563 RTC module.
 *
 * Initializes the provided TwoWire instance and checks communication with the RTC module.
 *
 * @param wirePort Reference to the TwoWire instance to be used.
 * @return true if initialization and communication with RTC succeed.
 * @return false if communication with RTC fails.
 */
bool PCF8563::begin(TwoWire &wirePort) {
  wire = &wirePort;
  wire->begin();

  wire->beginTransmission(ADDRESS);
  if (wire->endTransmission() != 0) {
    return false;
  }
  return true;
}

/**
 * @brief Converts a decimal number to Binary Coded Decimal (BCD).
 *
 * @param val Decimal number to convert (0-99).
 * @return uint8_t BCD representation of the input number.
 */
uint8_t PCF8563::dec2bcd(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

/**
 * @brief Converts a Binary Coded Decimal (BCD) number to decimal.
 *
 * @param val BCD number to convert.
 * @return uint8_t Decimal representation of the input BCD number.
 */
uint8_t PCF8563::bcd2dec(uint8_t val) {
  return ((val / 16 * 10) + (val % 16));
}

/**
 * @brief Writes data to a specific register of the RTC.
 *
 * @param reg Register address to write to.
 * @param data Data byte to write.
 * @return true if writing succeeds.
 * @return false if writing fails.
 */
bool PCF8563::writeRegister(uint8_t reg, uint8_t data) {
  wire->beginTransmission(ADDRESS);
  wire->write(reg);
  wire->write(data);
  return (wire->endTransmission() == 0);
}

/**
 * @brief Reads data from specific registers of the RTC.
 *
 * @param reg Starting register address to read from.
 * @param buffer Pointer to a buffer where the read data will be stored.
 * @param len Number of bytes to read.
 * @return true if reading succeeds.
 * @return false if reading fails.
 */
bool PCF8563::readRegisters(uint8_t reg, uint8_t *buffer, uint8_t len) {
  wire->beginTransmission(ADDRESS);
  wire->write(reg);
  if (wire->endTransmission() != 0) {
    return false;
  }
  uint8_t count = wire->requestFrom(ADDRESS, len);
  if (count < len) {
    return false;
  }
  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = wire->read();
  }
  return true;
}

/**
 * @brief Sets the current time and date of the RTC.
 *
 * @param year Year value (full year, e.g., 2023).
 * @param month Month value (1-12).
 * @param day Day value (1-31).
 * @param hour Hour value (0-23).
 * @param minute Minute value (0-59).
 * @param second Second value (0-59).
 * @return true if setting the time succeeds.
 * @return false if setting the time fails.
 */
bool PCF8563::setTime(uint16_t year, uint8_t month, uint8_t day,
                      uint8_t hour, uint8_t minute, uint8_t second) {
  uint8_t buffer[7];

  buffer[0] = dec2bcd(second & 0x7F);
  buffer[1] = dec2bcd(minute);
  buffer[2] = dec2bcd(hour);
  buffer[3] = dec2bcd(day);
  buffer[4] = 0;

  if (year >= 2000) {
    buffer[5] = dec2bcd(month);
  } else {
    buffer[5] = 0x80 | dec2bcd(month);
  }

  buffer[6] = dec2bcd(year % 100);

  wire->beginTransmission(ADDRESS);
  wire->write(VL_SECONDS);
  for (uint8_t i = 0; i < 7; i++) {
    wire->write(buffer[i]);
  }
  return (wire->endTransmission() == 0);
}

/**
 * @brief Retrieves the current time and date from the RTC.
 *
 * @param dt Reference to a DateTime structure to store retrieved time and date.
 * @return true if retrieval succeeds.
 * @return false if retrieval fails.
 */
bool PCF8563::getTime(DateTime &dt) {
  uint8_t buffer[7];
  if (!readRegisters(VL_SECONDS, buffer, 7)) {
    return false;
  }
  
  dt.second = bcd2dec(buffer[0] & 0x7F);
  dt.minute = bcd2dec(buffer[1] & 0x7F);
  dt.hour = bcd2dec(buffer[2] & 0x3F);
  dt.day = bcd2dec(buffer[3] & 0x3F);
  dt.weekday = buffer[4] & 0x07;
  dt.month = bcd2dec(buffer[5] & 0x1F);
  uint8_t centuryFlag = (buffer[5] & 0x80) >> 7;
  dt.year = bcd2dec(buffer[6]);

  if (centuryFlag == 0) {
    dt.year += 2000;
  } else {
    dt.year += 1900;
  }
  return true;
}

/**
 * @brief Checks if the RTC time is valid.
 *
 * @return true if the RTC time is valid.
 * @return false if the RTC time is invalid or communication fails.
 */
bool PCF8563::isTimeValid() {
  uint8_t sec;
  if (!readRegisters(VL_SECONDS, &sec, 1)) {
    return false;
  }

  return !(sec & 0x80);
}