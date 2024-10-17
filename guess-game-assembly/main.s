.extern printf
.extern scanf
.extern srand
.extern rand

.section  .data
  
  user_config_input: 
    .space 32, 0x0

  user_guess_input: 
    .space 32, 0x0

  random_number:
    .space 32, 0x0
  
.section .rodata

  num_fmt:
   .string " %d"

  user_config_fmt:
   .string "Enter configuration seed: "
  
  user_input_fmt:
    .string "What is your guess? \n"
  
  worng_guess_fmt:
    .string "Incorrect \n"

  good_guess_fmt:
    .string "Congratz! You Won!"

  over_fmt:
    .string "Game over, you lost :(. The correct answer was %d"


  scanf_fmt:
    .string " %d"
  
.section .text
  .globl main

main:
  pushq %rbp
  movq %rsp, %rbp

  # print the config line
  movq $user_config_fmt, %rdi
  xorq %rax, %rax
  call printf

  # read the config numner
  movq $scanf_fmt, %rdi
  movq $user_config_input, %rsi
  xorq %rax, %rax
  call scanf

  # Generate random number
  movl (user_config_input), %edi 
  call srand
  call rand

  # convert the number to range 1 - 10
  xorl %edx, %edx
  movl $11, %ebx
  divl %ebx
  movl %edx, (random_number)
  


  # loop for guess the number
  movl $0, %ebx
  .loop:
    cmp $5, %ebx
    je endLoop

    # print the question
    movq $user_input_fmt, %rdi
    xorq %rax, %rax
    call printf

    # read the guess numner
    movq $scanf_fmt, %rdi
    movq $user_guess_input, %rsi
    xorq %rax, %rax
    call scanf
    movq %rsi, (user_guess_input)
    
    # check if the guess is correct
    movq (random_number), %rdx
    movq (user_guess_input), %rax
    cmp %rax, %rdx
    je correctGuess
    
    # continue to next iteration
    movq $worng_guess_fmt, %rdi
    xorq %rax, %rax
    call printf
    inc %ebx
    jmp .loop

    endLoop:
      movq $over_fmt, %rdi
      movq (random_number), %rsi
      xorq %rax, %rax
      call printf
      jmp end

    correctGuess:
      movq $good_guess_fmt, %rdi
      xorq %rax, %rax
      call printf

    end:


  #Exit
  xorq %rax, %rax
  movq %rbp, %rsp
  popq %rbp
  ret
   
  
  
  