#include<stdio.h>

static int n,filteredCount;

struct Rooms {
    char name[30];
    char address[100];
    int grade;
    int charge;
    int rooms;
};

//function to read data.
void readRoom(struct Rooms a[]) {
    int i;
    for(i = 0; i < n; i++) {
        printf("Give room %d, name\n>>> ", i+1);
        scanf(" %[^\n]", a[i].name);
        printf("Give room %d, address\n>>> ", i+1);
        scanf(" %[^\n]", a[i].address);
        printf("Give room %d, grade rating\n>>> ", i+1);
        scanf("%d", &a[i].grade);
        printf("Give room %d, average charge\n>>> ", i+1);
        scanf("%d", &a[i].charge);
        printf("Give room %d, number of rooms\n>>> ", i+1);
        scanf("%d", &a[i].rooms);
        printf("\n");
    }
}

//function to filter by grade.
void filterByGrade(struct Rooms a[], struct Rooms b[], int filter) {
    int i, j = 0;
    for(i = 0; i < n; i++) {
        if(a[i].grade >= filter) {
            b[j] = a[i];
            j++;
        }
    filteredCount++;
    }
}

//function to sort by charges.
void sortByCharges(struct Rooms a[], int size) {
    int i, j;
    struct Rooms temp;
    for(i = 0; i < size-1; i++) {
        for(j = 0; j < size-i-1; j++) {
            if(a[j].charge < a[j+1].charge) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

//function to display result.
void display(struct Rooms a[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("\nRoom %d\n", i+1);
        printf("Room Name: %s\n", a[i].name);
        printf("Address: %s\n", a[i].address);
        printf("Grade: %d\n", a[i].grade);
        printf("Charges: %d\n", a[i].charge);
        printf("Number of rooms: %d\n\n", a[i].rooms);
    }
}

int main() {
    int filter;
    printf("How many rooms do you wish to review?\n>>> ");
    scanf("%d", &n);
    
    struct Rooms arr[n], result[n];
    
    readRoom(arr);
    
    printf("Filter by grade\n>>> ");
    scanf("%d", &filter);
    
    filterByGrade(arr, result, filter);
    sortByCharges(result, filteredCount);
    display(result, filteredCount);
    
    return 0;
}
