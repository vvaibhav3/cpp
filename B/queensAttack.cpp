#include <iostream>
#include <iomanip>
using namespace std;

#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PINK    "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[4;37m"  //with underline
#define RESET   "\033[0m"

#define SIZE 8
int count, k;
int board[SIZE][SIZE];
struct
{
    int r, c;
} q[SIZE];

bool checkRow(int r, int col)
{
    for (int i = 0; i < col; i++)
    {
        if (q[i].r == r)
        {
            return true;
        }
    }
    return false;
}

bool checkDiagonalUp(int r, int c)
{
    int i = 0;
    for (i = 0; i <= r && (r-i)>=0; i++)
    {
        if (board[r - i][c - i] == 1)
        {
            return true;
        }
    }
    return false;
}

bool checkDiagonalDown(int r, int c)
{
    int i = 0;
    for (i = 0; i <= c && (r+i)<SIZE; i++)
    {
        if (board[r + i][c - i] == 1)
        {
            return true;
        }
    }
    return false;
}

bool checkDiagonal(int r, int c)
{
    if (!checkDiagonalUp(r, c))
    {
        if (!checkDiagonalDown(r, c))
        {
            // cout<<"\nPossible : Row : "<<r<<" Col : "<<c<<endl;
            return false;
        }
    }
    return true;
}

void showData()
{
    cout <<GREEN<<"\n";

    for (int i = 0; i < SIZE; i++ )
    {   

        for (int j = 0; j < SIZE; j++ )
        {  
            if (board[i][j] == 1)
            {
                cout <<WHITE<<" Q "<<RESET<<GREEN;
            }
            else
                cout << " "<<board[i][j]<<" ";
        }
        cout << endl;
    }
    cout <<RESET<<"\n";
}


bool placeQueens1(int row, int col)
{

    // cout<<"COl : "<<col<<endl;
    if (col >= SIZE)
    {
        return true;
    }
    else
    {
        int i = row;
        while (i < SIZE)
        {
            if (!checkRow(i, col) && !checkDiagonal(i, col))
            {
                board[i][col] = 1;
                cout<<"Col : "<<col<<endl;
                showData();
                q[count].r = i, q[count].c = col;
                count += 1;
                if (count == SIZE)
                {
                    k += 1;
                    cout << "Soln No : " << k << endl;
                    showData();
                }
                if (placeQueens1(0, col + 1))
                {
                    cout <<RED<< "row : " << i << " col : " << col <<RESET<< endl;
                    return true;
                }
                count -= 1;
                board[i][col] = 0;
            }
            i++;
        }
    }
    // cout<<"\n\033[1;31m\a<--------------------->Backtracking<--------------------->\033[0m\n";
    return false;
}

bool placeQueens(int row, int col)
{

    // cout<<"COl : "<<col<<endl;
    if (col > SIZE)
    {
        return true;
    }
    else
    {
        int i = row;
        while (i < SIZE)
        {
            if (!checkRow(i, col) && !checkDiagonal(i, col))
            {
                board[i][col] = 1;
                // showData();
                q[count].r = i, q[count].c = col;
                count += 1;
                if (count == SIZE)
                {
                    k += 1;
                    cout << "Soln No : " << k << endl;
                    showData();
                }
                if (placeQueens(0, col + 1))
                {
                    cout << "row : " << i << " col : " << col << endl;
                    return true;
                }
                count -= 1;
                board[i][col] = 0;
            }
            i++;
        }
    }
    // cout<<"\n\033[1;31m\a<--------------------->Backtracking<--------------------->\033[0m\n";
    return false;
}

int main()
{
    int ch;
    cout<<YELLOW<<endl;
    cout<<"\\\\\\\\\\--------------------------MENU----------------------------//////\n\n";   
    cout<<"######################## 1.Show single iterative soln ##############\n";
    cout<<"######################## 2.Show all posible soln ###################\n";
    cout<<"######################## 3.Exit ####################################\n\n";
    cout<<"choice :- "<<RESET;
    cin>>ch;
    switch(ch){
        case 1: placeQueens1(0, 0);
                break;
        case 2: placeQueens(0, 0);
                cout << "Soln :" << k << endl;
                break;
        default :
                return 0;
    }
    return 0;
}
