(define (my_func xx yy zz)
    (print xx yy zz))
; I can declare a new variable and use that in the function call argument
(define new_variable 87)
; using the declared variable in the function call argument
; giving all three argument but using keyword and out of order to check to make sure they are catching the right vales
(my_func zz=new_variable xx=652 yy=9)
; regular function call
(my_func 32 875 3463)
; switching position for yy and zz
(my_func 45 zz=98 yy=432)
;using keyword but in the same position as actual function
(my_func 21 yy=83 zz=8763)
;using keyword only for the last variable
(my_func 34 98 zz=8247)
