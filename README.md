# anira-bela-examples

Examples to use anira on the Bela platform. There are two examples provided in this repository:

- `anira_bela_inference` is a simple example that demonstrates how to use anira to infer a model on the Bela platform.
- `anira_bela_benchmark` is a simple example that demonstrates how to use anira to benchmark a model on the Bela platform.

The examples can be activated with the following flags:
`-DANIRA_BELA_INFERENCE=ON` (default is ON)
`-DANIRA_BELA_BENCHMARK=ON` (default is OFF)

All examples are meant to be cross-compiled in the [xc-bela-container](https://github.com/pelinski/xc-bela-container). To do so, please follow closely the instructions in the README of the [xc-bela-container](https://github.com/pelinski/xc-bela-container) repository and make sure that the `libbelafull.so` has been copied to the `Bela/lib/` directory on your Bela board.

The cmake toolchain file to use with these examples is [Bela toolchain](Toolchain_Bela.cmake).

## Step by step guide

1. Clone this repository:

TODO