open System

[<EntryPoint>]
let main argv =
    let line = Console.ReadLine().Split()
    let a = Convert.ToInt64(line.[0])
    let b = Convert.ToInt64(line.[1])
    let c = Convert.ToInt64(line.[2])
    printfn "%d" (a+b+c)
    0
