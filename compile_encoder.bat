g++ ^
                -g ^
                ./subbyte.cpp ^
                ./encrypt_block.cpp ^
                ./AES_Encoder.cpp ^
                ./shift_rows.cpp  ^
                ./logging_functions.cpp ^
                ./mix_columns.cpp ^
                ./add_round_key.cpp ^
                ./key_schedule.cpp ^
                ./inverse_subbyte.cpp ^
                ./inverse_mix_columns.cpp ^
                ./inverse_shift_rows.cpp ^
                ./decrypt_block.cpp ^
                ./function_manipulate_data.cpp ^
                ./function_related_to_program_arguments.cpp ^
                ./data_retrieval_and_insertion_into_mat.cpp ^
                ./function_related_to_text_file.cpp ^
                -o ^
                AES_Encoder.exe ^
                -I C:\OpenCV\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\include ^
                -L C:\OpenCV\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin ^
                -llibopencv_calib3d411 ^
                -llibopencv_core411 ^
                -llibopencv_dnn411 ^
                -llibopencv_features2d411 ^
                -llibopencv_flann411 ^
                -llibopencv_highgui411 ^
                -llibopencv_imgcodecs411 ^
                -llibopencv_imgproc411
                GOTO endcomment1
                -llibopencv_ml411 ^
                -llibopencv_objdetect411 ^
                -llibopencv_photo411 ^
                -llibopencv_stitching411 ^
                -llibopencv_video411 ^
                -llibopencv_videoio411
                :endcomment1