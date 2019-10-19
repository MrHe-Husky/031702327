#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
     int in, out, m = -1, n = -1, i, get, count=0;//count统计共有多少个换行符
     char ch;
     char* ff;
     string strp, strpp;//输入后单词存入strp中，其间以‘ ’分隔
 /*    for (i = 1; i < argc; i++) {
          cout << argv[i] << endl;
     }
 *///测试用码
     for (i = 1; i < argc; i++) {
          ff = argv[i];
          if ((get = strcmp("-i", ff)) == 0) {
               in = i + 1;
          }
          if ((get = strcmp("-o", ff)) == 0) {
               out = i + 1;
          }
          if ((get = strcmp("-m", ff)) == 0) {
               m = atoi(argv[i + 1]);
          }
          if ((get = strcmp("-n", ff)) == 0) {
               n = atoi(argv[i + 1]);
          }
     }
     fstream infile(argv[in], ios::in);       //指定输入文件流对象
     fstream outfile(argv[out], ios::out);     //指定输出文件流对象.
     //连续读入单词，中间以空格分割
     infile >> strp; 
     while (infile >> strpp) {
          strp = strp + ' ' +  strpp;
     }

     infile.clear();
     infile.seekg(0, ios::beg);
     while (1) {
          if ((ch = infile.get()) == '\n') {
               count++;
          }
          else if (ch == EOF) {
               break;
          }
     }
     cout << strp << endl;//用于在cmd中查看结果
     cout << count;//输出共有几行
}
