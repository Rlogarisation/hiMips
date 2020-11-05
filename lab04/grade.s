main: 
    # printf("Enter a mark: ");
    la		$a0, stringPrintf		
    li		$v0, 4		# $v0 = 4
    syscall

    # scanf("%d", &mark);
    li		$v0, 5		# $t0 = 5
    syscall

    # Assign mark into variable $t0
    move 	$t0, $v0		# $t0 = $v0

    # if (mark < 50)
    blt		$t0, 50, fail	# if $t0 < $t1 then fail
    
    # else if (mark < 65)
    blt		$t0, 65, pass	# if $t0 < 65 then pass
    
    # else if (mark < 75)
    blt		$t0, 75, credit	# if $t0 < 75 then credit
    
    # else if (mark < 85)
    blt		$t0, 85, distinction	# if $t0 < 85 then distinction
    
    # else
    la		$a0, stringHDMsg		# 
    li		$v0, 4		# $t0 = 4
    syscall
    
    j		end				# jump to end
    

fail:
    # printf("FL\n");
    la		$a0, stringFailMsg		
    li		$v0, 4		# $v0 = 4
    syscall

    j		end				# jump to end
    
pass:
    # printf("PS\n");  
    la		$a0, stringPassMsg		# 
    li		$v0, 4		# $v0 = 4
    syscall

    j		end				# jump to end
    
credit:
    # printf("CR\n");
    la		$a0, stringCrMsg		# 
    li		$v0, 4		# $v0 = 4
    syscall

    j		end				# jump to end

distinction:
    # printf("DN\n");
    la		$a0, stringDNMsg		# 
    li		$v0, 4		# $v0 = 4
    syscall

    j		end				# jump to end
    
    
end:
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    




    .data
stringPrintf:
    .asciiz "Enter a mark: "
stringFailMsg:
    .asciiz "FL\n"
stringPassMsg:
    .asciiz "PS\n"
stringCrMsg:
    .asciiz "CR\n"
stringDNMsg:
    .asciiz "DN\n"
stringHDMsg:
    .asciiz "HD\n"
