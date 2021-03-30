#ifndef FILERECORD_H
#define FILERECORD_H

class FileRecord{
    public:
    unsigned int signature;
    char* filename;
    int filename_len;
    int offset;//without signature 4 byte
    int total;
    int taken;
};

#endif