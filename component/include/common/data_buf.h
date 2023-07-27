#pragma once
#include <string>

namespace gomros {
namespace common {

class DataBuf
{
    public:
    DataBuf();
    ~DataBuf();
    void From(const char * buffer, size_t len, bool copydata);
    void From(DataBuf& src, bool copydata);
    void Checksize(size_t needlen, bool copydata);
    void Append(const char * buffer, size_t len);

    void Detach();
    void Free();
    size_t datalen;
    size_t buflen;

    char *buf;
};

}
}