//403100043
#include <stdio.h>
#include <stdarg.h>
#include "grader.h"


double average(int n, ...) {
    va_list args;
    va_start(args, n);
    double average = 0;
    for(int i = 0; i < n; i++) {
        average += va_arg(args, double);        
    }
    va_end(args);
    average /= n;
    return average;
}

double variance(int n, ...) {
    double variance = 0, arr[100],av = 0, temp;
    va_list args;
    va_start(args , n);
    for(int i = 0; i < n; i++) {
        arr[i] = va_arg(args, double);
        av += arr[i];
    }
    av /= n;
    for(int i = 0; i < n; i++) {
        temp = arr[i] - av;
        temp *= temp;
        variance += temp;
    }
    va_end(args);

    variance /= n-1;
    return variance;
}

double calculate_a(int n, double average_x, double average_y, double average_xy, double variance_x) {
    double a;
    a = average_xy - (average_x * average_y);
    a *= n;
    a /= n-1;
    a /= variance_x;
    return a;
}

double calculate_b(double a, double average_x, double average_y) {
    double b;
    b = average_y - a * average_x;
    return b;
}
