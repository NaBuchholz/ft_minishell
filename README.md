# Minishell

<p align="center">
	<img src="https://img.shields.io/badge/Norma-42-blue?style=flat&logo=42&logoColor=white" alt="42-school">
	<img src="https://img.shields.io/badge/linguagem-C-00599C?style=flat&logo=c&logoColor=white" alt="C">
	<img src="https://img.shields.io/badge/shell-bash-4EAA25?style=flat&logo=gnu-bash&logoColor=white" alt="shell">
</p>

## 📋 Sobre

O **Minishell** é uma recriação simplificada do shell bash, desenvolvida como projeto da 42 School. Este shell implementa funcionalidades essenciais como pipelines, redirecionamentos, expansão de variáveis e comandos internos (built-ins), proporcionando uma experiência similar ao terminal padrão.

## ✨ Funcionalidades

### 🔧 Comandos Internos (Built-ins)
- `echo` com opção `-n`
- `cd` com caminhos relativos ou absolutos
- `pwd` sem opções
- `export` para variáveis de ambiente
- `unset` para remover variáveis
- `env` para listar variáveis de ambiente
- `exit` para sair do shell

### 🔀 Redirecionamentos e Pipes
- `|` - Pipes para conectar comandos
- `<` - Redirecionamento de entrada
- `>` - Redirecionamento de saída
- `>>` - Redirecionamento em modo append
- `<<` - Heredoc com delimitador

### 🌍 Expansão de Variáveis
- Expansão de variáveis de ambiente (`$VAR`)
- Status de saída do último comando (`$?`)
- Manipulação de aspas simples e duplas

### ⌨️ Controle de Sinais
- `Ctrl+C` - Nova linha com prompt
- `Ctrl+D` - Sair do shell
- `Ctrl+\` - Sem ação (como no bash)

## 🚀 Instalação e Uso

### Pré-requisitos
- GCC compiler
- Biblioteca readline
- Make

### Compilação
```bash
make
```

### Execução
```bash
./minishell
```

## 📂 Arquitetura

O projeto está organizado em módulos bem definidos:

```
src/
├── main.c              # Ponto de entrada e loop principal
├── init.c              # Inicialização do shell
├── lexer/              # Análise léxica (tokenização)
├── parser/             # Análise sintática
├── executor/           # Execução de comandos e pipelines
├── builtins/           # Comandos internos
├── environment/        # Gestão de variáveis de ambiente
├── heredoc/            # Implementação do heredoc (<<)
├── tests/              # Suíte de testes
└── signals/            # Tratamento de sinais
```

## 🎯 Exemplos de Uso

```bash
# Comandos simples
minishell> echo "Hello World"
minishell> pwd
minishell> ls -la

# Pipes e redirecionamentos
minishell> ls | grep .c
minishell> echo "test" > output.txt
minishell> cat < input.txt

# Heredoc
minishell> cat << EOF
> linha 1
> linha 2
> EOF

# Variáveis de ambiente
minishell> export MY_VAR="valor"
minishell> echo $MY_VAR
minishell> echo $?  # status de saída
```

## ⚙️ Características Técnicas

- **Parsing robusto**: Análise sintática com verificação de erros
- **Gestão de processos**: Fork e execução de comandos externos
- **Gestão de memória**: Limpeza adequada sem vazamentos
- **Tratamento de sinais**: Comportamento similar ao bash
- **Expansão de variáveis**: Suporte completo a `$VAR` e `$?`

## 🧪 Testes

O projeto inclui uma suíte de testes localizada na pasta `src/tests/` que verifica as funcionalidades principais:

- **Lexer**: Testes de tokenização e análise léxica
- **Parser**: Testes de análise sintática e validação
- **Heredoc**: Testes específicos para operador `<<`
- **Argumentos**: Testes de processamento de argumentos

Para executar os testes, no momento, é preciso fazer alterações no código fonte.O próximo passo será adicionar
estes testes em um script que automtize sua execução. (AGUARDE)

## 🛠️ Desenvolvimento

Para debugar o projeto:
```bash
make debug
gdb ./minishell
```

## 🏆 Conformidade

- ✅ Norma 42 School
- ✅ Sem vazamentos de memória
- ✅ Tratamento robusto de erros
- ✅ Compatibilidade com bash

---
## 🎗 Licença

Este projeto está licenciado sob a Licença MIT.

<p align="center">Feito com 💜 por Nyx & Vini</p>
