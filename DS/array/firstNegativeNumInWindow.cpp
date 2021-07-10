//sliding window
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void firstNegNumInWin(vector<int> arr, int k)
{

    //to store -ne no of window
    queue<int> q;
    //two pointers start and end
    int start = 0, end = 0;

    while (end < arr.size())
    {

        //if -ne then insert to q
        if (arr[end] < 0)
            q.push(arr[end]);

        //if subarray size encountered then
        if ((end - start + 1) == k)
        {

            //if list is empty then no -ne num in window
            //else start==q.front then remove since we crossed that element it is no more required
            if (q.empty())
                cout << "0\n";
            
            cout << q.front() << "\n";

            if (arr[start] == q.front())
                q.pop();

            start++;
        }

        end++;
    }
}

int main(int argc, char const *argv[])
{
    cout << "Input : \n";
    cout << "First line will contain 2 integer N - size of array and K - size of window \n";
    cout << "Second line will contain N elements of array\n";

    int N, K;
    cin >> N >> K;
    vector<int> arr(N);

    for (int i = 0; i < N; i++)
        cin >> arr[i];

    firstNegNumInWin(arr, K);

    return 0;
}
