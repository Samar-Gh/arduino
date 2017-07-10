Assignment
Wack-A-Mole 1D

Task: 
Connect a disc (cardboard or similar) to a servo motor. Stick or draw a symbol onto on part of the disc. Another cardboard or a box around this installation only allows seeing one small segment.

The game: 
The servo motor is randomly moving the disc around. Whenever the player is able to see the symbol, he/she has to press a button. Think of a level and points system for this game.

Instructions:
1. Connect the Arduino board using the USB port to the PC.
2. Open the Arduino console from PC and open the project file/s.
3. If the "COM" port (Serial Port) is not already selected, please select the right serial port from the Tool Menu. 
4. Open the serial monitor (Ctrl+Shift+M) to monitor your outputs.
5. Compile and load your project files and at this point the kit should start.
If the kit doesn't work, please make sure that all the connections are correct from the circuit diagram given in the folder.

Game description:
The moving arm would show itself thru the 5 openings for a specified amount of time within which the player should press the button at the exact time to score a point. If the player cannot "Wack the mole" or press the button at the right time, he will lose a life, consindering he has a total of "3 lives". If the player scores 10 points, he would be advanced to the next level which implies the mole would show up for a shorter period of time at a faster rate. If the player looses all his lifes the game will end and the result will be displayed at the serial monitor.
