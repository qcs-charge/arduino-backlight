#define GRBLED_PIN_R 6
#define GRBLED_PIN_G 5
#define GRBLED_PIN_B 3
#define BTN1 12
#define BTN2 13
#define BTN3 11
#define BTN4 10

#define BTN_DELAY 2000

int rgbled_r=255, rgbled_g=0, rgbled_b=0, mode=0, rgbled=0, k=0, frozen=false;

void setup(){
  Serial.begin(9600);

  pinMode(GRBLED_PIN_R, OUTPUT);
  pinMode(GRBLED_PIN_G, OUTPUT);
  pinMode(GRBLED_PIN_B, OUTPUT);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);

  analogWrite(GRBLED_PIN_R, 0);
  analogWrite(GRBLED_PIN_G, 255);
  analogWrite(GRBLED_PIN_B, 255);
  delay(500);
  analogWrite(GRBLED_PIN_R, 255);
  analogWrite(GRBLED_PIN_G, 0);
  analogWrite(GRBLED_PIN_B, 255);
  delay(500);
  analogWrite(GRBLED_PIN_R, 255);
  analogWrite(GRBLED_PIN_G, 255);
  analogWrite(GRBLED_PIN_B, 0);
  delay(500);
}

void loop(){
  if (!digitalRead(BTN4)) {
    frozen = !frozen;
    delay(300);
  }
  if (!frozen) {
    if (!digitalRead(BTN1) && !digitalRead(BTN2)) {
      analogWrite(GRBLED_PIN_R, 0);
      analogWrite(GRBLED_PIN_G, 0);
      analogWrite(GRBLED_PIN_B, 255);
      delay(BTN_DELAY);
    } else if (!digitalRead(BTN1)) {
      analogWrite(GRBLED_PIN_R, 255);
      analogWrite(GRBLED_PIN_G, 0);
      analogWrite(GRBLED_PIN_B, 255);
      delay(BTN_DELAY);
    } else if (!digitalRead(BTN2)) {
      analogWrite(GRBLED_PIN_R, 0);
      analogWrite(GRBLED_PIN_G, 255);
      analogWrite(GRBLED_PIN_B, 255);
      delay(BTN_DELAY);
    } else if (!digitalRead(BTN3)) {
      mode = (mode + 1) % 7;
      rgbled = 0;
      k = 1;
      delay(300);
    } else if (mode == 0) {
      if (rgbled_r == 255) {
        rgbled_r = 254;
        rgbled_g = 1;
      } else if (rgbled_g == 255) {
        rgbled_g = 254;
        rgbled_b = 1;
      } else if (rgbled_b == 255) {
        rgbled_b = 254;
        rgbled_r = 1;
      } else if (rgbled_r && rgbled_g) {
        --rgbled_r;
        ++rgbled_g;
      } else if (rgbled_g && rgbled_b) {
        --rgbled_g;
        ++rgbled_b;
      } else if (rgbled_b && rgbled_r) {
        --rgbled_b;
        ++rgbled_r;
      }
      analogWrite(GRBLED_PIN_R, 255-rgbled_r);
      analogWrite(GRBLED_PIN_G, 255-rgbled_g);
      analogWrite(GRBLED_PIN_B, 255-rgbled_b);
      delay(30);
    } else if (mode == 1) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255 - rgbled);
      analogWrite(GRBLED_PIN_G, 255 - rgbled);
      analogWrite(GRBLED_PIN_B, 255 - rgbled);
      delay(30);
    } else if (mode == 2) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255 - rgbled);
      analogWrite(GRBLED_PIN_G, 255);
      analogWrite(GRBLED_PIN_B, 255);
      delay(30);
    } else if (mode == 3) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255);
      analogWrite(GRBLED_PIN_G, 255 - rgbled);
      analogWrite(GRBLED_PIN_B, 255);
      delay(30);
    } else if (mode == 4) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255);
      analogWrite(GRBLED_PIN_G, 255);
      analogWrite(GRBLED_PIN_B, 255 - rgbled);
      delay(30);
    } else if (mode == 5) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255 - rgbled);
      analogWrite(GRBLED_PIN_G, 255 - rgbled);
      analogWrite(GRBLED_PIN_B, 255);
      delay(30);
    } else if (mode == 6) {
      if (rgbled == 255) {
        k = -abs(k);
      } else if (rgbled == 1) {
        k = abs(k);
      }
      rgbled = (rgbled + k) % 256;
      analogWrite(GRBLED_PIN_R, 255);
      analogWrite(GRBLED_PIN_G, 255 - rgbled);
      analogWrite(GRBLED_PIN_B, 255 - rgbled);
      delay(30);
    }
  } else {
    delay(100);
  }
}
