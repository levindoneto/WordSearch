# Buscador de palavras

## Motivação
Uma tarefa crucial na área de recuperação de informações é recuperar documentos que possuam as palavras-chave especificadas em uma consulta. A fim de resolver as consultas, os documentos precisam ser primeiro indexados. O programa desenvolvido simula o funcionamento de um buscador de palavras-chave. A aplicação desenvolvida é composta por dois módulos: indexação e consulta. Durante a indexação, as palavras do texto dado como entrada são carregadas em uma estrutura de dados, de forma que se possa identificar a linha em que cada palavra ocorre. Durante a fase de consultas, a aplicação lê um arquivo com as palavras a serem consultadas e gera um arquivo de saída com as palavras consultadas e as linhas do texto nas quais elas ocorrem.

## Estruturas de dados utilizadas e explicação
As estruturas de dados utilizadas foram uma árvore AVL e Listas Simplesmente Encadeadas. A
árvore AVL possui os nodos de controle normais acrescidos de um nodo com a palavra lida do texto
e um nodo com um ponteiro para uma Lista Simplesmente Encadeada que contêm dois nodos, um
contendo a linha onde a palavra foi encontrada e outro com um ponteiro para o próximo elemento da
lista(próxima linha, caso houver).
A escolha da árvore levou em conta a otimização de tempo para a consulta(explicado melhor na
próxima seção), pois como o objetivo é ter uma consulta ágil e eficaz, e como o tempo de inserção
pode ser longo, já que a inserção na árvore só será feita uma vez e a consulta será feita tantas vezes
quanto necessárias. Assim, a escolha mais adequada foi AVL.
A escolha da lista levou em consideração a simplicidade de acesso e armazenamento na memória,
admitindo que a inserção já é feita em ordem crescente, a consulta pode ser feita do início da lista
até o fim da mesma, fazendo com que o uso de LSE’s(Listas Simplesmente Encadeadas) fosse o mais
adequado.

## Passo a passo
- Abre o arquivo;
- Vai pegando letra por letra e colocando no vetor até encontrar caracteres que sejam aceitados
pelo código;
- Quando a palavra estiver formada no vetor, esta é posta no nodo da árvore juntamente com a respectiva linha onde ela se encontrou;
- O procedimento acima é repetido até acabar o arquivo de entrada;
- Na consulta a formação de palavras é feita do mesmo jeito;
- Quando a palavra é formada, já é procurada na árvore AVL;
- Encontrado o nodo onde a palavra está, salva as linhas onde elas se situam no arquivo de saída.

## Otimização de tempo
A otimização do código para demorar menos na parte de indexação foi, depois do código pronto, eliminar
códigos não-alcançáveis ou redundantes, aplicação de um conjunto de heurísticas para detectar
essas sequências e substituí-las por outras que removam as situações de ineficiência no programa.
Outra coisa foi que ao invés de criar uma estrutura para o arquivo consulta, nosso programa pega
palavra à palavra e faz a consulta direto na árvore previamente indexada.

