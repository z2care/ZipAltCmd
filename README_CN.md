中文页 | [English](README.md)

[![GitHub release](https://img.shields.io/github/release/z2care/ZipAltCmd.svg)](https://github.com/z2care/ZipAltCmd/releases/latest) [![license](https://img.shields.io/github/license/z2care/ZipAltCmd)](https://raw.githubusercontent.com/z2care/ZipAltCmd/master/LICENSE)

# ZipAltCmd
这是一个改变zip包内部文件顺序的命令行工具。

#Usage
ZipAltCmd.exe <in_zip> <out_zip> <list.txt>
1. in_zip: 要读入的文件
2. out_zip: 要输出的文件
3. list.txt: 要改变文件顺序的文件列表

#History
# v1.0
1. 仅支持未签名apk
2. 必须把AndroidManifest.xml放在list.txt的顶端

# v1.1
1. 支持APK Signature Scheme v2
