
DECLARATIONS

	Pred:	(Integer) -> Boolean;
	Pred2:	(Integer, Integer) -> Boolean;
	#~ Pred:	(Signal) -> Boolean;
	
FACTS

	Pred(1);
	#~ Pred(1);

	!Pred2(5, 5);

	All x:Integer #, y:Real
		Pred(x) & x <= 5 => Pred(x + 1) & Pred2(x, x+1);

RESTRICTIONS

	Pred(6);
	Pred(7);







#~ DECLARATIONS
#~ 
	#~ Pred:	(Integer) -> Boolean;
	#~ PredR:	(Real) -> Boolean;
	#~ Func:	(Integer) -> Integer;
	#~ Pred2: (Type) -> Boolean;
#~ 
#~ FACTS
#~ 
#~ 
	#~ Pred(1);
	#~ 
	#~ All x:Integer
		#~ Pred(x) & Pred(Func(x ^ 5))
			#~ => Pred(-x);
	#~ 
	#~ All x:Integer
		#~ Pred (x) & x < 5 => Pred(x + 1);
		#~ Pred (x) & x < 5 => PredR(sin(3.14)) & PredR(tan(3.14)) & Pred(min(7.0, 4));
	
	#~ !Pred(3)
	#~ Func(12) = 2;
	#~ Pred(2);

#~ RESTRICTIONS   #sdfsdsds;;;
#~ 
	#~ 5 + 3 = 8;

	#~ All x1, x2: type
		#~ P2(x1, x2) => P1(x1) & F1(x1) = Func2(-(123 + 45)) & 5 < 4;

	
	#~ All x, y:Integer
		#~ Pred(x) & Pred(y) & !Pred(x + 1) => Func1(x) = x * 2 & Pred2(x, x + 1);
	#~ 
	#~ Func1(1) = 1.2;
	#~ 
	#~ F3(1, 2, 3) = 1.5;
	#~ F3(1, 4, 3) = 1.6;
	#~ F3(1, 5, 3) = 1.6;
	#~ F3(0, 2, 3) = 1.7;
	
	#~ P3(1, 2, 3);
	#~ !P3(1, 4, 3);
	#~ !P3(1, 5, 3);
	#~ P3(0, 2, 3);
	
	#~ sdfsfdfsdf;
	
	#~ Pred(5);
	#~ 
	#~ All x: Integer
		#~ Pred(x) &  x <= x
			#~ => Pred2(-(x + x * -2) / 10, x - 128);


###################
	#~ A(a, b);	A(g, d);
	#~ B(b, d);	B(b, e);	B(b, k);
	#~ C(c, d);	C(e, a);
#~ 
	#~ All x:Type, y:Type, z:Type, v:Type, p:Type
		#~ A(x, y) & B(y, z) & C(v, p) => B(z, p);
	#~ 
	#~ All x:Type, y:Type, z:Type, v:Type
		#~ A(x, y) & C(z, v) => B(x, z);


























###############
#~ PREDICATES
	#~ A ( 2 )   B ( 2 )   C ( 2 )
#~ FUNCTIONS
#~ FACTS
#~ 
#~ A  a b
#~ A  g d
#~ 
#~ B  b d
#~ B  b e
#~ B  b k
#~ 
#~ C  c d
#~ C  e a
#~ 
#~ =>  & 3   A _x _y   B _y _z   C _v _p     B _z _p
#~ =>  & 2   A _x _y   C _z _v		  B _x _z
#~ RESTRICTIONS
#~ END

###############




#~ DECLARATIONS
	#~ P1:	(type) -> Boolean;
	#~ P2:	(type, type) -> Boolean;
	#~ P3:	(type, type, type) -> Boolean;
#~ 
	#~ F1:	(type) -> type;
	#~ F2:	(type, type) -> type;
	#~ F3:	(type, type, type) -> type;
#~ 
#~ FACTS
#~ 
	#~ All x1:type, x2:type All x3:type
		#~ P1(F1(x1)) & F2(x1, x2) = x3 & P3(x1, x2, x3) => P1(x3);
