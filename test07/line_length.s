# read a line and print its length

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
    la		$a0, line		    # 
    add		$t0, $a0, $s0		# line[i]'s address
    lb		$t1, 0($t0)		    # line[i]

    beq		$t1, 0, endLoopA	# if $t1 == 0 then endLoopA
    
    addi	$s0, $s0, 1			# i++
    j		loopA				# jump to loopA
    
endLoopA:

    la   $a0, str1       # printf("Line length: ");
    li   $v0, 4
    syscall

    move 	$a0, $s0		# $a0 = $s0
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256

