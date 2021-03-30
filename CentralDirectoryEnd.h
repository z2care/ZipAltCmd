#ifndef CENTRAL_DIRECTORY_END_H
#define CENTRAL_DIRECTORY_END_H

#include <iostream>
#include <fstream>
#include <vector>
#include "FileRecord.h"
#include "Common.h"

using namespace std;

int readCentralDirectoryEndRecord(fstream& zipfile, vector<FileRecord>& centralFileHeaders, int cur_offset);

#endif

/*End of central directory record
Offset   Length   Contents
  0      4 bytes  End of central dir signature (0x06054b50)
  4      2 bytes  Number of this disk
  6      2 bytes  Number of the disk with the start of the central directory
  8      2 bytes  Total number of entries in the central dir on this disk
 10      2 bytes  Total number of entries in the central dir
 12      4 bytes  Size of the central directory
 16      4 bytes  Offset of start of central directory with respect to the starting disk number
 20      2 bytes  zipfile comment length (c)
 22     (c)bytes  zipfile comment
*/