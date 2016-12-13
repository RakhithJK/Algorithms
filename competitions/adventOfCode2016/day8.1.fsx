type RectangleDimensions = { X: int; Y : int}
type RotationOptions     = { Index : int; Offset : int }
type Command             = DrawRectangle of RectangleDimensions | RotateColumn of RotationOptions | RotateRow of RotationOptions

let drawTemplateCmd = "rect 3x2"
let rotateColumndTemplateCmd = "rotate column x=1 by 1"

let parseDrawRectangleCommand (commandText : string) =
    let commandParts = commandText.Split(' ', 'x')
    let x = int commandText.[1] 
    let y = int commandText.[2] 
    DrawRectangle { X = x; Y = y}
    
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
let screenGrid = Array2D.init 6 50 (fun i j -> '.')