#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "Chi_distance.h"
#include "Queue.h"
#define WIDE 242
#define HIGH 393
// ��3x3ͼ��Ӧ��LBP�㷨
void computeLBP(Queue& pixelQueue, int image[9]) {
    int centerIndex = 4;
    unsigned char centerValue = image[centerIndex];
    // ����LBP����
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

    // ���ڱ���ÿ�����ص����Ϣ�Ķ���
    Queue pixelQueue;

    char* eigenvalue = new char[8];
    int i = 0;
    // ����3x3ͼ�񣬽�ÿ�����ص�ĻҶ�ֵ�ȽϽ�������
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
void Get_Part(int Matrix[][WIDE], int i, int j, int image_part[]) {  //��Matrix[i][j]Ϊ���ĵľŹ���ת����һά���鱣�浽image��
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
            if (i != 0 && j != 0 && i != HIGH - 1 && j != WIDE - 1) {//ȥ���߽�
                Get_Part(Matrix, i, j, image);//��ȡ�Ź���
                histogram[Abstract_One_Area(image)] += 1;
            }
        }
    }
}
int main() {
    //����һ��ͼƬ�ĻҶȾ��󣬼���������ֵ����
    freopen("person5-2.txt", "r", stdin);//Դ�ļ�
    double histogram1[256] = { 0 };//ͳ��ֱ��ͼ������LBP������ֵ��Ƶ��
    int Matrix1[HIGH][WIDE] = { 0 };
    Get_Matrix(Matrix1);   //�Ȼ�ȡ����
    Caculate(Matrix1, histogram1);//�������ÿ�����ص��LBP����ֵ������ÿ��������浽ͳ��ֱ��ͼ��
    for (int i = 0; i < 256; i++) {
        std::cout << histogram1[i] << ",";
    }

    freopen("person5-1.txt", "r", stdin);//Դ�ļ�
    double histogram2[256] = { 0 };//ͳ��ֱ��ͼ������LBP������ֵ��Ƶ��
    int Matrix2[HIGH][WIDE] = { 0 };
    Get_Matrix(Matrix2);   //�Ȼ�ȡ����
    Caculate(Matrix2, histogram2);//�������ÿ�����ص��LBP����ֵ������ÿ��������浽ͳ��ֱ��ͼ��
    for (int i = 0; i < 256; i++) {
        std::cout << histogram2[i] << ",";
    }
    HistogramNormalization(histogram1, histogram2);
    std::cout<< std::endl;
    std::cout<< chiSquaredDistance(histogram1, histogram2)<<std::endl;
    return 0;
}
