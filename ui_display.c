#include "bus_reservation.h"

void displaySeatMap() {
    printf("\n    Seat Map (Row x Column)\n");
    printf("    Col1  Col2  Col3  Col4\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Row %2d: ", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (seats[i][j].booked)
                printf("[ X ] ");              
            else
                printf("[   ] ");
        }
        printf("\n");
    }
    printf("\nLegend: [ X ] = Booked, [   ] = Available\n");
}

void searchPassenger() {
    char query[50];
    int found = 0;

    printf("\nEnter passenger name or phone to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (seats[i][j].booked) {
                if (strcmp(seats[i][j].name, query) == 0 ||
                    strcmp(seats[i][j].phone, query) == 0) {
                    printf("\n✅ Found Passenger:\n");
                    printf("   Name  : %s\n", seats[i][j].name);
                    printf("   Phone : %s\n", seats[i][j].phone);
                    printf("   Price : $%.2f\n", seats[i][j].price);
                    printf("   Seat  : Row %d, Column %d\n", i+1, j+1);
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        printf("❌ No passenger found with that name or phone.\n");
    }
}