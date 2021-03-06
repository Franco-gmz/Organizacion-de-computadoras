#include<sys/regdef.h>

#define _SP 8
#define _GP 4
#define _FP 0

#define _A1 8
#define _A2 12
#define _A3 16
#define _A4 20
#define _A5 24

    .abicalls
    .text
    .align 2
    .set noreorder
    .cpload t9
    .set reorder
    .globl proximo
    .ent proximo

proximo:

    /*STACKFRAME*/	
    subu sp,sp,_SP
    sw gp,_GP(sp)
    sw fp,_FP(sp)
    move fp,sp

    /*ARGUMENTS*/ 
    sw a0,_A1(sp)
    sw a1,_A2(sp)
    sw a2,_A3(sp)
    sw a3,_A4(sp)
    lw t5,_A5(sp)

    j cell_address

cell_address:

    mul t0,a1,t5
    add t0,t0,a2
    add t0,a0,t0
    j cell_on_border

cell_on_border:

    beq a2,zero,left_border
    subu t6,t5,1
    subu t2,a2,t6
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

    lbu t0,0(t0)
    lbu t1,0(t1)
    lbu t2,0(t2)
    j next_state

next_state:

    sll t1,t1,2
    sll t0,t0,1
    or t6,t0,t1
    or t6,t6,t2
    srl v0,a3,t6
    addi t4,zero,1
    and v0,v0,t4

finish:
   
    lw gp,_GP(sp)
    lw fp,_FP(fp)
    addi sp,sp,_SP
    jr ra

    .end proximo
