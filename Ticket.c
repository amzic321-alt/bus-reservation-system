/*
 * ============================================================
 *  TICKET.C
 * ============================================================
 *  Prints a formatted ticket for a booked seat.
 * ============================================================
 */
 
#include <stdio.h>
#include "bus_reservation.h"
 
void printTicket(void) {
    int row, col;
 
    printf("\n  Enter row of ticket to print (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1 || row < 1 || row > ROWS) {
        printf("  [!] Invalid row.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
 
    printf("  Enter column (1-%d): ", COLS);
    if (scanf("%d", &col) != 1 || col < 1 || col > COLS) {
        printf("  [!] Invalid column.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
 
    row--; col--;
 
    if (seats[row][col] == 0) {
        printf("  [!] That seat is not booked.\n");
        return;
    }
 
    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].row == row && passengers[i].col == col && passengers[i].active) {
            printf("\n");
            printLine('*', 40);
            printf("        BUS TICKET\n");
            printLine('*', 40);
            printf("  Passenger : %s\n",     passengers[i].name);
            printf("  Phone     : %s\n",     passengers[i].phone);
            printf("  Seat      : Row %d, Column %d\n", row+1, col+1);
            printf("  Price     : RM %.2f\n", TICKET_PRICE);
            printf("  Status    : CONFIRMED\n");
            printLine('*', 40);
            printf("    Thank you for riding with us!\n");
            printLine('*', 40);
            return;
        }
    }
    printf("  [!] Passenger record not found.\n");
}
