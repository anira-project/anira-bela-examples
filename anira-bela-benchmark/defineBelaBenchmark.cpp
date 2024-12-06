#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <anira/anira.h>
#include <anira/benchmark.h>

#include "../models/configs/HybridNNConfig.h"
#include "../models/configs/HybridNNPrePostProcessor.h"
#include "../models/configs/SimpleGainConfig.h"

/* ============================================================ *
 * ========================= Configs ========================== *
 * ============================================================ */

#define NUM_ITERATIONS 5
#define NUM_REPETITIONS 2
#define BUFFER_SIZE 512
#define SAMPLE_RATE 44100

/* ============================================================ *
 * ================== BENCHMARK DEFINITIONS =================== *
 * ============================================================ */

typedef anira::benchmark::ProcessBlockFixture ProcessBlockFixture;

anira::InferenceConfig my_inference_config = gain_config;
anira::PrePostProcessor my_pp_processor(gain_config);
// anira::InferenceConfig my_inference_config = hybridnn_config;
// HybridNNPrePostProcessor my_pp_processor;

BENCHMARK_DEFINE_F(ProcessBlockFixture, BM_SIMPLE)(::benchmark::State& state) {

    // The buffer size return in get_buffer_size() is populated by state.range(0) param of the google benchmark
    anira::HostAudioConfig host_config = {(size_t) get_buffer_size(), SAMPLE_RATE};
    anira::InferenceBackend inference_backend = anira::InferenceBackend::ONNX;

    m_inference_handler = std::make_unique<anira::InferenceHandler>(my_pp_processor, my_inference_config);
    m_inference_handler->prepare(host_config);
    m_inference_handler->set_inference_backend(inference_backend);

    m_buffer = std::make_unique<anira::AudioBuffer<float>>(my_inference_config.m_num_audio_channels[anira::Input], host_config.m_host_buffer_size);

    initialize_repetition(my_inference_config, host_config, inference_backend);

    for (auto _ : state) {
        push_random_samples_in_buffer(host_config);

        initialize_iteration();

        auto start = std::chrono::high_resolution_clock::now();
        
        m_inference_handler->process(m_buffer->get_array_of_write_pointers(), get_buffer_size());

        // Using yield here is important to let the inference thread run as the Bela board is a single-core system
        while (!buffer_processed()) {
            std::this_thread::yield();
        }
        
        auto end = std::chrono::high_resolution_clock::now();

        interation_step(start, end, state);
    }
    repetition_step();
}

// /* ============================================================ *
//  * ================== BENCHMARK REGISTRATION ================== *
//  * ============================================================ */

BENCHMARK_REGISTER_F(ProcessBlockFixture, BM_SIMPLE)
->Unit(benchmark::kMillisecond)
->Iterations(NUM_ITERATIONS)->Repetitions(NUM_REPETITIONS)
->Arg(BUFFER_SIZE)
->UseManualTime();
