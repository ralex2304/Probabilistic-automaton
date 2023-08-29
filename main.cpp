#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "nodevector.h"
#include "automaton_parser.h"

int main(int argc, char* argv[]) {
    int LEVEL = 3;
    ssize_t cnt = 1000;
    if (argc < 3) {
        printf("Max automaton level and symbols count isn't specified. Autoset level to 5 and 1000\n");
    } else if (argc > 3) {
        printf("Wrong console arguments. Exiting\n");
        return 1;
    } else {
        if (sscanf(argv[1], "%d", &LEVEL) != 1) {
            printf("Wrong console argument. Specify max automaton level\n");
            return 0;
        }
        if (sscanf(argv[2], "%lld", &cnt) != 1) {
            printf("Wrong console argument. Specify symbols count\n");
            return 0;
        }
    }

    FILE* file = fopen("text.txt", "r");

    Nodes nodes = {};
    vec_ctor(&nodes.vec);

    auto_parse(file, &nodes, LEVEL);

    fclose(file);

    char str[10] = {};

    printf("---------- level %d ----------\n", LEVEL);

    auto_get_node(&nodes, str, 0, 0, LEVEL);

    int downgrade = 0;
    while (--cnt > 0) {
        for (ssize_t i = 0; i < LEVEL; i++)
            str[i] = str[i + 1];

        while (!auto_get_node(&nodes, str, 0, LEVEL, LEVEL) && --cnt > 0) {
            downgrade++;
            if (LEVEL < downgrade) downgrade = LEVEL;

            auto_get_node(&nodes, str, 0, LEVEL - downgrade, LEVEL);

            printf("%c", str[0]);
            for (ssize_t i = 0; i < LEVEL; i++)
                str[i] = str[i + 1];
        }
        printf("%c", str[0]);
        downgrade = 0;
    }
    printf("\n---------- stop ----------\n");

    auto_detor(&nodes);
}
