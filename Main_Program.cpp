#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "Chi_distance.h"
#include "Queue.h"
#define WIDE 242
#define HIGH 393
// 对3x3图像应用LBP算法
void computeLBP(Queue& pixelQueue, int image[9]) {
    int centerIndex = 4;
    unsigned char centerValue = image[centerIndex];
    // 计算LBP编码
    for (int i = 0; i < 3; ++i) {
        pixelQueue.enqueue(image[i] >= image[centerIndex] ? 1 : 0);
    }
    pixelQueue.enqueue(image[5] >= image[centerIndex] ? 1 : 0);
    for (int i = 8; i >= 6; --i) {
        pixelQueue.enqueue(image[i] >= image[centerIndex] ? 1 : 0);
    }
    pixelQueue.enqueue(image[3] >= image[centerIndex] ? 1 : 0);
}
int binary_dec_Convert(char eigenvalue[9]) {
    int dec = 0;
    for (int i = 0; i < 8; ++i) {
        dec += eigenvalue[i] * pow(2, 7 - i);
    }
    return dec;
}
int Abstract_One_Area(int image[9]) {

    // 用于保存每个像素点的信息的队列
    Queue pixelQueue;

    char* eigenvalue = new char[8];
    int i = 0;
    // 遍历3x3图像，将每个像素点的灰度值比较结果入队列
    computeLBP(pixelQueue, image);
    while (!pixelQueue.isEmpty()) {
        eigenvalue[i] = pixelQueue.dequeue();
        ++i;
    }
    /*
    for (int i = 0; i < 8; i++) {
        std::cout << (int)eigenvalue[i];
    }
    */
    return binary_dec_Convert(eigenvalue);
}
void Get_Part(int Matrix[][WIDE], int i, int j, int image_part[]) {  //将Matrix[i][j]为中心的九宫格转化成一维数组保存到image中
    int p = 0;
    for (int k = i - 1; k <= i + 1; k++) {
        for (int s = j - 1; s <= j + 1; s++)
        {
            image_part[p] = Matrix[k][s];
            ++p;
        }
    }
}
void Get_Matrix(int Matrix[][WIDE]) {
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < WIDE; j++) {
            std::cin >> Matrix[i][j];
        }
    }
}
void Caculate(int Matrix[][WIDE], double histogram[256]) {
    int image[9];
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < WIDE; j++) {
            if (i != 0 && j != 0 && i != HIGH - 1 && j != WIDE - 1) {//去除边界
                Get_Part(Matrix, i, j, image);//获取九宫格
                histogram[Abstract_One_Area(image)] += 1;
            }
        }
    }
}
int main() {
    //输入一张图片的灰度矩阵，计算其特征值矩阵
    freopen("person5-2.txt", "r", stdin);//源文件
    double histogram1[256] = { 0 };//统计直方图，保存LBP特征正值的频次
    int Matrix1[HIGH][WIDE] = { 0 };
    Get_Matrix(Matrix1);   //先获取矩阵
    Caculate(Matrix1, histogram1);//计算矩阵每个像素点的LBP特征值，并把每个结果保存到统计直方图中
    for (int i = 0; i < 256; i++) {
        std::cout << histogram1[i] << ",";
    }

    freopen("person5-1.txt", "r", stdin);//源文件
    double histogram2[256] = { 0 };//统计直方图，保存LBP特征正值的频次
    int Matrix2[HIGH][WIDE] = { 0 };
    Get_Matrix(Matrix2);   //先获取矩阵
    Caculate(Matrix2, histogram2);//计算矩阵每个像素点的LBP特征值，并把每个结果保存到统计直方图中
    for (int i = 0; i < 256; i++) {
        std::cout << histogram2[i] << ",";
    }
    HistogramNormalization(histogram1, histogram2);
    std::cout<< std::endl;
    std::cout<< chiSquaredDistance(histogram1, histogram2)<<std::endl;
    return 0;
}
