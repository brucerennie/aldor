--------------------------------------------------------------------------------
--
-- sm_polring0.as: A basic category constructor to define polynomial domains
-- either as finite abelian monoid rings (as in AXIOM or most computer algebra
-- systems) or simply as the results of repeated iterations of the rule
-- `R -> R[X]' (as in classical algebra textbooks) without building monomials
-- explicitely.
--
--------------------------------------------------------------------------------
--  Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
-- Copyright: INRIA, UWO and University of Lille I, 2001
-- Copyright: Marc Moreno Maza
--------------------------------------------------------------------------------

-- cat PolynomialRing0

#include "algebra"


macro { 
      NNI == Integer;
      UPP == IndexedFreeRRing(%,NNI);
}

+++ `PolynomialRing0(R,V)' is the category of the domains that implement
+++ a polynomial ring with coefficients in `R' and variables in `V'.
+++ If `V' is a finite set `{v1,...,vl}' this polynomial ring is just
+++ `R[v1,...,vl]'. If `V' is finite or not, the set of monomials is
+++ the free abelian monoid `E' generated by `V'. Moreover `E' is
+++ totally ordered by the lexicographical ordering induced by `V'.
+++ Author: Marc Moreno Maza
+++ Date Createds: 09/12/97
+++ Date Last Update: 12/07/01

define PolynomialRing0(R:Join(ArithmeticType, ExpressionType),
   V: Join(TotallyOrderedType, ExpressionType)): Category == 
   	Join(PolynomialTypeRing(R, V), FreeAlgebra R) with {
        default {
	   -- this default is for commutative variables only
           univariate(P: UPP)(p: %,v: V): P == {
              ground? p => p::P;
              terms: P := 0;
              local lwz: List Cross(V, NNI);
              local d: NNI;
              for pair in support(p) repeat {
                 (r, m) := pair;
                 lwz := empty;
                 d := 0;
                 for wz in variableProduct(m) repeat {
                    (w: V, z: NNI) := wz;
                    if w = v then { 
                       d := z;
                    } else {
                       lwz := cons(wz,lwz);
                    }
                 }
                 if zero? d then {
                    m := r * m;
                 } else {
                    m := term(r,generator(lwz));
                 }
                 terms := add!(terms, m, d);
              }
              terms;
           }     
	}
     }


#if ALDOC
\thistype{PolynomialRing0}
\History{Marc Moreno Maza}{08/07/01}{created}
\Usage{\this~(R,V): Category}
\Params{
{\em R} & \altype{ArithmeticType} & The coefficient domain \\
        & \altype{ExpressionType} &\\
{\em V} & \altype{TotallyOrderedType} & The variable domain \\
         & \altype{ExpressionType} &\\
}
\Descr{\this~(R,V) is the category of the domains that implement
 a polynomial ring with coefficients in $R$ and variables in $V.$
 If $V$ is a finite set $\left\{v_1, \ldots ,v_l \right\}$ 
 this polynomial ring is just
 $R[v_1, \ldots ,v_l].$ 
 If $V$ is finite or not, the set of monomials is
 the free abelian monoid $E$ generated by $V.$ 
 Moreover the default total ordering endowing $E$ is the
 the lexicographical one induced by $V.$
 Observe that the domain $V$ is not assumed to satisfy \altype{VariableType}.
 In fact, only weaker conditions are required.
 Hence it is possible to use any totally ordered set as a domain
 of variables. For instance a set of algebraically independent numbers.
 Observe that \this~(R,V) provides essentially operations
 related to the structure of a free algebra.
 For more sophisticated operations (differentiation, evaluation, \ldots)
 see the category constructor \altype{PolynomialRing}.}
\begin{exports}
\category{\altype{PolynomialTypeRing}(R, V)} \\
\category{\altype{FreeAlgebra} R} \\
\end{exports}
#endif

#if ALDORTEST

---------------------- test polring0.as --------------------------
#include "algebra"
#include "aldortest"

macro {
	B == Boolean;
        Z == Integer;
	N == Integer;
}

main():() == {
   import from String, Symbol, MachineInteger, Integer, TextWriter;

   R1 == Integer;
   R2 == SmallPrimeField(41);
   V == OrderedVariableTuple(-"x",-"y",-"z");
   x: V := variable(1)$V;
   y: V := variable(2)$V;
   z: V := variable(3)$V;
   lv: List(V) == [x,y,z];
   E1 == MachineIntegerDegreeLexicographicalExponent(V);

   import from R1, R2, E1;

   P1 == DistributedMultivariatePolynomial1(R1,V,E1);
   P2 == DistributedMultivariatePolynomial1(R2,V,E1);
   P3 == SparseIntegerMultivariatePolynomial(V);

   lr1: List(R1) == [-1,-3,6,12,-18,21,24,111,-789,103];
   lr2: List(R2) == [r1 :: R2 for r1 in lr1];
   n1: Z := (#lr1) :: Z;  
   degMax := n1;

   le1: List(E1) == [exponent(0,0,0), exponent(1,0,0), exponent(0,1,0), exponent(0,0,1), exponent(1,2,3),  exponent(3,2,1), exponent(2,3,1), exponent(1,2,0), exponent(2,1,0), exponent(1,1,1)];


   pack1 == PolynomialRing0TestPackage(R1,V,P1);
   lp1: List List Cross (R1, List V, List N)  == makeZoo(lr1,lv,degMax, n1 * n1 * n1)$pack1;
   errors: Z := PRTest(lp1,false,false)$pack1;
   if zero? errors  then {
      stdout << " OK " << newline;
   } else {
      stdout << " ERROR " << newline;
   }

   stdout << newline << "... with DMP1 mod p ... ";
   pack2 == PolynomialRing0TestPackage(R2,V,P2);
   lp2: List List Cross (R2, List V, List N)  == makeZoo(lr2,lv,degMax, n1 * n1 * n1)$pack2;
   errors: Z := PRTest(lp2,false,false)$pack2;
   if zero? errors  then {
      stdout << " OK " << newline;
   } else {
      stdout << " ERROR " << newline;
   }

--   stdout << newline << "... with RMP over Z ... ";
--   pack3 == PolynomialRing0TestPackage(R1,V,P3 pretend PolynomialRing0(R1,V));
--   lp3: List List Cross (R1, List V, List N)  == makeZoo(lr1,lv,degMax, n1)$pack3;
--   errors: Z := PRTest(lp3,false,false)$pack3;
--   if zero? errors  then {
--      stdout << " OK " << newline;
--   } else {
--      stdout << " ERROR " << newline;
--   }
--   TEST FAILED: ERROR

}


main();

stdout << endnl;

#endif
