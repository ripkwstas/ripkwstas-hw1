#include <stdio.h>
#include <stdlib.h>

int printmonth();
void firstday();
void printyear();
int get_dow();

int maxdaysofmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int main() {
    int year, month;

    printf("Welcome to the calendar.\nYear: ");
    if (scanf("%d", &year) != 1 || year < 0) {
        printf("Wrong input, try again (only non-negative years allowed)\n");
        exit(1);
    }

    printf("Month (0 to print entire year): ");
    if (scanf("%d", &month) != 1 || month < 0 || month > 12) {
        printf("Wrong input, try again by putting a number between 0-12\n");
        exit(1);
    }

    if (month != 0) {
        printmonth(month, year);
    }else{
       printyear(year);
    }
    
    return 0;
}

// Συνάρτηση για να εκτυπώσουμε τον μήνα
int printmonth(int month, int year) { 
    int mera, day, res;
    int meres_mhna[12][31];

    for (int i = 0; i < 12; i++) { // Επανάληψη για τους μήνες (0 έως 11)
        for (int j = 0; j < maxdaysofmonth[i]; j++) { // Επανάληψη για τις ημέρες του μήνα
            meres_mhna[i][j] = j; // Ανάθεση του δείκτη του μήνα σε κάθε ημέρα
        }
    }

    
    printf("         %s           \n", months[month - 1]);
    printf("Su Mo Tu We Th Fr Sa  \n");   
    
    

    if (month == 2) { // Έλεγχος για Φεβρουάριο
        if (year < 1752 || (year == 1752 && month < 9)) { // Ιουλιανό ημερολόγιο
            maxdaysofmonth[1] = (year % 4 == 0 && year % 100 != 0) ? 29 : 28;
        } else { // Γρηγοριανό ημερολόγιο
            maxdaysofmonth[1] = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        }
    }

    if(month == 9 && year == 1752){ //Για να μην κάνουμε πιο περίπλοκο το προγραμμα στην περίπτωση που είναι ο μήνας αλλαγής(Σεπτέμβρης 1752) θα τυπώνεται κατεθείαν
        printf("       1  2 14 15 16\n17 18 19 20 21 22 23\n24 25 26 27 28 29 30\n");
        exit(2);
    }
    // Υπολογισμός της πρώτης ημέρας του μήνα
    day = get_dow(1, month, year);

    firstday(day); // Εκτυπώνει την πρώτη μέρα του μήνα με τα κατάλληλα κενά
    if(day == 0)
        printf("\n");

    for (int i = 2; i <= maxdaysofmonth[month - 1]; i++) {  // για τις υπόλοιπες μέρες του μήνα

        if (day == 6) {  // Αν είναι Σάββατο
            printf("%2d\n", i); 
            day = 0;  // κάνουμε κυριακή την μέρα μετά το Σάββατο
        } else {
            printf("%2d ", i);
            day++;  // Αύξηση της ημέρας για την επόμενη
        }
    }

    printf("\n");
}

void firstday(int first_day) { // Συνάρτηση για να εκτυπώνουμε την πρώτη μέρα του μήνα
    switch (first_day) {
        case 1: // Κυριακή
            printf(" 1 ");
            break;
        case 2: // Δευτέρα
            printf("    1 ");
            break;
        case 3: // Τρίτη
            printf("       1 ");
            break;
        case 4: // Τετάρτη
            printf("          1 ");
            break;
        case 5: // Πέμπτη
            printf("             1 ");
            break;
        case 6: // Παρασκευή
            printf("                1 ");
            break;
        case 0: // Σάββατο
            printf("                   1 ");
            break;
        default:
            break;
    }
}


int get_dow(int day, int month, int year){

    if (month < 3) {  // Αλλαγες για σωστό υπολογισμό του τύπου
        month += 12;
        year -= 1;
    }

    if (year < 1752 || (year == 1752 && month < 9)) { 
    int dayOfWeek = (day + (13 * (month + 1)) / 5 + year + (year / 4) + 5) % 7;

    return dayOfWeek; // Ιουλιανό ημερολόγιο

    }   else if(year > 1752 || (year == 1752 && month > 9)){

        return (day + (13 * (month + 1)) / 5 + year + (year / 4) - (year / 100) + (year / 400)) % 7;  // Γρηγοριανό ημερολόγιο
    }else 
        return(0); 
}

void printyear(int year) {
    int i, j;
    int count = 0;

    int temp = year;
    while (temp != 0) {
        temp /= 10;
        count++;
    }

    printf("%*s%d%*s\n", (65 - count) / 2, "", year, (65 - count) / 2, ""); // Εκτύπωση αριθμού έτους στο κέντρο.

    for (i = 0; i < 4; i++) { // 4 γραμμές.
        printf("\n");

        // Εκτύπωση ονόματος μηνών.
        for (j = 0; j < 3; j++) {
            int month = i * 3 + j + 1; // Υπολογισμός του μήνα.
            printf("%12s%10s", months[month - 1], ""); // Εκτύπωση ονόματος μήνα από τον πίνακα.
        }
        printf("\n");

        // Εκτύπωση ονόματος ημερών της εβδομάδας.
        for (j = 0; j < 3; j++) {
            printf("Su Mo Tu We Th Fr Sa  ");
        }
        printf("\n");

        int day1[3], daysInMonth[3]; // Πρώτη μέρα και αριθμός ημερών για κάθε μήνα της σειράς.
        for (j = 0; j < 3; j++) {
            int month = i * 3 + j + 1; // Υπολογισμός του μήνα.
            day1[j] = get_dow(1, month, year); // Υπολογισμός πρώτης ημέρας.
            daysInMonth[j] = maxdaysofmonth[month - 1]; // Αριθμός ημερών του μήνα.
        }

        int fin[3] = {0, 0, 0}; // Έλεγχος ολοκλήρωσης μηνών.
        for (int week = 0; !fin[0] || !fin[1] || !fin[2]; week++) {
            for (j = 0; j < 3; j++) {
                if (fin[j]) {
                    printf("                   "); // Εκτύπωση κενών για ολοκληρωμένους μήνες.
                } else {
                    for (int day = 0; day < 7; day++) {
                        int current_day = week * 7 + day - day1[j] + 2; // Υπολογισμός ημέρας.
                        if (current_day > 0 && current_day <= daysInMonth[j]) {
                            printf("%2d ", current_day);
                        } else {
                            printf("   ");
                        }
                    }
                    if (week * 7 + 1 - day1[j] + 2 > daysInMonth[j]) {
                        fin[j] = 1; // Ο μήνας ολοκληρώθηκε.
                    }
                }
                printf(" "); // Κενά μεταξύ μηνών.
            }
            printf("\n");
        }
    }
}



