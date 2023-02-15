@rem  程序功能：编译出DLL 用于跳板
@rem	实现方式: 填写需要导出的dll

@rem 输出导出函数
@rem python.exe .\gen_def.py version_7.dll

@rem 根据导出函数编译出自己的dll
@rem 32位
@rem i686-w64-mingw32-gcc -shared -o chrome_elf.dll chrome_elf.c chrome_elf.def -s
@rem 64位
x86_64-w64-mingw32-g++ -shared -o version.dll version.c version.def -s
@rem 重命名需要的DLL
@rem ren version_7.dll chrome_core.dll 