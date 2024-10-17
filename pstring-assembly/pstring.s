

.section .text
.globl pstrlen
  pstrlen:
    pushq %rbp
    movq %rsp, %rbp

    movl $0, %ebx # initial len to 0
    incq %rdi
    .loop:
      # Read byte from string
      movb (%rdi), %al

      # If we're at the end of the string, exit
      cmpb $0x0, %al
      je .done1

      # not at the end of the string
      incl %ebx # lenth += 1
      incq %rdi # next char
      jmp .loop

      .done1:
        movl %ebx, %eax
        jmp exit


.globl swapCase
  swapCase:
    pushq %rbp
    movq %rsp, %rbp

    incq %rdi
    movq %rdi, %rax
    .loop2:
      # check if string is end
      movb (%rdi), %bl
      cmpb $0x0, %bl
      je .done2

      # not end

      # in case not char
      cmpb $65, %bl
      jl .next

      cmpb $122, %bl
      jg .next

      # check is small letter
      cmpb $97, %bl
      jl .big_letter

      # mean is small letters (last case)
      jmp .small_leter

      .big_letter:
         addb $32, (%rdi)
         jmp .next

       .small_leter:
         subb $32, (%rdi)
         movb (%rdi), %bl
         jmp .next

       .next:
        incq %rdi # next char
        jmp .loop2

       .done2:
         jmp exit
         
.globl pstrijcpy
  pstrijcpy:
    pushq %rbp
    movq %rsp, %rbp

    movq %rdi, %rax # move first string
    movq %rsi, %r9 # move second string
    
    incq %rax # move to the start of the string 1
    inc %r9 # move to the start of the string 2
    incl %ecx # j + 1

    movl $0x0, %ebx
    .loop_get_index:
      cmpl %edx, %ebx
      je .loop_copy

      # in case k < i
      incq %rax 
      incq %r9
      incl %ebx
      jmp .loop_get_index
    
    .loop_copy:
      cmpl %ecx, %ebx
      je .return_value

      # process of the copy
      movb (%r9), %r8b
      movb %r8b, (%rax)
      incq %rax 
      incq %r9
      incl %ebx
      jmp .loop_copy

      .return_value:
        movq %rdi, %rax # return value
        jmp exit 

    exit:
      movq %rbp, %rsp
      popq %rbp
      ret
    