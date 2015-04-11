# cache-simulator
Implementação de um simulador de caches parametrizável.

Cache L1 e L2 unified, endereçada a byte.
Edereço possui 32bits.

`./cache <nsets_L1>:<bsize_L1>:<assoc_L1> <nsets_L2>:<bsize_L2>:<assoc_L2> arquivo_de_entrada`

Onde cada um desses campos possui o significado:
- \<nsets> = número de conjuntos da cache
- \<bsize> = tamanho do bloco em bytes
- \<assoc> = associatividade

Política de substituição: randomica
Política de escrita: write-back
Default: nsets=1024 bsize=4 assoc=1

O  arquivo de entrada indica a leitura de um arquivo que será utilizado como entradapara o simulador (armazenado em formato binário) que conterá os endereços requisitados a cache (endereços em 32 bits) seguido de um valor indicando a leitura ou escrita (leitura =0 e escrita =1).
