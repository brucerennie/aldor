#include "abquick.h"
#include "abuse.h"
#include "axlobs.h"
#include "debug.h"
#include "format.h"
#include "scobind.h"
#include "stab.h"
#include "testlib.h"
#include "tinfer.h"
#include "sefo.h"
#include "ablogic.h"
#include "comsg.h"
#include "symbol.h"
#include "tform.h"

local void testSymeSExpr();
local void testSymeAddCondition();

void
symeTest()
{
	init();
	TEST(testSymeSExpr);
	TEST(testSymeAddCondition);
	fini();
}

extern int stabDebug;

local void
testSymeSExpr()
{
	String aSimpleDomain = "+++Comment\nDom: Category == with {f: () -> () ++ f\n}";
	StringList lines = listList(String)(1, aSimpleDomain);
	AbSynList code = listCons(AbSyn)(stdtypes(), abqParseLines(lines));

	AbSyn absyn = abNewSequenceL(sposNone, code);

	Stab stab;
	SymeList symes;
	Syme syme;
	SExpr sx;

	initFile();
	stab = stabFile();

	abPutUse(absyn, AB_Use_NoValue);
	scopeBind(stab, absyn);
	typeInfer(stab, absyn);

	testTrue("Declare is sefo", abIsSefo(absyn));
	testIntEqual("Error Count", 0, comsgErrorCount());

	symes = stabGetMeanings(stab, ablogFalse(), symInternConst("Dom"));
	testIntEqual("unique meaning", 1, listLength(Syme)(symes));

	syme = car(symes);
	sx = symeSExprAList(syme);

	finiFile();
}

local void
testSymeAddCondition()
{
	String B_imp = "import from Boolean";
	String C_txt = "C: Category == with";
	String D1_txt = "D1: with == add";
	String D2_txt = "D2: with == add";
	StringList lines = listList(String)(4, B_imp, C_txt, D1_txt, D2_txt);
	AbSynList code = listCons(AbSyn)(stdtypes(), abqParseLines(lines));
	
	AbSyn absyn = abNewSequenceL(sposNone, code);

	AbSyn D1, D2, C;
	Syme syme1, syme2;
	Stab stab;

	initFile();
	stab = stabFile();
	
	abPutUse(absyn, AB_Use_NoValue);
	scopeBind(stab, absyn);
	typeInfer(stab, absyn);
	
	D1 = abFrSyme(uniqueMeaning(stabFile(), "D1"));
	D2 = abFrSyme(uniqueMeaning(stabFile(), "D2"));
	C = abFrSyme(uniqueMeaning(stabFile(), "C"));
	syme1 = symeNewExport(symInternConst("syme2"), tfNewAbSyn(TF_General, id("D")), car(stab));
	symeAddCondition(syme1, sefo(has(D1, C)), true);
	testIntEqual("test1", 1, listLength(Sefo)(symeCondition(syme1)));

	syme2 = symeNewExport(symInternConst("syme1"),tfNewAbSyn(TF_General, id("D")), car(stab));
	symeAddCondition(syme2, sefo(and(has(D1, C),
					 has(D2, C))), true);
	
	testIntEqual("test2", 2, listLength(Sefo)(symeCondition(syme2)));

	finiFile();
}
