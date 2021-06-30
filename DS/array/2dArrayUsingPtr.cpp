#include<bits/stdc++.h>
using namespace std;

void access2d(int **mat){
    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++)
    //         printf("%d\n",*(mat+(i*4)+j));

    //     printf("\n");
    // }

    
    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++)
    //         printf("%d\n",*(mat+j)+i);

    //     printf("\n");
    // }

    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            printf("%d\n",mat[j]+i);

        printf("\n");
    }
}


int main(){

    int n=4;
    int data[][4]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
        };
    access2d((int**)data);
    return 0;
}