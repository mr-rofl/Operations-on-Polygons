#include <iostream>
#include <string>
#include "vector"
#include "cstdlib"
#include "algorithm"
#include <math.h>
#include <iomanip>
using namespace std;
string inpt;

class point {
	
public:
	
	point(){
	x=0;y=0;
	}

	point(float temp_x , float temp_y){
	x=temp_x;
	y=temp_y;
	}
	bool equal(point p){if(x==p.x&& y==p.y)return true;
	else return false;
	}
	float get_x(){return x;}
	float get_y(){return y;}
	float slope(point p){return (p.y - y) / (p.x - x);}
	void printPoint(){
	cout<<"("<<x<<","<<y<<")";
	}
	float distance(point p){
	return sqrt(pow(x-p.x,2)+pow(y-p.y,2)) ;
	}
	point between(point p1,point p2){
		float maxx=x , maxy=y , minx=x,miny=y;
		if(p1.get_x()<minx)minx=p1.get_x();
		if(p2.get_x()<minx)minx=p2.get_x();
		if(p1.get_y()<miny)miny=p1.get_y();
		if(p2.get_y()<miny)miny=p2.get_y();
		if(p1.get_x()>maxx)maxx=p1.get_x();
		if(p2.get_x()>maxx)maxx=p2.get_x();
		if(p1.get_y()>maxy)maxy=p1.get_y();
		if(p2.get_y()>maxy)maxy=p2.get_y();
		if((x>minx && x<maxx)|| (y>miny && y<maxy))return point(x,y);
		if((p1.get_x()>minx && p1.get_x()<maxx)|| (p1.get_y()>miny && p1.get_y()<maxy))return p1;
		if((p2.get_x()>minx && p2.get_x()<maxx)|| (p2.get_y()>miny && p2.get_y()<maxy))return p2;
	}
private :
	
	float x,y;
};

class line{
private :
		 
	point p1, p2;
	float length ,slope;

public:
	line(){}
	void setLinePoints(point temp1,point temp2){
	p1=temp1;p2=temp2;
	}
	float slopeLine(){
		return p1.slope(p2);
	}
	bool equalline(line l){
		if (slopeLine()==l.slopeLine()){
			if(p1.slope(l.p2)==slopeLine())return true;
		}
		else return false;}
	float getLength(){
		return sqrt(pow(p1.get_x()-p2.get_x(),2)+pow(p1.get_y()-p2.get_y(),2));
	}
	bool perpendicular(line l){
		float rx1=p1.get_x()-p2.get_x() , ry1=p1.get_y()-p2.get_y();
		float rx2=l.p1.get_x()-l.p2.get_x() , ry2=l.p1.get_y()-l.p2.get_y();
		if((rx1 * rx2) + (ry1*ry2) ==0){return true;}
		else if(p1.slope(p2) * l.p1.slope(l.p2) == -1)return true;
		else return false;
	}
	bool parallel(line l){
		float rx1=p1.get_x()-p2.get_x() , ry1=p1.get_y()-p2.get_y();
		float rx2=l.p1.get_x()-l.p2.get_x() , ry2=l.p1.get_y()-l.p2.get_y();
		if((rx1 * ry2)- (ry1 * rx2) ==0) return true;
		else return false;
		if ( slopeLine() == l.slopeLine())return true;
		else return false;
	}

	bool intersect(line l){
		if(p1.equal(l.p1)||p1.equal(l.p2)||p2.equal(l.p1)||p2.equal(l.p2))return true;
		else if(equalline(l))return true;
		else if(parallel(l))return false;
		else{
			float maxx=p1.get_x() , minx=p1.get_x() , maxy=p1.get_y() , miny=p1.get_y();
			if(p2.get_x()>maxx)maxx=p2.get_x();
			if(p2.get_x()<minx)minx=p2.get_x();
			if(p2.get_y()>maxy)maxy=p2.get_y();
			if(p2.get_y()<miny)miny=p2.get_y();
			float x=( slopeLine() *p1.get_x() - l.slopeLine() * l.p1.get_x() + l.p1.get_y() - p1.get_x() )/(slopeLine() - l.slopeLine() );
			float y=(p1.get_y()/slopeLine() - l.p1.get_y()/l.slopeLine() +l.p1.get_x() -p1.get_x())*(slopeLine()*l.slopeLine()/(l.slopeLine()-slopeLine()));
			point p3(x,y);
			if(p3.between(p1,p2).equal(p3))return true;
			else return false;
			//if(minx<=x && x<=maxx && miny<=y && y<=maxy)return true;
			//if(l.p2.get_x()<=x && x<=l.p1.get_x())return true;
			//else return false;
		}
	}
	void printline(){
		p1.printPoint();cout<<",";p2.printPoint();
	}



};

class polygon  {
	
public :
	polygon(){}

	
	void setPolygonPoint (point temp_p){
		Point.push_back(temp_p);
	}
	point getPoint(int i){
	
	return Point[i];}
	void printPolygon(){
		Point[0].printPoint();
		for(int i=1;i<Point.size();i++){
			cout<<",";Point[i].printPoint();
		}
	}
	int redundant_points(){
		int count=0; setprecision(20);
		int	k=Point.size();
		if(Point[0].equal(Point[Point.size()-1])){
		Point.erase(Point.begin());
		count++;
		}
		for(int i=1;i<Point.size();i++){
			if(Point[i-1].equal(Point[i])){
				Point.erase(Point.begin()+i-1);
				count++;i-=2;
				continue;
			}
		if(Point[0].slope(Point[Point.size()-1]) == Point[Point.size()-1].slope(Point[Point.size()-2]) ){
			if(Point[0].between(Point[Point.size()-1],Point[Point.size()-2]).equal(Point[Point.size()-1]))
				Point.erase(Point.begin()+Point.size()-1);
			else if(Point[0].between(Point[Point.size()-1],Point[Point.size()-2]).equal(Point[Point.size()-2]))
				Point.erase(Point.begin()+Point.size()-2);
			else if(Point[0].between(Point[Point.size()-1],Point[Point.size()-2]).equal(Point[0]))
				Point.erase(Point.begin());
			count++;
		}
		if(Point[0].slope(Point[Point.size()-1]) == Point[0].slope(Point[1]) ){
	
			if(Point[0].between(Point[Point.size()-1],Point[1]).equal(Point[Point.size()-1]))
				Point.erase(Point.begin()+Point.size()-1);
			else if(Point[0].between(Point[Point.size()-1],Point[1]).equal(Point[1]))
				Point.erase(Point.begin()+1);
			else if(Point[0].between(Point[Point.size()-1],Point[1]).equal(Point[0]))
				Point.erase(Point.begin());
	
		count++;
		}
			else{if(i+1>=Point.size())break; else{
				float slope1=Point[i].slope(Point[i+1]);
				float slope2=Point[i-1].slope(Point[i]);
				if(slope1 == slope2){
			if(Point[i].between(Point[i-1],Point[i+1]).equal(Point[i-1]))
				Point.erase(Point.begin()+i-1);
			else if(Point[i].between(Point[i-1],Point[i+1]).equal(Point[i+1]))
				Point.erase(Point.begin()+i+1);
			else if(Point[i].between(Point[i-1],Point[i+1]).equal(Point[i]))
				Point.erase(Point.begin()+i);
					count++;
				}
			}
			}
		}

		if(Point[0].equal(Point[Point.size()-1])){
		Point.erase(Point.begin());
		count++;
		}

		return count;}
	bool search(string s){
		int temp1=s.find(',');
		string tempx=s.substr(1,temp1 -1);
		string tempy=s.substr(temp1 +1, s.size()-1);
		float x=atof(tempx.c_str());
		float y=atof(tempy.c_str());
		for(int i=0;i<Point.size();i++){
			if(Point[i].get_x()==x&&Point[i].get_y()==y){return true;}
		}
	return false;
	}
	int sizePolygon(){
		return Point.size();
	}
	
	void setLine(){
		line l;
		l.setLinePoints(Point[0],Point[Point.size()-1]);
		Line.push_back(l);
		for(int i=1;i<Point.size();i++){
			line l;
			l.setLinePoints( Point[i-1] , Point[i]);
			Line.push_back(l);
		}
	}
	line getLine(int i){return Line[i];}
	bool rectangle2(){
		if(Point.size()==4){
		if(Line[0].perpendicular(Line[1])&&Line[2].perpendicular(Line[1])&&Line[3].perpendicular(Line[2]))
		{return true;}
		else{return false;}
		}
		else{return false;}

	}
	bool trapezoid(){
		
		if(Point.size()==4){
			if(Line[0].parallel(Line[2]) && !Line[1].parallel(Line[3]))return true;
			if(!Line[0].parallel(Line[2]) && Line[1].parallel(Line[3])) return true;
			else return false;
		}
		else return false;
	}
	float perimeter(){
	float sum=0;
	for (int i=0;i<Line.size();i++){
		sum+=Line[i].getLength();
	}
	return sum;}
	float area(){
	float sum =0;
	sum+= Point[Point.size()-1].get_x() * Point[0].get_y() - Point[0].get_x()*Point[Point.size()-1].get_y() ;
	for(int i=1;i<Point.size();i++)
	{	sum+=Point[i-1].get_x()*Point[i].get_y() - Point[i-1].get_y()*Point[i].get_x();
	}
	return fabs(sum)/2.0 ;

	}
	bool enclosing(polygon p){
		float minx=99999 , miny=99999 , maxx= -99999 , maxy= -99999 ;
		for(int i=0;i<p.sizePolygon();i++){
			if(p.getPoint(i).get_x()<minx)minx=p.getPoint(i).get_x();
			if(p.getPoint(i).get_x()>maxx)maxx=p.getPoint(i).get_x();
			if(p.getPoint(i).get_y()<miny)miny=p.getPoint(i).get_y();
			if(p.getPoint(i).get_y()>maxy)maxy=p.getPoint(i).get_y();
		}int count=0;
		for(int i=0;i<sizePolygon();i++){
				if(minx<=getPoint(i).get_x()&&getPoint(i).get_x()<=maxx && miny<=getPoint(i).get_y()&&getPoint(i).get_y()<=maxy )count++;
				else break;
		}
		if (count==sizePolygon())return true;
		else return false;
	}
private :
	vector<point> Point;
	vector<line> Line;
};

int polygon_num(){
	int count=0;
	for(int i=0;i<inpt.length();i++)
	{
		if(inpt[i]==';')count++;
	}
	
	return count+1;
}
int num_Points(){
	int count=0;
	
	for(int z=0;z<inpt.length();z++)
	{
		if(inpt[z]=='('){count++;}
		
	}
	return count ;
	
}

float minx(vector<polygon> p){
	float min=p[0].getPoint(0).get_x();
	for(int i=0;i<polygon_num();i++){
		for(int k=0;k<p[i].sizePolygon();k++){
		if( min>p[i].getPoint(k).get_x() )
		{min=p[i].getPoint(k).get_x() ;
	}
}
	}
return min;
}
float miny(vector<polygon> p){
	float min=p[0].getPoint(0).get_y();
	for(int i=0;i<polygon_num();i++){
		for(int k=0;k<p[i].sizePolygon();k++){
		if( min>p[i].getPoint(k).get_y() )
		{min=p[i].getPoint(k).get_y() ;
	}
}
	}
return min;}

float maxx(vector<polygon> p){
	float max=p[0].getPoint(0).get_x();
	for(int i=0;i<polygon_num();i++){
		for(int k=0;k<p[i].sizePolygon();k++){
		if( max<p[i].getPoint(k).get_x() )
		{max=p[i].getPoint(k).get_x() ;
	}
}
	}
return max;}
float maxy(vector<polygon> p){
	float max=p[0].getPoint(0).get_y();
	for(int i=0;i<polygon_num();i++){
		for(int k=0;k<p[i].sizePolygon();k++){
		if( max<p[i].getPoint(k).get_y() )
		{max=p[i].getPoint(k).get_y() ;
	}
}
	}
return max;}

void max_rect(vector<polygon> p){
	cout<<"("<<maxx(p)<<","<<maxy(p)<<")"<<","<<"("<<maxx(p)<<","<<miny(p)<<")"
		<<",("<<minx(p)<<","<<miny(p)<<")"<<",("<<minx(p)<<","<<maxy(p)<<")";
}

vector<int> search_all(string s , vector<polygon> p){
	vector<int> count;
	for (int i=0;i<polygon_num();i++){
		if(p[i].search(s)){count.push_back(i+1);}
	}
	for(int i=0;i<count.size();i++){
		if(i==0){cout<<count[0];}
		else{cout<<","<<count[i];}
	}
return count;}

int repeated_point(point Point,  vector<polygon> p){
	int count=0;
	for(int i=0;i<p.size();i++){
		for(int k=0;k<p[i].sizePolygon();k++){
			if(p[i].getPoint(k).equal(Point)){count++;break;}
		}
	
	}

return count;
}

vector<int> points_more(int n ,vector<polygon> p ){
	vector<int> count;
	for(int i=0;i<polygon_num();i++){
		if(p[i].sizePolygon()>n){
			count.push_back(i);
		}
	}
	return count;}
void print_polygons_more(int n ,vector<polygon> p ){
	if (p.size()==0)cout<<"none";
	for(int i=0;i<points_more(n,p).size();i++)
		if(i==0){cout<<points_more(n,p)[0]+1;}
		else{cout<<","<<points_more(n,p)[i]+1;}
}

vector<int> points_less(int n ,vector<polygon> p ){
	vector<int> count;
	for(int i=0;i<polygon_num();i++){
		if(p[i].sizePolygon()<n){
			count.push_back(i);
		}
	}
	return count;}
void print_polygons_less(int n ,vector<polygon> p ){
	if (p.size()==0)cout<<"none";
	for(int i=0;i<points_less(n,p).size();i++)
		if(i==0){cout<<points_less(n,p)[0]+1;}
		else{cout<<","<<points_less(n,p)[i]+1;}
}

vector<int> points_equal(int n ,vector<polygon> p ){
	vector<int> count;
	for(int i=0;i<polygon_num();i++){
		if(p[i].sizePolygon()==n){
			count.push_back(i);
		}
	}
	return count;}
void print_polygons_equal(int n ,vector<polygon> p )	{
	if (p.size()==0)cout<<"none";
	for(int i=0;i<points_equal(n,p).size();i++)
		if(i==0){cout<<points_equal(n,p)[0]+1;}
		else{cout<<","<<points_equal(n,p)[i]+1;}
}


void print_points_more(int n ,vector<polygon> p ){
	vector<point> repeatedPoints;
	for(int i=0;i<p.size();i++){
		for(int j=0;j<p[i].sizePolygon();j++){
			if( repeated_point(p[i].getPoint(j),p) > n)repeatedPoints.push_back(p[i].getPoint(j));
		}
	
	}
	for(int i=0;i<repeatedPoints.size();i++){
		for(int j=i+1;j<repeatedPoints.size();j++){
			if(repeatedPoints[i].equal(repeatedPoints[j])){
				repeatedPoints.erase(repeatedPoints.begin()+j);
				j--;}
		}
	}
	if(repeatedPoints.size()==0)cout<<"none";
	repeatedPoints[0].printPoint();
	for(int i=1;i<repeatedPoints.size();i++){
		
		cout<<",";repeatedPoints[i].printPoint();
	}
}
void print_points_less(int n ,vector<polygon> p ){
	vector<point> repeatedPoints;
	for(int i=0;i<p.size();i++){
		for(int j=0;j<p[i].sizePolygon();j++){
			if( repeated_point(p[i].getPoint(j),p) < n)repeatedPoints.push_back(p[i].getPoint(j));
		}
	
	}
	for(int i=0;i<repeatedPoints.size();i++){
		for(int j=i+1;j<repeatedPoints.size();j++){
			if(repeatedPoints[i].equal(repeatedPoints[j])){
				repeatedPoints.erase(repeatedPoints.begin()+j);
				j--;}
		}
	}
		if(repeatedPoints.size()==0)cout<<"none";
	repeatedPoints[0].printPoint();
	for(int i=1;i<repeatedPoints.size();i++){
		
		cout<<",";repeatedPoints[i].printPoint();
	}
}
void print_points_equal(int n ,vector<polygon> p ){
	vector<point> repeatedPoints;
	for(int i=0;i<p.size();i++){
		for(int j=0;j<p[i].sizePolygon();j++){
			if( repeated_point(p[i].getPoint(j),p) == n)repeatedPoints.push_back(p[i].getPoint(j));
		}
	
	}
	for(int i=0;i<repeatedPoints.size();i++){
		for(int j=i+1;j<repeatedPoints.size();j++){
			if(repeatedPoints[i].equal(repeatedPoints[j])){
				repeatedPoints.erase(repeatedPoints.begin()+j);
				j--;}
		}
	}
		if(repeatedPoints.size()==0)cout<<"none";
	repeatedPoints[0].printPoint();
	for(int i=1;i<repeatedPoints.size();i++){
		
		cout<<",";repeatedPoints[i].printPoint();
	}
}

void List_Triangles(vector<polygon> p){
	if(points_equal(3,p).size()==0){cout<<"none";}
	else print_polygons_equal(3,p);
}
void List_Rectangles(vector<polygon> p){
	
	vector<int> rect;
	for(int i=0;i<points_equal(4,p).size();i++){
		if(p[points_equal(4,p)[i]].rectangle2()){rect.push_back(points_equal(4,p)[i]+1);}
	}
	if(rect.size()==0){cout<<"none";}
	else{
	cout<<rect[0];
	if(rect.size()>1){
		for(int i=1;i<rect.size();i++){
		cout<<","<<rect[i];
		}
	}}
}
void List_Trapezoids(vector<polygon> p){
	vector<int> count;
	for(int i=0;i<points_equal(4,p).size();i++){
		if(p[points_equal(4,p)[i]].trapezoid()){count.push_back(points_equal(4,p)[i]+1);}
	}
	if(count.size()==0){cout<<"none";}
	else{
	cout<<count[0];
	if(count.size()>1){
		for(int i=1;i<count.size();i++){
		cout<<","<<count[i];
		}
	}}

}

void inside_Rectangle(string s ,vector<polygon> p){
		vector<int> p1;
		float min_x=9999 , min_y=9999 , max_x=-9999 , max_y= -9999;
		for(int i=0; i <s.length();){
		int temp1 =s.find('(',i);
		int temp2 =s.find(',',temp1);
		int temp3 =s.find(')',temp2);
		string temp_x=s.substr(temp1 +1,temp2-temp1 -1);
		string temp_y=s.substr(temp2 +1,temp3-temp2 -1);
		float tempx=atof(temp_x.c_str());
		float tempy=atof(temp_y.c_str());
		if(max_x<tempx){max_x=tempx;}
		if(min_x>tempx){min_x=tempx;}
		if(max_y<tempy){max_y=tempy;}
		if(min_y>tempy){min_y=tempy;}
		//p[k](atof(tempx.c_str()),atof(tempy.c_str()));
		i=temp3;
	}
		
		for(int i=0;i<p.size();i++){
			int count=0;
			for(int k=0;k<p[i].sizePolygon();k++){

				if(min_x<=p[i].getPoint(k).get_x()&&p[i].getPoint(k).get_x()<=max_x && min_y<=p[i].getPoint(k).get_y()&&p[i].getPoint(k).get_y()<=max_y )count++;
				else break;
				if (count==p[i].sizePolygon()){p1.push_back(i);}
			}
		}
		if(p1.size()==0)cout<<"none";
		else cout<<p1[0]+1; if(p1.size()>1){
			for (int i=1;i<p1.size();i++){
			cout<<","<<p1[i]+1;
			}
		}
}
void inside_Circle(string s, vector<polygon> p){
	int temp1=s.find(',');
	int temp2=s.find(')');
	string sx=s.substr(1,temp1-1) , sy=s.substr(temp1 +1,temp2 -1) , sr=s.substr(temp2 +2, s.length()-1);
	float x=atof(sx.c_str()) , y=atof(sy.c_str()), r=atof(sr.c_str());
	point center(x,y);
	
	vector<int> inside;
	for (int i=0;i<p.size();i++){
		int count=0;
		for (int k=0;k<p[i].sizePolygon();k++){
			if(p[i].getPoint(k).distance(center)>r)break;
			else count++;
		}
		if(count ==p[i].sizePolygon()) inside.push_back(i);

	}
	if(inside.size()==0)cout<<"none";
	else cout<<inside[0]+1;
	for(int i=1;i<inside.size();i++){
	cout<<","<<inside[i]+1;
	}
}

float Polygon_Area(int n, vector<polygon> p){
	return p[n-1].area();
}
void Polygons_Area_Range(string s , vector<polygon> p){
	float minA , maxA;
	int temp1 =s.find(',');
	minA=atof(s.substr(0,temp1 ).c_str());
	maxA=atof(s.substr(temp1 +1).c_str());
	vector<int> range;
	for (int i=0;i<p.size();i++){
		if(minA<=p[i].area() && p[i].area()<=maxA) range.push_back(i);
		}
	if(range.size()==0)cout<<"none";
	else {
	cout<<range[0]+1;
	for(int i=1;i<range.size();i++){
		cout<<","<<range[i]+1 ;
	}
	}
}

void Enclosing_Point(string s,vector<polygon> p){
	int temp1=s.find(',');
	int temp2=s.find(')');
	string sx=s.substr(1,temp1-1) , sy=s.substr(temp1 +1,temp2 -1) ;
	float x=atof(sx.c_str()) , y=atof(sy.c_str()) ;
	vector<int> enclosing;
	
	for(int i=0;i<p.size();i++){
		int count =0;
		float max_x=p[i].getPoint(0).get_x() , min_x=p[i].getPoint(0).get_x();
		float max_y=p[i].getPoint(0).get_y() , min_y=p[i].getPoint(0).get_y();
	
		for(int j=0;j<p[i].sizePolygon();j++){
			if(p[i].getPoint(j).get_x()<min_x) min_x=p[i].getPoint(j).get_x();
			if(p[i].getPoint(j).get_x()>max_x) max_x=p[i].getPoint(j).get_x();
			if(p[i].getPoint(j).get_y()<min_y) min_y=p[i].getPoint(j).get_y();
			if(p[i].getPoint(j).get_y()>max_y) max_y=p[i].getPoint(j).get_y();
	}
	
		for(int k=0;k<p[i].sizePolygon();k++){
			if(	min_x <= x && x<= max_x && min_y <= y && y <= max_y)count++;
			else break;
	}
		if(count==p[i].sizePolygon())enclosing.push_back(i);
	}
	if(enclosing.size()==0)cout<<"none";
	else{
			cout<<enclosing[0]+1;
	for(int i=1;i<enclosing.size();i++){
		cout<<","<<enclosing[i]+1 ;
	}
	
	
	}
}
bool Is_Intersecting(string s, vector<polygon> p){
	int p1 , p2;
	int temp1 =s.find(',');
	p1=atof(s.substr(0,temp1 ).c_str());
	p2=atof(s.substr(temp1 +1).c_str());
	if(p[p1 -1].enclosing(p[p2 -1]) || p[p2 -1].enclosing(p[p1 -1])) return true;
	for (int i=0;i<p[p1 -1].sizePolygon();i++){
		for (int j=0;j<p[p2 -1].sizePolygon();j++){
			if(p[p1 -1].getLine(i).intersect(p[p2 -1].getLine(j)))return true;
		
		}
	
	}
return false;
	}
bool Is_Intersecting(int p1 , int p2 , vector<polygon> p){
	if(p[p1 -1].enclosing(p[p2 -1]) || p[p2 -1].enclosing(p[p1 -1])) return true;
	for (int i=0;i<p[p1 -1].sizePolygon();i++){
		for (int j=0;j<p[p2 -1].sizePolygon();j++){
			if(p[p1 -1].getLine(i).intersect(p[p2 -1].getLine(j)))return true;
		
		}
	
	}
return false;}
bool Intersecting_Group(string s,vector<polygon> p ){
	int i,j,k;
	int temp1 =s.find(',',0);
	int temp2 =s.find(',',temp1 +1);
	i=atof(s.substr(0,temp1 ).c_str());
	j=atof(s.substr(temp1 +1, temp2 - temp1 -1).c_str());
	k=atof(s.substr(temp2 +1).c_str());
	if(Is_Intersecting(i,j,p)&&Is_Intersecting(i,k,p)&&Is_Intersecting(j,k,p))return true;
	else return false;
}
void Largest_Intersecting_Pair(vector<polygon> p ){
	float max=0;	int max_points[2];
	for (int i=0;i<p.size() -1;i++){
		for(int j=i+1;j<p.size();j++){
			if(Is_Intersecting(i+1,j+1,p)){
				if(p[i].area()+p[j].area() >max){
				max=p[i].area()+p[j].area() ;
				max_points[0]=i;max_points[1]=j;
				}
			}
		}
	}
	cout<<max_points[0]+1<<","<<max_points[1]+1 ;
}

bool Is_Connected(int p1 , int p2 , vector<polygon>p){	
	
	if(Is_Intersecting(p1,p2,p))return true;
	else{ vector<int> temp1;vector<int> temp2;
		for (int i=0;i<p.size();i++){
			if(i==p1-1 || i== p2 -1)continue;
			else{
				if(Is_Intersecting(p1 , i+1,p))temp1.push_back(i);
				if(Is_Intersecting(p2 , i+1,p))temp2.push_back(i);
			}
		}
		for(int i=0;i<temp1.size();i++){
			for(int k=0;k<temp2.size();k++){
			if(temp1[i]==temp2[k])return true;
			if(Is_Intersecting(i+1,k+1,p))return true;
			}
		}
	}
	

return false;}
bool Is_Connected(string s, vector<polygon>p){
	int p1 , p2;
	int temp1 =s.find(',');
	p1=atof(s.substr(0,temp1 ).c_str());
	p2=atof(s.substr(temp1 +1).c_str());
	if(Is_Intersecting(p1,p2,p))return true;
	else{ vector<int> temp1;vector<int> temp2;
		for (int i=0;i<p.size();i++){
			if(i==p1-1 || i== p2 -1)continue;
			else{
				if(Is_Intersecting(p1 , i+1,p))temp1.push_back(i);
				if(Is_Intersecting(p2 , i+1,p))temp2.push_back(i);
			}
		}
		for(int i=0;i<temp1.size();i++){
			for(int k=0;k<temp2.size();k++){
			if(temp1[i]==temp2[k])return true;
			if(Is_Intersecting(i+1,k+1,p))return true;
			}
		}
	}
	

return false;}
bool Is_Connected_Group(string s, vector<polygon>p){
	{
	int i,j,k;
	int temp1 =s.find(',',0);
	int temp2 =s.find(',',temp1 +1);
	i=atof(s.substr(0,temp1 ).c_str());
	j=atof(s.substr(temp1 +1, temp2 - temp1 -1).c_str());
	k=atof(s.substr(temp2 +1).c_str());
	if(Is_Connected(i,j,p)&&Is_Connected(i,k,p)&&Is_Connected(j,k,p))return true;
	else return false;
}
}

int main(){
	//cin>>inpt;
	//inpt="polygons=[(1,1),(1,8),(8,8),(8,1);(2,3),(8,1),(5,3),(4,8);(1,5),(1,1),(5,1),(5,5);(7,7),(6,8),(4,11),(3,10),(5,3),(2,5),(3,3),(3,3),(5,5),(5,5),(7,7);(4,5),(8,1),(7,8),(6,11),(3,8);(2,6),(5,8),(5,13),(1,11);(0,6),(2,10),(2,12),(8,1),(-1,13),(-2,11),(-2,7);(-5,5),(-1,5),(-1,10),(-1,10),(5,12);(-4,4),(-2,8),(-2,10),(-4,4);(-5,3),(-3,3),(-1,3),(-3,7),(-5,6);(-2,-1),(-4,4),(-4,-7),(-2,-9),(-2,-4),(-2,-1);(-2,-7),(-4,-10),(-1,-12);(-1,-6),(-3,-6),(-2,-9),(1,-11),(3,-6),(0,-6),(-1,-6);(1,-9),(4,-2),(7,-5),(4,-11);(5,-5),(1,-3),(4,1),(7,2),(7,-6),(1,1)]" ;
	//inpt="[(2,3),(5,3),(4,8);(7,7),(6,8),(4,11),(3,10),(2,5),(3,3),(3,3),(5,5),(5,5),(7,7);(4,5),(7,8),(6,11),(3,8);(2,6),(5,8),(5,13),(1,11);(0,6),(2,10),(2,12),(-1,13),(-2,11),(-2,7);(-5,5),(-1,5),(-1,10),(-1,10),(5,12);(-4,4),(-2,8),(-2,10),(-4,4);(-5,3),(-3,3),(-1,3),(-3,7),(-5,6);(-2,-1),(-4,4),(-4,-7),(-2,-9),(-2,-4),(-2,-1);(-2,-7),(-4,-10),(-1,-12);(-1,-6),(-3,-6),(-2,-9),(1,-11),(3,-6),(0,-6),(-1,-6);(1,-9),(4,-2),(7,-5),(4,-11);(5,-5),(1,-3),(4,1),(7,2),(7,-6)]" ;
	//inpt="[(3,0),(1,1),(2,2),(2,2),(3,3),(0,3),(3,0);(2,3),(4,8),(4,4),(6,6),(3,0),(2,3);(5,5),(1,1),(0,0),(3,0),(6,7)]" ;
	//inpt="[(0.9881,1.0367),(0.9881,1.0367),(1.4993,2.1766),(1.8926,2.3731),(2.7224,2.7878),(3.3005,3.0767),(3.3005,2.1766),(3.3005,1.8326),(3.9572,3.0767),(4.4881,2.3731),(4.4881,1.9014),(4.4881,1.0367),(3.7999,1.0367),(2.571,1.0367),(1.6664,1.0367),(0.9881,1.0367);(4.1642,1.5428),(4.8722,1.0908),(5.6241,0.6108),(5.6241,0.6108),(6.072,2.5452),(6.072,2.5452);(-0.497,1.0367),(-3.4865,1.0367),(-3.4865,3.0267),(-0.497,3.0267);(9.0766,0.2734),(7.14,1.2805),(7.8514,2.1592),(8.6007,3.0848),(9.9955,2.6035),(10.5982,1.3002);(9.2346,2.4653),(7.5945,1.5569),(9.1457,0.6288);(8.6595,1.9043),(8.2096,3.2984),(6.9237,3.2984),(6.3061,3.2984),(5.9815,0.382),(6.9937,0.9574),(7.8156,1.4246);(7.466,1.399),(6.7348,0.382),(7.051,-0.6349),(8.79,-1.0595),(9.9559,0.0068),(8.0126,2.1592),(7.466,1.399);(6.3689,1.7587),(4.62,3.9012),(5.0943,5.9351),(7.7906,2.6319);(5.7532,4.1692),(6.7345,6.8138),(9.6196,6.8138),(11.6056,5.9943),(9.9753,5.007),(11.7341,4.6614),(11.7341,3.8518),(11.7341,3.1311),(9.2893,3.5554),(7.2725,3.9055),(6.1521,4.1),(5.7532,4.1692);(-3.0718,1.8089),(-6.1127,-0.0698),(-1.8784,-2.2752),(0.2449,-0.9634);(1.6617,-0.9634),(3.7494,0.1366),(6.3386,-1.1724),(5.7962,-2.8189),(3.248,-3.954),(0.8941,-2.9416);(4.8342,-1.9394),(6.2977,-4.2506),(7.5258,-3.4836),(8.3813,-2.9493),(9.395,-2.3162),(4.8342,-1.9394);(6.3693,-3.3404),(3.033,-4.2813),(5.2845,-4.2813),(3.3605,-5.2323),(8.2114,-4.2199);(7.9658,-2.5837),(8.5287,-1.1724),(10.2992,-1.1724),(11.6398,-2.011);(9.0603,-0.9887),(13.5768,-3.1403),(11.6352,-7.2161),(7.1187,-5.0645);(9.9559,0.0068),(10.5982,1.3002),(12.4125,1.5898),(11.1369,-0.9792);(10.5982,1.3002),(10.0725,3.0487),(12.1191,2.7801);(10.5982,1.3002),(12.3419,0.4695),(13.8771,3.6921),(12.1334,4.5228);(13.5768,-3.1403),(12.2895,-1.6623),(15.4483,-0.6542),(17.036,-1.8276),(16.209,-3.9264);(2.971,6.1238),(2.3229,4.0151),(0.8773,4.6792),(-1.2662,3.8989),(-3.4264,4.8619),(1.841,5.3102),(0.9936,6.6385),(-0.6016,5.9744),(-1.1167,7.9669),(-3.094,6.4227),(-4.395,5.4067),(-6.3342,6.0906),(-4.44,7.1034),(-5.52,8.4816),(-2.4626,8.4816),(0.5782,7.7344),(2.3728,8.5148),(4.4997,5.2438);(-6.0245,2.1356),(-8.2909,-0.6815),(-11.7458,-0.6815),(-13.9016,1.2518),(-16.555,1.2518),(-17.7987,4.4279),(-13.6529,7.2727),(-12.2709,3.1022),(-10.8613,8.8888),(-9.9492,3.1022),(-8.2632,3.1022),(-8.5949,5.726),(-7.2682,3.9584),(-7.2682,6.9136),(-6.0245,2.1356)]";
	inpt="[(-2,7),(1,1),(-2,1),(-5,1),(-4,3),(-4,3),(-3,5);(-5.5,5.5),(-4,7),(-3,8),(1,7.5),(-4,2.5),(-5.5,5.5);(6.5,-1.5),(9.5,-2.5),(9,-7),(5,-6.5),(5,-5),(5,-3.5);(7.5,-3.5),(12.5,-3.5),(7.5,-6);(5.5,8.5),(10,8.5),(11.5,4.5),(5.5,4.5);(4.5,-5),(6.5,-2.5),(6.5,-4),(6.5,-7),(6.5,-7),(4.5,-5);(6.5,7.5),(9.5,7.5),(9.5,7.5),(9.5,5.5),(6.5,5.5);(11,3),(12,2),(13,1),(10,1),(6,1),(8,3);(-9.5,9),(-7,6.5),(-8.5,5),(-10,3.5),(-12.5,6),(-11,7.5),(-11,7.5),(-9.5,9);(-7.5,-1.5),(-9,-5),(-8,-8.5),(-12,-7),(-10.5,-2.5),(-10.5,-2.5),(-7.5,-1.5);(-3,-2),(-6,-4),(-6,-6),(-6,-6),(-6,-8),(-4.5,-5),(-3,-5)]";
	//inpt="[(0,1),(1,0),(-1,0);(1,1),(1,-1),(-1,-1),(-1,1)]";
	//inpt="Polygons=[(4,8),(4,3),(4,3),(10,3),(13,3),(13,8),(13,8);(-1,5),(-4,11),(2,18),(2,18),(2,18),(8,6);(17,14),(9,9),(14,5),(17,14);(-13,-1),(-6,3),(2,-11),(-5,-15),(-9,-8),(-9,-8);(7,-14),(4,-17),(4,-17),(-1,-14),(-2,-9),(3,-6),(10,-7),(6,-11);(-7,12),(-6.5,13),(3,4),(3,4),(-8,10);(19,-8),(19,-8),(16,-3),(10,-4),(7,-8),(10,-11),(13,-8),(14,-12),(19,-8),(19,-8);(7,-4),(5,-5),(3,-6),(5,-1);(3,-6),(1,-2),(-1,-4)]";
	vector<polygon> Polygon0(polygon_num());
	
		int k=0 ;
		for(int i=0; i <inpt.length();){
		int temp1 =inpt.find('(',i);
		int temp2 =inpt.find(',',temp1);
		int temp3 =inpt.find(')',temp2);
		string tempx=inpt.substr(temp1 +1,temp2-temp1 -1);
		string tempy=inpt.substr(temp2 +1,temp3-temp2 -1); 

		point p(atof(tempx.c_str()),atof(tempy.c_str()));
		
		Polygon0[k].setPolygonPoint(p);
		
		

		if(inpt[temp3 +1]==';'){k++;}
		if(inpt[temp3 +1]==']'){break;}
		i=temp3;
	}
		vector<polygon> PurePolygon;
		PurePolygon=Polygon0;
		
		int sum=0;
		for(int i=0;i<polygon_num();i++)
		{	sum+=PurePolygon[i].redundant_points();
		
		}
		for(int i=0;i<Polygon0.size();i++){
			Polygon0[i].setLine();
			PurePolygon[i].setLine();	
		}
		Polygon0[0].printPolygon();cout<<endl;
		PurePolygon[0].printPolygon();cout<<endl;
		/*for(int i=0;i<Polygon0.size();i++){
			cout<<Polygon0[i].redundant_points();cout<<endl;
		}*/
		//cout<<sum<<endl;
		string user_input;
		cin>>user_input;
		while(1){
			if(user_input=="Number_Polygons"){cout<<polygon_num();}
			else if(user_input=="Total_Number_Points"){cout<<num_Points();}
			else if(user_input=="Minimum_X"){cout<<minx(Polygon0)<<endl;}
			else if(user_input=="Minimum_Y"){cout<<miny(Polygon0)<<endl;}
			else if(user_input=="Maximum_X"){cout<<maxx(Polygon0)<<endl;}
			else if(user_input=="Maximum_Y"){cout<<maxy(Polygon0)<<endl;}
			else if(user_input=="Enclosing_Rectangle"){max_rect(Polygon0);cout<<endl;}
			else if(user_input=="Total_Redundant_Points"){if (sum==0)cout<<"none";else cout<<sum<<endl;}
			else if(user_input=="Quit"){break;}
			else if(user_input=="Point_Polygons"){
				string s;
				cin>>s;
				search_all(s,Polygon0);}
			else if(user_input=="Polygon_Points"){
				int j;
				cin>>j;
				//Polygon0[j-1].printPolygon();
				PurePolygon[j-1].printPolygon();
				cout<<endl;}
			else if(user_input=="List_Polygons_Points"){
				string next_input;
				cin>>next_input;
				int n;
				cin>>n;
				if(next_input=="More")print_polygons_more(n,PurePolygon);
				else if(next_input=="Less")print_polygons_less(n,PurePolygon);
				else if(next_input=="Equal")print_polygons_equal(n,PurePolygon);
				
			}
			else if(user_input=="List_Points_Polygons"){
				string next_input;
				cin>>next_input;
				int n;
				cin>>n;
				if(next_input=="More")print_points_more(n,PurePolygon);
				else if(next_input=="Less")print_points_less(n,PurePolygon);
				else if(next_input=="Equal")print_points_equal(n,PurePolygon);	
			}
			else if(user_input=="Polygon_Perimeter"){
			int n;cin>>n;
			cout<<PurePolygon[n-1].perimeter();
			}
			else if(user_input=="List_Triangles"){
				List_Triangles(PurePolygon);
			}
			else if(user_input=="List_Rectangles"){
				List_Rectangles(PurePolygon);
			}
			else if(user_input=="List_Trapezoid"){
				List_Trapezoids(PurePolygon);
			}
			else if(user_input=="Inside_Rectangle"){
				string next_input;
				cin>>next_input;
				inside_Rectangle(next_input,PurePolygon);
			}
			else if(user_input=="Inside_Circle"){
				string next_input;
				cin>>next_input;
				inside_Circle(next_input,PurePolygon);
			}
			else if(user_input=="Polygon_Area"){
				int n;
				cin>>n;
				cout<<PurePolygon[n-1].area()<<endl;
			}
			else if(user_input=="Polygons_Area_Range"){
				string next_input;
				cin>>next_input;
				Polygons_Area_Range(next_input,PurePolygon);
			}
			else if(user_input=="Polygons_Enclosing_Point"){
				string next_input;
				cin>>next_input;
				Enclosing_Point(next_input,PurePolygon);			
			}
			else if(user_input=="Is_Intersecting"){
				string next_input;
				cin>>next_input;
				if(Is_Intersecting(next_input,PurePolygon))cout<<"True";
				else cout<<"False";
			}
			else if(user_input=="Intersecting_Group"){
				string next_input;
				cin>>next_input;
				if(Intersecting_Group(next_input,PurePolygon))cout<<"True";
				else cout<<"False";
			
			}
			else if(user_input=="Largest_Intersecting_Pair"){
			Largest_Intersecting_Pair(PurePolygon);
			}
			else if(user_input=="Is_Connected"){
			string next_input;cin>>next_input;
			if(Is_Connected(next_input , PurePolygon))cout<<"True";
			else cout<<"False";
			}
			else if(user_input=="Is_Connected_Group"){
			string next_input;cin>>next_input;
			if(Is_Connected_Group(next_input,PurePolygon))cout<<"True";
			else cout<<"False";
			}
		cin>>user_input;}

		return 0;}