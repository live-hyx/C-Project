//作业一
#include <iostream>
using namespace std;
void pl();
int main()
{
    pl();
    return 0;
}
void pl()
{
    int x,y,z,m;
    cin >> x >> y >> z;
    if(x>y)
    {
        m=x;
        x=y;
        y=m;
    }
    if(y>z)
    {
        m=y;
        y=z;
        z=m;
    }
    if(x>y)
    {
        m=x;
        x=y;
        y=m;
    }
    cout << x << "," << y << "," << z << endl;
}
