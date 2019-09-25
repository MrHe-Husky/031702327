#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class element {
public:
     int num;                                //值，未定则为0
     int row_num;                            //行号
     int column_num;                         //列号
     int block_num;                          //宮号
     int possible_num[10];                   //可能取值(possible_num[0]为是否确定，1:不定,0:确定，1~9分别对应9个数,0代表不可能，1可能)
     int rm_row(int i, int j, element ele[][10], int m);                           //根据行进行可能取值排除
     int rm_column(int i, int j, element ele[][10], int m);                       //根据列进行可能取值排除
     int rm_block(int i, int j, element ele[][10], int m);                        //根据宫进行可能取值排除
     int set(int rnum, int cnum, int number, int m);                             //第一次设定（初始化对象数组）
     int selfcheck(int i, int j, element ele[][10], int m);                        //自我检查（如果possible_num的值和为2,把possible_num[0]设为0，num设为值，返回num）
     element() {
          num = 0;
          row_num = 0;
          column_num = 0;
          block_num = 0;
          for (int i = 0; i < 10; i++) possible_num[i] = 1;
     }
};
class row {};             //暂且无用，可做优化算法入口
class column {};          //暂且无用，可做优化算法入口
class block {};            //暂且无用，可做优化算法入口

int main(int argc, char *argv[])
{
     if (argc != 9) {     //检查是否按规则输入命令行参数
          cout << "请按规定输入：Sudoku.exe -m <阶数(3<=m<=9)> -n <需求解个数> -i <输入文件路径> -o <输出文件路径>" << endl;
          cout << "Press anykey to exit." << endl;
          getchar();
          exit(1);
     }
     cout << "输入文件: " << argv[6] << endl;
     cout << "输出文件: " << argv[8] << endl;
     int m, n;
     m = atoi(argv[2]);
     n = atoi(argv[4]);
     if (m < 3 || m>9) {
          cout << "请按规定输入：Sudoku.exe -m <阶数(3<=m<=9)> -n <需求解个数> -i <输入文件路径> -o <输出文件路径>" << endl;
          cout << "Press anykey to exit." << endl;
          getchar();
          exit(1);
     }
     fstream infile(argv[6], ios::in);       //指定输入文件流对象
     fstream outfile(argv[8], ios::out);     //指定输出文件流对象
     int i, j, k, number;
     element ele[10][10];
     if (!infile) {
          cout << "open input.txt error" << endl;
          exit(1);
     }
     for (k = 0; k < n; k++) {              //循环读入、输出n次
          for (i = 1; i <= m; i++) {
               for (j = 1; j <= m; j++) {
                    infile >> number;
                    ele[i][j].set(i, j, number, m);           //根据读入数独表设置元素表
               }
          }
          for (i = 1; i <= m; i++) {
               for (j = 1; j <= m; j++) {
                    cout << ele[i][j].num << ' ';             //输出读入的元素表（测试用）
               }
               cout << endl;
          }
          for (i = 1; i <= m; i++) {                          //排除行、列、区块并自我检测是否能确定值
               for (j = 1; j <= m; j++) {
                    ele[i][j].rm_row(i, j, ele, m);
                    ele[i][j].rm_column(i, j, ele, m);
                    ele[i][j].rm_block(i, j, ele, m);
                    ele[i][j].selfcheck(i, j, ele, m);
               }
          }
          cout << endl;
          for (i = 1; i <= m; i++) {                           //输出完成的数独表（测试用）
               for (j = 1; j <= m; j++) {
                    cout << ele[i][j].num << ' ';
               }
               cout << endl;
          }
          for (i = 1; i <= m; i++) {                           //输出到文件
               for (j = 1; j <= m; j++) {
                    outfile << ele[i][j].num << ' ';
               }
               outfile << endl;
          }
          cout << endl;
          outfile << endl;
     }
     return 0;
}

int element::set(int rnum, int cnum, int number, int m)
{
     int i;
     row_num = rnum;
     column_num = cnum;
     if (number > m) {                                           //输入数独表正确性判断
          cout << "表中数值不能大于阶数" << endl;
          exit(1);
     }
     if (number != 0) {                                          //确定的数值
          num = number;
          for (i = 0; i <= m; i++) {
               possible_num[i] = 0;
          }
          possible_num[number] = 1;
     }
     else {                                                     //输入值为0，重置可能性表和num
          num = 0;
          for (int k = 0; k < 10; k++) possible_num[k] = 1;
     }
     if (m == 4) {                                              //根据阶数判断块号
          if (rnum <= 2 && cnum <= 2)block_num = 1;
          if (rnum <= 2 && cnum > 2)block_num = 2;
          if (rnum > 2 && cnum <= 2)block_num = 3;
          if (rnum > 2 && cnum > 2)block_num = 4;
     }
     if (m == 6) {
          if (rnum <= 2 && cnum <= 3)block_num = 1;
          if (rnum <= 2 && cnum > 3)block_num = 2;
          if (rnum > 2 && rnum <= 4 && cnum <= 3)block_num = 3;
          if (rnum > 2 && rnum <= 4 && cnum > 3)block_num = 4;
          if (rnum > 4 && cnum <= 3)block_num = 5;
          if (rnum > 4 && cnum > 3)block_num = 6;
     }
     if (m == 8) {
          if (rnum <= 4 && cnum <= 2)block_num = 1;
          if (rnum <= 4 && cnum > 2 && cnum <= 4)block_num = 2;
          if (rnum <= 4 && cnum > 4 && cnum <= 6)block_num = 3;
          if (rnum <= 4 && cnum > 6)block_num = 4;
          if (rnum > 4 && cnum <= 2)block_num = 5;
          if (rnum > 4 && cnum > 2 && cnum <= 4)block_num = 6;
          if (rnum > 4 && cnum > 4 && cnum <= 6)block_num = 7;
          if (rnum > 4 && cnum > 6)block_num = 8;
     }
     if (m == 9) {
          if (rnum <= 3 && cnum <= 3)block_num = 1;
          if (rnum <= 3 && cnum > 3 && cnum <= 6)block_num = 2;
          if (rnum <= 3 && cnum > 6)block_num = 3;
          if (rnum > 3 && rnum <= 6 && cnum <= 3)block_num = 4;
          if (rnum > 3 && rnum <= 6 && cnum > 3 && cnum <= 6)block_num = 5;
          if (rnum > 3 && rnum <= 6 && cnum > 6)block_num = 6;
          if (rnum > 6 && cnum <= 3)block_num = 7;
          if (rnum > 6 && cnum > 3 && cnum <= 6)block_num = 8;
          if (rnum > 6 && cnum > 6)block_num = 9;
     }
     return 0;
}

int element::selfcheck(int i, int j, element ele[][10], int m)
{
     int s = 0;
     int t, k;
     int ci, cj;  //c:check，作为行，列，块排除循环参数
     for (t = 0; t <= m; t++) {
          s = s + ele[i][j].possible_num[t];
          if (ele[i][j].possible_num[t] != 0) {  //找最后一个可能的数值k
               k = t;
          }
     }
     if (s == 2) {    //如果可能数值唯一，则对其所在行，列，块排除该数并判断是否能确定元素值(element::selfcheck())，并设定num
          ele[i][j].num = k;
          ele[i][j].possible_num[0] = 0;//设为0则不可能再进入判断循环
          for (cj = 1; cj <= m; cj++) {
               ele[i][cj].rm_row(i, cj, ele, m);
               ele[i][cj].selfcheck(i, cj, ele, m);
          }
          for (ci = 1; ci <= m; ci++) {
               ele[ci][j].rm_column(ci, j, ele, m);
               ele[ci][j].selfcheck(ci, j, ele, m);
          }
          if (m == 4 || m == 6 || m == 8 || m != 9) {
               for (ci = 1; ci <= m; ci++) {
                    for (cj = 1; cj <= m; cj++) {
                         if (ele[i][j].block_num == ele[ci][cj].block_num) {
                              ele[ci][cj].rm_block(ci, cj, ele, m);
                              ele[ci][cj].selfcheck(ci, cj, ele, m);
                         }
                    }
               }
          }
     }
     return 0;
}

int element::rm_row(int i, int j, element ele[][10], int m)
{
     int t, f;
     for (t = 1; t <= m; t++) {
          if ((f = ele[i][t].num) != 0) {
               ele[i][j].possible_num[f] = 0;
          }
     }
     return 0;
}

int element::rm_column(int i, int j, element ele[][10], int m)
{
     int t, f;
     for (t = 1; t <= m; t++) {
          if ((f = ele[t][j].num) != 0) {
               ele[i][j].possible_num[f] = 0;
          }
     }
     return 0;
}

int element::rm_block(int i, int j, element ele[][10], int m)
{
     if (m != 4 && m != 6 && m != 8 && m != 9) {
          return 1;
     }
     int ci, cj, f;
     for (ci = 1; ci <= m; ci++) {
          for (cj = 1; cj <= m; cj++) {
               if ((ele[ci][cj].block_num == ele[i][j].block_num) && ((f = ele[ci][cj].num) != 0)) {
                    ele[i][j].possible_num[f] = 0;
               }
          }
     }
     return 0;
}