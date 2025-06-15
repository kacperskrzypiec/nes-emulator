#pragma once

#include <cstdint>

namespace ks {
	class Bus {
	public:
		Bus() = default;
		~Bus() = default;

		auto read(const uint16_t address) -> uint8_t {
			// Once again, I like to explore.
			if (address == 32768) {
				return 0xA9;
			}
			else if (address == 32769) {
				return 0x20;
			}
			else if (address == 32770) {
				return 0xE8;
			}

			return 0;
		}
		auto write(const uint16_t address, uint8_t value) -> void {

		}

	private:
		
	};
}