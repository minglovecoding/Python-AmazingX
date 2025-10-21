#include<iostream>
using namespace std;
int main()
{
	int mj=0, gj=0, xj=0;                  //定义变量分别表示母鸡、公鸡、小鸡并初始化
	for (gj = 0; gj <= 20; gj++)		   //公鸡最多可买20个
	{
		for (mj = 0; mj <= 33; mj++)	   //母鸡最多可买33个
		{
			xj = 100 - gj - mj;			   // 三种鸡的总数是100只
			if (xj % 3 == 0 && 5 * gj + 3 * mj + xj / 3 == 100)    // 总花费为100元。
		    cout<<gj<<" "<<mj<<" "<<xj<<endl;
		}
	}
	return 0;
}