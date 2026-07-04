#ifndef BUS_RESERVATION_H
#define BUS_RESERVATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 10
#define COLS 4
#define FILENAME "bookings.dat"

// Passenger structure with price included
typedef struct {
    char name[50];
    char phone[15];
    float price;        // Ticket price
    int booked;         // 1 = booked, 0 = available
} Passenger;

// Global seat map (extern so all files share it)
extern Passenger seats[ROWS][COLS];

// ---- Function Prototypes ----

// Member 1 (Main)
void initializeSeats();

// Member 2 (Display & Search)
void displaySeatMap();
void searchPassenger();

// Member 3 (Booking)
void bookSeat();
void cancelSeat();

// Member 4 (File I/O, Ticket, Validators)
void printTicket();
void saveBookings();
void loadBookings();
int isValidPhone(const char *phone);
int isValidPrice(float price);
void clearInputBuffer();

#endif