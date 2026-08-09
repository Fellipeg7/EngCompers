# EngCompers

Robô de sumô autônomo em modo **caçador (Hunter Mode)** — Arduino com shield de motor AFMotor.

## 🤖 Hardware

- **Shield:** AFMotor (L293D) — motores 1 (esq) e 2 (dir)
- **Ultrassônicos:** TRIG/ECHO esq (8/9) e dir (10/11)
- **Sensores de borda (IR):** A0 (esq) e A1 (dir)
- **Config:** limite de borda 500, distância de busca 60 cm

## 🎯 Comportamento

1. **Busca** — varre o dohyo com os ultrassônicos procurando o adversário
2. **Ataque** — ao encontrar alvo dentro do alcance, avança para empurrar
3. **Borda** — sensores IR evitam que o robô saia da arena (linha branca)

## 🛠️ Compilar

- IDE: Arduino IDE (ou PlatformIO)
- Dependências: `AFMotor.h` (Adafruit Motor Shield)
- Upload: `EngCompers/HunterMode.ino`

## 📁 Estrutura

```
EngCompers/
└── HunterMode.ino   → código principal do robô caçador
```
