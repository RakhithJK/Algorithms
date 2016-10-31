open System
open System.Collections.Generic
open System.Linq

type position = { row : int; column: int }
type substep  = { startPosition: position; endPosition: position; duration: int }
type step     = { substeps: substep list; startTime: int; duration: int }

let loadMapOfNColumns() = 
    let loadMapLine rowIndex = Console.ReadLine()
    let map = [0..9] |> List.map (fun rowIndex -> loadMapLine())
    map

let loopUntil predicate sourceList = 
    let rec loop accumulator list =
        match list with 
        | head::tail when predicate head -> List.rev accumulator, head::tail
        | head::tail -> loop (head::accumulator) tail
        | [] -> sourceList, []
        
    loop [] sourceList

let mutable currentMap = [|
    ".....XX...X";
    "....XX...XX";
    "...XX...XX.";
    "...........";
    "....XXX....";
    "...........";
    ".....X.....";
    "....XX...X.";
    "...XX...XX.";
    "...X...XX.."
    |]

let rowsContainer      = new Dictionary<int, char list>()
let getRowFromIndex ix = 
    let getRowAndCacheIt() =    
        let row = (List.ofArray (currentMap.[ix].ToCharArray()))
        rowsContainer.Add(ix, row)
        row

    let existsInCache = rowsContainer.ContainsKey(ix)
    match existsInCache with 
    | true  -> rowsContainer.[ix]
    | false -> getRowAndCacheIt()

let isTargetInMap targetRow targetColumn maxColumnIndex = 
        targetRow    <= 9              && targetRow     >= 0  && 
        targetColumn <= maxColumnIndex && targetColumn  >= 0

let isAboveCeilingOrObstacle elementPosition maxColumnIndex = 
    let targetRow    = elementPosition.row    - 1
    let targetColumn = elementPosition.column + 1 
   
    let checkInMap() =
       let maybeCeilingRow  = List.ofArray (currentMap.[targetRow].ToCharArray())
       elementPosition.row  = 0 || maybeCeilingRow.[targetColumn] = 'X'

    match isTargetInMap targetRow targetColumn maxColumnIndex  with 
       | true  -> checkInMap()
       | false -> true

let isBelowFloorOrObstacle elementPosition maxColumnIndex =
    let targetRow    = elementPosition.row + 1
    let targetColumn = elementPosition.column + 1 

    let checkInMap() =
        let maybeFloorRow   = List.ofArray (currentMap.[elementPosition.row + 1].ToCharArray())
        elementPosition.row = 9 || maybeFloorRow.[elementPosition.column + 1] = 'X'

    match isTargetInMap targetRow targetColumn maxColumnIndex  with 
       | true  -> checkInMap()
       | false -> true

let findStoppingPositionAbove searchRowIndex currentPosition = 
    let row                     = getRowFromIndex searchRowIndex
    let doesRowContainObstacles = row.Any(fun x -> x = 'X')

    let findAscendingPosition()   = 
        let stopping = 
            row
            |> List.filter (fun el -> el = '.')
            |> List.mapi   (fun columnIx el -> { row = currentPosition.row - 1; column = columnIx })
            |> List.find   (fun el -> el.row = currentPosition.row - 1 && el.column = currentPosition.column + 1)
        stopping

    let endPosition = 
        match doesRowContainObstacles with 
        | true  -> findAscendingPosition()
        | false -> { row = currentPosition.row - 1; column = currentPosition.column + 1 }

    let substep = { startPosition = currentPosition; endPosition = endPosition; duration = Math.Abs (endPosition.row - currentPosition.row) }
    substep

let findPositionBelow searchRowIndex currentPosition = 
    let row                     = getRowFromIndex searchRowIndex
    let doesRowContainObstacles = row.Any(fun x -> x = 'X')

    let findDescendingPosition()  = 
        let stopping = 
            row
            |> List.filter (fun el          -> el = '.')
            |> List.mapi   (fun columnIx el -> { row = currentPosition.row + 1; column = columnIx })
            |> List.find   (fun el          -> el.row = currentPosition.row + 1 && el.column = currentPosition.column + 1)
        stopping

    let endPosition =
        match doesRowContainObstacles with 
        | true  -> findDescendingPosition()
        | false -> { row = currentPosition.row + 1; column = currentPosition.column + 1 }

    let substep = { startPosition = currentPosition; endPosition = endPosition; duration = Math.Abs (endPosition.row - currentPosition.row) }
    substep
   
let canAscend  position maxColumnIndex = not (isAboveCeilingOrObstacle position maxColumnIndex)
let canDescend position maxColumnIndex = not (isBelowFloorOrObstacle position maxColumnIndex)

let goRightOrAscend searchRowIndex currentPosition maxColumnIndex =
    let substep = findStoppingPositionAbove searchRowIndex currentPosition
    substep, (canAscend substep.endPosition maxColumnIndex)

let goRightOrDescend searchRowIndex currentPosition maxColumnIndex =
    let substep = findPositionBelow searchRowIndex currentPosition
    substep, (canDescend substep.endPosition maxColumnIndex)

let goRight currentPosition currentSearchRow maxColumnIndex =
    let row               = getRowFromIndex currentSearchRow
    let doesRowContainObstacles = row.Any(fun x -> x = 'X')
    let unexploredRowPart = row.[currentPosition.column .. maxColumnIndex]
    let canMoves          = (loopUntil (fun el -> el = 'X') unexploredRowPart)

    let takeElementIfPositionAfterCurrentPosition ix el = 
                match ix with 
                | ix when ix > currentPosition.column -> Some el
                | _                                   -> None

    let horizontalMoves  =
        (fst canMoves) 
            |> List.mapi    (takeElementIfPositionAfterCurrentPosition) 
            |> List.filter  (fun option -> option.IsSome)
            |> List.map     (fun el -> el.Value)

    let findAscendingPosition = 
        let stopping = 
            horizontalMoves
            |> List.filter (fun el -> el = '.')
            |> List.mapi   (fun columnIx el -> { row = currentSearchRow; column = columnIx }) 
            |> List.sortByDescending (fun el -> el.column) 
            |> List.take 1
            |> List.exactlyOne

        stopping

    let endPosition = 
        match doesRowContainObstacles with 
        | true  -> findAscendingPosition
        | false -> { row = currentPosition.row - 1; column = currentPosition.column + 1 }

    let substep = { startPosition = currentPosition; endPosition = endPosition; duration = Math.Abs (endPosition.row - currentPosition.row) }
    substep, (canAscend substep.endPosition maxColumnIndex)    

  
    
let solve map columnsCount = 
    let mutable stepsCount        = 0;
    let mutable maxColumnIndex    = columnsCount - 1;
    let mutable currentPosition   = { row = 9; column = 0 }
    let mutable currentSearchRow  = 9
    let mutable currentTimestamp  = 0
    let mutable previousTimestamp = 1

    let maxColumnIndex = columnsCount - 1
    let operations = new Queue<substep>()
    let steps      = new Queue<step>()

    while currentPosition.column <> maxColumnIndex do
        let mutable shouldAscend  = canAscend  currentPosition maxColumnIndex
        let mutable shouldDescend = canDescend currentPosition maxColumnIndex

        if (not shouldAscend && not shouldDescend || stepsCount = 0 && currentPosition.column <> maxColumnIndex) then
            let horizontalMoves   = (goRight currentPosition currentSearchRow maxColumnIndex)
            currentTimestamp <- 
                match ((fst horizontalMoves).duration) with
                | 0 -> currentTimestamp + 1 // horizontalMove
                | _ -> currentTimestamp + ((fst horizontalMoves).duration)
            currentPosition       <- (fst horizontalMoves).endPosition

        while shouldAscend = true && shouldDescend = false && currentPosition.column <> maxColumnIndex do
            let performAscendOrGoRight = goRightOrAscend currentSearchRow currentPosition maxColumnIndex
            operations.Enqueue (fst performAscendOrGoRight)
            currentPosition  <- ((fst performAscendOrGoRight).endPosition)
            shouldAscend     <- (snd performAscendOrGoRight)
            shouldDescend    <- (not shouldAscend)

            currentSearchRow <- 
                match shouldAscend with
                | true  -> currentSearchRow - 1
                | false -> currentSearchRow + 1

            currentTimestamp <- 
                match ((fst performAscendOrGoRight).duration) with
                | 0 -> currentTimestamp + 1 // horizontalMove
                | _ -> currentTimestamp + ((fst performAscendOrGoRight).duration)

            if((fst performAscendOrGoRight).duration = 0) then
                operations.Dequeue() |> ignore
               
        stepsCount <- stepsCount + 1
        steps.Enqueue({ startTime = previousTimestamp; duration = currentTimestamp - previousTimestamp; substeps = List.ofArray (operations.ToArray()) })
        operations.Clear()

        previousTimestamp <- currentTimestamp

        currentSearchRow <- 
            match shouldAscend with
            | true  -> currentPosition.row - 1
            | false -> currentPosition.row + 1

        while shouldAscend = false && shouldDescend = true && currentPosition.column <> maxColumnIndex do
            let performDescendOrGoRight = goRightOrDescend currentSearchRow currentPosition maxColumnIndex
            operations.Enqueue (fst performDescendOrGoRight)
            currentPosition  <- ((fst performDescendOrGoRight).endPosition)
            shouldDescend    <- (snd performDescendOrGoRight)
            shouldAscend     <- (not shouldDescend)

            currentSearchRow <-
                match shouldDescend with
                | true  -> currentSearchRow + 1
                | false -> currentSearchRow - 1

            currentTimestamp <- 
                match ((fst performDescendOrGoRight).duration) with
                | 0 -> currentTimestamp + 1 // horizontalMove
                | _ -> currentTimestamp + ((fst performDescendOrGoRight).duration)

        previousTimestamp <- currentTimestamp

        currentSearchRow <- 
            match shouldAscend with
            | true  -> currentPosition.row - 1
            | false -> currentPosition.row + 1

    List.ofArray (steps.ToArray())

[<EntryPoint>]
let main argv = 
    let numberOfColumns = Int32.Parse(Console.ReadLine())
    let map             = loadMapOfNColumns()
    currentMap          <- Array.ofList map

    let steps = solve map (numberOfColumns - 1) 
    printfn "%A" steps.Length
    steps |> List.iter (fun step -> printfn "%A %A" step.startTime step.duration)
         
    Console.ReadKey() |> ignore
    0 