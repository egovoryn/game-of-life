#include "game_of_life.h"

int main() {
    int **c = current_array(), **f = future_array();
    char **d = display_array();
    char space, temp;
    int popul = 1;
    files_import(c);
    display(c, d);
    output(d);
    do {
        input(&space, &temp);
        if (space == ' ' && temp == '\n') {
            logic(c, f, &popul);
            display(c, d);
        }
        output(d);
    } while (popul != 0 && space != 'q');
    printf("Game Over");
    free_array(c, f, d);
    return 0;
}

int **current_array() {  // creating an array of the current state
    int **a = NULL;
    a = (int **)calloc(M, sizeof(int *));
    for (int i = 0; i < M; i++) {
        a[i] = (int *)calloc(N, sizeof(int));
    }
    return a;
}

int **future_array() {  // creating an array of the future state
    int **b = NULL;
    b = (int **)calloc(M, sizeof(int *));
    for (int i = 0; i < M; i++) {
        b[i] = (int *)calloc(N, sizeof(int));
    }
    return b;
}

char **display_array() {  // creating an array of the draw
    char **d = NULL;
    d = (char **)calloc((M - 2), sizeof(char *));
    for (int i = 0; i < M - 2; i++) {
        d[i] = (char *)calloc((N - 2), sizeof(char));
    }
    return d;
}

void free_array(int **cur, int **fut, char **d) {
    for (int i = 0; i < M; i++) {
        free(cur[i]);
    }
    free(cur);

    for (int i = 0; i < M; i++) {
        free(fut[i]);
    }
    free(fut);

    for (int i = 0; i < M - 2; i++) {
        free(d[i]);
    }
    free(d);
}

void buffer(int **cur) {
    cur[0][0] = cur[M - 2][N - 2];  // corners: top left
    cur[0][N - 1] = cur[M - 2][1];  // top right
    cur[M - 1][N - 1] = cur[1][1];  // lower right
    cur[M - 1][0] = cur[1][N - 2];  // lower left

    for (int j = 1; j < N - 1; j++) {  // horizontal borders
        cur[0][j] = cur[M - 2][j];     // top
        cur[M - 1][j] = cur[1][j];     // lower
    }

    for (int i = 1; i < M - 1; i++) {  // vertical borders
        cur[i][0] = cur[i][N - 2];     // left
        cur[i][N - 1] = cur[i][1];     // right
    }
}

void logic(int **cur, int **fut, int *popul) {
    int count;
    buffer(cur);
    for (int i = 1; i < M - 1; i++) {  // future state array calculation
        for (int j = 1; j < N - 1; j++) {
            count = cur[i - 1][j - 1] + cur[i - 1][j] + cur[i - 1][j + 1] +
                    cur[i][j - 1] + cur[i][j + 1] + cur[i + 1][j - 1] +
                    cur[i + 1][j] + cur[i + 1][j + 1];
            if (count == 3) {
                fut[i][j] = 1;
            } else if (count == 2) {
                fut[i][j] = cur[i][j];
            } else {
                fut[i][j] = 0;
            }
        }
    }

    *popul = 0;
    for (int i = 1; i < M - 1; i++) {  // population count
        for (int j = 1; j < N - 1; j++) {
            if (cur[i][j] > fut[i][j]) {
                *popul += cur[i][j] - fut[i][j];
            } else {
                *popul += fut[i][j] - cur[i][j];
            }
        }
    }

    for (int i = 1; i < M - 1; i++) {  // updating the current state array
        for (int j = 1; j < N - 1; j++) {
            cur[i][j] = fut[i][j];
        }
    }
}

void display(int **cur, char **dis) {
    for (int i = 0; i < M - 2; i++) {
        for (int j = 0; j < N - 2; j++) {
            if (cur[i + 1][j + 1])
                dis[i][j] = 'o';
            else
                dis[i][j] = '.';
        }
    }
}

void output(char **dis) {
    printf("\33c\e[3J");
    for (int i = 0; i < M - 2; i++) {
        for (int j = 0; j < N - 2; j++) {
            printf("%c", dis[i][j]);
        }
        printf("\n");
    }
}

char input(char *space, char *temp) {
    fflush(stdin);
    if (scanf("%c%c", space, temp) == 2 && *temp == '\n' && *space == ' ' &&
        *space != '\n') {
        return 1;
    } else if (EOF) {
        fseek(stdin, 0, SEEK_END);
        return 0;
    } else {
        return 0;
    }
    return *space;
}

int files_import(int **cur) {
    FILE *fp;
    char temp;
    int flag_err = 0;
    int version;
    char ch = 0;

    system("clear");
    printf("Enter a number from 1 to 5: ");

    if (scanf("%d%c", &version, &temp) != 2 && temp != '\n') {
        flag_err = 1;
    }

    switch (version) {
        case 1:
            if ((fp = fopen("files/file1.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 2:
            if ((fp = fopen("files/file2.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 3:
            if ((fp = fopen("files/file3.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 4:
            if ((fp = fopen("files/file4.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 5:
            if ((fp = fopen("files/file5.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        default:
            flag_err = 1;
            break;
    }

    if (!flag_err) {
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                if ((ch = fgetc(fp)) == EOF) {
                    flag_err = 1;
                    break;
                }
                if (ch == '\n') {
                    if ((ch = fgetc(fp)) == EOF) {
                        flag_err = 1;
                    }
                    break;
                }
                if (ch == '0') cur[i][j] = 0;
                if (ch == '1') cur[i][j] = 1;
            }
            if (flag_err == 1) break;
        }
        fclose(fp);
    }
    return flag_err;
}
