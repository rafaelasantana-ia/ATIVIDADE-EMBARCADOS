"""Converte um .tflite nos simbolos usados pelo firmware, sem depender de xxd."""
import argparse
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("entrada", type=Path)
parser.add_argument("saida", type=Path)
args = parser.parse_args()
data = args.entrada.read_bytes()
if data[4:8] != b"TFL3":
    parser.error("O arquivo nao possui identificador TFL3.")
rows = ["  " + ", ".join(f"0x{b:02x}" for b in data[i:i + 12]) + ","
        for i in range(0, len(data), 12)]
args.saida.write_text('#include "model.h"\n\nalignas(16) const unsigned char g_model[] = {\n'
                     + "\n".join(rows) + '\n};\nconst int g_model_len = sizeof(g_model);\n',
                     encoding="utf-8")
print(f"Gerados {len(data)} bytes em {args.saida}")
