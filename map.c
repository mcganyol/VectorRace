#include "map.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include "SDL_image.h"
#include "config.h"
#include "koord.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include "gfx.h"

void init_map (char *a, palya_t *palya) {       /* betolti a palya kepet, beteszi a palyaba a megjelenitendo surface-t is, es a jatekosok kezdohelyet is */
    /* A betoltendo kep palettas, a 0,1,2... stb pixelek jelolik a kov infokat, rendre paletta koddal: palyavonal, startvonal, celconal, p1startpoz,p2startpoz,p3startpoz,p4startpoz */
    int x;
    char a_with_path[50] = "./maps/";
    strcat(a_with_path,a);
    palya->palyakep = IMG_Load(a_with_path); /*this is the .gif, we leave it untouched for main menu*/
        if (!palya->palyakep) {
        fprintf(stderr, "Nem sikerult betolteni a kepfajlt!\n");
        exit(2);
    }
    palya->rajzolando_palyakep = IMG_Load(a_with_path); /*we load it again, to later in this function substitute the pixels we don't want to show in-game*/

    palya->palya_color = ((char*)palya->palyakep->pixels)[0];
    palya->start_color = ((char*)palya->palyakep->pixels)[1];
    palya->finish_color = ((char*)palya->palyakep->pixels)[2];
    palya->p1start_color = ((char*)palya->palyakep->pixels)[3];
    palya->p2start_color = ((char*)palya->palyakep->pixels)[4];
    palya->p3start_color = ((char*)palya->palyakep->pixels)[5];
    palya->p4start_color = ((char*)palya->palyakep->pixels)[6];
    palya->metadata_color = ((char*)palya->palyakep->pixels)[7];
    palya->transparent_color = ((char*)palya->palyakep->pixels)[8];

    for (x = 0; x< palya->palyakep->w * palya->palyakep->h; x++) { /* a jatekos kezdopozicioja, koord-ra atszamitva, az utolso elofordulas szamit ha tobb is van a kepen! */
        if (((char*)palya->palyakep->pixels)[x] == palya->p1start_color) {
            palya->p1start.x = round(((x % palya->palyakep->w)+1)/racsmeret);
            palya->p1start.y = round( ( floor(x / palya->palyakep->w) + 1) /racsmeret);
        }
        if (((char*)palya->palyakep->pixels)[x] == palya->p2start_color) {
            palya->p2start.x = round(((x % palya->palyakep->w)+1)/racsmeret);
            palya->p2start.y = round( ( floor(x / palya->palyakep->w) + 1) /racsmeret);
        }
        if (((char*)palya->palyakep->pixels)[x] == palya->p3start_color) {
            palya->p3start.x = round(((x % palya->palyakep->w)+1)/racsmeret);
            palya->p3start.y = round( ( floor(x / palya->palyakep->w) + 1) /racsmeret);
        }
        if (((char*)palya->palyakep->pixels)[x] == palya->p4start_color) {
            palya->p4start.x = round(((x % palya->palyakep->w)+1)/racsmeret);
            palya->p4start.y = round( ( floor(x / palya->palyakep->w) + 1) /racsmeret);
        }
    }

    for (x = 0; x< palya->palyakep->w * palya->palyakep->h; x++) { /*substitute the pixel we dont want to see while in a race*/
        if ((((char*)palya->rajzolando_palyakep->pixels)[x] == palya->p1start_color) ||
            (((char*)palya->rajzolando_palyakep->pixels)[x] == palya->p2start_color) ||
            (((char*)palya->rajzolando_palyakep->pixels)[x] == palya->p3start_color) ||
            (((char*)palya->rajzolando_palyakep->pixels)[x] == palya->p4start_color) ||
            (((char*)palya->rajzolando_palyakep->pixels)[x] == palya->metadata_color) ||
            (((char*)palya->rajzolando_palyakep->pixels)[x] == palya->start_color))
            {
                ((char*)palya->rajzolando_palyakep->pixels)[x] = palya->transparent_color;
            }
    }
}

void build_maplist(palyalista_t **palyalista) {  /* atvett lib, hogy a palyak listajat sikeruljon kiolvasni. a palyak listajat felepitem, egy duplan lancolt korlistaba */
    DIR *dp;
    struct dirent *ep;
    palyalista_t *temp;
    palyalista_t *temp_last;
    dp = opendir ("./maps");
    if (dp != NULL)
    {
        while ((ep = readdir (dp)) != NULL) {
            if (strcmp(strrchr(ep->d_name,'.'),".gif") == 0) {
                if (*palyalista == NULL) { /* nem volt meg egy elemunk sem eddig*/
                    *palyalista = (palyalista_t*)malloc(sizeof(palyalista_t));  /* ezt direkt nem fogom a programban free-zni, mert a futas ido alatt vegig kell! */
                    strcpy((*palyalista)->name, ep->d_name);
                    (*palyalista)->next = *palyalista;
                    (*palyalista)->prev = *palyalista;
                }
                else if ((*palyalista)->next == *palyalista) { /* eddig egy elemu a lancolt lista */
                    temp = (palyalista_t*)malloc(sizeof(palyalista_t)); /*TODO ha nem siekrul a malloc szolni,par sorral feljebb meg lejebb is ugyanez */
                    (*palyalista)->next = temp;
                    (*palyalista)->prev = temp;
                    temp->next = *palyalista;
                    temp->prev = *palyalista;
                    strcpy(temp->name, ep->d_name);
                }
                else  { /* 2 vagy tobb elemu mar a listank */
                    temp = (palyalista_t*)malloc(sizeof(palyalista_t));
                    temp_last = (*palyalista)->prev;
                    (*palyalista)->prev = temp;
                    temp_last->next = temp;
                    temp->next = (*palyalista);
                    temp->prev = temp_last;
                    strcpy(temp->name, ep->d_name);
                }
            }
        }

        closedir (dp);
    }
    else
        exit(3); /*Couldn't open the directory*/

}

