#define GRBLED_PIN_R 6
#define GRBLED_PIN_G 5
#define GRBLED_PIN_B 3
#define BTN1 10
#define BTN2 11
#define BTN3 12
#define BTN4 13


int mode = 0, frozen_mode = 0;
float rgbled_r = 255.0, rgbled_g = 0.0, rgbled_b = 0.0, rainbow_step = 0.25, rgbled = 0.2, k = 0.01;
bool frozen = false;


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
  delay(333);
  analogWrite(GRBLED_PIN_R, 255);
  analogWrite(GRBLED_PIN_G, 0);
  analogWrite(GRBLED_PIN_B, 255);
  delay(333);
  analogWrite(GRBLED_PIN_R, 255);
  analogWrite(GRBLED_PIN_G, 255);
  analogWrite(GRBLED_PIN_B, 0);
  delay(333);
}

void loop(){
  if (!digitalRead(BTN1) || !digitalRead(BTN2)) {
    if (!digitalRead(BTN1)) {
      analogWrite(GRBLED_PIN_R, 255);
      analogWrite(GRBLED_PIN_G, 0);
    } else {
      analogWrite(GRBLED_PIN_R, 0);
      analogWrite(GRBLED_PIN_G, 255);
    }
    analogWrite(GRBLED_PIN_B, 255);
    delay(2000);
    if (frozen) {
      if (mode == 0) {
        analogWrite(GRBLED_PIN_R, 255 - rgbled_r / 1);
        analogWrite(GRBLED_PIN_G, 255 - rgbled_g / 1);
        analogWrite(GRBLED_PIN_B, 255 - rgbled_b / 1);
      } else {
        analogWrite(GRBLED_PIN_R, rgbled_r / 1);
        analogWrite(GRBLED_PIN_G, rgbled_g / 1);
        analogWrite(GRBLED_PIN_B, rgbled_b / 1);
      }
    }
  } else if (frozen && !digitalRead(BTN3)) {
    frozen_mode = (frozen_mode + 1) % 2;
    rgbled = 0.5;
    k = 0.01;
    delay(300);
  } else if (!digitalRead(BTN3)) {
    mode = (mode + 1) % 2;
    delay(300);
  } else if (!digitalRead(BTN4)) {
    frozen_mode = 0;
    frozen = !frozen;
    rgbled = 0.5;
    k = 0.01;
    analogWrite(GRBLED_PIN_R, 255);
    analogWrite(GRBLED_PIN_G, 255);
    analogWrite(GRBLED_PIN_B, 255);
    delay(100);
    if (mode == 0) {
      analogWrite(GRBLED_PIN_R, 255 - rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, 255 - rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, 255 - rgbled_b / 1);
    } else {
      analogWrite(GRBLED_PIN_R, rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, rgbled_b / 1);
    }
    delay(200);
  } else if (!frozen && (mode == 0 || mode == 1)) {
    if (rgbled_r == 255) {
      rgbled_r = 255 - rainbow_step;
      rgbled_g = rainbow_step;
    } else if (rgbled_g == 255) {
      rgbled_g = 255 - rainbow_step;
      rgbled_b = rainbow_step;
    } else if (rgbled_b == 255) {
      rgbled_b = 255 - rainbow_step;
      rgbled_r = rainbow_step;
    } else if (rgbled_r && rgbled_g) {
      rgbled_r -= rainbow_step;
      rgbled_g += rainbow_step;
    } else if (rgbled_g && rgbled_b) {
      rgbled_g -= rainbow_step;
      rgbled_b += rainbow_step;
    } else if (rgbled_b && rgbled_r) {
      rgbled_b -= rainbow_step;
      rgbled_r += rainbow_step;
    }
    if (mode == 0) {
      analogWrite(GRBLED_PIN_R, 255 - rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, 255 - rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, 255 - rgbled_b / 1);
    } else {
      analogWrite(GRBLED_PIN_R, rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, rgbled_b / 1);
    }
    delay(70);
  } else if (frozen && frozen_mode == 0) {
    if (mode == 0) {
      analogWrite(GRBLED_PIN_R, 255 - rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, 255 - rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, 255 - rgbled_b / 1);
    } else {
      analogWrite(GRBLED_PIN_R, rgbled_r / 1);
      analogWrite(GRBLED_PIN_G, rgbled_g / 1);
      analogWrite(GRBLED_PIN_B, rgbled_b / 1);
    }
    delay(50);
  } else if (frozen && frozen_mode == 1) {
    rgbled += k;
    if (rgbled <= 0.2) k = 0.01;
    else if (rgbled >= 0.97) k = -0.01;
    if (mode == 0) {
      analogWrite(GRBLED_PIN_R, 255 - rgbled_r * rgbled / 1);
      analogWrite(GRBLED_PIN_G, 255 - rgbled_g * rgbled / 1);
      analogWrite(GRBLED_PIN_B, 255 - rgbled_b * rgbled / 1);
    } else if (mode == 1) {
      analogWrite(GRBLED_PIN_R, rgbled_r * rgbled / 1);
      analogWrite(GRBLED_PIN_G, rgbled_g * rgbled / 1);
      analogWrite(GRBLED_PIN_B, rgbled_b * rgbled / 1);
    }
    delay(100);
  }
}
