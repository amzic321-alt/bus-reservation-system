/*
 * ============================================================
 *  BUS TICKET RESERVATION SYSTEM
 *  Group 7 - Programming Fundamentals Final Project
 * ============================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ── Constants ─────────────────────────────────────── */
#define ROWS         5
#define COLS         4
#define MAX_PASS     (ROWS * COLS)
#define FILE_NAME    "bookings.txt"
#define TICKET_PRICE 15.00

/* ── Struct ─────────────────────────────────────────── */
typedef struct {
    char name[50];
    char phone[15];
    int  row;
    int  col;
    int  active;   /* 1 = booked, 0 = empty slot */
} Passenger;

/* ── Global Data ────────────────────────────────────── */
int       seats[ROWS][COLS];          /* 0=available, 1=booked */
Passenger passengers[MAX_PASS];
int       totalPassengers = 0;

/* ── Function Prototypes ────────────────────────────── */
void displaySeatMap();
void bookSeat();
void cancelSeat();
void searchPassenger();
void printTicket();
void saveBookings();
void loadBookings();
void printLine(char c, int len);
void clearInputBuffer();

/* ==========================================================
   MAIN
   ========================================================== */
int main() {
    int choice;

    loadBookings();

    do {
        printf("\n");
        printLine('=', 40);
        printf("   BUS TICKET RESERVATION SYSTEM\n");
        printLine('=', 40);
        printf("  [1] View Seat Map\n");
        printf("  [2] Book a Seat\n");
        printf("  [3] Cancel a Booking\n");
        printf("  [4] Search Passenger\n");
        printf("  [5] Print Ticket\n");
        printf("  [0] Exit\n");
        printLine('-', 40);
        printf("  Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("  [!] Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: displaySeatMap();   break;
            case 2: bookSeat();         break;
            case 3: cancelSeat();       break;
            case 4: searchPassenger();  break;
            case 5: printTicket();      break;
            case 0:
                saveBookings();
                printf("\n  Bookings saved. Goodbye!\n\n");
                break;
            default:
                printf("  [!] Invalid option. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

/* ==========================================================
   1. DISPLAY SEAT MAP
   ========================================================== */
void displaySeatMap() {
    printf("\n");
    printLine('-', 40);
    printf("         BUS SEAT MAP\n");
    printf("    [ O ] = Available   [ X ] = Booked\n");
    printLine('-', 40);

    printf("     Seat: ");
    for (int c = 0; c < COLS; c++) {
        printf("  %d ", c + 1);
    }
    printf("\n");

    for (int r = 0; r < ROWS; r++) {
        printf("  Row %d:  ", r + 1);
        for (int c = 0; c < COLS; c++) {
            if (seats[r][c] == 0)
                printf("[ O]");
            else
                printf("[ X]");
        }
        printf("\n");
    }
    printLine('-', 40);
    printf("  Total Seats: %d  |  Booked: %d  |  Available: %d\n",
        ROWS * COLS, totalPassengers, ROWS * COLS - totalPassengers);
    printLine('-', 40);
}

/* ==========================================================
   2. BOOK A SEAT
   ========================================================== */
void bookSeat() {
    int row, col;
    char name[50], phone[15];

    displaySeatMap();

    printf("\n  Enter row number (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1 || row < 1 || row > ROWS) {
        printf("  [!] Invalid row number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("  Enter column number (1-%d): ", COLS);
    if (scanf("%d", &col) != 1 || col < 1 || col > COLS) {
        printf("  [!] Invalid column number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Convert to 0-based index */
    row--; col--;

    if (seats[row][col] == 1) {
        printf("  [!] Seat Row %d Col %d is already booked!\n", row+1, col+1);
        return;
    }

    printf("  Enter passenger name  : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) {
        printf("  [!] Name cannot be empty.\n");
        return;
    }

    printf("  Enter phone number    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';
    if (strlen(phone) == 0) {
        printf("  [!] Phone cannot be empty.\n");
        return;
    }

    /* Save booking */
    seats[row][col] = 1;
    passengers[totalPassengers].row    = row;
    passengers[totalPassengers].col    = col;
    passengers[totalPassengers].active = 1;
    strncpy(passengers[totalPassengers].name,  name,  49);
    strncpy(passengers[totalPassengers].phone, phone, 14);
    totalPassengers++;

    printf("\n");
    printLine('=', 40);
    printf("  BOOKING CONFIRMED!\n");
    printf("  Seat   : Row %d, Column %d\n", row+1, col+1);
    printf("  Name   : %s\n", name);
    printf("  Phone  : %s\n", phone);
    printf("  Price  : RM %.2f\n", TICKET_PRICE);
    printLine('=', 40);
}

/* ==========================================================
   3. CANCEL A SEAT
   ========================================================== */
void cancelSeat() {
    int row, col;

    displaySeatMap();

    printf("\n  Enter row of seat to cancel (1-%d): ", ROWS);
    if (scanf("%d", &row) != 1 || row < 1 || row > ROWS) {
        printf("  [!] Invalid row.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("  Enter column of seat to cancel (1-%d): ", COLS);
    if (scanf("%d", &col) != 1 || col < 1 || col > COLS) {
        printf("  [!] Invalid column.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    row--; col--;

    if (seats[row][col] == 0) {
        printf("  [!] Seat Row %d Col %d is not booked.\n", row+1, col+1);
        return;
    }

    /* Find and remove passenger */
    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].row == row && passengers[i].col == col && passengers[i].active) {
            printf("\n  Cancelling booking for: %s\n", passengers[i].name);
            passengers[i].active = 0;
            seats[row][col] = 0;
            totalPassengers--;
            /* Shift array */
            for (int j = i; j < totalPassengers; j++)
                passengers[j] = passengers[j+1];
            printf("  [OK] Booking cancelled successfully.\n");
            return;
        }
    }
    printf("  [!] Error: passenger record not found.\n");
}

/* ==========================================================
   4. SEARCH PASSENGER
   ========================================================== */
void searchPassenger() {
    char keyword[50];
    int  found = 0;

    printf("\n  Enter passenger name to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("\n");
    printLine('-', 50);
    printf("  %-20s %-15s  %s\n", "Name", "Phone", "Seat");
    printLine('-', 50);

    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].active &&
            strstr(passengers[i].name, keyword) != NULL) {
            printf("  %-20s %-15s  Row %d, Col %d\n",
                passengers[i].name,
                passengers[i].phone,
                passengers[i].row + 1,
                passengers[i].col + 1);
            found++;
        }
    }

    if (!found)
        printf("  [!] No passenger found with name: %s\n", keyword);

    printLine('-', 50);
    printf("  Found: %d result(s)\n", found);
}

/* ==========================================================
   5. PRINT TICKET
   ========================================================== */
void printTicket() {
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

/* ==========================================================
   6. SAVE BOOKINGS TO FILE
   ========================================================== */
void saveBookings() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("  [!] Error: Could not save bookings.\n");
        return;
    }
    fprintf(fp, "%d\n", totalPassengers);
    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].active) {
            fprintf(fp, "%s\n%s\n%d\n%d\n",
                passengers[i].name,
                passengers[i].phone,
                passengers[i].row,
                passengers[i].col);
        }
    }
    fclose(fp);
    printf("  [OK] Bookings saved to %s\n", FILE_NAME);
}

/* ==========================================================
   7. LOAD BOOKINGS FROM FILE
   ========================================================== */
void loadBookings() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("  [i] No existing bookings found. Starting fresh.\n");
        return;
    }
    int count;
    fscanf(fp, "%d\n", &count);
    for (int i = 0; i < count; i++) {
        fgets(passengers[i].name,  50, fp);
        passengers[i].name[strcspn(passengers[i].name, "\n")] = '\0';
        fgets(passengers[i].phone, 15, fp);
        passengers[i].phone[strcspn(passengers[i].phone, "\n")] = '\0';
        fscanf(fp, "%d\n%d\n", &passengers[i].row, &passengers[i].col);
        passengers[i].active = 1;
        seats[passengers[i].row][passengers[i].col] = 1;
    }
    totalPassengers = count;
    fclose(fp);
    if (count > 0)
        printf("  [OK] Loaded %d existing booking(s).\n", count);
}

/* ==========================================================
   HELPER FUNCTIONS
   ========================================================== */
void printLine(char c, int len) {
    for (int i = 0; i < len; i++) printf("%c", c);
    printf("\n");
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
