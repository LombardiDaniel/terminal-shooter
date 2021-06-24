[![tag](https://img.shields.io/github/v/release/LombardiDaniel/terminal-shooter?include_prereleases&style=for-the-badge)](https://github.com/LombardiDaniel/terminal-shooter/releases/)
# Terminal Shooter
Projeto de Algoritmos e Estruturas de Dados I - Inspirado em Wolfenstein 3D, DOOM e QUAKE.

make: `mingw32-make`

## Integrantes:
- Augusto Luchesi Matos
- Daniel Lombardi de Oliveira
- Pedro Freire Baleeiro

### Pseudo-Relatorio:
O primeiro passo foi a adaptacao do renderizador ao sistema utilizado. O renderizador funciona utilizando caracteres [ASCII](http://www.asciitable.com) sem colorização. A renderizacao (por ray-tracing/casting) cria uma ilusao 3D a partir das ditancias dos objetos e entidades do mapa. A HUD e o mini-mapa sao tratados como overlays e sao adicionados sobre o frame apos sua renderizacao a partir de uma `std::string` que eh interpretada para maior flexibilidade artistica dos caracteres.

A proxima etapa foi adaptar os elementos previstos ([Entidades](src/headers/entity.h), utilizadas pelas classes: [Player](src/headers/player.h) e [Mob](src/headers/mob.h)). Neste momento, foi criado a fila (TAD) de spawn de mobs, que trabalha com a classe [MobsWave](src/headers/mob.h) para preencher o tabuleiro de inimigos ao final dos rounds.

Em seguida (16/6) o loop do jogo foi tratado. Utilizamos a standard library `chrono` para marcar a diferenca entre cada iteracao do loop principal (encontrado na [main.cpp](src/main.cpp)), agora garantimos que a movimentacao das Entidades ocorre de maneira constante, independente da frquencia de atualizacao do jogo (que depende do computador do usuario, desde que rode pelo menos a tick rate definida na [engine.h](src/engine.h)). Agora eh possivel tratar dos eventos dentro do loop (dano, movimentacao etc).

Com as adaptacoes em relacao ao tempo e criacao da tick-rate do jogo, foi possivel (finalmente) implementar os disparos e danos aos mobs (feitos por hit-scan), com logica muito proxima ao do ray-tracing utilizado na renderizacao.

Conforme a complexidade do codigo ia aumentando cada vez mais, adicionar uma simples funcionalidade como permitir que o jogador recarregasse sua arma necessitava de diversas modificacoes e adicoes ao codigo de varios arquivos, causando grande probabilidade de erros. Assim, foi desenvolvida uma simples classe de Logging (encontrada em [`utila.h`](src/headers/utils.h)) que possibilitou o desenvolivmento mais conciso e robusto de novas features, ja que agora poderiamos conferir valores das variaveis sem precisar ter a feature completa em funcionamento. Estes "mini-projetos" dentro do trabalho principal foram otimas maneiras de aumentar nosso conhecimento em C++, no caso do Logger, o principal foi o trabalho com [Veriadic Templates](https://en.cppreference.com/w/cpp/language/parameter_pack) (template pack), permitindo passar diferentes quantidades de parametros para uma funcao (o equivalente ao `*args, **kwargs`, em python).

### URGENTE:

- **CORRIGIR** TAD para spawn das unidades: fazer funcao `MobsWave createNewWave();`:  no arquivo utils e dar push na fila de MobsWave e a coloca na fila. - Usar system::clock no RNG (pegar segundos pra fazer a seed)
- Implementar Entidades com movimentacao, TAD das entidades.
- Municao com TAD (fila) e tipos diferentes

### NAO-URGENTE:
- HUD dinamico
- Tipos de entidades
- Animacoes (tiro, hit-effect, morte)
- Musica

### Prioridades:
- criar classe de logger simples, pqp ta foda
- hp pra 80-70-100 sla
