#include <stdio.h>
#include <ctype.h>
#include <string.h>

using namespace std;

int GetClassSymbol(char c) {
    switch (c) {
    case 'c':
        return 0;
    case 'o':
        return 1;
    case '1':
        return 2;
    case '2':
        return 3;
    case '3':
        return 4;
    case 'n':
        return 5;
    case 's':
        return 6;
    case 't':
        return 7;
    case 'v':
    	return 8;
    case 'a':
    	return 9;
    case 'r':
    	return 10;
    default:
        return 11;
    }
}

int main() {
    char S[100]; // the line from the file
    int ST; // automats conditions
    int CL; // class of the symbol
    int BEG; // index of lexems beginning

    int M[10][12] =
    {
        {2, 1, -4, -4, -4, -4, -4, -4, 7, -4, -4, -4},
        {1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 1, 1, 1, -4, -4, -4, 7, -4, -4, -1},
        {2, 1, 1, 1, 1, 4, -4, -4, 7, -4, -4, -1},
        {2, 1, -4, -4, -4, -4, 5, -4, 7, -4, -4, -4},
        {2, 1, -4, -4, -4, -4, -4, 6, 7, -4, -4, -4},
        {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
        {2, 1, -4, -4, -4, -4, -4, -4, 7, 8, -4, -4},
        {2, 1, -4, -4, -4, -4, -4, -4, 7, -4, 9, -4},
        {-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3}
    }; // matrix of movements

    const char* out[] = { "identifier in alphabet", "Word const ", "Word var "};

    FILE* in = fopen("lexer.dat", "r");
    FILE* outFile = fopen("output.txt", "w");

    fprintf(outFile, "%s", "");
    fclose(outFile);

    outFile = fopen("output.txt", "a");

    S[0] = '\0';
    int i = 0;
    ST = 0; // initial condition
    char outStr[] = "";

    while (1) 
    {
        if ((ST == 0) && (S[i] == '\0')) 
        {
            if (fgets(S, 100, in) == NULL) {
                printf("End of work\n");
                fputs("End of work\n", outFile);
                return 0;
            }
            i = 0;
        }
        
        if (ST == 0) {
	    BEG = i;
        }
	if (CL == 7) {
	    BEG = i - 2;
        }


        int CL = GetClassSymbol(S[i]);
        ST = M[ST][CL];// automats movement

        i++;
        if (ST < 0) // checking whether that is the final condition
        {
            // if not other symbol
            if (ST != -4) 
            {
                i--;
                if (-ST - 1 != 0) 
		 {
       	    printf("%s\n", out[-ST - 1]);
       	    fputs(out[-ST - 1], outFile);
       	    puts("");
       	    fprintf(outFile, "%c", '\n');
                }
                else 
                {
       	     for (int j = BEG; j < i; j++)
		     {
                        putchar(S[j]);
                        fprintf(outFile, "%c", S[j]);
          	     }
		     printf("\n");
             	     fprintf(outFile, "%c", '\n');
                }
            }

            // return to the initial condition
            ST = 0;
        }
    }
}
