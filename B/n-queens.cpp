#include<iostream>
using namespace std;
#define SIZE 4
int count=4,currentRow,currentCol,k;
int board[SIZE][SIZE];
struct{
	int r,c;
}q[4];

bool checkRow(int r=0){
	for(int i=r;i<SIZE;i++){
		if(board[i][currentCol]==1){
			return true;
		}
	}
	return false;
}

bool checkDiagonalUp(int x,int y){
	int i=0;
	for(i=1;i<=y;i++){
		if(board[x-i][y-i]==1){
			return true;
		}
	}
	return false;
}

bool checkDiagonalDown(int x,int y){
        int i=0;
        for(i=1;i<=y;i++){
                if(board[x+i][y-i]==1){
                        return true;
                }
        }
        return false;
}

bool checkDiagonal(int x,int y){
	if(!checkDiagonalUp(x,y)){
		if(!checkDiagonalDown(x,y)){
			return false;
		}
	}
	return true;
}

void placeQueens(int row,int col){
	if(count==0 ){
		return;
	}
	else{
		if(col<=0 || col>=SIZE)
			return;

		int i=row;
		while(i<SIZE){
			if(!checkRow(i) && !checkDiagonal(col,i)){
				currentCol=col,currentRow=i;
				board[i][col]=1;
				count-=1;
				cout<<"Current Row : "<<currentRow<<" Current col : "<<currentCol<<endl;
				break;
			}
			i++;
		}
		if(i==SIZE){
			cout<<"False : "<<row<<" "<<col<<endl;
			count+=1;
			placeQueens(count-1,col-1);
		}
		else{
			placeQueens(row,col+1);
		}
	}
}

int main(){

	int i=0,j=0,k=0;

	i=0,j=0;
	//start here
	board[i][j]=1;
	count-=1;
	placeQueens(i,j+1);
	return 0;
}
