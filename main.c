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

int main() {
    int choice;

    // Load previous bookings (Member 4's function)
    loadBookings();

    do {
        printf("\n====== BUS SEAT RESERVATION SYSTEM ======\n");
        printf("1. Display Seat Map\n");
        printf("2. Book a Seat\n");
        printf("3. Cancel a Booking\n");
        printf("4. Search Passenger\n");
        printf("5. Print Ticket\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();  // Member 4's helper

        switch (choice) {
            case 1: displaySeatMap(); break;   // Member 2
            case 2: bookSeat(); break;         // Member 3
            case 3: cancelSeat(); break;       // Member 3
            case 4: searchPassenger(); break;  // Member 2
            case 5: printTicket(); break;      // Member 4
            case 6: 
                saveBookings();                // Member 4
                printf("Data saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}