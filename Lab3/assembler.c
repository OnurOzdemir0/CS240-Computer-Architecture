#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>



uint32_t dividing (uint32_t low, uint32_t high, uint32_t divisor)
{
    uint32_t result = divisor & ((1 << (high+1)) -1);
    result = divisor >> low;

    return result;
}


int main(int argc, char *argv[])
{
    FILE *input,*output;

    input = fopen(argv[1],"r");
    output = fopen("out.hex","w");

    if( input == NULL || output == NULL ) {
        fprintf(stderr,"Couldn't access file\n");
        return -1;
    }

    char buffer[100], instruction[10];
    uint32_t hex, opcode, funct3, funct7, rd, rs1, rs2, imm;

    while(fgets(buffer, 100, input) != NULL){
        sscanf(buffer,"%s", instruction);

        if (!strcmp(instruction, "ecall")) {
            opcode = 115;
            hex = opcode;
        }

        if (!strcmp(instruction, "addi")) {
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm);
            opcode = 19;
            funct3 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
            hex &= 0xFFFFFFFF; 
        }

        if (!strcmp(instruction, "add")) {
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            opcode = 51;
            funct3 = 0;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
            hex &= 0xFFFFFFFF; 
        }

        if (!strcmp(instruction, "bne")) {
            sscanf(buffer, "%*s x%d, x%d, %d", &rs1, &rs2, &imm);
            opcode = 0x63;
            funct3 = 1;
            hex = (opcode) | ((imm & 0x800) >> 4) | (rs1 << 15) | (funct3 << 12) | (rs2 << 20) | ((imm & 0x1E) << 7) | ((imm & 0x7E0) << 20) | ((imm & 0x1000) << 19);
            hex &= 0xFFFFFFFF;
        }

        if(!strcmp (instruction, "sub"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 0;
            funct7 = 32;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "sll"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 1;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "slt"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 2;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "xor"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 4;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "srl"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 5;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "or"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 6;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        if(!strcmp (instruction, "and"))
        {
            sscanf(buffer, "%*s x%d, x%d, x%d",&rd,&rs1,&rs2);
            opcode = 0x33;
            funct3 = 7;
            funct7 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

            if (!strcmp(instruction, "lui")) {
            sscanf(buffer, "%*s x%d, %x", &rd, &imm);
            opcode = 0x37;
            hex = (opcode) | (rd << 7) | (imm << 12);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "andi")) {
            sscanf(buffer, "%*s x%d, x%d, %x", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x7;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "ori")) {
            sscanf(buffer, "%*s x%d, x%d, %x", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x6;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "xori")) {
            sscanf(buffer, "%*s x%d, x%d, %x", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x4;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "slli")) {
            sscanf(buffer, "%*s x%d, x%d, %x", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x1;
            funct7 = 0x0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0x1F) << 20) | (funct7 << 25);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "srli")) {
            sscanf(buffer, "%*s x%d, x%d, %x", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x5;
            funct7 = 0x0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0x1F) << 20) | (funct7 << 25);
            hex &= 0xFFFFFFFF;
        }

        if (!strcmp(instruction, "slti")) {
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm);
            opcode = 0x13;
            funct3 = 0x2;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
            hex &= 0xFFFFFFFF;
        }

//control flow
            if (!strcmp(instruction, "jal")) {
                sscanf(buffer, "%*s x%d, %d", &rd, &imm);
                opcode = 0x6F;
                hex = (opcode) | (rd << 7) | ((imm & 0x80000) >> 9) | ((imm & 0x7FE) << 20) | ((imm & 0x1000) << 19) | ((imm & 0xFF000) >> 12);
                hex &= 0xFFFFFFFF;
            }
                                        

        if(!strcmp(instruction, "beq"))
        {
            sscanf(buffer, "%*s x%d, x%d, %d",&rs1,&rs2,&imm);
            opcode = 0x63;
            funct3 = 0;
            hex = (opcode) | ((imm & 0x800) >> 4) | (rs1 << 15) | (funct3 << 12) | (rs2 << 20) | ((imm & 0x1E) << 7) | ((imm & 0x7E0) << 20) | ((imm & 0x1000) << 19);
        }

        if(!strcmp (instruction, "blt"))
        {
            sscanf(buffer, "%*s x%d, x%d, %d",&rs1,&rs2,&imm);
            opcode = 0x63;
            funct3 = 4;
            hex = (opcode) | ((imm & 0x800) >> 4) | (rs1 << 15) | (funct3 << 12) | (rs2 << 20) | ((imm & 0x1E) << 7) | ((imm & 0x7E0) << 20) | ((imm & 0x1000) << 19);
        }

        if(!strcmp (instruction, "bge"))
        {
            sscanf(buffer, "%*s x%d, x%d, %d",&rs1,&rs2,&imm);
            opcode = 0x63;
            funct3 = 5;
            hex = (opcode) | ((imm & 0x800) >> 4) | (rs1 << 15) | (funct3 << 12) | (rs2 << 20) | ((imm & 0x1E) << 7) | ((imm & 0x7E0) << 20) | ((imm & 0x1000) << 19);
        }




//load
        if (!strcmp(instruction, "lw")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rd, &imm, &rs1);
            opcode = 3;
            funct3 = 2;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
        } 

        if (!strcmp(instruction, "lb")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rd, &imm, &rs1);
            opcode = 3;
            funct3 = 0;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
        }

        if (!strcmp(instruction, "lh")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rd, &imm, &rs1);
            opcode = 3;
            funct3 = 1;
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | ((imm & 0xFFF) << 20);
        }


//store
        if (!strcmp(instruction, "sw")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rs2, &imm, &rs1);
            opcode = 35;
            funct3 = 2;
            hex = (opcode) | (rs2 << 20) | (funct3 << 12) | (rs1 << 15) | (((imm & 0xFE0) << 20) >> 5) | ((imm & 0x1F) << 7);
        }
                        
        if (!strcmp(instruction, "sb")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rs2, &imm, &rs1);
            opcode = 35;
            funct3 = 0;
            hex = (opcode) | ((imm & 0x1F) << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | ((imm & 0xFE0) << 20);
        }


        if (!strcmp(instruction, "sh")) {
            sscanf(buffer, "%*s x%d, %d(x%d)", &rs2, &imm, &rs1);
            opcode = 35;
            funct3 = 1;
            hex = (opcode) | ((imm & 0x1F) << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | ((imm & 0xFE0) << 20);
        }
//--------------------------------------------------------------------------------------------------//
        printf("%08x\n", hex);
    }
    fclose(input);
    fclose(output);

    return 0;

}
