#include "CentralDirectoryEnd.h"

int readCentralDirectoryEndRecord(fstream& zipfile, vector<FileRecord>& centralFileHeaders, int cur_offset, int* cd_offset){
    Byte tmpBuf2[2];
    Byte tmpBuf4[4];
    FileRecord efh;
    efh.signature = NSignature::kEcd;
    efh.offset = cur_offset;
    zipfile.seekg(12, ios::cur);

    zipfile.read((char *)&tmpBuf4, sizeof(tmpBuf4));
    *cd_offset = Get32(tmpBuf4);

    zipfile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 comment_len = Get16(tmpBuf2);
    
    zipfile.seekg(comment_len, ios::cur);

    efh.total = 22 + comment_len;
    efh.taken = 0;
    centralFileHeaders.push_back(efh);
    
    cur_offset += efh.total;

    return cur_offset;
}