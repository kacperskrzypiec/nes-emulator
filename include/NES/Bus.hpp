#pragma once

#include "IBus.hpp"

#include <cstdint>
#include <array>

namespace ks {
	class Bus : public IBus {
	public:
		Bus() {
			m_memory[0x0055] = 0x12;
			m_memory[0x0043] = 0x69;

			m_memory[0x8000] = 0xA2; // LDX #$1
			m_memory[0x8001] = 0x01; //	
			m_memory[0x8002] = 0xB5; // LDA $42+X
			m_memory[0x8003] = 0x42; //
			m_memory[0x8004] = 0x65; // ADC $55
			m_memory[0x8005] = 0x55; //
			m_memory[0x8006] = 0xA2; // LDX #$24
			m_memory[0x8007] = 0x24; //	
			m_memory[0x8008] = 0xE8; // INX
			m_memory[0x8009] = 0x4C; // JMP $8000
			m_memory[0x800A] = 0x00; // 
			m_memory[0x800B] = 0x80; // 
		}
		~Bus() = default;

		virtual auto read(const uint16_t address) -> uint8_t {
			return m_memory[address];
		}
		virtual auto write(const uint16_t address, uint8_t value) -> void {
			m_memory[address] = value;
		}

	private:
		std::array<uint8_t, 65536> m_memory{};
	};
}