# Laboratory Work A

## Variant 26: Temperature (2)

### Task Description:
A file contains information (line by line): date and average temperature for that day.
Read the file into a list in such a way that it remains sorted in ascending order of average
temperature (when average temperatures match, sorting should be done by date).
Display information about all days where the average temperature was below zero.
Enter a number from the keyboard and check if there is a day with such average temperature in the list.

### Implementation:
The program is implemented in C using a doubly linked list for storing
climate data with automatic sorting on insertion.

### Project Structure:
labA/
 temp.h
 weather_journal.h
 weather_journal.c
 data_parser.h
 data_parser.c
 main.c
 test_weather.c
 Makefile
 weather_data.txt
 README.md