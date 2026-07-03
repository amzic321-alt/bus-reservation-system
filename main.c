#include "bus_reservation.h"

// Define the global seats array (allocates memory)
Passenger seats[ROWS][COLS];

void initializeSeats() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            seats[i][j].booked = 0;
            seats[i][j].name[0] = '\0';
            seats[i][j].phone[0] = '\0';
        }
    }
}

int main() {
    int choice;
    loadBookings(); // Member 4's job

    do {
        printf("\n====== BUS SEAT RESERVATION SYSTEM ======\n");
        printf("1. Display Seat Map (Member 2)\n");
        printf("2. Book a Seat (Member 3)\n");
        printf("3. Cancel a Booking (Member 3)\n");
        printf("4. Search Passenger (Member 2)\n");
        printf("5. Print Ticket (Member 4)\n");
        printf("6. Save & Exit (Member 4)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Member 4's job

        switch (choice) {
            case 1: displaySeatMap(); break;  // Calls Member 2
            case 2: bookSeat(); break;        // Calls Member 3
            case 3: cancelSeat(); break;      // Calls Member 3
            case 4: searchPassenger(); break; // Calls Member 2
            case 5: printTicket(); break;     // Calls Member 4
            case 6: saveBookings();           // Calls Member 4
                    printf("Data saved. Exiting...\n");
                    break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}