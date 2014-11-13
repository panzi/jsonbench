#include "rapidjson/reader.h"

using namespace rapidjson;
using namespace std;

struct MyHandler {
    bool Null() { return true; }
    bool Bool(bool) { return true; }
    bool Int(int) { return true; }
    bool Uint(unsigned) { return true; }
    bool Int64(int64_t) { return true; }
    bool Uint64(uint64_t) { return true; }
    bool Double(double) { return true; }
    bool String(const char*, SizeType, bool) { return true; }
    bool StartObject() { return true; }
    bool Key(const char*, SizeType, bool) { return true; }
    bool EndObject(SizeType) { return true; }
    bool StartArray() { return true; }
    bool EndArray(SizeType) { return true; }
};

extern "C" int jsonbench(const char buffer[], size_t filesize, size_t stride) {
    (void)filesize;
    (void)stride;

    MyHandler handler;
    Reader reader;
    StringStream ss(buffer);

    return reader.Parse(ss, handler) ? 0 : -1;
}
