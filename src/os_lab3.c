#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file_reverse(FILE *fp, FILE *fwp) {
    int i, size, start, loop, counter;
    char *buffer;
    char line[256];

    start = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    buffer = malloc((size + 1) * sizeof (char));

    for (i = 0; i < size; i++) {
        fseek(fp, size - 1 - i, SEEK_SET);
        buffer[i] = fgetc(fp);

        if (buffer[i] == 10) {
            if (i != 0) {
                counter = 0;
                for (loop = i; loop > start; loop--) {
                    if ((counter == 0) && (buffer[loop] == 10)) {
                        continue;
                    }
                    line[counter] = buffer[loop];
                    counter++;
                }
                line[counter] = 0;
                start = i;
                fprintf(fwp, "%s\n", line);
            }
        }
    }

    if (i > start) {
        counter = 0;
        for (loop = i; loop > start; loop--) {
            if ((counter == 0) && ((buffer[loop] == 10) || (buffer[loop] == 0))) {
                continue;
            }
            line[counter] = buffer[loop];
            counter++;
        }
        line[counter] = 0;
        fprintf(fwp, "%s\n", line);
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: os_lab3 [originalfile] [modifiedfile]\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *fwp = fopen(argv[2], "ab+");
    read_file_reverse(fp, fwp);
    fclose(fp);
    fclose(fwp);
    return 0;
}
