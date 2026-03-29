# TP01 — Manipulador de Dados da Justiça Eleitoral

Sistema em C para leitura, concatenação e análise de dados jurisdicionais da Justiça Eleitoral a partir de arquivos CSV.

---

## Estrutura do Projeto

```
/
├── base_de_dados/
├── list.h
├── list.c
├── main.c
├── documentacao.pdf
├── .gitignore
└── README.md
```

---

## Funcionalidades

### 1. Concatenar arquivos
Lê todos os arquivos CSV presentes em `base_de_dados/` e os une em um único arquivo de saída, mantendo o cabeçalho apenas uma vez.

### 2. Gerar resumo por tribunal
Percorre a lista de registros e agrupa os dados por `sigla_tribunal`, calculando o total de julgados e os indicadores de Meta 1, Meta 2A, Meta 2Ant, Meta 4A e Meta 4B. O resultado é salvo em um arquivo CSV.

### 3. Filtrar por município
Recebe um nome de município via entrada do usuário, percorre a lista e grava em um arquivo `.txt` todas as ocorrências cujo campo `municipio_oj` corresponda ao valor informado. O arquivo gerado recebe o nome do município (ex: `MACAPA.txt`).

---

O programa exibe um menu numerado com as três opções disponíveis. Os arquivos CSV devem estar na pasta `base_de_dados/` no mesmo diretório do executável.

---

## Dependências

Apenas bibliotecas padrão do C: `stdio.h`, `stdlib.h`, `string.h`.
