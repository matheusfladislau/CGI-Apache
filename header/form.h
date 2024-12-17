#define MAX_SIZE 256

typedef struct pair {
    char name[MAX_SIZE];
    char value[MAX_SIZE];
} PAIR;

void header(char *MYME_type);
void start_page(char *title);
void end_page(void);
