main:
    li		$s0, 0		            # $s0 = counter = 0
    
loopScan:
    bge		$s0, 10, endLoopScan    # if $s0 >= 10 then endLoopScan
    
    la		$a0, enterNumberMsg		# printf("Enter a number: ");
    li		$v0, 4		            # $v0 = 4
    syscall

    li		$v0, 5		            # scanf("%d", &numbers[count]);
    syscall

    mul     $t0, $s0, 4             # $t0 = position index
    la		$t1, numbers		    # $t1 = array
    add		$t2, $t1, $t0		    # $t2 = array[index]
    sw		$v0, ($t2)		        # store into variable
    

    add		$s0, $s0, 1		        # counter++
    j		loopScan				# jump to loopScan
    
endLoopScan:
    la		$a0, reverseMsg		    # printf("Reverse order:\n");
    li		$v0, 4		            # $v0 = 4
    syscall

    li		$s0, 9		            # Reset counter = 9
    
    j		loopPrint				# jump to loopPrint
    
loopPrint:
    blt		$s0, 0, endLoopPrint	# if $s0 < 0 then endLoopPrint
    
    mul     $t0, $s0, 4             # $t0 = position index
    la		$t1, numbers		    # $t1 = array
    add		$t2, $t1, $t0		    # $t2 = array[index]
    lw		$a0, ($t2)		        # printf("%d\n", numbers[count]);
    li		$v0, 1		            # $v0 = 1
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    sub	    $s0, $s0, 1			    # counter--;
    j		loopPrint				# jump to loopPrint
    
endLoopPrint:
    li		$v0, 0		            # $v0 = 0
    jr		$ra					    # jump to $ra
    


.data
numbers:
    # .space 40
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
enterNumberMsg:
    .asciiz "Enter a number: "

reverseMsg:
    .asciiz "Reverse order:\n"