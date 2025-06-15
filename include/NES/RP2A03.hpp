#pragma once

#include "Instruction.hpp"
#include "Register.hpp"

#include <cstdint>

namespace ks {
	class IBus;

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
		RP2A03(IBus& bus);
		~RP2A03() = default;

		auto cycle() -> void;
		auto step() -> void;

		auto rst() -> void;
		auto irq() -> void;
		auto nmi() -> void;

		auto get_state() const -> const State& {
			return m_state;
		}

		auto get_cycles() const -> uint64_t {
			return m_cycles;
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
			uint16_t address{};
			union {
				uint8_t imm{};
				uint8_t n;
			};
		};

	private:
		auto fetch_and_decode() -> void;
		auto load() -> void;
		auto execute() -> void;

		auto check_NZ_flags(const uint8_t value) -> void {
			m_state.status[Flag::Negative] = (value >> 7) & 0x1;
			m_state.status[Flag::Zero] = (value == 0);
		}

	private:
		IBus& m_bus;

		ExecutionUnit m_executionUnit;
		State m_state;

		uint64_t m_cycles{};
	};
}