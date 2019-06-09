//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2016-10-31 papa Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef ARDUINO
  #include "Arduino.h"
#endif

// #define NDEBUG

#ifdef NDEBUG

  #include <stdint.h>

  #define DPRINT(str)
  #define DPRINTLN(str)
  #define DHEX(b...)
  #define DHEXLN(b)
  #define DDEC(b)
  #define DDECLN(b)

  #define DINIT(baudrate,msg)
  #define DDEVINFO(dev)

#else

#ifdef ARDUINO
  template <class T>
  inline void DPRINT(T str) { Serial.print(str); }
  template <class T>
  inline void DPRINTLN(T str) { DPRINT(str); DPRINT(F("\n")); }
  inline void DHEX(uint8_t b) {
    if( b<0x10 ) Serial.print('0');
    Serial.print(b,HEX);
  }
  inline void DHEX(uint16_t b) { 
    if( b<0x10 ) Serial.print(F("000")); 
    else if( b<0x100 ) Serial.print(F("00"));
    else if( b<0x1000 ) Serial.print(F("0"));
    Serial.print(b,HEX);
  }
  inline void DHEX(uint32_t b) {
    if( b<0x10 ) Serial.print(F("0000000"));
    else if( b<0x100 ) Serial.print(F("000000"));
    else if( b<0x1000 ) Serial.print(F("00000"));
    else if( b<0x10000 ) Serial.print(F("0000"));
    else if( b<0x100000 ) Serial.print(F("000"));
    else if( b<0x1000000 ) Serial.print(F("00"));
    else if( b<0x10000000 ) Serial.print(F("0"));
    Serial.print(b,HEX);
  }

  template<typename TYPE>
  inline void DDEC(TYPE b) {
    Serial.print(b,DEC);
  }

  #define DINIT(baudrate,msg) \
    Serial.begin(baudrate); \
    DPRINTLN(msg);

  #define DDEVINFO(dev) \
    HMID devid; \
    dev.getDeviceID(devid); \
    DPRINT(F("ID: "));devid.dump(); \
    uint8_t serial[11]; \
    dev.getDeviceSerial(serial); \
    serial[10]=0; \
    DPRINT(F("  Serial: "));DPRINTLN((char*)serial);

#else

  #include <iostream>
  #include <iomanip>

  #ifndef F
    #define F(str) str
  #endif

  template <class T>
  inline void DPRINT(T str) { std::cout << str << std::flush; }
  template <class T>
  inline void DPRINTLN(T str) { std::cout << str << std::endl;  }
  inline void DHEX(uint8_t b) { std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)b; }
  inline void DHEX(uint16_t b) { std::cout << std::setw(4) << std::setfill('0') << std::hex << (int)b; }
  inline void DHEX(uint32_t b)  { std::cout << std::setw(8) << std::setfill('0') << std::hex << (int)b; }

  template<typename TYPE>
  inline void DDEC(TYPE b) { std::cout << std::dec << (int)b; }

#endif // ARDUINO

  inline void DHEX(const uint8_t* b,uint8_t l) {
    for( int i=0; i<l; i++, b++) {
      DHEX(*b); DPRINT(F(" "));
    }
  }
  inline void DHEXLN(uint8_t b) { DHEX(b); DPRINT(F("\n")); }
  inline void DHEXLN(uint16_t b) { DHEX(b); DPRINT(F("\n")); }
  inline void DHEXLN(uint32_t b) { DHEX(b); DPRINT(F("\n")); }
  template<typename TYPE>
  inline void DDECLN(TYPE b) { DDEC(b); DPRINT(F("\n")); }
  inline void DHEXLN(const uint8_t* b,uint8_t l) { DHEX(b,l); DPRINT(F("\n")); }

#endif

#endif
