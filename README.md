# Trabalho Final de AED I (com API do Windows)

Esse foi meu trabalho final da disciplina de Algoritmos e Estruturas de Dados I, lecionada pelo professor Rafael Burlamaqui na Universidade Federal de Pelotas. 

Essa versão possui uma interface muito mais interessante com o usuário, usando dos recursos disponíveis na API do Windows.

Muitos dos recursos usados aqui foram reaproveitados do código que escrevi para fazer os gráficos do [8-Puzzle](https://github.com/Equiel-1703/8-Puzzle), jogo feito como trabalho final da disciplina de Programação de Computadores. Esses códigos foram muito melhorados e otimizados. Por exemplo, antes os sprites eram lidos diretamente de um arquivo txt salvo no disco rígido. Agora, os sprites são carregados em strings alocadas dinamicamente na RAM, otimizando e muito a utilização dos sprites. 

A forma de exibir os sprites na tela também foi otimizada. Antes eles eram exibidos linha a linha usando funções como fgets ou getline para ler do arquivo no disco e imprimindo na tela com printf. Nessa versão melhorada, o arquivo já está na RAM, portanto só percorri o vetor buscando o índice de início e fim desejado e imprimi na tela usando fwrite (que é muito mais rápido que a função printf).

Essas e outras melhorias permitiram até mesmo compilar com o MinGW-W64. Isso era impossível antes, pois por algum motivo quando o 8-Puzzle era compilado com o MinGW-W64 os sprites eram exibidos linha a linha de forma extremamente lenta, tornando impossível de jogar o game. Mas isso estranhamente não acontecia no MinGW normal (que é de 32 bits).

Meu palpite é de que no MinGW normal o compilador criava um buffer onde os arquivos que eram constantemente acessados no disco (os sprites nesse caso) eram salvos, e portanto não causava lentidão na hora de exibir na tela. Já o MinGW-W64 não faz isso, e então causa o bug que mencionei. Mas graças às melhorias feitas na biblioteca de gráficos, esse bug não acontece mais com o MinGW-W64.

A parte do TAD da árvore AVL é exatamente igual em ambas as versões do trabalho final de AED I.
