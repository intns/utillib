#ifndef _FSTREAM_READER_HPP
#define _FSTREAM_READER_HPP

#include <fstream>
#include <type_traits>
#include <types.hpp>
#include <vector>

namespace util {

class fstream_reader {
public:
    enum class Endianness : u8 {
        Little = 0,
        Big
    };

    fstream_reader(std::ifstream& file, std::size_t position = 0, Endianness endianness = Endianness::Little);
    ~fstream_reader() = default;
    fstream_reader(const fstream_reader&) = delete;
    fstream_reader& operator=(const fstream_reader&) = delete;

    inline const std::ifstream& getStream() const { return m_filestream; }
    inline const std::size_t getRemaining() const { return m_filesize - m_filestream.tellg(); }
    inline const std::streampos getFilesize() const { return m_filesize; }

    inline Endianness& endianness() { return m_endianness; }
    inline const Endianness& endianness() const { return m_endianness; }

    inline void setPosition(std::size_t position)
    {
        if (position <= m_filesize) {
            m_filestream.seekg(position);
        }
    }
    inline const std::size_t getPosition() const { return m_filestream.tellg(); }

    template <typename T>
    inline constexpr T read()
    {
        // UNSIGNED INTEGER TYPES
        if constexpr (std::is_same<T, u32>::value) {
            return readU32();
        } else if constexpr (std::is_same<T, u16>::value) {
            return readU16();
        } else if constexpr (std::is_same<T, u8>::value) {
            return readU8();
        }

        // SIGNED INTEGER TYPES
        else if constexpr (std::is_same<T, s32>::value) {
            return readS32();
        } else if constexpr (std::is_same<T, s16>::value) {
            return readS16();
        } else if constexpr (std::is_same<T, s8>::value) {
            return readS8();
        }

        return T();
    }

    inline u8 readU8()
    {
        u8 byte = 0;
        m_filestream.read(reinterpret_cast<s8*>(&byte), 1);
        return byte;
    }
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

    inline s8 readS8()
    {
        s8 byte = 0;
        m_filestream.read(&byte, 1);
        return byte;
    }
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
    std::ifstream& m_filestream;
    std::streampos m_filesize;
    Endianness m_endianness;
};

}

#endif