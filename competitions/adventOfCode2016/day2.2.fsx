let input = "LLLUDRDLLULDUDLLRLUDURULDURRRRLLURLDLDDDULLDDUDLRDLRDUURRDUUDLLRUUDDLULURDLRDUUDUDRURULLLLDRULDDLRDDRDLRDDLURLDDUDLLUUDLRDDDDLULUUURRDLUUDDLULLURRRDULLUDUDRDRDDRLDLLRLRDDDRDLULLUULDLLLRRDDUURUURDLLDRRDDLRULDLLDRLLUDRRDLUUULDLURLLDDURRUULLLLLRLUDLDDLLLURRRDUDULRULULDDLLDLRDDDUULRLRDUURLURRUDDURRUUDUDLDDLDULDDDDDULRULRDLRLDLRDLDDLUDRDUUDLDUDUDLLLRLUUDRUDDDRDRURRLLLDLUULDUULRDLULLUURLDRRRLDRLUDRRURLDULULDRUDDULLLDRDLLULUDDDDRDRULDULRRRRDDRULDLRDU
DLDDRRDLLDUURRLULLLLRDRLUDURLDRRDURRRRUUDDUDRRDDDRRLDDLDDLURDLDRLUDULDUDUUDDDLLULRRLLUDULLLUULDDRDDUDUUDULURULULLDRLRUURDRDDLRRUDRUULLLLURRUDRDULDDRURRURLLLLLRLLLRLLUDUDLRDLULDUDLULLLUUDLLDDDUDUDLLRRDLRDLLLRRLRUDRDUDRURLUUURULLDDDDLLURDULURRLLLRLRRULLRRRLUUULLLLRLRDUURRDUURLLLDRDURRRULDDUDRRDLRLDLLRUDDLLUDRLLUUDRLLLLLLUDLURLLRUDRUUUULDLUDULLDDDDRLURUURDDDURRRLRLUDUUDURDDDDRRLRDLURDDLLULDRDDURLLURULUUUUURDUUULDRRLLURRRRRLDDUULLRULLDLDLDLRRRDRLDRUUD
RLDRRRURULDLUDLDUDLLDUUURRDUDDURULLRRDDULUUDRRRULRUURRRLUUULRDRUDRRLLRLURDLDRDRDLLUDRUULRUDRUDDRURLRLURRDDRRURUUDRRDDRURURUDUUUDUDRRLRDRUUURLLUUUDLRUUDDRDDDDLDRLRDUDDULDDLRLLRURLLURLDDLDLDDULLDDUUURDLRUDUUDLDURDDRUULDRDDRDDDUUUDRDRDDRRDRRDLRDRURDUDDLUUUDULLUULULULRDRUUDDURURDRRRRLUDLDUDURLDRURDLLUUUDLRRDRRURDDULULURLDUDDLUDLDDLLRLDULLULULURUURLDULUDLLUUDLDDULDRRDDUULLUDLDLLRDRDURDDURDDURLDDURUURLLRURURUDDURRDRLRLDDUUDUULRDLLURRRRULURULDUDUDDUDDRLLLDLURDUURUURLUULRRLDLULDDRLDDUURULURUDRD
URLDDRLLRRLDRLLRRURURURDDLRRRUUUURULRRUUDLUDRULLDLRUDDLULRUULDULURLLRLLUDDUDLURDRRRRLURULRURRURRULRRRULDLLDDLRLUDULUUUDDUDDRRDDDDUULRRLDRRULULRDUURRLDDRDULDURUDUDDLDLLURDDLDDRUDUUUDUUURDLDUDUUULLDLRDULRRRDLLURLDLLULRDDULULURLRLUULRLLLDDDUDLLDLURRRULRDUDDLULUDRUDDURULRLRUDDURLLURULLURDRULDUDLDULRRDLDURLUURRDDUDDUDRURUDDURRUUDURUULLLLDDRDDDDDULUUDDURRULLDRRLRRRRRDDRUUDDDURDRDRUDDUULDUDRRDRULUURLURLUDUDULDDRDULDLRUUDLLLRRLRDRDDUUULRDUDLUDLURRDUURDULDRLLDRDULDUDUULRLLDLRLDLUUDLRUULDUUULDLRLRLUULLLLRLRDUDRUUDURLDUDRRURLRUDRRLRDDLRDDLDDUDDDRLRLLRLUUURLURRRLULRLLDRLRDDRRDRL
DLLLLLLRLRDRUDLRLLRLDLRURRUURLDLDDDDDUDUULLLLRRLRRDUUDUDLULLRRDULUDLLULURLRULURUULRLURDUDLUDULULUUURLRUDULURULRURULURLRLDRRRRLUDLLDULLDDLLULUURRULRDURDUUDDDURRUDLLLLRLDLUDDULLDUDDURURURRRRULDULULUDDUUDRLRLLLDLLLUUUURUDUUDLDLLRLRDDUULLUURLDDLRRDRLULDLULRULDLDURLULUURRRUDLLRDLUDDULRULULUDDURDLUUURDUUURDUDURLUUDRLUDRULUDDRRDLUUDLLLRDDDDDDLDURDDLDRDLUUDRULLUDRDLDULLULDDRUUDRRLRURRUULLRLRDUUURRDRRDULDDULUUDDURLULRLRURLLRRR"

let testInput = "ULL
RRDDD
LURDL
UUUUD"

open System

type Direction = Up | Down | Left | Right 
type SingleNumberInstructions = { Directions : Direction list }
type MultipleNumberInstructions = { Instructions : SingleNumberInstructions list }
type MultipleNumberInstructionsAccumulator = { CurrentPosition : int * int; CalculatedNumbers : char list } 

let parseDirection directionAsChar = 
    match directionAsChar with 
    | 'U' -> Up
    | 'D' -> Down
    | 'L' -> Left
    | 'R' -> Right
    | _ -> failwith "unknown direction"

let parseSingleNumberInstructions (singleNumberInstructionsAsString : string) = { Directions = singleNumberInstructionsAsString.ToCharArray() |> Array.map parseDirection |> List.ofArray }
let parseMultipleNumberInstructions (input : string) = { Instructions = input.Split('\n', '\r') |> Array.map parseSingleNumberInstructions |> List.ofArray }

let mutable currentNumber = 0

let seedFunc i j = 
    currentNumber <- currentNumber + 1
    currentNumber

let keypad = [|
    [|'X'; 'X'; '1'; 'X'; 'X'|]; 
    [|'X'; '2'; '3'; '4'; 'X'|]; 
    [|'5'; '6'; '7'; '8'; '9'|]; 
    [|'X'; 'A'; 'B'; 'C'; 'X'|]; 
    [|'X'; 'X'; 'D'; 'X'; 'X'|]; 
|]
let startKeyPosition = 2,0

let isInKeypad x y = x >= 0 && y >= 0 && x <= 4 && y <= 4
let canMove x y =
    let isInKeypad = isInKeypad y x

    match isInKeypad with 
    | true -> 
         let nextChar = keypad.[x].[y]
         let isDigit = keypad.[x].[y] <> 'X'
         isDigit
    | false -> false
    
    
let moveTo direction currentPosition =
    let nextPosition = 
        match direction with 
        | Up   ->  fst currentPosition - 1, snd currentPosition 
        | Down -> fst currentPosition + 1, snd currentPosition 
        | Right -> fst currentPosition, snd currentPosition + 1
        | Left -> fst currentPosition, snd currentPosition - 1

    match (canMove (fst nextPosition) (snd nextPosition)) with 
    | true  -> nextPosition
    | false -> currentPosition

let computeSingleNumber singleNumberInstructions currentPosition  =
    let numberPosition = singleNumberInstructions.Directions |> List.fold (fun previousPosition instruction -> moveTo instruction previousPosition) currentPosition
    numberPosition, keypad.[fst numberPosition].[snd numberPosition]

let computeBathroomCode (multipleNumberInstructions : MultipleNumberInstructions) =
    let sd accumulator instructions =
        let computedNumber = computeSingleNumber instructions accumulator.CurrentPosition
        { CurrentPosition = fst computedNumber; CalculatedNumbers = (snd computedNumber) :: accumulator.CalculatedNumbers }

    multipleNumberInstructions.Instructions |> List.filter (fun instructions -> instructions.Directions.Length > 0) |> List.fold sd { CurrentPosition = startKeyPosition; CalculatedNumbers = []}

let solve (input : string) =
    let formNumberFromDigits computationResult = 
        let digits = List.rev computationResult.CalculatedNumbers 
        digits |> List.fold (fun number digit -> number + string digit) ""
        
    parseMultipleNumberInstructions input |> computeBathroomCode |> formNumberFromDigits

solve input