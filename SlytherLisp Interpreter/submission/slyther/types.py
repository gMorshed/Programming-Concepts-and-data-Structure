import collections.abc as abc

from typing import Dict

from functools import partial, update_wrapper


class ConsCell:

    """

    A simple cons cell data structure:



    >>> cell = ConsCell(1, 2)

    >>> cell.car

    1

    >>> cell.cdr

    2

    >>> cell.car = 4

    >>> cell.car

    4

    """

    def __init__(self, car, cdr):

        self.car = car

        self.cdr = cdr

    def __eq__(self, other):
        """

        Two cons cells are equal if each of their ``car`` and

        ``cdr`` are equal:



        >>> a = ConsCell(1, 2)

        >>> b = ConsCell(2, 1)

        >>> c = ConsCell(1, 1)

        >>> d = ConsCell(1, 2)

        >>> a == a

        True

        >>> a == b

        False

        >>> b == c

        False

        >>> b == d

        False

        >>> a == d

        True



        Should return ``False`` if ``other`` is not an instance of a

        ``ConsCell``.

        """

        if not isinstance(other, ConsCell):

            return False

        if self.car == other.car and self.cdr == other.cdr:

            return True

        else:

            return False

    def __repr__(self):
        """

        A cons cell should ``repr`` itself in a format that would

        be parsable and evaluable to our language.



        >>> ConsCell(1, 2)

        (cons 1 2)

        >>> ConsCell(ConsCell(2, 1), 1)

        (cons (cons 2 1) 1)



        .. hint::



            The string formatting specifier ``!r`` will get you the

            ``repr`` of an object.

        """

        return '(cons ' + repr(self.car) + ' ' + repr(self.cdr) + ')'


class ConsList(ConsCell, abc.Sequence):

    """

    A ``ConsList`` inherits from a ``ConsCell``, but the ``cdr`` must

    be a ``ConsList`` or any structure which inherits from that.



    >>> cell = ConsList(1, ConsList(2, NIL))

    >>> cell.car

    1

    >>> cell.cdr.car

    2

    >>> cell = ConsList(1, 2)

    Traceback (most recent call last):

        ...

    TypeError: cdr must be a ConsList

    """

    def __init__(self, car, cdr=None):
        """

        If the ``cdr`` was not provided, assume to be ``NIL``.



        >>> cell = ConsList(1)

        >>> cell.cdr

        NIL

        """

        if not isinstance(cdr, ConsList):

            if(cdr is not None):

                raise TypeError("cdr must be a ConsList")

        if cdr is None:

            cdr = NIL

        super().__init__(car, cdr)

    @classmethod
    def from_iterable(cls, it):
        """

        Create an instance of ``cls`` from an iterable (anything that can go

        on the right hand side of a ``for`` loop).



        >>> lst = ConsList.from_iterable(iter(range(3)))

        >>> [lst.car, lst.cdr.car, lst.cdr.cdr.car, lst.cdr.cdr.cdr]

        [0, 1, 2, NIL]

        >>> ConsList.from_iterable([])

        NIL



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(n), where n is length of ``it``

        :Space complexity: O(n) ``ConsList`` objects,

                           O(1) everything else (including stack frames!)

        """

        it = iter(it)

        try:

            shell = cls(next(it))

        except StopIteration:

            return NIL

        nextcell = shell

        for i in it:

            nextcell.cdr = cls(i)

            nextcell = nextcell.cdr

        return shell

    def __getitem__(self, idx):
        """

        Get item at index ``idx``:



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> clst = ConsList.from_iterable(lst)

        >>> [lst[i] == clst[i] for i in range(len(lst))]

        [True, True, True, True, True, True]

        """

        for i, element in enumerate(self):

            if i == idx:

                return element

        return NIL

    def __iter__(self):
        """

        Iterate over the ``car`` of each cell:



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> for itm in ConsList.from_iterable(lst):

        ...     print(itm)

        1

        1

        2

        3

        5

        8



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(1) for each yield

        :Space complexity: O(1)

        """

        head = self

        while (head != NIL):

            yield head.car

            head = head.cdr

    def cells(self):
        """

        Iterate over each cell (rather that the ``car`` of each):



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> for cell in ConsList.from_iterable(lst).cells():

        ...     print(cell.car)

        1

        1

        2

        3

        5

        8



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(1) for each yield

        :Space complexity: O(1)

        """

        head = self

        while (head != NIL):

            yield head

            head = head.cdr

    def __len__(self):
        """

        Return the number of elements in the list:



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> len(ConsList.from_iterable(lst))

        6



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(n), where n is the length of the list.

        :Space complexity: O(1)

        """

        count = 0

        head = self

        while (head != NIL):

            count += 1

            head = head.cdr

        return count

    def __contains__(self, p):
        """

        Return ``True`` if the list contains an element ``p``, ``False``

        otherwise. A list is said to contain an element ``p`` iff there is any

        element ``a`` in the list such that ``a == p``.



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> clst = ConsList.from_iterable(lst)

        >>> 1 in clst

        True

        >>> 3 in clst

        True

        >>> 8 in clst

        True

        >>> NIL in clst

        False

        >>> 9 in clst

        False



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(n), where n is the length of the list.

        :Space complexity: O(1)

        """

        head = self

        while(head != NIL):

            if head.car == p:

                return True

            head = head.cdr

        return False

    def __reversed__(self):
        """

        Iterate over the elements of our list, reversed.



        >>> lst = [1, 1, 2, 3, 5, 8]

        >>> clst = ConsList.from_iterable(lst)

        >>> for x in reversed(clst):

        ...     print(x)

        8

        5

        3

        2

        1

        1



        Note: Your implementation is subject to the following constraints:



        :Time complexity: O(n), where n is the length of the list.

        :Space complexity: O(n)

        """

        list1 = []

        head = self

        while(head != NIL):

            list1.append(head.car)

            head = head.cdr

        for i in reversed(list1):

            yield i

    def __bool__(self):
        """ NilType overrides this to be ``False``. """

        return True

    def __eq__(self, other):
        """

        Test if two lists have the same elements in the same order.



        >>> l1, l2 = map(

        ...     ConsList.from_iterable,

        ...     ([1, 2, 10, 3, 4, 7], [1, 2, 10, 3, 4, 7]))

        >>> l1 == l2

        True

        >>> l1, l2 = map(

        ...     ConsList.from_iterable,

        ...     ([1, 2, 10, 4, 3, 7], [1, 2, 10, 3, 4, 7]))

        >>> l1 == l2

        False

        >>> l1, l2 = map(

        ...     ConsList.from_iterable,

        ...     ([1, 2, 10, 3, 4, 7], [1, 2, 10, 3, 4, 7, 1]))

        >>> l1 == l2

        False

        >>> l2 == l1

        False

        >>> l1 = NIL

        >>> l1 == l2

        False

        >>> l2 == l1

        False

        >>> SExpression.from_iterable(l2) == NIL

        False

        """

        if not isinstance(self, type(other)):

            return False

        while self is not NIL and other is not NIL:

            if(self.car != other.car):

                return False

            self = self.cdr

            other = other.cdr

        if(self is NIL and other is not NIL):

            return False

        elif(other is NIL and self is not NIL):

            return False

        return True

    def __repr__(self):
        """

        Represent ourselves in a format evaluable in SlytherLisp.



        >>> ConsList.from_iterable([1, 2, 3])

        (list 1 2 3)

        """

        re_str = "list"

        head = self

        while head != NIL:

            re_str += " "

            re_str += repr(head.car)

            head = head.cdr

        return '({})'.format(re_str)


class NilType(ConsList):

    """

    The type for the global ``NIL`` object.

    """

    def __new__(cls):
        """

        If already constructed, don't make another. Just

        return our already existing instance.

        """

        if 'NIL' in globals().keys():

            return NIL

        return super().__new__(cls)

    def __init__(self):
        """

        The ``car`` and ``cdr`` of ``NIL`` are ``NIL``.

        """

        self.car = self

        self.cdr = self

    def __bool__(self):
        """

        Empty lists are implicitly falsy.

        """

        return False

    def __eq__(self, other):
        """

        There is only one ``NIL`` instance anyway...

        """

        return self is other

    def __repr__(self):
        """

        Represent ourselves in SlytherLisp evaluable format

        """

        return 'NIL'


NIL = NilType()


class Boolean:

    """

    Type for a boolean with SlytherLisp evaluable representation.

    """

    # too bad we can't subclass bool...

    class LispTrue:

        def __bool__(self):

            return True

        def __repr__(self):

            return '#t'

    class LispFalse:

        def __bool__(self):

            return False

        def __repr__(self):

            return '#f'

    t_instance = LispTrue()

    f_instance = LispFalse()

    def __new__(cls, v=False):
        """

        There shall only be one true, and one false!

        """

        if v:

            return Boolean.t_instance

        return Boolean.f_instance


class SExpression(ConsList):

    """

    ConsList which we use to store s-expressions. Has an alternate

    representation.



    >>> SExpression(4)

    (4)

    """

    def __repr__(self):

        return '({})'.format(' '.join(map(repr, self)))


def cons(car, cdr) -> ConsCell:
    """

    Factory for cons cell like things. Tries to make a ``ConsList`` or

    ``SExpression`` if it can (if ``cdr`` is...), otherwise makes a

    plain old ``ConsCell``.



    >>> cons(5, ConsList(4, NIL))

    (list 5 4)

    >>> cons(5, NIL)

    (list 5)

    >>> cons(5, 4)

    (cons 5 4)

    >>> cons(5, SExpression(4, NIL))

    (5 4)

    """

    if isinstance(cdr, SExpression):

        cellex = SExpression(car, cdr)

        return cellex

    elif isinstance(cdr, ConsList):

        celllist = ConsList(car, cdr)

        return celllist

    elif cdr == NIL or None:

        celllist = ConsList(car, cdr)

        return celllist

    else:

        cell = ConsCell(car, cdr)

        return cell


class Variable:

    """

    A simple wrapper to reference an object. The reference may change using the

    ``set`` method.



    The reason for this is so that ``(set! ...)`` works, even in different

    environments. Also lets Python's garbage collection do the dirty work for

    us.



    Note: ``Variable`` will never appear in an abstract syntax tree. Its sole

    purpose is to be used with the ``LexicalVariableStorage``.

    """

    def __init__(self, value):

        self.set(value)

    def set(self, value):

        self.value = value


class LexicalVarStorage:

    """

    Storage for lexically scoped variables. Has two parts:



    * An ``environ`` part: a dictionary of the containing

      environment (closure).

    * A ``local`` part: a dictionary of the local variables

      in the function.

    """

    def __init__(self, environ: Dict[str, Variable]):

        self.environ = environ

        self.local = {}

    def fork(self) -> Dict[str, Variable]:
        """

        Return the union of the ``local`` part and the ``environ``

        part. Should not modify either part.



        >>> environ = {k: Variable(v) for k, v in (('x', 10), ('y', 11))}

        >>> stg = LexicalVarStorage(environ)

        >>> stg.put('y', 12)

        >>> stg.put('z', 13)

        >>> for k, v in stg.fork().items():

        ...     print(k, v.value)

        x 10

        y 12

        z 13

        """
        n_dict = self.environ.copy()

        n_dict.update(self.local)

        return n_dict

    def put(self, name: str, value) -> None:
        """

        Put a **new** variable in the local environment, giving

        it a value ``value``.

        """

        self.local[name] = Variable(value)

    def __getitem__(self, key: str) -> Variable:
        """

        Return a Variable object, first checking the local

        environment, then checking the containing environment,

        otherwise raising a ``KeyError``.



        >>> environ = {k: Variable(v) for k, v in (('x', 10), ('y', 11))}

        >>> stg = LexicalVarStorage(environ)

        >>> stg.put('y', 12)
        >>> stg.put('z', 13)

        >>> stg['x'].value

        10

        >>> stg['y'].value

        12

        >>> stg['z'].value

        13

        >>> stg['x'].set(11)

        >>> stg['foo'].value

        Traceback (most recent call last):

            ...

        KeyError: "Undefined variable 'foo'"

        >>> stg['bar'].set(10)

        Traceback (most recent call last):

            ...

        KeyError: "Undefined variable 'bar'"

        """
        if key in self.local.keys():

            return self.local[key]

        elif key in self.environ.keys():

            return self.environ[key]

        else:

            raise KeyError("Undefined variable " + repr(key))


class Quoted:

    """

    A simple wrapper for a quoted element in the abstract syntax tree.

    """

    def __init__(self, elem):

        self.elem = elem

    def __repr__(self):

        return "'{!r}".format(self.elem)

    def __eq__(self, other):

        return isinstance(other, self.__class__) and self.elem == other.elem


class Symbol(str):

    """

    A type for symbols, like a ``str``, but alternate representation.

    """

    def __repr__(self):

        return str(self)


class String(str):

    """

    A type for SlytherLisp strings, like a ``str``, but alternate

    representation: always use double quotes since SlytherLisp only

    allows double quoted strings.

    """

    def __repr__(self):

        r = super().__repr__()

        if r.startswith("'"):

            return '"{}"'.format(r[1:-1].replace('"', '\\"')

                                        .replace("\\'", "'"))

        return r


class Function(abc.Callable):

    """

    Base class for user and builtin functions. No implementation needed.

    """

# new function helper for Userfunction


def index_of_equal_sign(s):
    for index, item in enumerate(s):
        if(item == '='):
            return index


class UserFunction(Function):

    """

    Type for user defined functions.



    * ``params`` is an s-expression of the parameters, like so:

      (a b c)

    * ``body`` is an SExpression with the body of the function. The

      result of the last element in the body should be returned when

      the function is called.

    * ``environ`` is a dictionary created by calling ``.fork()`` on a

      ``LexicalVarStorage`` when the function was created.



    """

    def __init__(self, params: SExpression, body: SExpression, environ: dict):
        """

        >>> from slyther.parser import lisp

        >>> f = UserFunction(

        ...     params=lisp('(a b c)'),

        ...     body=lisp('((print a b) (print c))'),

        ...     environ={})

        >>> f

        (lambda (a b c) (print a b) (print c))

        >>> f.params

        (a b c)

        >>> f.body

        ((print a b) (print c))

        >>> f.environ

        {}

        """
        self.environ = environ
        # new code handling default parameter
        modified_params = []
        found_default_argument = False
        for item in params:
            s = str(item)
            if('=' in s):
                equal_index = index_of_equal_sign(s)
                modified_params.append(s[:equal_index])
                if(s[equal_index + 1:].isdigit()):
                    '''
                    if its primitive number, good to go
                    '''
                    environ[s[:equal_index]] = Variable(s[equal_index + 1:])
                else:  # otherwise have to find the value
                    environ[s[:equal_index]] = Variable(
                        self.environ[(s[equal_index + 1:])].value)
                found_default_argument = True
            else:
                if(found_default_argument):
                    raise BaseException(
                        'non-default argument follows default argument')
                modified_params.append(s)
        # default parameter handling done
        if(found_default_argument):
            self.params = SExpression.from_iterable(modified_params)
        else:
            self.params = params
        self.body = body

    def __call__(self, *args):
        """

        Call the function with arguments ``args``.



        Make use of ``lisp_eval``. Note that a fully working ``lisp_eval``

        implementation will require this function to work properly, and this

        will require a working ``lisp_eval`` to work properly, so you must

        write both before you can test it.



        Warning: Do not make any attempt to modify ``environ`` here. That is

        not how lexical scoping works. Instead, construct a new

        ``LexicalVarStorage`` from the existing environ.

        """

        # avoid circular imports

        from slyther.evaluator import lisp_eval

        new_lex_var = LexicalVarStorage(self.environ)

        param_list = []

        for item in self.params:

            param_list.append(item)
        # keyword argument handling code start
        param_dict = {}
        count = 0
        for item in param_list:
            param_dict[item] = count
            count = count + 1
        new_args = [0 for i in range(len(param_list))]
        found_keyword_args = False
        for index, item in enumerate(args):
            s = str(item)
            if('=' in s):
                equal_index = index_of_equal_sign(s)
                new_args[param_dict[s[:equal_index]]] = int(
                    s[equal_index + 1:])
                found_keyword_args = True
            else:
                if(found_keyword_args):
                    raise BaseException(
                        'positional argument follows keyword argument')
                new_args[index] = item
        if(found_keyword_args):
            args = new_args
        # key word argument handling done
        for p, a in zip(param_list, args):

            new_lex_var.put(p, a)

        for cell in self.body.cells():
            if isinstance(cell.cdr, NilType):
                return (cell.car, new_lex_var)
            lisp_eval(cell.car, new_lex_var)
        return NIL

    def __repr__(self):
        """

        Represent in self-evaluable form.

        """

        return "(lambda ({}) {})".format(

            ' '.join(self.params),

            ' '.join(repr(x) for x in self.body))


class Macro(abc.Callable):

    """

    Base class for all macros. No implementation needed.

    """


class BuiltinCallable(abc.Callable):

    """

    Base class for builtin callables (functions and macros)

    """

    py_translations = {

        bool: Boolean,

        str: String,

        list: ConsList.from_iterable,

        tuple: ConsList.from_iterable,

    }

    def __new__(cls, arg=None, name=None):

        if isinstance(arg, str):

            return partial(cls, name=arg)

        obj = super().__new__(cls)

        obj.func = arg

        update_wrapper(obj, obj.func)

        obj.__name__ = name or obj.func.__name__

        return obj

    def __call__(self, *args, **kwargs):

        # Note: this function was provided for you in the starter code

        # and you do NOT need to change it.

        result = self.func(*args, **kwargs)

        if result is None:

            return NIL

        if type(result) in self.py_translations.keys():

            return self.py_translations[type(result)](result)

        return result


class BuiltinFunction(BuiltinCallable, Function):

    """

    Builtin functions have this type. Unlike macros, functions cannot

    return s-expressions, and they should be downgraded to cons lists.

    """

    py_translations = dict(BuiltinCallable.py_translations)

    py_translations.update({SExpression: ConsList.from_iterable})


class BuiltinMacro(BuiltinCallable, Macro):

    """

    Builtin macros have this type. No implementation needed.

    """
