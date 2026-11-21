#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define M 65536

int main() {
    unsigned char mem[M] = {0};
    unsigned a, last = 0, v;
    char in[256], *p, *t;
    int n;

    puts("========================================\n"
         "   Operating System Emulator in C\n"
         "========================================\n"
         "Command Format:\n"
         "  [ADDR].       -> View memory contents (Inspection)\n"
         "  [ADDR]:[DATA] -> Write bytes to memory (Modify)\n"
         "  [ADDR]R       -> Run the program from the address\n"
         "  EXIT          -> Exit the program\n");

    while (printf("\\ "), fgets(in, sizeof in, stdin)) {
        in[strcspn(in, "\r\n")] = 0;
        if (!(n = strlen(in))) continue;
        if (!strcasecmp(in, "EXIT")) break;

        if (toupper(in[n - 1]) == 'R') {                 /* Run */
            in[n - 1] = 0;
            if (sscanf(in, "%x", &a) == 1) {
                printf("--> Executing execution from address 0x%04X...\n"
                       "[CPU Simulation] Bytes at location: ", a);
                for (int i = 0; i < 4; i++) printf("%02X ", mem[(a + i) % M]);
                puts("");
            } else puts("Error: Incorrect address format");

        } else if ((p = strchr(in, '.'))) {              /* Inspect */
            *p = 0;
            if (sscanf(in, "%x", &a) != 1) a = last;
            printf("%04X: ", a);
            for (int i = 0; i < 8; i++) printf("%02X ", mem[(a + i) % M]);
            puts("");
            last = (a + 8) % M;

        } else if ((p = strchr(in, ':'))) {              /* Modify */
            *p = 0;
            if (sscanf(in, "%x", &a) != 1) a = last;
            for (t = strtok(p + 1, " \t"); t; t = strtok(0, " \t"))
                if (sscanf(t, "%x", &v) == 1) mem[a++ % M] = v;
            last = a % M;

        } else puts("Error: Command not recognized");
    }
    return 0;
}
