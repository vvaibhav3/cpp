#include<iostream>
#include<fstream>
#include<iomanip>
#define SIZE 1024
using namespace std;

struct data{
	char lable[SIZE],mnemonic[SIZE],op1[SIZE],op2[SIZE];
};

ostream &operator<<(ostream &stream,struct data s1){
	stream<<s1.lable<<" "<<s1.mnemonic<<" "<<s1.op1<<" "<<s1.op2<<"\n";
	return stream;
}

int main(){

    struct data s1;
	
	fstream ifs;
	ifs.open("./prgm1.dat",ios::in | ios::binary);

    if(!ifs)
        return 0;

    // ifs.seekg(ios::beg);    
	while(1){
        ifs.read((char*)&s1,sizeof(struct data));
        
		if(ifs)
			cout<<s1;
		else
			break;
	}
    ifs.close();


return 0;

}
