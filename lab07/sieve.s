# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# $s0 = i
# $s1 = j
main:
    la		$t0, prime		    # $t0 = the address of prime
    
loopA:
    bge		$s0, 1000, endLoopA	# if $s0 >= 1000 then endLoopA 
    add		$t1, $s0, $t0		# The position of i in array

    li		$t2, 1		        # $t2 = 1
    sb		$t2, ($t1)		    # prime[i] = 1;

    addi	$s0, $s0, 1			# $s0 = $s0 + 1
    j		loopA				# jump to loopA
endLoopA:
    li		$s0, 2		        # $s0 = i = 2
loopB:
    bge		$s0, 1000, endLoopB	# if $s0 >= 1000 then endLoopB
    add		$t1, $s0, $t0		# The position of i in array
    lb		$t2, ($t1)		
    bne		$t2, 1, endIf	    # if prime[i] != 1 then endIf
    # printf("%d\n", i);
    move 	$a0, $s0		    # $a0 = $s0
    li		$v0, 1		        # $v0 = 1
    syscall
    la		$a0, '\n'		    # $a0 = '\n'
    li		$v0, 11		        # $v0 = 11
    syscall

    # int j = 2 * i;
    mul     $s1, $s0, 2

loopC:
    bge		$s1, 1000, endLoopC	# if $s1 >= 1000 then endLoopC
    add		$t1, $t0, $s1		# the position of j

    li		$t2, 0		        # $t2 = 0
    sb		$t2, ($t1)		    # prime[j] = 0;
    
    add		$s1, $s1, $s0		# j = j + i;
    j		loopC				# jump to loopC

endIf:
endLoopC:
    addi	$s0, $s0, 1			# $s0 = $s0 + 1
    j		loopB				# jump to loopB
    
endLoopB:
    li      $v0, 0              # return 0
    jr      $31

.data
prime:
    .space 1000

