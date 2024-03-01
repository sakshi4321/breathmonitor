#include "mbed.h"

// Define analog input and digital output pins
AnalogIn   analogIn(PB_1);
DigitalOut digitalOut(PB_0);

// Define constants
const float THRESHOLD = 0.9;
const int MAX_NO_BREATHING_COUNT = 10;
const int WAIT_TIME = 200000; // Microseconds
const int SAMPLE_INTERVAL = 500; // Milliseconds

// Function to monitor breathing and control digital output accordingly
void monitorBreathing() {
    uint32_t noBreathingCounter = 0;

    while (1) {
        float voltage = analogIn.read();

        if (voltage > THRESHOLD) {
            printf("No breathing\n");
            noBreathingCounter++;

            // If no breathing is detected for a consecutive number of times, activate digital output
            if (noBreathingCounter >= MAX_NO_BREATHING_COUNT) {
                digitalOut = 1;
                wait_us(WAIT_TIME);
            }
        } else {
            printf("Breathing\n");
            digitalOut = 0;
            noBreathingCounter = 0; // Reset the counter if breathing is detected
        }

        // Print voltage and percentage
        printf("Voltage: %f\n", voltage);
        printf("Percentage: %3.3f%%\n", voltage * 100.0f);

        thread_sleep_for(SAMPLE_INTERVAL);
    }
}

int main() {
    // Test Cases
    // 1. Simulate no breathing for prolonged duration
    //    Result: Digital output should be activated after exceeding the threshold for a specified duration
    // 2. Simulate continuous breathing
    //    Result: Digital output should remain deactivated
    // 3. Simulate noisy signal around the threshold
    //    Result: Noisy signal should not trigger false positives
    // 4. Simulate sudden change in breathing pattern
    //    Result: Digital output should respond accordingly

    monitorBreathing(); // Start monitoring breathing
    return 0;
}
