#include "cport.h"
#include "store.h"
#include "ttable.h"

local PointerTSet ptrTSetCreate	(void);
local void 	  ptrTSetFree	(PointerTSet);
local void 	  ptrTSetAdd	(PointerTSet, Pointer);
local void 	  ptrTSetRemove	(PointerTSet, Pointer);
local Bool 	  ptrTSetMember	(PointerTSet, Pointer);
local Bool 	  ptrTSetIsEmpty(PointerTSet);

const struct TSetOpsStructName(Pointer) ptrTSetOps = {
	ptrTSetCreate,
	ptrTSetFree,
	ptrTSetAdd,
	ptrTSetRemove,
	ptrTSetMember,
	ptrTSetIsEmpty,
};

local PointerTSet
ptrTSetCreate()
{
	PointerTSet tset = (PointerTSet) stoAlloc(OB_Other, sizeof(*tset));
	tset->lst = listNil(Pointer);
	return tset;
}

local void
ptrTSetFree(PointerTSet tset)
{
	listFree(Pointer)(tset->lst);
	stoFree(tset);
}

local Bool
ptrTSetIsEmpty(PointerTSet tset)
{
	return listNil(Pointer) == tset->lst;
}

local Bool
ptrTSetMember(PointerTSet tset, Pointer ptr)
{
	return listMemq(Pointer)(tset->lst, ptr);
}

local void
ptrTSetAdd(PointerTSet tset, Pointer ptr)
{
	if (listMemq(Pointer)(tset->lst, ptr))
		return;
	tset->lst = listCons(Pointer)(ptr, tset->lst);
}

local void
ptrTSetRemove(PointerTSet tset, Pointer ptr)
{
	tset->lst = listNRemove(Pointer)(tset->lst, ptr, 0);
}
