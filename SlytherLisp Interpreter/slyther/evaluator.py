from slyther.types import (Quoted, NIL, SExpression, ConsList, Symbol,
                           Macro, NilType, LexicalVarStorage)


def lisp_eval(expr, stg: LexicalVarStorage):
    """
    Takes a **single** AST element (such as a SExpression, NIL, or
    number) and evaluates it, returning the result, if any.

    Depending on what type ``expr`` is, the evaluation will be computed
    differently:

    +---------------------+-------------------------------------------------+
    | If ``expr`` is a... | return...                                       |
    +=====================+=================================================+
    | ``NIL``             | ``NIL``                                         |
    +---------------------+-------------------------------------------------+
    | Quoted s-expression | A ``ConsList`` with each of the elements in the |
    |                     | s-expression quoted and then ``lisp_eval``-ed.  |
    +---------------------+-------------------------------------------------+
    | Quoted non-SE       | The element unquoted.                           |
    +---------------------+-------------------------------------------------+
    | Symbol              | The value of the corresponding ``Variable`` in  |
    |                     | the lexical variable storage (``stg``).         |
    +---------------------+-------------------------------------------------+
    | S-Expression        | ``lisp_eval`` the CAR and if that's a...        |
    |                     |                                                 |
    |                     | :Macro:                                         |
    |                     |     call the macro with the unevaluated         |
    |                     |     arguments and ``stg`` and return the        |
    |                     |     ``lisp_eval``-ed result.                    |
    |                     | :Function:                                      |
    |                     |     ``lisp_eval`` each of the arguments and     |
    |                     |     call the function. Return the result.       |
    |                     | :Something else:                                |
    |                     |     Raise a ``TypeError``.                      |
    +---------------------+-------------------------------------------------+
    | Something else      | Return it as is.                                |
    +---------------------+-------------------------------------------------+

    Here is some examples:

    >>> from slyther.types import *
    >>> empty_stg = LexicalVarStorage({})
    >>> lisp_eval(NIL, empty_stg)
    NIL
    >>> lisp_eval(3, empty_stg)
    3
    >>> lisp_eval(Quoted(3), empty_stg)
    3
    >>> some_stg = LexicalVarStorage({
    ...     'x': Variable(2),
    ...     'NIL': Variable(NIL)})
    >>> lisp_eval(Symbol('x'), some_stg)
    2
    >>> lisp_eval(Quoted(Symbol('x')), some_stg)
    x
    >>> lisp_eval(Symbol('NIL'), some_stg)
    NIL
    >>> from slyther.parser import lisp
    >>> def test(code):                 # test function
    ...     return lisp_eval(lisp(code), some_stg)
    >>> test("3")
    3
    >>> test("'(1 2 3)")
    (list 1 2 3)
    >>> l = test("'(x y z)")
    >>> l
    (list x y z)
    >>> type(l.car)
    <class 'slyther.types.Symbol'>
    >>> test("'(x y z (a b c))")
    (list x y z (list a b c))
    >>> test("'((a b (c)) (1 (2) 3))")
    (list (list a b (list c)) (list 1 (list 2) 3))

    Function calls should take *evaluated parameters*, do something
    with them, and return a result (which, unlike macros, ``lisp_eval``
    does not need called on to compute).

    >>> identity = UserFunction(
    ...     params=SExpression(Symbol('x')),
    ...     body=SExpression(Symbol('x')),
    ...     environ=some_stg.fork())
    >>> some_stg.put('identity', identity)
    >>> test("(identity 4)")
    4
    >>> test("(identity ())")
    NIL
    >>> test("(identity NIL)")
    NIL
    >>> test("(identity x)")
    2
    >>> import operator
    >>> some_stg.put('add', BuiltinFunction(operator.add))
    >>> test("(add 10 20)")
    30
    >>> test("(add '10 '20)")
    30
    >>> test('(add "10" "20")')
    "1020"
    >>> test('(add x x)')
    4
    >>> test('((identity add) (identity x) (identity x))')
    4

    Macros should take *unevaluated paramaters* and the storage, do
    something with them, and return an expression *to be evaluated*!

    >>> def testmac(se, stg):
    ...     for i, arg in enumerate(se):
    ...         print(i, arg)
    ...     stg.put('f', se.car)
    ...     return se
    >>> some_stg.put('testmac', BuiltinMacro(testmac))
    >>> test("(testmac add 3 6)")
    0 add
    1 3
    2 6
    9
    >>> type(test('f'))
    <class 'slyther.types.Symbol'>
    >>> test('(f 1 2)')
    Traceback (most recent call last):
        ...
    TypeError: 'Symbol' object is not callable
    >>> test('((identity testmac) (identity add) (identity 1) 2)')
    0 (identity add)
    1 (identity 1)
    2 2
    3

    """
    # print(expr,type(expr))
    while(True):
        if expr is NIL:
            return NIL
        elif isinstance(expr, Quoted):
            if isinstance(expr.elem, SExpression):
                return quoted_sexpression_helper(expr.elem, stg)
            else:
                return expr.elem
        elif isinstance(expr, Symbol):
            return stg[str(expr)].value
        elif isinstance(expr, SExpression):
            call_able_var = lisp_eval(expr.car, stg)
            if isinstance(call_able_var, Macro):
                # return lisp_eval(call_able_var(expr.cdr, stg), stg)
                expr = call_able_var(expr.cdr, stg)
                continue
            elif callable(call_able_var):
                arguments = []
                for item in expr.cdr:
                    # handling the positional argument, new stuff starting
                    new_str = str(item)
                    if ('=' in new_str):
                        equal_index = index_of_equal_sign(new_str)
                        parameter_name, value = new_str[:equal_index], \
                            new_str[equal_index + 1:]
                        if(not value.isdigit()):
                            value = stg[value].value
                            new_str = parameter_name + '=' + str(value)
                            arguments.append(new_str)
                        else:
                            arguments.append(item)
                    # new stuff done
                    else:
                        arguments.append(lisp_eval(item, stg))
                value_returned = call_able_var(*arguments)
                if(isinstance(value_returned, tuple)):
                    expr, stg = value_returned
                    continue
                else:
                    return value_returned
            else:
                raise TypeError(
                    f"'{type(call_able_var).__name__}' object is not callable")
        else:
            return expr


def index_of_equal_sign(s):
    for index, item in enumerate(s):
        if(item == '='):
            return index


def quoted_sexpression_helper(expr, stg):
    if(expr.cdr is NIL):
        return ConsList(lisp_eval(Quoted(expr.car), stg), expr.cdr)
    else:
        return ConsList(
            lisp_eval(
                Quoted(
                    expr.car), stg), (quoted_sexpression_helper(
                        expr.cdr, stg)))
