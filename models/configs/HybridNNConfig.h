#ifndef ANIRA_HYBRIDNNCONFIG_H
#define ANIRA_HYBRIDNNCONFIG_H

#include <anira/anira.h>

static std::vector<anira::ModelData> model_data_hybridnn_config = {
#ifdef USE_LIBTORCH
        {MODELS_PATH + std::string("/GuitarLSTM-dynamic.pt"), anira::InferenceBackend::LIBTORCH},
#endif
#ifdef USE_ONNXRUNTIME
        {MODELS_PATH + std::string("/GuitarLSTM-libtorch-dynamic.onnx"), anira::InferenceBackend::ONNX},
#endif
#ifdef USE_TFLITE
        {MODELS_PATH + std::string("/GuitarLSTM-256.tflite"), anira::InferenceBackend::TFLITE},
#endif
};

static std::vector<anira::TensorShape> tensor_shape_hybridnn_config = {
#ifdef USE_LIBTORCH
        {{{256, 1, 150}}, {{256, 1}}, anira::InferenceBackend::LIBTORCH},
#endif
#ifdef USE_ONNXRUNTIME
        {{{256, 1, 150}}, {{256, 1}}, anira::InferenceBackend::ONNX},
#endif
#ifdef USE_TFLITE
        {{{256, 150, 1}}, {{256, 1}}, anira::InferenceBackend::TFLITE},
#endif
};

static anira::InferenceConfig hybridnn_config (
        model_data_hybridnn_config,
        tensor_shape_hybridnn_config,
        5.33f,
        0,
        2
);

#endif //ANIRA_HYBRIDNNCONFIG_H
