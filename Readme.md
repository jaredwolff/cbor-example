# CBOR Example using Rust and C

This repository is an example from the blog post on [jaredwolff.com.](#)

## Building the Rust server

Already assuming you have Rust installed ([`rustup`](https://rustup.rs) is recommended)

Then run

```
cargo run
```

This will build and run your server. When ready you'll see:

```
cbor-example on  master [+?] is 📦 v0.1.0 via 🦀 v1.47.0 
❯ cargo run
    Finished dev [unoptimized + debuginfo] target(s) in 0.48s
     Running `target/debug/cbor-example`
```

## Building the C code

This code does use `cmake` please be sure to install before you continue. You should also have `curl` installed.

```
> brew install cmake curl
```

My example above uses [Homebrew for OSX](https://brew.sh). You should install per your OS recommended package manager. 

Once installed

```
> cd client
❯ cmake .
-- The C compiler identification is AppleClang 12.0.0.12000032
-- The CXX compiler identification is AppleClang 12.0.0.12000032
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/jaredwolff/Git/cbor-example/client
```

Then build it

```
❯ cmake --build .
Scanning dependencies of target client
[ 12%] Building C object CMakeFiles/client.dir/main.c.o
[ 25%] Building C object CMakeFiles/client.dir/src/telemetry_codec.c.o
[ 37%] Building C object CMakeFiles/client.dir/lib/QCBOR/src/UsefulBuf.c.o
[ 50%] Building C object CMakeFiles/client.dir/lib/QCBOR/src/ieee754.c.o
[ 62%] Building C object CMakeFiles/client.dir/lib/QCBOR/src/qcbor_decode.c.o
[ 75%] Building C object CMakeFiles/client.dir/lib/QCBOR/src/qcbor_encode.c.o
[ 87%] Building C object CMakeFiles/client.dir/lib/QCBOR/src/qcbor_err_to_str.c.o
[100%] Linking C executable client
[100%] Built target client
```

Then run it with:

```
> ❯ ./client 
Start of QCBOR Example
```

You should see an instant response on the other side:

```
Message from id: 1234
Telemetry: TelemetryData { version: "0.1.0", rssi: -49 }
```

Well done! You did it!