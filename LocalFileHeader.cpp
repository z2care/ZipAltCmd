#include "LocalFileHeader.h"

int readLocalFileHeaderRecord(fstream& infile, vector<FileRecord> &localFileHeaders, int cur_offset){

    Byte tmpBuf2[2];
    Byte tmpBuf4[4];
    
    FileRecord lfh;
    lfh.signature = NSignature::kLocalFileHeader;
    lfh.offset = cur_offset;
    infile.seekg(14, ios::cur);

    infile.read((char *)&tmpBuf4, sizeof(tmpBuf4));
    UInt32 compressed_len = Get32(tmpBuf4);//transfer type here

    infile.seekg(4, ios::cur);//skip 4 byte for uncompress size value

    infile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 filename_len = Get16(tmpBuf2);
    lfh.filename_len = filename_len;

    infile.read((char *)&tmpBuf2, sizeof(tmpBuf2));
    UInt16 extra_filed_len = Get16(tmpBuf2);

    //whatever store but never short than filename_len,
    //and add 1 byte for eof of string
    lfh.filename = new char[filename_len+1]{};
    infile.read((char *)lfh.filename, filename_len);

    infile.seekg(compressed_len + extra_filed_len, ios::cur);

    lfh.total = 30 + filename_len + compressed_len + extra_filed_len;
    lfh.taken = 0;
    localFileHeaders.push_back(lfh);

    cur_offset += lfh.total;
    return cur_offset;
}

void writeLocalFileHeaderRecord(fstream& infile, fstream& outfile, vector<FileRecord>& localFileHeaders, vector<char*>& pickFiles){

    for (auto itrf = pickFiles.cbegin(); itrf != pickFiles.cend(); itrf++) {

        for (vector<FileRecord>::iterator itrl = localFileHeaders.begin(); itrl != localFileHeaders.end(); itrl++) {
            if(strncmp((*itrf), (*itrl).filename, (*itrl).filename_len) == 0){
                infile.seekg(((*itrl).offset), ios::beg);

                char* temp = new char[(*itrl).total]{};//whatever store but never short than filename_len
                infile.read((char *)temp, (*itrl).total);//read content in total size byte

                (*itrl).offset = outfile.tellp();
                outfile.write((const char *)temp, (*itrl).total);//write to target file
                (*itrl).taken = 1;//mark this localfile taken = 1

                delete[] temp;
                break;
            }
        }
    }

    for (vector<FileRecord>::iterator itrl = localFileHeaders.begin(); itrl != localFileHeaders.end(); itrl++) {
        if((*itrl).taken==0){
            infile.seekg(((*itrl).offset), ios::beg);//input file offset

            char* temp = new char[(*itrl).total]{};
            infile.read((char *)temp, (*itrl).total);

            (*itrl).offset = outfile.tellp();//change to output file offset
            
            outfile.write((const char *)temp, (*itrl).total);            
        }
    }
}