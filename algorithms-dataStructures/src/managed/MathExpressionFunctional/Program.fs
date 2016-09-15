open System
open System.Text
open System.Text.RegularExpressions
open System.Collections.Generic

let convertInfixExpressionToPostfix (expression: string) =
    let mutable operatorsStack           = new Stack<string>()
    let mutable postfixExpressionBuilder = new StringBuilder()

    let isNumber           maybeNumber       = Int32.TryParse maybeNumber
    let isOperator         maybeOperator     = maybeOperator = "+" || maybeOperator = "-" || maybeOperator = "*" || maybeOperator = "/"
    let isLeftParenthesis  maybeParenthesis  = maybeParenthesis = "("
    let isRightParenthesis maybeParenthesis  = maybeParenthesis = ")"

    let appendExpressionPartToPostFixExpression expressionPart =  
        if isOperator expressionPart || isLeftParenthesis expressionPart then
            operatorsStack.Push (" " + expressionPart) |> ignore
        else if isRightParenthesis expressionPart then
            while operatorsStack.Count > 0 && operatorsStack.Peek().Trim() <> "(" do
                postfixExpressionBuilder.Append(" " + operatorsStack.Pop().Trim())  |> ignore
        else 
            postfixExpressionBuilder.Append (expressionPart) |> ignore

    let parseExpressionPart                expressionPart     = appendExpressionPartToPostFixExpression expressionPart
    let addOperatorToExpression            (operator: string) = postfixExpressionBuilder.Append operator |> ignore 
    let isNotLeftParenthesis               (operator: string) = operator.Trim() <> "("
    let convertMultipleWhitespacesToSingle expression         = Regex.Replace(expression, @"\s+", " ")

    expression 
    |> Seq.map string 
    |> Seq.iter parseExpressionPart

    let restOperators = operatorsStack.ToArray() |> Array.filter isNotLeftParenthesis
    Array.iter addOperatorToExpression restOperators

    postfixExpressionBuilder
        .ToString()
        .Trim()
        .ToCharArray() |> 
         String.Concat |> 
         convertMultipleWhitespacesToSingle

let evaluatePostfixExpression (expression : string) =
    let solveExpressionPart results currentResult =  
     match (currentResult, results) with
     | "+", y::x::previousResults -> (x + y)::previousResults
     | "-", y::x::previousResults -> (x - y)::previousResults 
     | "*", y::x::previousResults -> (x * y)::previousResults
     | "/", y::x::previousResults -> (x / y)::previousResults
     | _ -> (float currentResult)::results
    (expression.Split(' ') |> Seq.map string |> Seq.fold solveExpressionPart []) |> List.head

[<EntryPoint>]
let main argv = 
   Console.ReadLine()              |>
   convertInfixExpressionToPostfix |> 
   evaluatePostfixExpression       |> 
   Console.WriteLine               |>
   Console.ReadKey                 |> 
   ignore
   0 