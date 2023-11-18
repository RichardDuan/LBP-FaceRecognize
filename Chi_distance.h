#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#define HISTOGRAM_LENGTH 256

void HistogramNormalization(double hist1[], double hist2[]) {
    int MinHistogram1 = 0;
    int MaxHistogram1 = 0;
    int MinHistogram2 = 0;
    int MaxHistogram2 = 0;
    for (int i = 0; i < HISTOGRAM_LENGTH; i++) {
        if (hist1[i] > MaxHistogram1)
            MaxHistogram1 = hist1[i];
        if (hist1[i] < MinHistogram1)
            MinHistogram1 = hist1[i];

    }
    for (int i = 0; i < HISTOGRAM_LENGTH; i++) {
        hist1[i] = hist1[i] / (MaxHistogram1 - MinHistogram1);

    }
    for (int i = 0; i < HISTOGRAM_LENGTH; i++) {
        if (hist2[i] > MaxHistogram2)
            MaxHistogram2 = hist2[i];
        if (hist1[i] < MinHistogram2)
            MinHistogram2 = hist2[i];

    }
    for (int i = 0; i < HISTOGRAM_LENGTH; i++) {
        hist2[i] = hist2[i] / (MaxHistogram2 - MinHistogram2);

    }
}

double chiSquaredDistance(double hist1[], double hist2[]) {
    double chiSquared = 0.0;

    for (int i = 0; i < HISTOGRAM_LENGTH; ++i) {
        double diff = hist1[i] - hist2[i];
        if (hist1[i] != 0 && hist2[i] != 0)
            chiSquared += (diff * diff) / (hist1[i] + hist2[i]); // ¼ÆËã¿¨·½Öµ
    }

    return chiSquared;
}