.text
main:
	la s11, vars
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(sp)
	sw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(sp)
	sw t0, 4(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	slt t0, t0, t1
	sw t0, 0(sp)
	addi sp, sp,4
	beq t0, zero, elsein1
whilecheck0:
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	slt t0, t0, t1
	sw t0, 0(sp)
	addi sp, sp,4
	beq t0, zero, whileout0
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	addi t0, zero, 2
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	mul t0, t0, t1
	sw t0, 0(sp)
	lw t0, 0(sp)
	sw t0, 0(s11)
	addi sp, sp,4
	jal zero, whilecheck0
whileout0:
	jal zero, ifout1
elsein1:
ifout1:
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi sp, sp,4
	add a0, t0, zero
	addi a7, zero, 1
	ecall
	addi a0, zero, 10
	addi a7, zero, 11
	ecall
	lw t0, 4(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi sp, sp,4
	add a0, t0, zero
	addi a7, zero, 1
	ecall
	addi a0, zero, 10
	addi a7, zero, 11
	ecall
	addi a0, zero,0
	addi a7,zero, 10
	ecall
.data
vars:
.space 8
