#include <iostream>
#include <vector>
using namespace std;

int Min, Max;
void setMinMax(int list[], int l, int r)
{
    if (Max < list[l])
        Max = list[l];

    if (Min > list[l])
        Min = list[l];

    if (Max < list[r])
        Max = list[r];

    if (Min > list[r])
        Min = list[r];
}
void divide(int list[], int l, int r)
{

    int mid;

    //if single
    if (l == r)
    {
        setMinMax(list, l, r);
        cout << "Min : " << Min << endl
             << "Max : " << Max <<"\n\n";
    }
    //if size==2
    else if (r - 1 == l)
    {
        //check
        setMinMax(list, l, r);
        cout << "Min : " << Min << endl
             << "Max : " << Max <<"\n\n";
    }
    else
    {
        mid = (r + l) / 2;
        //first
        divide(list, l, mid);
        //second
        divide(list, mid + 1, r);
    }
}

int main(int argc, char const *argv[])
{
    int N;
    // cout<<"\n\n\n\033[1;32m--------------MAX-MIN OF LIST----------------\033[0m\n\n";
    cout << "Enter list size : ", cin >> N;

    int arr[N];

    cout << "\nEnter elements : \n";
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    Min = arr[0];
    Max = arr[0];

    divide(arr, 0, N - 1);
    cout << "Result : " << endl;
    cout << "Min : " << Min << endl
         << "Max : " << Max << endl;

    return 0;
}