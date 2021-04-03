[中文页](README_CN.md) | English

[![GitHub release](https://img.shields.io/github/release/z2care/ZipAltCmd.svg)](https://github.com/z2care/ZipAltCmd/releases/latest) [![license](https://img.shields.io/github/license/z2care/ZipAltCmd)](https://raw.githubusercontent.com/z2care/ZipAltCmd/master/LICENSE)

# ZipAltCmd
This cmdline tool is to alter the order of zip internal files.

#Usage
ZipAltCmd.exe <in_zip> <out_zip> <list.txt>
1. in_zip: file which you want to read from
2. out_zip: file which you want to write to
3. list.txt: files list which you want to change the order

#History
# v1.0
1. Only support un-signed apk
2. MUST put AndroidManifest.xml on the top of list.txt

# v1.1
1. Support APK Signature Scheme v2
