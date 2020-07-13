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
Mat encrypt_block(Mat, Mat);
Mat subbyte(Mat);
Mat shift_rows(Mat);
Mat mix_columns(Mat);
Mat add_round_key(Mat,Mat);
Mat key_schedule(Mat,unsigned int);
void find_keys(Mat);
void log_block(Mat);
void log(const char *);
void log_Mat_value(uint8_t);
Mat decrypt_block(Mat,Mat);
Mat inverse_mix_columns(Mat);
Mat inverse_subbyte(Mat);
Mat inverse_shift_rows(Mat);
Mat slice_of_data(Mat,int,int);
void put_back_together(Mat *, Mat, int, int);

//macros
#define ROWS 4
#define COLS 4

//globals
extern Mat * keys[11];