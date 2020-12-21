
#include <stdio.h>
#include <stdlib.h>
#include "linkedListFunctions.h"
//#define NDEBUG
#include <assert.h>

void print_Menu(){
    printf("This program finds smallest number in txt file\n");
    printf("Choose what you want to do:\n");
    printf("0. Exit program\n");
    printf("1. Read file and create a list\n");
    printf("2. Print list\n");
    printf("3. Find smallest number and remove it\n");
    printf("4. Reprint options\n");
    printf("5. Print file format\n");
}


void print_File_Format(){
    printf("Only integer values are read in the file\n");
    printf("Any values that are not integer will be ignored\n");
    printf("Also values bigger than 9 numbers will also be ignored\n");
    printf("Press enter to continue");
    getchar();
}


int input(doubleLinkedList** list){
    int number = -1;
    int return_code;
    int smallest;

    while(number < 0 || number > 5){
        printf("Enter choice: ");
        while ((return_code = scanf("%d", &number) == 0) || (getchar() != '\n')){
            scanf("%*[^\n]");
            printf("Enter a  valid number: ");
        }
    }

    switch (number){
        case 0:
            *list = free_Memory(*list);
            printf("exiting...");
            return 0;
        case 1:
            system("cls");
            *list = read_File(list);
            //print_List(*list);
            system("cls");
            return 1;
        case 2:
            system("cls");
            print_List(*list);
            system("cls");
            return 1;
        case 3:
            system("cls");
            smallest = get_Smallest(*list);
            printf("Smallest element is: %d\n", smallest);
            remove_Smallest(list, smallest);
            printf("Press enter to continue");
            getchar();
            system("cls");
            return 1;
        case 4:
            system("cls");
            return 1;
        case 5:
            system("cls");
            print_File_Format();
            return 1;
        default:
            return 1;
    }

    return 1;
}

int main() {
    doubleLinkedList *list = NULL;
    int exit = 1;
    while(exit){
        print_Menu();
        exit = input(&list);
    }
    return 0;

}
