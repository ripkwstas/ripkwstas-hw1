#include <stdio.h>
#include <stdlib.h>

const char* whichmonth(int month);
int printmonth(int month, int year);
void firstday(int first_day);
void printyear();
int iouliano();
int grigoriano();


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

// Συνάρτηση για να βρούμε το όνομα του μήνα
const char* whichmonth(int month) {
    switch (month) {
        case 1: return "Jan";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "May";
        case 6: return "Jun";
        case 7: return "Jul";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Oct";
        case 11: return "Nov";
        case 12: return "Dec";
        default: return "Invalid month"; 
    }
}

// Συνάρτηση για να εκτυπώσουμε τον μήνα
int printmonth(int month, int year) { 
    int mera, meres_mhna = 30, typwnw, first_day;
    const char* thismonth;

    thismonth = whichmonth(month);

    printf("         %s\n", thismonth);
    printf("Su Mo Tu We Th Fr Sa\n");

    // 30 ή 31 ημέρες
    if(month == 4 || month == 6 || month == 9 || month == 11)
        meres_mhna = 30;
    else if(month == 2){ // Έλεγχος για Φεβρουάριο
        if(year < 1752 || (year == 1752 && month < 9)){ // Ιουλιανό ημερολόγιο
            if(year % 4 == 0 && year % 100 != 0)
                meres_mhna = 29;
            else
                meres_mhna = 28;
        } else {  // Γρηγοριανό ημερολόγιο
            if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
                meres_mhna = 29;
            else 
                meres_mhna = 28; 
        }
    } else {
        meres_mhna = 31;
    }

    if(month == 9 && year == 1752){ //Για να μην κάνουμε πιο περίπλοκο το προγραμμα στην περίπτωση που είναι ο μήνας αλλαγής θα τυπώνεται κατεθείαν
        printf("       1  2 14 15 16\n17 18 19 20 21 22 23\n24 25 26 27 28 29 30\n");
        exit(1);
    }
    // Υπολογισμός της πρώτης ημέρας του μήνα
    if (year < 1752 || (year == 1752 && month < 9)) { 
        first_day = iouliano(1, month, year); // Ιουλιανό ημερολόγιο
    } else {
        first_day = grigoriano(1, month, year); // Γρηγοριανό ημερολόγιο
    }

    firstday(first_day); // Εκτυπώνει την πρώτη μέρα του μήνα

    //υπόλοιπες ημέρες του μήνα
        for (int i = 2; i <= 9; i++) { 
            int day_of_week = (year < 1752 || (year == 1752 && month < 9)) ? iouliano(i - 1, month, year) : grigoriano(i - 1, month, year);
            
            if (day_of_week == 6) {
                printf("  %d\n", i);
            } else {
                if (day_of_week != 0) {
                    printf("  %d", i); 
                } else {
                    printf(" %d", i); // Όταν είναι Κυριακή
                }
            }
        }

    for (int i = 10; i <= meres_mhna; i++) {
    int day_of_week = (year < 1752 || (year == 1752 && month < 9)) ? iouliano(i - 1, month, year) : grigoriano(i - 1, month, year);
    
        if (day_of_week == 6) {
            printf(" %d\n", i); // Αλλαγή γραμμής μετά το Σάββατο
        } else {
            if (day_of_week != 0) {
                printf(" %d", i); // Κανονική εκτύπωση για μέρες εκτός Κυριακής και Σαββάτου
            } else {
                printf("%d", i); // Όταν είναι Κυριακή
            }
        }
    }
    printf("\n");
}



// Συνάρτηση για να εκτυπώνουμε την πρώτη μέρα του μήνα
void firstday(int first_day) {
    switch (first_day) {
        case 1: // Κυριακή
            printf(" 1");
            break;
        case 2: // Δευτέρα
            printf("    1");
            break;
        case 3: // Τρίτη
            printf("       1");
            break;
        case 4: // Τετάρτη
            printf("          1");
            break;
        case 5: // Πέμπτη
            printf("             1");
            break;
        case 6: // Παρασκευή
            printf("                1");
            break;
        case 0: // Σάββατο
            printf("                   1\n");
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
    for (int month = 1; month <= 12; month++) {
        printmonth(month, year);
        printf("\n");  // Print an empty line between months for readability
    }
}
