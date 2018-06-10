module Hw2 where
import Data.List -- YOU MAY USE THIS MODULE FOR SORTING THE AGENTS

data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)
-- DO NOT CHANGE THE DEFINITIONS ABOVE. --

instance Ord Prey where
	compare (Prey _id1 _en1 _) (Prey _id2 _en2 _)
		| (compare _en1 _en2) /= EQ = compare _en1 _en2
		| otherwise = compare _id2 _id1


instance Ord Hunter where
	compare (Hunter _id1 _level1 _en1 _num1 _) (Hunter _id2 _level2 _en2 _num2 _)
		| (compare _level1 _level2) /= EQ = compare _level1 _level2
		| (compare _en1 _en2) /= EQ = compare _en1 _en2
		| (compare _num1 _num2) /= EQ = compare _num1 _num2
		| otherwise = compare _id2 _id1


getAgents' (P (Prey id en dir)) x y (lst_p,lst_h) =  (lst_p ++ [((Prey id en dir),(x,y))],lst_h)
getAgents' (H (Hunter _id _level _en _num _dir)) x y (lst_p,lst_h) = (lst_p,lst_h ++ [((Hunter _id _level _en _num _dir),(x,y))])
getAgents' _ x y (lst_p,lst_h)= (lst_p,lst_h)

getAgentsX [] _ _ (lst_p, lst_h) = (lst_p, lst_h)
getAgentsX (a:l) x y (lst_p, lst_h) = getAgentsX l (x+1) (y) (getAgents' a x y (lst_p, lst_h))


getAgentsY []  _ (lst_p, lst_h) = (lst_p, lst_h)
getAgentsY (a:l)  y (lst_p, lst_h) = getAgentsY l  (y+1) (getAgentsX a 0 y (lst_p, lst_h))  


sortAgents (lst_p,lst_h) = (sort (lst_p), reverse (sort (lst_h)))


getTraps' T x y = [(x,y)]
getTraps' _ _ _ = []

getTrapsX [] _ _ = []
getTrapsX (a:l) x y = (getTraps' a x y) ++ getTrapsX l (x+1) y

getTrapsY [] _ = []
getTrapsY (a:l) y = [getTrapsX a 0 y] ++ getTrapsY l (y+1)

makeitMove lst dir (x,y) | dir == W && x/= 0 && lst!!y!!(x-1) /= X = (x-1,y)
						 | dir == E && x/= ((length (lst!!0)) - 1) && lst!!y!!(x+1) /= X = (x+1,y)
						 | dir == N && y/= 0 && lst!!(y-1)!!x /= X = (x,y-1)
						 | dir == S && y/= ((length lst)-1) && lst!!(y+1)!!x /= X = (x,y+1)
						 |otherwise = (x,y)

movePrey ((Prey _id _en (a:l)),s) grid  = if _en >= 10 then ((Prey _id (max 0 (_en - 1)) l), (makeitMove grid a s)) else ((Prey _id (_en+1) l),s)

moveHunter ((Hunter _id _level _en _num (a:l)),s) grid = if _en >= 10 then ((Hunter _id _level(max 0 (_en-1)) _num l), makeitMove grid a s) else ((Hunter _id _level(max 0 (_en+1)) _num l),s)

flatten xs = (\z n -> foldr (\x y -> foldr z y x) n xs) (:) []

trapPrey ((Prey _id _en _lst),s) = ((Prey _id (max 0 (_en - 10)) _lst), s) 

checkTraps [] _ = []
checkTraps (a:l) traps
	| elem (snd a) traps = trapPrey a: checkTraps l traps
	| otherwise = a:checkTraps l traps

movePreys [] _ = []
movePreys (a:l) grid = (movePrey a grid): movePreys l grid

moveHunters [] _  = []
moveHunters lst_h@(a:l) grid = (moveHunter a grid): moveHunters l grid 

moveAgents (lst_p, lst_h) grid = (movePreys lst_p grid, moveHunters lst_h grid)

catchPrey ((Hunter _id1 _level1 _en1 _num1 _dir1),cord1) ((Prey _id _en _dir),cord2) = if cord1 == cord2 then [(Prey _id _en _dir)] else []


catchPreys _ []  _ processed lst_seen = processed
catchPreys h_c (a:l) x processed lst_seen
	| (length processed) >= 2 = catchPreys h_c [] x processed lst_seen
	| ((snd h_c) == (snd a)) && not (elem x lst_seen) = catchPreys h_c l (x+1) (processed++[x]) lst_seen
	| otherwise = catchPreys h_c l (x+1) processed lst_seen 


getSeens _ _ [] seens = seens
getSeens h_c (lst_h) (a:l) seens
	| (fst a) >= length lst_h =  (seens)
	| (snd h_c) == (snd (lst_h!!(fst a))) =  getSeens h_c lst_h l (seens ++ (snd a))
	| otherwise = getSeens h_c lst_h l seens

forHunters [] _ _ result _= result
forHunters (a:l) lst_p x result lst_h =  forHunters l lst_p (x+1) (result ++ [(x,(catchPreys a lst_p 0 [] (getSeens (a) lst_h result [])))]) lst_h

updateHunter (Hunter _id _level _en _num _dir) (num,lst) = Hunter _id _level (min 100 (_en + (length lst) * 20)) (_num + (length lst)) _dir


updateHunters [] _ = []
updateHunters lst_h@(a:l) lst_c@(b:ll) = ((updateHunter (fst a) b), snd a):updateHunters l ll

updatePrey _ [] = False
updatePrey x lst_c@(b:ll) = (elem x (snd b)) || updatePrey x ll

updatePreys [] _ _  lst = (sort lst)
updatePreys (a:l) lst_c x  lst
	|updatePrey x lst_c = updatePreys l lst_c (x+1) lst
	|otherwise =  updatePreys l lst_c (x+1) (lst ++ [a])

checkDirHunter (Hunter _id _level _en _num _dir) = if length _dir > 0 then False else True
checkDir (a:l) = checkDirHunter (fst a)


helper grid lst_h@(a:l) lst_p
	| length lst_p == 0 = (lst_h, [])
	| (checkDirHunter (fst a)) = ((reverse (sort (updateHunters lst_h (forHunters lst_h lst_p 0 [] lst_h)))), (sort (checkTraps (updatePreys lst_p (forHunters lst_h lst_p 0 [] lst_h) 0 [] ) (flatten (getTrapsY grid 0)))))
	| otherwise = if length ((updatePreys lst_p (forHunters lst_h lst_p 0 [] lst_h) 0 [] )) /= 0 then helper grid (reverse (sort (moveHunters (updateHunters lst_h (forHunters lst_h lst_p 0 [] lst_h)) grid ))) (sort ( movePreys (checkTraps (updatePreys lst_p (forHunters lst_h lst_p 0 [] lst_h) 0 [] ) (flatten (getTrapsY grid 0))) grid)) else ((updateHunters lst_h (forHunters lst_h lst_p 0 [] lst_h)),[])

simulate grid = helper grid (snd (sortAgents (getAgentsY grid 0 ([],[])))) (fst (sortAgents (getAgentsY grid 0 ([],[]))))
