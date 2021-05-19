#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define lli long long int
string temp = "0000000000";

lli largeMult(string A, string B)
{

    A.insert(0, temp, 0, A.size() % 2);
    B.insert(0, temp, 0, B.size() % 2);

    int m = A.size() / 2;

    string a1, a2, b1, b2;
    a1.assign(A, 0, m);
    a2.assign(A, m, m);
    b1.assign(B, 0, m);
    b2.assign(B, m, m);

    cout << "N/2 : " << m << endl;
    cout << "a1 : " << a1 << " a2 : " << a2 << endl;
    cout << "b1 : " << b1 << " b2 : " << b2 << endl;

    if (m == 1)
    {
        int x1 = stoi(a1), x2 = stoi(a2);
        int y1 = stoi(b1), y2 = stoi(b2);

        lli t1 = x1 * y2, t2 = y1 * x2;
        lli c1 = x1 * y1, c2 = t1 + t2, c3 = x2 * y2;

        // cout<<"Result : ";
        return ((c1 * pow(10, m * 2)) + (c2 * pow(10, m)) + c3);
    }

    return (largeMult(a1, b1) * pow(10, m * 2) + (largeMult(a1, b2) + largeMult(b1, a2)) * pow(10, m) + (largeMult(a2, b2)));
}

//assuming no is 4 to 6 digit for simplicity
int main(int argc, char const *argv[])
{
    cout << "Enter No's For Multiplication : " << endl;
    string a, b;
    cout << "Enter A : " << endl;
    cin >> a;
    cout << "Enter B : " << endl;
    cin >> b;
    int m = a.size() / 2;
    // // assuming 4 digit
    // string a1,a2,b1,b2;
    // a1.assign(a,0,2);
    // a2.assign(a,2,2);
    // b1.assign(b,0,2);
    // b2.assign(b,2,2);

    // cout<<"N/2 : "<<m<<endl;
    // cout<<"a1 : "<<a1<<" a2 : "<<a2<<endl;
    // cout<<"b1 : "<<b1<<" b2 : "<<b2<<endl;

    // int x1=stoi(a1),x2=stoi(a2);
    // int y1=stoi(b1),y2=stoi(b2);

    // lli t1=x1*y2,t2=y1*x2;
    // lli c1=x1*y1,c2=t1+t2,c3=x2*y2;

    // cout<<"Result : ";
    // cout<<(lli)((c1*pow(10,m*2))+(c2*pow(10,m))+c3)<<endl;

    if (a.size() > b.size())
    {
        int z = a.size() - b.size();
        b.insert(0, temp, 0, z);
    }
    else if (a.size() < b.size())
    {
        int z = b.size() - a.size();
        a.insert(0, temp, 0, z);
    }

    cout << "A : " << a << " B : " << b << endl;

    cout << largeMult(a, b) << endl;

    return 0;
}
