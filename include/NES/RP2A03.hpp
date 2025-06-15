#pragma once

#include "Instruction.hpp"
#include "Register.hpp"

#include <cstdint>

namespace ks {
	class RP2A03 {
	public:
		enum Flag {
			Carry=0,
			Zero=1,
			Interrupt=2,
			Decimal=3,
			Break=4,
			__IGNORED=5, // always 1
			Overflow=6,
			Negative=7
		};

		struct State {
			uint16_t PC{ 0x8000 };
			uint8_t SP{ 0xfd };
			uint8_t A{};
			uint8_t X{};
			uint8_t Y{};
			Register status{ 0x20 };
		};

	public:
		RP2A03() = default;
		~RP2A03() = default;

		auto cycle() -> void;
		auto step() -> void;

		auto rst() -> void;
		auto irq() -> void;
		auto nmi() -> void;

		auto get_state() const -> const State& {
			return m_state;
		}

	private:
		enum class ExecutionStage : uint8_t {
			FETCH_AND_DECODE=0,
			LOAD,
			EXECUTE
		};
		struct ExecutionUnit {
			Instruction instruction{};
			ExecutionStage stage{ ExecutionStage::FETCH_AND_DECODE };
			uint8_t cycle{};
			uint8_t operand1{};
			uint8_t operand2{};
		};

	private:
		auto fetch_and_execute() -> void;
		auto load() -> void;
		auto execute() -> void;

	private:
		ExecutionUnit m_executionUnit;
		State m_state;
	};
}