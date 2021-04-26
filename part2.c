#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"

// forward declarations
void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_auipc(Instruction, Processor *);
void execute_lui(Instruction, Processor *);

void execute_instruction(Instruction instruction,Processor *processor,Byte *memory) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  (*processor).PC+=4; //  Aumentamos el valor del pc en bytes para asegurar que apunte a 
                      // La siguiente instruccion que se ejecutara despues de la actual.
          
  unsigned int opcode = instruccion.opcode; //Obtenemos el opcode de la instruccion.

  switch(opcode) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x33:
      execute_rtype(instruction, processor);
      processor->PC += 4;
      break;
    case 0x03:
      execute_load(instruction, processor, memory);
      processor->PC += 4;
      break;
    case 0x13:
      execute_itype_except_load(instruction, processor);
      processor->PC += 4;
      break;
    case 0x73:
      execute_ecall(processor, memory);
      processor->PC += 4;
      break;        
    case 0x23:
      execute_store(instruction, processor, memory);
      processor->PC += 4;
      break;
    case 0x63:
      execute_branch(instruction, processor);
      break;
    case 0x17:
      execute_auipc(instruction, processor);
      break;
    case 0x67:
      execute_jalr(instruction, processor);
      break;
    case 0x37:
      execute_lui(instruction, processor);
      processor->PC += 4;
      break;
    case 0x6f:
      execute_jal(instruction, processor);
      break;
    default: // undefined opcode
      handle_invalid_instruction(instruction);
      exit(0);
      break;
  }
}

void execute_rtype(Instruction instruction, Processor *processor) {
  unsigned int function7 = instruction.rtype.funct7; //Encontramos el Funct7 para diferenciar casos posibles
  unsigned int function3 = instruction.rtype.funct3;
  unsigned int rd = instruction.rtype.rd; //Encontramos el registro destino (posicion)
  unsigned int rs1 = instruction.rtype.rs1; // Encontramos el primer registro (posicion)
  unsigned int rs2 = instruction.rtype.rs2; //Encontramos el segundo regisro (posicion)

  switch (function3){
    case 0x0:
      switch(function7){
        case 0x00:
          int add1 = processor->R[rs1];
          int add2 = processor->R[rs2];
          processor->R[rd] = add1 + add2;
          break;

        case 0x01: 
          int mul1 = processor->R[rs1];
          int mul2 = processor->R[rs2];
          processor->R[rd] = mul1 * mul2;
          break;

        case 0x20:
          int sub1 = processor->E[rs1];
          int sub2 = processor->R[rs2];
          processor->R[rd]= sub1 - sub2;
          break;
        
        default:
          handle_invalid_instruction(instruction);
          exit(0);
          break;
      }

    case 0x1:
      switch(function7){
        case 0x00:
          unsigned int sft1 = processor->R[rs1];
          int sft2 = processor->R[rs2];
          processor->R[rd] = sft1 << sft2;
          break;

        case 0x01:
          sDouble mulh1 = processor->R[rs1];
          sDouble mulh2 = processor->R[rs2];
          sDouble result = mulh1 * mulh2;
          processor->R[rd] = result >> 32;
        
        default:
          handle_invalid_instruction(Instruction);
          exit(0);
          break;
      }
    case 0x2:
      int slt1 = processor->R[rs1];
      int slt2 = processor->R[rs2];
      if(slt1 < slt2){
        processor->R[rd] = 1;
      }else{
        processor->R[rd] = 0;
      }
      break;
    
    case 0x4:
      switch (function7){
        case 0x00:
          unsigned int xor1 = processor->R[rs1];
          unsigned int xor2 = processor->R[rs2];
          processor->R[rd] = xor1 ^ xor2;
          break;
        
        case 0x01:
          int div1 = processor->R[rs1];
          int div2 = processor->R[rs2];
          processor->R[rd] = div1 / div2;
          break;
      
        default:
          handle_invalid_instruction(Instruction);
          exit(0)
          break;
      }
    
    case 0x5:
      switch(function7){
        case 0x00:
          unsigned int srl1 = processor->R[rs1];
          int srl2 = processor->R[rs2];
          processor->R[rd] = srl1 >> srl2;
          break;
        
        case 0x20:
          int sra1 = processor->R[rs1];
          int sra2 = processor->R[rs2];
          processor->R[rd] = sra1 >> sra2;
          break;

        default:
          handle_invalid_instruction(Instruction);
          exit(0);
          break;

      }
    
    case 0x6:
      switch(function7){
        case 0x00:
          unsigned int or1 = processor->R[rs1];
          unsigned int or2 = processor->R[rs2];
          processor->R[rd] = rem1 % rem2;
          break;

        default:
          handle_invalid_instruction(Instruction);
          exit(0);
          break;
      }

    case 0x7:
      unsigned int and1 = processor->[rs1];
      unsigned int and2 = processor->[rs2];
      processor->R[rd] = and1 & and2;
      break;

    default:
      handle_invalid_instruction(Instruction);
      exit(0);
      break;
  }
}

void execute_itype_except_load(Instruction instruction, Processor *processor) {
  unsigned int function7 = instruction.itype.funct7; //Encontramos el Funct7 para diferenciar casos posibles
  unsigned int function3 = instruction.itype.funct3;
  unsigned int rd = instruction.itype.rd; //Encontramos el registro destino (posicion)
  unsigned int rs1 = instruction.itype.rs1; // Encontramos el primer registro (posicion)
  unsigned int imm = instruction.itype.imm;

  switch(function3) { // What do we switch on?
        /* YOUR CODE HERE */
    case 0x0:
      int addi1 = processor->R[rs1];
      int addi2 = bitSigner(imm, 12);
      processor->R[rd] = addi1 + addi2;
      break;

    case 0x1:
      unsigned int slli1 = processor->R[rs1];
      int slli2 = imm;
      processor->R[rd] = slli1 << slli2;
      break;

    case 0x2:
      int slti1 = processor->R[rs1];
      int slti2 = bitSigner(imm, 12);
      if (slti1 < slti2) {
        processor->R[rd] = 1;
      } else {
        processor->R[rd] = 0;
      }
      break;

    case 0x4:
      unsigned int xori1 = processor->R[rs1];
      unsigned int xori2 = bitSigner(imm, 12);
      processor->R[rd] = xori1 ^ xori2;
      break;

    case 0x5:
      switch(imm >> 5) {

        case 0x00:
          unsigned int srli1 = processor->R[rs1];
          int srli2 = imm;
          processor->R[rd] = srli1 >> srli2;
          break;

        case 0x20:
          int srai1 = processor->R[rs1];
          int srai2 = imm;
          processor->R[rd] = srai1 >> srai2;
          break;

        default:
          handle_invalid_instruction(instruction);
          exit(0);
          break;
      }

    case 0x6:
      unsigned int ori1 = processor->R[rs1];
      unsigned int ori2 = bitSigner(imm, 12);
      processor->R[rd] = ori1 | ori2;
      break;

    case 0x7:
      unsigned int andi1 = processor->R[rs1];
      unsigned int andi2 = bitSigner(imm, 12);
      processor->R[rd] = andi1 & andi2;
      break;

    default:
      handle_invalid_instruction(instruction);
      exit(0);
      break;
    }
}

void execute_ecall(Processor *p, Byte *memory) {
  switch(p->R[10]) { // What do we switch on?
    case 1:
      printf("%d", p->R[11]);
      break;

    case 10:
      printf("exiting the simulator\n");
      exit(0);
      break;

    default: // undefined ecall
      printf("Illegal ecall number %d\n", -1); // What stores the ecall arg?
      exit(0);
      break;
    }
}

void execute_branch(Instruction instruction, Processor *processor) {
  unsigned int rs1 = instruction.sbtype.rs1;
  unsigned int rs2 = instruction.sbtype.rs2;
  int branchaddr = processor->PC + bitSigner(get_branch_offset(instruction), 13);
  int eq1 = processor->R[rs1];
  int eq2 = processor->R[rs2];
    /* Remember that the immediate portion of branches
       is counting half-words, so make sure to account for that. */
    switch(instruction.sbtype.funct3) { // What do we switch on?
        case 0x0:
          if (eq1 == eq2) {
            processor->PC = branchaddr;
          } else {
            processor->PC += 4;
          }
          break;
        case 0x1:
          if (eq1 != eq2) {
            processor->PC = branchaddr;
          } else {
            processor->PC += 4;
          }
          break;
        /* YOUR CODE HERE */
        default:
            handle_invalid_instruction(instruction);
            exit(0);
            break;
    }
}

void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
  unsigned int rd = instruction.itype.rd;
  unsigned int rs1 = instruction.itype.rs1;
  unsigned int imm = instruction.itype.imm;

  switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
    case 0x0:
      processor->R[rd] = load(memory, processor->R[rs1] + bitSigner(instruction.itype.imm, 12), LENGTH_BYTE, 0);
      break;
    case 0x1:
      processor->R[rd] = load(memory, processor->R[rs1] + bitSigner(imm, 12), LENGTH_HALF_WORD, 0);
      break;
    case 0x2:
      processor->R[rd] = load(memory, processor->R[rs1] + bitSigner(imm, 12), LENGTH_WORD, 0);
      break;
    default:
      handle_invalid_instruction(instruction);
      exit(0);
      break;
  }
}

void execute_store(Instruction instruction, Processor *processor, Byte *memory) {
  unsigned int rs1 = instruction.stype.rs1;
  unsigned int rs2 = instruction.stype.rs2;
  unsigned int function3 = instruction.stype.funct3;

  switch(function3) {
        /* YOUR CODE HERE */
    case 0x0:
      store(memory, processor->R[rs1] + get_store_offset(instruction), LENGTH_BYTE, processor->R[rs2], 0);
      break;
    case 0x1:
      store(memory, processor->R[rs1] + get_store_offset(instruction), LENGTH_HALF_WORD, processor->R[rs2], 0);
      break;
    case 0x2:
      store(memory, processor->R[rs1] + get_store_offset(instruction), LENGTH_WORD, processor->R[rs2], 0);
      break;
    default:
      handle_invalid_instruction(instruction);
      exit(0);
      break;
  }
}

void execute_jalr(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  int imm = bitSigner(instruction.itype.imm, 12);
  unsigned int rd = instruction.itype.rd;
  unsigned int rs1 = instruction.itype.rs1;

  processor->R[rd] = processor->PC + 4;
  processor->PC = R[rs1] + imm;
}

void execute_jal(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  unsigned int rd = instruction.ujtype.rd;
  int nextPC = processor->PC + get_jump_offset(instruction);

  processor->R[rd] = processor->PC + 4;
  processor->PC = nextPC;

}


void execute_auipc(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  unsigned int rd = instruction.ujtype.rd;
  int imm = bitSigner(instruction.utype.imm, 32) << 12;
  processor->R[rd] = processor->PC + imm;
}

void execute_lui(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  int imm = bitSigner(instruction.utype.imm, 32) << 12;
  int rd = instruction.utype.rd;
  processor->R[rd] = imm;
}

/* Checks that the address is aligned correctly */
int check(Address address, Alignment alignment) {
  if (address > 0 && address < MEMORY_SPACE) {
    // byte align
    if (alignment == LENGTH_BYTE) return 1;
    // half align
    if (alignment == LENGTH_HALF_WORD) return ((address % 2) == 0);
    // word align
    if (alignment == LENGTH_WORD) return ((address % 4) == 0);
  }
  return 0;
}

void store(Byte *memory, Address address, Alignment alignment, Word value, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_write(address);
  }
  /* YOUR CODE HERE */
  if (alignment == LENGTH_BYTE) {
      memory[address] = value & 0xFF;
  
  } else if (alignment == LENGTH_HALF_WORD) {
      memory[address] = value & 0xFF;
      memory[address + 1] = (value >> 8) & 0xFF;

  } else if (alignment == LENGTH_WORD) {
      memory[address] = value & 0xFF;
      memory[address + 1] = (value >> 8) & 0xFF;
      memory[address + 2] = (value >> 16) & 0xFF;
      memory[address + 3] = (value >> 24) & 0xFF;
    }
}

Word load(Byte *memory, Address address, Alignment alignment, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_read(address);
  }
  /* YOUR CODE HERE */
  uint32_t data = 0;
  if (alignment == LENGTH_BYTE) {
    data = bitSigner(memory[address], 8);
  } else if (alignment == LENGTH_HALF_WORD) {
      data = memory[address + 1];
      data = (data << 8) | memory[address];
      data = bitSigner(data, 16);
  } else if (alignment == LENGTH_WORD) {
      data = memory[address + 3];
      data = (data << 8) | memory[address + 2];
      data = (data << 8) | memory[address + 1];
      data = (data << 8) | memory[address];
  }
    return data;
}

//sssssssssssssssssssssssssssssssssss