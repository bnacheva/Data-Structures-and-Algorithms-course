#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void readArr(short int n, short int arr[])
{
    for (short int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}

int main()
{
    short int tests;
    cin >> tests;
    for (short int i = 0; i < tests; i++)
    {
        short int n;
        cin >> n;
        short int arr[n];
        readArr(n, arr);
        sort(arr, arr + n);
        int sum = 0;
        if (n == 1)
        {
            cout << arr[0] << endl;
        }
        else
        {
            for (short int j = 0; j < n - 1; j += 2)
            {
                if (arr[j] <= 0 && arr[j + 1] <= 0)
                {
                    sum += arr[j] * arr[j + 1];
                }
                else if (arr[j] <= 0 && arr[j + 1] > 0)
                {
                    sum += arr[j];
                }
                if (j + 2 == n - 1 && arr[j + 2] <= 0)
                {
                    sum += arr[j + 2];
                }
            }
            for (short int z = n - 1; z > 0; z -= 2)
            {
                if (arr[z] > 0 && arr[z - 1] > 0)
                {
                    sum += arr[z] * arr[z - 1];
                }
                else if (arr[z] > 0 && arr[z - 1] <= 0)
                {
                    sum += arr[z];
                }
                if (z - 2 == 0 && arr[z - 2] > 0)
                {
                    sum += arr[z - 2];
                }
            }
            cout << sum << endl;
            sum = 0;
        }
    }
    return 0;
}
