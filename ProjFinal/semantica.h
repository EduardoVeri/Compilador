#ifndef _ANALISE_SEMANT_H_
#define _ANALISE_SEMANT_H_

void percorrerDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* auxEscopo);
void percorrerExp(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], char escopo[]);
void percorrerArvore(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* escopo);
int buscaIgual(PONTEIROITEM* tabelaHash, PONTEIRONO arvoreSintatica, int indice, char* escopo);
void mostrarErroSemantico(erroSemantico erro, char* nome, int linha);

#endif