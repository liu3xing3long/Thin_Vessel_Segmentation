#ifndef NSTAIO_H
#define NSTAIO_H

#include <stdio.h>

// Read/Writing big block of data
inline long long fwrite_big( const void* _Str, size_t _Size, unsigned long long _Count, FILE* _File );
inline long long fread_big( void* _DstBuf, size_t _ElementSize, unsigned long long _Count, FILE* _File );


inline long long fwrite_big( const void* _Str, size_t _Size, unsigned long long _Count, FILE* _File )
{
    char* ptr = (char*) _Str;
    unsigned long long size = (unsigned long long) _Size * _Count;
    // the page size of a i386 system is 4096 bytes
    const size_t page_size = 1<<12;
    long long size_write_total = 0;
    size_t size_write;
    for( ; size>page_size; size-=page_size, ptr+=page_size )
    {
        size_write = fwrite( ptr, 1, page_size, _File);
        size_write_total += size_write;
        if( size_write < page_size )
        {
            // this indicates an error while writing
            return size_write_total;
        }
    }
    size_write = fwrite( ptr, 1, (size_t) size, _File);
    size_write_total += size_write;
    return size_write_total;
}

inline long long fread_big( void* _DstBuf, size_t _ElementSize, unsigned long long _Count, FILE* _File )
{
    char* ptr = (char*) _DstBuf;
    unsigned long long size = (unsigned long long) _ElementSize * _Count;
    // the page size of a i386 system is 4096 bytes
    const size_t page_size = 1<<12;
    long long size_read_total = 0;
    size_t size_read = 0;
    for( ; size>page_size; size-=page_size, ptr+=page_size )
    {
        size_read = fread( ptr, 1, page_size, _File );
        size_read_total += size_read;
        if( size_read < page_size )
        {
            // this indicates an error while reading
            return size_read_total;
        }
    }
    size_read = fread( ptr, 1, (size_t) size, _File);
    size_read_total += size_read;
    return size_read_total;
};

#endif