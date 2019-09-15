; you can define a variable and use that
; so doing default argument with a predefined variable
(define my_var 120)
(define (my_func xx yy=my_var zz=98)
    (print xx yy zz))

; two default arguments
; passing only one value to see if it defaults the other two
(my_func 32)
;passing two values to see if it defaults the last one
(my_func 12 43)
; making sure regular function call works
(my_func 56 768 9800)
