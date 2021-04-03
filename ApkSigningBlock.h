#ifndef APK_SIGNING_BLOCK_H
#define APK_SIGNING_BLOCK_H

#include <fstream>

#include "Common.h"

using namespace std;
int readApkSigningBlock(fstream& infile, int sig_offset, int* sig_size);
void writeApkSigningBlock(fstream& infile, fstream& outfile, int sig_offset, int sig_size);

#endif