#include "ZipAltCmd.h"
#include "LocalFileHeader.h"
#include "CentralDirectory.h"
#include "CentralDirectoryEnd.h"
#include "ApkSigningBlock.h"

using namespace std;

vector<FileRecord> localFileHeaders;
vector<FileRecord> centralFileHeaders;
vector<char*> pickFiles;

void help(){
    cout<<"help:"<<endl;
    cout<<"ZipAltCmd.exe <in_zip> <out_zip> <list.txt>"<<endl;
    cout<<"1. list.txt without empty line 2. list.txt must put AndroidManifest.xml on top"<<endl;
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

    fstream outfile(argv[2], ios::out | ios::binary);
    if(outfile.fail()){
        cout<<"can't open newzip file"<<endl;
        return -1;
    }

    Byte startBuf[4];//zip marker size is 4 byte
    int cur_pos = 0;
    int cd_offset = 0;
    int sig_size = 0;
    int sig_offset = 0;
    while(infile.peek() != EOF){
        infile.read((char*)startBuf, sizeof(startBuf));
        UInt32 value = Get32(startBuf);
        if(value == NSignature::kLocalFileHeader){
            cur_pos = readLocalFileHeaderRecord(infile, localFileHeaders, cur_pos);
        }else if(value == NSignature::kCentralFileHeader){
            cd_offset = cur_pos;
            cur_pos = readCentralDirectoryRecord(infile, centralFileHeaders, cur_pos);
        }else if(value == NSignature::kEcd){
            cur_pos = readCentralDirectoryEndRecord(infile, centralFileHeaders, cur_pos);
        }else{
            if(!infile.eof()){
                sig_offset = cur_pos;
                cout<<"Apk signing block exist."<<endl;
                cur_pos = readApkSigningBlock(infile, cur_pos, &sig_size);
            }else{
                cout<<value<<endl;
                cout<< "No zip marker found.skiip 1006."<<endl;
                break;
            }            
        }
    }

    int exp_offset = 0;
    writeLocalFileHeaderRecord(infile, outfile, localFileHeaders, pickFiles);
    if(sig_size != 0){
        writeApkSigningBlock(infile, outfile, sig_offset, sig_size);
    }
    writeCentralDirectoryRecord(infile, outfile, centralFileHeaders, localFileHeaders, pickFiles, cd_offset);
    infile.close();
    outfile.close();    
    return 0;
}
