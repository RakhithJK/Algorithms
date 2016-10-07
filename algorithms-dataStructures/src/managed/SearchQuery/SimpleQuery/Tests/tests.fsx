#I __SOURCE_DIRECTORY__
#load "load-project.fsx"

open SimpleQuery.Query
open SimpleQuery.Parser

let implicitQueries = [
    "test123 test456 test";
    "  'test123' test456   test    test  "
]

let explicitQueries = [
    ":userName=Gabrijel Boduljak, :postType=NewsArticle";
    "   :userName=Gabrijel Boduljak,    :postType=NewsArticle ";
]

let mixedQueries = [
    "test123,  test 12312,  test, :userName=Gabrijel Boduljak, test46, :postType=Contest";
    "   :userName=Gabrijel Boduljak,  test123,  test,  :from=24.4.1999,  12312,  test, :postType=NewsArticle ";
]

let testImplicitQueries = printfn "Successfully parsed : \n %A" (List.map parse implicitQueries)
let testExplicitQueries = printfn "Successfully parsed : \n %A" (List.map parse explicitQueries)
let testMixedQueries    = printfn "Successfully parsed : \n %A" (List.map parse mixedQueries)

testImplicitQueries