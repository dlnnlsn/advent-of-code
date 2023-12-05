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

data Revelation = Revelation {
    red :: Integer,
    green :: Integer,
    blue :: Integer
} deriving (Show)

data Game = Game {
    game_id :: Integer,
    revelations :: [Revelation]
} deriving (Show)

read_revelation' :: Revelation -> String -> Revelation
read_revelation' revelation piece =
    let (count : colour : rest) = splitOn ' ' (trim_left piece) in
        case colour of
            "red" -> Revelation (read count) (green revelation) (blue revelation)
            "green" -> Revelation (red revelation) (read count) (blue revelation)
            "blue" -> Revelation (red revelation) (green revelation) (read count)
            otherwise -> revelation

read_revelation :: String -> Revelation
read_revelation string = foldl read_revelation' (Revelation 0 0 0) (splitOn ',' string)

read_game :: String -> Game
read_game string =
    let (tag : [revelation_string]) = splitOn ':' string in
        let (_ : [id]) = splitOn ' ' tag; revelations = splitOn ';' revelation_string in
            Game (read id) $ map read_revelation revelations

valid :: Game -> Bool
valid game = 
    let game_red = maximum $ map red $ revelations game;
        game_green = maximum $ map green $ revelations game;
        game_blue = maximum $ map blue $ revelations game in
        (game_red <= 12) && (game_green <= 13) && (game_blue <= 14)

valid_id_sum :: [Game] -> Integer
valid_id_sum games = sum $ map game_id $ filter valid games

main :: IO ()
main = do
    content <- getContents
    let games_strings = lines content
    let games = map read_game games_strings 
    let id_sum = valid_id_sum games
    putStrLn $ show id_sum

    
