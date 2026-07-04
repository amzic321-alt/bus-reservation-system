/*
 * ============================================================
 *  STORAGE.C
 * ============================================================
 *  Saves bookings to a text file and loads them back in,
 *  so data persists between program runs.
 * ============================================================
 */
 
#include <stdio.h>
#include <string.h>
#include "bus_reservation.h"
 
/* ==========================================================
   SAVE BOOKINGS TO FILE
   ========================================================== */
void saveBookings(void) {
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
   LOAD BOOKINGS FROM FILE
   ========================================================== */
void loadBookings(void) {
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
 
