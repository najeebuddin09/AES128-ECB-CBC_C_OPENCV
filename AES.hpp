//includes in the whole project
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <stdio.h>

//namespaces that is used in the project
using namespace std;
using namespace cv;

//prototypes of all function inside the project
void encrypt_block();
Mat subbyte(Mat);
Mat shift_rows(Mat);
Mat mix_columns(Mat);
Mat add_round_key(Mat,Mat);
Mat key_schedule(Mat);
void log_block(Mat);
void log(const char *);
void log_Mat_value(uint8_t);

//macros
#define ROWS 4
#define COLS 4