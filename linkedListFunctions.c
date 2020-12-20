#include "linkedListFunctions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
//#define NDEBUG


int ends_With_Txt(char *file_name){
    assert(file_name);
    file_name = strrchr(file_name, '.');

    if( file_name != NULL ){
        if(strcmp(file_name, ".txt") == 0){
            return 1;
        } else {
            return -1;
        }
    }
    return -1;
}


char* get_Name(){//used for getting filename
    printf("Please enter name of the files you want to read in xxx.txt format(filename cannot be longer than 260 characters): \n");
    char *name = malloc(260 * sizeof(char));//MAX_SIZE of filename
    memory_Allocation_Check(name);//check if malloc works
    int ending_value = -1;

    while(ending_value < 0){
        if (fgets(name, 260, stdin)) {
            name[strcspn(name, "\n")] = '\0';//replace /n with \0, for opening
            ending_value = ends_With_Txt(name);//function t check if ends with .txt, if so return 1
            if (ending_value != 1){
                printf("Please enter a valid name:");
            }
        }
    }
    return name;
}


void print_List(doubleLinkedList* list){
    //assert(list);
    if(list == NULL){
        printf("No list found\n");
        printf("Press enter to continue");
        getchar();
        return;
    }

    doubleLinkedList* last;
    printf("Print in forward direction \n");
    while (list != NULL){
        printf("%d ", list->data);
        last = list;
        list = list->next;
    }

    printf("\nPrint in reverse direction \n");
    while (last != NULL){
        printf("%d ", last->data);
        last = last->previous;
    }

    printf("\n");
    printf("Press enter to continue");
    getchar();
}


void memory_Allocation_Check(void* pointer){
    if(pointer == NULL){
        printf("Cannot allocate memory\n");
        exit(1);
    }
}


int check_If_Digit(char* text){
    assert(text != NULL);
    int length = strlen(text);

    if(length > 9){
        return 1;
    }

    int digit = 0;

    for(int i = 0; i < length; ++i) {
        digit += isdigit(((int)text[i]));
    }
    if(digit == length){
        return 0;
    }

    return 1;
}


int check_If_Zero(char* text){
    assert(text != NULL);
    int length = strlen(text);
    int match = 0;

    for(int i = 0; i < length; ++i){
        if(((int)text[i]) == 48){
            ++match;
        }
    }

    if (match == length){
        return 0;
    }
    return 1;
}


void append(struct doubleLinkedList** head_value, int new_data){
    assert(new_data < INT_MAX);
    assert(new_data > INT_MIN);
    doubleLinkedList* new_item = (doubleLinkedList*) malloc (sizeof(struct doubleLinkedList));
    memory_Allocation_Check(new_item);
    doubleLinkedList* last = *head_value;

    new_item->data = new_data;
    new_item->next = NULL;

    if (*head_value == NULL) {
        new_item->previous = NULL;
        *head_value = new_item;
        return;
    }
    while (last->next != NULL){
        last = last->next;
    }

    last->next = new_item;
    new_item->previous = last;
}

doubleLinkedList* sort_Text(doubleLinkedList* list, char* text){
    assert(text);
    if(text == NULL){
        return list;
    }

    char delimiter[] = " \n";
    char *separation_pointer = strtok(text, delimiter);
    int variable;

    if(strncmp(separation_pointer, "-", 1) != 0){//!!!changes
        variable = atoi(separation_pointer);
        if((variable != 0 && check_If_Digit(separation_pointer) == 0) || check_If_Zero(separation_pointer) == 0){
            append(&list, variable);
        }
    } else {
        variable = atoi((separation_pointer+1));
        if((variable != 0 && check_If_Digit(separation_pointer+1) == 0) || check_If_Zero(separation_pointer+1) == 0){
            variable = -1 * variable;
            append(&list, variable);
        }
    }

    while(separation_pointer != NULL){
        separation_pointer = strtok(NULL, delimiter);
        if (separation_pointer == NULL){
            break;
        }
        //printf("%d", strncmp(separation_pointer, "-", 1));//!!!not necessary
        if(strncmp(separation_pointer, "-", 1) != 0){
            variable = atoi(separation_pointer);
            if((variable != 0 && check_If_Digit(separation_pointer) == 0) || check_If_Zero(separation_pointer) == 0){
                append(&list, variable);
            }
        } else {
            variable = atoi((separation_pointer+1));//If we have negative value, atoi wont convert it, so we give it string without negative sign (pointer+1) and after multiply by -1
            if((variable != 0 && check_If_Digit(separation_pointer+1) == 0) || check_If_Zero(separation_pointer+1) == 0){
                variable = -1 * variable;
                append(&list, variable);
            }
        }
    }
    return list;
}


doubleLinkedList* read_File(doubleLinkedList **list){
    FILE *file_pointer;
    char* name = NULL;
    //doubleLinkedList *list = NULL;
    int file_open = 0;

    while (file_open == 0){
        name = get_Name();
        if ((file_pointer = fopen(name, "r")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else{
            printf("Successfully opened file\n");
            file_open = 1;
        }
    }

    int buffer_size = 256;
    char read[buffer_size];

    while ((fgets(read, buffer_size, file_pointer)) != NULL) {
        *list = sort_Text(*list, read);
    }
    if(list == NULL){
        printf("Could not make a list of numbers (might be because file is empty!)\n");
    } else {
        printf("File read successfully\n");
    }

    if(file_pointer != NULL){
        fclose(file_pointer);
    }

    printf("Press enter to continue");
    getchar();
    return *list;
}


int get_Smallest(doubleLinkedList* list){
    assert(list);//Changes!!!
    int smallest = list->data;
    int number;
    if(list == NULL){
        printf("No list detected!\n");
        return 0;
    }

    //doubleLinkedList *previous;

    if(list->next == NULL){
        return list->data;
    } else {
        number = get_Smallest(list->next);
        if(number < smallest){
            return number;
        } else {
            return smallest;
        }//Changes!!!
//        if (list->previous != NULL){
//            previous = list->previous;
//            if(smallest < previous->data){
//                return smallest;
//            } else{
//                return previous->data;
//            }
//        } else {
//            if(smallest < list->data){
//                return smallest;
//            } else {
//                return list->data;
//            }
//        }
    }
}


void remove_Smallest(doubleLinkedList** head, int smallest){
    assert(smallest < INT_MAX);
    assert(smallest > INT_MIN);
    doubleLinkedList *small = *head;

    if(small == NULL){
        printf("No list exists\n");
        return;
    }

    while (small->data != smallest && small->next != NULL){ //!!!Changes
        small = small->next;
    }
    if(small->next == NULL && small->data != smallest){
        printf("No such number found\n");
        return;
    }

    if(small->next == NULL && small->previous == NULL){
        *head = NULL;
    } else if(small->next == NULL){
        small->previous->next = NULL;
    } else if (small->previous == NULL){
        small->next->previous = NULL;
        *head = small->next;
    } else {
        small->previous->next = small->next;
        small->next->previous = small->previous;
    }

    free(small);
    printf("Smallest item removed\n");
}


doubleLinkedList* free_Memory(doubleLinkedList* list){//!!!Changes
    if(list == NULL){
        return NULL;
    }

    doubleLinkedList *current;
    while(list != NULL){
        current = list;
        list = list->next;
        free(current);
    }
    return list;
//    doubleLinkedList *current;
//    doubleLinkedList *next_item;
//
//    while(current->next != NULL){
//        print_List(list);
//        next_item = current->next;
//        free(current);
//        current = next_item;
//    }

    //free(current);
}