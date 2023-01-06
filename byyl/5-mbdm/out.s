.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra
write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra
main:
	li $t1, 0
	li $t2, 1
	li $t3, 0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $t4, $v0
label1:
	blt $t3, $t4, label2
	j label3
label2:
	add $t5, $t1, $t2
	move $a0, $t2
	addi, $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw, $ra, 0($sp)
	addi, $sp, $sp, 4
	move $t1, $t2
	move $t2, $t5
	addi $t3, $t3, 1
	j label1
label3:
	move $v0, $0
	jr $ra

