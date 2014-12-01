//Author: Castañeda, Zymon Prado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//structure for the flightCS11

struct flightCS11 {
    char code;
    char fname[20];
    char lname[20];
    char bday[10];
    int seatrow;
    int seatcol;
};

//initialization of global variables
struct flightCS11 passengers[10];
//airplane contains the seat position mapping of every passenger
//passenger code started with 'A' for initialization purpose incase the application will start a blank record
char airplane[5][5], passenger_code = 'A';
//initialize the counter for passengers and the max passengers for the airplane
int passenger_count = 0, max_passenger = 10;

records_reload() {
    //this function's main purpose is to refresh the records when adding a passenger in order to quickly
    //view the airplane diagram
    FILE *fp;
    int x = 0;
    fp = fopen("records.txt", "r");
    if (!fp) {
        printf("System: Record file Error!");
    } else {
        while (!feof(fp)) {
            fscanf(fp, "%c", &passengers[x].code);
            fscanf(fp, "%s", passengers[x].fname);
            fscanf(fp, "%s", passengers[x].lname);
            fscanf(fp, "%s", passengers[x].bday);
            fscanf(fp, "%d", &passengers[x].seatrow);
            fscanf(fp, "%d\n", &passengers[x].seatcol);
            if (passengers[x].seatcol == 0) {
                airplane[0][passengers[x].seatrow] = toupper(passengers[x].code);
            }
            if (passengers[x].seatcol == 1) {
                airplane[1][passengers[x].seatrow] = toupper(passengers[x].code);
            }
            x++;
            passenger_count = x;
        }
    }
    fclose(fp);
}

void records_append(char code, char fname[20], char lname[20], char bday[10], int seatrow, int seatcol) {
    //the main purpose of this function is to append the record of the new passenger to be added
    //to the airplane by using the information of the user's input
    FILE *fp;
    fp = fopen("records.txt", "a");
    fprintf(fp, "%c\n", code);
    fprintf(fp, "%s ", fname);
    fprintf(fp, "%s\n", lname);
    fprintf(fp, "%s\n", bday);
    fprintf(fp, "%d ", seatrow);
    fprintf(fp, "%d\n", seatcol);
    fclose(fp);
}

void records_read() {
    //initialization of the local variables before reading the record file
    FILE *fp;
    int x = 0;
    //instructs the application to the target record file
    fp = fopen("records.txt", "r");
    //check if the file exists
    if (!fp) {
        printf("System: Record file error!");
    } else {
        //if the file exists the application will read the records based on
        //the format given by the professor, then add it to the passengers array
        while (!feof(fp)) {
            fscanf(fp, "%c", &passengers[x].code);
            fscanf(fp, "%s", passengers[x].fname);
            fscanf(fp, "%s", passengers[x].lname);
            fscanf(fp, "%s", passengers[x].bday);
            fscanf(fp, "%d", &passengers[x].seatrow);
            fscanf(fp, "%d\n", &passengers[x].seatcol);
            printf("Loading Passenger %c..\n", passengers[x].code);
            //the 'toupper' method from 'ctype.h' forces the character to uppercase
            //it is used to ensure the consistency of the data in the application
            if (passengers[x].seatcol == 0) {
                airplane[0][passengers[x].seatrow] = toupper(passengers[x].code);
            }
            if (passengers[x].seatcol == 1) {
                airplane[1][passengers[x].seatrow] = toupper(passengers[x].code);
            }
            x++;
            passenger_count = x;
        }
        printf("Loading of records complete!\n");
    }
    fclose(fp);
}

void displaySeats() {
    //this block of code checks if there is anyone seated in the airplane
    //if no one's sitting in a slot, the value would be a 'space' instead of a letter
    int x;
    for (x = 0; x < 5; x++) {
        // the '\0' means a null character, unlike int which can be compared to NULL
        //in this case it is '\0' for character
        if (airplane[0][x] == '\0') {
            airplane[0][x] = ' ';
        }
        if (airplane[1][x] == '\0') {
            airplane[1][x] = ' ';
        }
    }
    //draw the awesome airplane which passengers can take a seat
    printf("\n         .-.");
    printf("\n        /   \\");
    printf("\n       /0   1\\");
    printf("\n      .---+---.");
    printf("\n   0  | %c | %c |", airplane[0][0], airplane[1][0]);
    printf("\n     .|---+---|.");
    printf("\n   1/ | %c | %c | \\", airplane[0][1], airplane[1][1]);
    printf("\n   /  |---+---|  \\");
    printf("\n  /2  | %c | %c |   \\", airplane[0][2], airplane[1][2]);
    printf("\n /    |---+---|    \\");
    printf("\n ==3==| %c | %c |=====", airplane[0][3], airplane[1][3]);
    printf("\n      |---+---|");
    printf("\n   4  | %c | %c |", airplane[0][4], airplane[1][4]);
    printf("\n      =========");
}

void passenger_add() {
    //local variables for the passenger_add function
    char add_code;
    char add_fname[20];
    char add_lname[20];
    char add_bday[10];
    int add_seatrow;
    int add_seatcol;
    //check passenger count
    if (passenger_count == 0) {
        add_code = passenger_code;
    } else {
        add_code = passenger_code + passenger_count;
    }
    //checks if there is a seat available for another passenger of the airplane
    if (passenger_count < max_passenger) {
        printf("\nPassenger Code: %c", add_code);
        printf("\nFirst Name: ");
        scanf("%s", add_fname);
        printf("\nLast Name: ");
        scanf("%s", add_lname);
        printf("\nBirthday (mm-dd-yyyy): ");
        scanf("%s", add_bday);
        printf("\nChoose a seat:");
        displaySeats();
        printf("\nSeat Row: ");
        scanf("%d", &add_seatrow);
        printf("\nSeat Col: ");
        scanf("%d", &add_seatcol);
        //validation for seat information incase the user enters invalid data
        if (add_seatrow < 5 && add_seatcol < 2) {
            if (airplane[add_seatcol][add_seatrow] == ' ') {
                records_append(add_code, add_fname, add_lname, add_bday, add_seatrow, add_seatcol);
                records_reload();
                displaySeats();
                printf("\nAdd Successful!");
            } else {
                printf("\nNOTICE: Sorry, seat already taken.");
            }
        } else {
            printf("\nSystem: Invalid seat information!");
        }
    } else {
        printf("\nThe Airplane is full!");
    }
    (void) getch();
}

void passenger_view() {
    //local variables for the function passenger_view
    char passenger_code;
    int x, result = 0;
    //as user for the passenger code
    printf("\nPlease enter the passenger code: ");
    scanf(" %c", &passenger_code);
    //checks the passengers array for any matches in the record
    for (x = 0; x < 10; x++) {
        //if a record matches, display the information of the passenger
        if (passengers[x].code == toupper(passenger_code)) {
            //flag that there is a result for the match
            result = 1;
            printf("\nFirst name: %s", passengers[x].fname);
            printf("\nLast name: %s", passengers[x].lname);
            printf("\nBirthday: %s", passengers[x].bday);
            printf("\nSeat assignment: Row%d Col%d", passengers[x].seatrow, passengers[x].seatcol);
        }
    }
    //notify the user that there is no record for the passenger code input
    if (result < 1) {
        printf("\nNo Record found!");
    }
    printf("\n\nPress any key to return..");
    (void) getch();
}

void menu() {
    //main menu function with the switch to choose what to do with the application's options
    int menu_choice;
    printf("\nWelcome aboard flight CS11! What would you like to do?\n");
    printf("\t1. Add Passenger\n\t2. Display Seats\n\t3. Display Passenger Info\n\t4. Exit\n");
    printf("Choice: ");
    scanf("%d", &menu_choice);
    switch (menu_choice) {
        case 1:
            passenger_add();
            break;
        case 2:
            displaySeats();
            (void) getch();
            break;
        case 3:
            passenger_view();
            break;
        case 4:
            printf("\nSYSTEM: Thank you! ;)\n");
            (void) getch();
            exit(1);
            break;
        default:
            printf("\nWARNING: Incorrect input! Try again.");
            (void) getch();
            break;
    }
}
//main method for the application

int main() {
    //infinite loop for the menu so that the user can choose different options
    //as long as the user did not choose the exit option designated by the system
    for (;;) {
        FILE *fp;
        int x = 0;
        //instructs the application to the target record file
        fp = fopen("records.txt", "r");
        if (fp) {
            //calls the records_read funtion if there's a passenger
            records_read();
            fclose(fp);
        } else {
            fclose(fp);
        }
        menu();
        system("cls");
    }
}
