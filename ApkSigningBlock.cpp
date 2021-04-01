#include "ApkSigningBlock.h"

int readApkSigningBlock(fstream& infile, int cur_offset){
	Byte tmpBuf8[8];
    infile.read((char*)tmpBuf8, sizeof(tmpBuf8));
    sig_size = Get64(tmpBuf8);
    infile.seekg(sig_size, ios::cur);
    return sig_size;
}

void writeApkSigningBlock(fstream& infile, fstream& outfile, int sig_size){
    char* sig_temp = new char[sig_size]{};//whatever store but never short than filename_len
    infile.read((char *)sig_temp, sig_size);//read content in total size byte

    outfile.write((const char *)sig_temp, sig_size);//write to target file
}