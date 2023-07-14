// Code your design here

`define FETCH_STATE 0
`define DECODE_STATE 1
`define EXMEM_STATE 2
`define WB_STATE 3

module riscvcore
  (
    clk,
    rst, 
  	// RAM I/F
    memAddr,
    dataRd,
    dataWr,
    wrEn,
    mask
  );
  
  input clk, rst;
  // Memory I/F
  input [31:0] dataRd;
  output reg [13:0] memAddr;
  output reg [31:0] dataWr;
  output reg wrEn;
  output reg [3:0] mask;
  
  // Internal Signals
  reg [31:0] PC, PC_next;
  reg [1:0] state, state_next;  // FETCH = 0, DECODE = 1, EXMEM = 2, WB = 3 
  reg [31:0] instr, instr_next; // Current instruction
  
  // REGISTERS
  reg [31:0] regfile [0:31];
  reg [31:0] result, result_next; // Holds the value to write into regfile
  reg regfileWr, regfileWr_next;  // Regfile Write Signal
  
  // Decoder I/F
  wire [31:0] decoder_in;
  wire [6:0] opcode;
  wire [4:0] rd;
  wire [2:0] funct3,aluControl;
  wire [4:0] rs1;
  wire [4:0] rs2;
  wire [6:0] funct7;
  wire [11:0] imm12;
  wire [19:0] imm20;
  wire regWrite, aluSrcA, aluSrcB, memWrite, branch, jump;
  wire [1:0] immSrc, resultSrc, aluOP;
  
  assign decoder_in = (state == `DECODE_STATE) ? dataRd:instr;
  
  riscv_decoder decoder(
    .clk(clk),
    .rst(rst),
    .in(decoder_in),
    .opcode(opcode),
    .rd(rd),
    .funct3(funct3),
    .rs1(rs1),
    .rs2(rs2),
    .funct7(funct7),
    .imm12(imm12),
    .imm20(imm20),
    .aluControl(aluControl),
    .regWrite(regWrite),
    .aluSrcA(aluSrcA),
    .aluSrcB(aluSrcB),
    .memWrite(memWrite),
    .branch(branch),
    .jump(jump),
    .immSrc(immSrc),
    .resultSrc(resultSrc),
    .aluOP(aluOP)
  );
  
  always @(posedge clk) begin
    PC <= #1 PC_next;
    state <= #1 state_next;
    instr <= #1 instr_next;
    regfileWr <= #1 regfileWr_next;
    result <= #1 result_next;
    if (regfileWr)
      regfile[rd] <= #1 result;
  end
  
  always @(*) begin
    PC_next = PC;
    state_next = state + 1;
    instr_next = instr;
    regfileWr_next = 0;
    result_next = result;
    wrEn = 0;
    mask = 0;
    if (rst) begin
    	PC_next = 0;
      	state_next = 0;
     	regfileWr_next = 0;
    end else
      case(state)
        `FETCH_STATE: begin
          // FILL,
            PC_next = PC + 4;
            memAddr = PC;
            state_next = `DECODE_STATE;
        end
        `DECODE_STATE: begin
            instr_next = dataRd;
            state_next = `EXMEM_STATE;
        end
        `EXMEM_STATE: begin
            if (memWrite) begin
            memAddr = result;
            dataWr = regfile[rs2];
            wrEn = 1;
            end
            if (branch) begin
            if (result) begin
                PC_next = PC + imm12;
            end
            else begin
                PC_next = PC + 4;
            end
            end
            else if (jump) begin
            PC_next = result;
            end
            else begin
            result_next = resultSrc ? imm12 : result;
            regfileWr = regWrite;
            end
            state_next = `WB_STATE;
        end
        `WB_STATE: begin
            if(regWrite) begin 
            regfile[rd] = result;
            end
            PC_next = PC;
            state_next = `FETCH_STATE;
        end
      endcase
  end
  

endmodule