# Terminal Shooter
Projeto de Algoritmos e Estruturas de Dados I - Inspirado por Wolfenstein 3D, DOOM e QUAKE.

make: `mingw32-make`

## Integrantes:
- Augusto Luchesi Matos
- Daniel Lombardi de Oliveira
- Pedro Freire Baleeiro

### Pseudo-Relatorio:
O primeiro passo foi a adaptacao do renderizador ao sistema utilizado. O renderizador funciona utilizando caracteres [ASCII](http://www.asciitable.com) sem colorização. A renderizacao (por ray-tracing/casting) cria uma ilusao 3D a partir das ditancias dos objetos e entidades do mapa. A HUD e o mini-mapa sao tratados como overlays e sao adicionados sobre o frame apos sua renderizacao.


### URGENTE:
- Implementar Entidades com movimentacao, renderizacao correta e TAD das entidades.
- Municao com TAD (fila) e tipos diferentes

### NAO-URGENTE:
- HUD dinamico
- Tipos de entidades
- Animacoes (tiro, hit-effect, morte)
- Musica
