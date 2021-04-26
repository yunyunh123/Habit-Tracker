# Habit-Tracker

# Compiling and Executing

The habit tracker application is compiled and executed by typing the following two lines in the terminal:

make main
main

The makefile contains all classes and libraries needed for compiling.

# Menu

Brief directions are displayed in each window's title bar.
Once a menu window pops up, press the up or down keyboard to move through the different options. Press enter to select the option.

# New Habit

If the user selects "New Habit", the user will see four boxes that needs input. "Habit Name" and "Units" should be strings. "Amount" should be a positive float. "Frequency" should be a positive integer less than or equal to five. The "Amount" is the total amount that the user wants to exercise his or her habit per day. The "Units" indicate how the "Amount" should be quantified. "Frequency" denotes the number of times per day that the user wants to record his or her habit.

The first textbox is selected by default, but the user can choose to select any of the four textboxes by pressing the up or down key. Close the window by clicking the X button on the window's top-right corner. All inputted values will be stored in "currenthabs.txt", and the user will be able to track the new habit.

If one or more textbox is missing a user input or has an invalid value (e.g., a string for "Amount"), then closing the window will pop up a new window with the same requested values. Only until the user inputs all correct values will he or she be able to close the window successfully.

Once the user closes the window successfully, he or she can select another option in the menu window.

# Track Habit(s)

If the user selects "Track Habit(s)", the user will see all current habits. If no habits are created yet, this window will be blank.

Press the up or down key to move through the different habits. Press enter to select the habit.

Once a habit is selected, a new window will pop up with one to five textboxes, depending on the chosen "Frequency". The first textbox is selected by default. Press enter to select the next textbox. Once the last textbox is selected, the user may press the escape key to select the first textbox again. 

Only until all textboxes are filled and its units are valid (i.e., floats) will the user be able to successfully close the window. Otherwise, the same window will pop up again to request user input. 

Close both window to return to the menu. The user input will be used to calculate the daily averages and update the "avgdata.txt".

# View Habit Progress

If the user selects "View Habit Progress", the daily averages will be displayed on the window for each habit. Once done viewing habit progress, the user may close the window and return to the Menu.

# Closing the application

Once all windows are closed, the application is done executing. The user can reopen the application, with previous data saved in "currenthabs.txt" and "avgdata.txt".
