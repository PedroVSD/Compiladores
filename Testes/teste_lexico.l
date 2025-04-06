%{
#include <string.h>
%}

%%




[0-9]+        { 
    yylval.intValue = atoi(yytext); 
    return INT; 
}


[0-9]+\.[0-9]+  { 
    yylval.doubleValue = atof(yytext); 
    return DOUBLE; 
}


"\'[a-zA-Z]\'" { 
    yylval.charValue = yytext[1]; 
    return CHAR; 
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.nome = strdup(yytext);
    return VAR;
}



"+" {return PLUS_TK;}
"-" {return LESS_TK;}
"*" {return PROD_TK;}
"/" {return DIVIDE_TK;}    
"==" {return EQUAL_EQUAL_TK;}
"!=" {return NOT_EQUAL_TK;}
"&&" {return AND_TK;}
"||" {return OR_TK;}
"!" {return NOT_TK;}
"=" {yylval.nome = yytext; return ATRIBUICAO_TK;}
"++" {return INCREMENT_TK;}    
"--" {return DECREMENT_TK;}

"main"        { return MAIN_TK; }
"if"          { return IF_TK; }
"for"         { return FOR_TK; }
"while"       { return WHILE_TK; }
"int"         { return INT_TK; }
"double"      { return FLOAT_TK; }
"char"        { return CHAR_TK; }
"string"      { return STRING_TK; }
"bool"        { return BOOL_TK; }
"var"         { return VAR_TK; }

[ \t]         {  }


"\n" {return FIM_LINHA_TK;}
%%
