#include <iostream>
#include <util/fstream_reader.hpp>
#include <util/misc.hpp>
#include <util/vector_reader.hpp>

int main(int argc, char** argv)
{
    // CHECKING DUMP FUNCTIONS
    std::ofstream dump_out("out.txt", std::ios_base::binary);
    dump_out.write("test test dump to hex test", 26);
    dump_out.close();
    util::DumpFileToCppHeader("out.txt");

    // CHECKING READING FUNCTIONS
    util::vector_reader vector_reader({ 80, 16, 2, 3, 4, 5, 6 }, 0, util::vector_reader::Endianness::Big);
    std::cout << vector_reader.readS16() << std::endl;

    std::ifstream fstream_reader_file("out.txt", std::ios_base::binary);
    util::fstream_reader fstream_reader(fstream_reader_file);
    std::cout << (u32)fstream_reader.readU8() << std::endl;
    fstream_reader_file.close();

    // CHECKING ANAGRAM FUNCTIONS
    std::vector<std::string> check = { "ahahah", "aioasg", "helol", "heLLa", "heLLO" };
    std::optional<std::vector<std::string>> aohCheck = util::IsAnagramOfList("hello", check);
    if (aohCheck.has_value()) {
        const std::vector<std::string>& anagramsOfHello = aohCheck.value();

        for (const std::string& foundStrs : anagramsOfHello) {
            std::cout << foundStrs << " is an anagram of hello" << std::endl;
        }
    }

    std::remove("out.txt");
}