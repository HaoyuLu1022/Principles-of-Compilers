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
li $t0, 0
li $t1, 1
li $t2, 0
add $sp, $sp, -4
sw, $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
move $t3, $v0
//少一行
label1:
blt $t2, $t3, label2
j label3
label2:
add $t4, $t0, $t1
move $a0, $t1
addi, $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw, $ra, 0($sp)
addi, $sp, $sp, 4
move $t0, $t1
move $t1, $t4
//差三行
//
//
label3:
move $v0, $0
jr $ra

