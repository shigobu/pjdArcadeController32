#include <Wire.h>
#include <Adafruit_MPR121.h>

#include "Adafruit_TinyUSB.h"
#include "pjdArcadeController.h"

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_GAMEPAD_MIKU()
};

// USB HID object
Adafruit_USBD_HID usb_hid;

// Report payload defined in src/class/hid/hid.h
// - For Gamepad Button Bit Mask see  hid_gamepad_button_bm_t
// - For Gamepad Hat    Bit Mask see  hid_gamepad_hat_t
hid_gamepad_report_miku_t gp;

Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();

volatile uint8_t touch_X  = (uint8_t)0x10000000;
volatile uint8_t touch_Y  = (uint8_t)0x10000000;
volatile uint8_t touch_Z  = (uint8_t)0x10000000;
volatile uint8_t touch_RZ = (uint8_t)0x10000000;


void setup() {
  TinyUSBDevice.setID( VID, PID );

  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }  

  // Setup HID
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();

  // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
  if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
  }

  pinMode(BUTTON_PIN_A    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_B    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_Y    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_X    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_PLUS , INPUT_PULLUP);
  pinMode(BUTTON_PIN_MINUS, INPUT_PULLUP);
  pinMode(BUTTON_PIN_L    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_R    , INPUT_PULLUP);

  pinMode(BUTTON_PIN_UP    , INPUT_PULLUP);
  pinMode(BUTTON_PIN_LEFT  , INPUT_PULLUP);
  pinMode(BUTTON_PIN_RIGHT , INPUT_PULLUP);
  pinMode(BUTTON_PIN_DOWN  , INPUT_PULLUP);
//  pinMode(BUTTON_PIN_CENTER, INPUT_PULLUP);



}

void setup1() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  Wire.setSDA(SDA);
  Wire.setSCL(SCL);
  if (!cap1.begin(MPR121_ADDRESS1, &Wire)) {
    digitalWrite(LED_BUILTIN, 1);
    while (1) {
      ;
    }
  }
  if (!cap2.begin(MPR121_ADDRESS2, &Wire)) {
    digitalWrite(LED_BUILTIN, 1);
    while (1) {
      ;
    }
  }
  if (!cap3.begin(MPR121_ADDRESS3, &Wire)) {
    digitalWrite(LED_BUILTIN, 1);
    while (1) {
      ;
    }
  }

  // cap1.setThreshholds(5, 2);
  // cap2.setThreshholds(5, 2);
  // cap3.setThreshholds(5, 2);
}

void loop() {
  #ifdef TINYUSB_NEED_POLLING_TASK
  // Manual call tud_task since it isn't called by Core's background
  TinyUSBDevice.task();
  #endif

  // not enumerated()/mounted() yet: nothing to do
  if (!TinyUSBDevice.mounted()) {
    return;
  }

  if (!usb_hid.ready()) return;

  gp.x = touch_X;
  gp.y = touch_Y;
  gp.z = touch_Z;
  gp.rz = touch_RZ;

  gp.buttons = 0;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_A) << BUTTON_CONT_A_bp;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_B) << BUTTON_CONT_B_bp;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_Y) << BUTTON_CONT_Y_bp;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_X) << BUTTON_CONT_X_bp;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_PLUS ) << BUTTON_CONT_PLUS_bp ;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_MINUS) << BUTTON_CONT_MINUS_bp;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_L    ) << BUTTON_CONT_L_bp    ;
  gp.buttons |= !(uint)digitalRead(BUTTON_PIN_R    ) << BUTTON_CONT_R_bp    ;

  if (!digitalRead(BUTTON_PIN_UP) && !digitalRead(BUTTON_PIN_RIGHT)){
    gp.hat = GAMEPAD_HAT_UP_RIGHT;
  }
  else if (!digitalRead(BUTTON_PIN_UP) && !digitalRead(BUTTON_PIN_LEFT)){
    gp.hat = GAMEPAD_HAT_UP_LEFT;
  }
  else if (!digitalRead(BUTTON_PIN_DOWN) && !digitalRead(BUTTON_PIN_RIGHT)){
    gp.hat = GAMEPAD_HAT_DOWN_RIGHT;
  }
  else if (!digitalRead(BUTTON_PIN_DOWN) && !digitalRead(BUTTON_PIN_LEFT)){
    gp.hat = GAMEPAD_HAT_DOWN_LEFT;
  }
  else if (!digitalRead(BUTTON_PIN_UP)){
    gp.hat = GAMEPAD_HAT_UP;
  }
  else if (!digitalRead(BUTTON_PIN_DOWN)){
    gp.hat = GAMEPAD_HAT_DOWN;
  }
  else if (!digitalRead(BUTTON_PIN_RIGHT)){
    gp.hat = GAMEPAD_HAT_RIGHT;
  }
  else if (!digitalRead(BUTTON_PIN_LEFT)){
    gp.hat = GAMEPAD_HAT_LEFT;
  }
  else{
    gp.hat = GAMEPAD_HAT_CENTERED;
  }

  usb_hid.sendReport(0, &gp, sizeof(gp));


}

void loop1(){
  
}
