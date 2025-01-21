# gamemode-openmp

Uma gamemode base de código aberto, simples, porém completa e em dia com as boas práticas de código e segurança.

[![Licença](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/license/mit)

---

## Estrutura do Projeto

| **Nome**            | **Descrição**                                                                                 |
|---------------------|-----------------------------------------------------------------------------------------------|
| `compiler/include/` | Contém as bibliotecas necessárias                                                             |
| `components/`       | Contém os componentes (plugins que foram migrados para o open.mp)                             |
| `plugins/`          | Contém os plugins SA-MP (plugins legado que ainda não foram migrados para o open.mp)           |
| `gamemodes/`        | Contém o arquivo compilado e o código fonte do script                                          |
| `.env`              | Contém as variáveis de ambiente contendo as credenciais do banco de dados MySQL                |
| `config.json`       | Contém as configurações do servidor open.mp. Para mais informações, veja a [documentação oficial](https://www.open.mp/docs/server/config.json) |
| `omp-server`        | Executável que inicia o servidor                                                              |
| `scheme.sql`        | Contém a estrutura da tabela SQL de jogadores e suas colunas                                   |

---

## Vantagens

- **Escalabilidade**  
- **Criptografia de todas as senhas utilizando bcrypt**  
- **Código limpo e bem documentado**  
- **Fácil de configurar, exigindo apenas conhecimento extremamente básico em gerenciamento de banco de dados e Pawn**


## Funções

- Tela de login simples em `dialog`
- Sistema de escolha de gênero do personagem
- Salvamento da última posição do jogador no servidor

## Compilação

### Pré-requisitos
As versões pré-compiladas podem ser encontradas na [página de releases](https://github.com/spc-samp/gamemode-openmp/releases/latest).

Nas versões distribuídas, o servidor inclui uma pasta chamada **Qawno**, que é o ambiente de desenvolvimento padrão do open.mp, equivalente ao **Pawno** do SA-MP. 

### Passo-a-passo para compilar usando Qawno:

#### Abra o **Qawno**
Execute o arquivo `qawno.exe` que está na pasta baixada.

#### Abra o arquivo do script
No **menu superior**, clique em `File > Open` e navegue até a pasta `gamemodes/`. Selecione o arquivo **Main.pwn**.

![qawno](https://i.imgur.com/zybzJxD.png)

#### Compile o script
Clique em `Build > Compile` ou pressione **F5** no teclado.

![qawno](https://i.imgur.com/pLII7sm.png)

### Nota sobre Warnings
Se você optar por usar **Qawno** e **sampvoice**, pode ignorar os dois *warnings* que surgirem devido à versão do compilador do open.mp.  

Caso prefira, adicione a linha abaixo no topo do script para suprimir esses *warnings* (embora eu não recomende esta abordagem uma vez que encoraja más práticas):

```pawn
#pragma warning disable 239
```

## Para Desenvolvedores Avançados
Recomendamos o uso do Visual Studio Code como ambiente de desenvolvimento.

Confira este tutorial para configurar o Visual Studio Code para compilar scripts Pawn: https://youtu.be/jITcf95XGgA

## Escolhendo a Versão da Gamemode
Se você está confuso sobre qual versão escolher para o seu sistema operacional, veja abaixo:

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

## Como Identificar Sua Distribuição Linux
Se você não tem certeza sobre qual distribuição Linux seu servidor está utilizando:

1. Consulte seu provedor de hospedagem.
2. Rode o comando abaixo no terminal para obter informações:
```
lsb_release -a
```
Esse comando exibirá a distribuição e a versão do sistema operacional.

## Estrutura SQL

### Tabela `jogadores`

| **Nome**            | **Descrição**                                                                                 |
|---------------------|-----------------------------------------------------------------------------------------------|
| `ID` | ID númerico único gerado pelo banco de dados ao jogador se registrar (segue começando a partir de 0)                                                             |
| `Nome`       | Nome/apelido do jogador                             |
| `Hash`          | Hash gerado a partir da senha do jogador pelo bcrypt           |
| `X_Pos`        | Eixo X da última posição salva do jogador antes de se desconectar                                         |
| `Y_Pos`              | Eixo Y da última posição salva do jogador antes de se desconectar                |
| `Z_Pos`       | Eixo Z da última posição salva do jogador antes de se desconectar |
| `Angle`        | Último ângulo/rotação do jogador registrado antes de se desconectar                                                              |
| `Skin`        | ID da skin/roupa do jogador                                   |
| `Genero`        | Gênero do jogador (0 para masculino / 1 para feminino)                                   |

## Licença

Copyright © SA-MP Programming Community

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Você pode obter uma cópia da licença em:
https://opensource.org/licenses/MIT

### O que você pode fazer ✅

1. **Uso Comercial**: 
   - Liberdade total para uso comercial
   - Pode vender produtos baseados no código
   - Sem necessidade de pagamento de royalties
   - Pode usar em produtos proprietários

2. **Modificação**: 
   - Modificação completa do código fonte
   - Criar trabalhos derivados
   - Adaptar para qualquer propósito
   - Integrar com outros sistemas

3. **Distribuição**: 
   - Distribuir o software original
   - Compartilhar versões modificadas
   - Incluir em outros projetos
   - Distribuir comercialmente

4. **Uso Privado**: 
   - Uso em projetos privados
   - Modificações confidenciais
   - Sem obrigação de divulgação
   - Uso interno irrestrito

5. **Sublicenciamento**: 
   - Pode mudar a licença do código derivado
   - Escolher diferentes termos para suas modificações
   - Combinar com outras licenças
   - Criar termos próprios para distribuição

### O que você deve fazer ⚠️

1. **Incluir Licença**: 
   - Manter cópia da licença com o código
   - Incluir em todas as distribuições
   - Preservar texto original
   - Manter visível e acessível

2. **Atribuição**: 
   - Manter aviso de direitos autorais
   - Incluir em todas as cópias
   - Preservar créditos originais
   - Documentar origem do código

### O que você não pode fazer ❌

1. **Responsabilizar os Autores**: 
   - Sem garantias de funcionamento
   - Autores não são responsáveis por danos
   - Sem suporte obrigatório
   - Uso por conta e risco
