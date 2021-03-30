#ifndef LOCALFILE_HEADER_H
#define LOCALFILE_HEADER_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

#include "Common.h"
#include "FileRecord.h"

using namespace std;

int readLocalFileHeaderRecord(fstream& zipfile, vector<FileRecord> &localFileHeaders, int cur_offset);
void writeLocalFileHeaderRecord(fstream& infile, fstream& outfile, vector<FileRecord>& localFileHeaders, vector<char*>& pickFiles);

#endif
/*
Offset   Length   Contents
  0      4 bytes  Local file header signature (0x04034b50)
  4      2 bytes  Version needed to extract
  6      2 bytes  General purpose bit flag
  8      2 bytes  Compression method
 10      2 bytes  Last mod file time
 12      2 bytes  Last mod file date
 14      4 bytes  CRC-32
 18      4 bytes  Compressed size (n)
 22      4 bytes  Uncompressed size
 26      2 bytes  Filename length (f)
 28      2 bytes  Extra field length (e)
        (f)bytes  Filename
        (e)bytes  Extra field
        (n)bytes  Compressed data
*/