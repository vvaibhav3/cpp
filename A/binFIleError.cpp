#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// string will give you error always go through char array
struct data{
	string lable,mnemonic,op1,op2;
};

ostream &operator<<(ostream &stream,struct data s1){
	stream<<s1.lable<<" "<<s1.mnemonic<<" "<<s1.op1<<" "<<s1.op2<<"\n";
	return stream;
}

int main(){
	struct data s1;
	char ch='y';
	ofstream ofs;
	ofs.open("prgm1.dat",ios::out | ios::binary);
	//system("0A);
	cout<<"\n---------->Instruction <--------------- \n\n";
	cout<<"\a1.Add ('-') for empty field \n2.Format of statement is : <lable> <mnemonic> <op1> <op2> \n3.To terminate enter keyword ('~') on new line\n\n";
	cout<<"Write your code >>>> \n";
	while(1){
		cin>>s1.lable;
		ch=s1.lable[0];
		if(ch=='~')
			break;
		cin>>s1.mnemonic>>s1.op1>>s1.op2;
		ofs.write((char *) &s1,sizeof(struct data));
	}
	ofs.close();
	if(!ofs.good())
		cout<<"error occured in writing.......\n";

	ifstream ifs;
	ifs.open("prgm1.dat",ios::in | ios::binary);

	while(1){
		ifs.read((char*)&s1,sizeof(struct data));
		if(ifs)
			cout<<s1;
		else
			break;
	}
	ifs.close();

	if(!ifs.good() && !ifs.bad())
		cout<<"error occured in reading.......\n";

return 0;

}
