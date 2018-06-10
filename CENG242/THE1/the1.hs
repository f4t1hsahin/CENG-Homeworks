module Hw1 where

data Cell = H | P | O | X deriving (Read,Show,Eq)
data Result = Fail | Caught (Int,Int) deriving (Read,Show,Eq)
data Direction = N | S | E | W deriving (Read,Show,Eq)

simulate :: [[Cell]] -> [(Direction, Direction)] -> Result
-- DO NOT CHANGE ABOVE THIS LINE, WRITE YOUR CODE BELOW --
simulate [] _  = Fail
simulate lst tpl = if (move lst tpl (findinY lst 0 H) (findinY lst 0 P)) /= (-1,-1) then Caught ((move lst tpl (findinY lst 0 H) (findinY lst 0 P))) else Fail

findinX [] _ _ = -1
findinX (a:l) x t = if  (a == t)  then x else findinX l (x+1) t

findinY [] _ _ = (-1,-1)
findinY (a:l) y t = if ((findinX a 0 t) /= -1) then (findinX a 0 t , y) else (findinY l (y+1) t)

move _ [] (x1,y1) (x2,y2) = if x1 == x2 && y1 == y2 then (x1,y1) else ((-1),(-1))
move lst (a:l) (x1,y1) (x2,y2) = if x1 == x2 && y1 == y2 then (x1,y1) else move lst l (makeitMove lst (fst a) (x1,y1)) (makeitMove lst (snd a) (x2,y2))

makeitMove lst dir (x,y) | dir == W && x/= 0 && lst!!y!!(x-1) /= X = (x-1,y)
						 | dir == E && x/= ((length (lst!!0)) - 1) && lst!!y!!(x+1) /= X = (x+1,y)
						 | dir == N && y/= 0 && lst!!(y-1)!!x /= X = (x,y-1)
						 | dir == S && y/= ((length lst)-1) && lst!!(y+1)!!x /= X = (x,y+1)
						 |otherwise = (x,y)
