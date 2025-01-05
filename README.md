# gamemode-open
Uma gamemode base de c�digo aberto, simples, por�m completa e em dia com as boas pr�ticas de c�digo e seguran�a.

[![Licen�a](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/license/mit)

# Estrutura
| Nome                | Descri��o                                                                                     |
|---------------------|-----------------------------------------------------------------------------------------------|
| `compiler/include/*/` | Cont�m as bibliotecas necess�rias                                                           |
| `components/*`      | Cont�m os componentes (plugins que foram migrados para o open.mp)                             |
| `gamemodes/*`       | Cont�m o arquivo compilado e o c�digo fonte do script                                         |
| `.env`              | Cont�m as vari�veis de ambiente contendo as credenciais do banco de dados MySQL              |
| `config.json`       | Cont�m as configura��es do servidor open.mp. Para mais informa��es, veja [documenta��o](https://www.open.mp/docs/server/config.json) |
| `omp-server`        | Execut�vel que inicia o servidor                                                             |
| `scheme.sql`        | Cont�m a estrutura da tabela SQL `jogadores` e suas colunas                                  |

# Vantagens
- Escalabilidade
- Criptografia de todas as senhas utilizando bcrypt
- C�digo limpo e bem documentado
- F�cil de configurar, bastando conhecimento extremamente b�sico sobre gerenciamento de banco de dados e Pawn

# Fun��es
- Tela de login simples em dialog
- Sistema de g�nero
- Salvamento de �ltima posi��o do jogador

# Compila��o
Nas vers�es pr�-compiladas ([que podem ser encontradas aqui](https://github.com/spc-samp/gamemode-openmp/releases/latest)), o servidor vem com uma pasta extra chamada Qawno, que � o ambiente de desenvolvimento padr�o do open.mp, equivalente ao Pawno. Tudo o que voc� precisa fazer � executar o arquivo qawno.exe e seguir o passo-a-passo abaixo:

1 - Ao abrir o programa, no canto superior esquerdo, clique na op��o "File" e selecione "Open"
![qawno](https://i.imgur.com/zybzJxD.png)

Ap�s isso, navegue at� a pasta onde a gamemode est� localizada e abra o arquivo `Main.pwn` localizado na pasta `gamemodes`

2 - Clique na op��o "Build" no menu superior e selecione a op��o "Compile" ou pressione F5 em seu teclado
![qawno](https://i.imgur.com/pLII7sm.png)

E � simples assim. A compila��o deve gerar um arquivo chamado "Main.amx" na pasta `gamemodes`.

Aviso: caso optar por utilizar o Qawno e sampvoice, ignore os dois warnings que surgem devido a vers�o do compilador do open.mp ou adicione o c�digo `#pragma warning disable 239` no topo do script (embora eu pessoalmente n�o recomende essa abordagem pois promove m�s pr�ticas de programa��o). S�o warnings de *const-correctness* que n�o afetam em nada a compila��o ou o funcionamento do servidor.

# Escolhendo a Vers�o da Gamemode

Se voc� est� confuso sobre qual vers�o escolher para o seu sistema operacional, aqui est� uma breve explica��o:

### Vers�es Dispon�veis

- **`gamemode-win-x86`**
  - **Descri��o:** Esta vers�o � para sistemas Windows.
  - **Detalhes:** Roda o servidor e seus plugins na arquitetura x86, que � o padr�o para a maioria dos plugins.

- **`gamemode-x86-centos`**
  - **Descri��o:** Esta vers�o � destinada � distribui��o CentOS.
  - **Detalhes:** Certifique-se de que seu servidor utiliza o CentOS antes de escolher esta vers�o.

- **`gamemode-x86-debian`**
  - **Descri��o:** Esta vers�o � para a distribui��o Debian e distribui��es baseadas em Debian.
  - **Detalhes:** Inclui suporte para distribui��es como Ubuntu (a mais popular) e outras variantes baseadas em Debian.

### Como Identificar Sua Distribui��o Linux

Se voc� n�o tem certeza sobre qual distribui��o Linux seu servidor est� rodando, recomendamos:

1. Consultar seu provedor de hospedagem.
2. Rodar o comando `lsb_release` (dispon�vel na maioria das distribui��es Linux) para obter informa��es relacionadas � sua distribui��o.

**Nota:** A diferencia��o entre distribui��es baseadas em CentOS e Debian � necess�ria porque o plugin MySQL possui vers�es espec�ficas para cada tipo de distribui��o.


