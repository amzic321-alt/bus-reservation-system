#include "bus_reservation.h"

void bookSeat() {
    int row, col;
    char name[50], phone[15];
    float price;

    displaySeatMap();  
    printf("\nEnter seat row (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter seat column (1-%d): ", COLS);
    scanf("%d", &col);
    clearInputBuffer();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("❌ Invalid seat number!\n");
        return;
    }

    int r = row - 1, c = col - 1;

    if (seats[r][c].booked) {
        printf("❌ Seat already booked!\n");
        return;
    }

    printf("Enter passenger name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter passenger phone (digits only, min 10): ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    if (!isValidPhone(phone)) {   
        printf("❌ Invalid phone number! Booking cancelled.\n");
        return;
    }

    printf("Enter ticket price (USD, e.g., 25.50): ");
    scanf("%f", &price);
    clearInputBuffer();

    if (!isValidPrice(price)) {   // Member 4's validator
        printf("❌ Invalid price! Must be positive. Booking cancelled.\n");
        return;
    }

    strcpy(seats[r][c].name, name);
    strcpy(seats[r][c].phone, phone);
    seats[r][c].price = price;
    seats[r][c].booked = 1;

    printf("✅ Seat booked successfully! Total price: $%.2f\n", price);
}

void cancelSeat() {
    int row, col;

    printf("\nEnter seat row (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter seat column (1-%d): ", COLS);
    scanf("%d", &col);
    clearInputBuffer();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("❌ Invalid seat number!\n");
        return;
    }

    int r = row - 1, c = col - 1;

    if (!seats[r][c].booked) {
        printf("❌ Seat is not booked.\n");
        return;
    }

    // Clear the seat
    seats[r][c].booked = 0;
    seats[r][c].name[0] = '\0';
    seats[r][c].phone[0] = '\0';
    seats[r][c].price = 0.0;

    printf("✅ Booking cancelled for seat (%d, %d).\n", row, col);
}