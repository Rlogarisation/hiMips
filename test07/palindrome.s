# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    # $s0 = i = 0
    li		$s0, 0		        # $s0 = 0
loopA:
    la		$a0, line		
    add		$t0, $s0, $a0		# line[i]'s address
    lb		$t1, 0($t0)		    # 
    
    beq		$t1, 0, endLoopA	# if $t1 == 0 then endLoopA
    
    addi	$s0, $s0, 1			# i++
    j		loopA				# jump to loopA
    
endLoopA:
    # $s1 = j = 0
    li		$s1, 0		        # $s1  = 0
    # $s2 = k = i - 2;
    addi	$s2, $s0, -2		# $s2 = $s0 + -2
loopB:
    bge		$s1, $s2, endLoopB	# if $s1 >= $s2 then endLoopB

    la		$a0, line		    # 
    add		$t2, $a0, $s1		# line[j]'s address
    lb		$t3, 0($t2)		    # line[j]
    add		$t4, $a0, $s2		# line[k]'s address
    lb		$t5, 0($t4)		    # line[k]
    
    beq		$t3, $t5, endIf	    # if $t3 == $t5 then endIf
    la		$a0, not_palindrome	# printf("not palindrome\n");
    li		$v0, 4		        # $v0 = 4
    syscall
    li		$v0, 0		        # $v0 = 0
    jr		$ra					# jump to $ra
    

endIf:

    addi	$s1, $s1, 1			# $s1 = $s1 + 1
    addi	$s2, $s2, -1		# $s2 = $s2 + -1
    j		loopB				# jump to loopB
    
endLoopB:   

    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

