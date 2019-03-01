#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
    int input;
    scanf("%d", &input);
    for(int i = 0; i < input; i++)
    {
        int inp1, inp2, x, y, s;
        scanf("%d%d", &inp2, &inp1);
        int matrix[inp2+1][inp2+1], arr[inp2+1], indArr, v[inp2+1], L[inp2+1], indL;
        for(int j = 1; j <= inp2; j++)
        {
            arr[j] = 0;
            v[j] = 0;
            L[j] = 0;
            for(int k = 1; k <= inp2; k++)
            {
                matrix[j][k] = 0;
            }
        }
        for(int j = 0; j < inp1; j++)
        {
            scanf("%d%d", &x, &y);
            matrix[x][y] = 1;
            matrix[y][x] = 1;
        }
        scanf("%d", &s);
        arr[1] = s;
        v[s] = 1;
        L[1] = 0;
        indL = 1;
        indArr = 1;
        for(int j = 1; j < indArr + 1; j++)
        {
            for(int k = 1; k <= inp2; k++)
            {
                if(matrix[arr[j]][k] == 1 && v[k]==0)
                {
                    indArr++;
                    arr[indArr] = k;
                    v[k] = 1;
                    indL++;
                    L[indL] = L[j] + 1;

                }
            }
        }
        int len[inp2+1];
        for(int j = 1; j < inp2 + 1; j++)
        {
            len[j] = -1;
            for(int k = 1; k <= indArr; k++)
            {
                if(j == arr[k])
                {
                    len[j] = 6*L[k];
                }
            }
        }
        for(int j = 1; j <= inp2; j++)
        {
            if(j != s)
            {
                cout << len[j] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
