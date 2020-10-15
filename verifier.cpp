#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include<algorithm>
#include<cmath>
#include <iostream>
#include<ctime>
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
		
		else if (val == 1){
			return this->y;
		}

		else{
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

int distance(const Point & a, const Point & b){
	return abs(a.x - b.x) + abs(a.y-b.y) + abs(a.z-b.z);
}

void split(int rangedavg, int dim, vector<Point>& initial, vector<Point> &split){
	int c=1;
   for( int i= 0; i< initial.size(); i++ ){
	 	auto it = initial.begin()+i;

 	 if(it->get(dim)>rangedavg) {
			split.push_back(*it);

			//auto deleteMe = i;
			//i++;

			
			initial.erase(it);
			i--;
		}

   	c++;
   }
   }




int verify(vector<vector<Point>> sectors){
	int maxDist=0;
	int count=1;
	for(vector<Point> x : sectors){
		int interDist = 0;
		for(int i = 0; i<x.size()-1; i++){
			for(int j = i+1; j<x.size(); j++){
				int dist = distance(x.at(i),x.at(j));
				if (dist>maxDist) maxDist = dist;
				if (dist>interDist) interDist =dist;
			}
		}
		count++;
	}
	return maxDist;
}

void sortbins( vector<Point> &points,int dir){
	
	if(dir== 0){
		sort(points.begin(),points.end(),&xComp);
	}
	if(dir== 1){
		sort(points.begin(),points.end(),&yComp);
	}
	if(dir== 2){
		sort(points.begin(),points.end(),&zComp);
	}
}


vector<vector<Point>> binmerge(vector<Point> p){
	srand(time(0));
	vector<vector<Point>> sectors;
	sectors.push_back(p);
	int largestSector=0;
	for(int i =0; sectors.size()<k; i++){//do this until k sectors

		for(int j=0; j<sectors.size(); j++){
			if(sectors.at(j).size()>sectors.at(largestSector).size()) largestSector = j;
		}
		int dim = (rand())%3;
		sortbins(sectors.at(largestSector), dim);
		vector<Point> temp;
		int avg = (sectors.at(largestSector).front().get(dim)+sectors.at(largestSector).back().get(dim))/2; // get the range avg for dim
		split(avg, dim, sectors.at(largestSector), temp);
		if(temp.size()>0)
		sectors.push_back(temp);
	}
	return sectors;
}

void print(vector<vector<Point>> points, int dist,string filename){
   fstream f;

   f.open(filename.substr(0,filename.find(".txt"))+"_out.txt",ios::out);
   if(f.is_open()){
	f << to_string(dist)<< '\n';	
	for(auto it = points.begin(); it != points.end(); it++){

		for(auto itt = it->begin(); itt != it->end(); itt++ ){
			f<<to_string(itt->index);
			auto tmp = (itt+1);
			if(tmp != it->end()){//the next is not the end
				f<<' ';
			}
		}
		f<<'\n';

	}
   }
   f.close();
}

bool verifyBin(string output, vector<Point> &points){
fstream f;
int dist;
   f.open(output,ios::in);
   if(f.is_open()){
	string line;
	getline(f,line);
	dist = stoi(line);//get n
	vector<vector<Point>> bins;
	vector<Point> temp;
	while(getline(f,line)){
		stringstream parse(line);
		while(!parse.eof()){
		Point tmp;
	       	int id;
		parse >> id;
		if(id>n) return false;
		temp.push_back(points.at(id-1));
		}
		bins.push_back(temp);
		temp.clear();
	}
	return dist == verify(bins);
   }
   return false;
}

int main(int argc, char* argv[]){
	string inputfilename = "inputs/input_group217.txt"; 
	vector<string> outputfilenames;
        if(argc>1){ 
                for(int i=1; i<argc; i++){
		outputfilenames.push_back(argv[i]);
                } 
        } 
        vector<Point> points;
	load(inputfilename, points);
	for(int i = 0; i<outputfilenames.size(); i++){
	//First, open up the input file
	//second, load teams best dist and bins
	bool valid = verifyBin(outputfilenames.at(i), points);
	string temp = outputfilenames.at(i);
	cout<<"Team "<<temp.substr(temp.find("2"), 3)<<" "<<valid<<endl;
	}

	return 0;
}
