#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void singleTape(vector<int> prgms)
{
    vector<int>::iterator s, e;
    s = prgms.begin();
    e = prgms.end();
    sort(s, e);

    int size = prgms.size();
    int time[size];
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += prgms[i];
        time[i] = sum;
    }
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total += time[i];
    }
    cout << "\nSum : " << sum << " Total : " << total << endl;
    cout << "\nMRT : " << (float)total / size << endl;
}

void multipleTapes(vector<int> prgms, int noOfTapes)
{
    int size = prgms.size();

    // int tapes[tapes][size/tapes];
    vector<int> tapes[noOfTapes];
    int whichTape = 0, k = 0;
    for (int i = 0; i < size; i++)
    {
        tapes[whichTape].push_back(prgms[i]);
        whichTape = (whichTape + 1) % noOfTapes;
    }

    int sum = 0;
    vector<int> times[noOfTapes];
    for (int i = 0; i < noOfTapes; i++)
    {
        for (int j = 0; j < tapes[i].size(); j++)
        {
            sum += tapes[i][j];
            times[i].push_back(sum);
        }
        sum = 0;
    }

    int total[noOfTapes];

    for (int i = 0; i < noOfTapes; i++)
    {
        total[i] = 0;
    }
    int final = 0;
    for (int i = 0; i < noOfTapes; i++)
    {   
        for (int j = 0; j < times[i].size(); j++)
        {
            total[i] += times[i][j];
        }
        // cout<<"total : "<<total[i]<<endl;
        final += total[i];
    }
    // cout<<"final : "<<final<<endl;
    cout << "\nMRT : " << (float) final / noOfTapes << endl;
}
int main(int argc, char const *argv[])
{
    /* code */
    int n, m;
    cout << "No of prgms : ";
    cin >> n;
    cout << "No of tapes : ";
    cin >> m;
    vector<int> prgms(n);

    cout << "Enter prgms size : \n";
    for (int i = 0; i < n; i++)
        cin >> prgms[i];

    //singleTape(prgms);
    vector<int>::iterator s, e;
    s = prgms.begin();
    e = prgms.end();
    sort(s, e);
    multipleTapes(prgms, m);

    // for(int i=0;i<n;i++)
    //     cout<<prgms[i];

    return 0;
}
