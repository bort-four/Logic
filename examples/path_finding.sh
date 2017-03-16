# Пример поиска пути в квадратном поле 6 на 6 клеток, которые могут быть свободны, или заняты
# программа находит кротчайшие пути из клетки (1, 1) во все свободные клетки, для которых это возможно

DECLARATIONS

    Busy: (Integer, Integer) -> Boolean;		# занятость клетки (клетка задаётся парой коодринат)
	Reachable: (Integer, Integer) -> Boolean;	# достижимость клетки
	
    Conected: (Integer, Integer, Integer, Integer) -> Boolean;	# соседство клеток
	Distance: (Integer, Integer) -> Integer;					# длина минимального пути между клетками
	ExtShoterWay: (Integer, Integer, Integer) -> Boolean;		# ExtShoterWay(x, y, n) := в клетку (x, y) существует
	                                                            # путь длины меньше, чем n.

    OnWay: (Integer, Integer, Integer, Integer) -> Boolean;		# первая клетка является предпоследним звеном на кратчайшем
	                                                            # пути ко второй (для восстановления пути)

FACTS
	
    # Устанавливаем отношение соседства
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

    # Устанавливаем предикат ExtShoterWay
	All x1, y1, x2, y2: Integer
	    Conected(x1, y1, x2, y2)
		& Distance(x1, y1) < Distance(x2, y2)
		    => ExtShoterWay(x1, y1, Distance(x2, y2) + 1);

    # если в точку (x, y) можно попасть из точек (x1, y1) и (x2, y2)
	# и расстояние до (x1, y1) меньше, чем до (x2, y2),
	# то существует путь до (x, y) меньший, чем путь через (x2, y2)
	All x1, y1, x2, y2, x, y: Integer
		Conected(x1, y1, x, y) & Conected(x2, y2, x, y)
		& Distance(x1, y1) < Distance(x2, y2)
			=> ExtShoterWay(x, y, Distance(x2, y2) + 1);

    # если мы знаем, что в точку (x2, y2) не существует более короткого пути, чем через (x1, y1)
	# то устанавливаем достижимость и дистанцию для (x2, y2)
	All x1, y1, x2, y2: Integer
		Reachable(x1, y1) & Conected(x1, y1, x2, y2)
		& !ExtShoterWay(x2, y2, (Distance(x1, y1) + 1))
			=> 	Reachable(x2, y2)
			    & Distance(x2, y2) = (Distance(x1, y1) + 1)
				& OnWay(x1, y1, x2, y2);


    # начальная точка достижима за 0 шагов
	Reachable(1, 1);
	Distance(1, 1) = 0;

    # задаём карту
	# ..##........
	# ............
	# ##..##......
	# ....##..##..
	# ..##........
	# ......##....
	
                Busy(2, 1);

	Busy(1, 3);				Busy(3, 3);
							Busy(3, 4);				Busy(5, 4);
				Busy(2, 5);
										Busy(4, 6);

RESTRICTIONS
    # Проверяем достижимость нижней правой клетки
	Reachable(6, 6);
