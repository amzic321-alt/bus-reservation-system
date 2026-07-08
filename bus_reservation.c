#include "bus_reservation.h"

Passenger seats[ROWS][COLS];

void initializeSeats() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            seats[i][j].booked = 0;
            seats[i][j].name[0] = '\0';
            seats[i][j].phone[0] = '\0';
            seats[i][j].price = 0.0f;
        }
    }
}
