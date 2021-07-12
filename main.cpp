#include <iostream>
#include <util/reader.hpp>

int main(int argc, char** argv)
{
    using namespace util;

    Reader reader({ 80, 16, 2, 3, 4, 5, 6 });
    reader.setEndianness(Reader::Endianness::Big);
    std::cout << reader.readU16();
}