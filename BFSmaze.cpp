#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <cstring>
#include <deque>
#define NUM 101
using namespace std;

long long int map[NUM][NUM]; //1表示障礙物，0表示通道
long long int re[NUM][NUM];
long long int gor[4]={1,0,-1,0}; //四個方向
long long int goc[4]={0,1,0,-1}; //四個方向

typedef struct _point
{
  long long int r;
  long long int c;
  long long int dis;
}Point;

deque<Point> myq;  //BFS的queue

long long int bound(long long int row,long long int col,long long int nr,long long int nc)  //檢查是否在棋盤內
{
  if (((row>0)&&(row<=nr))&&((col>0)&&(col<=nc))) return 1;
  else return 0;
}
int main()
{
  //ifstream fin("pc.in");
  //ofstream fout("pc.out");
  long long int n, r, c, sr, sc, er, ec;
  string s;
  Point myp, nextp; // myp:目前的點  nextp:
  cin >> n;         //n個case

  for(long long int k=0;k<n;k++)
  {
    memset(re,0,sizeof(re));
    myq.clear();  //清空供下一次使用
    cin >> r >> c >> sr >> sc >> er >> ec;

    getline(cin,s);  //去除newline
    for(long long int i=1;i<=r;i++){
      getline(cin,s);
      for(long long int j=1;j<=c;j++){
        map[i][j]=s[j-1]-'0';
      }
    }
    //起點
    myp.r=sr;
    myp.c=sc;
    myp.dis=1;

    //步數設為1
    re[sr][sc]=1;

    myq.push_back(myp);   //將起點加入queue中
    while (myq.size()>0)  //還有路走
    {
      nextp=myq.front();  //取出queue的第一個
      myq.pop_front();    //將queue的第一個刪除
      if ((nextp.r==er)&&(nextp.c==ec)) //判斷是否到達目標
      {
         cout <<re[nextp.r][nextp.c] << endl;
         break;
      }
      for(long long int i=0;i<4;i++)//四個方向加入queue
      {
          if (bound(nextp.r+gor[i],nextp.c+goc[i],r,c) && (map[nextp.r+gor[i]][nextp.c+goc[i]] == 0) && (re[nextp.r+gor[i]][nextp.c+goc[i]] == 0))
          {// (1)範圍內 (2)可以走 (3)未走過 才走
            re[nextp.r+gor[i]][nextp.c+goc[i]]=nextp.dis+1; //紀錄第幾步走到
            myp.r=nextp.r+gor[i];
            myp.c=nextp.c+goc[i];
            myp.dis=nextp.dis+1;
            myq.push_back(myp); //加入queue
          }
      }
    }
    if(re[er][ec]==0)
      cout << 0 << "\n";//走不到
  }
  return 0;
}