#ifndef CENTRAL_DIRECTORY_H
#define CENTRAL_DIRECTORY_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

#include "Common.h"
#include "FileRecord.h"

using namespace std;

int readCentralDirectoryRecord(fstream& zipfile, vector<FileRecord>& centralFileHeaders, int cur_offset);
void writeCentralDirectoryRecord(fstream& infile, fstream& outfile, vector<FileRecord>& centralFileHeaders, vector<FileRecord> localFileHeaders, vector<char*>& pickFiles, int cd_offset);

#endif
/*
Offset   Length   Contents
  0      4 bytes  Central file header signature (0x02014b50)
  4      2 bytes  Version made by
  6      2 bytes  Version needed to extract
  8      2 bytes  General purpose bit flag
 10      2 bytes  Compression method
 12      2 bytes  Last mod file time
 14      2 bytes  Last mod file date
 16      4 bytes  CRC-32
 20      4 bytes  Compressed size
 24      4 bytes  Uncompressed size
 28      2 bytes  Filename length (f)
 30      2 bytes  Extra field length (e)
 32      2 bytes  File comment length (c)
 34      2 bytes  Disk number start
 36      2 bytes  Internal file attributes
 38      4 bytes  External file attributes
 42      4 bytes  Relative offset of local header//
 46     (f)bytes  Filename//
        (e)bytes  Extra field
        (c)bytes  File comment
*/

/*
      0 - The file is stored (no compression)
      1 - The file is Shrunk
      2 - The file is Reduced with compression factor 1
      3 - The file is Reduced with compression factor 2
      4 - The file is Reduced with compression factor 3
      5 - The file is Reduced with compression factor 4
      6 - The file is Imploded
      7 - Reserved for Tokenizing compression algorithm
      8 - The file is Deflated
*/
