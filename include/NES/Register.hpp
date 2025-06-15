#pragma once

#include <cstdint>
#include <cassert>

namespace ks {
	struct Register {
		uint8_t data{};

		auto get_bit(const uint8_t index) const -> bool {
			assert(index >= 0 && index < 8);

			return (data >> index) & 0x1;
		}
		auto set_bit(const uint8_t index, const bool value) -> void {
			assert(index >= 0 && index < 8);

			data ^= (-(int8_t)value ^ data) & (1 << index);

			/*
			value = 0:
				data ^= data & (1 << index)
				0^0 = 0
				1^1 = 0

			value = 1:
				data ^= ~data & (1 << index)
				1^0 = 1
				0^1 = 1
			*/
		}

		operator uint8_t() const {
			return data;
		}
	};
}