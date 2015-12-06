#define PWM_PIN (0)
#define BUTTON_PIN (3)

// Full-bright duty cycle, where 0 = 0% and 255 = 100%
#define MAX_BRIGHTNESS (0xc0)

// How long the light stays on at full brightness
#define ON_DURATION_MSEC (15 * 60 * 1000)

// How long the dim phase lasts
#define DIM_DURATION_MSEC (5 * 60 * 1000)

// The amount of time we'll delay at a single time in the
// main loop. Larger makes the button less responsive.
// Shorter could theoretically use more power, but probably
// not and even if it does, it doesn't matter.
#define DELAY_MSEC (5)

enum {
  STATE_ON = 0,
  STATE_DIMMING,
  STATE_OFF
};

int state = STATE_ON;
int state_msec_remaining = ON_DURATION_MSEC;
int current_duty_cycle = MAX_BRIGHTNESS;
// see below about pullup & why button is normally high
int last_button_state = HIGH;

void setup() {
  pinMode(PWM_PIN, OUTPUT);

  // http://forum.arduino.cc/index.php?topic=142041.0
  // INPUT_PULLUP means the pin is normally in a HIGH state when
  // unconnected to anything.
#ifdef INPUT_PULLUP
  pinMode(BUTTON_PIN, INPUT_PULLUP);
#else
  // https://digistump.com/board/index.php?topic=1430.0
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
#endif

  // fade-on the light at startup
  for (current_duty_cycle = 0;
       current_duty_cycle <= MAX_BRIGHTNESS;
       current_duty_cycle++) {
    analogWrite(PWM_PIN, current_duty_cycle);
    delay(5);  // 5 * 192 = 960 milliseconds
  }
}

void loop() {
  switch (state) {
    case STATE_ON:
      delay(DELAY_MSEC);
      state_msec_remaining -= DELAY_MSEC;
      if (state_msec_remaining <= 0) {
        state = STATE_DIMMING;
      }
      break;
    case STATE_DIMMING:
      analogWrite(PWM_PIN, current_duty_cycle);
      if (--current_duty_cycle <= 0) {
        state = STATE_OFF;
      }
      delay(DIM_DURATION_MSEC / MAX_BRIGHTNESS);  // 1562 msec
      break;
    case STATE_OFF:
      // Just to be sure
      current_duty_cycle = 0;
      analogWrite(PWM_PIN, current_duty_cycle);
      break;
  }

  // This is incomplete. It simply flickers the light
  // when the button is pressed. As an exercise to the reader,
  // introduce more states.
  int current_button_state = digitalRead(BUTTON_PIN);
  if (current_button_state != last_button_state) {
    if (current_button_state == HIGH) {
      for (int i = 0; i < 10; ++i) {
        analogWrite(PWM_PIN, 255);
        delay(20);
        analogWrite(PWM_PIN, 0);
        delay(20);
      }
      analogWrite(PWM_PIN, current_duty_cycle);
    } else {
      // Button is down. Do nothing and wait for it to be
      // released.
    }
    delay(50);  // debounce
    last_button_state = current_button_state;
  }
}

