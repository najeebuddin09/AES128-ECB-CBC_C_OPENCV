if (!search_through_program_args(argc,argv,"-f") || (!search_through_program_args(argc,argv,"-ecb") && !search_through_program_args(argc,argv,"-cbc")) || !search_through_program_args(argc,argv,"-key") || (search_through_program_args(argc,argv,"-cbc") && !search_through_program_args(argc,argv,"-iv"))){
    log("ERROR: Please provide the correct arguments");
    log("Usage: [AES_Encoder/AES_Decoder].exe -f [file_name.txt/.jpg] -[ecb/cbc] -key [key in hex] -iv(in case of -cbc) [iv in hex]");
    return 1;
}
const char * file = argv[search_through_program_args(argc,argv,"-f")+1];

if (strstr(file,".txt")==NULL && strstr(file,".png")==NULL && strstr(file,".jpg")==NULL){
    log("ERROR: Sorry this program can only Encrypt a txt or jpg or png file");
    return 1;
}

if (strlen(argv[search_through_program_args(argc,argv,"-key")+1]) != 32){
    log("ERROR: Key is not of the right length i.e 32 characters");
    return 1;
}

if (search_through_program_args(argc,argv,"-cbc") && strlen(argv[search_through_program_args(argc,argv,"-iv")+1]) != 32){
    log("ERROR: Initialization Vector is not of the right length i.e 32 characters");
    return 1;
}

