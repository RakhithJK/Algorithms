type UnorderedMaxPQ(capacity) =
    let elementsHolder           = Array.zeroCreate(capacity)
    let mutable lastElementIndex = -1;

    member this.isEmpty = lastElementIndex = -1
    member this.size    = lastElementIndex + 1
    member this.insert element =
        lastElementIndex <- lastElementIndex + 1 
        elementsHolder.[lastElementIndex] <- element
    member this.deleteMax =
        // find min
        let mutable maxElementIndex = 0;
        for i in [1..lastElementIndex] do   
            if (elementsHolder.[i] < elementsHolder.[maxElementIndex]) then
                maxElementIndex <- i

        let maxElement = elementsHolder.[maxElementIndex]

        //exchange minElement with lastElementIndex - 1

        let temp = elementsHolder.[lastElementIndex]
        elementsHolder.[lastElementIndex] <- elementsHolder.[maxElementIndex]
        elementsHolder.[maxElementIndex]  <- temp

        // delete lastElement
        lastElementIndex <- lastElementIndex - 1
        maxElement


let pq = UnorderedMaxPQ(5)

pq.insert 1
pq.insert 4
pq.insert 0
pq.insert 3
pq.insert 2


printfn "%A" pq.deleteMax
printfn "%A" pq.deleteMax
printfn "%A" pq.deleteMax
printfn "%A" pq.deleteMax
printfn "%A" pq.deleteMax
