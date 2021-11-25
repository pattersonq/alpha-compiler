%{
#include <stdio.h>
#include "y.tab.h"

extern FILE * out;
long yylin = 1;
long yycol = 1;
int yy_morph_error = 0;
%}
%option noyywrap
ESPACIO 		    [ \t]+
COMENTARIO          "//".*\n
SALTOLINEA	        \n|\n\r|\r
MAIN                "main"
INT                 "int"
BOOLEAN             "boolean"
ARRAY               "array"
FUNCTION            "function"
IF                  "if"
ELSE                "else"
WHILE               "while"
SCANF               "scanf"
PRINTF              "printf"
RETURN              "return"
PUNTOYCOMA          ";"
COMA                ","
PARENTESISIZQUIERDO "("
PARENTESISDERECHO   ")"
CORCHETEIZQUIERDO   "["
CORCHETEDERECHO     "]"
LLAVEIZQUIERDA      "{"
LLAVEDERECHA        "}"
ASIGNACION          "="
MAS                 "+"
MENOS               "-"
DIVISION            "/"
ASTERISCO           "*"
AND                 "&&"
OR                  "||"
NOT                 "!"
IGUAL               "=="
DISTINTO            "!="
MENORIGUAL          "<="
MAYORIGUAL          ">="
MENOR               "<"
MAYOR               ">"
CONSTANTE_ENTERA    -?[0-9]+
TRUE                "true"
FALSE               "false"
IDENTIFICADOR       [a-zA-Z][a-zA-Z0-9]{0,98}
ERROR		        [a-zA-Z][a-zA-Z0-9]{99,}|.
%%  
{ESPACIO}	            { yycol += yyleng; }
{COMENTARIO}	        { yycol=0; yylin++; }
{SALTOLINEA}	        { yycol=0; yylin++; }
{MAIN}                  { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAIN; }          
{INT}                   { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_INT; }            
{BOOLEAN}               { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_BOOLEAN; }            
{ARRAY}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ARRAY; }        
{FUNCTION}              { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_FUNCTION; }          
{IF}                    { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IF; }              
{ELSE}                  { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ELSE; }          
{WHILE}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_WHILE; }        
{SCANF}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_SCANF; }        
{PRINTF}                { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PRINTF; }              
{RETURN}                { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_RETURN; }              
{PUNTOYCOMA}            { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA; }                             
{COMA}                  { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_COMA; }                           
{PARENTESISIZQUIERDO}   { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PARENTESISIZQUIERDO; }                            
{PARENTESISDERECHO}     { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PARENTESISDERECHO; }                          
{CORCHETEIZQUIERDO}     { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CORCHETEIZQUIERDO; }                          
{CORCHETEDERECHO}       { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CORCHETEDERECHO; }                            
{LLAVEIZQUIERDA}        { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_LLAVEIZQUIERDA; }                             
{LLAVEDERECHA}          { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_LLAVEDERECHA; }                           
{ASIGNACION}            { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ASIGNACION; }                             
{MAS}                   { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAS; }                            
{MENOS}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENOS; }                          
{DIVISION}              { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_DIVISION; }                           
{ASTERISCO}             { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ASTERISCO; }                          
{AND}                   { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_AND; }                            
{OR}                    { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_OR; }                             
{NOT}                   { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_NOT; }                            
{IGUAL}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IGUAL; }                          
{DISTINTO}              { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_DISTINTO; }                           
{MENORIGUAL}            { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENORIGUAL; }                             
{MAYORIGUAL}            { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL; }                             
{MENOR}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENOR; }                          
{MAYOR}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAYOR; }          
{CONSTANTE_ENTERA}      { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA; }                        
{TRUE}                  { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_TRUE; }                        
{FALSE}                 { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_FALSE; }                  
{IDENTIFICADOR}         { yycol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IDENTIFICADOR; }                                         
{ERROR}                 {fprintf(stderr, "****Error en linea (Flex) %ld: \n", yylin); yycol += yyleng; yy_morph_error = 1; return  TOK_ERROR;}
%%
 
/*
int main() {
         return yylex();
}*/