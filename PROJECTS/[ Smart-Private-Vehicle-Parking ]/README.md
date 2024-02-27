- ### To View the Explanation Video Press -> [here]()

![Capture](https://github.com/mgtera200/Master-Embedded-System/blob/main/PROJECTS/%5B%20Smart-Private-Vehicle-Parking%20%5D/Project_Simulation/Project.png)

# Description:

The Smart Parking project is a simulation of a parking system that incorporates two gates, an entry gate, and an exit gate.
The system allows an administrator to input authentic IDs initially. Subsequently, when users utilize the RFID scanner for entry or exit, the system processes the request and permits only authentic IDs.
Additionally, the system checks the availability of parking slots before granting entry.

# Features:

-  The administrator can input authentic IDs.
-  The system uses 2 LCDs to interface, one in the admin panel, and the other in the entry gate.
-  The entry gate’s RFID module accepts input if the parking is not full.
-  The exit gate’s RFID module accepts input if the parking is not empty.
-  PIR motion sensors to detect the car is not beneath the gate before closing it.
-  Checking availability of parking slots.

# Components used:

-  STM32F103C6T6.
-  2 x RFID scanners (Simulated using UART).
-  4x3 Keypad.
-  2 x 16x4 LCD.
-  2 x servo motor.
-  2 x PIR sensor.
-  Green LED.
-  Red LED.
