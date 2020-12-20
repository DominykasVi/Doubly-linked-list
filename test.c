//LSP: 1911122, Dominykas Višnevskis, dominykas.vi@gmail.com(studento dominykas.visnevskis@mif.stud.vu.lt), 3 uzd
#include <stdio.h>
#include <stdlib.h>
#include "linkedListFunctions.h"
//#define NDEBUG
#include <assert.h>
#include <string.h>
#include <assert.h>

doubleLinkedList* return_End(doubleLinkedList* list){
    while (list->next != NULL){
        list = list->next;
    }
    return list;
}

int main() {
    doubleLinkedList *list = NULL;
    system("cls");
    
    //test append
    append(&list, 1);
    assert(list->data == 1);
    append(&list, -10);
    assert(return_End(list)->data == -10);
    append(&list, 0);
    assert((return_End(list)->data) == 0);
    append(&list, 14);
    assert(return_End(list)->data == 14);

    //test txt
    assert(ends_With_Txt("file.txt") == 1);
    assert(ends_With_Txt("fitxtle.txt") == 1);
    assert(ends_With_Txt("filetttt.txt") == 1);
    assert(ends_With_Txt("fileaaaaaa.txt") == 1);
    assert(ends_With_Txt("file.tx") == -1);
    assert(ends_With_Txt("file.xt") == -1);
    assert(ends_With_Txt("file.tt") == -1);
    assert(ends_With_Txt("file.x") == -1);
    assert(ends_With_Txt("file.xx") == -1);
    assert(ends_With_Txt("txt.xx") == -1);
    assert(ends_With_Txt("file") == -1);

    //digit check
    assert(check_If_Digit("983") == 0);
    assert(check_If_Digit("9") == 0);
    assert(check_If_Digit("98765") == 0);
    assert(check_If_Digit("a9a") == 1);
    assert(check_If_Digit("9a9") == 1);
    assert(check_If_Digit("a9") == 1);
    assert(check_If_Digit("9a") == 1);

    //zero check
    assert(check_If_Zero("0") == 0);
    assert(check_If_Zero("0a") == 1);
    assert(check_If_Zero("a0") == 1);
    assert(check_If_Zero("0a0") == 1);
    assert(check_If_Zero("a0a") == 1);
    assert(check_If_Zero("000") == 0);
    assert(check_If_Zero("00000") == 0);

    //test get smallest and remove smallest
    remove_Smallest(&list, -120);
    assert(get_Smallest(list) == -10);
    remove_Smallest(&list, -10);
    assert(get_Smallest(list) == 0);
    remove_Smallest(&list, 0);
    assert(get_Smallest(list) == 1);
    remove_Smallest(&list, 1);
    assert(get_Smallest(list) == 14);
    remove_Smallest(&list, 14);

    append(&list, 0);
    assert(get_Smallest(list) == 0);
    append(&list, -5);
    assert(get_Smallest(list) == -5);
    append(&list, 6);
    assert(get_Smallest(list) == -5);
    append(&list, 7);
    assert(get_Smallest(list) == -5);
    system("cls");

    //check sort text
    list = free_Memory(list);
    char *text = (char*) calloc(22, sizeof(char));
    strcpy(text, "0 9a");
    assert(sort_Text(list, text)->data == 0);
    strcpy(text, "0 9");
    assert(sort_Text(list, text)->next->data == 9);
    strcpy(text, "0 9a a9 a9a 9a9 1");
    assert(sort_Text(list, text)->next->data == 1);
    strcpy(text, "0 -1 -9a -a9 -a9a -9a9 -1");
    assert(sort_Text(list, text)->next->data  == -1);
    strcpy(text, "0 1 2 3 4 5s5 6");
    assert(sort_Text(list, text)->next->next->next->data == 3);
    strcpy(text, "0 1 2 3 4 5s5 6");
    assert(sort_Text(list, text)->next->next->next->next->next->data == 6);

    printf("All tests passed");
    return 0;
}
