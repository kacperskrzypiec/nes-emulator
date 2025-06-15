#include "NES/RP2A03.hpp"
#include "NES/IBus.hpp"

#include <functional>

namespace ks {
	RP2A03::RP2A03(IBus& bus)
		: m_bus(bus) {

	}

	auto RP2A03::cycle() -> void {
		switch (m_executionUnit.stage) {
		case ExecutionStage::FETCH_AND_DECODE: fetch_and_decode(); break;
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

	auto RP2A03::fetch_and_decode() -> void {
		m_executionUnit.cycle = 0;

		const uint8_t opcode = m_bus.read(m_state.PC++);
		m_executionUnit.instruction = ks::decode_instruction(opcode);

		switch (m_executionUnit.instruction.addressingMode) {
			using enum AddressingMode;
		case Implied:
			m_executionUnit.stage = ExecutionStage::EXECUTE;
			break;
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
		case Immediate:
			m_executionUnit.imm = m_bus.read(m_state.PC++);
			execute();
			break;
		case ZeroPage:
			m_executionUnit.n = m_bus.read(m_bus.read(m_state.PC++));
			m_executionUnit.stage = ExecutionStage::EXECUTE;
			break;
		case ZeroPageX:
			if (m_executionUnit.cycle == 0) {
				m_executionUnit.n = m_bus.read(m_state.PC++);
			}
			else if (m_executionUnit.cycle == 1) {
				m_executionUnit.n = m_bus.read(m_executionUnit.n + m_state.X);
				m_executionUnit.stage = ExecutionStage::EXECUTE;
			}
			m_executionUnit.cycle++;
			break;
		case Absolute:
			if (m_executionUnit.cycle == 0) {
				m_executionUnit.operand1 = m_bus.read(m_state.PC++);
			}
			else if (m_executionUnit.cycle == 1) {
				m_executionUnit.operand2 = m_bus.read(m_state.PC++);
				m_executionUnit.address = m_executionUnit.operand2 << 8 | m_executionUnit.operand1;

				if (m_executionUnit.instruction.type == InstructionType::JMP) {
					m_state.PC = m_executionUnit.address;
					m_executionUnit.stage = ExecutionStage::FETCH_AND_DECODE;
				}
				else {
					m_executionUnit.stage = ExecutionStage::EXECUTE;
				}
			}
			m_executionUnit.cycle++;
			break;
		case Implied:
		case Accumulator:
			assert(0 && "Implied, Accumulator addressing modes should not be in the load stage.");
		}
	}
	auto RP2A03::execute() -> void {
		switch (m_executionUnit.instruction.type) {
			using enum InstructionType;
		case ADC: {
			const uint8_t operand = std::invoke([&]() -> uint8_t {
				switch (m_executionUnit.instruction.addressingMode) {
					using enum AddressingMode;
				case Immediate: return m_executionUnit.imm; break;
				case ZeroPage: return m_executionUnit.n; break;
				case ZeroPageX: return m_executionUnit.n; break;
				case Absolute: break;
				case AbsoluteX: break;
				case AbsoluteY: break;
				case IndexedIndirect: break;
				case IndirectIndexed: break;
				}
				return 0;
			});

			int16_t sum = m_state.A + operand + m_state.status[Flag::Carry];

			m_state.status[Flag::Carry] = sum > 0xFF;
			m_state.status[Flag::Overflow] = ((~(m_state.A^operand) & (m_state.A^sum) & 0x80) != 0);

			m_state.A = sum & 0xFF;
			check_NZ_flags(m_state.A);

		}	break;
		case INX:
			m_state.X++;
			check_NZ_flags(m_state.X);
			break;
		case INY:
			m_state.Y++;
			check_NZ_flags(m_state.Y);
			break;
		case DEX:
			m_state.X--;
			check_NZ_flags(m_state.X);
			break;
		case DEY:
			m_state.Y--;
			check_NZ_flags(m_state.Y);
			break;
		case LDA:
			switch (m_executionUnit.instruction.addressingMode) {
				using enum AddressingMode;
			case Absolute: m_state.A = m_bus.read(m_executionUnit.address); break;
			case Immediate: m_state.A = m_executionUnit.imm; break;
			case ZeroPage: m_state.A = m_executionUnit.n; break;
			case ZeroPageX: m_state.A = m_executionUnit.n; break;
			}
			break;
		case LDX:
			switch (m_executionUnit.instruction.addressingMode) {
				using enum AddressingMode;
			case Absolute: m_state.X = m_bus.read(m_executionUnit.address); break;
			case Immediate: m_state.X = m_executionUnit.imm; break;
			case ZeroPage: m_state.X = m_executionUnit.n; break;
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
