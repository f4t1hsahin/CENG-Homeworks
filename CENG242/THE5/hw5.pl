:- module(hw5, [configuration/3]).
:- [hardware].

outer_edges(X) :-
	sections(Sections),
	outers(Sections, X).

outers([],[]).
outers([H | T],Res) :-
	c_adjacent(H,Z),
	length(Z, Z_length),
	Z_length < 4,!,
	outers(T, Rev),
	append(Rev,[H],Res).
outers([H | T], Res) :-
	c_adjacent(H,Z),
	length(Z, Z_length),
	Z_length >= 4,
	outers(T, Res).


c_adjacent(X,Res) :-
	findall(Y,(adjacent(X,Y) ; adjacent(Y,X)), Res).

configuration(Edevatlar, Tes, Qeqo) :-
	sections(Sections),
	test(Edevatlar, Tes, Test, Sections),
	que(Edevatlar, Test, Rev),
	reverse(Rev,Qeqo).

test([],_,[],_).
test(Edevatlar, [close_to(X,Y) | Rest], Placements, Kalan) :-
	sections(Sections),
	length(Sections, Sec_length),
	length(Edevatlar, Ede_length),
	Sec_length>=Ede_length,
	select(X, Edevatlar, Edevatlar1),
	select(Y, Edevatlar1, Yeni_edevatlar),
	member(First, Kalan),
	member(Second, Kalan),
	(adjacent(First, Second) ; adjacent(Second, First)),
	select(First, Kalan, Kalan1),
	select(Second, Kalan1, Kalan2),
	test(Yeni_edevatlar, Rest, Rev, Kalan2),
	append(Rev, [put(Y, Second)], Placements1),
	append(Placements1, [put(X, First)], Placements).


test(Edevatlar, [], Placements,Kalan) :-
	member(X, Edevatlar),!,
	sections(Sections),
	length(Sections, Sec_length),
	length(Edevatlar, Ede_length),
	Sec_length>=Ede_length,
	member(Section, Kalan),
	select(X, Edevatlar, Yeni_edevatlar),
	select(Section, Kalan, Kalan2),
	test(Yeni_edevatlar, [], Rev, Kalan2),
	append(Rev, [put(X, Section)], Placements).
	



test(Edevatlar, [outer_edge(X) | Rest], Placements, Kalan) :-
	sections(Sections),
	length(Sections, Sec_length),
	length(Edevatlar, Ede_length),
	Sec_length>=Ede_length,
	select(X, Edevatlar, Yeni_edevatlar),
	member(Section, Kalan),
	outer_edges(Outers),
	member(Section, Outers),
	select(Section, Kalan, Kalan2),
	test(Yeni_edevatlar, Rest, Rev, Kalan2),
	append(Rev, [put(X, Section)], Placements).

que([],_,[]).
que([H | T], Qeqo, Res) :-
	member(put(H,S), Qeqo),!,
	que(T,Qeqo, Rev),
	append(Rev,[put(H,S)],Res).

