#ifndef CENTRAL_DIRECTORY_END_H
#define CENTRAL_DIRECTORY_END_H

#include <iostream>
#include <fstream>
#include <vector>
#include "FileRecord.h"
#include "Common.h"

using namespace std;

int readCentralDirectoryEndRecord(fstream& zipfile, vector<FileRecord>& centralFileHeaders, int cur_offset, int* cd_offset);
int readZip64CentralDirectoryEndRecord();
int readZip64CentralDirectoryEndLocator();

#endif

/*
Offset	Length	Description
0	4	zip64 end of central dir signature		0x06064b50
4	8	size of zip64 end of central directory record		
12	2	version made by		
14	2	version needed to extract		
16	4	number of this disk		
20	4	number of the disk with the start of the central directory		
24	8	total number of entries in the central directory on this disk		
32	8	total number of entries in the central directory		
40	8	size of the central directory		
48	8	offset of start of central directory with respect to the starting disk number		
56		zip64 extensible data sector
*/

/*
Offset	Length	Description
0	4	zip64 end of central dir locator signature		0x07064b50
4	4	number of the disk with the start of the zip64 end of central directory		
8	8	relative offset of the zip64 end of central directory record		
16	4	total number of disks
*/

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