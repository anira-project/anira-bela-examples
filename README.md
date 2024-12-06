# anira-bela-examples

Examples to use anira on the Bela platform. There are two examples provided in this repository:

- [anira-bela-inference](./anira-bela-inference/) is a simple example that demonstrates how to use anira to infer a model on the Bela platform.
- [anira-bela-benchmark](./anira-bela-benchmark/) is a simple example that demonstrates how to use anira to benchmark a model on the Bela platform.

All examples are meant to be cross-compiled in the [xc-bela-container](https://github.com/pelinski/xc-bela-container). To set up the environment, please follow closely the instructions in the README of the [xc-bela-container](https://github.com/pelinski/xc-bela-container) repository and make sure that the `libbelafull.so` has been copied to the `/root/Bela/lib/` directory on your Bela board.

The cmake toolchain file to use with these examples is [Toolchain_Bela.cmake](./Toolchain_Bela.cmake).

> **Note:** More information about the anira library can be found in the [anira repository](https://github.com/anira-project/anira). An extensive usage guide is provided [here](https://github.com/anira-project/anira/blob/main/docs/anira-usage.md) and more information about benchmarks with anira can be found [here](https://github.com/anira-project/anira/blob/main/docs/benchmark-usage.md).

## Options

The examples can be activated with the following flags:

- `DANIRA_BELA_INFERENCE=ON` (default is `ON`)
- `DANIRA_BELA_BENCHMARK=ON` (default is `ON`)

When the anira library is added as a subdirectory (default see [CMakeLists.txt](./CMakeLists.txt) section Setting up anira), the following options can be set:

- `-DANIRA_WITH_INSTALL=ON` (default is `ON`)

This will make sure that the anira library is bundeled with the examples when installing them.

If you don't want to bundle the anira library with the install artifacts, set this option to `OFF`. This requires that the anira library is installed on the bela board under the path `/root/anira`. This works by simply copying the [latest release](https://github.com/anira-project/anira/releases/latest) of the anira library there. If want to use the [anira-bela-benchmark](./anira-bela-benchmark/) example, you need to build the anira library yourself with the `ANIRA_WITH_BENCHMARK=ON` option, install and then copy the library to the bela board.

## Step by step guide (using anira as a subdirectory)

Clone this repository

```bash
git clone --recursive git@github.com:anira-project/anira-bela-examples.git
```

Start the [xc-bela-container](https://github.com/pelinski/xc-bela-container)

Before doing so make sure you have pulled the image, the right ip address of your Bela board and that the `libbelafull.so` has been copied to the `Bela/lib/` directory on your Bela board (more information [xc-bela-container](https://github.com/pelinski/xc-bela-container)). We mount the anira-bela-examples directory to the container to be able to cross-compile the examples.

```bash
docker run -it --name bela-container -e BBB_HOSTNAME=192.168.7.2 -v path/to/anira-bela-examples:/sysroot/root/anira-bela-examples pelinski/xc-bela-container:v1.1.0
```

Inside the container crosscompile the examples and install them. Then exit the container.

```bash
# You might first need to get the ownership of the anira-bela-examples directory
chown -R root:root /sysroot/root/anira-bela-examples
cd anira-bela-examples
cmake -B build -DCMAKE_TOOLCHAIN_FILE=Toolchain_Bela.cmake
cmake --build build
cmake --install build
exit
```

With the Bela board connected copy the install artifacts to the Bela board.

```bash
rsync -avzP path/to/anira-bela-examples/anira-bela-examples-0.0.1/ root@192.168.7.2:~/anira-bela-examples-0.0.1/
```

Copy the models to the Bela board. By default the model path is set to `/root/models/`. You can change this in the [CMakeLists.txt](./CMakeLists.txt) file.

```bash
scp -r path/to/anira-bela-examples/models/ root@192.168.7.2:/root/models/
```

For the [anira-bela-inference](./anira-bela-inference/) example, copy the audio file to the Bela board. By default the audio file path is set to `/root/audio/`. You can change this in the [CMakeLists.txt](./anira-bela-inference/CMakeLists.txt) of the [anira-bela-inference](./anira-bela-inference/) example.

```bash
scp -r path/to/anira-bela-examples/audio/ root@192.168.7.2:/root/audio/
```

SSH into the Bela board and run the examples.

```bash
ssh root@192.168.7.2
./anira-bela-examples-0.0.1/bin/anira-bela-inference
./anira-bela-examples-0.0.1/bin/anira-bela-benchmark
```

(Optional) Exit the Bela board and get back the ownership of the anira-bela-examples directory.

```bash
exit
sudo chown -R $USER:$USER path/to/anira-bela-examples
```
