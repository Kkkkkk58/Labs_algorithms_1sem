#include <stdio.h>

int main(){
    int a, b;
    FILE *fin, *fout;
    fin = fopen("aplusb.in", "r");
    fout = fopen("aplusb.out", "w");
    fscanf(fin, "%d %d", &a, &b);
    fprintf(fout, "%d", a + b);
    fclose(fin);
    fclose(fout);
    return 0;
}