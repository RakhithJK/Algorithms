module wave_packager

open System
open System.IO
open System.Text

let private getASCIIBytes (asciiString: string) = Encoding.ASCII.GetBytes asciiString

let packToStream (samples : int16[]) =
    let stream = new MemoryStream()
    let writer = new BinaryWriter(stream, Encoding.ASCII)
    let dataLength = Array.length samples * 2

    writer.Write (getASCIIBytes "RIFF")
    writer.Write (Array.length samples)
    writer.Write (getASCIIBytes "WAVE")
    writer.Write (getASCIIBytes "fmt ")
    writer.Write (16)
    writer.Write (1s)
    writer.Write (1s)
    writer.Write (44100)
    writer.Write (44100 * 16 / 8)
    writer.Write (2s)
    writer.Write (16s)

    writer.Write (getASCIIBytes "data")
    writer.Write (dataLength)

    let data:byte[] = Array.zeroCreate dataLength
    Buffer.BlockCopy (samples, 0, data, 0, data.Length)
    writer.Write data
    stream

let writeStreamToFile fileName (ms : MemoryStream) = 
    use fs = new FileStream(Path.Combine(__SOURCE_DIRECTORY__, fileName), FileMode.Create)
    ms.WriteTo fs

Array.ofSeq