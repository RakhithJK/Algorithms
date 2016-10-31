type graph(verticesCount) = 
    let mutable connectionsHolder          = Array.init verticesCount (fun index -> index)   
    let mutable modificationsCount         = 0 
    member this.elementsCount              = verticesCount
    member this.findVertexRoot vertexIndex =
        let rec searchForRootRecursively maybeRootIndex =
            let value = connectionsHolder.[maybeRootIndex]
            match maybeRootIndex with 
            | index when index = value -> value
            | _ -> searchForRootRecursively connectionsHolder.[maybeRootIndex]
        searchForRootRecursively vertexIndex

    member this.areConnected p q = this.findVertexRoot p = this.findVertexRoot q
    member this.connect      p q = 
        let performConnection =
            let pRoot = this.findVertexRoot p
            let qRoot = this.findVertexRoot q

            connectionsHolder.[pRoot] <- qRoot
            modificationsCount <- modificationsCount + 1
            connectionsHolder
        match this.areConnected p q with
        | true  -> connectionsHolder
        | false -> performConnection 
            
let graph  = graph 10
let state1 = graph.connect 4 3
let state2 = graph.connect 3 8
let state3 = graph.connect 6 5
let state4 = graph.connect 9 4
let state5 = graph.connect 2 1

let are8and9Connected = graph.areConnected 8 9
let are5and0Connected = graph.areConnected 5 0