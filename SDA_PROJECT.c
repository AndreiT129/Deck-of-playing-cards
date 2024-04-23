#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct card {
    int value;
    char symbol[10];
    struct card* next;
    struct card* prev;
} card;

typedef struct deck {
    int number;
    card* head;
    card* tail;
    struct deck* next;
    struct deck* prev;
} deck;

deck* create_deck(int number) {
	//function for creating a new deck//
	int i;
    deck* new_deck = (deck*) malloc(sizeof(deck));
    new_deck->number = number;
    new_deck->head = NULL;
    new_deck->tail = NULL;
    new_deck->next = NULL;
    new_deck->prev = NULL;
    int num_cards;
    printf("Enter number of cards to add to deck: ");
    scanf("%d", &num_cards);
    for(i = 0; i < num_cards; i++) {
        add_card(new_deck);
    }
    printf("\nTHE DECK HAS BEEN CREATED!\n");
    return new_deck;
}


void add_card(deck* d) {
	//adding cards to a existing deck//
    card* new_card = (card*) malloc(sizeof(card));
    int value;
    char symbol[10];
    printf("Enter card value and symbol (e.g. 7 clubs): ");
    scanf("%d %s", &value, symbol);
    //checking if the valuw is between 1-14//
    if(value < 1 || value > 14){
        printf("The provided card value is not a valid one\n");
        return;
    }
    //checking if the symbol is within the acceptable ones//
    if(strcmp(symbol,"diamonds") && strcmp(symbol,"clubs")&& strcmp(symbol,"hearts")&& strcmp(symbol,"spades")){
        printf("The provided card symbol is not a valid one\n");
        return;
    }
    new_card->value = value;
    strcpy(new_card->symbol,symbol);
    new_card->next = NULL;
    new_card->prev = d->tail;
    if(d->tail) {
        d->tail->next = new_card;
    }
    d->tail = new_card;
    if(!d->head) {
        d->head = new_card;
    }
    printf("\nCARD ADDED!\n");
}


void delete_card(deck* d, card* c) {
	//function from deleting a card//
    if(c->prev) {
        c->prev->next = c->next;
    }
    if(c->next) {
        c->next->prev = c->prev;
    }
    if(c == d->head) {
        d->head = c->next;
    }
    if(c == d->tail) {
        d->tail = c->prev;
    }
    free(c);
    printf("\nCARD DELETED!\n");
}

void delete_deck(deck* d) {
	//function for deleting a deck//
    card* c = d->head;
    while(c) {
        card* next = c->next;
        free(c);
        c = next;
    }
    free(d);
    printf("\nTHE DECK HAS BEEN DELETED!\n");
}

void display_deck(deck* d) {
	//function for displaying a specified deck//
    printf("Deck Number: %d\n", d->number);
    card* c = d->head;
    while(c) {
        printf("%d of %s\n", c->value, c->symbol);
        c = c->next;
    }
}

void display_deck_cards(deck* d) {
	//function for displaying the cards within a specidied deck//
    card* c = d->head;
    while(c) {
        printf("%d of %s\n", c->value, c->symbol);
        c = c->next;
    }
}

void display_all(deck* head) {
	//fucntion for displaying all the available decks//
    deck* current = head;
    while(current) {
        printf("Deck Number: %d\n", current->number);
        display_deck_cards(current);
        current = current->next;
    }
}


int main() {
    deck* head = NULL;
    deck* tail = NULL;
    int user_choice;
    do{	printf("\n\n");
        printf("What would you like to do?\n");
        printf("1. Create a deck\n");
        printf("2. Add a card to a deck\n");
        printf("3. Delete a card from a deck\n");
        printf("4. Delete a deck\n");
        printf("5. Display a deck\n");
        printf("6. Display all decks\n");
        printf("7. Exit\n\n");
        scanf("%d", &user_choice);
        switch(user_choice) {
            case 1: {
                int deck_num;
                printf("Enter deck number: ");
                scanf("%d", &deck_num);
                printf("\n");
                deck* new_deck = create_deck(deck_num);
                if(!head) {
                    head = new_deck;
                    tail = new_deck;
                } else {
                    new_deck->prev = tail;
                    tail->next = new_deck;
                    tail = new_deck;
                }
                break;
            }


            case 2: {
                int deck_num;
                printf("Enter deck number: ");
                scanf("%d", &deck_num);
                deck* current = head;
                while(current) {
						                    if(current->number == deck_num) {
                        add_card(current);
                        break;
                    }
                    current = current->next;
                }
                if(!current) {
                    printf("Deck not found\n");
                }
                break;
            }
            case 3: {
                int deck_num, card_value;
                char card_symbol[10];
                printf("Enter deck number: ");
                scanf("%d", &deck_num);
                printf("Enter card value: ");
                scanf("%d", &card_value);
                printf("Enter card symbol: ");
                scanf("%s", card_symbol);
                deck* current = head;
                while(current) {
                    if(current->number == deck_num) {
                        card* c = current->head;
                        while(c) {
                            if(c->value == card_value && !strcmp(c->symbol, card_symbol)) {
                                delete_card(current, c);
                                break;
                            }
                            c = c->next;
                        }
                        if(!c) {
                            printf("Card not found in deck\n");
                        }
                        break;
                    }
                    current = current->next;
                }
                if(!current) {
                    printf("Deck not found\n");
                }
                break;
            }
            case 4: {
                int deck_num;
                printf("Enter deck number: ");
                scanf("%d", &deck_num);
                deck* current = head;
                while(current) {
                    if(current->number == deck_num) {
                        if(current == head) {
                            head = current->next;
                            if(head) {
                                head->prev = NULL;
                            }
                        }
                        if(current == tail) {
                            tail = current->prev;
                            if(tail) {
                                tail->next = NULL;
                            }
                        }
                        if(current->prev) {
                            current->prev->next = current->next;
                        }
                        if(current->next) {
                            current->next->prev = current->prev;
                        }
                        delete_deck(current);
                        break;
                    }
                    current = current->next;
                }
                if(!current) {
                    printf("Deck not found\n");
                }
                break;
            }
            case 5: {
                int deck_num;
                printf("Enter deck number: ");
                scanf("%d", &deck_num);
                deck* current = head;
                while(current) {
                    if(current->number == deck_num) {
                        display_deck(current);
                        break;
                    }
                    current = current->next;
                }
                if(!current) {
                    printf("Deck not found\n");
                }
                break;
            }
            case 6: {
                display_all(head);
                break;
            }
            case 7: {
                break;
            }
            default: {
				   printf("Invalid option\n");
                break;
            }
        }
    } while(user_choice != 7);
    deck* current = head;
    while(current) {
        delete_deck(current);
        current = current->next;
    }
    return 0;
}


