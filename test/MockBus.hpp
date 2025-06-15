#pragma once

#include "NES/IBus.hpp"

#include <cstdint>
#include <array>
#include <memory>

namespace ks {
	class MockBus : public IBus {
	public:
		MockBus() {
			m_memory = std::make_unique<std::array<uint8_t, 65536>>();
		}
		~MockBus() = default;

		virtual auto read(const uint16_t address) -> uint8_t {
			return (*m_memory)[address];
		}
		virtual auto write(const uint16_t address, uint8_t value) -> void {
			(*m_memory)[address] = value;
		}

	private:
		std::unique_ptr<std::array<uint8_t, 65536>> m_memory{};
	};
}