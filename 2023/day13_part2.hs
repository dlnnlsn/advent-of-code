splitOn :: Eq a => a -> [a] -> [[a]]
splitOn _ [] = [[]]
splitOn delimiter (firstItem : rest) =
    if firstItem == delimiter then
        [] : splitOn delimiter rest
    else
        let firstList : remaining = splitOn delimiter rest in
            (firstItem : firstList) : remaining

segment :: Int -> [a] -> [a]
segment index items = if index * 2 >= length items then
        drop (index * 2 - length items) items
    else
        take (2 * index) items

mismatches :: Eq a => [a] -> [a] -> Int
mismatches items = length . filter id . zipWith (/=) items

verticalSmudges' :: Eq a => [a] -> Int
verticalSmudges' items = mismatches items (reverse items) `div` 2

verticalSmudges :: Eq a => Int -> [[a]] -> Int
verticalSmudges index = sum . map (verticalSmudges' . segment index)

horizontalSmudges :: Eq a => Int -> [[a]] -> Int
horizontalSmudges index items = sum (zipWith mismatches range (reverse range)) `div` 2
    where range = segment index items

isVerticalLineOfReflection :: Eq a => Int -> [[a]] -> Bool
isVerticalLineOfReflection index = (== 1) . verticalSmudges index

isHorizontalLineOfReflection :: Eq a => Int -> [[a]] -> Bool
isHorizontalLineOfReflection index = (== 1) . horizontalSmudges index

verticalScore :: Eq a => [[a]] -> Integer
verticalScore pattern = sum . map fromIntegral $ filter (`isVerticalLineOfReflection` pattern) [1 .. length (head pattern) - 1]

horizontalScore :: Eq a => [[a]] -> Integer
horizontalScore pattern = sum . map fromIntegral $ filter (`isHorizontalLineOfReflection` pattern) [1 .. length pattern - 1]

score :: Eq a => [[a]] -> Integer
score pattern = verticalScore pattern + 100 * horizontalScore pattern

main :: IO ()
main = do
    content <- getContents
    let contentLines = lines content
    let patterns = splitOn "" contentLines
    let totalScore = sum $ map score patterns
    print totalScore
