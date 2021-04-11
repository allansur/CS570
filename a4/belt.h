#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <vector>

typedef struct {
    int curr_CFB;
    int curr_EES;
    int total;
    vector<int> buffer();
} BELT;