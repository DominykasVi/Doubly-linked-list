#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/*Guard from repetition:
 *  Asserts:
 *  to check if functions get right parameters and
 *  to check if check_If_Digit and check_If_Zero work correctly
 *      */

typedef struct doubleLinkedList{
    int data;
    struct doubleLinkedList* next;
    struct doubleLinkedList* previous;
}doubleLinkedList;
int ends_With_Txt();
char* get_Name();
void print_List(doubleLinkedList* list);
void memory_Allocation_Check(void* pointer);
int check_If_Digit(char* text);
int check_If_Zero(char* text);
void append(struct doubleLinkedList** head_ref, int new_data);
doubleLinkedList* sort_Text(doubleLinkedList* list, char* text);
doubleLinkedList* read_File(doubleLinkedList **list);
int get_Smallest(doubleLinkedList* list);
void remove_Smallest(doubleLinkedList** head, int smallest);
doubleLinkedList*  free_Memory(doubleLinkedList* list);


#endif
