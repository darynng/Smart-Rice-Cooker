# Smart-Rice-Cooker
The Smart Rice Cooker offers remote control via Blynk app, automatic scheduling, and accurate portion calibration. It recommends water levels, supports multiple rice types, and cooks up to 10 cups. LCD shows countdown and status LEDs indicate progress. App notifies users when the meal is ready.

3D Sketch: https://www.tinkercad.com/things/jNkx0Fj2TPE-surprising-kieran-jaiks/edit?returnTo=%2Fthings%2FjNkx0Fj2TPE-surprising-kieran-jaiks 

## Project Description
The Smart Rice Cooker is an IoT-based cooking solution designed for convenience, precision, and customization. Integrated with ingredient containers and connected to the Blynk mobile app, it enables users to remotely control and monitor the cooking process with ease.

Users simply input the serving amount and desired serving time into the app. The system automatically calibrates the rice portion, recommends the correct water level based on desired rice type, and activates cooking 20 minutes before the target serving time - with LCD display that shows a real-time cooking countdown and a “finished” message upon completion, in addition to LED signals:

  Red LED – Cooking in progress
  Green LED – Meal ready

Additionally, the Blynk app sends notifications when the rice is finished, ensuring users are always informed.

## Key Features
Capacity: Can cook up to 8 cups of rice

Digital Display: Shows countdown and completion message

Automatic Mode Switch: Smart scheduling to finish cooking at the desired time

Variable Cooking Options: Supports different types of rice

Customized Portion: Calibrates for accurate rice measurement

## Challenges and Proposed Solutions

1. Device Offline / Not Showing Online on Blynk

Challenges: The device often appears offline, and the serial monitor does not indicate the reason for the disconnection.

Solutions:

Use WifiScan.ino to verify that the device is properly connected to Wi-Fi.

Ensure the correct #define BLYNK_AUTH_TOKEN is used; tokens may change and need updating to reconnect to the Blynk app.

Check the LCD I2C address (0x27) if display updates are not visible.

Turn on the serial monitor in the IDE with the correct baud rate to monitor status messages.

2. Countdown Timer Showing Incorrect Completion

Challenges: The timer shows zero minutes, but the countdown is still running in milliseconds, causing the “finish” message not to appear.

Solutions: Convert milliseconds to minutes when displaying the countdown to ensure accurate end-time notifications.

3. Program Unresponsiveness Due to delay()

Challenges: Using delay() halts all other operations, causing unresponsive behavior during multitasking or real-time updates.

Solutions: Replace delay() with non-blocking timing using millis() to allow simultaneous execution of multiple operations.

4. Blynk Auth Token Management

Challenges: Devices may fail to reconnect if the Blynk auth token is outdated.

Solutions: Regularly check and update the auth token to ensure the device remains connected to the app.
