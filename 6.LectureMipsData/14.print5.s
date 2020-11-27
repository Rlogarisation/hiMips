main:
    # Initial $t0 = i = 0;
    li		$t0, 0		# $t0 = 0

    la		$t1, numbers		# 
    
    
loop:
    bge		$t0, 5, end	# if $t0 >= 5 then end
    
    # $t2 = counter(i) * 4
    mul     $t2, $t0, 4
    # Move to corresponding array[location]
    add		$t3, $t1, $t2		# $t3 = $t2 + $t2
    # printf("%d\n", numbers[i]);
    lw		$a0, ($t3)		# 
    li		$v0, 1		# $v0 = 1
    syscall

    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall


    # i++;
    add		$t0, $t0, 1		# $t0 = $t0 + 1
    
    j		loop				# jump to loop
    

end:
    # return 0;
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    


.data
numbers:    .word   3, 9, 27, 81, 243