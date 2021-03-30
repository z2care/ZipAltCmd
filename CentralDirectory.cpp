#include "CentralDirectory.h"

int readCentralDirectoryRecord(fstream& zipfile, vector<FileRecord>& centralFileHeaders, int cur_offset){

    Byte tmpBuf2[2];
    Byte tmpBuf4[4];

    FileRecord cfh;
    cfh.signature = NSignature::kCentralFileHeader;
    cfh.offset = cur_offset;
    zipfile.seekg(24, ios::cur);

    zipfile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 filename_len = Get16(tmpBuf2);
    cfh.filename_len = filename_len;

    zipfile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 extra_filed_len = Get16(tmpBuf2);

    zipfile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 file_comment_len = Get16(tmpBuf2);

    zipfile.seekg(12, ios::cur);//skip 12 byte

    cfh.filename = new char[filename_len+1]{};//whatever store but never short than filename_len
    zipfile.read((char *)cfh.filename, filename_len);
    
    zipfile.seekg(extra_filed_len + file_comment_len, ios::cur);

    cfh.total = 46 + filename_len + extra_filed_len + file_comment_len;
    cfh.taken = 0;
    centralFileHeaders.push_back(cfh);
    cur_offset += cfh.total;
    return cur_offset;
}

void writeCentralDirectoryRecord(fstream& infile, fstream& outfile, vector<FileRecord>& centralFileHeaders, vector<FileRecord> localFileHeaders, vector<char*>& pickFiles, int cd_offset){

    for (auto itrf = pickFiles.cbegin(); itrf != pickFiles.cend(); itrf++) {
        for (vector<FileRecord>::iterator itrc = centralFileHeaders.begin(),itrl = localFileHeaders.begin(); itrc != centralFileHeaders.end(); itrc++, itrl++) {

            if(strncmp((*itrf), (*itrc).filename, (*itrc).filename_len) == 0){
                infile.seekg(((*itrc).offset), ios::beg);

                char* temp = new char[(*itrc).total]{};//whatever store but never short than filename_len
                infile.read((char *)temp, (*itrc).total);//read content in total size byte
                Set32((temp + 42), (*itrl).offset);

                outfile.write((const char *)temp, (*itrc).total);//write to target file
                (*itrc).taken = 1;//mark this localfile taken = 1

                delete[] temp;
                break;
            }
        }
    }

    for (auto itrc = centralFileHeaders.cbegin(), itrl = localFileHeaders.cbegin(); itrc != centralFileHeaders.cend(); itrc++, itrl++) {
        if((*itrc).taken==0){
            infile.seekg((*itrc).offset, ios::beg);

            char* temp = new char[(*itrc).total]{};
            infile.read((char *)temp, (*itrc).total);
            
            Set32((temp + 42), (*itrl).offset);

            outfile.write((const char *)temp, (*itrc).total);
        }
    }
}