#include <stddef.h>
#include <stdlib.h>
#include "deck.h"

int compare_cards(const void *card1, const void *card2)
{
    const card_t *c1 = *((const card_t **)card1);
    const card_t *c2 = *((const card_t **)card2);

    if (c1->kind != c2->kind)
        return c1->kind - c2->kind;

    /* Spades < Hearts < Clubs < Diamonds */
    if (c1->kind == SPADE || c1->kind == CLUB)
        return c1->value[0] - c2->value[0];
    else
        return c2->value[0] - c1->value[0];
}

void sort_deck(deck_node_t **deck)
{
    size_t size = 0;
    deck_node_t *node = *deck;
    deck_node_t **cards = NULL;
    size_t i = 0;

    if (deck == NULL || *deck == NULL || (*deck)->next == NULL)
        return;

    while (node != NULL)
    {
        size++;
        node = node->next;
    }

    cards = malloc(size * sizeof(deck_node_t *));
    if (cards == NULL)
        return;

    node = *deck;
    while (node != NULL)
    {
        cards[i++] = node;
        node = node->next;
    }

    qsort(cards, size, sizeof(deck_node_t *), compare_cards);

    *deck = cards[0];
    (*deck)->prev = NULL;

    for (i = 0; i < size - 1; i++)
    {
        cards[i]->next = cards[i + 1];
        cards[i + 1]->prev = cards[i];
    }

    cards[size - 1]->next = NULL;

    free(cards);
}

