#pragma once

#include <cstdint>

namespace ks {
	class RP2A03 {
	public:
		struct State {
			uint16_t PC{ 0x8000 };
			uint8_t SP{ 0xfd };
			uint8_t A{};
			uint8_t x{};
			uint8_t y{};
			uint8_t status{ 0x20 };
		};

	public:
		RP2A03() = default;
		~RP2A03() = default;

		auto cycle() -> void {}
		auto step() -> void {}

		auto rst() -> void {}
		auto irq() -> void {}
		auto nmi() -> void {}

		auto get_state() const -> const State& {
			return m_state;
		}

	private:
		enum class ExecutionStage : uint8_t {
			FETCH=0,
			DECODE,
			EXECUTE
		};

	private:
		ExecutionStage m_stage{ ExecutionStage::FETCH };
		uint8_t m_cycles{};

		State m_state;
	};
}