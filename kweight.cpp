#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include<algorithm>
#include<cmath>
#include <iostream>
#include<cmath>

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
	bool equals(Point p){
		for(int i=0; i<3; i++){
		if(this->get(i) != p.get(i))return false;
		}
		return true;
	}
};

int distance(const Point & a, const Point & b){
	return abs(a.x - b.x) + abs(a.y-b.y) + abs(a.z-b.z);
}

struct cluster{
	vector<Point> points;
	Point middle;
	void combine(cluster c){
		this->points.insert(this->points.end(),c.points.begin(),c.points.end());
		}
	int compareTo(cluster c){
		int max =0;
		for(Point p: this->points){
			for(Point q: c.points)
				if(max< distance(p,q)) max = distance(p,q);
		}
		return max;
	}
	int compareMid(Point p){
		return distance(p, middle);
	}
	Point findMiddle(){
		int x=0;
		int y=0;
		int z=0;
		for(auto it: this->points){
			x+=it.get(0);
			y+=it.get(1);
			z+=it.get(2);
		}
		int size = this->points.size();
		Point avg = Point(x/size,y/size,z/size);
		int closest = 6001;
		Point temp;
		for(Point p : points){
			if(distance(p, avg)<closest){
			closest = distance(p,avg);
			temp = p;
			}
		}
		middle = temp;
		return middle;
	}

	cluster(Point p){
	this->middle = p;
	}
	cluster(){}

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


int verify(vector<cluster> sectors){
	int maxDist=0;
	int count=1;
	for(cluster x : sectors){
		int interDist = 0;
		for(int i = 0; i<x.points.size()-1; i++){
			for(int j = i+1; j<x.points.size(); j++){
				int dist = distance(x.points.at(i),x.points.at(j));
				if (dist>maxDist) maxDist = dist;
				if (dist>interDist) interDist =dist;
			}
		}
		count++;
	}
	return maxDist;
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

void weightedDistribution(vector<cluster>& clust, vector<Point> p){
       	clust.push_back(p.at(rand()%p.size()));
	vector<pair<int,Point>> weight;
	
	while(clust.size()<k){
		int fullweight = 0;
		for(Point pnt: p){
			int dist = 6001;
			for(cluster c : clust){
				if(dist>c.compareMid(pnt)){
					dist = c.compareMid(pnt);
				}
			}
			dist = dist*dist;
			fullweight += dist;
			weight.push_back(pair<int,Point>(dist, pnt));
		}
		int upper = rand() % fullweight;
		for(auto it = weight.begin(); it!=weight.end();it++){
			if(it->first>upper){
				clust.push_back(it->second);
				//coutit->second.toString()<<endl;
				break;
			}
			upper -= it->first;
		}
		weight.clear();
	}	
	
}
vector<vector<Point>> binmerge(vector<Point> p,int start, int mult){
	vector<vector<Point>> sectors;
	sectors.push_back(p);
	int largestSector=0;
	for(int i =0; sectors.size()<k; i++){//do this until k sectors

		for(int j=0; j<sectors.size(); j++){
			if(sectors.at(j).size()>sectors.at(largestSector).size()) largestSector = j;
		}
		int dim = (start+mult*i)%3;
		sortbins(sectors.at(largestSector), dim);
		vector<Point> temp;
		int avg = (sectors.at(largestSector).front().get(dim)+sectors.at(largestSector).back().get(dim))/2; // get the range avg for dim
		split(avg, dim, sectors.at(largestSector), temp);
		if(temp.size()>0)
		sectors.push_back(temp);
	}
	return sectors;
}

void print(vector<cluster> clusters, int dist, string filename){
   fstream f;
   f.open(filename.substr(0,filename.find(".txt"))+"_kout.txt",ios::out);
   if(f.is_open()){
	f << to_string(dist)<< '\n';	
	for(cluster it : clusters ){

		for(auto itt = it.points.begin(); itt != it.points.end(); itt++ ){
			f<<to_string(itt->index);
			auto tmp = (itt+1);
			if(tmp != it.points.end()){//the next is not the end
				f<<' ';
			}
		}
		f<<'\n';

	}
   }
   f.close();
}

vector<cluster> createClusters(vector<Point> p){
	srand(time(0));
	vector<cluster> clusters;
/*	
	for(Point pnt : set){
		clusters.push_back(cluster(pnt));//creates k clusters
	}
	*/
	weightedDistribution(clusters, p);
	//cout"OUT CLUSTER"<<endl;
	int clusterchange = 1;
	int counter = 0;
	while(clusterchange>0){
		//coutcounter<<endl;
		clusterchange = 0;//clusterchange set to one
		for(int i = 0; i<p.size(); i++){ //groups point to nearest centroid 
			int smallestdist = 6001;
			int closestcluster = 0;
			for(int j =0; j<clusters.size(); j++){
				int dist = clusters.at(j).compareMid(p.at(i));		
				if(dist<smallestdist){
					smallestdist = dist;
					closestcluster = j;
				}
			}
			//cout"HERE 1"<<endl;
			//coutclosestcluster<<endl;
			//couti<<endl;
			//coutclusters.at(closestcluster).middle.toString()<<endl;
			clusters.at(closestcluster).points.push_back(p.at(i));	// for each point, add it to closest cluster		
		}
		
			//cout"HERE 2"<<endl;
		
		for(int i = 0; i<k; i++){
			Point temp = clusters.at(i).middle;
			if(!temp.equals(clusters.at(i).findMiddle())) clusterchange++; //if the centroid changed, add to cluster change
		}
			//cout"HERE 3"<<endl;
		//if there was a change in the middle (new points added), delete the vector of points
		if(clusterchange != 0){
			for(auto it= clusters.begin(); it!= clusters.end(); it++){
				it->points.clear(); 
			}
			
		}
	counter++;	
	}
return clusters;
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
		vector<Point> points;
		load(filename,points);//load the points up
		//cout"FILE: "<<filename<<endl;
		//cout"SIZE IS: " << points.size() <<" First Val: "<<points[0].toString()<<endl;
		vector<cluster> bestcluster;
		int smallestdist =6001;
		//cout"Looking to beat: "<<thresh<<endl;
		while(smallestdist>thresh){
		vector<cluster> clusters = createClusters(points);
		int dist = verify(clusters);
		if(dist<smallestdist){
			smallestdist = dist;
			bestcluster = clusters;
		}
		}
		print(bestcluster,smallestdist,filename);
	}
	return 0;
}
