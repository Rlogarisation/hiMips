main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0       # $t0 = x

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0       # $t1 = y

    addi	$s0, $t0, 1	        # $s0 = i  (int i = x + 1;)
    
loop:
    bge		$s0, $t1, end	    # if $s0 >= $t1 then end
    
ifStatement:
    beq		$s0, 13, endIf	# if $s0 == 13 then endIf
    
    move 	$a0, $s0		# printf("%d\n", i);
    li		$v0, 1		    # $v0 = 1
    syscall
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		    # $v0 = 11
    syscall

endIf:
    addi	$s0, $s0, 1			# i++;
    j		loop				# jump to loop
    

end:

    li   $v0, 0         # return 0
    jr   $ra
