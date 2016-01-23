#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct dirent **entry_list;
    struct stat attrib;
    int count;
    int i;

    if (argc < 2) {
        printf("Usage: os_lab2 [path]\n");
        return 1;
    }

    int (*datesort)(const struct dirent **file1, const struct dirent **file2);

    int sort(const struct dirent **file1, const struct dirent **file2) {
        struct stat attr1, attr2;
        char fpath1[PATH_MAX], fpath2[PATH_MAX];

        strcpy(fpath1, argv[1]);
        strcat(fpath1, "/");
        strcpy(fpath2, fpath1);
        strcat(fpath1, (*file1)->d_name);
        strcat(fpath2, (*file2)->d_name);

        stat(fpath1, &attr1);
        stat(fpath2, &attr2);

        double diff = difftime(attr1.st_mtime, attr2.st_mtime);
        if (diff < 0)
            return -1;
        if (diff > 0)
            return 1;
        if (diff == 0)
            return 0;
    }

    if (argc < 2) {
        printf("Usage: os_lab2 [path]\n");
        return 1;
    }

    datesort = &sort;
    count = scandir(argv[1], &entry_list, 0, datesort);

    if (count < 0) {
        perror("scandir");
    } else {
        for (i = 0; i < count; i++) {
            struct dirent *file;
            char filepath[PATH_MAX];

            file = entry_list[i];
            strcpy(filepath, argv[1]);
            strcat(filepath, "/");

            if (file->d_type == DT_REG) {
                strcat(filepath, file->d_name);
                stat(filepath, &attrib);
                printf("%s | %s", file->d_name, ctime(&attrib.st_mtime));
                free(file);
            }
        }

        for (i = 0; i < count; i++) {
            struct dirent *dir;
            char dirpath[PATH_MAX];

            dir = entry_list[i];
            strcpy(dirpath, argv[1]);
            strcat(dirpath, "/");

            if (dir->d_type == DT_DIR) {
                strcat(dirpath, dir->d_name);
                stat(dirpath, &attrib);
                printf("<DIR> %s | %s", dir->d_name, ctime(&attrib.st_mtime));
                free(dir);
            }
        }
        free(entry_list);
    }
    return 0;
}
