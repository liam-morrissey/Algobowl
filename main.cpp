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


int main(int argc, char* argv[]){
	vector<string> filenames; 
        int thresh; 
        if(argc>1){ 
                thresh = stoi(argv[1]); 
                for(int i=2; i<argc; i++){ 
                        filenames.push_back(argv[i]); 
                } 
        } 
        else{//defualt input 
        filenames.push_back("Input.txt"); 
        thresh = 2000; 
        }
	
	for( string filename : filenames){
		cout<<"Working with: "<<filename<<endl;
		vector<Point> points;
		load(filename,points);//load the points up
		cout<<"SIZE IS: " << points.size() <<" First Val: "<<points[0].toString()<<endl;
		vector<vector<Point>> bestbin;
		int smalldist = 6001;
		while(smalldist>thresh){
				vector<vector<Point>> bins = binmerge(points);
				int dist = verify(bins);
				if(dist<smalldist){
					smalldist = dist;
					bestbin = bins;
				}	
			
		}
	
	
		print(bestbin,smalldist,filename);
		cout<<endl;
	}

	return 0;
}
