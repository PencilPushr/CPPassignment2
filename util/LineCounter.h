// Author: Pete Kirkham
// string match benchmark - block io, 8-wide line break + BMH prefix match algorithm, full regex.
// bitmatch changed with reference to http://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdint.h>

#define BLOCK_SIZE 8096

// BMH string search
// pattern must be allocated to be a multiple of 8 chars
size_t prefix_search(const char* pattern, size_t pattern_length, int* table, const char* string, size_t string_length)
{
    const char      last_char(pattern[pattern_length - 1]);
    const size_t    last_index(string_length - 1);
    const size_t    pattern_last(pattern_length - 1);

    // scan pattern_length chars at a time for last char in pattern
    for (size_t index(0); index < last_index; )
    {
        size_t scan(pattern_last);

        for (; string[index + scan] == pattern[scan]; --scan)
            if (scan == 0)
                return index;

        int     jump(table[size_t(string[index + scan]) & 0xff]);
        size_t  matched(pattern_last - scan);

        if (jump <= matched)
            ++index;
        else
            index += jump - matched;
    }

    return string_length;
}

#define character_range(a, b)   if (line[index] < a || line[index] > b) return;    ++index;
#define character_equal(c)      if (line[index] != c) return;                      ++index;

// process a line of input
inline void process_line(size_t& matches, const char* pattern, size_t pattern_length, int* table, const char* line, size_t line_length)
{
    size_t match(prefix_search(pattern, pattern_length, table, line, line_length) + pattern_length);
    size_t index(match);

    if (index >= line_length - 18) return;

    character_range('0', '9');
    character_range('0', '9');
    character_range('0', '9');
    character_equal('x');
    character_equal('/');
    character_range('0', '9');
    character_range('0', '9');
    character_range('0', '9');
    character_range('0', '9');
    character_equal('/');
    character_range('0', '9');
    character_range('0', '9');
    character_equal('/');
    character_range('0', '9');
    character_range('0', '9');
    character_equal('/');

    while (index < line_length)
    {
        char ch(line[index]);

        if ((ch == '.') || (ch == '\n'))
            break;

        if (ch == ' ')
        {
            if (index > match + 18)
            {
                ++matches;
#ifdef LIST_MATCHES
                std::cout << std::string(line + match + 5, index - (match + 5)) << std::endl;
#endif
            }
            break;
        }

        ++index;
    }
}

// main
int main(int narg, char** argvp)
{
    if (narg < 2)
    {
        std::cout << "The name of the input file is required." << std::endl;
        return 1;
    }

    // open the file
    int file(open(argvp[1], O_RDONLY));

    if (!file)
    {
        std::cout << "failed to open " << argvp[1] << std::endl;
        return 2;
    }

    // prefix of pattern to find
    const char* pattern("GET /ongoing/When/");
    size_t      pattern_length(strlen(pattern));

    // bmh table
    int         table[256];

    for (size_t scan(0); scan < 256; ++scan)
        table[scan] = pattern_length;

    for (size_t scan(0); scan < pattern_length - 1; ++scan)
        table[size_t(pattern[scan]) & 0xff] = pattern_length - 1 - scan;

    // block IO
    // for splitting lines, we move any trailing part line to the start of
    // memory then read data into the area following it
    uint64_t    mem[BLOCK_SIZE / 4]; // use wider type to ensure alignment
    char* buf((char*)mem);
    ssize_t     bytes_read;
    size_t      bytes_carried(0);

    // count of matching lines
    size_t      matches(0);

    while ((bytes_read = read(file, buf + bytes_carried, BLOCK_SIZE)) > 0)
    {
        size_t chunk_length(bytes_carried + bytes_read);
        size_t line_start(0);

        // scan for line breaks, 8 chars at a time - on x64, you can do 16,
        for (size_t i(0); i < chunk_length; i += 16)
        {
            uint64_t    data(*((uint64_t*)(buf + i)));

            data = (data ^ 0x0a0a0a0a0a0a0a0aLL);

            if ((data - 0x0101010101010101LL) & ~data & 0x8080808080808080LL)
            {
                // you can do without this scan - if you know machine endianess, then
                // one of the eight non-zero values of data will give the index
                for (; i < chunk_length; ++i)
                {
                    if (buf[i] == '\n')
                    {
                        size_t line_length(i - line_start);
                        const char* line(buf + line_start);
#ifdef ECHO_LINES
                        buf[i] = '\0';

                        std::cout << buf + line_start << std::endl;
#endif

                        process_line(matches, pattern, pattern_length, table, line, line_length);

                        line_start = i + 1;

                        i &= ~7;

                        break; // assumes there are no lines < 8 characters
                    }
                }
            }
        }

        // copy trailing data to start of alternate block
        //  assumes that a line is never more than half a block long
        bytes_carried = chunk_length - line_start;

        memcpy(buf, buf + line_start, bytes_carried);
    }

    // if there is any last line, process that
    if (bytes_carried)
    {
        process_line(matches, pattern, pattern_length, table, buf, bytes_carried);
    }

    close(file);

    std::cout << "matches: " << matches << std::endl;

    return 0;
}


//c++ magic shit
/*

http://aggregate.org/MAGIC/#SIMD%20Within%20A%20Register%20(SWAR)%20Operations

*/