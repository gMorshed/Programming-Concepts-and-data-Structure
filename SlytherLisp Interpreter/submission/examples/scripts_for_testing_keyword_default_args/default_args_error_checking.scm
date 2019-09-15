(define (my_func xx yy=97 zz)
    (print xx yy zz))
; non default argument follows default argument
; usually python throws this error as a SyntaxError, but we choose to throw it as a 
; BaseError as a design choice, which is essential the way we set up our REPL.
(my_func 1 2 3)
