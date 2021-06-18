
#include<iostream>
using namespace std;
int key;

int binarySearch(int arr[], int l, int r)
{

    if(l>r)
        return 0;

    int mid = (l + r) / 2;

    if (arr[mid] == key)
        return mid+1;

    if (key > arr[mid])
        binarySearch(arr, mid + 1, r);
    else
        binarySearch(arr, l, mid - 1);
}

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter Size : ", cin >> n;
    int data[n];
    cout << "Enter elements of array in sorted manner : \n";
    for (int i = 0; i < n; i++)
        cin >> data[i];

    cout << "Enter element to find : ", cin >> key;

    int pos=binarySearch(data,0,n-1);
    if(!pos)
        cout<<"Element not found.. "<<endl;
    else
        cout<<"Element found at position : "<<pos<<endl;

    return 0;
}
