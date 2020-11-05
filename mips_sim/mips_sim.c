// COMP1521 20T3 Assignment 1: mips_sim -- a MIPS simulator
// starting point code v0.1 - 13/10/20
// Written by Zheng Luo (z5206267) from 18/10/2020 to 20/10/2020

/*
//////////////////////////////////////////////////////////////////////// 
//                          Approach Rundown                          // 
////////////////////////////////////////////////////////////////////////

The execute_instructions function has been designed into two general parts 
based on the statu of trace_mode, first part is consist by instruction_processor, 
which decomposes all input instructions, and prints out all required information.
In contrast, second part is core by simplied_instruction_processor,
which computes all instructions as well, but only prints out the outputs.

Both functions are highly similar, so please let me quickly introduce the inside
of function instruction_processor. 
Instruction_processor is also designed into two parts, 
first category is organised for instructions who do not have I component,
for example, add, sub, slt, mul, and syscall. 
The corresponding mask MASK_WITHOUT_I is initiated to fit for this category.
Similarly, second part is for I component, specified masks are also generated
in order to obtain the desired information by applying AND operation with 
the input instruction.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

//////////////////////////////////////////////////////////////////////// 
//                          Define Section                            // 
////////////////////////////////////////////////////////////////////////
// General definition.
#define MAX_LINE_LENGTH 256
#define INSTRUCTIONS_GROW 64
// The definition of syscall.
#define SYSCALL_PRINT_INT 1
#define SYSCALL_EXIT 10
#define SYSCALL_PRINT_CHARACTER 11
// The definition of register.
#define RETURN_VALUE_V0 2
#define PARAMETER_FUNCTION_A0 4
#define NUMBER_OF_REGISTER 31
// The definition of bit operation.
#define DESTINATION_LOW_BIT 12
#define I_HIGH_BIT 16
#define T_LOW_BIT 17
#define SOURCE_LOW_BIT 22

// The definition of bitwise instruction. (Without I category)
// add $d, $s, $t	d = s + t	000000ssssstttttddddd00000100000
#define INSTRUCTIONS_ADD        0x00000020
// sub $d, $s, $t	d = s - t	000000ssssstttttddddd00000100010
#define INSTRUCTIONS_SUB        0x00000022
// slt $d, $s, $t	d = s < t	000000ssssstttttddddd00000101010
// If $s is less than $t, $d is set to one. It gets zero otherwise.
#define INSTRUCTIONS_SLT        0x0000002A
// mul $d, $s, $t	d = s * t	011100ssssstttttddddd00000000010
#define INSTRUCTIONS_MUL        0x70000002
// syscall	        syscall	    00000000000000000000000000001100
#define INSTRUCTIONS_SYSCALL    0x0000000C
// Mask for those instructions which do not have I term
// AND operation with this mask, can filter variables out
// MASK_WITHOUT_I in bit pattern 11111100000000000000011111111111
#define MASK_WITHOUT_I           0xFC0007FF

// The definition of bitwise instruction. (With I category)
// MASK_WITH_I in bit pattern    11111100000000000000000000000000
#define MASK_WITH_I              0xFC000000
// beq $s, $t, I	if (s == t) PC += I	000100ssssstttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_BEQ        0x10000000
// bne $s, $t, I	if (s != t) PC += I	000101ssssstttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_BNE        0x14000000
// addi $t, $s, I	t = s + I	001000ssssstttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_ADDI       0x20000000
// ori $t, $s, I	t = s | I	001101ssssstttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_ORI        0x34000000
// lui $t, I	t = I << 16	    00111100000tttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_LUI        0x3C000000
// MASK_FOR_SOURCE_S            00000011111000000000000000000000
#define MASK_FOR_SOURCE_S       0x03E00000
// MASK_FOR_SOURSE_T            00000000000111110000000000000000
#define MASK_FOR_SOURCE_T       0x001F0000
// MASK_FOR_DESTINATION         00000000000000001111100000000000
#define MASK_FOR_DESTINATION    0x0000F800
// MASK_FOR_I                   00000000000000001111111111111111
#define MASK_FOR_I              0x0000FFFF

//////////////////////////////////////////////////////////////////////// 
//                       Function Prototypes                          // 
////////////////////////////////////////////////////////////////////////
void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode);
char *process_arguments(int argc, char *argv[], int *trace_mode);
uint32_t *read_instructions(char *filename, int *n_instructions_p);
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions);

// Self-created function prototypes below.
int instruction_processor(int pc, uint32_t instruction, 
                          int array_register[NUMBER_OF_REGISTER]);
int simplied_instruction_processor(int pc, uint32_t instruction, 
                                   int array_register[NUMBER_OF_REGISTER]);
void illegal_branch_msg(int pc);




//////////////////////////////////////////////////////////////////////// 
//                          Main function                             // 
////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int trace_mode;
    char *filename = process_arguments(argc, argv, &trace_mode);

    int n_instructions;
    uint32_t *instructions = read_instructions(filename, &n_instructions);

    execute_instructions(n_instructions, instructions, trace_mode);

    free(instructions);
    return 0;
}

//////////////////////////////////////////////////////////////////////// 
//                           functions                                // 
////////////////////////////////////////////////////////////////////////
// Simulate execution of instruction codes in instructions array,
// output from syscall instruction & any error messages are printed.
//
// if trace_mode != 0:
// information is printed about each instruction as it executed.
//
// execution stops if it reaches the end of the array.

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode) {

    int pc = 0;
    // Initial a array used to store values into registers.
    int array_register[NUMBER_OF_REGISTER] = {0};


    while (pc < n_instructions) {
        // Print each instruction mode.
        if (trace_mode) {
            printf("%d: 0x%08X", pc, instructions[pc]);
            // Decompose 32 bit pattern instructions, 
            // and prints all information.
            pc = instruction_processor(pc, instructions[pc], array_register);
        }
        // Only print result mode.
        else if (trace_mode == 0) {
            pc = simplied_instruction_processor(pc, instructions[pc], 
            array_register);
        }
        pc++;
    }
}


//////////////////////////////////////////////////////////////////////// 
//                       Self-created functions                       // 
////////////////////////////////////////////////////////////////////////

/*
Instruction_processor and simplied_instruction_process are similar, but first
prints out all outputs line by line, the latter one only prints out the result.
Both functions take pc (counter), instruction (bitwise input), and 
array_register as inputs, and produce pc (counter) as output.
Both functions decompose instructions by applying AND opearation 
with appropriate mask, and store information into array_register, print out
information according to the statu of trace_mode.
*/
int instruction_processor(int pc, uint32_t instruction, 
                          int array_register[NUMBER_OF_REGISTER]){
    // Mask and bitwise opeartions.
    uint32_t instruction_filtered_without_i = instruction & MASK_WITHOUT_I;
    uint32_t destination_modified = 
    (instruction & MASK_FOR_DESTINATION) >> (DESTINATION_LOW_BIT - 1);
    uint32_t source_t_modified = 
    (instruction & MASK_FOR_SOURCE_T) >> (T_LOW_BIT - 1);
    uint32_t source_s_modified = 
    (instruction & MASK_FOR_SOURCE_S) >> (SOURCE_LOW_BIT - 1);
    // Computer can recognise negative number with int16_t.
    int16_t instruction_i = instruction & MASK_FOR_I;

    if (instruction_filtered_without_i == INSTRUCTIONS_ADD) {
        printf(" add  $%d, $%d, $%d\n", destination_modified, 
        source_s_modified, source_t_modified);
        // Perform add instruction, and store the result into register.
        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] + 
            array_register[source_t_modified];
            // print out the output.
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[destination_modified]);
        }
        // If destination_modified == 0, do not rewrite the value,
        // as $0 should always be 0.
        else if (destination_modified == 0) {
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[source_s_modified] + 
            array_register[source_t_modified]);
        }
        
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_SUB) {
        printf(" sub  $%d, $%d, $%d\n", destination_modified, 
        source_s_modified, source_t_modified);

        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] - 
            array_register[source_t_modified];
            // print out the output.
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[destination_modified]);
        }
        else if (destination_modified == 0) {
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[source_s_modified] - 
            array_register[source_t_modified]);
        }
        
    }  
    else if (instruction_filtered_without_i == INSTRUCTIONS_SLT) {
        printf(" slt  $%d, $%d, $%d\n", destination_modified, 
        source_s_modified, source_t_modified);
        // SLT -- Set on less than (signed),
        // If $s is less than $t, $d is set to one. It gets zero otherwise.
        if (destination_modified != 0 && 
        (array_register[source_s_modified] < 
        array_register[source_t_modified])) {
            array_register[destination_modified] = 1;
        }
        else {
            array_register[destination_modified] = 0;
        }
        // print out the output.
        printf(">>> $%d = %d\n", destination_modified, 
        array_register[destination_modified]);
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_MUL) {
        printf(" mul  $%d, $%d, $%d\n", destination_modified, 
        source_s_modified, source_t_modified);
        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] * 
            array_register[source_t_modified];
            // print out the output.
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[destination_modified]);
        }
        else if (destination_modified == 0) {
            printf(">>> $%d = %d\n", destination_modified, 
            array_register[source_s_modified] * 
            array_register[source_t_modified]);
        }
        
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_SYSCALL) {
        printf(" syscall\n");
        // $v0 == $2, print out the specified type of syscall.
        printf(">>> syscall %d\n", array_register[RETURN_VALUE_V0]);
        // $a0 == $4, print out the output by syscall.
        // print digit if syscall 1, print character if syscall 11,
        // and exit if syscall 10.
        if (array_register[RETURN_VALUE_V0] == SYSCALL_PRINT_INT) {
            printf("<<< %d\n", array_register[PARAMETER_FUNCTION_A0]);
        }
        else if (array_register[RETURN_VALUE_V0] == SYSCALL_PRINT_CHARACTER) {
            printf("<<< %c\n", array_register[PARAMETER_FUNCTION_A0]);
        }
        else if (array_register[RETURN_VALUE_V0] == SYSCALL_EXIT) {
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Unknown system call: %d\n", 
            array_register[RETURN_VALUE_V0]);
            exit(EXIT_FAILURE);
        }
        
    }
    // If the instruction goes into else,
    // this means instruction includes I inside,
    // different mask will be used in this category.
    else {
        uint32_t instruction_filtered_with_i = instruction & MASK_WITH_I;

        if (instruction_filtered_with_i == INSTRUCTIONS_BEQ) {
            printf(" beq  $%d, $%d, %d\n", source_s_modified, 
            source_t_modified, instruction_i);
            // Branches if the two registers are equal
            if (array_register[source_s_modified] == 
                array_register[source_t_modified]) {
                pc += instruction_i;
                printf(">>> branch taken to PC = %d\n", pc);
                illegal_branch_msg(pc);
                // However in the execution_instruction,
                // pc will be added by one as set in the while loop,
                // we do not wish this happen,
                // so we cancel this +1 by -1.
                pc--;
            }
            else {
                printf(">>> branch not taken\n");
            }
            
            
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_BNE) {
            printf(" bne  $%d, $%d, %d\n", source_s_modified, 
            source_t_modified, instruction_i);
            // Branches if the two registers are not equal
            if (array_register[source_s_modified] != 
                array_register[source_t_modified]) {
                pc += instruction_i;
                printf(">>> branch taken to PC = %d\n", pc);
                illegal_branch_msg(pc);
                pc--;
            } 
            else {
                printf(">>> branch not taken\n");
            }
            

        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_ADDI) {
            printf(" addi $%d, $%d, %d\n", source_t_modified, 
            source_s_modified, instruction_i);
            // Perform addi instruction, and store it into register.
            if (source_t_modified != 0) {
                array_register[source_t_modified] = 
                array_register[source_s_modified] + instruction_i;
                // Print located register and final result.
                printf(">>> $%d = %d\n", source_t_modified, 
                array_register[source_t_modified]);
            } 
            else if (source_t_modified == 0) {
                printf(">>> $%d = %d\n", source_t_modified, 
                array_register[source_s_modified] + instruction_i);
            }
            
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_ORI) {
            printf(" ori  $%d, $%d, %d\n", source_t_modified, 
            source_s_modified, instruction_i);
            // Perform ori instruction, and store the value into register.
            if (source_t_modified != 0) {
                array_register[source_t_modified] = 
                array_register[source_s_modified] | instruction_i;
                // Print detailed procedure.
                printf(">>> $%d = %d\n", source_t_modified, 
                array_register[source_t_modified]);
            }
            else if (source_t_modified == 0) {
                printf(">>> $%d = %d\n", source_t_modified, 
                array_register[source_s_modified] | instruction_i);
            }
            
        }
        // The immediate value is shifted left 16 bits,
        // and stored in the register. The lower 16 bits are zeroes.
        else if (instruction_filtered_with_i == INSTRUCTIONS_LUI) {
            printf(" lui  $%d, %d\n", source_t_modified, instruction_i);
            if (source_t_modified != 0) {
                array_register[source_t_modified] = instruction_i << I_HIGH_BIT;
                printf(">>> $%d = %d\n", source_t_modified, 
                array_register[source_t_modified]);
            }
            else if (source_t_modified == 0) {
                printf(">>> $%d = %d\n", source_t_modified, 
                instruction_i << I_HIGH_BIT);
            }
            

        }
        else {
            printf(" invalid instruction code\n");
            exit(EXIT_FAILURE);
        }
    }
    return pc;
}

int simplied_instruction_processor(int pc, uint32_t instruction, 
                                   int array_register[NUMBER_OF_REGISTER]) {
    uint32_t instruction_filtered_without_i = instruction & MASK_WITHOUT_I;
    uint32_t destination_modified = 
    (instruction & MASK_FOR_DESTINATION) >> (DESTINATION_LOW_BIT - 1);
    uint32_t source_t_modified = 
    (instruction & MASK_FOR_SOURCE_T) >> (T_LOW_BIT - 1);
    uint32_t source_s_modified = 
    (instruction & MASK_FOR_SOURCE_S) >> (SOURCE_LOW_BIT - 1);
    int16_t instruction_i = instruction & MASK_FOR_I;

    if (instruction_filtered_without_i == INSTRUCTIONS_ADD) {
        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] + 
            array_register[source_t_modified];
        }
        
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_SUB) {
        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] - 
            array_register[source_t_modified];
        }
    }  
    else if (instruction_filtered_without_i == INSTRUCTIONS_SLT) {
        if (destination_modified != 0 && 
        (array_register[source_s_modified] < 
        array_register[source_t_modified])) {
            array_register[destination_modified] = 1;
        }
        else {
            array_register[destination_modified] = 0;
        }
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_MUL) {
        if (destination_modified != 0) {
            array_register[destination_modified] = 
            array_register[source_s_modified] * 
            array_register[source_t_modified];
        }
        
    }
    else if (instruction_filtered_without_i == INSTRUCTIONS_SYSCALL) {
        if (array_register[RETURN_VALUE_V0] == SYSCALL_PRINT_INT) {
            printf("%d", array_register[PARAMETER_FUNCTION_A0]);
        }
        else if (array_register[RETURN_VALUE_V0] == SYSCALL_PRINT_CHARACTER) {
            printf("%c", array_register[PARAMETER_FUNCTION_A0]);
        }
        else if (array_register[RETURN_VALUE_V0] == SYSCALL_EXIT) {
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Unknown system call: %d\n", 
            array_register[RETURN_VALUE_V0]);
            exit(EXIT_FAILURE);
        }
        
    }
    else {
        uint32_t instruction_filtered_with_i = instruction & MASK_WITH_I;

        if (instruction_filtered_with_i == INSTRUCTIONS_BEQ) {
            // Branches if the two registers are equal
            if (array_register[source_s_modified] == 
                array_register[source_t_modified]) {
                pc += instruction_i;
                illegal_branch_msg(pc);
                pc--;
            }
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_BNE) {
            // Branches if the two registers are not equal
            if (array_register[source_s_modified] != 
                array_register[source_t_modified]) {
                pc += instruction_i;
                illegal_branch_msg(pc);
                pc--;
            } 
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_ADDI) {
            if (source_t_modified != 0) {
                array_register[source_t_modified] = 
                array_register[source_s_modified] + instruction_i;
            } 
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_ORI) {
            if (source_t_modified != 0) {
                array_register[source_t_modified] = 
                array_register[source_s_modified] | instruction_i;
            }
        }
        else if (instruction_filtered_with_i == INSTRUCTIONS_LUI) {
            if (source_t_modified != 0) {
                array_register[source_t_modified] = instruction_i << I_HIGH_BIT;
            }
        }
        else {
            printf("invalid instruction code\n");
            exit(EXIT_FAILURE);
        }
    }
    return pc;
}

// Illegal_branch_msg prints out the required message if pc (counter) < 0.
void illegal_branch_msg(int pc) {
    if (pc < 0) {
        printf("Illegal branch to address before instructions: PC = %d\n", pc);
        exit(EXIT_FAILURE);
    }
}



//////////////////////////////////////////////////////////////////////// 
//                       Provided functions                           // 
////////////////////////////////////////////////////////////////////////

// check_arguments is given command-line arguments
// it sets *trace_mode to 0 if -r is specified
//          *trace_mode is set to 1 otherwise
// the filename specified in command-line arguments is returned

char *process_arguments(int argc, char *argv[], int *trace_mode) {
    if (
        argc < 2 ||
        argc > 3 ||
        (argc == 2 && strcmp(argv[1], "-r") == 0) ||
        (argc == 3 && strcmp(argv[1], "-r") != 0)) {
        fprintf(stderr, "Usage: %s [-r] <file>\n", argv[0]);
        exit(1);
    }
    *trace_mode = (argc == 2);
    return argv[argc - 1];
}


// read hexadecimal numbers from filename one per line
// numbers are return in a malloc'ed array
// *n_instructions is set to size of the array

uint32_t *read_instructions(char *filename, int *n_instructions_p) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: '%s'\n", strerror(errno), filename);
        exit(1);
    }

    uint32_t *instructions = NULL;
    int n_instructions = 0;
    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, sizeof line, f) != NULL) {

        // grow instructions array in steps of INSTRUCTIONS_GROW elements
        if (n_instructions % INSTRUCTIONS_GROW == 0) {
            instructions = instructions_realloc(instructions, n_instructions + INSTRUCTIONS_GROW);
        }

        char *endptr;
        instructions[n_instructions] = strtol(line, &endptr, 16);
        if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
            fprintf(stderr, "%s:line %d: invalid hexadecimal number: %s",
                    filename, n_instructions + 1, line);
            exit(1);
        }
        n_instructions++;
    }
    fclose(f);
    *n_instructions_p = n_instructions;
    // shrink instructions array to correct size
    instructions = instructions_realloc(instructions, n_instructions);
    return instructions;
}


// instructions_realloc is wrapper for realloc
// it calls realloc to grow/shrink the instructions array
// to the speicfied size
// it exits if realloc fails
// otherwise it returns the new instructions array
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions) {
    instructions = realloc(instructions, n_instructions * sizeof *instructions);
    if (instructions == NULL) {
        fprintf(stderr, "out of memory");
        exit(1);
    }
    return instructions;
}