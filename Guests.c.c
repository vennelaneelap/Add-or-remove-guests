/* Name: Vennela Neelap
UID: U50476402
Description: The program keeps track of the guest list used by a restraunt. 
Guests can be added by using the operation code a, and listed by p and can quit 
by q. The guests' first name and last name and phone number and party size are used
to list in this program. All these requirements are from Project 8 but Project 9 needs
to have a function that can remove a guest and required info. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_LEN 30
#define PHONE_LEN 20

struct guest {   // This Struct is for a guest who has all the necessary information like phone number,last and first name and party size
    char phone[PHONE_LEN + 1];
    char last[NAME_LEN + 1];
    char first[NAME_LEN + 1];
    int party_size;
    struct guest *next;
};

struct guest *add_guest(struct guest *list); //adds a guest whose contact info isnt on the list
struct guest *remove_guest(struct guest *list); //removes a guest who is on the list or is recently added
void print_list(struct guest *list);  //prints guest list
void clear_list(struct guest *list);
int read_line(char str[], int n); //Reads Input from the user

int main(void) 
{
    char code;

    struct guest *new_list = NULL;
    printf("Operation Code: a for adding to the list at the end, r for removing from the list, p for printing the list; q for quit.\n"); //added 'r' operation code
    for (;;) {    //runs as many times as needed
        printf("Enter operation code: ");     
        scanf(" %c", &code);   //takes user input for operation code(a,p,q)
        while (getchar() != '\n') /* skips to the end of the line */
            ;
        switch (code) {
        case 'a':   new_list = add_guest(new_list); // lets you enter all contact info used by the restraunt
                    break;
        case 'r':   new_list = remove_guest(new_list);
                    break;
        case 'p':   print_list(new_list);  //prints the guest list 
                    break;
        case 'q':   clear_list(new_list);  //quits the code and starts a new linked list
                    return 0;
        default:    printf("Illegal code\n");  //if any letter entered expect for a,p,q, the code is illegal 
        }
        printf("\n");
    }
}

struct guest *add_guest(struct guest *list) {  //takes the pointer guest list and returns an updated list  
    char phone[PHONE_LEN + 1];  //phone array storing the number 
    struct guest *ptr = list;  //pointer to point to the already existing list

    printf("Enter phone number: ");
    read_line(phone, PHONE_LEN);  //asks for a phone number

    while (ptr != NULL) {   //checks if the guests are already in the list 
        if (strcmp(ptr->phone, phone) == 0) {
            printf("guest already exists."); //if guests are already in the list, returns this statement 

            return list;
        }
        ptr = ptr->next;  //returns the original list wihtout making changes
    }

    struct guest *extra_guest = (struct guest *)malloc(sizeof(struct guest));

    if (extra_guest == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }  //if no contact info then allocation will fail

    strcpy(extra_guest->phone, phone);  //stores the phone number for the new guest

    printf("Enter guest's last name: ");  //stores the last name for the new guest
    read_line(extra_guest->last, NAME_LEN);

    printf("Enter guest's first name: "); //stores the first name for the new guest
    read_line(extra_guest->first, NAME_LEN);

    printf("Enter party size: ");  //stores the party size for the new guest
    scanf("%d", &(extra_guest->party_size));

    extra_guest->next = NULL;

    if (list == NULL) {   //returns the new guest as first guest in the list if the list starts out to be empty
        return extra_guest;
    } else {  //else if there is already another guest existing, it takes the new guest to the next line to enter the information
        ptr = list;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = extra_guest;
        return list;
    }
}

void print_list(struct guest *list) {  // prints the list 
    while (list != NULL) {  //if list is not null then takes phone, last and first name and party size.
        printf("%-15s%-20s%-20s%5d\n", list->phone, list->last, list->first, list->party_size);
        list = list->next;// pointer to the next guest
    }
}

void clear_list(struct guest *list) {  //delloacates memory for the entire linked list
    struct guest *ptr= list;
    struct guest *next;

    while (ptr != NULL) {  //contiues the current linked list until its Null
        next = ptr->next;
        free(ptr);
        ptr = next; //next iteration for the new guest 
    }
}

int read_line(char str[], int n) { //reads input, takes an str array and n which is the max number of characters
    int ch, i = 0;  //ch is variable to store each character and i is track the position in the array

    while (isspace(ch = getchar()))  //reads the charcater until a whitespace is entered
        ;
    str[i++] = ch;  
    while ((ch = getchar()) != '\n') {  //continues to read charcter until new line is placed
        if (i < n)
            str[i++] = ch;
    }
    str[i] = '\0'; //null terminator to end the string
    return i;  //length of the array.
}

struct guest *remove_guest(struct guest *list) { // this removes guests including all their info in the linked list
    char phone[PHONE_LEN + 1];
    char last[NAME_LEN + 1];
    char first[NAME_LEN + 1];

    printf("Enter phone number: ");
    read_line(phone, PHONE_LEN);

    printf("Enter guest's last name: ");
    read_line(last, NAME_LEN);

    printf("Enter guest's first name: ");
    read_line(first, NAME_LEN);

    struct guest *ptr = list;
    struct guest *previous = NULL;

    while (ptr != NULL) {
        if (strcmp(ptr->phone, phone) == 0 &&   //guests are recognized using the phone number, last and first name
            strcmp(ptr->last, last) == 0 &&
            strcmp(ptr->first, first) == 0) {  

            if (previous == NULL) {
                list = ptr->next;  //updating the first guets in the list
            } else {
                previous->next = ptr->next; // altering the previous node so it byapaases the removed noed
            }
            free(ptr);   //frees the memory of the existing list
            return list; //returns the updated linked list
        }

        previous = ptr;
        ptr = ptr->next;
    }

    printf("Guest does not exist.\n"); //according to requirements, the print statement is supposed to  print a message "guest does not exist"
    return list; //returing the list according to 3)
}
