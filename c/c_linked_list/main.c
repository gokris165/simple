#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

struct LinkedList {
    char word[5];
    int len;
    struct LinkedList *next;
};

int getLine(char text[], int limit); 
int createList(char text[], struct LinkedList *current);
void sortList(struct LinkedList *head, int word_count);
int compareWords(char *this, int this_len, char *that, int that_len);
void printList(struct LinkedList *node, int word_count);
void swap(struct LinkedList *prev, struct LinkedList *this, struct LinkedList *that);
void displayMenu();
void wordController(struct LinkedList *head, int flags);
void lowercase(char *store, char *this);
void addWord(char *word, int len, struct LinkedList *head);
void deleteList(struct LinkedList *head);

int main() {
    char text[MAXLEN];
    struct LinkedList *head = malloc(sizeof(struct LinkedList));
    head->len = -1;

    printf("Write a sentence: ");               // prompt the user for a sentence
    getLine(text, MAXLEN);                      // read user input
    int wc = createList(text, head);            // create linkedlist
    sortList(head, wc);

    // control flow
    char c;
    displayMenu();
    while (1) {
        printf("> ");
        c = getchar();
        while(getchar() != '\n');

        switch(c) {
            case '1':
                printList(head->next, wc);
                break;
            case '2':
                int LOOKUP_FLAG = 1;
                wordController(head, LOOKUP_FLAG);
                break;
            case '3':
                int INSENSITIVE_LOOKUP_FLAG = 2;
                wordController(head, INSENSITIVE_LOOKUP_FLAG);
                break;
            case '4':
                int ADD_WORD_FLAG = 3;
                wordController(head, ADD_WORD_FLAG);
                break;
            case '5': 
                deleteList(head);
                printf("Write a sentence: ");
                getLine(text, MAXLEN);
                int wc = createList(text, head);
                sortList(head, wc);
                printf("...initialized list\n");
                break;
            case '6':
                printf("exiting...");
                return 0;
            default:
                printf("|...INVALID INPUT...|\n");
                displayMenu();
        }
    }
    return 0;
}

void deleteList(struct LinkedList *head) {
    struct LinkedList *next_node = head->next->next;
    struct LinkedList *erase = head->next;
    while (next_node != NULL) {
        free(erase);
        erase = next_node;
        next_node = next_node->next;
    }
    free(erase);    // free up the last node

    return;         // only the head node should be remaining
}

void lookup(char *word, int len, struct LinkedList *head, int insensitive) {
    struct LinkedList *node = head->next;

    // convert user given word to lowercase
    // use this if insensitive, ignore if sensitive
    char lower_user_word[len + 1];
    lowercase(lower_user_word, word);

    while (node != NULL) {
        if (insensitive) {
            char lower_node_word[10];
            lowercase(lower_node_word, node->word);
            if (compareWords(lower_user_word, len, lower_node_word, node->len) == 0) {
                printf("FOUND\n");
                printf("word: %s \tlen: %d\n", node->word, node->len);
                return;
            }
        } else {
            if (compareWords(word, len, node->word, node->len) == 0) {
                printf("FOUND\n");
                printf("word: %s \tlen: %d\n", node->word, node->len);
                return;
            }
        }
        node = node->next;
    }
    printf("NOT FOUND\n");
}

// convert string stored in *this to lowercase and store it in *store
void lowercase(char *store, char *this) {
    int i;
    for (i = 0; this[i] != '\0'; i++) {
        if (this[i] < 97) store[i] = (32 + this[i]);
        else store[i] = this[i];
    }
    store[i] = this[i];
}

void addWord(char *word, int len, struct LinkedList *head) {
    struct LinkedList *new_node = malloc(sizeof(struct LinkedList));
    new_node->len = len;
    int i;
    // copy first 4 letters to node
    for (i = 0; i < 4 && i < len; i++) {
        new_node->word[i] = word[i];
    }
    new_node->word[i] = '\0';

    // find correct place to insert node
    struct LinkedList *current = head;
    while (current->next != NULL) {
        if (compareWords(word, len, current->next->word, current->next->len) < 0) {
            new_node->next = current->next;
            current->next = new_node;
            return;
        }
        current = current->next;
    }
    // insert node at the end
    if (current->next == NULL) {
        new_node->next = NULL;
        current->next = new_node;
    }
    return;
}

/**
 * flags: 
 * 1 = lookup
 * 2 = insensitive lookup
 * 3 = add word
*/
void wordController(struct LinkedList *head, int flags) {

    char word[MAXLEN];
    printf("Enter word: ");
    int wc = getLine(word, MAXLEN);

    int i;
    for (i = 0; i < wc; i++) {
        if (word[i] == ' ' || word[i] == '\n')
            break;
    }
    word[i] = '\0';
    wc = i; // length of word

    switch (flags) {
        case 1:       // CASE SENSITIVE LOOKUP
            int SENSITIVE_FLAG = 0;
            lookup(word, wc, head, SENSITIVE_FLAG);
            break;
        case 2:       // CASE INSENSITIVE LOOKUP
            int INSENSITIVE_FLAG = 1;
            lookup(word, wc, head, INSENSITIVE_FLAG);
            break;
        case 3:       // ADD WORD
            addWord(word, wc, head);
            break;
        default:
            printf("\n---UNEXPECTED ERROR ---\n");
            printf("function: wordController\n");
            printf("flags: %d\n\n", flags);
    }
}

void displayMenu() {
    printf("\nAvailable options: \n");
    printf("1 = Print words (alphabetical order)\n");
    printf("2 = Lookup word (case sensitive)\n");
    printf("3 = Lookup word (case insensitive)\n");
    printf("4 = Add word\n");
    printf("5 = Delete and initialize new linked list\n");
    printf("6 = EXIT\n");
    printf("---\n");
}

// read user input
int getLine(char text[], int limit) {
    int i, c;
    for (i = 0; i < limit && (c = getchar()) != '\n'; i++) {
        text[i] = c;
    }
    text[i] = '\n';
    text[i+1] = '\0';
    return i;
}

// create linked list
int createList(char text[], struct LinkedList *current) {

    int i, len = 0, wc = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ' || text[i] == '\n') {
            struct LinkedList *node = malloc(sizeof(struct LinkedList));
            node->next = NULL;
            node->len = len;

            // copy first 4 letters to node
            int j, k;
            for (j = i - len, k = 0; k < 4 && k < len; j++, k++) {
                node->word[k] = text[j];
            }
            node->word[k] = '\0';

            current->next = node;
            current = current->next;

            len = 0;    // reset word length
            wc++;
        }
        else 
            len++;
    }
    return wc;
}

// bubble sort linked list
void sortList(struct LinkedList *head, int word_count) {
    struct LinkedList *node;
    for (int i = 1; i < word_count; i++) {
        node = head;
        for (int j = 0; j < word_count - i; j++) {
            if (compareWords(
                    node->next->word,
                    node->next->len,
                    node->next->next->word,
                    node->next->next->len) > 0)
                swap(node, node->next, node->next->next);
            node = node->next;
        }
    }
}

// sort based on ascii value, shorter word < longer word
int compareWords(char *this, int this_len, char *that, int that_len) {
    int i;
    for (i = 0; this[i] != '\0' && that[i] != '\0'; i++) {
        if (this[i] < that[i])
            return -1;
        else if (this[i] > that[i])
            return 1;
    }
    if (this_len < that_len)
        return -1;
    else if (this_len > that_len)
        return 1;
    return 0;
}

// print linked list
void printList(struct LinkedList *node, int word_count) {
    printf("WORD COUNT = %d\n", word_count);
    while(node != NULL) {
        printf("word: %s \tlen: %d\n", node->word, node->len);
        node = node->next;
    }
}

// swap positions of *this and *that 
void swap(struct LinkedList *prev, struct LinkedList *this, struct LinkedList *that) {
    prev->next = that;
    this->next = that->next;
    that->next = this;
}

