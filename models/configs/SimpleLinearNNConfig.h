#ifndef ANIRA_SIMPLELINEARNNCONFIG_H
#define ANIRA_SIMPLELINEARNNCONFIG_H

#include <anira/anira.h>

static std::vector<anira::ModelData> model_data_linear_config = {
#ifdef USE_LIBTORCH
    {MODELS_PATH + std::string("/simple_linear_network.pt"), anira::InferenceBackend::LIBTORCH},
#endif
#ifdef USE_ONNXRUNTIME
    {MODELS_PATH + std::string("/simple_linear_network.onnx"), anira::InferenceBackend::ONNX},
#endif
#ifdef USE_TFLITE
    {MODELS_PATH + std::string("/simple_linear_network.tflite"), anira::InferenceBackend::TFLITE},
#endif
};

static std::vector<anira::TensorShape> tensor_shape_linear_config = {
    {{{1, 32}}, {{1, 32}}}, // When no backend is specified, the tensor shape is seen as universal for all backends
};

static anira::InferenceConfig simple_linear_nn_config (
    model_data_linear_config,
    tensor_shape_linear_config,
    5.f,
    0,
    1
);

#endif //ANIRA_SIMPLELINEARNNCONFIG_H
