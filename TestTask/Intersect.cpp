#include <iostream>
class vector3d 
{
public:
  double x;
  double y;
  double z;
};
using namespace std;

class Segment3D
{
private: 
  vector3d start;
  vector3d end;
  vector3d direct;
public:
  void SetVector(vector3d v1,vector3d v2)
  {
    start = v1;
    end = v2;
  }

  void SetDirect()
  {
    direct.x = end.x - start.x;
    direct.y = end.y - start.y;
    direct.z = end.z - start.z;
  }

  vector3d GetDirect()
  {
    return direct;
  }

  vector3d GetStart()
  {
    return start;
  }

  vector3d GetEnd()
  {
    return end;
  }
};

 bool ComparisonVector(vector3d a, vector3d b)
 {
   if (a.x == b.x && a.y == b.y && a.z == b.z)
    return true;
   else return false;
 }

vector3d Intersect(Segment3D s1, Segment3D s2)
{
  vector3d inters,d1,d2,p1,p2;
  double m,n,r,s,a,b,c;
  d1 = s1.GetDirect();
  d2 = s2.GetDirect();
  p1 = s1.GetStart();
  p2 = s2.GetStart();
  a = p2.x - p1.x;
  b = p2.y - p1.y;
  c = p2.z - p1.z; 
    
  if (d1.x * d2.y != d1.y * d2.x)
  {
    m = d1.x;
    n = d2.x;
    r = d1.y;
    s = d2.y;
  } else if (d1.x * d2.z != d1.z * d2.x)
  {
    m = d1.x;
    n = d2.x;
    r = d1.z;
    s = d2.z;
  } else if (d1.y * d2.z != d1.z * d2.y)
  {
    m = d1.y;
    n = d2.y;
    r = d1.z;
    s = d2.z;
  } else 
  {
    if (ComparisonVector(s1.GetStart(), s2.GetStart()) || ComparisonVector(s1.GetStart(), s1.GetEnd() ))
      return s1.GetStart();
      
    if (ComparisonVector(s1.GetEnd(), s2.GetEnd()) || ComparisonVector(s1.GetEnd(), s2.GetEnd()))
      return s1.GetEnd();
  }
  
   double p = (b * n - a * s)/(n * r - m * s);
   double q = (b * m - a * r)/ (n * r - m * s);
  inters.x = p1.x + d1.x*p;
  inters.y = p1.y + d1.y*p;
  inters.z = p1.z + d1.z*p;
  return inters;
}

bool CheckIntersect(vector3d inters, Segment3D s1, Segment3D s2)
{
  vector3d st1 = s1.GetStart();
  vector3d st2 = s1.GetEnd();
  vector3d st3 = s2.GetStart();
  vector3d st4 = s2.GetEnd(); 
  if (min(st1.x,st2.x) <= inters.x && inters.x <= max(st1.x,st2.x) && min(st1.y,st2.y) <= inters.y && inters.y <= max(st1.y,st2.y) && min(st1.z,st2.z) <= inters.z && inters.z <= max(st1.z,st2.z) ){
    return true;
  }
  else { return false; } 
}

//x - x1  y -y1   z -  z1 |
//x2 - x1 y2 - y1 z2 - z1 | = 0
//x3 - x1 y3 - y1 z3 - z1 |
bool CheckVectors(vector3d v1, vector3d v2, vector3d v3,vector3d v4)
{
  double x = v1.x ,y = v1.y,z = v1.z,x1 = v2.x ,y1 = v2.y,z1 = v2.z,x2 = v3.x,y2 = v3.y,z2 = v3.z,x3 = v4.x,y3 = v4.y,z3 = v4.z;
  double a1 =(x - x1)*((y2-y1)*(z3 - z1) - (y3 - y1)*(z2 - z1));
  double a2 =(y - y1) *((x2 - x1)*(z3 - z1)-(x3 - x1)*(z2 - z1));
  double a3 =(z -  z1)*((x2 - x1)*(y3 - y1)-(x3 - x1 )*(y2 - y1));
  if (a1-a2+a3 == 0)
   return true;
   else return false;
};

using namespace std;

int main() {
  vector3d v1,v2,v3,v4,ans;
  v1.x = 0; v1.y = 0; v1.z = 0;
  v2.x = 0; v2.y = 5; v2.z = 0;
  v3.x = -2; v3.y = 2; v3.z = 0;
  v4.x = 2; v4.y = 2; v4.z = 0;
  Segment3D s1,s2;
  bool res;
  s1.SetVector(v1,v2);
  s1.SetDirect();
  s2.SetVector(v3,v4);
  s2.SetDirect();
  res = CheckVectors(v1,v2,v3,v4);
  cout << res << " " << endl;
  if ( res ){
    ans = Intersect(s1,s2);
      if (CheckIntersect(ans,s1,s2) == true)
        cout << ans.x << " " << ans.y << " " << ans.z << endl;
  }
  return 0;
}