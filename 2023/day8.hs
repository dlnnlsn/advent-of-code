import qualified Data.Map as Map
import Data.Maybe

trim_left :: String -> String
trim_left "" = ""
trim_left string@(first_char : rest) =
    if first_char == ' ' then
        trim_left rest
    else
        string

splitOn :: Char -> String -> [String]
splitOn _ [] = [[]]
splitOn delimiter (first_char : rest) =
    if first_char == delimiter then
        [] : splitOn delimiter rest
    else
        let first_word : words = splitOn delimiter rest in
            (first_char : first_word) : words

data Node = Node {left_child :: String, right_child :: String} deriving (Show)

read_nodes :: [String] -> Map.Map String Node
read_nodes [] = Map.empty
read_nodes (line : lines) =
    let name : [children] = splitOn '=' line;
        nodes = read_nodes lines in 
        let left : [right] = splitOn ',' children in
            Map.insert (init name) (Node (tail $ tail left) (init $ tail right)) nodes

steps_necessary' :: Integer -> String -> String -> Map.Map String Node -> Integer
steps_necessary' current_steps "ZZZ" _ _ = current_steps
steps_necessary' current_steps starting_node (first_instruction : path) nodes =
    steps_necessary' (current_steps + 1) next_node path nodes 
    where
        node = fromJust $ Map.lookup starting_node nodes
        next_node = if first_instruction == 'L' then left_child node else right_child node


steps_necessary :: String -> Map.Map String Node -> Integer
steps_necessary path nodes = steps_necessary' 0 "AAA" (concat $ repeat path) nodes

main :: IO ()
main = do
    content <- getContents
    let path : blank_line : node_lines = lines content
    let nodes = read_nodes node_lines
    let answer = steps_necessary path nodes
    putStrLn $ show answer
