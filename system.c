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