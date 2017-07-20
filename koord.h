#ifndef KOORD_H
#define KOORD_H

typedef struct Koord { /* ez a jatekter koordinatai, nem a keppontoke! 1,1 a balfelso sarok */
    int x;
    int y;
} koord_t;

koord_t add_koords (koord_t *koord1, koord_t *koord2);
koord_t sub_koords (koord_t *a, koord_t *b); /* the result vector is from b to a */

#endif
