#include<iostream>
#include<fstream>
using namespace std;
#define SIZE 1024

int main(){

    //file 1 to write data and cloneFile to copy file 1 content into it
    ofstream ofs("file1.txt"),ofs2("cloneFile.txt");
    char buffer[SIZE];
    int noOfLines=0,noOfWords=0,noOfChars=0,i=0;

    cout<<"Enter data (to end data enter '$' keyword) : \n";
    cin.getline(buffer,SIZE,'$');

    ofs<<buffer;
    ofs.close();

    ifstream ifs("file1.txt");

    while(!ifs.eof()){
        ifs.getline(buffer,SIZE);
        ofs2<<buffer<<"\n"; // pasting in clone file
        while(buffer[i]!='\0'){
            //to check space if then incr word
            if((buffer[i]==' ' && buffer[i+1]!=' ') || buffer[i]==',' ){
				noOfWords+=1;
			}
            noOfChars+=1;
            i++;
        }
        //incr by 1 becoz of new line 
        noOfLines+=1;
        noOfChars+=1;
        noOfWords+=1;
        i=0;
    }
    cout<<"\n------------------------------------------------------------------------------------------\n";
    cout<<"Data Written successfully in 'file1.txt'\n";
    cout<<"------------------------------------------------------------------------------------------\n";
    cout<<"No. of chars : "<<noOfChars<<" No. of words : "<<noOfWords<<" No. of lines : "<<noOfLines<<endl;
    cout<<"------------------------------------------------------------------------------------------\n";
	cout<<"data copied successfully in 'cloneFile.txt' \n";
    //closing streams
    ifs.close();
    ofs2.close();

    return 0;
}
