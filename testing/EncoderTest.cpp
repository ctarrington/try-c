#include <unordered_map>
#include <algorithm>
#include "gtest/gtest.h"

std::string repeat(const std::string &value, const int count) {
    std::string result;
    for (int ctr=0; ctr<count;ctr++) {
        result += value;
    }

    return result;
};

std::string long_as_string(const long &value) {
    std::stringstream stream;
    stream << std::hex << value;
    std::string result(stream.str());
    return result;
}

long hex_string_as_long(const std::string block) {
    long value;
    std::stringstream stream;
    stream << std::hex << block;
    stream >> value;

    return value;
}

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
    int block_size = 31; // allow for sentinel
    std::string combined;

    long result = 1; // sentinel
    int letter_ctr = 0;
    for (const char &letter : raw) {
        if (letterToValueMap.count(letter) > 0) {
            const short value = letterToValueMap.find(letter)->second;
            result <<= 2;
            result |= value;

            letter_ctr++;

            if (letter_ctr == block_size) {
                letter_ctr = 0;
                combined = combined.length() > 0 ? long_as_string(result) + combined : long_as_string(result);
                result = 1;
            }
        }
    }

    if (result > 1) {
        combined = combined.length() > 0 ? long_as_string(result) + combined : long_as_string(result);
    }

    return combined;
}

std::string uncompress(const std::string &raw) {
    int block_size = 16;
    std::string combined;
    std::string remaining = raw;

    while (remaining.length() > 0) {
        std::string result;

        int split_point = 0;
        std::string block = remaining;
        if (remaining.length() > block_size) {
            split_point = remaining.length() - block_size;
            block = remaining.substr(split_point);
            remaining = remaining.substr(0, split_point);
        } else {
           remaining = "";
        }

        long number = hex_string_as_long(block);
        while (log2(number) > 1) {
            short extracted = number & 3;
            if (valueToLetterMap.count(extracted) > 0) {
                char letter = valueToLetterMap.find(extracted)->second;
                result = letter + result;

                number >>= 2;
            }
        }

        combined += result;
    }

    return combined;
}


TEST(EncoderTest, tiny) {
    std::string raw = "A";
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);
}

TEST(EncoderTest, small) {
    std::string raw = repeat("ACGT", 3);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);

    float compressed_size = static_cast<float>(compressed.length());
    float raw_size = static_cast<float>(raw.length());
    float ratio =  compressed_size / raw_size;
    EXPECT_LT(ratio, 0.75);
}


TEST(EncoderTest, silly) {
    std::string raw = "CATGAGTAGAAAGGGTTTAC";
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);
}

TEST(EncoderTest, exact) {
    std::string raw = repeat("C", 31);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(compressed.length(), 16);
    EXPECT_EQ(raw, recovered);
}

TEST(EncoderTest, exactPlusOne) {
    std::string raw = repeat("C", 32);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(compressed.length(), 17);
    EXPECT_EQ(raw, recovered);
}

TEST(EncoderTest, large) {
    std::string raw = repeat("ACGT", 100*1000);
    std::string compressed = compress(raw);
    std::string recovered = uncompress(compressed);

    EXPECT_EQ(raw, recovered);

    float compressed_size = static_cast<float>(compressed.length());
    float raw_size = static_cast<float>(raw.length());
    float ratio =  compressed_size / raw_size;

    EXPECT_LT(ratio, 0.55);
}
