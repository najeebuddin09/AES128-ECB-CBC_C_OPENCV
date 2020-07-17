# AES128-ECB-CBC_C_OPENCV
Computer Security project - implementation of AES128 both ECB and CBC mode in C++ language using OpenCV

# Usage:
[AES_Encoder/AES_Decoder].exe -f [file_name.txt/.jpg] -[ecb/cbc] -key [key in hex] -iv(in case of -cbc) [iv in hex]
e.g
.\AES_Encoder.exe -f text.txt -cbc -key 2b28ab097eaef7cf15d2154f16a6883c -iv 328831e0435a3137f6309807a88da234

# Output:
In case of text encoding, after running the program "encrypted_file.txt" file will be generated that contains encrypted text
In case of image encoding, after running the program "encrypted_file.png" file will be generated that contains encrypted image
the output file is in png format because jpg use lossy compression and it cannot be decrypted
In case of text decoding, after running the program "decrypted_file.txt" file will be generated that contains decrypted text
In case of image decoding, after running the program "decrypted_file.jpg" file will be generated that contains decrypted image

The program also prints the time (in micro seconds) it took to encrypt/decrypt the provided file

# Implementation:
Relevent functions are divided into seperate files
AES.hpp contains all the prototypes of the functions
other header files are created to avoid code redundancy
AES_decoder.cpp and AES_Encoder.cpp contains the 'main' function for decoding and encoding programs respectively

# Compilation:
For compilation change the include and bin directory addresses of opencv in compile_decoder.bat and compile_encoder.bat files
Also add include and bin director addresses of opencv to system path variable
For trying out code in VS Code also add the opencv include address to includepath in c_cpp_properties.json file under .vscode
folder in project directory

For compilation use the following commands:
for decoder
.\compile_decoder.bat
for encoder
.\compile_encoder.bat

# Timings:
This program take the following time (on average) while encrypting and decrypting

-ECB
Encoding 0.025MB/S
Decoding 0.020MB/S
-CBC
Encoding 0.022MB/S
Decoding 0.018MB/S