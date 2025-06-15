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
		/* Relative	*/ Relative,
		/* Absolute	*/ Absolute,
		/* ABS, X	*/ AbsoluteX,
		/* ABS, Y	*/ AbsoluteY,
		/* Indirect	*/ Indirect,
		/* (IND, X)	*/ IndexedIndirect,
		/* (IND), Y	*/ IndirectIndexed,
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

	struct Instruction {
		AddressingMode addressingMode{};
		InstructionType type{};
		uint8_t bytes{};
		uint8_t cycles{};
		uint8_t extraCycles{};
	};

	constexpr auto make_instruction_set() -> std::array<Instruction, 256> {
		using AM = AddressingMode;
		using IT = InstructionType;
		std::array<Instruction, 256> instructionSet{};
		
		instructionSet[0x69] = { AM::Immediate, IT::ADC, 2, 2 };
		instructionSet[0x65] = { AM::ZeroPage, IT::ADC, 2, 3 };
		instructionSet[0x75] = { AM::ZeroPageX, IT::ADC, 2, 4 };
		instructionSet[0x6D] = { AM::Absolute, IT::ADC, 3, 4 };
		instructionSet[0x7D] = { AM::AbsoluteX, IT::ADC, 3, 4, 1 };
		instructionSet[0x79] = { AM::AbsoluteY, IT::ADC, 3, 4, 1 };
		instructionSet[0x61] = { AM::IndexedIndirect, IT::ADC, 2, 6 };
		instructionSet[0x71] = { AM::IndirectIndexed, IT::ADC, 2, 5, 1 };

		instructionSet[0x29] = { AM::Immediate, IT::AND, 2, 2 };
		instructionSet[0x25] = { AM::ZeroPage, IT::AND, 2, 3 };
		instructionSet[0x35] = { AM::ZeroPageX, IT::AND, 2, 4 };
		instructionSet[0x2D] = { AM::Absolute, IT::AND, 3, 4 };
		instructionSet[0x3D] = { AM::AbsoluteX, IT::AND, 3, 4, 1 };
		instructionSet[0x39] = { AM::AbsoluteY, IT::AND, 3, 4, 1 };
		instructionSet[0x21] = { AM::IndexedIndirect, IT::AND, 2, 6 };
		instructionSet[0x31] = { AM::IndirectIndexed, IT::AND, 2, 5, 1 };

		instructionSet[0x0A] = { AM::Accumulator, IT::ASL, 1, 2 };
		instructionSet[0x06] = { AM::ZeroPage, IT::ASL, 2, 5 };
		instructionSet[0x16] = { AM::ZeroPageX, IT::ASL, 2, 6 };
		instructionSet[0x0E] = { AM::Absolute, IT::ASL, 3, 6 };
		instructionSet[0x1E] = { AM::AbsoluteX, IT::ASL, 3, 7 };

		instructionSet[0x90] = { AM::Relative, IT::BCC, 2, 2, 2 };

		instructionSet[0xB0] = { AM::Relative, IT::BCS, 2, 2, 2 };

		instructionSet[0xF0] = { AM::Relative, IT::BEQ, 2, 2, 2 };

		instructionSet[0x24] = { AM::ZeroPage, IT::BIT, 2, 3 };
		instructionSet[0x2C] = { AM::Absolute, IT::BIT, 3, 4 };

		instructionSet[0x30] = { AM::Relative, IT::BMI, 2, 2, 2 };

		instructionSet[0xD0] = { AM::Relative, IT::BNE, 2, 2, 2 };

		instructionSet[0x10] = { AM::Relative, IT::BPL, 2, 2, 2 };

		instructionSet[0x00] = { AM::Implied, IT::BRK, 1, 7 };

		instructionSet[0x50] = { AM::Relative, IT::BVC, 2, 2, 2 };

		instructionSet[0x70] = { AM::Relative, IT::BVS, 2, 2, 2 };

		instructionSet[0x18] = { AM::Implied, IT::CLC, 1, 2 };

		instructionSet[0xD8] = { AM::Implied, IT::CLD, 1, 2 };

		instructionSet[0x58] = { AM::Implied, IT::CLI, 1, 2 };

		instructionSet[0xB8] = { AM::Implied, IT::CLV, 1, 2 };

		instructionSet[0xC9] = { AM::Immediate, IT::CMP, 2, 2 };
		instructionSet[0xC5] = { AM::ZeroPage, IT::CMP, 2, 3 };
		instructionSet[0xD5] = { AM::ZeroPageX, IT::CMP, 2, 4 };
		instructionSet[0xCD] = { AM::Absolute, IT::CMP, 3, 4 };
		instructionSet[0xDD] = { AM::AbsoluteX, IT::CMP, 3, 4, 1 };
		instructionSet[0xD9] = { AM::AbsoluteY, IT::CMP, 3, 4, 1 };
		instructionSet[0xC1] = { AM::IndexedIndirect, IT::CMP, 2, 6 };
		instructionSet[0xD1] = { AM::IndirectIndexed, IT::CMP, 2, 5, 1 };

		instructionSet[0xE0] = { AM::Immediate, IT::CPX, 2, 2 };
		instructionSet[0xE4] = { AM::ZeroPage, IT::CPX, 2, 3 };
		instructionSet[0xEC] = { AM::Absolute, IT::CPX, 3, 4 };

		instructionSet[0xC0] = { AM::Immediate, IT::CPY, 2, 2 };
		instructionSet[0xC4] = { AM::ZeroPage, IT::CPY, 2, 3 };
		instructionSet[0xCC] = { AM::Absolute, IT::CPY, 3, 4 };

		instructionSet[0xC6] = { AM::ZeroPage, IT::DEC, 2, 5 };
		instructionSet[0xD6] = { AM::ZeroPageX, IT::DEC, 2, 6 };
		instructionSet[0xCE] = { AM::Absolute, IT::DEC, 3, 6 };
		instructionSet[0xDE] = { AM::AbsoluteX, IT::DEC, 3, 7 };

		instructionSet[0xCA] = { AM::Implied, IT::DEX, 1, 2 };

		instructionSet[0x88] = { AM::Implied, IT::DEY, 1, 2 };

		instructionSet[0x49] = { AM::Immediate, IT::EOR, 2, 2 };
		instructionSet[0x45] = { AM::ZeroPage, IT::EOR, 2, 3 };
		instructionSet[0x55] = { AM::ZeroPageX, IT::EOR, 2, 4 };
		instructionSet[0x4D] = { AM::Absolute, IT::EOR, 3, 4 };
		instructionSet[0x5D] = { AM::AbsoluteX, IT::EOR, 3, 4, 1 };
		instructionSet[0x59] = { AM::AbsoluteY, IT::EOR, 3, 4, 1 };
		instructionSet[0x41] = { AM::IndexedIndirect, IT::EOR, 2, 6 };
		instructionSet[0x51] = { AM::IndirectIndexed, IT::EOR, 2, 5, 1 };

		instructionSet[0xE6] = { AM::ZeroPage, IT::INC, 2, 5 };
		instructionSet[0xF6] = { AM::ZeroPageX, IT::INC, 2, 6 };
		instructionSet[0xEE] = { AM::Absolute, IT::INC, 3, 6 };
		instructionSet[0xFE] = { AM::AbsoluteX, IT::INC, 3, 7 };

		instructionSet[0xE8] = { AM::Implied, IT::INX, 1, 2 };

		instructionSet[0xC8] = { AM::Implied, IT::INY, 1, 2 };

		instructionSet[0x4C] = { AM::Absolute, IT::JMP, 3, 3 };
		instructionSet[0x6C] = { AM::Indirect, IT::JMP, 3, 5 };

		instructionSet[0x20] = { AM::Absolute, IT::JSR, 3, 6 };

		instructionSet[0xA9] = { AM::Immediate, IT::LDA, 2, 2 };
		instructionSet[0xA5] = { AM::ZeroPage, IT::LDA, 2, 3 };
		instructionSet[0xB5] = { AM::ZeroPageX, IT::LDA, 2, 4 };
		instructionSet[0xAD] = { AM::Absolute, IT::LDA, 3, 4 };
		instructionSet[0xBD] = { AM::AbsoluteX, IT::LDA, 3, 4, 1 };
		instructionSet[0xB9] = { AM::AbsoluteY, IT::LDA, 3, 4, 1 };
		instructionSet[0xA1] = { AM::IndexedIndirect, IT::LDA, 2, 6 };
		instructionSet[0xB1] = { AM::IndirectIndexed, IT::LDA, 2, 5, 1 };

		instructionSet[0xA2] = { AM::Immediate, IT::LDX, 2, 2 };
		instructionSet[0xA6] = { AM::ZeroPage, IT::LDX, 2, 3 };
		instructionSet[0xB6] = { AM::ZeroPageY, IT::LDX, 2, 4 };
		instructionSet[0xAE] = { AM::Absolute, IT::LDX, 3, 4 };
		instructionSet[0xBE] = { AM::AbsoluteY, IT::LDX, 3, 4, 1 };

		instructionSet[0xA0] = { AM::Immediate, IT::LDY, 2, 2 };
		instructionSet[0xA4] = { AM::ZeroPage, IT::LDY, 2, 3 };
		instructionSet[0xB4] = { AM::ZeroPageX, IT::LDY, 2, 4 };
		instructionSet[0xAC] = { AM::Absolute, IT::LDY, 3, 4 };
		instructionSet[0xBC] = { AM::AbsoluteX, IT::LDY, 3, 4, 1 };

		instructionSet[0x4A] = { AM::Accumulator, IT::LSR, 1, 2 };
		instructionSet[0x46] = { AM::ZeroPage, IT::LSR, 2, 5 };
		instructionSet[0x56] = { AM::ZeroPageX, IT::LSR, 2, 6 };
		instructionSet[0x4E] = { AM::Absolute, IT::LSR, 3, 6 };
		instructionSet[0x5E] = { AM::AbsoluteX, IT::LSR, 3, 7 };

		instructionSet[0xEA] = { AM::Implied, IT::NOP, 1, 2 };

		instructionSet[0x09] = { AM::Immediate, IT::ORA, 2, 2 };
		instructionSet[0x05] = { AM::ZeroPage, IT::ORA, 2, 3 };
		instructionSet[0x15] = { AM::ZeroPageX, IT::ORA, 2, 4 };
		instructionSet[0x0D] = { AM::Absolute, IT::ORA, 3, 4 };
		instructionSet[0x1D] = { AM::AbsoluteX, IT::ORA, 3, 4, 1 };
		instructionSet[0x19] = { AM::AbsoluteY, IT::ORA, 3, 4, 1 };
		instructionSet[0x01] = { AM::IndexedIndirect, IT::ORA, 2, 6 };
		instructionSet[0x11] = { AM::IndirectIndexed, IT::ORA, 2, 5, 1 };

		instructionSet[0x48] = { AM::Implied, IT::PHA, 1, 3 };

		instructionSet[0x08] = { AM::Implied, IT::PHP, 1, 3 };

		instructionSet[0x68] = { AM::Implied, IT::PLA, 1, 4 };

		instructionSet[0x28] = { AM::Implied, IT::PLP, 1, 4 };

		instructionSet[0x2A] = { AM::Accumulator, IT::ROL, 1, 2 };
		instructionSet[0x26] = { AM::ZeroPage, IT::ROL, 2, 5 };
		instructionSet[0x36] = { AM::ZeroPageX, IT::ROL, 2, 6 };
		instructionSet[0x2E] = { AM::Absolute, IT::ROL, 3, 6 };
		instructionSet[0x3E] = { AM::AbsoluteX, IT::ROL, 3, 7 };

		instructionSet[0x6A] = { AM::Accumulator, IT::ROR, 1, 2 };
		instructionSet[0x66] = { AM::ZeroPage, IT::ROR, 2, 5 };
		instructionSet[0x76] = { AM::ZeroPageX, IT::ROR, 2, 6 };
		instructionSet[0x6E] = { AM::Absolute, IT::ROR, 3, 6 };
		instructionSet[0x7E] = { AM::AbsoluteX, IT::ROR, 3, 7 };

		instructionSet[0x40] = { AM::Implied, IT::RTI, 1, 6 };

		instructionSet[0x60] = { AM::Implied, IT::RTS, 1, 6 };

		instructionSet[0xE9] = { AM::Immediate, IT::SBC, 2, 2 };
		instructionSet[0xE5] = { AM::ZeroPage, IT::SBC, 2, 3 };
		instructionSet[0xF5] = { AM::ZeroPageX, IT::SBC, 2, 4 };
		instructionSet[0xED] = { AM::Absolute, IT::SBC, 3, 4 };
		instructionSet[0xFD] = { AM::AbsoluteX, IT::SBC, 3, 4, 1 };
		instructionSet[0xF9] = { AM::AbsoluteY, IT::SBC, 3, 4, 1 };
		instructionSet[0xE1] = { AM::IndexedIndirect, IT::SBC, 2, 6 };
		instructionSet[0xF1] = { AM::IndirectIndexed, IT::SBC, 2, 5, 1 };

		instructionSet[0x38] = { AM::Implied, IT::SEC, 1, 2 };

		instructionSet[0xF8] = { AM::Implied, IT::SED, 1, 2 };

		instructionSet[0x78] = { AM::Implied, IT::SEI, 1, 2 };

		instructionSet[0x85] = { AM::ZeroPage, IT::STA, 2, 3 };
		instructionSet[0x95] = { AM::ZeroPageX, IT::STA, 2, 4 };
		instructionSet[0x8D] = { AM::Absolute, IT::STA, 3, 4 };
		instructionSet[0x9D] = { AM::AbsoluteX, IT::STA, 3, 5 };
		instructionSet[0x99] = { AM::AbsoluteY, IT::STA, 3, 5 };
		instructionSet[0x81] = { AM::IndexedIndirect, IT::STA, 2, 6 };
		instructionSet[0x91] = { AM::IndirectIndexed, IT::STA, 2, 6 };

		instructionSet[0x86] = { AM::ZeroPage, IT::STX, 2, 3 };
		instructionSet[0x96] = { AM::ZeroPageY, IT::STX, 2, 4 };
		instructionSet[0x8E] = { AM::Absolute, IT::STX, 3, 4 };

		instructionSet[0x84] = { AM::ZeroPage, IT::STY, 2, 3 };
		instructionSet[0x94] = { AM::ZeroPageX, IT::STY, 2, 4 };
		instructionSet[0x8C] = { AM::Absolute, IT::STY, 3, 4 };

		instructionSet[0xAA] = { AM::Implied, IT::TAX, 1, 2 };

		instructionSet[0xA8] = { AM::Implied, IT::TAY, 1, 2 };

		instructionSet[0xBA] = { AM::Implied, IT::TSX, 1, 2 };

		instructionSet[0x8A] = { AM::Implied, IT::TXA, 1, 2 };

		instructionSet[0x9A] = { AM::Implied, IT::TXS, 1, 2 };

		instructionSet[0x98] = { AM::Implied, IT::TYA, 1, 2 };

		return instructionSet;
	}

	static constexpr auto instructionSet = make_instruction_set();

	constexpr auto decode_instruction(const uint8_t opcode) -> Instruction {
		return instructionSet[opcode];
	}
}