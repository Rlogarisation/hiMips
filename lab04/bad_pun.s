
main:
    la	$a0, string 
    li	$v0, 4		# $v0 = 4 
    syscall
    jr  $ra

    .data
string:
    .asciiz "I MIPS you!\n"
    