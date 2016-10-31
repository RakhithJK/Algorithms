type graph(verticesCount) = 
    let mutable connectionsHolder  = Array.init verticesCount (fun index -> index) 
    let mutable modificationsCount = 0 
    member this.elementsCount      = verticesCount
    member this.areConnected p q   = connectionsHolder.[p] = connectionsHolder.[q]
    member this.connect      p q   = 
        let performConnecting = 
            let pValue = connectionsHolder.[p]
            let qValue = connectionsHolder.[q]

            connectionsHolder <-  
                connectionsHolder |> 
                Array.map(
                    fun elementValue ->
                        match elementValue with 
                        | value when value = pValue -> qValue
                        | _ -> elementValue
                )
            modificationsCount <- modificationsCount + 1
            connectionsHolder

        let arePandQConnected = this.areConnected p q
        match arePandQConnected with
        | true  -> connectionsHolder
        | false -> performConnecting 
        
let graph  = graph 10
let state1 = graph.connect 4 3
let state2 = graph.connect 3 8
let state3 = graph.connect 6 5
let state4 = graph.connect 9 4
let state5 = graph.connect 2 1

let are8and9Connected = graph.areConnected 8 9
let are5and0Connected = graph.areConnected 5 0