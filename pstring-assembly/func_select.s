.extern printf
.extern scanf

.section .rodata
  
  invalid_input_fmt:
    .string "invalid option!\n"

  len_fmt:
    .string "first pstring length: %d, second pstring length: %d\n"

  func2_fmt:
    .string "length: %d, string: %s\n"

  scanf_fmt:
    .string " %d %d"


.section .text
.globl run_func

  run_func:
    pushq %rbp
    movq %rsp, %rbp

    
    # choice = 31
    cmpl $31, %edi
    je .pstr_len

    # choice = 33
    cmpl $33, %edi
    je .swap_case

    # choice = 34
    cmpl $34, %edi
    je .cpy_str

    # o.w
    movq $invalid_input_fmt, %rdi
    xorq %rax, %rax
    call printf
    jmp .exit

    .pstr_len:
      # calculate lenth of first pstring
      # pass the first argument
      movq %rsi, %rdi
      call pstrlen

      # initial local memory to first length
      subq $4, %rsp 
      movl %eax, -4(%rbp) 

      # calculate lenth of second pstring
      # pass the first argument
      movq %rdx, %rdi
      call pstrlen

      # initial local memory to second length
      subq $4, %rsp 
      movl %eax, -8(%rbp)

      # print
      subq $8, %rsp
      movq $len_fmt, %rdi
      movl -4(%rbp), %esi
      movl -8(%rbp), %edx
      xorq %rax, %rax
      call printf
      addq $8, %rsp
      jmp .exit


    .swap_case:
      # calculate lenth of first pstring
      # pass the first argument
      movq %rsi, %rdi
      call pstrlen

      # initial local memory to first length
      subq $4, %rsp 
      movl %eax, -4(%rbp) 

      # calculate lenth of second pstring
      # pass the first argument
      movq %rdx, %rdi
      call pstrlen

      # initial local memory to second length
      subq $4, %rsp 
      movl %eax, -8(%rbp)
      
      # first swap call
      movq %rsi, %rdi
      call swapCase
      subq $256, %rsp
      movq %rax, -264(%rbp)
      
      # second swap call
      movq %rdx, %rdi
      call swapCase
      subq $256, %rsp
      movq %rax, -520(%rbp)

      # print
      subq $8, %rsp
      movq $func2_fmt, %rdi
      movl -4(%rbp), %esi
      movq -264(%rbp), %rdx
      xorq %rax, %rax
      call printf
      addq $8, %rsp

      subq $8, %rsp
      movq $func2_fmt, %rdi
      movq -8(%rbp), %rsi
      movq -520(%rbp), %rdx
      call printf
      addq $8, %rsp

      jmp .exit

    .cpy_str:
      # calculate lenth of first pstring
      # pass the first argument
      movq %rsi, %rdi
      call pstrlen

      # initial local memory to first length
      subq $4, %rsp 
      movl %eax, -4(%rbp) 

      # calculate lenth of second pstring
      # pass the first argument
      movq %rdx, %rdi
      call pstrlen

      # initial local memory to second length
      subq $4, %rsp 
      movl %eax, -8(%rbp)
     
     subq $24, %rsp # save memory 
     movq %rsi, -16(%rbp) # save firts string
     movq %rdx, -24(%rbp) # save second string
      # get i,j

      movq $scanf_fmt, %rdi
      leaq -28(%rbp), %rsi
      leaq -32(%rbp), %rdx
      xorq %rax, %rax
      call scanf

      # check input
      movl -28(%rbp), %edi # i
      movl -32(%rbp), %esi # j
      movl -8(%rbp), %edx # len of second string

      subl $0x1, %edx # to check the last index
      
      # check if i < 0
      cmpl $0x0, %edi
      jl .wrong_input
      
      # check if j > len of second srting
      cmpl %edx, %esi
      jg .wrong_input

      addl $0x01, %edx
      jmp .do_copy


      .wrong_input:
        addl $0x01, %edx
        # print invalid input
        subq $32, %rsp
        movq $invalid_input_fmt, %rdi
        xorq %rax, %rax
        call printf
        addq $32, %rsp
        # print the strings
        subq $32, %rsp
        movq $func2_fmt, %rdi
        movl -4(%rbp), %esi # first len
        movq -16(%rbp), %rdx # first string
        xorq %rax, %rax
        call printf
        addq $32, %rsp

        subq $32, %rsp
        movq $func2_fmt, %rdi
        movl -8(%rbp), %esi # second len
        movq -24(%rbp), %rdx # second string
        call printf
        addq $32, %rsp
        jmp .exit

      .do_copy:
        # pass arguments to the function
        movq -16(%rbp), %rdi # first string (dst)
        movq -24(%rbp), %rsi # second string (src)
        movl -28(%rbp), %edx # index i
        movl -32(%rbp), %ecx # index j
        call pstrijcpy

        # print
        # print first string
        subq $32, %rsp
        movq $func2_fmt, %rdi
        movl -4(%rbp), %esi # move the len of dst string
        movq %rax, %rdx # move the dst string
        inc %rdx
        call printf
        addq $32, %rsp

        # print second string
        subq $32, %rsp
        movq $func2_fmt, %rdi
        movl -8(%rbp), %esi # move the len of src string
        movq -24(%rbp), %rdx # move the src string
        inc %rdx
        call printf
        addq $32, %rsp
        jmp .exit


      
      jmp .exit



  # Exit
  .exit:
  xorq %rax, %rax
  movq %rbp, %rsp
  popq %rbp
  ret