# Projeto Libft

O projeto Libft é uma biblioteca personalizada de funções em C, desenvolvida como parte do currículo da 42 School. Esta biblioteca contém implementações de várias funções padrão da biblioteca C, bem como algumas funções adicionais úteis para manipulação de strings, memória e listas.

## Funcionalidades

A biblioteca Libft inclui as seguintes categorias de funções:

1. **Funções de Manipulação de Memória**:
   - `ft_memset`: Preenche um bloco de memória com um valor específico.
   - `ft_bzero`: Zera um bloco de memória.
   - `ft_memcpy`: Copia um bloco de memória para outro.
   - `ft_memccpy`: Copia um bloco de memória até encontrar um caractere específico.
   - `ft_memmove`: Move um bloco de memória para outro, garantindo que áreas sobrepostas sejam tratadas corretamente.
   - `ft_memchr`: Procura um caractere em um bloco de memória.
   - `ft_memcmp`: Compara dois blocos de memória.

2. **Funções de Manipulação de Strings**:
   - `ft_strlen`: Calcula o comprimento de uma string.
   - `ft_strdup`: Duplica uma string.
   - `ft_strcpy`: Copia uma string para outra.
   - `ft_strncpy`: Copia um número específico de caracteres de uma string para outra.
   - `ft_strcat`: Concatena duas strings.
   - `ft_strncat`: Concatena um número específico de caracteres de uma string para outra.
   - `ft_strlcat`: Concatena duas strings, garantindo que o buffer de destino não seja excedido.
   - `ft_strchr`: Procura um caractere em uma string.
   - `ft_strrchr`: Procura a última ocorrência de um caractere em uma string.
   - `ft_strstr`: Procura uma substring em uma string.
   - `ft_strnstr`: Procura uma substring em uma string, limitando a busca a um número específico de caracteres.
   - `ft_strcmp`: Compara duas strings.
   - `ft_strncmp`: Compara um número específico de caracteres de duas strings.

3. **Funções de Conversão**:
   - `ft_atoi`: Converte uma string para um inteiro.
   - `ft_itoa`: Converte um inteiro para uma string.

4. **Funções de Manipulação de Caracteres**:
   - `ft_isalpha`: Verifica se um caractere é uma letra.
   - `ft_isdigit`: Verifica se um caractere é um dígito.
   - `ft_isalnum`: Verifica se um caractere é uma letra ou um dígito.
   - `ft_isascii`: Verifica se um caractere está no conjunto ASCII.
   - `ft_isprint`: Verifica se um caractere é imprimível.
   - `ft_toupper`: Converte um caractere para maiúscula.
   - `ft_tolower`: Converte um caractere para minúscula.

5. **Funções de Manipulação de Listas**:
   - `ft_lstnew`: Cria um novo nó de lista.
   - `ft_lstdelone`: Deleta um nó de lista.
   - `ft_lstdel`: Deleta uma lista inteira.
   - `ft_lstadd`: Adiciona um novo nó no início da lista.
   - `ft_lstiter`: Itera sobre cada nó da lista e aplica uma função.
   - `ft_lstmap`: Cria uma nova lista aplicando uma função a cada nó da lista original.

#### Como Usar

Para usar a biblioteca Libft em seu projeto, siga os passos abaixo:

1. Clone o repositório:
   ```sh
   git clone https://github.com/NaBuchholz/libft.git
   ```

2. Compile a biblioteca:
   ```sh
   cd libft
   make
   ```

3. Inclua a biblioteca no seu projeto:
   ```c
   #include "libft.h"
   ```

4. Compile seu projeto com a biblioteca:
   ```sh
   gcc -o seu_programa seu_programa.c -L. -lft
   ```

#### Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests no repositório.

#### Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
