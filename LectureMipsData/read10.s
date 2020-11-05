main:
    li		$s0, 0		            # $s0 = counter = 0

loopForScan:
    bge		$s0, 10, endLoopForScan	# if $s0 >= 10 then endLoopForScan
    
    la		$a0, printMsg		    # printf("Enter a number: ");
    li		$v0, 4		            # $v0 = 4 (print string)
    syscall

    li		$v0, 5		            # scanf("%d", &numbers[i]);
    syscall
    
                                    # Determine array[position] first
    mul     $t0, $s0, 4             # $t0 = position = counter * sizeof int
    la		$t1, numbers		    # $t1 = array[0]
    add		$t2, $t1, $t0		    # $t2 = array[position]
    sw		$v0, ($t2)		        # Store input into array 
                                    # IMPORTANT:$v0 not $a0
    
    add		$s0, $s0, 1		        # counter++
    j		loopForScan				# jump to loopForScan
    
endLoopForScan:
    li		$s0, 0		            # Reset the counter
    j		loopForPrint			# jump to loopForPrint
    
loopForPrint:
    bge		$s0, 10, endLoopForPrint# if $s0 >= 10 then endLoopForPrint    
    
    mul     $t0, $s0, 4             # $t0 = position = counter * sizeof int
    la		$t1, numbers		    # $t1 = array[0]
    add		$t2, $t1, $t0		    # $t2 = array[position]
    lw		$a0, ($t2)		       
    li		$v0, 1		            # printf("%d\n", numbers[i]);
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    add		$s0, $s0, 1		        # counter++
    j		loopForPrint			# jump to loopForPrint

endLoopForPrint:
    li		$v0, 0		            # $v0 = 0
    jr		$ra					    # jump to $ra
    
.data
numbers:
    # int numbers[10] = { 0 };
    # .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    .space 40
printMsg:
    .asciiz "Enter a number: "