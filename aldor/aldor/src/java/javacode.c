#include "javacode.h"
#include "javaobj.h"
#include "sexpr.h"
#include "util.h"

enum jc_clss_enum {
	JCO_CLSS_START,
	JCO_CLSS_String = JCO_CLSS_START,
	JCO_CLSS_Character,
	JCO_CLSS_Integer,
	JCO_CLSS_Float,
	JCO_CLSS_Double,
	JCO_CLSS_Keyword,
	JCO_CLSS_Id,
	JCO_CLSS_CommaSeq,
	JCO_CLSS_SpaceSeq,
	JCO_CLSS_NLSeq,
	JCO_CLSS_Seq,
	JCO_CLSS_Parens,
	JCO_CLSS_Braces,
	JCO_CLSS_SqBrackets,
	JCO_CLSS_ABrackets,
	JCO_CLSS_ImportedId,
	JCO_CLSS_ImportedStatic,
	JCO_CLSS_Annotation,
	JCO_CLSS_Class,
	JCO_CLSS_JavaDoc,
	JCO_CLSS_Comment,
	JCO_CLSS_Method,
	JCO_CLSS_Declaration,
	JCO_CLSS_Statement,
	JCO_CLSS_File,

	JCO_CLSS_If,
	JCO_CLSS_While,
	JCO_CLSS_Switch,
	JCO_CLSS_Case,
	JCO_CLSS_Block,
	JCO_CLSS_Try,
	JCO_CLSS_Catch,
	JCO_CLSS_Finally,

	JCO_CLSS_ArrRef,
	JCO_CLSS_MemRef,
	JCO_CLSS_Cast,

	JCO_CLSS_Apply,
	JCO_CLSS_Construct,

	JCO_CLSS_Not,
	JCO_CLSS_LogAnd,
	JCO_CLSS_LogOr,
	JCO_CLSS_And,
	JCO_CLSS_Or,
	JCO_CLSS_XOr,
	JCO_CLSS_Equals,
	JCO_CLSS_NEquals,
	JCO_CLSS_Assign,
	JCO_CLSS_Plus,
	JCO_CLSS_Minus,
	JCO_CLSS_Times,
	JCO_CLSS_Divide,
	JCO_CLSS_Modulo,
	JCO_CLSS_LT,
	JCO_CLSS_LE,
	JCO_CLSS_GT,
	JCO_CLSS_GE,
	JCO_CLSS_Negate,
	JCO_CLSS_ShiftUp,
	JCO_CLSS_ShiftDn,

	JCO_CLSS_Conditional,
	JCO_CLSSS_END
};

enum JavaKeywordTag {
JK_Abstract,
JK_Assert,
JK_Boolean,
JK_Break,
JK_Byte,
JK_Case,
JK_Catch,
JK_Char,
JK_Class,
JK_Const,
JK_Continue,
JK_Default,
JK_Do,
JK_Double,
JK_Else,
JK_Enum,
JK_Extends,
JK_Final,
JK_Finally,
JK_Float,
JK_For,
JK_Goto,
JK_If,
JK_Implements,
JK_Import,
JK_Instanceof,
JK_Int,
JK_Interface,
JK_Long,
JK_Native,
JK_New,
JK_Package,
JK_Private,
JK_Protected,
JK_Public,
JK_Return,
JK_Short,
JK_Static,
JK_Strictfp,
JK_Super,
JK_Switch,
JK_Synchronized,
JK_This,
JK_Throw,
JK_Throws,
JK_Transient,
JK_Try,
JK_Void,
JK_Volatile,
JK_While,
JK_False,
JK_Null,
JK_True,
JK_END
};


typedef struct javaKeyword {
	int id;
	String text;
} *JavaKeyword;

struct javaKeyword jkKeywords[] = {
	{ JK_Abstract,		"abstract"	},
	{ JK_Assert,		"assert"	},
	{ JK_Boolean,		"boolean"	},
	{ JK_Break,		"break"		},
	{ JK_Byte,		"byte"		},
	{ JK_Case,		"case"		},
	{ JK_Catch,		"catch"		},
	{ JK_Char,		"char"		},
	{ JK_Class,		"class"		},
	{ JK_Const,		"const"		},
	{ JK_Continue,		"continue"	},
	{ JK_Default,		"default"	},
	{ JK_Do,		"do"		},
	{ JK_Double,		"double"	},
	{ JK_Else,		"else"		},
	{ JK_Enum,		"enum"		},
	{ JK_Extends,		"extends"	},
	{ JK_Final,		"final"		},
	{ JK_Finally,		"finally"	},
	{ JK_Float,		"float"		},
	{ JK_For,		"for"		},
	{ JK_Goto,		"goto"		},
	{ JK_If,		"if"		},
	{ JK_Implements,	"implements"	},
	{ JK_Import,		"import"	},
	{ JK_Instanceof,	"instanceof"	},
	{ JK_Int,		"int"		},
	{ JK_Interface,		"interface"	},
	{ JK_Long,		"long"		},
	{ JK_Native,		"native"	},
	{ JK_New,		"new"		},
	{ JK_Package,		"package"	},
	{ JK_Private,		"private"	},
	{ JK_Protected,		"protected"	},
	{ JK_Public,		"public"	},
	{ JK_Return,		"return"	},
	{ JK_Short,		"short"		},
	{ JK_Static,		"static"	},
	{ JK_Strictfp,		"strictfp"	},
	{ JK_Super,		"super"		},
	{ JK_Switch,		"switch"	},
	{ JK_Synchronized,	"synchronized"	},
	{ JK_This,		"this"		},
	{ JK_Throw,		"throw"		},
	{ JK_Throws,		"throws"	},
	{ JK_Transient,		"transient"	},
	{ JK_Try,		"try"		},
	{ JK_Void,		"void"		},
	{ JK_Volatile,		"volatile"	},
	{ JK_While,		"while"		},
	{ JK_False,		"false"		},
	{ JK_Null,		"null"		},
	{ JK_True,		"true"		},
};

typedef Enum(jc_clss_enum) JcClassId;

local JWriteFn jcAnnotationPrint;
local JWriteFn jcApplyPrint;
local JWriteFn jcARefPrint;
local JWriteFn jcBinOpPrint;
local JWriteFn jcBlockHdrPrint;
local JWriteFn jcBlockKeywordPrint;
local JWriteFn jcBlockPrint;
local JWriteFn jcCasePrint;
local JWriteFn jcCastPrint;
local JWriteFn jcClassPrint;
local JWriteFn jcCommentPrint;
local JWriteFn jcCondPrint;
local JWriteFn jcConstructPrint;
local JWriteFn jcDeclarationPrint;
local JWriteFn jcIdPrint;
local JWriteFn jcImportPrint;
local JWriteFn jcIntegerPrint;
local JWriteFn jcJavaDocPrint;
local JWriteFn jcKeywordPrint;
local JWriteFn jcMethodPrint;
local JWriteFn jcParenPrint;
local JWriteFn jcSequencePrint;
local JWriteFn jcStatementPrint;
local JWriteFn jcFilePrint;
local JWriteFn jcStringPrint;
local JWriteFn jcUnaryOpPrint;

local JSExprFn jcCommentSExpr;
local JSExprFn jcIdSExpr;
local JSExprFn jcImportSExpr;
local JSExprFn jcIntegerSExpr;
local JSExprFn jcKeywordSExpr;
local JSExprFn jcStringSExpr;

local JavaCodeList jc0CreateModifiers(int modifiers);
local void jc0PrintWithParens(JavaCodePContext ctxt, JavaCodeClass oclss, JavaCode arg);
local Bool jc0NeedsParens(JavaCodeClass c1, JavaCodeClass c2);
local String jc0EscapeString(String s, Bool terminal);
local Bool jcBlockHdrIndent(JavaCode code);
local JavaCode jcBinaryOp(JavaCodeClass c, JavaCode lhs, JavaCode rhs);

/*
Operator	Description 	                  Associativity
15.    ()      Parentheses (grouping)                    left-to-right
14.    ++  --  Unary postincrement/postdecrement         right-to-left
13      ++  --  Unary preincrement/predecrement           right-to-left
        +  -    Unary plus/minus
        !  ~    Unary logical negation/bitwise complement
        (type)  Unary cast (change type)
12.     *  /  %         Multiplication/division/modulus    left-to-right
11.     +  -    Addition/subtraction    left-to-right
10.     <<  >>  Bitwise shift left, Bitwise shift right    left-to-right
9.      <  <=   Relational less than/less than or equal to       left-to-right
        >  >=   Relational greater than/greater than or equal to
        instanceof      Type comparison
8      ==  !=  Relational is equal to/is not equal to  left-to-right
7      &       Bitwise AND     left-to-right
6      ^       Bitwise exclusive OR    left-to-right
5.     |       Bitwise inclusive OR    left-to-right
4.      &&      Logical AND     left-to-right
3.      ||      Logical OR      left-to-right
2.      ?:      Ternary conditional     right-to-left
1.      =         Assignment                                  right-to-left
        +=  -=    Addition/subtraction assignment
        *=  /=    Multiplication/division assignment
        %=  &=    Modulus/bitwise AND assignment
        ^=  |=    Bitwise exclusive/inclusive OR assignment
        <<=  >>=  Bitwise shift left/right assignment

*/
static struct jclss jcClss[] = {
	{ JCO_CLSS_String,     jcStringPrint,  jcStringSExpr,  "string", "\""},
	{ JCO_CLSS_Character,  jcStringPrint,  jcStringSExpr, "char", "'"},
	{ JCO_CLSS_Integer,    jcIntegerPrint, jcIntegerSExpr, "integer"},
	{ JCO_CLSS_Float,      jcIntegerPrint, jcIntegerSExpr, "float"},
	{ JCO_CLSS_Double,     jcIntegerPrint, jcIntegerSExpr, "double"},
	{ JCO_CLSS_Keyword,    jcKeywordPrint, jcKeywordSExpr, "keyword"},
	{ JCO_CLSS_Id,         jcIdPrint,      jcIdSExpr,      "id"},

	{ JCO_CLSS_CommaSeq,   jcSequencePrint,jcNodeSExpr, "commaseq", ", "},
	{ JCO_CLSS_SpaceSeq,   jcSequencePrint,jcNodeSExpr, "spaceseq", " "},
	{ JCO_CLSS_NLSeq,      jcSequencePrint,jcNodeSExpr, "nlseq", "\n"},
	{ JCO_CLSS_Seq,        jcSequencePrint,jcNodeSExpr, "seq", ""},
	{ JCO_CLSS_Parens,     jcParenPrint,   jcNodeSExpr, "paren", "()", 15, JCO_NONE },
	{ JCO_CLSS_Braces,     jcParenPrint,   jcNodeSExpr, "braces", "{}", 15, JCO_NONE },
	{ JCO_CLSS_SqBrackets, jcParenPrint,   jcNodeSExpr, "sqbracket", "[]", 15, JCO_NONE },
	{ JCO_CLSS_ABrackets,  jcParenPrint,   jcNodeSExpr,  "angle", "<>" },
	{ JCO_CLSS_ImportedId, jcImportPrint,  jcImportSExpr,"importid", 0},
	{ JCO_CLSS_ImportedStatic,
	                       jcImportPrint,  jcImportSExpr,  "static-importid", 0},
	{ JCO_CLSS_Annotation, jcAnnotationPrint, jcNodeSExpr, "annotation", 0},
	{ JCO_CLSS_Class,      jcClassPrint,   jcNodeSExpr,    "class", 0},
	{ JCO_CLSS_JavaDoc,    jcJavaDocPrint, jcCommentSExpr, "javadoc", 0},
	{ JCO_CLSS_Comment,    jcCommentPrint, jcCommentSExpr, "comment", 0},
	{ JCO_CLSS_Method,     jcMethodPrint,  jcNodeSExpr,    "method", 0},
	{ JCO_CLSS_Declaration,jcDeclarationPrint, jcNodeSExpr,"declaration", 0},
	{ JCO_CLSS_Statement,  jcStatementPrint, jcNodeSExpr,  "statement", 0},
	{ JCO_CLSS_File,       jcFilePrint,      jcNodeSExpr,  "file", 0},

	{ JCO_CLSS_If,         jcBlockHdrPrint, jcNodeSExpr,  "if", "if"},
	{ JCO_CLSS_While,      jcBlockHdrPrint, jcNodeSExpr,  "while", "while"},
	{ JCO_CLSS_Switch,     jcBlockHdrPrint, jcNodeSExpr,  "switch", "switch"},
	{ JCO_CLSS_Case,       jcCasePrint,     jcNodeSExpr,  "case", "case"},
	{ JCO_CLSS_Block,      jcBlockPrint,    jcNodeSExpr,  "block"},
	{ JCO_CLSS_Try,        jcBlockKeywordPrint, jcNodeSExpr,  "try", "try"},
	{ JCO_CLSS_Catch,      jcBlockHdrPrint, jcNodeSExpr,  "catch", "catch"},
	{ JCO_CLSS_Finally,    jcBlockKeywordPrint, jcNodeSExpr,  "finally", "finally"},

	{ JCO_CLSS_ArrRef,     jcARefPrint,  jcNodeSExpr, "arrayref", 0, 20, JCO_NONE},
	{ JCO_CLSS_MemRef,     jcBinOpPrint, jcNodeSExpr, "memref", ".", 20, JCO_NONE},
	{ JCO_CLSS_Cast,       jcCastPrint, jcNodeSExpr, "cast",   " ", 16, JCO_NONE },

	{ JCO_CLSS_Apply,      jcApplyPrint,     jcNodeSExpr, "apply", 0, 20, JCO_NONE},
	{ JCO_CLSS_Construct,  jcConstructPrint, jcNodeSExpr, "new", 0, 20, JCO_NONE},

	{ JCO_CLSS_Not,     jcUnaryOpPrint,jcNodeSExpr, "not",    "!",    13,JCO_LR },
	{ JCO_CLSS_LogAnd,  jcBinOpPrint,  jcNodeSExpr, "and",    " && ", 4, JCO_LR },
	{ JCO_CLSS_LogOr,   jcBinOpPrint,  jcNodeSExpr, "or",     " || ", 4, JCO_LR },
	{ JCO_CLSS_And,     jcBinOpPrint,  jcNodeSExpr, "and",    " & ", 7, JCO_LR },
	{ JCO_CLSS_Or,      jcBinOpPrint,  jcNodeSExpr, "or",     " | ", 7, JCO_LR },
	{ JCO_CLSS_XOr,      jcBinOpPrint,  jcNodeSExpr, "xor",     " ^ ", 7, JCO_LR },
	{ JCO_CLSS_Equals,  jcBinOpPrint,  jcNodeSExpr, "equal",  " == ", 8, JCO_LR },
	{ JCO_CLSS_NEquals, jcBinOpPrint,  jcNodeSExpr, "nequal", " != ", 8, JCO_LR },
	{ JCO_CLSS_Assign,  jcBinOpPrint,  jcNodeSExpr, "assign", " = ",  1, JCO_RL },
	{ JCO_CLSS_Plus,    jcBinOpPrint,  jcNodeSExpr, "plus",   " + ",  11,JCO_LR },
	{ JCO_CLSS_Minus,   jcBinOpPrint,  jcNodeSExpr, "minus",  " - ",  11,JCO_LR },
	{ JCO_CLSS_Times,   jcBinOpPrint,  jcNodeSExpr, "times",  "*",    12,JCO_LR },
	{ JCO_CLSS_Divide,  jcBinOpPrint,  jcNodeSExpr, "divide", "/",    12,JCO_LR },
	{ JCO_CLSS_Modulo,  jcBinOpPrint,  jcNodeSExpr, "modulo", "%",    12,JCO_LR },
	{ JCO_CLSS_LT,      jcBinOpPrint,  jcNodeSExpr, "lt",     " < ",  9, JCO_LR },
	{ JCO_CLSS_LE,      jcBinOpPrint,  jcNodeSExpr, "le",     " <= ", 9, JCO_LR },
	{ JCO_CLSS_GT,      jcBinOpPrint,  jcNodeSExpr, "gt",     " > ",  9, JCO_LR },
	{ JCO_CLSS_GE,      jcBinOpPrint,  jcNodeSExpr, "ge",     " >= ", 9, JCO_LR },
	{ JCO_CLSS_Negate,  jcUnaryOpPrint,jcNodeSExpr, "negate", "-",    13,JCO_LR },
	{ JCO_CLSS_ShiftUp, jcBinOpPrint,  jcNodeSExpr, "shiftup", "<<",    10,JCO_LR },
	{ JCO_CLSS_ShiftDn, jcBinOpPrint,  jcNodeSExpr, "shiftdn", ">>",    10,JCO_LR },

	{ JCO_CLSS_Conditional,jcCondPrint,jcNodeSExpr, "cond",   0,      2, JCO_RL },
};

void
jcInit()
{
	int i;
	for (i=0; i<JK_END; i++) {
		if (jkKeywords[i].id != i)
			bug("Java is a mess");
	}
}



local JavaCodeClass jc0ClassObj(JcClassId);

JavaCode
jcClass(int modifiers, String comment,
	JavaCodeList annotations,
	JavaCode id, JavaCode superclass,
	JavaCodeList extendList, JavaCodeList body)
{
	JavaCodeList jcmods = jc0CreateModifiers(modifiers);

	JavaCode clss = jcoNew(jc0ClassObj(JCO_CLSS_Class),
			       6,
			       jcNLSeq(annotations),
			       jcSpaceSeq(jcmods),
			       id, superclass,
			       extendList == listNil(JavaCode) ? NULL : jcCommaSeq(extendList),
			       jcNLSeq(body));
	if (comment == NULL)
		return clss;

	return jcDocumented(comment, clss);
}

void
jcClassPrint(JavaCodePContext ctxt, JavaCode clss)
{
	JavaCode annotations = jcoArgv(clss)[0];
	JavaCode modifiers  = jcoArgv(clss)[1];
	JavaCode id         = jcoArgv(clss)[2];
	JavaCode superclass = jcoArgv(clss)[3];
	JavaCode implList   = jcoArgv(clss)[4];
	JavaCode body       = jcoArgv(clss)[5];

	jcoWrite(ctxt, annotations);
	jcoPContextWrite(ctxt, "\n");
	if (modifiers != NULL && jcoArgc(modifiers) > 0) {
		jcoWrite(ctxt, modifiers);
		jcoPContextWrite(ctxt, " ");
	}
	jcoPContextWrite(ctxt, "class ");
	jcoWrite(ctxt, id);
	if (superclass != NULL) {
		jcoPContextWrite(ctxt, " extends ");
		jcoWrite(ctxt, superclass);
	}
	if (implList != NULL) {
		jcoPContextWrite(ctxt, " implements ");
		jcoWrite(ctxt, implList);
	}
	jcoPContextWrite(ctxt, " {");
	jcoPContextNewlineIndent(ctxt);
	jcoWrite(ctxt, body);
	jcoPContextNewlineUnindent(ctxt);
	jcoPContextWrite(ctxt, "}");
}

/*
 * :: Methods (actually, could be 'member' instead)
 */
JavaCode
jcMethod(int modifiers, String comment,
			 JavaCode retnType,
			 JavaCode id, JavaCodeList genArgs,
			 JavaCodeList args,
			 JavaCodeList exns, JavaCode body)
{
	JavaCode meth = jcoNew(jc0ClassObj(JCO_CLSS_Method),
			       2,
			       jcDeclaration(modifiers, retnType,
					     id, listNil(JavaCode),
					     jcParens(jcCommaSeq(args)), exns),
			       body);
	return meth;
}

JavaCode
jcConstructor(int modifiers, String comment,
	      JavaCode id, JavaCodeList genArgs,
	      JavaCodeList args,
	      JavaCodeList exns, JavaCode body)
{
	JavaCode meth = jcoNew(jc0ClassObj(JCO_CLSS_Method),
			       2,
			       jcDeclaration(modifiers, jcSpaceSeqV(0),
					     id, listNil(JavaCode),
					     jcParens(jcCommaSeq(args)), exns),
			       body);
	return meth;
}

local void
jcMethodPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCode decl = jcoArgv(code)[0];
	JavaCode body = jcoArgv(code)[1];

	jcoWrite(ctxt, decl);
	jcoPContextWrite(ctxt, " {");
	jcoPContextNewlineIndent(ctxt);
	jcoWrite(ctxt, body);
	jcoPContextNewlineUnindent(ctxt);
	jcoPContextWrite(ctxt, "}");
	jcoPContextNewline(ctxt);
}


/*
 * :: Declarations
 */

JavaCode
jcDeclaration(int modifiers,
	      JavaCode retnType,
	      JavaCode id, JavaCodeList genArgs,
	      JavaCode args,
	      JavaCodeList exns)
{
	JavaCodeList l      = listNil(JavaCode);
	JavaCodeList jcmods = jc0CreateModifiers(modifiers);

	l = listCons(JavaCode)(jcSpaceSeq(jcmods), l);
	l = listCons(JavaCode)(retnType, l);
	l = listCons(JavaCode)(id, l);
	if (args != NULL) {
		l = listCons(JavaCode)(args, l);
		l = listCons(JavaCode)(jcCommaSeq(exns), l);
	}
	l = listNReverse(JavaCode)(l);
	return jcoNewFrList(jc0ClassObj(JCO_CLSS_Declaration), l);
}

JavaCode
jcMemberDecl(int modifiers, JavaCode type, JavaCode id)
{
	return jcDeclaration(modifiers, type, id, 0, 0, 0);
}

JavaCode
jcParamDecl(int modifiers, JavaCode type, JavaCode id)
{
	return jcDeclaration(modifiers, type, id, 0, 0, 0);
}

JavaCode
jcLocalDecl(int modifiers, JavaCode type, JavaCode id)
{
	return jcDeclaration(modifiers, type, id, 0, 0, 0);
}

JavaCode
jcInitialisation(int modifiers, JavaCode type, JavaCode id, JavaCode value)
{
	return jcParamDecl(modifiers, type, jcAssign(id, value));
}


local void
jcDeclarationPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCode mods = jcoArgv(code)[0];
	JavaCode retn = jcoArgv(code)[1];
	JavaCode name = jcoArgv(code)[2];

	if (!jcoIsEmpty(mods)) {
		jcoWrite(ctxt, mods);
		jcoPContextWrite(ctxt, " ");
	}
	if (!jcoIsEmpty(retn)) {
		jcoWrite(ctxt, retn);
		jcoPContextWrite(ctxt, " ");
	}
	jcoWrite(ctxt, name);
	if (jcoArgc(code) > 3) {
		JavaCode args = jcoArgv(code)[3];
		JavaCode exns = jcoArgv(code)[4];
		jcoWrite(ctxt, args);
		if (jcoArgc(exns) > 0) {
			jcoPContextWrite(ctxt, " throws ");
			jcoWrite(ctxt, exns);
		}

	}

}

/*
 * :: Annotations
 */

JavaCode
jcAnnotation(JavaCode annotationClass, JavaCodeList arguments)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Annotation),
		      2, annotationClass,
		      jcParens(jcCommaSeq(arguments)));
}

local void
jcAnnotationPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, "@");
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoWrite(ctxt, jcoArgv(code)[1]);
}

/*
 * :: Function application
 */

JavaCode
jcApply(JavaCode c, JavaCodeList args)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Apply), 2, c, jcParens(jcCommaSeq(args)));
}

JavaCode
jcApplyV(JavaCode c, int n, ...)
{
	va_list  argp;
	JavaCode jc;
	va_start(argp, n);
	jc = jcApplyP(c, n, argp);
	va_end(argp);
	return jc;
}

JavaCode
jcApplyP(JavaCode c, int n, va_list argp)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Apply),
		      2, c, jcParens(jcCommaSeqP(n, argp)));
}

JavaCode
jcApplyMethod(JavaCode c, JavaCode id, JavaCodeList args)
{
	return jcApply(jcMemRef(c, id), args);
}

JavaCode
jcApplyMethodV(JavaCode c, JavaCode id, int n, ...)
{
	va_list  argp;
	JavaCode jc;

	va_start(argp, n);

	jc =  jcApplyP(jcMemRef(c, id), n, argp);
	va_end(argp);
	return jc;
}

local void
jcApplyPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoWrite(ctxt, jcoArgv(code)[1]);
}

JavaCode
jcGenericMethodName(JavaCode methodName, JavaCodeList genArgs)
{
	return jcSeqV(2, jcABrackets(jcCommaSeq(genArgs)));
}

JavaCode
jcGenericMethodNameV(JavaCode methodName, int n, ...)
{
	JavaCode jc;
	va_list argp;
	va_start(argp, n);
	jc = jcSeqV(2, jcABrackets(jcCommaSeqP(n, argp)), methodName);
	va_end(argp);
	return jc;
}


/*
 * :: Parens
 */
JavaCode
jcParens(JavaCode args)
{
	JavaCode jco = jcoNew(jc0ClassObj(JCO_CLSS_Parens), 1, args);
	return jco;
}

JavaCode
jcBraces(JavaCode args)
{
	JavaCode jco = jcoNew(jc0ClassObj(JCO_CLSS_Braces), 1, args);
	return jco;
}

JavaCode
jcSqBrackets(JavaCode args)
{
	JavaCode jco = jcoNew(jc0ClassObj(JCO_CLSS_SqBrackets), 1, args);
	return jco;
}

JavaCode
jcABrackets(JavaCode args)
{
	JavaCode jco = jcoNew(jc0ClassObj(JCO_CLSS_ABrackets), 1, args);
	return jco;
}

local void
jcParenPrint(JavaCodePContext ctxt, JavaCode code)
{
	char s[2] = " ";
	String txt = jcoClass(code)->txt;
	s[0]=txt[0];
	jcoPContextWrite(ctxt, s);
	jcoWrite(ctxt, jcoArgv(code)[0]);
	s[0]=txt[1];
	jcoPContextWrite(ctxt, s);
}


/*
 * :: Comments
 */
JavaCode
jcDocumented(String comment, JavaCode code)
{
	JavaCode doc = jcoNewLiteral(jc0ClassObj(JCO_CLSS_JavaDoc), comment);
	return jcNLSeqV(2, doc, code);
}

JavaCode
jcCommented(String comment, JavaCode code)
{
	return jcSpaceSeqV(2, jcComment(comment), code);
}

JavaCode
jcComment(String comment)
{
	JavaCode jc = jcoNewLiteral(jc0ClassObj(JCO_CLSS_Comment), comment);
	return jc;
}

local void
jcJavaDocPrint(JavaCodePContext ctxt, JavaCode code)
{
	String s = strReplace(jcoLiteral(code), "\n", "\n * ");
	jcoPContextWrite(ctxt, "/**\n * ");
	jcoPContextWrite(ctxt, s);
	jcoPContextWrite(ctxt, "\n */");
	strFree(s);
}


local void
jcCommentPrint(JavaCodePContext ctxt, JavaCode code)
{
	String s = strReplace(jcoLiteral(code), "\n", "\n *");
	jcoPContextWrite(ctxt, "/* ");
	jcoPContextWrite(ctxt, s);
	jcoPContextWrite(ctxt, "*/");
	strFree(s);
}

local SExpr
jcCommentSExpr(JavaCode code)
{
	SExpr  h = sxiFrSymbol(symIntern(jcoClass(code)->name));
	String s = jc0EscapeString(jcoLiteral(code), false);
	SExpr sx = sxiFrString(s);
	strFree(s);
	return sxiList(2, h, sx);
}

/*
 * :: Imports
 */

JavaCode
jcImportedIdFrString(String str)
{
	String p = strLastIndexOf(str, '.');
	if (p == NULL) {
		return jcId(strCopy(str));
	}
	else {
		String pkg = strnCopy(str, p - str);
		String id = strCopy(p+1);
		return jcImportedId(pkg, id);
	}
}

JavaCode
jcImportedId(String pkg, String name)
{
	return jcoNewImport(jc0ClassObj(JCO_CLSS_ImportedId), pkg, listNil(String), name, false);
}


String
jcImportedIdName(JavaCode id)
{
	return jcoImportId(id);
}

String
jcImportedIdPkg(JavaCode id)
{
	return jcoImportPkg(id);
}


JavaCode
jcImportedStaticId(String pkg, String clss, String name)
{
	assert(strLastIndexOf(clss, '.') == NULL);
	assert(strLastIndexOf(name, '.') == NULL);

	return jcoNewImport(jc0ClassObj(JCO_CLSS_ImportedStatic), pkg,
			    listSingleton(String)(clss), name, false);
}

JavaCode
jcImportedStaticIdFrString(String str)
{
	String p = strLastIndexOf(str, '.');
	String id = strCopy(p+1);
	String pkgClss = strnCopy(str, p - str);
	String dclss   = strLastIndexOf(pkgClss, '.');
	String clss    = strCopy(dclss+1);
	String pkg     = strnCopy(pkgClss, dclss - pkgClss);

	return jcImportedStaticId(pkg, clss, id);
}

String
jcImportedStaticIdClass(JavaCode importedId)
{
	return car(jcoImportPath(importedId));
}

String
jcImportedStaticIdPkg(JavaCode importedId)
{
	return jcoImportPkg(importedId);
}

String
jcImportedStaticIdName(JavaCode importedId)
{
	return jcImportedIdName(importedId);
}

local void
jcImportPrint(JavaCodePContext ctxt, JavaCode code)
{
	if (jcoImportIsImported(code))
		jcoPContextWrite(ctxt, jcoImportId(code));
	else {
		if (strlen(jcoImportPkg(code)) != 0) {
			jcoPContextWrite(ctxt, jcoImportPkg(code));
			jcoPContextWrite(ctxt, ".");
		}
		jcoPContextWrite(ctxt, jcoImportId(code));
	}
}

local SExpr
jcImportSExpr(JavaCode code)
{
	SExpr sym = sxiFrSymbol(symIntern(jcoClass(code)->name));
	if (jcoImportPkg(code) == NULL) {
		return sxiList(2, sym, sxiFrString(jcoImportId(code)));
	}
	return sxiList(3, sym,
		       sxiFrString(jcoImportPkg(code)),
		       sxiFrString(jcoImportId(code)));
}


/*
 * :: String literals
 */


JavaCode
jcLiteralString(String s)
{
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_String),
			     jc0EscapeString(s, false));
}

JavaCode
jcLiteralStringWithTerminalChar(String s)
{
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_String),
			     jc0EscapeString(s, true));
}

JavaCode
jcLiteralChar(String s)
{
	String t;
	if (s[0] == '\0')
		t = strCopy("\\0");
	else if (s[0] == '\'')
		t = strCopy("\\'");
	else if (s[0] == '"')
		t = strCopy("\\\"");
	else if (s[0] == '\n')
		t = strCopy("\\n");
	else if (s[0] == '\t')
		t = strCopy("\\t");
	else if (s[0] == '\\')
		t = strCopy("\\\\");
	else if (s[0] == -1)
		t = strCopy("\\1");
	else
		t = strCopy(s);

	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_Character), t);
}

local void
jcStringPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss = jcoClass(code);
	jcoPContextWrite(ctxt, thisClss->txt);
	jcoPContextWrite(ctxt, jcoLiteral(code));
	jcoPContextWrite(ctxt, thisClss->txt);
}

local SExpr
jcStringSExpr(JavaCode code)
{
	String s  = jcoLiteral(code);
	SExpr  sx;
	s = jc0EscapeString(s, false);
	sx = sxiFrString(s);
	strFree(s);
	return sx;
}

/*
 * :: Numeric literals
 */


JavaCode
jcLiteralInteger(AInt i)
{
	String s = strPrintf("%d", i);
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_Integer), s);
}

JavaCode
jcLiteralIntegerFrString(String s)
{
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_Integer), s);
}

JavaCode
jcLiteralFloatFrString(String s)
{
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_Float), s);
}

void
jcIntegerPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, jcoLiteral(code));
}

local SExpr
jcIntegerSExpr(JavaCode code)
{
	int i = atoi(jcoLiteral(code));
	return sxiFrInteger(i);
}

/*
 * :: Keywords
 */


JavaCode
jcKeyword(Symbol sym)
{
	return jcoNewToken(jc0ClassObj(JCO_CLSS_Keyword), sym);
}

JavaCode
jcReturn(JavaCode c)
{
	return jcSpaceSeqV(2, jcKeyword(symInternConst("return")), c);
}

JavaCode
jcReturnVoid()
{
	return jcKeyword(symInternConst("return"));
}


JavaCode
jcNull()
{
	return jcKeyword(symInternConst("null"));
}

JavaCode
jcTrue(String name)
{
	return jcKeyword(symInternConst("true"));
}
JavaCode
jcFalse(String name)
{
	return jcKeyword(symInternConst("false"));
}

JavaCode
jcThis(String name)
{
	return jcKeyword(symInternConst("this"));
}

local SExpr
jcKeywordSExpr(JavaCode code)
{
	return sxiFrSymbol(jcoToken(code));
}

local void
jcKeywordPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, symString(jcoToken(code)));
}

/*
 * :: Ids
 */

JavaCode
jcId(String name)
{
	return jcoNewLiteral(jc0ClassObj(JCO_CLSS_Id), name);
}

String
jcIdName(JavaCode id)
{
	return jcoLiteral(id);
}

local SExpr
jcIdSExpr(JavaCode code)
{
	return sxiFrString(jcoLiteral(code));
}

void
jcIdPrint(JavaCodePContext ctxt, JavaCode code)
{
	String name = jcoLiteral(code);
	jcoPContextWrite(ctxt, name);
}


/*
 * :: Generic id
 */
JavaCode
jcGenericId(JavaCode root, JavaCodeList genArgs)
{
	return jcSeqV(2, root, jcABrackets(jcCommaSeq(genArgs)));
}


/*
 * :: Constructor Call
 */
JavaCode
jcConstructBase(JavaCode t, JavaCode body)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Construct), 2, t, body);
}

JavaCode
jcConstruct(JavaCode t, JavaCodeList args)
{
	return jcConstructBase(jcApply(t, args), 0);
}

JavaCode
jcConstructSubclass(JavaCode t, JavaCodeList args, JavaCode body)
{
	return jcConstructBase(jcApply(t, args), body);
}

JavaCode
jcConstructV(JavaCode t, int n, ...)
{
	JavaCode jc;
	va_list  argp;

	va_start(argp, n);
	jc = jcConstructBase(jcApplyP(t, n, argp), 0);
	va_end(argp);
	return jc;
}

local void
jcConstructPrint(JavaCodePContext ctxt, JavaCode t)
{
	jcoPContextWrite(ctxt, "new ");
	jcoWrite(ctxt, jcoArgv(t)[0]);
	if (jcoArgv(t)[1] != 0) {
		jcoPContextWrite(ctxt, " { ");
		jcoPContextNewlineIndent(ctxt);
		jcoWrite(ctxt, jcoArgv(t)[1]);
		jcoPContextNewlineUnindent(ctxt);
		jcoPContextWrite(ctxt, "}");
	}
}

/*
 * :: Arrays
 */

JavaCode
jcArrayOf(JavaCode type)
{
	return jcSpaceSeqV(2, type, jcSqBrackets(jcSpaceSeqV(0)));
}

JavaCode
jcNAry(JavaCode type)
{
	return jcSpaceSeqV(2, type,
			   jcKeyword(symInternConst("...")));
}

JavaCode
jcArrayNew(JavaCode t, JavaCode sz)
{
	return jcConstructBase(jcArrayRef(t, sz), 0);
}

JavaCode
jcArrayRef(JavaCode arr, JavaCode idx)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_ArrRef), 2, arr, idx);
}

void jcARefPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss = jcoClass(code);

	jc0PrintWithParens(ctxt, thisClss, jcoArgv(code)[0]);
	jcoPContextWrite(ctxt, "[");
	jcoWrite(ctxt, jcoArgv(code)[1]);
	jcoPContextWrite(ctxt, "]");
}

/*
 * :: Binary operations
 */

JavaCode
jcAssign(JavaCode lhs, JavaCode rhs)
{
	return jcBinaryOp(jc0ClassObj(JCO_CLSS_Assign), lhs, rhs);
}

JavaCode
jcCast(JavaCode lhs, JavaCode rhs)
{
	return jcBinaryOp(jc0ClassObj(JCO_CLSS_Cast), lhs, rhs);
}

JavaCode
jcMemRef(JavaCode lhs, JavaCode rhs)
{
	return jcBinaryOp(jc0ClassObj(JCO_CLSS_MemRef), lhs, rhs);
}



/*
 * :: Operations
 */
typedef JavaCode (*JcOpBuilder)(JavaCodeList l);
struct jcOpInfo {
	JcOperation op;
	JcOpBuilder builder;
	JcClassId   clsId;
};
typedef struct jcOpInfo *JcOpInfo;

local JavaCode jcOpNot(JavaCodeList l);
local JavaCode jcOpNegate(JavaCodeList l);
local JavaCode jcOpTimesPlus(JavaCodeList args);

local JcOpInfo jc0OpInfo(JcOperation op);


struct jcOpInfo JcOpInfoTable[] = {
	{ JCO_OP_Not,     jcOpNot},
	{ JCO_OP_LogAnd,     0, JCO_CLSS_LogAnd},
	{ JCO_OP_LogOr,      0, JCO_CLSS_LogOr},
	{ JCO_OP_And,     0, JCO_CLSS_And},
	{ JCO_OP_Or,      0, JCO_CLSS_Or},
	{ JCO_OP_XOr,      0, JCO_CLSS_XOr},
	{ JCO_OP_Equals,  0, JCO_CLSS_Equals},
	{ JCO_OP_NEquals, 0, JCO_CLSS_NEquals},
	{ JCO_OP_Assign,  0, JCO_CLSS_Assign},
	{ JCO_OP_Plus,    0, JCO_CLSS_Plus},
	{ JCO_OP_Minus,   0, JCO_CLSS_Minus},
	{ JCO_OP_Times,   0, JCO_CLSS_Times},
	{ JCO_OP_Divide,  0, JCO_CLSS_Divide},
	{ JCO_OP_Modulo,  0, JCO_CLSS_Modulo},
	{ JCO_OP_LT,      0, JCO_CLSS_LT},
	{ JCO_OP_LE,      0, JCO_CLSS_LE},
	{ JCO_OP_GT,      0, JCO_CLSS_GT},
	{ JCO_OP_GE,      0, JCO_CLSS_GE},
	{ JCO_OP_Negate,    jcOpNegate},
	{ JCO_OP_TimesPlus, jcOpTimesPlus},
	{ JCO_OP_ShiftUp,   0, JCO_CLSS_ShiftUp},
	{ JCO_OP_ShiftDn,   0, JCO_CLSS_ShiftDn},
};

JavaCode
jcOp(JcOperation op, JavaCodeList args)
{
	JcOpInfo inf = jc0OpInfo(op);
	if (inf->builder == 0)
		return jcBinaryOp(jc0ClassObj(inf->clsId), car(args), car(cdr(args)));
	else
		return inf->builder(args);
}

JavaCode
jcBinOp(JcOperation op, JavaCode e1, JavaCode e2)
{
	JcOpInfo inf = jc0OpInfo(op);

	if (inf->builder == 0)
		return jcBinaryOp(jc0ClassObj(inf->clsId), e1, e2);
	else
		return inf->builder(listList(JavaCode)(2, e1, e2));
}


local JavaCode
jcOpNot(JavaCodeList l)
{
	return jcNot(car(l));
}

local JavaCode
jcOpNegate(JavaCodeList l)
{
	return jcNegate(car(l));
}

local JavaCode
jcOpTimesPlus(JavaCodeList args)
{
	JavaCode a1 = car(args);
	JavaCode a2 = car(cdr(args));
	JavaCode a3 = car(cdr(cdr(args)));

	return jcBinaryOp(jc0ClassObj(JCO_CLSS_Plus),
			  jcBinaryOp(jc0ClassObj(JCO_CLSS_Times), a1, a2),
			  a3);
}


local JcOpInfo
jc0OpInfo(JcOperation op)
{
	JcOpInfo inf = &JcOpInfoTable[op];

	assert(inf->op == op);
	return inf;
}

/*
 * :: Binary operations
 */

JavaCode
jcBinaryOp(JavaCodeClass c, JavaCode lhs, JavaCode rhs)
{
	JavaCode r = jcoNew(c, 2, lhs, rhs);
	return r;
}

local void
jcBinOpPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss = jcoClass(code);
	JavaCode lhs = jcoArgv(code)[0];
	JavaCode rhs = jcoArgv(code)[1];

	jc0PrintWithParens(ctxt, thisClss, lhs);
	jcoPContextWrite(ctxt, thisClss->txt);
	jc0PrintWithParens(ctxt, thisClss, rhs);
}

local void
jc0PrintWithParens(JavaCodePContext ctxt, JavaCodeClass oClss, JavaCode arg)
{
	JavaCodeClass aClss = jcoClass(arg);
	if (jc0NeedsParens(oClss, aClss)) {
		jcoPContextWrite(ctxt, "(");
		jcoWrite(ctxt, arg);
		jcoPContextWrite(ctxt, ")");
	}
	else {
		jcoWrite(ctxt, arg);
	}
}

local Bool
jc0NeedsParens(JavaCodeClass c1, JavaCodeClass c2)
{
	if (c2->prec == 0)
		return false;
	return c1->prec > c2->prec;
}

/*
 * :: Unary operations
 */

JavaCode
jcNot(JavaCode arg)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Not), 1, arg);
}

JavaCode
jcNegate(JavaCode arg)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Negate), 1, arg);
}


local void
jcUnaryOpPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss, aClss;
	JavaCode arg = jcoArgv(code)[0];
	thisClss = jcoClass(code);
	aClss    = jcoClass(arg);

	jcoPContextWrite(ctxt, thisClss->txt);
	jc0PrintWithParens(ctxt, thisClss, arg);

}

local void
jcCastPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss, aClss;
	JavaCode arg1 = jcoArgv(code)[0];
	JavaCode arg2 = jcoArgv(code)[1];

	thisClss = jcoClass(code);
	aClss    = jcoClass(code);

	jcoPContextWrite(ctxt, "(");
	jcoWrite(ctxt, arg1);
	jcoPContextWrite(ctxt, ")");

	jc0PrintWithParens(ctxt, thisClss, arg2);
}

/*
 * :: Ternary operators
 * Well, there's only ?:.
 */

JavaCode
jcConditional(JavaCode test, JavaCode truePart, JavaCode falsePart)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Conditional), 3, test, truePart, falsePart);
}

local void
jcCondPrint(JavaCodePContext ctxt, JavaCode code)
{
	JavaCodeClass thisClss;
	JavaCode arg1 = jcoArgv(code)[0];
	JavaCode arg2 = jcoArgv(code)[1];
	JavaCode arg3 = jcoArgv(code)[2];

	thisClss = jcoClass(code);
	jc0PrintWithParens(ctxt, thisClss, arg1);
	jcoPContextWrite(ctxt, " ? ");
	jc0PrintWithParens(ctxt, thisClss, arg2);
	jcoPContextWrite(ctxt, " : ");
	jc0PrintWithParens(ctxt, thisClss, arg3);
}

/*
 * :: Statements
 */
JavaCode
jcStatement(JavaCode stmt)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Statement), 1, stmt);
}

local void
jcStatementPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoPContextWrite(ctxt, ";");
}

/*
 * :: Sequences
 */

JavaCode
jcCommaSeq(JavaCodeList lst)
{
	return jcoNewFrList(jc0ClassObj(JCO_CLSS_CommaSeq), lst);
}

JavaCode
jcCommaSeqP(int n, va_list argp)
{
	return jcoNewP(jc0ClassObj(JCO_CLSS_CommaSeq), n, argp);
}

JavaCode
jcSeq(JavaCodeList lst)
{
	return jcoNewFrList(jc0ClassObj(JCO_CLSS_Seq), lst);
}

JavaCode
jcSeqV(int n, ...)
{
	va_list argp;
	JavaCode jc;
	va_start(argp, n);
	jc = jcoNewP(jc0ClassObj(JCO_CLSS_Seq), n, argp);
	va_end(argp);
	return jc;
}

JavaCode
jcNLSeq(JavaCodeList lst)
{
	return jcoNewFrList(jc0ClassObj(JCO_CLSS_NLSeq), lst);
}

JavaCode
jcSpaceSeq(JavaCodeList lst)
{
	return jcoNewFrList(jc0ClassObj(JCO_CLSS_SpaceSeq), lst);
}

JavaCode
jcSpaceSeqV(int n, ...)
{
	va_list argp;
	JavaCode jc;
	va_start(argp, n);
	jc = jcoNewP(jc0ClassObj(JCO_CLSS_SpaceSeq), n, argp);
	va_end(argp);
	return jc;
}

JavaCode
jcNLSeqV(int n, ...)
{
	va_list argp;
	JavaCode jc;
	va_start(argp, n);
	jc = jcoNewP(jc0ClassObj(JCO_CLSS_NLSeq), n, argp);
	va_end(argp);
	return jc;
}

local void
jcSequencePrint(JavaCodePContext ctxt, JavaCode code)
{
	char *theSep = jcoClass(code)->txt;
	char *sep = 0;
	int i=0;
	for (i=0; i<jcoArgc(code); i++) {
		if (sep != 0)
			jcoPContextWrite(ctxt, sep);
		jcoWrite(ctxt, jcoArgv(code)[i]);
		sep = theSep;
	}
}

JavaCode
jcBlockNoNL(JavaCode body)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Braces), 1, body);
}

JavaCode
jcBlock(JavaCode body)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Block), 1, body);
}

local void
jcBlockPrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, "{");
	jcoPContextNewlineIndent(ctxt);
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoPContextNewlineUnindent(ctxt);
	jcoPContextWrite(ctxt, "}");

}

JavaCode
jcBreak(JavaCode label)
{
	if (label == 0)
		return jcKeyword(symInternConst("break"));
	else
		return jcSpaceSeqV(2, jcKeyword(symInternConst("break")), label);
}

JavaCode
jcContinue(JavaCode label)
{
	if (label == 0)
		return jcKeyword(symInternConst("continue"));
	else
		return jcSpaceSeqV(2, jcKeyword(symInternConst("continue")), label);
}

JavaCode
jcCaseLabel(JavaCode label)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Case), 1, label);
}

local void
jcCasePrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, "case ");
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoPContextWrite(ctxt, ": ");
}

JavaCode
jcTryCatch(JavaCode body, JavaCode catch, JavaCode finally)
{
	return jcTry(body, listSingleton(JavaCode)(catch), finally);
}

JavaCode
jcTry(JavaCode body, JavaCodeList catches, JavaCode finally)
{
	JavaCodeList lst = listNil(JavaCode);
	lst = listCons(JavaCode)(jcoNew(jc0ClassObj(JCO_CLSS_Try), 1, body), lst);
	lst = listNConcat(JavaCode)(lst, catches);
	if (finally != NULL) {
		lst = listNConcat(JavaCode)(lst,
					    listSingleton(JavaCode)(jcoNew(jc0ClassObj(JCO_CLSS_Finally),
									   1, finally)));
	}
	return jcNLSeq(lst);
}

JavaCode
jcCatch(JavaCode decl, JavaCode body)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_Catch), 2, decl, body);
}

/*
 * :: Import, Package
 */

JavaCode
jcImport(JavaCode arg)
{
	return jcSpaceSeqV(2, jcKeyword(symInternConst("import")), arg);
}

JavaCode
jcPackage(JavaCode arg)
{
	return jcSpaceSeqV(2, jcKeyword(symInternConst("package")), arg);
}

/*
 * :: Throw, catch
 */

JavaCode
jcThrow(JavaCode arg)
{
	return jcSpaceSeqV(2, jcKeyword(symInternConst("throw")), arg);
}

/*
 * :: If, Switch, While
 */

JavaCode
jcIf(JavaCode test, JavaCode stmt)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_If), 2, test, stmt);
}

JavaCode
jcSwitch(JavaCode test, JavaCodeList bodyList)
{
	JavaCode block = jcBraces(jcNLSeq(bodyList));
	return jcoNew(jc0ClassObj(JCO_CLSS_Switch), 2, test, block);
}

JavaCode
jcWhile(JavaCode test, JavaCode stmt)
{
	return jcoNew(jc0ClassObj(JCO_CLSS_While), 2, test, stmt);
}

local void
jcBlockHdrPrint(JavaCodePContext ctxt, JavaCode code)
{
	Bool needsIndent;
	char *key = (char *) jcoClass(code)->txt;
	jcoPContextWrite(ctxt, key);
	jcoPContextWrite(ctxt, " (");
	jcoWrite(ctxt, jcoArgv(code)[0]);
	jcoPContextWrite(ctxt, ") ");

	needsIndent = jcBlockHdrIndent(jcoArgv(code)[1]);
	if (needsIndent)
		jcoPContextNewlineIndent(ctxt);
	jcoWrite(ctxt, jcoArgv(code)[1]);
	if (needsIndent)
		jcoPContextNewlineUnindent(ctxt);

}

local void
jcBlockKeywordPrint(JavaCodePContext ctxt, JavaCode code)
{
	Bool needsIndent;
	char *key = (char *) jcoClass(code)->txt;
	jcoPContextWrite(ctxt, key);
	jcoPContextWrite(ctxt, " ");

	needsIndent = jcBlockHdrIndent(jcoArgv(code)[0]);
	if (needsIndent)
		jcoPContextNewlineIndent(ctxt);
	jcoWrite(ctxt, jcoArgv(code)[0]);
	if (needsIndent)
		jcoPContextNewlineUnindent(ctxt);

}

local Bool
jcBlockHdrIndent(JavaCode code)
{
	return jcoClass(code)->id != JCO_CLSS_Braces
		&& jcoClass(code)->id != JCO_CLSS_Block;
}

/*
 * :: File
 */

JavaCode
jcFile(JavaCode pkg, JavaCode name, JavaCodeList imports, JavaCode body)
{
	JavaCodeList whole;
	JavaCode file;

	whole = listNil(JavaCode);
	if (pkg != NULL) {
		whole = listSingleton(JavaCode)(jcStatement(jcPackage(jcoCopy(pkg))));
	}
	whole = listNConcat(JavaCode)(whole, imports);
	whole = listNConcat(JavaCode)(whole, listSingleton(JavaCode)(body));

	file = jcoNew(jc0ClassObj(JCO_CLSS_File),
		      3, name, jcoCopy(pkg), jcNLSeq(whole));

	jcoFree(pkg);

	return file;
}

void
jcFilePrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoWrite(ctxt, jcoArgv(code)[2]);
}

String
jcFileClassName(JavaCode file)
{
	return jcIdName(jcoArgv(file)[0]);
}

String
jcFilePackageName(JavaCode file)
{
	if (jcoArgv(file)[1] == NULL) {
		return "";
	}
	else {
		return jcIdName(jcoArgv(file)[1]);
	}
}

/*
 * :: Generic operations
 */
SExpr
jcNodeSExpr(JavaCode code)
{
	Symbol sym = symIntern(jcoClass(code)->name);
	SExpr whole = sxiList(1, sxiFrSymbol(sym));
	int i=0;

	for (i=0; i<jcoArgc(code); i++) {
		JavaCode jc = jcoArgv(code)[i];
		SExpr sexpr = jc == NULL ?  sxNil : jcoSExpr(jc);
		whole = sxCons(sexpr, whole);
	}
	return sxNReverse(whole);
}

extern void
jcNodePrint(JavaCodePContext ctxt, JavaCode code)
{
	jcoPContextWrite(ctxt, "<<node>>");
}


void
jcListPrint(JavaCodePContext ctxt, JavaCode code)
{
	char *theSep = (char *) jcoClass(code)->txt;
	char *sep = "";
	int i;
	for (i=0; i<jcoArgc(code); i++) {
		jcoPContextWrite(ctxt, sep);
		jcoWrite(ctxt, jcoArgv(code)[i]);
		sep = theSep;
	}
}


/*
 * :: Utils
 */
local Symbol jc0ModifierSymbol(int idx);

local JavaCodeClass
jc0ClassObj(JcClassId id)
{
	JavaCodeClass clss = &jcClss[id];
	assert(clss->id == id);
	return clss;
}

struct jcModifierInfo {
	int mask;
	String txt;
	Symbol sym;
};


static struct jcModifierInfo jcModifierList[] = {
	{ JCO_MOD_Public,    "public"},
	{ JCO_MOD_Private,   "private"},
	{ JCO_MOD_Protected, "protected"},
	{ JCO_MOD_Static,    "static"},
	{ JCO_MOD_Final,     "final"},
	{ JCO_MOD_Transient, "transient"},
	{ JCO_MOD_Volatile,  "volatile"},
};

local JavaCodeList
jc0CreateModifiers(int modifiers)
{
	JavaCodeList l = listNil(JavaCode);
	int i=0, m;
	for (m=1; m< JCO_MOD_MAX; m=m<<1) {
		if (modifiers & m)
			l = listCons(JavaCode)(jcoNewToken(jc0ClassObj(JCO_CLSS_Keyword),
							   jc0ModifierSymbol(i)), l);
		i++;
	}
	return listNReverse(JavaCode)(l);
}

local Symbol
jc0ModifierSymbol(int idx)
{
	struct jcModifierInfo *inf = &jcModifierList[idx];
	if (inf->sym == NULL)
		inf->sym = symInternConst(inf->txt);
	return inf->sym;
}


local Bool jc0ImportEq(JavaCode c1, JavaCode c2);
local void jc0CollectImports(Table tbl, Table nameTbl, JavaCode code);

JavaCodeList
jcCollectImports(JavaCode code)
{
	Table tbl = tblNew((TblHashFun) jcoHash, (TblEqFun) jc0ImportEq);
	Table nameTbl = tblNew((TblHashFun) strHash, (TblEqFun) strEqual);
	TableIterator it;
	JavaCodeList resList = listNil(JavaCode);

	jc0CollectImports(tbl, nameTbl, code);

	for (tblITER(it, tbl); tblMORE(it); tblSTEP(it)) {
		JavaCode id = (JavaCode) tblKEY(it);
		JavaCodeList codes = (JavaCodeList) tblELT(it);
		JavaCodeList tmp;
		JavaCode copy = jcImportedId(jcoImportPkg(id), jcoImportId(id));
		JavaCodeList usages = (JavaCodeList) tblElt(nameTbl, jcoImportId(id), listNil(JavaCode));
		if (cdr(usages) != listNil(JavaCode)) {
			continue;
		}
		else {
			resList = listCons(JavaCode)(copy, resList);
			tmp = codes;
			while (tmp != 0) {
				JavaCode imp = car(tmp);
				jcoImportSetImported(imp, true);
				tmp = cdr(tmp);
			}
			listFree(JavaCode)(codes);
		}
	}
	return resList;
}

local Bool
jc0ImportEq(JavaCode c1, JavaCode c2)
{
	assert(jcoIsImport(c1) && jcoIsImport(c2));

	if (strcmp(jcoImportPkg(c1), jcoImportPkg(c2)) != 0)
		return false;
	if (strcmp(jcoImportId(c1), jcoImportId(c2)) != 0)
		return false;

	return true;
}


local void
jc0CollectImports(Table tbl, Table nameTbl, JavaCode code)
{
	if (code == 0)
		return;
	if (jcoIsImport(code)) {
		JavaCodeList l = (JavaCodeList) tblElt(tbl, code, listNil(JavaCode));
		JavaCode key = code;
		l = listCons(JavaCode)(code, l);
		tblSetElt(tbl, key, l);

		String name = jcoImportId(code);
		JavaCodeList ids = (JavaCodeList) tblElt(nameTbl, name, listNil(JavaCode));
		if (!listMember(JavaCode)(ids, code, jc0ImportEq)) {
			tblSetElt(nameTbl, name, (TblElt) listCons(JavaCode)(code, ids));
		}
	}
	if (jcoIsNode(code)) {
		int i=0;
		for (i=0; i<jcoArgc(code); i++) {
			jc0CollectImports(tbl, nameTbl, jcoArgv(code)[i]);
		}
	}
}

/*
 * Returns a newly allocated string with properly escaped characters.
 */
local String
jc0EscapeString(String s, Bool addTerminalChar)
{
	Buffer buf;
	buf = bufNew();
	while (*s != 0) {
		switch (*s) {
		case '\\':
			bufPuts(buf, "\\\\");
			break;
		case '\n':
			bufPuts(buf, "\\\n");
			break;
		case '\"':
			bufPuts(buf, "\\\"");
			break;
		default:
			bufPutc(buf, *s);
			break;
		}
		s++;
	}
	if (addTerminalChar) {
		bufPutc(buf, '\\');
		bufPutc(buf, '0');
	}

	return bufLiberate(buf);
}

/*
 * :: Names and so on
 */

local Bool jcIsId(String word);

Bool
jcIsLegalClassName(String word)
{
	int i;
	if (!jcIsId(word))
		return false;

	for (i=0; i<JK_END; i++) {
		if (strcmp(word, jkKeywords[i].text) == 0)
			return false;
	}
	return true;
}

local Bool
jcIsId(String word)
{
	char *p = word;
	if (word[0] == '\0')
		return false;
	if (!(word[0] == '_' || isalpha(word[0])))
		return false;
	while (*p != '\0') {
		if (!(*p == '_' || isalnum(*p)))
			return false;
		p++;
	}

	return true;
}
