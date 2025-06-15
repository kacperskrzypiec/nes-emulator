#pragma once

#include <cstdint>
#include <array>

namespace ks {
	class Bus {
	public:
		Bus() {
			m_memory[0x8000] = 0xA9; // LDA 
			m_memory[0x8001] = 0x20; // #$20
			m_memory[0x8002] = 0xE8; // INX
			m_memory[0x8003] = 0xCA; // INX
		}
		~Bus() = default;

		auto read(const uint16_t address) -> uint8_t {
			return m_memory[address];
		}
		auto write(const uint16_t address, uint8_t value) -> void {
			m_memory[address] = value;
		}

	private:
		std::array<uint8_t, 65536> m_memory{};
	};
}