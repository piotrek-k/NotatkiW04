grammar supergramatyka;

/* Obsług dowolną ilość wyrażeń expr aż do końca pliku */
plik
	: expr* EOF;

/*
Spodziewaj się jednomianu a zaraz po nim dowolnej ilości wyrażeń "[plus LUB minus] [jednomian]"
*/
expr
	: term ((PLUS term
	| MINUS term))*
	;
	
/* 
Spodziewaj się wyrażenia atom a zaraz po nim zero lub więcej wyrażeń "`*` atom" LUB "`/` atom" 
Obsługuje jednomiany
*/
term
	: atom(MUL atom
	| DIV atom)*
	;

/* spodziewaj się liczby LUB wyrażenia expr między nawiasami */	
atom
	: INT
	| (LP expr RP)
	;

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :	'0'..'9'+
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        ) {$channel=HIDDEN;}
    ;
    
PLUS : '+';
MINUS: '-';
MUL  : '*';
DIV  : '/';
NL   : '\n';

LP	:'('
	;

RP	: ')'
	;

