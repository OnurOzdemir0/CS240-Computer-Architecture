module riscv_decoder(
  input clk,
  input rst,
  input [31:0] in,
  output reg [6:0] opcode,
  output reg [4:0] rd,
  output reg [2:0] funct3,
  output reg [4:0] rs1,
  output reg [4:0] rs2,
  output reg [6:0] funct7,
  output reg [11:0] imm12,
  output reg [19:0] imm20,
  output reg aluControl,
  output reg regWrite, 
  output reg aluSrcA, 
  output reg aluSrcB, 
  output reg memWrite, 
  output reg branch, 
  output reg jump,
  output reg [1:0] immSrc, 
  output reg [1:0] resultSrc, 
  output reg [1:0] aluOP
);

  always @* begin
    if (rst) begin
      opcode = 0;
      rd = 0;
      funct3 = 0;
      rs1 = 0;
      rs2 = 0;
      funct7 = 0;
      imm12 = 0;
      imm20 = 0;
      aluControl = 0;
      regWrite = 0;
      aluSrcA = 0;
      aluSrcB = 0;
      memWrite = 0;
      branch = 0;
      jump = 0;
      immSrc = 0;
      resultSrc = 0;
      aluOP = 0;
    end else begin
      opcode = in[6:0];
        case (opcode)
        7'b0010011: // I
        begin
          rd = in[11:7];
          funct3 = in[14:12];
          rs1 = in[19:15];
          imm12 = in[31:20];

          regWrite = 1;
          immSrc = 2'b00;
          aluSrcA = 0;
          aluSrcB = 1;
          memWrite = 0;
          resultSrc = 2'b01;
          branch = 0;
          aluOP = 2'b00;
          jump = 0;
        end
        7'b0110011: // R
        begin
          rd = in[11:7];
          funct3 = in[14:12];
          rs1 = in[19:15];
          rs2 = in[24:20];
          funct7 = in[31:25];

          regWrite = 1;
          aluSrcA = 0;
          aluSrcB = 0;
          memWrite = 0;
          resultSrc = 2'b00;
          branch = 0;
          aluOP = 2'b10;
          jump = 0;
          
        case ({funct3, funct7[5]})
          5'b00000: aluControl = 3'b011; // ADD
          5'b00001: aluControl = 3'b011; // SUB
          5'b00101: aluControl = 3'b101; // SLT
          5'b00111: aluControl = 3'b011; // OR
          5'b00110: aluControl = 3'b010; // AND
          default: aluControl = 3'b000; // Default to ADD operation
        endcase
        end
        7'b1101111: // J
        begin
          rd = in[11:7];
          imm20 = {in[31], in[19:12], in[20], in[30:21], 1'b0};

          regWrite = 1;
          aluSrcA = 0;
          aluSrcB = 1;
          memWrite = 0;
          resultSrc = 2'b01;
          branch = 0;
          jump = 1;
          aluOP = 2'b01;
          aluControl = 3'b000;
        end
        7'b1100011: // B
        begin
          rd = 0;
          funct3 = in[14:12];
          rs1 = in[19:15];
          rs2 = in[24:20];
    	  imm12 = {in[31], in[7], in[30:25], in[11:8], 1'b0};

          regWrite = 0;
          aluSrcA = 0;
          aluSrcB = 0;
          memWrite = 0;
          resultSrc = 2'b00;
          branch = 1;
          jump = 0;
          aluOP = 2'b01;
          aluControl = 3'b000;
        end
          7'b0100011: // S
          begin
            rd = 0;
            funct3 = in[14:12];
            rs1 = in[19:15];
            rs2 = in[24:20];
            imm12 = {in[31:25], in[11:7]};

            regWrite = 0;
            aluSrcA = 0;
            aluSrcB = 1;
            memWrite = 1;
            resultSrc = 2'b00;
            branch = 0;
            jump = 0;
            aluOP = 2'b00;
            aluControl = 3'b000;
          end
          
        default:
        begin
          rd = 0;
          funct3 = 0;
          rs1 = 0;
          rs2 = 0;
          funct7 = 0;
          imm12 = 0;
          imm20 = 0;
          aluControl = 0;
          regWrite = 0;
          aluSrcA = 0;
          aluSrcB = 0;
          memWrite = 0;
          branch = 0;
          jump = 0;
          immSrc = 0;
          resultSrc = 0;
          aluOP = 0;
        end
      endcase
    end
  end

endmodule