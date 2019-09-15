from __future__ import unicode_literals
from prompt_toolkit import PromptSession
from prompt_toolkit.completion import WordCompleter
from prompt_toolkit.lexers import PygmentsLexer
from prompt_toolkit.styles import Style
from pygments.lexers.sql import SqlLexer

import traceback
import sys


def repl(interpreter, debug=False):

    sql_completer = WordCompleter(['define',
                                   'floordiv',
                                   'list',
                                   'car',
                                   'cdr',
                                   'nil',
                                   'lambda',
                                   'let',
                                   'if',
                                   'cond',
                                   'and',
                                   'or',
                                   'set!',
                                   'eval',
                                   'parse',
                                   'abort',
                                   'action',
                                   'add',
                                   'after',
                                   'all',
                                   'alter',
                                   'analyze',
                                   'and',
                                   'as',
                                   'asc',
                                   'attach',
                                   'autoincrement',
                                   'before',
                                   'begin',
                                   'between',
                                   'by',
                                   'cascade',
                                   'case',
                                   'cast',
                                   'check',
                                   'collate',
                                   'column',
                                   'commit',
                                   'conflict',
                                   'constraint',
                                   'create',
                                   'cross',
                                   'current_date',
                                   'current_time',
                                   'current_timestamp',
                                   'database',
                                   'default',
                                   'deferrable',
                                   'deferred',
                                   'delete',
                                   'desc',
                                   'detach',
                                   'distinct',
                                   'drop',
                                   'each',
                                   'else',
                                   'end',
                                   'escape',
                                   'except',
                                   'exclusive',
                                   'exists',
                                   'explain',
                                   'fail',
                                   'for',
                                   'foreign',
                                   'from',
                                   'full',
                                   'glob',
                                   'group',
                                   'having',
                                   'if',
                                   'ignore',
                                   'immediate',
                                   'in',
                                   'index',
                                   'indexed',
                                   'initially',
                                   'inner',
                                   'insert',
                                   'instead',
                                   'intersect',
                                   'into',
                                   'is',
                                   'isnull',
                                   'join',
                                   'key',
                                   'left',
                                   'like',
                                   'limit',
                                   'match',
                                   'natural',
                                   'no',
                                   'not',
                                   'notnull',
                                   'null',
                                   'of',
                                   'offset',
                                   'on',
                                   'or',
                                   'order',
                                   'outer',
                                   'plan',
                                   'pragma',
                                   'primary',
                                   'query',
                                   'raise',
                                   'recursive',
                                   'references',
                                   'regexp',
                                   'reindex',
                                   'release',
                                   'rename',
                                   'replace',
                                   'restrict',
                                   'right',
                                   'rollback',
                                   'row',
                                   'savepoint',
                                   'select',
                                   'set',
                                   'table',
                                   'temp',
                                   'temporary',
                                   'then',
                                   'to',
                                   'transaction',
                                   'trigger',
                                   'union',
                                   'unique',
                                   'update',
                                   'using',
                                   'vacuum',
                                   'values',
                                   'view',
                                   'virtual',
                                   'when',
                                   'where',
                                   'with',
                                   'without',
                                   'print'],
                                  ignore_case=True)

    style = Style.from_dict({
        'completion-menu.completion': 'bg:#008888 #ffffff',
        'completion-menu.completion.current': 'bg:#00aaaa #000000',
        'scrollbar.background': 'bg:#88aaaa',
        'scrollbar.button': 'bg:#222222',
    })
    session = PromptSession(
        lexer=PygmentsLexer(SqlLexer), completer=sql_completer, style=style)

    """
    Take an interpreter object (see ``slyther/interpreter.py``) and give a REPL
    on it. Should not return anything: just a user interface at the terminal.
    For example::

        $ slyther
        > (print "Hello, World!")
        Hello, World!
        NIL
        > (+ 10 10 10)
        30

    When the user presses ^D at an empty prompt, the REPL should exit.

    When the user presses ^C at any prompt (whether there is text or
    not), the input should be cancelled, and the user prompted again::

        $ slyther
        > (blah bla^C
        >                   <-- ^C resulted in new prompt line

    Should be pretty easy. No unit tests for this function, but I will
    test the interface works when I grade it.

    Optionally, you may want to prevent the REPL from raising an exception
    when an exception in user code occurs, and allow the user to keep
    typing further expressions. This is not required, just a suggestion.
    If you do this, you should probably disable this behavior when ``debug``
    is set to ``True``, as it allows for easy post-mortem debugging with pdb
    or pudb.
    """
    while(True):
        try:
            code = session.prompt('> ')
            print(interpreter.exec(code))
        except EOFError:
            sys.exit(0)
        except KeyboardInterrupt:
            print()
            continue
        except SyntaxError:
            while(True):
                try:
                    code = code + session.prompt('. ')
                    print(interpreter.exec(code))
                    break
                except SyntaxError:
                    continue
                except BaseException:
                    if(not debug):
                        traceback.print_exc()
                    break
        except BaseException:
            if(not debug):
                traceback.print_exc()
                continue
