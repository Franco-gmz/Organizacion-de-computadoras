#include<sys/regdef.h>

#define STATE_0 48
#define STATE_1 49

#define _SP 16
#define _RA 12
#define _GP 8
#define _FP 4

#define _A1 16
#define _A2 20
#define _A3 24
#define _A4 28
#define _A5 32

    .abicalls
    .text
    .align 2
    .set reorder
    .cpload t9
    .set reorder
    .globl proximo
    .ent proximo

proximo:
    
    j create_stack

create_stack:

    addi sp,sp,-16
    sw ra,_RA(sp)
    sw gp,_GP(sp)
    sw fp,_FP(sp)
    move fp,sp
    j save_arguments

save_arguments:

    sw a0,_A1(sp)
    sw a1,_A2(sp)
    sw a2,_A3(sp)
    sw a3,_A4(sp)
    lw t5,_A5(sp)
    j cell

cell:

    addi t0,a1,-1
    mul t0,t0,t5
    addi t1,a2,-1
    add t0,t0,t1
    add t0root,a0,t0
    j check_overflow

check_overflow:

    beq t1,zero,first_cell
    subu t2,a2,t5
    beq t2,zero,last_cell
    j medium_cell

first_cell:

    addi t2,t0,1
    addi t1,t5,-1
    add t1,t0,t1
    j neighbours

last_cell:

    addi t1,t0,-1
    addi t2,t5,-1
    subu t2,t0,t2
    j neighbours

medium_cell:

    addi t1,t0,-1
    addi t2,t0,1
    j neighbours

neighbours:

    lb t0,0(t0)
    lb t1,0(t1)
    lb t2,0(t2)
    j next_state

next_state:

    add t9,t0,t1
    add t9,t9,t2
    addi t9,t9,-1
    beq t9,zero,state_1
    bltz t9,state_0
    beq t1,zero,state_1
    j state_0

state_0:

    addi v0,zero,48
    j finish

state_1:

    addi v0,zero,49
    j finish

finish:

    lw ra,12(sp)
    lw gp,8(sp)
    lw fp,4(fp)
    addi sp,sp,16
    jr ra

    .end proximo