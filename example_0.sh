# example_0.sh

DECLARATIONS

	A:(Type, Type) -> Boolean;
	B:(Type, Type) -> Boolean;
	C:(Type, Type) -> Boolean;

	#~ P1: (Type) -> Boolean;
	#~ P2: (Type, Type) -> Boolean;
	#~ P3: (Type, Type, Type) -> Boolean;
	#~ P4: (Type, Type, Type, Type) -> Boolean;
	#~ P5: (Type, Type, Type, Type, Type) -> Boolean;


FACTS

	#~ P2(a, b);	P2(b, b);
	#~ P2(a, c);	P2(c, c);
	#~ P1(a);
#~ 
	#~ All x1, x2:Type
		#~ P1(x1) & P2(x1, x2) & P2(x2, x2) => P3(x1, x2, x2);
	

	A(a, b);	A(g, d);
	B(b, d);	B(b, e);	B(b, k);
	C(c, d);	C(e, a);

	All x, y, z, v, p : Type
		A(x, y) & B(y, z) & C(v, p) => B(z, p);
	
	All x, y, z, v : Type
		A(x, y) & C(z, v) => B(x, z);
