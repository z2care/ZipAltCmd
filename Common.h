#ifndef COMMON_H
#define COMMON_H

typedef unsigned char Byte;

typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long UInt64;

#define GetUi16(p) (*(const UInt16 *)(const void *)(p))
#define Get16(p) GetUi16(p)

#define GetUi32(p) (*(const UInt32 *)(const void *)(p))
#define Get32(p) GetUi32(p)

#define GetUi64(p) (*(const UInt64 *)(const void *)(p))
#define Get64(p) GetUi64(p)

#define SetUi32(p, v) { *(UInt32 *)(p) = (v); }
#define Set32(p, d) SetUi32(p, d)

namespace NSignature
{
    const UInt32 kLocalFileHeader   = 0x04034B50;
    const UInt32 kDataDescriptor    = 0x08074B50;
    const UInt32 kCentralFileHeader = 0x02014B50;
    const UInt32 kEcd               = 0x06054B50;
    const UInt32 kEcd64             = 0x06064B50;
    const UInt32 kEcd64Locator      = 0x07064B50;
    const UInt32 kSpan              = 0x08074B50;
    const UInt32 kNoSpan            = 0x30304B50; // PK00, replaces kSpan, if there is only 1 segment
}

#endif