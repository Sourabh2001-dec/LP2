#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int> &arr)
{
    int size = arr.size();
    for (int i = 0; i < size; i++)
    {   
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}
        
int main()
{

    int option;
    while (option != 2)
    {
        cout << "1. Enter array\n"
             << "2. Exit\n"
             << "Enter option : ";
        cin >> option;

        if (option == 1)
        {
            cout << "\nEnter size of array : ";
            vector<int> arr;
            int len;
            cin >> len;
            cout << "\nEnter space separated elements of array : ";
            while (len--)
            {
                int input;
                cin >> input;
                arr.push_back(input);
            }

            selectionSort(arr);

            cout << "\nSorted array : ";

            for (int i : arr)
            {
                cout << i << " ";
            }
            cout << "\n\n";
        }
    }
}