; zz is instantiated as default value 98
(define (my_func xx yy zz=98)
    (print xx yy zz))
; checking the deafult argument
; checking without zz value
(my_func 123 -9)
;checking with zz value given by the user
(my_func 123 -9 76)
;checking with keyword argument
(my_func 123 9 zz=34)
