#include <iostream>
#include <limits>
#include <stdexcept>

class GrayCoder {
public:
    static unsigned int EncodeGrayCode(unsigned int num) {
        return num ^ (num >> 1);
    }

    static unsigned int DecodeGrayCode(unsigned int gray) {
        unsigned int num = gray;
        while (gray >>= 1) {
            num ^= gray;
        }
        return num;
    }
};

#include <cassert>
#include <vector>

int main() {
    
    // TEST
    assert(GrayCoder::EncodeGrayCode(0) == 0);
    assert(GrayCoder::EncodeGrayCode(1) == 1);
    assert(GrayCoder::EncodeGrayCode(2) == 3);
    assert(GrayCoder::EncodeGrayCode(3) == 2);
    assert(GrayCoder::EncodeGrayCode(4) == 6);
    // TEST_END
    
    // TEST
    assert(GrayCoder::DecodeGrayCode(0) == 0);
    assert(GrayCoder::DecodeGrayCode(1) == 1);
    assert(GrayCoder::DecodeGrayCode(3) == 2);
    assert(GrayCoder::DecodeGrayCode(2) == 3);
    assert(GrayCoder::DecodeGrayCode(6) == 4);
    // TEST_END
    
    // TEST
    unsigned int maxInput = std::numeric_limits<unsigned int>::max();
    assert(GrayCoder::EncodeGrayCode(maxInput) == (maxInput ^ (maxInput >> 1)));
    assert(GrayCoder::DecodeGrayCode(GrayCoder::EncodeGrayCode(maxInput)) == maxInput);
    // TEST_END
    
    // TEST
    std::vector<unsigned int> test_inputs = {
        0,
        1,
        2,
        0x3F,
        0x7FF,
        0xFFFF,
        0x1FFFFF,
        0xFFFFFFFF
    };

    for (unsigned int input : test_inputs)
    {
        unsigned int encoded = GrayCoder::EncodeGrayCode(input);
        unsigned int decoded = GrayCoder::DecodeGrayCode(encoded);
                
        assert(decoded == input);
        assert(GrayCoder::EncodeGrayCode(decoded) == encoded);
        assert(GrayCoder::DecodeGrayCode(GrayCoder::EncodeGrayCode(input)) == input);

    }
    // TEST_END
    
    return 0;
}


