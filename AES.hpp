//includes in the whole project
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

//prototypes of all function inside the project
Mat subbyte(Mat);
void encrypt_block();