#include<iostream>
#include"myFilePrint.h"
#include <stdarg.h>
void mfprint(
	FILE *out,
	const char* _Format,
	...){
	va_list info;
	va_start(info, _Format);
 if (out != NULL)vfprintf_s(out, _Format,info);
 else vprintf_s(_Format,info);
	va_end(info);
}