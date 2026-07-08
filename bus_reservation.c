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

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int isValidPhone(const char *phone) {
    int len = (int)strlen(phone);
    if (len < 7 || len > 14) {
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidPrice(float price) {
    return price > 0.0f && price <= 100.0f;
}

void bookSeat() {
    int row, col;
    char name[50], phone[15];
    float price;

    printf("\nEnter seat row (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1) {
        clearInputBuffer();
        printf("Invalid row input.\n");
        return;
    }
    printf("Enter seat column (1-%d): ", COLS);
    if (scanf("%d", &col) != 1) {
        clearInputBuffer();
        printf("Invalid column input.\n");
        return;
    }
    clearInputBuffer();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Seat position is out of range.\n");
        return;
    }

    row--; col--;

    if (seats[row][col].booked) {
        printf("This seat is already booked.\n");
        return;
    }

    printf("Enter passenger name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Failed to read name.\n");
        return;
    }
    name[strcspn(name, "\n")] = '\0';

    printf("Enter phone number: ");
    if (fgets(phone, sizeof(phone), stdin) == NULL) {
        printf("Failed to read phone number.\n");
        return;
    }
    phone[strcspn(phone, "\n")] = '\0';

    printf("Enter ticket price: ");
    if (scanf("%f", &price) != 1) {
        clearInputBuffer();
        printf("Invalid price input.\n");
        return;
    }
    clearInputBuffer();

    if (!isValidPhone(phone)) {
        printf("Invalid phone number. Use digits only (7-14 digits).\n");
        return;
    }

    if (!isValidPrice(price)) {
        printf("Invalid price. Price must be between 0 and 100.\n");
        return;
    }

    strcpy(seats[row][col].name, name);
    strcpy(seats[row][col].phone, phone);
    seats[row][col].price = price;
    seats[row][col].booked = 1;

    printf("Seat booked successfully.\n");
}

void cancelSeat() {
    int row, col;

    printf("\nEnter seat row to cancel (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1) {
        clearInputBuffer();
        printf("Invalid row input.\n");
        return;
    }
    printf("Enter seat column to cancel (1-%d): ", COLS);
    if (scanf("%d", &col) != 1) {
        clearInputBuffer();
        printf("Invalid column input.\n");
        return;
    }
    clearInputBuffer();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Seat position is out of range.\n");
        return;
    }

    row--; col--;

    if (!seats[row][col].booked) {
        printf("No booking found for that seat.\n");
        return;
    }

    seats[row][col].booked = 0;
    seats[row][col].name[0] = '\0';
    seats[row][col].phone[0] = '\0';
    seats[row][col].price = 0.0f;

    printf("Booking cancelled successfully.\n");
}

void printTicket() {
    int row, col;

    printf("\nEnter seat row (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1) {
        clearInputBuffer();
        printf("Invalid row input.\n");
        return;
    }
    printf("Enter seat column (1-%d): ", COLS);
    if (scanf("%d", &col) != 1) {
        clearInputBuffer();
        printf("Invalid column input.\n");
        return;
    }
    clearInputBuffer();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Seat position is out of range.\n");
        return;
    }

    row--; col--;

    if (!seats[row][col].booked) {
        printf("No booking exists for this seat.\n");
        return;
    }

    printf("\n===== TICKET =====\n");
    printf("Passenger : %s\n", seats[row][col].name);
    printf("Phone     : %s\n", seats[row][col].phone);
    printf("Seat      : Row %d, Column %d\n", row + 1, col + 1);
    printf("Price     : $%.2f\n", seats[row][col].price);
    printf("==================\n");
}

void saveBookings() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Unable to save bookings.\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (seats[i][j].booked) {
                fprintf(file, "%d %d %s %s %.2f\n",
                        i + 1, j + 1, seats[i][j].name, seats[i][j].phone, seats[i][j].price);
            }
        }
    }

    fclose(file);
}

void loadBookings() {
    FILE *file = fopen(FILENAME, "r");
    int row, col;
    char name[50], phone[15];
    float price;

    initializeSeats();

    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%d %d %49s %14s %f", &row, &col, name, phone, &price) == 5) {
        row--; col--;
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            strcpy(seats[row][col].name, name);
            strcpy(seats[row][col].phone, phone);
            seats[row][col].price = price;
            seats[row][col].booked = 1;
        }
    }

    fclose(file);
}
