#undef UNICODE

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdint.h>

void flip_array();
void convert_user();

int main()
{
	std::cout << "Mode?\n1: RGB888 to RGB565 and vice versa\n2: Flip bits of XBM array\n";

	int mode;
	std::cin >> mode;

	switch(mode) {
	case 1:
		while(1) convert_user();
		break;
	case 2:
		while(1) flip_array();
		break;
	default:
		break;
	}

	return 0;
}

// using https://www.online-utility.org/image/convert/to/XBM causes the bits to be flipped
// so I flipped back using this code I made:
void flip_array()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	std::cout << "Copy paste numbers in format 0xFF, 0xFF, ... 0xFF: (last line send \"END\")\n";

	std::string full;
	std::string part;

	while(1) {
		std::getline(std::cin, part);
		if (part.find("END") == 0) break;

		if (part.size() && part.back() == '\n') part.pop_back();
		full.append(part);
	}

	std::cout << "Processing...\n";

	std::vector<unsigned char> nums;

	for(size_t p = 0; p < full.length(); )
	{
		size_t next_number = full.find("0x", p);
		if (next_number == std::string::npos) break;
        
        const auto ref = std::strtol(full.c_str() + next_number + 2, nullptr, 16);
		nums.push_back(static_cast<unsigned char>(ref));
        
        p = next_number + 2;		
	}

	std::cout << "Found " << nums.size() << " values, flipping and printing back...\n\n";

    printf("const unsigned char image[] = {\n    ");

    size_t drop = 0;
    for(auto& i : nums) {
        unsigned char inverted = 0;
        for(size_t off = 0; off < 8; ++off) {
            inverted |= (i & (1 << (7 - off))) ? (1 << off) : 0;
        }
        printf("0x%02X, ", inverted);
        if (++drop >= 12) {
            drop = 0;
            printf("\n    ");
        }
    }

    printf("}\n\n");
}

void convert_user()
{
	std::string str;
	std::cout << "Type your number (in HEX, like \"E621\"): ";
	std::getline(std::cin, str);

	const int val = std::stoi(str, nullptr, 16);

	printf("Number got in hex: %X\n", val);

	uint8_t r = ((((val >> 11) & 0x1F) * 527) + 23) >> 6;
	uint8_t g = ((((val >> 5) & 0x3F) * 259) + 33) >> 6;
	uint8_t b = (((val & 0x1F) * 527) + 23) >> 6;
	uint32_t RGB888 = r << 16 | g << 8 | b;

	r = ((val >> 16) & 0xFF) * 31.0f / 255.0f;
	g = ((val >> 8) & 0xFF) * 63.0f / 255.0f;
	b = ((val) & 0xFF) * 31.0f / 255.0f;

	uint32_t RGB565 = (r << 11) | (g << 5) | b;

	printf("888 -> 565: %X\n565 -> 888: %X\n", RGB565, RGB888);
}