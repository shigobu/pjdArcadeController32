#include "Adafruit_TinyUSB.h"

#define VID 0x0F0D
#define PID 0x00FB

#define TUD_HID_REPORT_DESC_GAMEPAD_MIKU(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_GAMEPAD  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
    /* 8 bit X, Y, Z, Rz, Rx, Ry (min 0, max 255 ) */ \
    HID_USAGE_PAGE     ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE          ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE          ( HID_USAGE_DESKTOP_Y                    ) ,\
    HID_USAGE          ( HID_USAGE_DESKTOP_Z                    ) ,\
    HID_USAGE          ( HID_USAGE_DESKTOP_RZ                   ) ,\
    HID_PHYSICAL_MIN   ( 0                                      ) ,\
    HID_PHYSICAL_MAX   ( 0xff                                   ) ,\
    HID_REPORT_COUNT   ( 4                                      ) ,\
    HID_REPORT_SIZE    ( 8                                      ) ,\
    HID_INPUT          ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 8 bit DPad/Hat Button Map  */ \
    HID_USAGE_PAGE     ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE          ( HID_USAGE_DESKTOP_HAT_SWITCH           ) ,\
    HID_LOGICAL_MIN    ( 1                                      ) ,\
    HID_LOGICAL_MAX    ( 8                                      ) ,\
    HID_PHYSICAL_MIN   ( 0                                      ) ,\
    HID_PHYSICAL_MAX_N ( 315, 2                                 ) ,\
    HID_REPORT_COUNT   ( 1                                      ) ,\
    HID_REPORT_SIZE    ( 8                                      ) ,\
    HID_INPUT          ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 32 bit Button Map */ \
    HID_USAGE_PAGE     ( HID_USAGE_PAGE_BUTTON                  ) ,\
    HID_USAGE_MIN      ( 1                                      ) ,\
    HID_USAGE_MAX      ( 32                                     ) ,\
    HID_LOGICAL_MIN    ( 0                                      ) ,\
    HID_LOGICAL_MAX    ( 1                                      ) ,\
    HID_REPORT_COUNT   ( 32                                     ) ,\
    HID_REPORT_SIZE    ( 1                                      ) ,\
    HID_INPUT          ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \

typedef struct TU_ATTR_PACKED
{
  uint8_t  x;        ///< Delta x  movement of left analog-stick
  uint8_t  y;        ///< Delta y  movement of left analog-stick
  uint8_t  z;        ///< Delta z  movement of right analog-joystick
  uint8_t  rz;       ///< Delta Rz movement of right analog-joystick
  uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
  uint32_t buttons;  ///< Buttons mask for currently pressed buttons
}hid_gamepad_report_miku_t;

#define SDA 0
#define SCL 1

#define MPR121_TOUCH_THRESHOLD 20

#define BUTTON_PIN_A        2
#define BUTTON_PIN_B        3
#define BUTTON_PIN_Y        5
#define BUTTON_PIN_X        4
#define BUTTON_PIN_PLUS     12
#define BUTTON_PIN_MINUS    13
#define BUTTON_PIN_L        6
#define BUTTON_PIN_R        7
#define BUTTON_PIN_ZL       8
#define BUTTON_PIN_ZR       9
#define BUTTON_PIN_LB       10
#define BUTTON_PIN_RB       11

#define BUTTON_PIN_UP       14
#define BUTTON_PIN_LEFT     16
#define BUTTON_PIN_RIGHT    15
#define BUTTON_PIN_DOWN     17

#define BUTTON_CONT_A_bp    2
#define BUTTON_CONT_B_bp    1
#define BUTTON_CONT_Y_bp    0
#define BUTTON_CONT_X_bp    3
#define BUTTON_CONT_PLUS_bp   9
#define BUTTON_CONT_MINUS_bp  8
#define BUTTON_CONT_L_bp      4
#define BUTTON_CONT_R_bp      5
#define BUTTON_CONT_ZL_bp      6
#define BUTTON_CONT_ZR_bp      7
#define BUTTON_CONT_LB_bp      10
#define BUTTON_CONT_RB_bp      11

#define MPR121_ADDRESS1 0x5A
#define MPR121_ADDRESS2 0x5B
#define MPR121_ADDRESS3 0x5C
