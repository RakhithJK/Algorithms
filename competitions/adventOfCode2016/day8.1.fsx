type RectangleDimensions = { X: int; Y : int}
type RotationOptions     = { Index : int; Offset : int }
type Command             = DrawRectangle of RectangleDimensions | RotateColumn of RotationOptions | RotateRow of RotationOptions

let drawTemplateCmd = "rect 3x2"
let rotateColumndTemplateCmd = "rotate column x=1 by 1"

let parseDrawRectangleCommand (commandText : string) =
    let commandParts = commandText.Split(' ', 'x')
    let x = int commandParts.[1] 
    let y = int commandParts.[2] 
    DrawRectangle { X = y; Y = x }
    
let parseRotationPart (commandText : string) =
    let withoutDelimiter = commandText.Replace("by", "")
    let commandParts = 
        withoutDelimiter.Split(' ', 'x', 'y', '=') |>
        Array.filter (fun commandPart -> commandPart.Length > 0)
    let index   = int commandParts.[2]
    let offset  = int commandParts.[3]

    { Index = index; Offset = offset }

let parseRotateColumnCommand (commandText : string) = RotateColumn (parseRotationPart commandText)
let parseRotateRowCommand (commandText : string) = RotateRow (parseRotationPart commandText)

let parseCommand (commandText : string) = 
    let isDrawCommand         = commandText.StartsWith "rect" 
    let isRotateColumnCommand = commandText.Contains   "column" 
    let isRotateRowCommand    = commandText.Contains   "row" 
    match isDrawCommand with
    | true -> parseDrawRectangleCommand commandText
    | false ->
        match isRotateColumnCommand with
        | true -> parseRotateColumnCommand commandText
        | false ->
            match isRotateRowCommand with
            | true -> parseRotateRowCommand commandText
            | false -> failwith "incorrect syntax"

let parseCommands (commandsText : string) = 
    commandsText.Split('\n', '\r') |>
    Array.filter (fun commandText -> commandText.Length > 0) |>
    Array.map parseCommand |>
    List.ofArray

let boolToPixel boolValue = 
    match boolValue with
    | true  -> '#'
    | false -> '.'
let isPixelOn boolValue = boolValue

let calculateNextPosition position maxPosition offset =
    let rec calculate currentOffset currentPosition =
        match currentOffset with
        | o when o < offset ->
            let nextPosition = currentPosition + 1
            match nextPosition with
            | p when p <= maxPosition -> calculate (currentOffset + 1) nextPosition
            | _ -> calculate (currentOffset + 1) 0
        | _ -> currentPosition
    calculate 0 position

let maxRowIndex = 5
let maxColumnIndex = 49
let screenGrid = Array2D.init (maxRowIndex + 1) (maxColumnIndex + 1) (fun i j -> false)

let drawRectangle dimensions =
    let auxArray = Array2D.init dimensions.X dimensions.Y (fun i j -> true)
    auxArray |> Array2D.iteri (fun i j pixel -> screenGrid.[i,j] <- pixel)

let rotateColumn options =
    let rotatedColumn = Array.init (maxRowIndex + 1) (fun rowIndex -> false)
    let columnToRotate = 
        let rec copyColumn currentRow columnValues =
            match currentRow with 
            | row when row <= maxRowIndex -> copyColumn (currentRow + 1) (columnValues@[screenGrid.[row, options.Index]])
            | _ -> columnValues 
        copyColumn 0 [] |> Array.ofList

    columnToRotate |> 
    Array.iteri (
        fun rowIndex pixel ->
            let nextRowPosition = calculateNextPosition rowIndex maxRowIndex options.Offset
            rotatedColumn.[nextRowPosition] <- pixel
    )
    rotatedColumn |> Array.iteri (fun rowIndex pixel -> screenGrid.[rowIndex, options.Index] <- pixel)

let rotateRow options =
    let rotatedRow = Array.init (maxColumnIndex + 1) (fun columnIndex -> false)
    let rowToRotate = 
        let rec copyRow currentColumn rowValues =
            match currentColumn with 
            | column when column <= maxColumnIndex -> copyRow (currentColumn + 1) (rowValues@[screenGrid.[options.Index, column]])
            | _ -> rowValues 
        copyRow 0 [] |> Array.ofList
    rowToRotate |> 
    Array.iteri (
        fun columnIndex pixel ->
            let nextColumnPosition = calculateNextPosition columnIndex maxColumnIndex options.Offset
            rotatedRow.[nextColumnPosition] <- pixel
    )
    rotatedRow |> Array.iteri (fun columnIndex pixel -> screenGrid.[options.Index, columnIndex] <- pixel)

let executeCommand command =
    match command with 
    | DrawRectangle dimensions -> drawRectangle dimensions
    | RotateColumn options     -> rotateColumn options
    | RotateRow options        -> rotateRow options

let executeCommands (commands : Command list) = 
    commands |>
    List.iter executeCommand
let solve (input : string) =
    let commands = parseCommands input
    executeCommands commands
    let test = screenGrid |> Seq.cast<bool> |> Seq.map boolToPixel |> List.ofSeq
    screenGrid |> Seq.cast<bool> |> Seq.filter isPixelOn |> Seq.length