#include "NES/RP2A03.hpp"
#include "doctest.h"

TEST_CASE("CPU initialization state")
{
	ks::RP2A03 cpu;
	FAST_CHECK_EQ(cpu.get_state().PC, 0x8000);
	FAST_CHECK_EQ(cpu.get_state().SP, 0xfd);
	FAST_CHECK_EQ(cpu.get_state().A, 0x00);
	FAST_CHECK_EQ(cpu.get_state().X, 0x00);
	FAST_CHECK_EQ(cpu.get_state().Y, 0x00);
	FAST_CHECK_EQ(cpu.get_state().status, 0x20);
}

TEST_CASE("CPU instructions")
{
	SUBCASE("INX")
	{
		ks::RP2A03 cpu;
		const int X = cpu.get_state().X;
		const int wantX = (X + 1) % 255;
		cpu.cycle();
		FAST_CHECK_EQ(cpu.get_state().X, X);
		cpu.cycle();
		FAST_CHECK_EQ(cpu.get_state().X, wantX);
	}
}