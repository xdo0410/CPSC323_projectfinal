# CPSC323_projectfinal
Write a programm that use the given gramma and print out the following output

Given the following CFG (some rules are in EBNF form):
<start> PROGRAM<pname>; VAR ,dec-list>; BEGIN <stat-list> END.
<pname>      <id>
<id>         <letter>{<letter>|<digit>}
<dec-list>   <dec> : <type>
<dec>        <id>, <dec> | <id>

<stat-list>  <stat>; | <stat>; <stat-list>
<stat>       <print> | <assign>
<print>      PRINT (<output>)
<output>     [“string”,} <id>
<assign>     <id> = <expr>

<expr>       <term> | <expr> + <term> | <expr> - <term>
<term>       <term> * <factor> | <term> / <factor> | <factor>
<factor>     <id> | <number> | <( <expr> )
<number>     <digit>{<digit>}
<type>       INTEGER
<digit>      0|1|2|…|9
<letter>     a|b|c|d|e|f

Where PROGRAM, VAR, BEGIN, END. , INTEGER, PRINT are reserved words   and all uppercase.

Your job is to use the given grammar and determine whether the program in part 1 is accepted or not (i.e. whether there are or aren’t syntax errors in the program).  Your program should produce one of the following error messages as soon as the error is detected:

	PROGRAM is expected (if PROGRAM is missing or spelled wrong)
	VAR     is expected (if VAR is missing or spelled wrong)
	BEGIN   is expected (if BEGIN is missing ir spelled wrong)
	END.    is expected (if END. is missing or spelled wrong)
	UNKNOWN IDENTIFIER if variable is not defined

	;       ; is missing
	‘       ‘ is missing
	.       . is missing
	(       ( is missing
	)       ) is missing
	,       , is missing
	=       = is missing
