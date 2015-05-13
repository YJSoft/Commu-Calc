int compare_san(int stat);
int compare_stat(int stat);
int random_val(int min,int max);
int X_prob(double x);
int init_prob(double x);
void printHelp();

typedef struct stat_struct{
        int atk;
        int def;
        int san;
        int dice;
} stat;
