#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    s_cell c;
    strcpy(c.contenu, "=2 3 + A2");

    analyser_chaine(&c);

    printf("Contenu : %s\n", c.contenu);
    printf("Tokens trouvés : %d\n", c.nbTokens);

    for (int i = 0; i < c.nbTokens; i++) {
        s_token t = c.tokens[i];

        if (t.type == VALUE) {
            printf("TOKEN %d : VALUE = %f\n", i, t.value.cst);
        }
        else if (t.type == REF) {
            printf("TOKEN %d : REF = %s\n", i, t.value.ref);
        }
        else if (t.type == OPERATOR) {
            char sym = '?';
            if (t.value.operator == op_add) sym = '+';
            else if (t.value.operator == op_sustr) sym = '-';
            else if (t.value.operator == op_mul) sym = '*';
            else if (t.value.operator == op_div) sym = '/';
            printf("TOKEN %d : OPERATEUR = %c\n", i, sym);
        }
    }
}