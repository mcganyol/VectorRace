#include "koord.h"

koord_t add_koords (koord_t *koord1, koord_t *koord2) {
    koord_t result;
    result.x = koord1->x + koord2->x;
    result.y = koord1->y + koord2->y;
    return result;
}

koord_t sub_koords (koord_t *a, koord_t *b) { /* the result vector is from b to a */
    koord_t result;
    result.x = a->x - b->x;
    result.y = a->y - b->y;
    return result;
}

