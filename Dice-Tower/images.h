#ifdef ESP32
// Only include on MH-ET LIVE MiniKit ESP32

// Logo - 128 x 64
static const unsigned char logoDiceTower[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xE0, 0x0F, 0xFE, 
  0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xA0, 0x0A, 0xAA, 0xA0, 0x0A, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xD6, 0x60, 0x0D, 0xD6, 0x60, 0x0D, 0x00, 0x0C, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xBF, 0xFA, 0xAB, 
  0xBF, 0x8A, 0x01, 0xC0, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0xC6, 0x00, 0x0F, 0x00, 0xC6, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A, 0x08, 0x07, 
  0x30, 0x07, 0x0A, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 
  0x55, 0x0D, 0x00, 0xF0, 0x00, 0x38, 0x12, 0xC0, 0x03, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xCA, 0x20, 0x00, 0x00, 0x00, 0x22, 0x80, 
  0x3C, 0x00, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x43, 0x00, 
  0x7E, 0x00, 0x44, 0x70, 0xC7, 0x03, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x0A, 0x84, 0x00, 0x00, 0x00, 0x84, 0x20, 0x02, 0x06, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x6D, 0x00, 0x00, 0x00, 0x0F, 0x04, 0x51, 
  0x05, 0x05, 0x00, 0x00, 0xAC, 0xAA, 0xAA, 0xAA, 0xAA, 0x86, 0x10, 0x02, 
  0x00, 0x30, 0x04, 0xFA, 0x87, 0x04, 0x00, 0x00, 0x58, 0x55, 0x55, 0x55, 
  0x55, 0x03, 0x20, 0x04, 0x00, 0x00, 0x08, 0x44, 0x41, 0x04, 0x00, 0x00, 
  0xB0, 0xAA, 0xAA, 0xAA, 0xAA, 0x01, 0x02, 0x08, 0x00, 0x00, 0x08, 0x88, 
  0x20, 0x08, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x84, 0x00, 
  0x00, 0x00, 0x08, 0x10, 0x10, 0x08, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x08, 0x21, 0x00, 0x00, 0x08, 0x20, 0x08, 0x0A, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x10, 0x42, 0x00, 0x00, 0x10, 0x40, 
  0x04, 0x0A, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x10, 0x80, 0x02, 0x11, 0x00, 0x00, 0x60, 0xF5, 0x55, 0xF5, 
  0xD5, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x11, 0x00, 0x00, 
  0xA0, 0x0A, 0xAA, 0x0A, 0xAA, 0x00, 0x80, 0xF8, 0x01, 0x00, 0x10, 0x80, 
  0x82, 0x11, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x00, 0xDE, 
  0x07, 0x00, 0x20, 0x40, 0x44, 0x12, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0x80, 0xDF, 0x0F, 0x00, 0x20, 0x20, 0x48, 0x22, 0x00, 0x00, 
  0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0xE0, 0xBF, 0x0F, 0x00, 0x20, 0x10, 
  0x90, 0x23, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0xF8, 0xBF, 
  0x1F, 0x00, 0x20, 0x08, 0x21, 0x20, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 
  0xD4, 0x00, 0xFE, 0x7F, 0x1F, 0x00, 0x40, 0xE4, 0x4E, 0x20, 0x00, 0x00, 
  0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0xCF, 0x7F, 0x3B, 0x00, 0x40, 0x42, 
  0x84, 0x40, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x87, 0xFF, 
  0x32, 0x00, 0x40, 0xA1, 0x0A, 0x41, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0xCE, 0xFC, 0x76, 0x00, 0xC0, 0xE0, 0x0F, 0x42, 0x00, 0x00, 
  0x60, 0xFD, 0x57, 0xFD, 0xD7, 0x00, 0x7E, 0xF8, 0x7D, 0x00, 0x80, 0x87, 
  0x02, 0x44, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xFC, 0x9C, 
  0xFD, 0x00, 0x00, 0x78, 0x01, 0x88, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0xFC, 0x0F, 0xFB, 0x00, 0x00, 0x80, 0x07, 0x90, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xF8, 0x9F, 0xFB, 0x01, 0x00, 0x00, 
  0x78, 0xA0, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0xF8, 0xFF, 
  0x04, 0x01, 0x00, 0x00, 0x80, 0xC7, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0xF0, 0x3F, 0xF5, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0xF0, 0xCF, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xE0, 0x73, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0xE0, 0xD4, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x3F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0x0A, 0x80, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xE5, 0x3F, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0xF2, 0xFF, 0x88, 0x02, 0x00, 0x00, 0x00, 0xE0, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0xF9, 0xFB, 0x35, 0xF9, 0x01, 0x1F, 0x00, 
  0xFC, 0x03, 0x3F, 0x00, 0x06, 0xF8, 0x80, 0x07, 0xA0, 0xF2, 0xE3, 0x71, 
  0xBC, 0xF3, 0x1F, 0x00, 0x7F, 0xC0, 0xEF, 0x00, 0x0E, 0xFF, 0xFC, 0x0F, 
  0x60, 0xC5, 0xF3, 0x73, 0x8E, 0xFB, 0x00, 0x80, 0x3F, 0xE0, 0xC0, 0x19, 
  0x9C, 0x07, 0x7C, 0x0C, 0xA0, 0xCA, 0xC7, 0x73, 0xC7, 0x39, 0x00, 0xC0, 
  0x39, 0x60, 0xC0, 0x0D, 0x98, 0x01, 0x38, 0x0E, 0x60, 0xD5, 0xD7, 0x3B, 
  0x17, 0xF8, 0x03, 0x00, 0x38, 0x70, 0xC0, 0x0D, 0xF8, 0x1F, 0x30, 0x07, 
  0xA0, 0xCA, 0xC7, 0xBB, 0xA3, 0xF8, 0x03, 0x00, 0x38, 0x70, 0xC0, 0x6D, 
  0xF8, 0x1F, 0xF8, 0x01, 0x60, 0xD5, 0xD3, 0xBB, 0xD3, 0x38, 0x00, 0x00, 
  0x38, 0x60, 0xE0, 0xFC, 0xF8, 0x01, 0xF8, 0x00, 0xA0, 0xCA, 0xE1, 0xBB, 
  0x23, 0x38, 0x00, 0x00, 0x38, 0x60, 0xF0, 0xFC, 0xF8, 0x01, 0x78, 0x00, 
  0x60, 0x05, 0xFC, 0x39, 0x87, 0x3B, 0x1C, 0x00, 0x38, 0xE0, 0x7C, 0xDE, 
  0xDC, 0xE1, 0xFC, 0x00, 0xA0, 0xE0, 0xFF, 0x3C, 0xFE, 0xF0, 0x1F, 0x00, 
  0x3C, 0x80, 0x1F, 0xCE, 0x9F, 0xFF, 0x9C, 0x3F, 0x60, 0xFD, 0x3F, 0x18, 
  0x00, 0xE0, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x80, 0x0F, 0x3F, 0x18, 0x1F, 
  0xB0, 0xFC, 0x87, 0x82, 0xAA, 0x01, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x58, 0x3D, 0x50, 0x55, 0x55, 0x03, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0x80, 0xAA, 0xAA, 
  0xAA, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0x1A, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, };
#endif

// Roll a dice - 128 x 64
static const unsigned char imgRollADice[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xE0, 0x0F, 0xFE, 
  0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xA0, 0x0A, 0xAA, 0xA0, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xD6, 0x60, 0x0D, 0xD6, 0x60, 0x0D, 0x00, 0x00, 
  0x00, 0x38, 0xE0, 0x81, 0x00, 0x01, 0x00, 0x00, 0xAA, 0xBF, 0xFA, 0xAB, 
  0xBF, 0x0A, 0x00, 0x00, 0x80, 0x5F, 0x50, 0x86, 0x00, 0x01, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 0x80, 0x47, 0x08, 0x8C, 
  0x00, 0x01, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A, 0x00, 0x00, 
  0x00, 0x62, 0x08, 0xCC, 0x80, 0x01, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 
  0x55, 0x0D, 0x00, 0x00, 0x00, 0x32, 0x0C, 0x4C, 0x80, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A, 0x00, 0x00, 0x00, 0x1A, 0x04, 0x44, 
  0x80, 0x00, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 
  0x00, 0x0F, 0x0C, 0x66, 0xC0, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x0A, 0x00, 0x00, 0x00, 0x0F, 0x88, 0xE3, 0xDF, 0x3F, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 0x00, 0xF3, 0xF3, 0x71, 
  0xFC, 0x38, 0x00, 0x00, 0xAC, 0xAA, 0xAA, 0xAA, 0xAA, 0x06, 0x00, 0x00, 
  0x00, 0x03, 0x00, 0x30, 0x60, 0x00, 0x00, 0x00, 0x58, 0x55, 0x55, 0x55, 
  0x55, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xB0, 0xAA, 0xAA, 0xAA, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x60, 0xF5, 0x55, 0xF5, 
  0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0x0A, 0xAA, 0x0A, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x11, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 
  0xD4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0xFD, 0x57, 0xFD, 0xD7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x04, 0x0F, 0x3C, 0x01, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x77, 0xC4, 0x89, 
  0x1F, 0x01, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 
  0x00, 0xC4, 0x64, 0xC8, 0x81, 0x01, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x00, 0x84, 0x24, 0xC4, 0x80, 0x00, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x84, 0x36, 0xC0, 
  0x8F, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x86, 0x32, 0xC0, 0x81, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x00, 0x40, 0x32, 0x40, 0x80, 0x00, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x20, 0x33, 0x58, 
  0x18, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 
  0x00, 0x1E, 0xE3, 0x87, 0x38, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x80, 0x03, 0x03, 0x80, 0xDF, 0x00, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x09, 0x04, 0x01, 0x80, 
  0x00, 0x10, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0xC9, 0x04, 0xC1, 0x99, 0x8C, 0x39, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x29, 0xE5, 0x21, 0xA4, 0x52, 0x12, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x2F, 0x15, 0xC1, 0xBC, 
  0x5E, 0x10, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 
  0x29, 0x15, 0x01, 0x85, 0x42, 0x52, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0xC9, 0xE4, 0xE1, 0x98, 0x8C, 0x21, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xB0, 0xAA, 0xAA, 0xAA, 0xAA, 0x01, 0x00, 0x00, 0x40, 0x98, 0x86, 0xC5, 
  0x9C, 0x04, 0x00, 0x00, 0x58, 0x55, 0x55, 0x55, 0x55, 0x03, 0x00, 0x00, 
  0xE0, 0xA4, 0x81, 0x2A, 0xA5, 0x04, 0x00, 0x00, 0xAC, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x06, 0x00, 0x00, 0x40, 0xA4, 0x80, 0xEA, 0xA5, 0x04, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 0x40, 0xA4, 0x80, 0x2A, 
  0xA4, 0x04, 0x00, 0x00, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0x1A, 0x00, 0x00, 
  0x40, 0x98, 0x80, 0xCA, 0x24, 0x07, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, };

// Dice detected - 128 x 64
static const unsigned char imgDiceDetected[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xE0, 0x0F, 0xFE, 
  0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xA0, 0x0A, 0xAA, 0xA0, 0x0A, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xD6, 0x60, 0x0D, 0xD6, 0x60, 0x0D, 0x00, 0x0C, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xBF, 0xFA, 0xAB, 
  0xBF, 0x8A, 0x01, 0xC0, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0xC6, 0x00, 0x0F, 0x00, 0xC6, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A, 0x08, 0x07, 
  0x30, 0x07, 0x0A, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 
  0x55, 0x0D, 0x00, 0xF0, 0x00, 0x38, 0x12, 0xC0, 0x03, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xCA, 0x20, 0x00, 0x00, 0x00, 0x22, 0x80, 
  0x3C, 0x00, 0x00, 0x00, 0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x43, 0x00, 
  0x7E, 0x00, 0x44, 0x70, 0xC7, 0x03, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x0A, 0x84, 0x00, 0x00, 0x00, 0x84, 0x20, 0x02, 0x06, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x6D, 0x00, 0x00, 0x00, 0x0F, 0x04, 0x51, 
  0x05, 0x05, 0x00, 0x00, 0xAC, 0xAA, 0xAA, 0xAA, 0xAA, 0x86, 0x10, 0x02, 
  0x00, 0x30, 0x04, 0xFA, 0x87, 0x04, 0x00, 0x00, 0x58, 0x55, 0x55, 0x55, 
  0x55, 0x03, 0x20, 0x04, 0x00, 0x00, 0x08, 0x44, 0x41, 0x04, 0x00, 0x00, 
  0xB0, 0xAA, 0xAA, 0xAA, 0xAA, 0x01, 0x02, 0x08, 0x00, 0x00, 0x08, 0x88, 
  0x20, 0x08, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x84, 0x00, 
  0x00, 0x00, 0x08, 0x10, 0x10, 0x08, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x08, 0x21, 0x00, 0x00, 0x08, 0x20, 0x08, 0x0A, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x10, 0x42, 0x00, 0x00, 0x10, 0x40, 
  0x04, 0x0A, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x10, 0x80, 0x02, 0x11, 0x00, 0x00, 0x60, 0xF5, 0x55, 0xF5, 
  0xD5, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x11, 0x00, 0x00, 
  0xA0, 0x0A, 0xAA, 0x0A, 0xAA, 0x00, 0x80, 0xF8, 0x01, 0x00, 0x10, 0x80, 
  0x82, 0x11, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x00, 0xDE, 
  0x07, 0x00, 0x20, 0x40, 0x44, 0x12, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0x80, 0xDF, 0x0F, 0x00, 0x20, 0x20, 0x48, 0x22, 0x00, 0x00, 
  0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0xE0, 0xBF, 0x0F, 0x00, 0x20, 0x10, 
  0x90, 0x23, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0xF8, 0xBF, 
  0x1F, 0x00, 0x20, 0x08, 0x21, 0x20, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 
  0xD4, 0x00, 0xFE, 0x7F, 0x1F, 0x00, 0x40, 0xE4, 0x4E, 0x20, 0x00, 0x00, 
  0xA0, 0x06, 0xAC, 0x06, 0xAC, 0x00, 0xCF, 0x7F, 0x3B, 0x00, 0x40, 0x42, 
  0x84, 0x40, 0x00, 0x00, 0x60, 0x05, 0x54, 0x05, 0xD4, 0x00, 0x87, 0xFF, 
  0x32, 0x00, 0x40, 0xA1, 0x0A, 0x41, 0x00, 0x00, 0xA0, 0x06, 0xAC, 0x06, 
  0xAC, 0x00, 0xCE, 0xFC, 0x76, 0x00, 0xC0, 0xE0, 0x0F, 0x42, 0x00, 0x00, 
  0x60, 0xFD, 0x57, 0xFD, 0xD7, 0x00, 0x7E, 0xF8, 0x7D, 0x00, 0x80, 0x87, 
  0x02, 0x44, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xFC, 0x9C, 
  0xFD, 0x00, 0x00, 0x78, 0x01, 0x88, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0xFC, 0x0F, 0xFB, 0x00, 0x00, 0x80, 0x07, 0x90, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xF8, 0x9F, 0xFB, 0x01, 0x00, 0x00, 
  0x78, 0xA0, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0xF8, 0xFF, 
  0x04, 0x01, 0x00, 0x00, 0x80, 0xC7, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0xF0, 0x3F, 0xF5, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 
  0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0xF0, 0xCF, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xE0, 0x73, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 
  0xD5, 0x00, 0xE0, 0xD4, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x55, 0x55, 0x55, 0xD5, 0x00, 0x00, 0x3F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x01, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x7E, 0xF0, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 
  0x1E, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x01, 0x0E, 0xC7, 0xFB, 0xF0, 0xC3, 0x7F, 0xF8, 0xC3, 
  0x8F, 0x87, 0x87, 0x7F, 0x3C, 0x0C, 0xDF, 0x01, 0x0E, 0x9E, 0x3B, 0x76, 
  0xE0, 0x3F, 0xE2, 0xE0, 0xC1, 0xC0, 0xB1, 0x0F, 0x06, 0x46, 0xDC, 0x01, 
  0x7E, 0x3E, 0x99, 0x37, 0xFE, 0x3F, 0x0E, 0x7E, 0x78, 0xFC, 0xBC, 0xC3, 
  0xE3, 0xC7, 0xD9, 0x01, 0x7E, 0x3E, 0x99, 0x3B, 0xFF, 0xFF, 0x0E, 0x3F, 
  0x7D, 0xFE, 0xDC, 0xE9, 0xF3, 0xDF, 0xC9, 0x01, 0x7E, 0x3E, 0xC9, 0x3F, 
  0xF0, 0xFF, 0x1E, 0xF0, 0x7D, 0x60, 0xFE, 0xEF, 0x03, 0xDF, 0xEB, 0x01, 
  0x7E, 0x1E, 0xCD, 0x3F, 0xFE, 0xFF, 0x0E, 0xFE, 0x7D, 0x7C, 0xFE, 0xEF, 
  0xE3, 0xDF, 0xE1, 0x01, 0x7E, 0x8F, 0xCD, 0xBF, 0xFF, 0xFF, 0xAF, 0xFF, 
  0x7D, 0x7F, 0xFE, 0xEF, 0xFB, 0xFF, 0xE5, 0x01, 0xFE, 0xC0, 0x8C, 0xA7, 
  0xE7, 0xFF, 0xB7, 0xE7, 0x7D, 0x4F, 0x3C, 0xEF, 0x7B, 0xFE, 0xFE, 0x01, 
  0x06, 0xF0, 0x1C, 0x78, 0xC7, 0x7F, 0x78, 0xC7, 0xFD, 0x8E, 0xC0, 0xEF, 
  0x77, 0x0C, 0xFF, 0x01, 0x06, 0xFC, 0xFC, 0x7F, 0xE0, 0x0F, 0x7F, 0xE0, 
  0xFD, 0xC0, 0xFF, 0xEF, 0x07, 0xE2, 0xE7, 0x01, 0xC6, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x01, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xAC, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x56, 0x55, 0x55, 0x55, 0x55, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0x1A, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, };
