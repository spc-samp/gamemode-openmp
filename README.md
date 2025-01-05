# gamemode-open
Uma gamemode base de código aberto, simples, porém completa e em dia com as boas práticas de código e segurança.

[![Licença](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/license/mit)

# Estrutura
| Nome                | Descrição                                                                                     |
|---------------------|-----------------------------------------------------------------------------------------------|
| `compiler/include/*/` | Contém as bibliotecas necessárias                                                           |
| `components/*`      | Contém os componentes (plugins que foram migrados para o open.mp)                             |
| `gamemodes/*`       | Contém o arquivo compilado e o código fonte do script                                         |
| `.env`              | Contém as variáveis de ambiente contendo as credenciais do banco de dados MySQL              |
| `config.json`       | Contém as configurações do servidor open.mp. Para mais informações, veja [documentação](https://www.open.mp/docs/server/config.json) |
| `omp-server`        | Executável que inicia o servidor                                                             |
| `scheme.sql`        | Contém a estrutura da tabela SQL `jogadores` e suas colunas                                  |

# Vantagens
- Escalabilidade
- Criptografia de todas as senhas utilizando bcrypt
- Código limpo e bem documentado
- Fácil de configurar, bastando conhecimento extremamente básico sobre gerenciamento de banco de dados e Pawn

# Funções
- Tela de login simples em dialog
- Sistema de gênero
- Salvamento de última posição do jogador

# Compilação
Nas versões pré-compiladas ([que podem ser encontradas aqui](https://github.com/spc-samp/gamemode-openmp/releases/latest)), o servidor vem com uma pasta extra chamada Qawno, que é o ambiente de desenvolvimento padrão do open.mp, equivalente ao Pawno. Tudo o que você precisa fazer é executar o arquivo qawno.exe e seguir o passo-a-passo abaixo:

1 - Ao abrir o programa, no canto superior esquerdo, clique na opção "File" e selecione "Open"
![qawno](https://i.imgur.com/zybzJxD.png)

Após isso, navegue até a pasta onde a gamemode está localizada e abra o arquivo `Main.pwn` localizado na pasta `gamemodes`

2 - Clique na opção "Build" no menu superior e selecione a opção "Compile" ou pressione F5 em seu teclado
![qawno](https://i.imgur.com/pLII7sm.png)

E é simples assim. A compilação deve gerar um arquivo chamado "Main.amx" na pasta `gamemodes`.

Aviso: caso optar por utilizar o Qawno e sampvoice, ignore os dois warnings que surgem devido a versão do compilador do open.mp ou adicione o código `#pragma warning disable 239` no topo do script (embora eu pessoalmente não recomende essa abordagem pois promove más práticas de programação). São warnings de *const-correctness* que não afetam em nada a compilação ou o funcionamento do servidor.

# Escolhendo a Versão da Gamemode

Se você está confuso sobre qual versão escolher para o seu sistema operacional, aqui está uma breve explicação:

### Versões Disponíveis

- **`gamemode-win-x86`**
  - **Descrição:** Esta versão é para sistemas Windows.
  - **Detalhes:** Roda o servidor e seus plugins na arquitetura x86, que é o padrão para a maioria dos plugins.

- **`gamemode-x86-centos`**
  - **Descrição:** Esta versão é destinada à distribuição CentOS.
  - **Detalhes:** Certifique-se de que seu servidor utiliza o CentOS antes de escolher esta versão.

- **`gamemode-x86-debian`**
  - **Descrição:** Esta versão é para a distribuição Debian e distribuições baseadas em Debian.
  - **Detalhes:** Inclui suporte para distribuições como Ubuntu (a mais popular) e outras variantes baseadas em Debian.

### Como Identificar Sua Distribuição Linux

Se você não tem certeza sobre qual distribuição Linux seu servidor está rodando, recomendamos:

1. Consultar seu provedor de hospedagem.
2. Rodar o comando `lsb_release` (disponível na maioria das distribuições Linux) para obter informações relacionadas à sua distribuição.

**Nota:** A diferenciação entre distribuições baseadas em CentOS e Debian é necessária porque o plugin MySQL possui versões específicas para cada tipo de distribuição.


