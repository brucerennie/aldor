#include "comp"
#include "aldorio"

#pile

TFormAttrs: with
    import from Id
    create: (s: Id == id "", sx: SExpression == nil) -> %
    id: % -> Id
    sx: % -> SExpression
== add
    Rep == Record(s: Id, sx: SExpression)
    import from Rep
    create(s: Id == id "", sx: SExpression): % == per [s, sx]
    id(a: %): Id == rep(a).s
    sx(a: %): SExpression == rep(a).sx

TForm: Join(OutputType, PrimitiveType) with
    args: % -> List %
    bindings: % -> BindingSet
    attrs: % -> TFormAttrs

    new: (TFormTagCat, List TForm) -> %
    new: (TFormTagCat, List TForm, BindingSet) -> %
    new: (TFormTagCat, List TForm, BindingSet, TFormAttrs) -> %

    kind: % -> String
== add
    Rep == Record(bindings: BindingSet, tag: TFormTagCat, args: List TForm, attrs: TFormAttrs);
    import from Rep
    import from TFormAttrs
    default tf, tf1, tf2: %

    args tf: List % == rep(tf).args
    tag tf: TFormTagCat == rep(tf).tag
    bindings tf: BindingSet == rep(tf).bindings
    attrs tf: TFormAttrs == rep(tf).attrs
    kind tf: String == name$(tag tf)

    new(D: TFormTagCat, args: List TForm): % ==
    	   new(D, args, empty()$BindingSet)

    new(D: TFormTagCat, args: List TForm, bindings: BindingSet): % ==
    	   new(D, args, bindings, create())

    new(D: TFormTagCat, args: List TForm, bindings: BindingSet, a: TFormAttrs): % ==
    	   per [bindings, D, args, a]
   
    (tf1: %) = (tf2: %): Boolean ==
        import from Id
        name$(tag tf1) = name$(tag tf2) => tfEquals(tf1, tf2)$(tag tf1)
	false


    (o: TextWriter) << tf: TextWriter ==
        import from Id
        o << "{" << name$(tag tf) << " ";
	info(o, tf)$(tag tf)
	o << args tf << " " << "}"

TFormTagCat: Category == with
    name: String
    tfEquals: (TForm, TForm) -> Boolean
    tfFreeVars: TForm -> List(Id)
    info: (TextWriter, TForm) -> ();
    default 
        info(tx: TextWriter, tf: TForm): () == {}