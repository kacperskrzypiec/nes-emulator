#include "NES/RP2A03.hpp"
#include "NES/Bus.hpp"

namespace ks {
	RP2A03::RP2A03(Bus& bus)
		: m_bus(bus) {

	}

	auto RP2A03::cycle() -> void {
		switch (m_executionUnit.stage) {
		case ExecutionStage::FETCH_AND_DECODE: fetch_and_execute(); break;
		case ExecutionStage::LOAD: load(); break;
		case ExecutionStage::EXECUTE: execute(); break;
		}
		m_cycles++;
	}
	auto RP2A03::step() -> void {
		do {
			cycle();
		} while (m_executionUnit.stage != ExecutionStage::FETCH_AND_DECODE);
	}

	auto RP2A03::fetch_and_execute() -> void {
		const uint8_t opcode = m_bus.read(m_state.PC++);
		m_executionUnit.instruction.decode(opcode);

		switch (m_executionUnit.instruction.get_addressing_mode()) {
		case AddressingMode::Immediate: 
			m_executionUnit.imm = m_bus.read(m_state.PC++);
			[[fallthrough]];
		case AddressingMode::Implied:
		case AddressingMode::Accumulator: 
			m_executionUnit.stage = ExecutionStage::EXECUTE; 
			break;

		default: 
			m_executionUnit.stage = ExecutionStage::LOAD; 
			break;
		}
	}
	auto RP2A03::load() -> void {
		switch (m_executionUnit.instruction.get_addressing_mode()) {
		case AddressingMode::Implied:
		case AddressingMode::Accumulator:
		case AddressingMode::Immediate:
			assert(0 && "Implied, Accumulator, and Immediate addressing modes should not be in the load stage.");
		}
	}
	auto RP2A03::execute() -> void {
		if (m_executionUnit.instruction.get_type() == InstructionType::INX) {
			m_state.X++;
			// no flags for now
		}
		else if (m_executionUnit.instruction.get_type() == InstructionType::LDA) {
			if (m_executionUnit.instruction.get_addressing_mode() == AddressingMode::Immediate) {
				m_state.A = m_executionUnit.imm;
			}
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
