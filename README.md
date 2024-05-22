# MATLAB GUI Based Calculator Using Cypress Development Board

## Overview

This project involves a simple calculator application where the GUI is created in MATLAB, and arithmetic operations are performed by a Cypress development board. When a user presses a button on the MATLAB GUI, the input is transmitted to the Cypress board via UART. The board performs the calculation and displays the result on an LCD.

## Features

- Basic arithmetic operations: addition, subtraction, multiplication, and division.
- User-friendly MATLAB GUI.
- UART communication between MATLAB and Cypress board.
- Result display on the Cypress board's LCD.

## Requirements

- MATLAB R2018a or later
- Cypress PSoC Creator 4.2 or later
- Cypress development board (e.g., CY8CKIT-059)
- USB cable for connection
- LCD module compatible with the Cypress board

## Setup Instructions

### Cypress Development Board

1. **Install PSoC Creator**: Download and install PSoC Creator from the Cypress website.
2. **Create a New Project**:
   - Open PSoC Creator and create a new project.
   - Configure the project to enable UART communication and interface with the LCD.
3. **UART Configuration**:
   - In the TopDesign.cysch file, drag and drop the UART and LCD components.
   - Configure the UART component (e.g., baud rate: 9600).
   - Write firmware to read inputs via UART, perform arithmetic operations, and display results on the LCD.
4. **LCD Configuration**:
   - Configure the LCD component to ensure it can display the results correctly.
5. **Build and Program**:
   - Build the project and program the Cypress development board.

### MATLAB GUI

1. **Install MATLAB**: Ensure you have MATLAB R2018a or later installed.
2. **Create GUI**:
   - Design the GUI using MATLAB's App Designer or GUIDE (Graphical User Interface Development Environment).
   - Implement buttons for digits and operations, and a display area for the input.
3. **Serial Communication**:
   - Set up serial communication in MATLAB to transmit data to the Cypress board.
   - Use MATLAB’s `serialport` functions to open, write to, and close the serial port.

## File Structure

- `calculator_GUI.m` - MATLAB script for creating the GUI and handling UART communication.
- `main.c` - Cypress firmware file for performing arithmetic operations and displaying results on the LCD.

## Running the Application

1. **Connect the Board**: Connect the Cypress development board to your computer via USB.
2. **Launch MATLAB GUI**:
   - Run `calculator_GUI.m` to launch the GUI.
3. **Perform Calculations**:
   - Use the GUI buttons to input numbers and select operations.
   - The input is transmitted to the Cypress board, which performs the calculation and displays the result on the LCD.

## Troubleshooting

- **Connection Issues**: Ensure the Cypress board is properly connected and recognized by your computer.
- **Serial Communication**: Verify the UART settings (baud rate, COM port) match between MATLAB and the Cypress firmware.
- **MATLAB Errors**: Check for syntax errors or missing functions in the MATLAB code.
- **LCD Display**: Ensure the LCD is correctly connected and configured on the Cypress board.

## Additional Resources

- [MATLAB Documentation](https://www.mathworks.com/help/matlab/)
- [Cypress PSoC Creator Documentation](https://www.cypress.com/documentation/software-and-drivers/psoc-creator)

## Contact

For any questions or issues, please contact Sourabh Kumar Singh at [706sourabh@gmail.com].
