#include "ZipAltCmd.h"
#include "LocalFileHeader.h"
#include "CentralDirectory.h"
#include "CentralDirectoryEnd.h"

using namespace std;

vector<FileRecord> localFileHeaders;
vector<FileRecord> centralFileHeaders;
vector<char*> pickFiles;

void help(){
    cout<<"help:"<<endl;
    cout<<"ZipAltCmd.exe <in_zip> <out_zip> <list.txt>"<<endl;
    cout<<"1. never suppport signed apk 2. list.txt without empty line"<<endl;
}

int main(int argc, char **argv){
    if(argc < 4){
        help();
        return -1;
    }

    fstream filelist(argv[3], ios::in | ios::binary);
    if(filelist.fail()){
        cout<<"can't open filelist file"<<endl;
        return -1;
    }

    while(!filelist.eof()){
        char* filename = new char[64]{};
        filelist.getline(filename, 63);
        pickFiles.push_back(filename);
    }
    filelist.close();

    fstream infile(argv[1], ios::in | ios::binary);
    if(infile.fail()){
        cout<<"can't open zip file"<<endl;
        return -1;
    }

    //"E:\\PracticeWork\\ZipModify\\newtest.zip"
    fstream outfile(argv[2], ios::out | ios::binary);
    if(outfile.fail()){
        cout<<"can't open newzip file"<<endl;
        return -1;
    }

    Byte startBuf[4];//zip marker size is 4 byte
    int cur_pos = 0;
    int cd_offset = 0;
    int sig_offset = -1;
    UInt64 sig_size = 0;
    while(infile.peek() != EOF){
        infile.read((char*)startBuf, sizeof(startBuf));
        UInt32 value = Get32(startBuf);
        if(value == NSignature::kLocalFileHeader){
            cur_pos = readLocalFileHeaderRecord(infile, localFileHeaders, cur_pos);
        }else if(value == NSignature::kCentralFileHeader){
            cur_pos = readCentralDirectoryRecord(infile, centralFileHeaders, cur_pos);
        }else if(value == NSignature::kEcd){
            cd_offset = readCentralDirectoryEndRecord(infile, centralFileHeaders, cur_pos);
        }else{
            infile.seekg(cur_pos-4, ios::beg);
            sig_offset = infile.tellg();
            Byte tmpBuf8[8];
            infile.read((char*)tmpBuf8, sizeof(tmpBuf8));
            sig_size = Get64(tmpBuf8);
            infile.seekg(value, ios::cur);


            cout<<value<<endl;
            cout<< "No zip marker found.skiip 1006."<<endl;
            cur_pos = infile.tellg();
            break;
        }
    }
    //infile.close();

    int exp_offset = 0;
    writeLocalFileHeaderRecord(infile, outfile, localFileHeaders, pickFiles);
    if(sig_offset != -1){
        char* sig_temp = new char[sig_size]{};//whatever store but never short than filename_len
        infile.read((char *)sig_temp, sig_size);//read content in total size byte

        outfile.write((const char *)sig_temp, sig_size);//write to target file
    }
    writeCentralDirectoryRecord(infile, outfile, centralFileHeaders, localFileHeaders, pickFiles, cd_offset);
    infile.close();
    outfile.close();    
    return 0;
}
