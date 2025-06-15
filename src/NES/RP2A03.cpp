#include "NES/RP2A03.hpp"

namespace ks {
	auto RP2A03::cycle() -> void {
		switch (m_executionUnit.stage) {
		case ExecutionStage::FETCH_AND_DECODE: fetch_and_execute(); break;
		case ExecutionStage::LOAD: load(); break;
		case ExecutionStage::EXECUTE: execute(); break;
		}
	}
	auto RP2A03::step() -> void {
		do {
			cycle();
		} while (m_executionUnit.stage != ExecutionStage::FETCH_AND_DECODE);
	}

	auto RP2A03::fetch_and_execute() -> void {
		const uint8_t opcode = 0xE8;
		m_executionUnit.instruction.decode(opcode);

		switch (m_executionUnit.instruction.get_addressing_mode()) {
		case AddressingMode::Implied: 
		case AddressingMode::Accumulator: m_executionUnit.stage = ExecutionStage::EXECUTE; break;

		default: m_executionUnit.stage = ExecutionStage::LOAD; break;
		}
	}
	auto RP2A03::load() -> void {

	}
	auto RP2A03::execute() -> void {
		if (m_executionUnit.instruction.get_type() == InstructionType::INX) {
			m_state.X++;
			// no flags for now
		}
		m_executionUnit.stage = ExecutionStage::FETCH_AND_DECODE;
	}

	auto RP2A03::rst() -> void {

	}
	auto RP2A03::irq() -> void {

	}
	auto RP2A03::nmi() -> void {

	}
}
