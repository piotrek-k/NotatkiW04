grammar test;

@members {
	class MyException extends RuntimeException {
		MyException() {
			System.out.println("Blad!");
		}
	}
}

/* Obsług dowolną ilość wyrażeń expr aż do końca pliku */
plik
	: expr* EOF { System.out.println("Wynik: " + $expr.value); };

/*
Spodziewaj się jednomianu a zaraz po nim dowolnej ilości wyrażeń "[plus LUB minus] [jednomian]"
*/
expr returns [int value]
	: beginning_term=term {$value = $beginning_term.value; System.out.println("beginning_term: " + $value);}
	(
	  (
	      PLUS plus_term=term {$value += $plus_term.value; System.out.println("plus_term: " + $value);}
	      | MINUS minus_term=term {$value -= $minus_term.value; System.out.println("minus_term: " + $value);}
	      )
	  )*
	;
	
/* 
Spodziewaj się wyrażenia atom a zaraz po nim zero lub więcej wyrażeń "`*` atom" LUB "`/` atom" 
Obsługuje jednomiany
*/
term returns [int value]
	: beginning_atom=atom {$value = $beginning_atom.value; System.out.println("beginning_atom: " + $value);}
	(MUL mul_atom=atom {$value *= $mul_atom.value; System.out.println("mul_atom: " + $value);}
	| DIV div_atom=atom {
		if ($div_atom.value == 0)
			throw new MyException();
		$value /= $div_atom.value;
		 System.out.println("div_atom: " + $value);
	}
	| MOD mod_atom=atom {
		$value = $value \% $mod_atom.value;
	})*
	;

/* spodziewaj się liczby LUB wyrażenia expr między nawiasami */	
atom returns [int value]
	: INT {$value = Integer.parseInt($INT.text); System.out.println("Odczytano: " + $value); }
	| (LP expr RP) {$value = $expr.value;}
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
MOD	:	 '%';
NL   : '\n';

LP	:'('
	;

RP	: ')'
	;

