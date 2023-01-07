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
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $t1, $v0
<<<<<<< HEAD
	li, $t3, 1
=======
	li $t3, 1
>>>>>>> 4b6823a2fae2058c28baea3fd8ec0a33a29a7921
	bgt $t1, $t3, label4
	j label5
label4:
	move $a0, $t1
<<<<<<< HEAD
	addi, $sp, $sp, -4
	sw $ra, 0($sp)
	jal fact
	lw, $ra, 0($sp)
	addi, $sp, $sp, 4
=======
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal fact
	lw $ra, 0($sp)
	addi $sp, $sp, 4
>>>>>>> 4b6823a2fae2058c28baea3fd8ec0a33a29a7921
	move $t2, $v0
	j label6
label5:
	li $t2, 1
label6:
	move $a0, $t2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
<<<<<<< HEAD
	lw, $ra, 0($sp)
	addi, $sp, $sp, 4
=======
	lw $ra, 0($sp)
	addi $sp, $sp, 4
>>>>>>> 4b6823a2fae2058c28baea3fd8ec0a33a29a7921
	move $v0, $0
	jr $ra

fact:
<<<<<<< HEAD
	beq $t0, $t3, label1
	j label2
label1:
	move $v0, $a0
	jr $ra
	j label3
label2:
	addi, $sp, $sp, -4
	sw $ra, 0($sp)
	sub $a0, $a0, 1
	jal fact
	lw, $ra, 0($sp)
	addi, $sp, $sp, 4
	mul $v0, $v0, $a0
	jr $ra
=======
	li $t3, 1
	beq $t0, $t3, label1
	j label2
label1:
	j label3
label2:
>>>>>>> 4b6823a2fae2058c28baea3fd8ec0a33a29a7921
label3:

