#include "mbed.h"

AnalogIn   analogIn(PB_1);
DigitalOut digitalOut(PB_0);

const float THRESHOLD = 0.9;
const int MAX_NO_BREATHING_COUNT = 10;
const int WAIT_TIME = 200000; // Microseconds
const int SAMPLE_INTERVAL = 500; // Milliseconds

void monitorBreathing() {
    uint32_t noBreathingCounter = 0;

    while (1) {
        float voltage = analogIn.read();

        if (voltage > THRESHOLD) {
            printf("No breathing\n");
            noBreathingCounter++;

            if (noBreathingCounter >= MAX_NO_BREATHING_COUNT) {
                digitalOut = 1;
                wait_us(WAIT_TIME);
            }
        } else {
            printf("Breathing\n");
            digitalOut = 0;
            noBreathingCounter = 0;
        }

        printf("Voltage: %f\n", voltage);
        printf("Percentage: %3.3f%%\n", voltage * 100.0f);

        thread_sleep_for(SAMPLE_INTERVAL);
    }
}

int main() {
    monitorBreathing();
    return 0;
}
