Tabela Hash de Contatos
Este projeto implementa uma tabela hash simples para armazenar contatos, permitindo adicionar, buscar, remover e exibir contatos. Além disso, mede o tempo de inserção e busca de contatos para análise de desempenho.

Funcionalidades
Adicionar Contato: Insere um novo contato na tabela hash.
Buscar Contato: Busca um contato pelo nome e exibe o telefone associado.
Remover Contato: Remove um contato da tabela hash pelo nome.
Exibir Contatos: Exibe todos os contatos armazenados na tabela hash.
Medição de Desempenho: Calcula e exibe o tempo de inserção e busca de contatos em milissegundos.
Estrutura do Código
Contato: Estrutura que representa um contato com nome, telefone e um ponteiro para o próximo contato.
Tabela Hash: Array de ponteiros para contatos, onde cada índice representa uma lista encadeada de contatos.
Função Hash: Calcula o índice da tabela hash com base na soma dos caracteres do nome do contato.
Funções de Manipulação: Funções para inicializar a tabela, criar contatos, adicionar, buscar, remover e exibir contatos.
Medição de Tempo: Uso das funções QueryPerformanceCounter e QueryPerformanceFrequency para medir o tempo de execução das operações.
