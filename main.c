#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "./zlib/zlib.h"
#include <emscripten.h>

unsigned long getMs(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec *1000 + tv.tv_usec/1000 ;
}

size_t zlibCompress(const char* p, size_t len, char* pout, size_t lenout){
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt)len; // size of input, string + terminator
    defstream.next_in = (Bytef *)p; // input char array
    defstream.avail_out = (uInt)lenout; // size of output
    defstream.next_out = (Bytef *)pout; // output char array

    deflateInit2(&defstream, Z_BEST_COMPRESSION, Z_DEFLATED, -15,4, Z_DEFAULT_STRATEGY);
    deflate(&defstream, Z_FULL_FLUSH);
    deflateEnd(&defstream);
    return defstream.total_out;
}

size_t zlibDecompress(const char* p, size_t len, char* pout, size_t lenout){
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (uInt)len;
    infstream.next_in = (Bytef *)p; // input char array
    infstream.avail_out = (uInt)lenout;
    infstream.next_out = (Bytef *)pout; // output char array

    inflateInit2(&infstream, -15);
    inflate(&infstream, Z_FULL_FLUSH);
    inflateEnd(&infstream);
    return infstream.total_out;
}


