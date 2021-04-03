#include "ApkSigningBlock.h"

int readApkSigningBlock(fstream& infile, int sig_offset, int* sig_total_size){

    infile.seekg(sig_offset, ios::beg);

	Byte tmpBuf8[8];    
    infile.read((char*)tmpBuf8, sizeof(tmpBuf8));    
    int sig_size = Get64(tmpBuf8);
    *sig_total_size = sig_size + 8;

    infile.seekg(sig_size, ios::cur);
    return infile.tellg();
}

void writeApkSigningBlock(fstream& infile, fstream& outfile, int sig_offset, int sig_size){

    infile.seekg(sig_offset, ios::beg);

    char* sig_temp = new char[sig_size]{};//whatever store but never short than filename_len
    infile.read((char *)sig_temp, sig_size);//read content in total size byte

    outfile.write((const char *)sig_temp, sig_size);//write to target file
}