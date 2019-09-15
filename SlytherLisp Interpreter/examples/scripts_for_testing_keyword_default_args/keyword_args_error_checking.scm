;once again throwing the Key Word argument error as BaseException, design choice that is 
; essential for our REPL
(define (my_func xx yy zz)
    (print xx yy zz))
; checking to make sure it if throws an erro if in the function call, positional argument follows keyword argument. 
(my_func 34 zz=98 837)
(my_func yy=34 2 3)
