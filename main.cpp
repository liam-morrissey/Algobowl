#include <map>
#include <string>
using namespace std;
struct Point{
	int x,y,z;
	int index;
	Point(){}
	Point(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
	}
};

void load(string filename, map<int,Point> &points, int &n, int &k ){

}

void radix(map<int,Point> &X){

}
int verify(int finalsort[][], map<int,Point> points){

}
int** mkbins(map<int,Point> &points,int dir, int size, int k){

}
int** binmerge(map<int,Point>[] X, int n){

}
void print(int finalsort[][], int dist){
}


int main(int argc, char* argv){
	string filename = "test";
	if(argc>1) filename = argv[1];
	int n,k;
	map<int,Point> points;
	//insert load function
	//radix(points,0); //O(n), 0 for x arg
	int Xbins[k][n-k] = mkbins(points,0,n,k); //O(n)
	//radix(points,1); //O(n) 1 for y arg
	int Ybins[k][n-k] = mkbins(points,1,n,k); //O(n)
	//radix(points,2); //O(n) 2 for z arg
	int Zbins[k][n-k] = mkbins(points,2,n,k); //O(n)

	int finalsort[k][n-k] = binmerge(Xbins,Ybins,Zbins);
	int dist = verify(finalsort);
	print(finalsort,dist);
}
