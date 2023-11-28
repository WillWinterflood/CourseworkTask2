#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char FileName[1000];
int buffer_size = 1000;
int Records_Counter = 0;
FILE *file;
int MinSteps = 9999999;
char minTime[6];
char minDate[11];
int MaxSteps = -1;
//DECLARING MOST OF MY VARIABLES HERE MEANING THEY ARE GLOBAL AND CAN BE USED IN THE SWITCH FUNCTION




// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {

    char line[buffer_size];
    char filename[buffer_size];
    char choice;

    // get filename from the user
    

    // these lines read in a line from the stdin (where the user types)
    // and then takes the actual string out of it
    // this removes any spaces or newlines.   

    

    while (1)
    {
        printf("Menu Options:\n");
        // This is the menu of options that the user can choose from
        
        printf("A: Specify the filename to be imported - you need to check that the file opened correctly.\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Exit\n");
        printf("Enter Choice: ");
        scanf(" %c", &choice);
        // defining the choice as a character 
        getchar();
        // getchar(), this read the single character and reads it as an unsigned char

        // switch statement to control the menu.
        switch (choice)
        {
        // this allows for either capital or lower case
        case 'A':
        case 'a':
            printf("Input Filename: ");
            scanf("%s", FileName);
            file = fopen(FileName, "r");
            if (file == NULL) {
                perror("Error: could not find or open the file. \n");
                // Error message.
                return 1;

            }
            printf("File successfully loaded.\n");
            fclose(file);
            break;

        case 'B':
        case 'b':
            Records_Counter = 0;
            // same as in task 1 
            file = fopen(FileName, "r");
            if (file == NULL) {
                perror("Error: Could not open the file. \n");
                return 1;
            
            }
            //Already defined records counter in the global variables bit.
            while (fgets(line, buffer_size, file) != NULL) {

                Records_Counter = Records_Counter + 1;
                //Counts how many lines there are in a file and increments 
                // the record counter by one for every line 
            }
            printf("Total records: %d\n", Records_Counter);
            //Printing the records counter
            fclose(file);
            break; 

        case 'C':
        case 'c':
            file = fopen(FileName,"r");
            if (file == NULL) {

                perror("Error: Could not open the file");
                return 1;
            }
            
            FITNESS_DATA listofffitnessdata[500];
            FITNESS_DATA loweststeps;
            int count = 0;

            while (fgets(line,buffer_size,file) != NULL) {
                int CurrentSteps[1000];

                char date[11];
                char time[6];
                char steps[100];
                //Declaring them all as characters as this means that you can append them to a list
                tokeniseRecord(line,",", date, time, steps);
                
                CurrentSteps[count] = atoi(steps);
                // changing steps into Currentsteps[count] which changes a chraracter into an integer 

               
                
                if (CurrentSteps[count] < MinSteps) {
                    MinSteps = CurrentSteps[count];
                    strcpy(minDate, date);
                    strcpy(minTime, time);
                    // This if statement is saying that if the steps is under the MinSteps(which is declared in the global section as 999999)
                    //  then it redefines MinSteps and copies the date and the time in that line to be then printed.
                    
                     
                }
            }
            printf("Fewest steps: %s %s\n", minDate, minTime);
            
            break;

        case 'D':
        case 'd':
            file = fopen(FileName,"r");
            if (file == NULL) {

                perror("Error: Could not open the file");
                return 1;
            }
            
            count = count*0;
            //Reseting the count to 0 after the previous case 

            while (fgets(line,buffer_size,file) != NULL) {
                int CurrentSteps[1000];
                char date[11];
                char time[6];
                char steps[100];
                //Declaring them all as characters as this means that you can append them to a list
                tokeniseRecord(line,",", date, time, steps);
                
                CurrentSteps[count] = atoi(steps);

               
                
                if (CurrentSteps[count] > MaxSteps) {
                    MaxSteps = CurrentSteps[count];
                    strcpy(minDate, date);
                    strcpy(minTime, time);
                    
                     
                }
            }
            printf("Largest steps: %s %s\n", minDate, minTime);
            //This is essentially the same code as case C however the MaxSteps is set to -1 in the global variables area and currentsteps[count]
            // only changes when it is greater than MaxSteps
            break;

        case 'E':
        case 'e':
            file = fopen(FileName,"r");
            if (file == NULL) {

                perror("Error: Could not open the file");
                return 1;
            }
            
            char date[11];
            char time[6];
            char steps_char[1000];
            int steps[1000];
            int meansteps;
            int sumsteps;
            int linecount = 0;

            while (fgets(line,buffer_size,file) != NULL) {
                linecount = linecount + 1;
                tokeniseRecord(line, ",", date, time, steps_char);
                steps[linecount] = atoi(steps_char);
                sumsteps = steps[linecount] + sumsteps;
                //This line sums the values in the array
                //every line the code goes through in the file, linecount increments by 1 
            }

            meansteps = sumsteps / linecount;
            printf("Mean step count: %d\n", meansteps);
            sumsteps = 0;
            break;

        case 'F':
        case 'f':
            file = fopen(FileName,"r");
            if (file == NULL) {

                perror("Error: Could not open the file");
                return 1;
            }
            int fivecount = 0;
            int steps1;
            int secondcounter = 0;
            char startdate[11];
            char enddate[11];
            char currentstartdate[11];
            char currentenddate[11];
            char starttime[6];
            char endtime[6];
            char currentstarttime[6];
            char currentendtime[6];
            //declaring all my variables im going to use in this case
            FITNESS_DATA current = {};
            //This holds each individual lines date and time value as the while loop is going through it.
            while (fgets(line,buffer_size,file) != NULL) {
                tokeniseRecord(line,",",current.date,current.time,steps_char);
                //splits the line up when theres a comma
                steps1 = atoi(steps_char);
                //steps_char is defined in the previous case, therefore as it is a character we need to redeclare it in this case as steps1 which is an integer

                if (steps1 > 500) {
                    if (fivecount > 0) {
                    strcpy(currentenddate, current.date);
                    strcpy(currentendtime, current.time);
                    }   
                    else {
                    strcpy(currentstartdate, current.date);
                    strcpy(currentstarttime, current.time);
                    }
                    fivecount = fivecount + 1;
                } 
                else {
                    if (fivecount > 0) {
                    //if the counter has already started then there is no need to set current.date to currentstartdate
                        if (fivecount > secondcounter) {
                            secondcounter = fivecount;
                            strcpy(startdate, currentstartdate);
                            strcpy(starttime, currentstarttime);
                            strcpy(enddate, currentenddate);
                            strcpy(endtime, currentendtime);
                        }
                        fivecount = 0; //This resets the count for the next period which over 500 steps is achieved.
        }
    }
}

            //This is checking whether the last counter of a period is greater than the second last counter of an period
            if (fivecount > secondcounter) {
                strcpy(startdate, currentstartdate);
                strcpy(starttime, currentstarttime);
                strcpy(enddate, currentenddate);
                strcpy(endtime, currentendtime);
            }

            printf("Longest period start date: %s %s\n", startdate, starttime);
            printf("Longest period end date: %s %s\n", enddate, endtime);
            break;
        case 'Q':
        case 'q':
        return 0;
        //Q is quit and when this is typed the code ends 
            break;

        // If they type another character which is not in the menu it will come back with this error message.
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
}
  