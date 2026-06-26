
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
