#include "comp"
#include "aldorio"
#pile

SymbolTableBinder: with
    bind: AbSyn -> SymbolTable
== add
    import from List AbSyn
    import from SymbolTable

    bind(whole: AbSyn): SymbolTable ==
        root: SymbolTable := root()$SymbolTable
	bind(whole, new(root, file))
	root
	
    bind(ab: AbSyn, tbl: SymbolTable): () ==
        stdout << "(Bind " << name tag ab << newline
        tag ab = lambda => bindLambda(ab, tbl)
	for abn in children ab repeat bind(abn, tbl)
        stdout << " Bind)" << newline

    bindLambda(ab: AbSyn, tbl: SymbolTable): () ==
        ab.symbolTable := new(tbl, lambda)
	for abn in children ab repeat bind(abn, ab.symbolTable)

    bindDeclarationsAndDefinitions(ab: AbSyn, tbl: SymbolTable): () ==
        tag ab = _define => bindDefine(ab, tbl)
        tag ab = declare => bindDeclare(ab, tbl)
	for abn in children ab repeat bindDeclarationsAndDefinitions(abn, symbolTable(ab, tbl)) 

    bindDefine(def: AbSyn, tbl: SymbolTable): () == never
    bindDeclare(def: AbSyn, tbl: SymbolTable): () == never
