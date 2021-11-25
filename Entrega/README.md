# PAUTLEN_P2
Práctica 3 PATULEN
## Autores
 - Pedro Sánchez de la Muela
 - Javier Barranco Tena
 - Pablo Quintanilla Berriochoa
## Uso del makefile
Hay 4 archivos de test, se pueden ejecutar con el comando:
```
  make test
```
Para limpiar la carpeta del proyecto de todos los archivos generados basta con usar:
```
  make clean
```
## Nota
Hemos tomado una decisión de implementación distinta a la que vienen en _gramatica de alfa.docx_, en este documento se define come _exp_ como, entre otras cosas: _(comparacion)_, y luego se definie _condicional_ como if(_exp_) {...}, lo que fuerza a que los if's se escriban con dobles paréntisis.

Para evitar esto hemos cambiado la regla de _exp_ a simplemente: _comparacion_
