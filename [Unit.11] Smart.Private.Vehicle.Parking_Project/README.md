- ### ** To View the Explanation Video Press [here](https://drive.google.com/file/d/1e63wff3yp4qt_NsAAtDSoXb--Aou8DEj/view?usp=sharing)**

![Capture]()

# Description:

The Smart Parking project is a simulation of a parking system that incorporates two gates, an entry gate, and an exit gate.
The system allows an administrator to input authentic IDs initially. Subsequently, when users utilize the RFID scanner for entry or exit, the system processes the request and permits only authentic IDs.
Additionally, the system checks the availability of parking slots before granting entry.

# Features:

1. The administrator can input authentic IDs.
2. The system uses 2 LCDs to interface, one in the admin panel, and the other in the entry gate.
3. The entry gate’s RFID module accepts input if the parking is not full.
4. The exit gate’s RFID module accepts input if the parking is not empty.
5. PIR motion sensors to detect the car is not beneath the gate before closing it.
6. Checking availability of parking slots.

# Components used:

1. STM32F103C6T6.
2. 2 x RFID scanners (Simulated using UART).
3. 4x3 Keypad.
4. 2 x 16x4 LCD.
5. 2 x servo motor.
6. 2 x PIR sensor.
7. Green LED.
8. Red LED.
