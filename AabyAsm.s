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
	addi t0, zero, 5
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	sub t0, t0, t1
	add t1, zero, t0
	slt t0, t1, zero
	slt t1, zero, t1
	add t0, t0, t1
	xori t0, t0, 1
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi sp, sp,4
	add a0, t0, zero
	addi a7, zero, 1
	ecall
	addi a0, zero, 10
	addi a7, zero, 11
	ecall
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	addi t0, zero, 5
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	sub t0, t0, t1
	add t1, zero, t0
	slt t0, t1, zero
	slt t1, zero, t1
	add t0, t0, t1
	xori t0, t0, 1
	sw t0, 0(sp)
	addi sp, sp,4
	beq t0, zero, ifout2
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
	jal zero, ifchainout0
ifout2:
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	addi t0, zero, 5
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	sub t0, t0, t1
	slt t0, zero, t0
	sw t0, 0(sp)
	addi sp, sp,4
	beq t0, zero, ifout1
	addi t0, zero, 70
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
	jal zero, ifchainout0
ifout1:
	lw t0, 0(s11)
	addi sp, sp, -4
	sw t0, 0(sp)
	addi t0, zero, 6
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 4(sp)
	lw t1, 0(sp)
	addi sp, sp,4
	slt t0, t0, t1
	sw t0, 0(sp)
	addi sp, sp,4
	beq t0, zero, ifout0
	addi t0, zero, +1
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
	jal zero, ifchainout0
ifout0:
ifchainout0:
	addi a0, zero,0
	addi a7,zero, 10
	ecall
.data
vars:
.space 4
