#ifndef APK_SIGNING_BLOCK_H
#define APK_SIGNING_BLOCK_H

#include <fstream>

#include "Common.h"

using namespace std;
int readApkSigningBlock(fstream& infile, int sig_offset, int* sig_total_size);
void writeApkSigningBlock(fstream& infile, fstream& outfile, int sig_offset, int sig_size);
        // FORMAT:
        // OFFSET       DATA TYPE  DESCRIPTION
        // * @+0  bytes uint64:    size in bytes (excluding this field)
        // * @+8  bytes pairs
        // * @-24 bytes uint64:    size in bytes (same as the one above)
        // * @-16 bytes uint128:   magic
#endif
