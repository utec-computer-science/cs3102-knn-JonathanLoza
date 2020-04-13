
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <set>
using namespace std;
template <typename T>
class CartesianCoord{
  public:
  typedef T value_t;
  value_t x;
  value_t y;
  public:
  CartesianCoord(value_t _x = 0, value_t _y = 0)
  :x(_x),y(_y){
  }
  ~CartesianCoord(void){
  }
  template<typename _T>
  friend ostream& operator<<(ostream &out, const CartesianCoord<_T> c){
    out << "(" << c.x << "," << c.y << ")";
    return out;
  }
};

typedef CartesianCoord<int> coord_t;

int euclideanDistance(const coord_t &p1,const coord_t &p2){
  return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}

vector<coord_t> knn ( int k, vector<coord_t> &points, const coord_t &q){
  typedef pair<int,int> distCoord;
  multiset<distCoord> nearPoints;
  for(int i=0; i<points.size(); ++i){
    nearPoints.insert({euclideanDistance(q,points[i]),i});
    if(nearPoints.size()>k){
      auto it = nearPoints.end();
      --it;
      nearPoints.erase(it);
    }
  }
  vector<coord_t> ans;
  for(distCoord pCord: nearPoints){
    ans.push_back(points[pCord.second]);
  }
  return ans;
}
int main() {
  srand (time(NULL));

  vector<coord_t> points;
  int n_points=100000;
  for(int i=0; i< n_points; i++)
    points.push_back(coord_t(rand()%1000,rand()%1000));

  vector<coord_t>::iterator it = points.begin();
  /*for (; it != points.end(); it++){
    fflush(stdout);
    cout << "\r" << *it;
    usleep(2000);
  }*/
  cout << endl;
  vector<coord_t> knns;
  cout << "Number of points: " << n_points << endl;
  auto start = chrono::high_resolution_clock::now();
  knns = knn(3, points, coord_t(100,200));
  auto stop = chrono::high_resolution_clock::now();
  auto durationSec = chrono::duration_cast<chrono::seconds>(stop - start);
  auto durationMicro = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << "Time: " << endl;
  cout << durationSec.count() << " seconds" << endl;
  cout << durationMicro.count() << " microseconds" << endl;
  cout << "knns" << endl;
  vector<coord_t>::iterator kit = knns.begin();
  for (; kit != knns.end(); kit++)
    cout << *kit << endl;
  return 0;
}
