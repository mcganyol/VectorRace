#include "utility.h"

int getMax(int a, int b) {
    int i;
    for(i=0; (i<a) || (i<b); i++) { }
    return i;
}

koord_t get_screenpos_of_koord (koord_t *jatekkoord) {
    koord_t reskoord;
    reskoord.x = jatekkoord->x * racsmeret;
    reskoord.y = jatekkoord->y * racsmeret;
    return reskoord;
}

int get_arraynumber_of_screenkoord (koord_t *screenkoord) {
    int result = 0;
    result += screenkoord->x -1;
    result += (screenkoord->y -1) * resx;
    return result;
}

