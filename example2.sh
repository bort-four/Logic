# example2.sh

DECLARATIONS

	#~ Free: (Integer, Integer) -> Boolean;
	Busy: (Integer, Integer) -> Boolean;
	Reachable: (Integer, Integer) -> Boolean;
	
	Pred: (Integer, Integer, Real) -> Boolean;
	
	Conected: (Integer, Integer, Integer, Integer) -> Boolean;
	Distance: (Integer, Integer) -> Integer;
	ExtShoterWay: (Integer, Integer, Integer) -> Boolean;
	OnWay: (Integer, Integer, Integer, Integer) -> Boolean;

FACTS

# Axioms

	#~ All x, y: Integer	# move from x to x + 1
		#~ Reachable(x, y) & x + 1 <= 6 & Free(x + 1, y)
			#~ => Conected(x, y, x + 1, y);
#~ 
	#~ All x, y: Integer	# move from x to x - 1
		#~ Reachable(x, y) & x - 1 >= 1 & Free(x - 1, y)
			#~ => Conected(x, y, x - 1, y);
#~ 
	#~ All x, y: Integer	# move from y to y + 1
		#~ Reachable(x, y) & y + 1 <= 6 & Free(x, y + 1)
			#~ => Conected(x, y, x, y + 1);
#~ 
	#~ All x, y: Integer	# move from y to y - 1
		#~ Reachable(x, y) & y - 1 >= 1 & Free(x, y - 1)
			#~ => Conected(x, y, x, y - 1);
	
	All x, y: Integer	# move from x to x + 1
		Reachable(x, y) & x + 1 <= 6 & !Busy(x + 1, y)
			=> Conected(x, y, x + 1, y);

	All x, y: Integer	# move from x to x - 1
		Reachable(x, y) & x - 1 >= 1 & !Busy(x - 1, y)
			=> Conected(x, y, x - 1, y);

	All x, y: Integer	# move from y to y + 1
		Reachable(x, y) & y + 1 <= 6 & !Busy(x, y + 1)
			=> Conected(x, y, x, y + 1);

	All x, y: Integer	# move from y to y - 1
		Reachable(x, y) & y - 1 >= 1 & !Busy(x, y - 1)
			=> Conected(x, y, x, y - 1);
	
	All x1, y1, x2, y2, x, y: Integer
		Conected(x1, y1, x, y) & Conected(x2, y2, x, y)
		& Distance(x1, y1) < Distance(x2, y2)
			=> ExtShoterWay(x, y, Distance(x2, y2) + 1);

	All x1, y1, x2, y2: Integer
		Reachable(x1, y1) & Conected(x1, y1, x2, y2)
		& !ExtShoterWay(x2, y2, Distance(x1, y1) + 1)
			=> 	Reachable(x2, y2)
				& Distance(x2, y2) = Distance(x1, y1) + 1
				& OnWay(x1, y1, x2, y2);


# Facts
# begin state

	Reachable(1, 1);
	Distance(1, 1) = 0;

# set map
	
#~ Free(1, 1);		!Free(2, 1);	Free(3, 1);		Free(4, 1);		Free(5, 1);		Free(6, 1);
#~ Free(1, 2);		Free(2, 2);		Free(3, 2);		Free(4, 2);		Free(5, 2);		Free(6, 2);
#~ !Free(1, 3);	Free(2, 3);		!Free(3, 3);	Free(4, 3);		Free(5, 3);		Free(6, 3);
#~ Free(1, 4);		Free(2, 4);		!Free(3, 4);	Free(4, 4);		!Free(5, 4);	Free(6, 4);
#~ Free(1, 5);		!Free(2, 5);	Free(3, 5);		Free(4, 5);		Free(5, 5);		Free(6, 5);
#~ Free(1, 6);		Free(2, 6);		Free(3, 6);		!Free(4, 6);	Free(5, 6);		Free(6, 6);
	
	
				Busy(2, 1);
							#~ Busy(3, 2);
	Busy(1, 3);				Busy(3, 3);
							Busy(3, 4);				Busy(5, 4);
				Busy(2, 5);
										Busy(4, 6);

RESTRICTIONS
	#~ All x:Integer Reachable(x, x);
	Reachable(6, 6);
