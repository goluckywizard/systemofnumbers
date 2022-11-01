#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SYSTEM 16
#define MIN_SYSTEM 2

int char_to_num (unsigned char c, int p1) {
    int x;
    if (isdigit(c)) {
        x = c - '0';
    }
    else {
        c = tolower(c);
        x = c - 'a' + 10;
    }
    if (x < 0 || x >= p1) {
        printf ("bad input");
        exit(0);
    }
    return x;
}

int num_to_char (int x) {
    if (x < 10)
        return (x + '0');
    return (x + 'A' - 10);
}

double str_to_num(const char *number, int p1) {
    long long result = 0;
    double st = 1 / (double) p1;
    int i = 0;
    if (number[i] == '-')
        ++i;
    while (number[i] != '.' && number[i] != 0) {
        result = result * p1 + char_to_num(number[i], p1);
        ++i;
    //    printf("%lld\n", result);
    }

    double result2 = 0;
    //printf ("%s", number);
    if (number[i] == '.') {
        ++i;
        if (number[i] == 0) {
            printf("bad input");
            exit(0);
        }
        while (number[i] != 0) {
            //printf("%d ", i);
            result2 += char_to_num(number[i], p1) * st;
            st = st / (double) p1;
            ++i;
        }
    }
    if (number[0] == '-')
        return -result - result2;
    return result + result2;
}

void num_to_str (char *str, double x, int p2) {
    int i = 0;
    long long y = (long long) floor(x);
    double fract;

    if (x > 0)
        fract = x - floor(x);
    else
        fract = -1 * x - floor(fabs(x));

    if (y < 0) {
        i++;
        y *= -1;
        if (fract != 0)
            y--;
    }

    int max_whole_index;
    if (y == 0) {
        str[i] = '0';
        i++;
    }
    while (y > 0) {
        str[i] = num_to_char(y % p2);
        ++i;
        y /= p2;
    }
    max_whole_index = i - 1;

    int min_whole_index = 0;
    if (x < 0){
        str[0] = '-';
        min_whole_index++;
    }
    //printf("%d %d\n", min_whole_index, max_whole_index);
    for (int j = 0; j < (max_whole_index - min_whole_index + 1) / 2; ++j) {
        char temp_c;
        temp_c = str[j + min_whole_index];
        int swap_index = max_whole_index - j + min_whole_index;
        str[j + min_whole_index] = str[swap_index];
        str[swap_index] = temp_c;
    }
    //printf("%s\n", str);
    if (fract != 0) {
        str[i] = '.';
        ++i;
    }
    while (fract > 0) {
        fract *= p2;
        str[i] = num_to_char((int)floor(fract));
        fract -= floor(fract);
        ++i;
    }
    str[i] = 0;
}

int main(void) {
    double x;
    int p1;
    int p2;
    char str1[256];
    char str2[256];
    if (scanf("%d%d", &p1, &p2) != 2) {
        printf("bad input\n");
        exit(0);
    }
    if (scanf("%255s", str1) != 1) {
        printf("bad input\n");
        exit(0);
    }
    if (p1 < MIN_SYSTEM || p1 > MAX_SYSTEM || p2 < MIN_SYSTEM || p2 > MAX_SYSTEM) {
        printf("bad input");
        exit(0);
    }
    x = str_to_num(str1, p1);
    //printf("%lf\n", x);
    num_to_str(str2, x, p2);

    printf("%s\n", str2);
    return 0;
}
