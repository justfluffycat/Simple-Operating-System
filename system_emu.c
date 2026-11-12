#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MEM_SIZE 65536

int main() {
    unsigned char memory[MEM_SIZE] = {0};
    unsigned int last_addr = 0;
    char input[256];

    printf("========================================\n");
    printf("   Operating System Emulator in C\n");
    printf("========================================\n");
    printf("Command Format:\n");
    printf("  [ADDR].       -> View memory contents (Inspection)\n");
    printf("  [ADDR]:[DATA] -> Write bytes to memory (Modify)\n");
    printf("  [ADDR]R       -> Run the program from the address\n");
    printf("  EXIT          -> Exit the program\n\n");

    while (1) {
        printf("\\ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        
        input[strcspn(input, "\r\n")] = 0;
        if (strlen(input) == 0) continue;
        if (strcasecmp(input, "EXIT") == 0) break;

        int len = strlen(input);

        if (toupper(input[len - 1]) == 'R') {
            input[len - 1] = 0;
            unsigned int addr;
            if (sscanf(input, "%x", &addr) == 1) {
                printf("--> Executing execution from address 0x%04X...\n", addr);
                printf("[CPU Simulation] Bytes at location: ");
                for(int i = 0; i < 4; i++) {
                    printf("%02X ", memory[addr + i]);
                }
                printf("\n");
            } else {
                printf("Error: Incorrect address format\n");
            }
            continue;
        }

        char *dot = strchr(input, '.');
        if (dot != NULL) {
            *dot = 0;
            unsigned int addr;
            if (sscanf(input, "%x", &addr) == 1) {
                last_addr = addr;
            } else {
                addr = last_addr;
            }
            
            printf("%04X: ", addr);
            for (int i = 0; i < 8; i++) {
                printf("%02X ", memory[(addr + i) % MEM_SIZE]);
            }
            printf("\n");
            last_addr = (addr + 8) % MEM_SIZE;
            continue;
        }

        char *colon = strchr(input, ':');
        if (colon != NULL) {
            *colon = 0;
            unsigned int addr;
            if (sscanf(input, "%x", &addr) == 1) {
                last_addr = addr;
            } else {
                addr = last_addr;
            }

            char *token = strtok(colon + 1, " \t");
            while (token != NULL) {
                unsigned int val;
                if (sscanf(token, "%x", &val) == 1) {
                    memory[addr % MEM_SIZE] = (unsigned char)val;
                    addr++;
                }
                token = strtok(NULL, " \t");
            }
            last_addr = addr % MEM_SIZE;
            continue;
        }

        printf("Error: Command not recognized\n");
    }

    return 0;
}
