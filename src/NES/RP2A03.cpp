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
		m_executionUnit.instruction = ks::decode_instruction(opcode);

		switch (m_executionUnit.instruction.addressingMode) {
			using enum AddressingMode;
		case Immediate: 
			m_executionUnit.imm = m_bus.read(m_state.PC++);
			[[fallthrough]];
		case Implied:
		case Accumulator: 
			m_executionUnit.stage = ExecutionStage::EXECUTE; 
			break;
		default: 
			m_executionUnit.stage = ExecutionStage::LOAD; 
			break;
		}
	}
	auto RP2A03::load() -> void {
		switch (m_executionUnit.instruction.addressingMode) {
			using enum AddressingMode;
		case Implied:
		case Accumulator:
		case Immediate:
			assert(0 && "Implied, Accumulator, and Immediate addressing modes should not be in the load stage.");
		}
	}
	auto RP2A03::execute() -> void {
		switch (m_executionUnit.instruction.type) {
			using enum InstructionType;
		case INX:
			m_state.X++;
			break;
		case DEX:
			m_state.X--;
			break;
		case LDA:
			if (m_executionUnit.instruction.addressingMode == AddressingMode::Immediate) {
				m_state.A = m_executionUnit.imm;
			}
			break;
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
