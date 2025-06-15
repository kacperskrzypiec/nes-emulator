#include "NES/Register.hpp"
#include "doctest.h"

TEST_CASE("Register behavior")
{
	ks::Register reg;

	// Test initial state
	FAST_CHECK_EQ(reg, 0);

	// Test setting bits
	reg.set_bit(4, 1);
	FAST_CHECK_EQ(reg, 0x10);
	FAST_CHECK_EQ(reg.get_bit(4), 1);

	reg.set_bit(7, 1);
	FAST_CHECK_EQ(reg, 0x90);
	FAST_CHECK_EQ(reg.get_bit(4), 1);
	FAST_CHECK_EQ(reg.get_bit(7), 1);

	reg.set_bit(0, 1);
	FAST_CHECK_EQ(reg, 0x91);
	FAST_CHECK_EQ(reg.get_bit(0), 1);
	FAST_CHECK_EQ(reg.get_bit(4), 1);
	FAST_CHECK_EQ(reg.get_bit(7), 1);

	// Test setting bits to 0
	reg = {};
	FAST_CHECK_EQ(reg, 0);
	for (int i = 0; i < 8; ++i) {
		FAST_CHECK_EQ(reg.get_bit(i), 0);
	}

	// Test setting bits one by one
	for(int i = 0; i < 8; ++i) {
		reg.set_bit(i, 1);
		for (int j = 0; j < i; j++) {
			FAST_CHECK_EQ(reg.get_bit(j), 1);
		}
	}
	
	FAST_CHECK_EQ(reg, 0xFF);
}