#include<sys/regdef.h>

#define _STATE0 48
#define _STATE1 49

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

    subu sp,sp,_SP
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
    j cell_address

cell_address:

    subu t0,a1,1
    mul t0,t0,t5
    subu t1,a2,1
    add t0,t0,t1
    add t0,a0,t0
    j cell_on_border

cell_on_border:

    beq t1,zero,left_border
    subu t2,a2,t5
    beq t2,zero,right_border
    j inner_cell

left_border:

    addi t2,t0,1
    addi t1,t5,-1
    add t1,t0,t1
    j neighbours

right_border:

    addi t1,t0,-1
    addi t2,t5,-1
    subu t2,t0,t2
    j neighbours

inner_cell:

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
    subu t9,t9,_STATE1
    subu t9,t9,_STATE0
    subu t9,t9,_STATE0
    beq t9,zero,state_1
    bltz t9,state_0
    addi t8,zero,_STATE0
    beq t1,zero,state_1
    j state_0

state_0:

    addi v0,zero,_STATE0
    j finish

state_1:

    addi v0,zero,_STATE1
    j finish

finish:

    lw ra,_RA(sp)
    lw gp,_GP(sp)
    lw fp,_FP(fp)
    addi sp,sp,16
    jr ra

    .end proximo