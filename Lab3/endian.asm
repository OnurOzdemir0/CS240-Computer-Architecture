_start:
    lui s0, 0xABCDE 
    addi s0, s0, 0x123 
    sw s0, 0x300(zero)
    addi x5, x0,0x300
    li x6, 8
convert_loop:
    lb x1, 0(x5)
    lb x2, 1(x5)
    lb x3, 2(x5)
    lb x4, 3(x5)
    sb x4, 0(x5)
    sb x3, 1(x5)
    sb x2, 2(x5)
    sb x1, 3(x5)
    addi x5, x5, 4
    addi x6, x6, -1
    bne x6, x0, convert_loop
    