#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"


// forward declarations
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_auipc(Instruction);
void write_lui(Instruction);
void write_jalr(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);


void decode_instruction(Instruction instruction) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */

  unsigned int opcode = instruction.opcode


  switch(opcode) { // What do we switch on?
    /* YOUR CODE HERE */


    case 51: //Valor decimal del opcode tipo R
    write_rtype(instruction);
    break;

    default: // undefined opcode
      handle_invalid_instruction(instruction);
      break;
  }
}




void write_rtype(Instruction instruction) {


  unsigned int function7 = instruction.rtype.funct7;

  switch(function7) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0: 
      switch (instruction.rtype.funct3){ //Switch del funct3 para diferenciar los casos 

        case 0: //colocamos el caso del add
        print_rtype("add", instruction); // Llamamos a la funcion print_rtype
        break;

        default:
        handle_invalid_instruction(instruction);
        break;
      
      
      } break;


    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_itype_except_load(Instruction instruction) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_load(Instruction instruction) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_store(Instruction instruction) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_branch(Instruction instruction) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction) {
  /* YOUR CODE HERE */
}


void write_lui(Instruction instruction) {
  /* YOUR CODE HERE */
}


void write_jalr(Instruction instruction) {
  /* YOUR CODE HERE */
}


void write_jal(Instruction instruction) {
  /* YOUR CODE HERE */
}


void write_ecall(Instruction instruction) {
  /* YOUR CODE HERE */
}


void print_rtype(char *name, Instruction instruction) {
  /* YOUR CODE HERE */

  unsigned int rd = instruction.rtype.rd; //obtemenos rd
  unsigned int rs1 = instruction.rtype.rs1; // obtenemos rs1
  unsigned int rs2 = instruction.rtype.rs2; // obtenemos rs2
  printf(RTYPE_FORMAT , name , rd , rs1 , rs2); // Hacemos el print de la instruccion


}


void print_itype_except_load(char *name, Instruction instruction, int imm) {
  /* YOUR CODE HERE */
}


void print_load(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
}


void print_store(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
}


void print_branch(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
}
