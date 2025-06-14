#pragma once

#include <cstdint>

namespace ks {
	class RP2A03 {
	public:
		RP2A03() = default;
		~RP2A03() = default;

		auto tick() -> void {}

	private:
		uint16_t m_PC{ 0x8000 };

		uint8_t m_SP{ 0xfd };
		uint8_t m_A{};
		uint8_t m_x{};
		uint8_t m_y{};
		uint8_t m_status{ 0x20 };
	};
}