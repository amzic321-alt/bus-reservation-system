#include "bus_reservation.h"

// ---- Validation Helpers ----

void clearInputBuffer() {
    while (getchar() != '\n');
}

int isValidPhone(const char *phone) {
    int len = strlen(phone);
    if (len < 10) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

int isValidPrice(float price) {
    return (price > 0.0);   // Price must be positive
}

// ---- Print Ticket (shows price) ----

void printTicket() {
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

    printf("\n==========================================\n");
    printf("              🚌 BUS TICKET               \n");
    printf("==========================================\n");
    printf("  Passenger : %s\n", seats[r][c].name);
    printf("  Phone     : %s\n", seats[r][c].phone);
    printf("  Seat      : Row %d, Column %d\n", row, col);
    printf("  Price     : $%.2f\n", seats[r][c].price);
    printf("==========================================\n");
    printf("         Thank you for travelling!        \n");
    printf("==========================================\n");
}

// ---- File Handling ----

void saveBookings() {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("❌ Error opening file for saving.\n");
        return;
    }
    fwrite(seats, sizeof(Passenger), ROWS * COLS, fp);
    fclose(fp);
    printf("✅ Bookings saved to %s\n", FILENAME);
}

void loadBookings() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        // No existing file – initialise fresh
        initializeSeats();
        return;
    }
    size_t read = fread(seats, sizeof(Passenger), ROWS * COLS, fp);
    fclose(fp);

    if (read != ROWS * COLS) {
        // File is corrupted or incompatible – reinitialise
        initializeSeats();
        printf("⚠️  Warning: Data file corrupted. Initialised fresh.\n");
    }
}