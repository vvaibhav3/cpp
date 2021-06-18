#include <iostream>
#include <vector>
using namespace std;
struct item_format{
	int profit,weight;
	float ratio;
};
void showRatio(vector<item_format*> &v1);

void sortRatio(vector<item_format*> &v1){

	item_format *p1=NULL,*p2=NULL;

	cout<<"sorting according ratio...\n";

	for(int i=0;i<v1.size()-1;i++){
		//p1=v1[i];
		//cout<<"1\n";
		for(int j=0;j<v1.size()-1;j++){
			p1=v1[j];
			p2=v1[j+1];
                        //cout<<p1->ratio<<"  "<<p2->ratio<<"\n";
			//cout<<"2\n";
			if((p1->ratio)<(p2->ratio)){
				v1[j]=p2;
				v1[j+1]=p1;
				//cout<<v1[i]->ratio<<"  "<<v1[j]->ratio<<"\n";
			}
		}
		showRatio(v1);
	}
}

void showRatio(vector<item_format*> &v1){

        vector<item_format*>::iterator s=v1.begin();
	while(s!=v1.end()){
	        cout<<(*s)->ratio<<"\t";
		s++;
	}
	cout<<"\n";
}

void calculateRatio(vector<item_format*> &v1){

	vector<item_format*>::iterator s=v1.begin();
	while(s!=v1.end()){
		(*s)->ratio=(float)(*s)->profit/(float)(*s)->weight;
		s++;
	}
}

float findProfit(vector<item_format*> v1,float total_weight){

	float total_profit=0,cur_weight=0;
	vector<item_format*>::iterator s=v1.begin();

	while(s!=v1.end()){

		if(cur_weight<total_weight){
			cur_weight+=(*s)->weight;
			total_profit+=(*s)->profit;
		}
		s++;
	}

	float temp=total_weight-cur_weight;
	while(s!=v1.end() && temp>0){
		total_profit+=(((*s)->profit)*(temp/(*s)->weight));
		temp=total_weight-cur_weight;
		s++;
	}
	return total_profit;
}

int main(){

int w,n;
cout<<"Enter no of items : ";
cin>>n;

cout<<"Enter total weight : ";
cin>>w;

vector<struct item_format*> items;
struct item_format p[n];

for(int i=0;i<n;i++){

	cout<<i<<"--->"<<endl;
	cout<<"Enter weight : ";
	cin>>p[i].weight;
	cout<<"Enter profit : ";
	cin>>p[i].profit;

	items.push_back(&p[i]);
}

calculateRatio(items);

sortRatio(items);

for(int i=0;i<n;i++){

	cout<<i<<" : "<<items[i]->ratio<<"\n";
}

cout<<"Total-profit : "<<findProfit(items,(float)w)<<"\n";

return 0;

}
