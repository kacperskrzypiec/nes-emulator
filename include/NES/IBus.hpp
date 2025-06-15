#pragma once

#include <cstdint>

namespace ks {
	class IBus {
	public:
		IBus() = default;
		virtual ~IBus() = default;

		virtual auto read(const uint16_t address) -> uint8_t = 0;
		virtual auto write(const uint16_t address, uint8_t value) -> void = 0;
	};
}