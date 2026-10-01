/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <cmath>
#include "output_handler.h"
#include "constants.h"
#include "tensorflow/lite/micro/micro_log.h"

// Avaliacao deterministica da curva; nao substitui um dataset de teste.
void HandleOutput(float x_value, float y_value) {
  static int sample = 0;
  static float absolute_sum = 0;
  static float squared_sum = 0;
  static float maximum = 0;
  const float reference = std::sin(x_value);
  const float error = std::fabs(y_value - reference);
  absolute_sum += error;
  squared_sum += error * error;
  if (error > maximum) maximum = error;
  ++sample;
  MicroPrintf("%d,%.4f,%.4f,%.4f,%.4f", sample,
              static_cast<double>(x_value), static_cast<double>(y_value),
              static_cast<double>(reference), static_cast<double>(error));
  if (sample == kInferencesPerCycle) {
    MicroPrintf("CICLO CONCLUIDO | MAE=%.5f | RMSE=%.5f | erro_max=%.5f",
                static_cast<double>(absolute_sum / sample),
                static_cast<double>(std::sqrt(squared_sum / sample)),
                static_cast<double>(maximum));
    sample = 0;
    absolute_sum = squared_sum = maximum = 0;
  }
}
