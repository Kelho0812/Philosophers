#include "../include/philosophers.h"

long long get_current_time() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    long long milliseconds = (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;

    return milliseconds;
}
