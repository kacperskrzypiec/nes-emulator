#pragma once

#include <cstdint>
#include <cassert>

namespace ks {
	struct Register {
		uint8_t data{};

		auto get_bit(const uint8_t index) const -> bool {
			assert(index < 8 && "Index should be less than 8.");

			return (data >> index) & 0x1;
		}
		auto set_bit(const uint8_t index, const bool value) -> void {
			assert(index < 8 && "Index should be less than 8.");

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
		auto operator[](const uint8_t index) const -> bool {
			assert(index < 8 && "Index should be less than 8.");
			return get_bit(index);
		}

		class RegRef {
		public:
			RegRef(Register& reg, const uint8_t index)
				:	m_reg(reg), m_index(index) {}

			auto operator=(const bool value) -> RegRef& {
				m_reg.set_bit(m_index, value);
				return *this;
			}

			operator bool() const {
				return m_reg.get_bit(m_index);
			}

		private:
			Register& m_reg;
			uint8_t m_index;
		};

		auto operator[](const uint8_t index) -> RegRef {
			assert(index < 8 && "Index should be less than 8.");
			return RegRef(*this, index);
		}
	};
}