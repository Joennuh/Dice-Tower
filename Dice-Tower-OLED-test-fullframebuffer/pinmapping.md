# Pin mapping

| Function  | D1 mini | ESP32 MiniKit |
| :-------- | :-----: | :-----------: |
| CFG_LED   | D0      | IO26          |
| EYE1_LED  | D1      | IO22          |
| EYE2_LED  | D2      | IO21          |
| FIRE1_LED | D6      | IO19          |
| FIRE2_LED | D7      | IO23          |
| FIRE3_LED | D8      | IO5           |
| IND_LED   | -       | IO14 (TMS)    |
| TRIGGER   | D3      | IO17          |
| CFG_BTN   | D5      | IO18          |
| UP_BTN    | -       | IO35          |
| SEL_BTN   | -       | IO33          |
| DWN_BTN   | -       | IO34          |
| SCK       | -       | IO27          |
| SDA       | -       | IO25          |
| RNDMSD    | A0      | IO36 (SVP)    |

## Remarks

* **IND_LED:** Display indicator led (for display module).
* **UP_BTN, SEL_BTN, DWN_BTN:** Navigational buttons for display module.
* **SCK, SDA:** Software I2C for SSD1306 display on display module.
* **RNDMSD:** Random seed. Analog pin. Should not be connected to anything. Noise of it is used to drive the random generator.