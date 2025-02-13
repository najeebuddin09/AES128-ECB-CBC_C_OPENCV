//includes in the whole project
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <math.h>
#include <string.h>
#include <sys/time.h>

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
Mat manipulate_data_any_size_ecb(Mat,Mat, Mat callback_function(Mat,Mat));
int char_count(fstream *);
Mat read_and_copy_text_file_to_mat_object(const char * );
void convert_mat_object_into_string_and_store_it_in_a_file(Mat, const char *);
Mat manipulate_data_any_size_cbc(Mat, Mat , Mat , Mat callback_function(Mat,Mat));
int search_through_program_args(int , char ** , const char * );
Mat retrieve_arg(int , char ** , const char * );

//macros
#define ROWS 4
#define COLS 4

//globals
extern Mat * keys[11];