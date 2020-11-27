main:
    li		$s0, 0		            # $s0 = i = 0
loopFirst:
    bge		$s0, 3, endLoopFirst	# if $s0 >= 3 then endLoopFirst
    li		$s1, 0		            # $s1 = j = 0
loopSecond:
    bge		$s1, 5, endLoopSecond	# if $s1 >= 5 then endLoopSecond
    
    # IMPORTANT!!!
    # printf("%d", numbers[i][j]);
    la		$t0, numbers		    # 
    mul     $t1, $s0, 20            # Determine which group i is located
    add		$t2, $t1, $t0		    # address + location
    mul     $t3, $s1, 4             # Determine the position of j
    add		$t4, $t2, $t3		    # $t4 = $t2 + $t3
    lw		$a0, 0($t4)		        # 
    li		$v0, 1		            # $v0 = 1
    syscall
    
    li		$a0, ' '		        # printf("%c", ' ');
    li		$v0, 11		            # $v0 = 11
    syscall
    addi	$s1, $s1, 1			    # j++
    j		loopSecond				# jump to loopSecond
endLoopSecond:

    li		$a0, '\n'		        # printf("%c", '\n');
    li		$v0, 11		            # $v0 = 11
    syscall
    addi	$s0, $s0, 1			    # i++
    j		loopFirst				# jump to loopFirst
    
endLoopFirst:
    li		$v0, 0		            # $v0 = 0
    jr		$ra					    # jump to $ra
    



.data
# int numbers[3][5] = {{3,9,27,81,243},{4,16,64,256,1024},
#                      {5,25,125,625,3125}};
numbers:
    .word   3, 9, 27, 81, 243, 4, 16, 64, 256, 1024, 5, 25, 125, 625, 3125