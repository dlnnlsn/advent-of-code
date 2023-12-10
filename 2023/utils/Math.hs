module Math
(
    bezout,
    crt
) where

import Control.Monad (foldM)
import Data.Maybe (fromJust)

bezout' :: Integer -> Integer -> Integer -> Integer -> Integer -> Integer -> (Integer, Integer, Integer)
bezout' a 0 s t _ _ = (s, t, a)
bezout' a b s t u v = bezout' b (a `mod` b) u v s' t'
    where
        q = a `div` b
        s' = s - q * u
        t' = t - q * v

bezout :: Integer -> Integer -> (Integer, Integer, Integer)
bezout m n = bezout' m n 1 0 0 1

mod_inverse :: Integer -> Integer -> Maybe Integer
mod_inverse m n = if g == 1 then Just (s `mod` n) else Nothing
    where (s, t, g) = bezout m n

crt2 :: (Integer, Integer) -> (Integer, Integer) -> Maybe (Integer, Integer)
crt2 (a1, m1) (a2, m2) = if (a1 `mod` g) /= (a2 `mod` g) then Nothing else
    Just ((a1 + (a2 - a1) * s) `mod` m, m)
    where
        g = gcd m1 m2
        m = lcm m1 m2
        m1' = m1 `div` g
        m2' = m2 `div` g
        s = m1' * (fromJust $ mod_inverse m1' m2')

crt :: [Integer] -> [Integer] -> Maybe (Integer, Integer)
crt remainders moduli = let pairs = zip remainders moduli in foldM crt2 (0, 1) pairs
