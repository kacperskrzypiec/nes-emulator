#include "NES/RP2A03.hpp"
#include "MockBus.hpp"

#include "doctest.h"

TEST_CASE("CPU initialization state") {
	ks::MockBus bus;
	ks::RP2A03 cpu(bus);
	FAST_CHECK_EQ(cpu.get_state().PC, 0x8000);
	FAST_CHECK_EQ(cpu.get_state().SP, 0xfd);
	FAST_CHECK_EQ(cpu.get_state().A, 0x00);
	FAST_CHECK_EQ(cpu.get_state().X, 0x00);
	FAST_CHECK_EQ(cpu.get_state().Y, 0x00);
	FAST_CHECK_EQ(cpu.get_state().status, 0x20);
}

TEST_CASE("CPU arithmetic instructions") {
	constexpr uint16_t pc = 0x8000;

	SUBCASE("") {
		auto test_increment_register = [pc](const uint8_t opcode) -> void {
			ks::MockBus bus;
			ks::RP2A03 cpu(bus);

			for (int i = 0; i < 256; i++) {
				bus.write(pc + i, opcode);
			}

			constexpr uint8_t wantTwoCycles = 2;
			constexpr uint8_t wantNoFlag = 0x20;
			constexpr uint8_t wantOnlyZ = 0x22;
			constexpr uint8_t wantOnlyN = 0xA0;

			auto get_reg_state = [opcode, &cpu]() -> uint8_t {
				return opcode == 0xE8 ? cpu.get_state().X : cpu.get_state().Y;
			};

			// Testing basic implementation
			const uint8_t N = get_reg_state();
			const uint8_t wantN = N + 1;

			cpu.cycle();
			FAST_CHECK_EQ(get_reg_state(), N);
			FAST_CHECK_EQ(cpu.get_state().status, wantNoFlag);
			cpu.cycle();
			FAST_CHECK_EQ(get_reg_state(), wantN);
			FAST_CHECK_EQ(cpu.get_state().status, wantNoFlag);
			FAST_CHECK_EQ(cpu.get_cycles(), wantTwoCycles);

			// Testing N and Z flags
			for (int i = 0; i < 254; i++) {
				cpu.step();
				if (get_reg_state() >= 128) {
					FAST_CHECK_EQ(cpu.get_state().status, wantOnlyN);
				}
				else {
					FAST_CHECK_EQ(cpu.get_state().status, wantNoFlag);
				}
			}

			// Testing Z flag
			constexpr uint8_t wantZero = 0x0;

			cpu.step();
			FAST_CHECK_EQ(get_reg_state(), wantZero);
			FAST_CHECK_EQ(cpu.get_state().status, wantOnlyZ);
			FAST_CHECK_EQ(cpu.get_cycles(), wantTwoCycles * 256);
		};

		SUBCASE("INX") {
			test_increment_register(0xE8);
		}
		SUBCASE("INY") {
			test_increment_register(0xC8);
		}
	}
	SUBCASE("") {
		auto test_decrement_register = [pc](const uint8_t opcode) -> void {
			ks::MockBus bus;
			ks::RP2A03 cpu(bus);

			for (int i = 0; i < 256; i++) {
				bus.write(pc + i, opcode);
			}

			constexpr uint8_t wantTwoCycles = 2;
			constexpr uint8_t wantNoFlag = 0x20;
			constexpr uint8_t wantOnlyZ = 0x22;
			constexpr uint8_t wantOnlyN = 0xA0;

			auto get_reg_state = [opcode, &cpu]() -> uint8_t {
				return opcode == 0xCA ? cpu.get_state().X : cpu.get_state().Y;
			};

			// Testing basic implementation
			const uint8_t N = get_reg_state();
			const uint8_t wantN = N - 1;

			cpu.cycle();
			FAST_CHECK_EQ(get_reg_state(), N);
			FAST_CHECK_EQ(cpu.get_state().status, wantNoFlag);
			cpu.cycle();
			FAST_CHECK_EQ(get_reg_state(), wantN);
			FAST_CHECK_EQ(cpu.get_state().status, wantOnlyN);
			FAST_CHECK_EQ(cpu.get_cycles(), wantTwoCycles);

			// Testing N and Z flags
			for (int i = 0; i < 254; i++) {
				cpu.step();
				if (get_reg_state() >= 128) {
					FAST_CHECK_EQ(cpu.get_state().status, wantOnlyN);
				}
				else {
					FAST_CHECK_EQ(cpu.get_state().status, wantNoFlag);
				}
			}

			// Testing Z flag
			constexpr uint8_t wantZero = 0x0;

			cpu.step();
			FAST_CHECK_EQ(get_reg_state(), wantZero);
			FAST_CHECK_EQ(cpu.get_state().status, wantOnlyZ);
			FAST_CHECK_EQ(cpu.get_cycles(), wantTwoCycles * 256);
		};

		SUBCASE("DEX") {
			test_decrement_register(0xCA);
		}
		SUBCASE("DEY") {
			test_decrement_register(0x88);
		}
	}
}