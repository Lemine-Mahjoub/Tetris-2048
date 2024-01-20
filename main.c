#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"
#include "menuPrincipal.c"
#include "jeu.c"

int main() {
    int a = menuPrincipal();
    if (a == 1) {
        jeu();
    }
    return 0;
}