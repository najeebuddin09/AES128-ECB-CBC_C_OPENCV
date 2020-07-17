#include "AES.hpp"

int main(int argc, char ** argv){
    #include "args_checks.hpp"
        
    if (strstr(file,".txt")!=NULL){
        //log("inside text file encryption condition");
        //check file existence
        fstream check_existence(file);
        if (!check_existence.is_open()){
            log("ERROR: Sorry this file does not exist");
            return 1;
        }
        check_existence.close();

        Mat key = retrieve_arg(argc,argv,"-key");
        
        //log("before reading from file");
        Mat data = read_and_copy_text_file_to_mat_object(file);
        Mat decrypted_data;
        //time_t time_start, time_end;
        struct timeval stop, start;
        //log("before condition check for mode");
        if (search_through_program_args(argc,argv,"-cbc")){
            Mat iv = retrieve_arg(argc,argv,"-iv");
            //time_start = time(NULL);
            gettimeofday(&start, NULL);
            decrypted_data = manipulate_data_any_size_cbc(data,key,iv,decrypt_block);
            //time_end = time(NULL);
            gettimeofday(&stop, NULL);
        } else {
            //time_start = time(NULL);
            gettimeofday(&start, NULL);
            decrypted_data = manipulate_data_any_size_ecb(data,key,decrypt_block);
            //time_end = time(NULL);
            gettimeofday(&stop, NULL);
        }
        const char * decrypted_file_name = "decrypted_file.txt";
        //log("before writing to file");
        convert_mat_object_into_string_and_store_it_in_a_file(decrypted_data,decrypted_file_name);
        cout<<decrypted_file_name<<" file created that contains the decrypted text"<<endl;
        cout<<"The decryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
    } else if (strstr(file,".png")!=NULL || strstr(file,".png")!=NULL){
        Mat image = imread(file,IMREAD_COLOR);    

        if (image.empty()){
            log("ERROR: Sorry the file does not exist");
            return 1;
        } 

        Mat splitChannels[3];
        Mat decrypted_splitChannels[3];
        Mat key = retrieve_arg(argc,argv,"-key");
        struct timeval stop, start;

        split(image, splitChannels);
        if (search_through_program_args(argc,argv,"-cbc")){
            //log("inside cbc");
            Mat iv = retrieve_arg(argc,argv,"-iv");
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                decrypted_splitChannels[i] = manipulate_data_any_size_cbc(splitChannels[i], key, iv, decrypt_block);
            }
            gettimeofday(&stop, NULL);
        } else {
            //log("inside ecb");
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                decrypted_splitChannels[i] = manipulate_data_any_size_ecb(splitChannels[i], key, decrypt_block);    
            }
            gettimeofday(&stop, NULL);
        }

        Mat decrypted_image;

        merge(decrypted_splitChannels, 3, decrypted_image);
        const char * decrypted_file_name = "decrypted_file.jpg";
        imwrite(decrypted_file_name,decrypted_image);
        cout<<decrypted_file_name<<" file created that contains the decrypted image"<<endl;
        cout<<"The decryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
    }
    return 0;
}
//AES_Decoder final implementation but its not working completely
/*
    #include "args_checks.hpp"
        
    if (strstr(file,".txt")!=NULL){
        //log("inside text file encryption condition");
        //check file existence
        fstream check_existence(file);
        if (!check_existence.is_open()){
            log("ERROR: Sorry this file does not exist");
            return 1;
        }
        check_existence.close();

        Mat key = retrieve_arg(argc,argv,"-key");
        
        //log("before reading from file");
        Mat data = read_and_copy_text_file_to_mat_object(file);
        Mat decrypted_data;
        //time_t time_start, time_end;
        struct timeval stop, start;
        //log("before condition check for mode");
        if (search_through_program_args(argc,argv,"-cbc")){
            Mat iv = retrieve_arg(argc,argv,"-iv");
            //time_start = time(NULL);
            gettimeofday(&start, NULL);
            decrypted_data = manipulate_data_any_size_cbc(data,key,iv,decrypt_block);
            //time_end = time(NULL);
            gettimeofday(&stop, NULL);
        } else {
            //time_start = time(NULL);
            gettimeofday(&start, NULL);
            decrypted_data = manipulate_data_any_size_ecb(data,key,decrypt_block);
            //time_end = time(NULL);
            gettimeofday(&stop, NULL);
        }
        const char * decrypted_file_name = "decrypted_file.txt";
        //log("before writing to file");
        convert_mat_object_into_string_and_store_it_in_a_file(decrypted_data,decrypted_file_name);
        cout<<decrypted_file_name<<" file created that contains the decrypted text"<<endl;
        cout<<"The decryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
    } else if (strstr(file,".jpg")!=NULL){
        Mat image = imread(file,IMREAD_COLOR);    

        if (image.empty()){
            log("ERROR: Sorry the file does not exist");
            return 1;
        } 

        Mat splitChannels[3];
        Mat decrypted_splitChannels[3];
        Mat key = retrieve_arg(argc,argv,"-key");
        struct timeval stop, start;

        split(image, splitChannels);
        if (search_through_program_args(argc,argv,"-cbc")){
            Mat iv = retrieve_arg(argc,argv,"-iv");
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                decrypted_splitChannels[i] = manipulate_data_any_size_cbc(splitChannels[i], key, iv, decrypt_block);    
            }
            gettimeofday(&stop, NULL);
        } else {
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                decrypted_splitChannels[i] = manipulate_data_any_size_ecb(splitChannels[i], key, decrypt_block);    
            }
            gettimeofday(&stop, NULL);
        }

        Mat decrypted_image;

        merge(decrypted_splitChannels, 3, decrypted_image);
        const char * decrypted_file_name = "decrypted_file.jpg";
        imwrite(decrypted_file_name,decrypted_image);
        cout<<decrypted_file_name<<" file created that contains the decrypted image"<<endl;
        cout<<"The decryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
   }
*/

// testing text encryption and decryption for cbc mode
/*
    const char * file_to_read = "text.txt";
    const char * file_to_write = "text_decrypted.txt";
    
    uint8_t test_block[ROWS][COLS] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };   

    Mat iv(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            iv.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    }
    
    Mat data = read_and_copy_text_file_to_mat_object(file_to_read);
    //log("data:");
    //log_block(data);
    Mat encrypted_data = manipulate_data_any_size_cbc(data,key,iv,encrypt_block);
    //log("encrypted data:");
    //log_block(encrypted_data);
    convert_mat_object_into_string_and_store_it_in_a_file(encrypted_data,"text_encrypted.txt");
    Mat encrypted_data_from_file = read_and_copy_text_file_to_mat_object("text_encrypted.txt");
    //log("encrypted data read from file:");
    //log_block(encrypted_data_from_file);
    Mat decrypted_data = manipulate_data_any_size_cbc(encrypted_data_from_file,key,iv,decrypt_block);
    //log("decrypted data:");
    //log_block(decrypted_data);
    convert_mat_object_into_string_and_store_it_in_a_file(decrypted_data,file_to_write);
*/
//testing image encryption and decryption in cbc mode
/*
    const char * file = "Linux_logo.jpg";
    uint8_t test_block[ROWS][COLS] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };   

    Mat iv(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            iv.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
 
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    }
   
    Mat image = imread(file,IMREAD_COLOR);     

    Mat splitChannels[3];
    Mat encrypted_splitChannels[3];
    Mat decrypted_splitChannels[3];

    split(image, splitChannels);

    for (int i=0; i<3; i++){
        encrypted_splitChannels[i] = manipulate_data_any_size_cbc(splitChannels[i], key, iv, encrypt_block);    
    }

    Mat encrypted_image;

    merge(encrypted_splitChannels, 3, encrypted_image);
    imshow("encrypted image", encrypted_image);
    
    for (int i=0; i<3; i++){
        decrypted_splitChannels[i] = manipulate_data_any_size_cbc(encrypted_splitChannels[i], key, iv, decrypt_block);    
    }

    Mat decrypted_image;

    merge(decrypted_splitChannels, 3, decrypted_image);
    imshow("decrypted image", decrypted_image);


    waitKey();
*/
// testing for text file encryption and decryption
/*
    const char * file_to_read = "text.txt";
    const char * file_to_write = "text_decrypted.txt";
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    }
    
    Mat data = read_and_copy_text_file_to_mat_object(file_to_read);
    //log("data:");
    //log_block(data);
    Mat encrypted_data = manipulate_data_any_size_ecb(data,key,encrypt_block);
    //log("encrypted data:");
    //log_block(encrypted_data);
    convert_mat_object_into_string_and_store_it_in_a_file(encrypted_data,"text_encrypted.txt");
    Mat encrypted_data_from_file = read_and_copy_text_file_to_mat_object("text_encrypted.txt");
    //log("encrypted data read from file:");
    //log_block(encrypted_data_from_file);
    Mat decrypted_data = manipulate_data_any_size_ecb(encrypted_data_from_file,key,decrypt_block);
    //log("decrypted data:");
    //log_block(decrypted_data);
    convert_mat_object_into_string_and_store_it_in_a_file(decrypted_data,file_to_write);
*/

/*
/
//testing image encryption and decryption
/*
    const char * file = "Linux_logo.jpg";
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    }
   
    Mat image = imread(file,IMREAD_COLOR);     

    Mat splitChannels[3];
    Mat encrypted_splitChannels[3];
    Mat decrypted_splitChannels[3];

    split(image, splitChannels);

    for (int i=0; i<3; i++){
        encrypted_splitChannels[i] = manipulate_data_any_size_ecb(splitChannels[i], key, encrypt_block);    
    }

    Mat encrypted_image;

    merge(encrypted_splitChannels, 3, encrypted_image);
    imshow("encrypted image", encrypted_image);
    
    for (int i=0; i<3; i++){
        decrypted_splitChannels[i] = manipulate_data_any_size_ecb(encrypted_splitChannels[i], key, decrypt_block);    
    }

    Mat decrypted_image;

    merge(decrypted_splitChannels, 3, decrypted_image);
    imshow("decrypted image", decrypted_image);


    waitKey();
*/
//test key and test block for testing
/*
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    } 
  
    uint8_t test_block[6][6] = {
        {0x32, 0x88, 0x31, 0xe0, 0x31, 0x31},
        {0x43, 0x5a, 0x31, 0x37, 0x31, 0x31},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31},
        {0xa8, 0x8d, 0xa2, 0x34, 0x31, 0x31},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31}
    };

    Mat block(6,6,CV_8UC1);
    for (int i=0; i<6; i++){
        for (int j=0; j<6; j++){
            block.at<uint8_t>(i,j) = test_block[i][j];
        }
    }
*/
//testing block encryption and decryption
/*
    uint8_t test_block[ROWS][COLS] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };

    Mat block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            block.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    } 
    
    log("block of data");
    log_block(block); 

    Mat encrypted_block = encrypt_block(block,key);
    
    log("block of data after encryption");
    log_block(encrypted_block); 
    
    Mat decrypted_block = decrypt_block(encrypted_block,key);
    
    log("block of data after decryption");
    log_block(decrypted_block); 

    return 0;
*/