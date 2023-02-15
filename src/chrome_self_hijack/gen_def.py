#!/usr/bin/env python3
#

import pefile
import sys
import os.path

#dll = pefile.PE('version_7.dll')
dll = pefile.PE(sys.argv[1])
dll_basename = os.path.splitext(sys.argv[1])[0]

#打开并写入导出函数
with open("version.def", "w") as fo:
    fo.write("EXPORTS\n")
    print("EXPORTS")
    for export in dll.DIRECTORY_ENTRY_EXPORT.symbols:
        if export.name:
            print('{}={}.{} @{}'.format(export.name.decode(), dll_basename, export.name.decode(), export.ordinal))
            #写入文件
            fo.write('{}={}.{} @{}\n'.format(export.name.decode(), dll_basename, export.name.decode(), export.ordinal))