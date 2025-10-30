# Geração de Bits Aleatórios com Arduino Uno

O projeto utiliza o ruído eletrônico captado pela porta analógica do Arduino Uno como fonte de entropia para gerar bits aleatórios. A abordagem combina técnicas físicas e matemáticas para maximizar a imprevisibilidade dos dados gerados, mesmo em um ambiente com recursos limitados.

Funcionamento:

1. Captura de ruído analógico;
Leituras da porta analógica A0, mantida desconectada, são utilizadas como fonte de entropia. O ruído elétrico do ambiente gera variações imprevisíveis de tensão, que são convertidas em valores digitais pelo conversor analógico-digital do Arduino.

2.Inicialização de gerador pseudoaleatório (LCG);
Os valores captados são utilizados para configurar um Gerador Congruente Linear (LCG), cuja fórmula é:

\[
   X_{n+1} = (a \cdot X_n + c) \mod m
   \]

Os parâmetros `a`, `c` e `m` são derivados das leituras analógicas, garantindo variabilidade a cada execução.

3. Mistura com novas leituras analógicas 
A cada geração, o número pseudoaleatório é misturado com novas leituras analógicas utilizando operações bit a bit (XOR), o que aumenta a entropia e reduz padrões previsíveis.

4. Extração de Von Neumann;
Para eliminar viés estatístico, os bits são extraídos usando a técnica de Von Neumann. Pares de bits iguais são descartados, enquanto pares diferentes são convertidos em um bit confiável. Isso contribui para uma distribuição mais uniforme entre 0 e 1.

5. Saída via porta serial;
O sistema imprime 10.000 bits aleatórios na porta serial, com intervalo de 10 milissegundos entre cada um, permitindo análise externa ou armazenamento.

Este projeto demonstra como é possível gerar aleatoriedade de qualidade razoável utilizando apenas recursos básicos do Arduino Uno, combinando ruído físico com técnicas de correção estatística.
