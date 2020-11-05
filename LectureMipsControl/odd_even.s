main:
    # printf("Enter a number: ");
    la		$a0, string0
    li		$v0, 4		# $v0 = 4
    syscall

    # scanf("%d", &x);
    li		$v0, 5		# $v0 = 5
    syscall

    and    $t0, $v0, 1
    beq		$t0, 1, odd	# if $t0 == 1 then odd
    
    # Even otherwise
    la		$a0, stringEven		# 
    li		$v0, 4		# $v0 = 4
    syscall	

    j		end				# jump to end
    
    
    
odd:
    # printf("Odd\n");
    la		$a0, stringOdd		# 
    li		$v0, 4		# $v0 = 4
    syscall

end:
    # End the function
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra


    .data
string0:
    .asciiz "Enter a number: "

stringOdd:
    .asciiz "Odd\n"

stringEven:
    .asciiz "Even\n"