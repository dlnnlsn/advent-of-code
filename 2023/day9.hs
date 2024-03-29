differences :: [Integer] -> [Integer]
differences list = zipWith (-) (tail list) list

predict :: [Integer] -> Integer
predict list =
    if all (== 0) (differences list) then
        head list
    else
        last list + predict (differences list)

predict_backwards :: [Integer] -> Integer
predict_backwards list =
    if all (== 0) (differences list) then
        head list
    else
        head list - predict_backwards (differences list)

read_sequence :: String -> [Integer]
read_sequence = map read . words

main :: IO ()
main = do
    content <- getContents
    let sequence_strings = lines content
    let sequences = map read_sequence sequence_strings
    let predictions = map predict sequences
    putStrLn $ show $ sum predictions
    let backwards_predictions = map predict_backwards sequences
    putStrLn $ show $ sum backwards_predictions
