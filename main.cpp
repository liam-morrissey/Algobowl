#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include<algorithm>

#include <iostream>
using namespace std;

int n,k;//global Variables

struct Point{
	int x,y,z;
	int index;
	Point(){}
	Point(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
	}
	string toString(){
		string tmp = to_string(this->x) + ' ' + to_string(this->y) + ' ' + to_string(this->z);
		return tmp;
	}
	int get(int val){
		
		if (val ==0){
			return this->x;
		}
		
		if (val == 1){
			return this->y;
		}

		if (val == 2){
			return this->z;
		}
	}
};

void load(string fname, vector<Point> &points){
   fstream f;
   f.open(fname,ios::in);
   if(f.is_open()){
	string line;
	
	getline(f,line);
	n = stoi(line);//get n
	
	getline(f,line);
	k = stoi(line);// get k
	
	int c=1;
	while(getline(f,line)){
		stringstream parse(line);
		Point tmp;
	       	int cord;
		parse >> cord;
		tmp.x = cord;
		
		parse >> cord;
		tmp.y = cord;
		
		parse >> cord;
		tmp.z = cord;
		tmp.index = c;
		points.push_back(tmp);//add the point and ints index to the map
		c++;
	}
   }
}




bool xComp(const Point & a, const Point& b) {
   return a.x < b.x;
}
bool yComp(const Point & a, const Point& b) {
   return a.y < b.y;
}
bool zComp(const Point & a, const Point& b) {
   return a.z < b.z;
}



int verify(int** finalsort, vector<Point> points){
return NULL;
}

int* mkbins(const vector<Point> points,int dir){
	vector<Point> tmp = points;
	if(dir== 0){
		sort(tmp.begin(),tmp.end(),&xComp);
	}
	if(dir== 1){
		sort(tmp.begin(),tmp.end(),&yComp);
	}
	if(dir== 2){
		sort(tmp.begin(),tmp.end(),&zComp);
	}
	
	int* arr = new int[1000];//intilize an array
	
	int c =0;
	for(auto it = tmp.begin(); it !=tmp.end(); it++){
		arr[c] = it->index;
		c++;
	}
	arr[n] = 0;//the null of the array
	return arr;	
}


int** binmerge(int** X, int** Y, int** Z){
return NULL;
}

void print(int ** finalsort, int dist){
   fstream f;
   f.open("output.txt",ios::out);
   if(f.is_open()){
	f << to_string(dist)<< '\n';	
	for(int i = 0; i < 2; i ++){
		int *p = finalsort[i];//pointer to an array
		for(int j =0; j < n-k; j++){
			int tmp = p[j];//the value
			//cout<<"Tmp is: "<<tmp<<endl;
			f<<to_string(tmp);
			if(p[j+1] == 0){//the next value is 0, that means we have reached the end for this array
				break;
			}
			f<<' ';
		}
		f<<'\n';

	}
   }
   f.close();
}


int main(int argc, char* argv[]){
	string filename = "Input.txt";
	if(argc>1) filename = argv[1];

	vector<Point> points;
	load(filename,points);//load the points up
	cout<<"SIZE IS: " << points.size() <<" First Val: "<<points[0].toString()<<endl;
	
	int *Xbins = mkbins(points,0);
		
	int* Ybins = mkbins(points,1); //O(nlogn) uses quick sort

	int* Zbins = mkbins(points,2); //O(nlogn)
	
	//int** finalsort = binmerge(Xbins,Ybins,Zbins);

	//int dist = verify(finalsort);
	//print(finalsort,dist);
	return 0;
}
