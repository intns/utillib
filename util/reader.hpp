#include <types.hpp>
#include <vector>

namespace util {

class Reader {
public:
    enum class Endianness : u8 {
        Little = 0,
        Big
    };

    Reader(std::vector<u8> bytes = { 0 })
        : m_buffer(bytes)
        , m_position(0)
        , m_endianness(Endianness::Little)
    {
    }
    ~Reader() = default;
    Reader(const Reader&) = delete;
    Reader& operator=(const Reader&) = delete;

    inline const std::vector<u8>& getBuffer() const { return m_buffer; }
    inline const std::size_t getRemaining() const { return m_buffer.size() - m_position; }

    inline void setEndianness(Endianness endian) { m_endianness = endian; }
    inline const Endianness& getEndianness() const { return m_endianness; }

    inline void setPosition(std::size_t position)
    {
        if (position <= m_buffer.size()) {
            m_position = position;
        }
    }
    inline const std::size_t& getPosition() const { return m_position; }

    inline u8 readU8() { return m_buffer[m_position++]; }
    inline u16 readU16()
    {
        u8 byte0 = readU8();
        u8 byte1 = readU8();

        return (m_endianness == Endianness::Little)
            ? (byte0 | (byte1 << 8))
            : (byte1 | (byte0 << 8));
    }
    inline u32 readU32()
    {
        u8 byte0 = readU8();
        u8 byte1 = readU8();
        u8 byte2 = readU8();
        u8 byte3 = readU8();

        return (m_endianness == Endianness::Little)
            ? (byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24))
            : (byte3 | (byte2 << 8) | (byte1 << 16) | (byte0 << 24));
    }

    inline s8 readS8() { return (s8)m_buffer[m_position++]; }
    inline s16 readS16()
    {
        s8 byte0 = readS8();
        s8 byte1 = readS8();

        return (m_endianness == Endianness::Little)
            ? (byte0 | (byte1 << 8))
            : (byte1 | (byte0 << 8));
    }
    inline s32 readS32()
    {
        s8 byte0 = readS8();
        s8 byte1 = readS8();
        s8 byte2 = readS8();
        s8 byte3 = readS8();

        return (m_endianness == Endianness::Little)
            ? (byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24))
            : (byte3 | (byte2 << 8) | (byte1 << 16) | (byte0 << 24));
    }

private:
    std::vector<u8> m_buffer;
    std::size_t m_position;
    Endianness m_endianness;
};

}