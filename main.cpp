#include <iostream>
#include <util/misc.hpp>
#include <util/reader.hpp>

int main(int argc, char** argv)
{
    using namespace util;

    // CHECKING READING FUNCTIONS
    Reader reader({ 80, 16, 2, 3, 4, 5, 6 }, 0, Reader::Endianness::Big);
    std::cout << reader.read<s16>() << std::endl;

    // CHECKING ANAGRAM FUNCTIONS
    std::vector<std::string> check = { "ahahah", "aioasg", "helol", "heLLa", "heLLO" };
    std::optional<std::vector<std::string>> aohCheck = IsAnagramOfList("hello", check);
    if (aohCheck.has_value()) {
        const std::vector<std::string>& anagramsOfHello = aohCheck.value();

        for (const std::string& foundStrs : anagramsOfHello) {
            std::cout << foundStrs << " is an anagram of hello" << std::endl;
        }
    }

    // CHECKING DUMP FUNCTIONS
    std::ofstream out("out.txt", std::ios_base::binary);
    out.write("test test dump to hex test", 26);
    out.close();
    DumpFileToCppHeader("out.txt");
    std::remove("out.txt");
}