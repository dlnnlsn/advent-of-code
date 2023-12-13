splitOn :: Eq a => a -> [a] -> [[a]]
splitOn _ [] = [[]]
splitOn delimiter (firstItem : rest) =
    if firstItem == delimiter then
        [] : splitOn delimiter rest
    else
        let firstList : remaining = splitOn delimiter rest in
            (firstItem : firstList) : remaining

isLineOfReflection :: Eq a => Int -> [a] -> Bool
isLineOfReflection index items =
    and $ zipWith (==) segment (reverse segment)
    where
        segment = if index * 2 >= length items then
            drop (index * 2 - length items) items
        else
            take (2 * index) items

isVerticalLineOfReflection :: Eq a => Int -> [[a]] -> Bool
isVerticalLineOfReflection = all . isLineOfReflection

isHorizontalLineOfReflection :: Eq a => Int -> [[a]] -> Bool
isHorizontalLineOfReflection = isLineOfReflection

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
