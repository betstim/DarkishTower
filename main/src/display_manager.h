#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#if !defined(SIMULATION)
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#else
// Simple simulation stub used when building with -DSIMULATION (Wokwi, CI, etc.)
#include <Arduino.h>
// Minimal color definitions used by the code (standard RGB565 values)
#define ST77XX_BLACK   0x0000
#define ST77XX_WHITE   0xFFFF
#define ST77XX_RED     0xF800
#define ST77XX_GREEN   0x07E0
#define ST77XX_BLUE    0x001F
#define ST77XX_YELLOW  0xFFE0
#define ST77XX_CYAN    0x07FF
#define ST77XX_MAGENTA 0xF81F

class Adafruit_ST7789 {
public:
  Adafruit_ST7789(int8_t cs, int8_t dc, int8_t rst) {}
  void init(int w, int h) { width_ = w; height_ = h; }
  void setSPISpeed(uint32_t) {}
  void setFont(const void*) {}
  void setTextWrap(bool) {}
  void fillScreen(uint16_t) { Serial.println("[SIM] fillScreen"); }
  void drawRGBBitmap(int16_t x, int16_t y, const uint16_t* p, int16_t w, int16_t h) { Serial.printf("[SIM] drawRGBBitmap %d,%d %dx%d\n", x, y, w, h); }
  void startWrite() {}
  void setAddrWindow(int16_t, int16_t, int16_t, int16_t) {}
  void writePixels(const uint16_t*, int16_t) {}
  void endWrite() {}
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t) { Serial.printf("[SIM] fillRect %d,%d %dx%d\n", x, y, w, h); }
  void setCursor(int16_t x, int16_t y) { cursorX = x; cursorY = y; }
  void setTextColor(uint16_t) {}
  void print(const String& s) { cursorX += s.length() * 6; }
  int16_t getCursorX() { return cursorX; }
  int16_t width() { return width_; }
  int16_t height() { return height_; }
private:
  int16_t width_ = 240;
  int16_t height_ = 320;
  int16_t cursorX = 0;
  int16_t cursorY = 0;
};
#endif
#include <array>
#include <vector>
#include "screen_layout.h"

// If building for Wokwi (online simulator), use these default pin mappings
// and allow the real Adafruit ST7789 driver to be used. Adjust wiring in
// the Wokwi editor to match these pins.
#if defined(WOKWI)
  #define TFT_CS         5
  #define TFT_RST        17
  #define TFT_DC         16
#endif

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        6//10
  #define TFT_RST        -1//9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         5//3//8
#endif

class DisplayManager {

public:
    void setup();
    
    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t *pcolors);
    void drawRGBBitmap2X( int16_t x, int16_t y, const uint16_t *pcolors);

    void repaint();

    const ScreenLayout& getState() const {
        return mDesiredLayout;
    }
    int getSelection() const {
        return mDesiredLayout.mSelection;
    }
    TextLine getSelectedOption() {
        return mDesiredLayout.mOptions[getSelection()];
    }

    void setTitle(const String& title);
    String getTitle() const;

    void setBitmapsAndValues(const uint16_t* primaryBitmap, const uint16_t* secondaryBitmap);
    void setBitmapAndValue(const uint16_t* primaryBitmap, int value);
    void clearBitmaps();

    void setValues(int left, int right, uint16_t leftColor, uint16_t rightColor);
    void clearValues();

    void addInfo(const String& text, uint16_t color);
    void clearInfo();

    void addOption(const String& text, uint16_t value);
    void clearOptions();
    int32_t getOptionCount();
     
    void pinSelection();

    void setSelection(int index);
    
    void forceRepaint();

    int16_t drawTextCentered(const String& text, int yPos, uint16_t color);

    void setDesiredLayout(const ScreenLayout& layout);
    void update();
   
private:
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
    ScreenLayout mCurrentLayout;
    ScreenLayout mDesiredLayout;
    bool mForceRepaint= true;
    int mStartLine= 0;

    int mPostTitleVert = 0;
    int mPostBitmapVert = 0;
    int mPostNumbersVert = 0;
    int mPostTextVert = 0;
    int mPostOptionsVert = 0;
};

#endif // DISPLAY_MANAGER_H