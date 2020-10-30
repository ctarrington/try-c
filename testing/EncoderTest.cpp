#include <unordered_map>
#include "gtest/gtest.h"

std::string repeat(const std::string &value, const int count) {
    std::string result;
    for (int ctr=0; ctr<count;ctr++) {
        result += value;
    }

    return result;
};

static const std::map<char, short> letterToValueMap {
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3},
};

static const std::map<short, char> valueToLetterMap {
        { 0, 'A'},
        {1, 'C'},
        {2, 'G'},
        {3, 'T'},
};

std::string compress(const std::string &raw) {
    int result = 1; // sentinel
    for (const char &letter : raw) {
        if (letterToValueMap.count(letter) > 0) {
            const short value = letterToValueMap.find(letter)->second;
            result <<= 2;
            result |= value;
        }
    }

    return std::to_string(result);
}

std::string uncompress(const std::string &raw) {
    std::string result;

    int number = std::stoi(raw);
    while (log2(number) > 1) {
        short extracted = number & 3;
        if (valueToLetterMap.count(extracted) > 0) {
            char letter = valueToLetterMap.find(extracted)->second;
            result = letter + result;

            number >>= 2;
        }
    }

    return result;
}


TEST(EncoderTest, small) {
    std::string raw = repeat("ACGT", 3);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);

    float compressed_size = static_cast<float>(compressed.length());
    float raw_size = static_cast<float>(raw.length());
    float ratio =  compressed_size / raw_size;
    EXPECT_LT(ratio, 0.7);
}


TEST(EncoderTest, silly) {
    std::string raw = "CATGAGTAGAAAGGGTTTAC";
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);
}

TEST(EncoderTest, large) {
    std::string raw = repeat("ACGT", 1000);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);

    float ratio = static_cast<float>(sizeof(compressed)) / static_cast<float>(sizeof(raw));
    EXPECT_LT(ratio, 0.3);
}
