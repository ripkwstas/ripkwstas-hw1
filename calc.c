#include <stdio.h>
#include <stdlib.h>

int printmonth();
void firstday();
void printyear();
int iouliano();
int grigoriano();

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
        goto september;
    }
    // Υπολογισμός της πρώτης ημέρας του μήνα
    if (year < 1752 || (year == 1752 && month < 9)) { 
        day = iouliano(1, month, year); // Ιουλιανό ημερολόγιο
    } else {
        day = grigoriano(1, month, year); // Γρηγοριανό ημερολόγιο
    }

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
    september:
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


int iouliano(int day, int month, int year) {
    if (month < 3) {  
        month += 12;
        year -= 1;
    }
    
    int dayOfWeek = (day + (13 * (month + 1)) / 5 + year + year + (year / 4)) % 7;
    return dayOfWeek;  
}

int grigoriano(int day, int month, int year) {
    if (month < 3) {  
        month += 12;
        year -= 1;
    } 
    
    return (day + (13 * (month + 1)) / 5 + year + (year / 4) - (year / 100) + (year / 400)) % 7;
}

void printyear(int year) {
    int day1, day2, day3;
    int d1 = 2, d2 = 2, d3 = 2;
    int month;

    // Προσαρμογή των ημερών Φεβρουαρίου 
    if (year < 1752 || (year == 1752 && 9 > 9)) { // Ιουλιανό ημερολόγιο
        maxdaysofmonth[1] = (year % 4 == 0 && year % 100 != 0) ? 29 : 28;
    } else { // Γρηγοριανό ημερολόγιο
        maxdaysofmonth[1] = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }

    for (month = 0; month < 12; month += 3) { // Εκτύπωση ονομάτων μηνών
        printf("         %s                     %s                     %s           \n", months[month], months[month + 1], months[month + 2]);
        printf("Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa  \n");

        // Υπολογισμός της πρώτης ημέρας κάθε μήνα
        day1 = (year < 1752 || (year == 1752 && month < 9)) ? iouliano(1, month + 1, year) : grigoriano(1, month + 1, year);
        day2 = (year < 1752 || (year == 1752 && month + 1 < 9)) ? iouliano(1, month + 2, year) : grigoriano(1, month + 2, year);
        day3 = (year < 1752 || (year == 1752 && month + 2 < 9)) ? iouliano(1, month + 3, year) : grigoriano(1, month + 3, year);


        
        // Εκτύπωση της πρώτης εβδομάδας για τους τρεις μήνες

            firstday(day1);
            if(day1 == 0){
                printf("   ");
                d1++;
            }else if(day1 == 6){
                printf(" %2d", d1);
                d1++;
            }else{
                for(int j = 1; j <= 7; j++){
                    if(day1 == 6){
                        printf("%2d ", d1);
                        d1++;
                        printf("%2d  ", d1);
                        d1++;
                        break;
                    }else{
                        printf("%2d ", d1);
                        d1++;
                        day1++;
                    }
                }
            }
            firstday(day2);
            if(day2 == 0){
                printf("   ");
                d2++;
            }else if(day2 == 6){
                printf(" %2d", d2);
                d2++;
            }else{
                for(int j = 1; j <= 7; j++){
                    if(day2 == 6){
                        printf("%2d ", d2);
                        d2++;
                        printf("%2d  ", d2);
                        d2++;
                        break;
                    }else{
                        printf("%2d ", d2);
                        d2++;
                        day2++;
                    }
                }
            }
            firstday(day3);
            if(day3 == 0){
                printf("   ");
                d3++;
            }else if(day3 == 6){
                printf(" %2d", d3);
                d3++;
            }else{
                for(int j = 3; j <= 7; j++){
                    if(day3 == 6){
                        printf("%2d ", d3);
                        d3++;
                        printf("%2d  ", d3);
                        d3++;
                        break;
                    }else{
                        printf("%2d ", d3);
                        d3++;
                        day3++;
                    }
                }
            }
            printf("\n");
    



       

            
        // Εκτύπωση των υπολοίπων ημερών για κάθε μήνα
        for (int i = 0; i < 5; i++) { // 5 εβδομάδες προς εκτύπωση
            // Εκτύπωση εβδομάδας για τον πρώτο μήνα
            for (int j = 0; j < 7; j++) {
                if (d1 <= maxdaysofmonth[month]) {
                    if (i == 0 && j >= day1) {
                        printf("%2d ", d1++);
                    } else if (i > 0) {
                        printf("%2d ", d1++);
                    } else {
                        printf("   ");
                    }
                } else {
                    printf("   ");
                }
            }
            printf("   ");
            // Εκτύπωση εβδομάδας για τον δεύτερο μήνα
            for (int j = 0; j < 7; j++) {
                if (d2 <= maxdaysofmonth[month + 1]) {
                    if (i == 0 && j >= day2) {
                        printf("%2d ", d2++);
                    } else if (i > 0) {
                        printf("%2d ", d2++);
                    } else {
                        printf("   ");
                    }
                } else {
                    printf("   ");
                }
            }
            printf("   ");
            // Εκτύπωση εβδομάδας για τον τρίτο μήνα
            for (int j = 0; j < 7; j++) {
                if (d3 <= maxdaysofmonth[month + 2]) {
                    if (i == 0 && j >= day3) {
                        printf("%2d ", d3++);
                    } else if (i > 0) {
                        printf("%2d ", d3++);
                    } else {
                        printf("   ");
                    }
                } else {
                    printf("   ");
                }
            }
            printf("\n");
        }
    }
}

