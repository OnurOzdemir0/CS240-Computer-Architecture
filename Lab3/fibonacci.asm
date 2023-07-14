lui x1, 0x00000
addi x1, x1, 10
addi x5, x0, 0
addi x6, x0, 1
addi x7, x0, 0
addi x2, x0, 1
loop:
    beq x2, x1, exit
    add x7, x5, x6
    add x5, x6, x0
    add x6, x7, x0
    addi x2, x2, 1
    j loop
exit:
    add x10, x6, x0
lui s0, 0xABCDE
addi s0, s0, 0x123
sw s0, 0x300(zero)
