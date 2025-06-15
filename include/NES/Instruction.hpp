#pragma once

#include <cstdint>
#include <array>

namespace ks {
	enum class AddressingMode : uint8_t {
		/* Implied	*/ Implied=0,
		/* Accum	*/ Accumulator,
		/* IMM		*/ Immediate,
		/* ZP		*/ ZeroPage,
		/* ZP, X	*/ ZeroPageX,
		/* ZP, Y	*/ ZeroPageY,
		/* Relative */ Relative,
		/* Absolute */ Absolute,
		/* ABS, X	*/ AbsoluteX,
		/* ABS, Y	*/ AbsoluteY,
		/* Indirect */ Indirect,
		/* (IND, X) */ IndexedIndirect,
		/* (IND), Y */ IndirectIndexed,
	};

	enum class InstructionType : uint8_t {
		/* Access		*/ LDA = 0, STA, LDX, STX, LDY, STY,
		/* Transfer		*/ TAX, TXA, TAY, TYA,
		/* Arithmetic	*/ ADC, SBC, INC, DEC, INX, DEX, INY, DEY,
		/* Shift		*/ ASL, LSR, ROL, ROR,
		/* Bitwise		*/ AND, ORA, EOR, BIT,
		/* Compare		*/ CMP, CPX, CPY,
		/* Branch		*/ BCC, BCS, BEQ, BNE, BPL, BMI, BVC, BVS,
		/* Jump			*/ JMP, JSR, RTS, BRK, RTI,
		/* Stack		*/ PHA, PLA, PHP, PLP, TXS, TSX,
		/* Flags		*/ CLC, SEC, CLI, SEI, CLD, SED, CLV,
		/* Other		*/ NOP,
	};

	class Instruction {
	public:
		Instruction() = default;
		~Instruction() = default;

		auto decode(const uint8_t opcode) -> void {
			if (opcode == 0xE8) {
				m_addressingMode = AddressingMode::Implied;
				m_type = InstructionType::INX;
				m_bytes = 1;
				m_cycles = 2;
			}
		}

		auto get_addressing_mode() const -> AddressingMode {
			return m_addressingMode;
		}
		auto get_type() const -> InstructionType {
			return m_type;
		}
		auto get_bytes() const -> uint8_t {
			return m_bytes;
		}
		auto get_cycles() const -> uint8_t {
			return m_cycles;
		}

	private:
		AddressingMode m_addressingMode{};
		InstructionType m_type{};
		uint8_t m_bytes{};
		uint8_t m_cycles{};
	};
}