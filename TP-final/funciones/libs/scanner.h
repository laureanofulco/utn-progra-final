#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

void limpiarBuferDeEntrada(void);
int confirmar(char condicion);
int scanInt(void);
float scanFloat(void);
int scanString(char* string, int maxLength);

#endif // SCANNER_H_INCLUDED
