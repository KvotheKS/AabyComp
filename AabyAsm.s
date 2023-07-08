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
	addi a0, zero,0
	addi a7,zero, 10
	ecall
.data
vars:
.space 4
