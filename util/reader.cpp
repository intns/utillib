#include <util/reader.hpp>

namespace util {

Reader::Reader(Endianness endianness)
    : m_buffer({ 0 })
    , m_position(0)
    , m_endianness(endianness)
{
}

Reader::Reader(std::vector<u8> bytes, std::size_t position, Endianness endianness)
    : m_buffer(bytes)
    , m_position(position)
    , m_endianness(endianness)
{
}

} // namespace util