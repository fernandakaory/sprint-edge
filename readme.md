# Mapeamento inteligente - SmarTech

<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/34f0bd23-e519-4d59-b81a-2407b76a7918" width="300" height="100" alt="logotipo">
</div>

## Integrantes
- Fernanda Kaory Saito – RM 551104
- Geovanna Silva Cunha – RM 97736
- Lana Giulia Auada Leite – RM 551143
- Mirella de Rossi Imenez – RM 97990

## Plataforma de mapeamento inteligente como nossa proposta de solução do Challenge com a IBM
Estamos desenvolvendo uma plataforma de mapeamento dos meios de transporte sustentáveis em São Paulo. Nosso projeto visa disponibilizar informações sobre as frotas de trens, metrôs, linhas de ônibus
elétricos e pontos de bicicletas compartilhadas disponíveis na cidade. Um dos focos principais é o baixo investimento recebido pelas linhas elétricas de ônibus.
Nossa plataforma irá disponibilizar ao usuário meios de transporte exclusivamente sustentáveis. Além disso, visamos melhorar constantemente nossos serviços, assim, forneceremos ao usuário a opção de “Feedback”, a
qual permitirá o usuário compartilhar pontos negativos, sugestões de melhoria e pontos positivos que contribuam para uma experiência mais satisfatória no transporte utilizado no dia a dia. Também será possível consultar informações
detalhadas sobre o trajeto de cada linha de metrô, trem ou ônibus. Os usuários também poderão verificar em tempo real se um veículo está “lotado” ou com uma ocupação “razoável”, de acordo com informações captadas por um sensor de
movimento inserido nos principais ônibus, visando oferecer informações para uma melhor experiência do usuário. Dessa forma, temos o intuito de proporcionar aos usuários uma plataforma completa e eficiente para o deslocamento
sustentável na cidade de São Paulo.

## Aplicação de Edge Computing and Computer Systems no projeto
Este projeto se concentra na aplicação de Edge Computing e Computer Systems para verificar a ocupação de veículos de transporte público indicados no nosso site, especialmente ônibus elétricos. Para atingir esse objetivo, utilizamos sensores de movimento infravermelhos.
Nosso sistema inclui dois dispositivos distintos: um sensor de entrada e um sensor de saída. Esses sensores desempenham papéis complementares no monitoramento da ocupação do veículo. Quando um passageiro se aproxima da porta de entrada, o sensor de entrada é ativado e registra sua presença. O código-fonte em um microcontrolador ESP32 mantém uma variável que é incrementada a cada novo passageiro detectado pela porta de entrada.
O sensor de saída, por outro lado, está localizado na saída do veículo. Quando um passageiro deixa o veículo, o sensor de saída é acionado e decrementa a variável correspondente, refletindo a diminuição da ocupação. Desta maneira, a partir dos valores da lotação, uma mensagem sobre o status da ocupação será exibida/transmitida, com o objetivo de promover uma consulta rápida e simples para os usuários.
Esse sistema de monitoramento, garante que os dados coletados sobre a ocupação dos veículos sejam precisos e confiáveis. Além disso, proporciona uma solução eficaz para garantir uma experiência melhor e mais confortável para noddod usuários.


## Utilização de Iot no projeto
Para a manipulação e visualização dos dados coletados pelos sensores, a SmarTech utilizara ferramentas importantes de IoT, como Fiware, a plataforma Postman e protocolos como MQTT. Primeiramente, os dispositivos, coletam continuamente informações sobre a ocupação dos veículos. Esses dados serão processados a partir do Fiware, que permite o transporte dos dados.
Utilizaremos o protocolo MQTT para a comunicação entre os dispositivos IoT e o servidor, garantindo uma transferência de dados segura. Com isso, somos capazes de coletar, transmitir e processar informações em tempo real.
Para tornar esses dados acessíveis ao público e aos interessados, utilizamos uma plataforma com recursos para a criação de dashboards simples e amigáveis, o <a href=https://freeboard.io/> freeboard </a>. Os dados processados serão exibidos em gráficos, dashboards intuitivos e de fácil entendimento, proporcionando uma visão clara da ocupação dos ônibus elétricos. Isso não apenas melhora a experiência do usuário, mas também auxilia na gestão do transporte público, permitindo que os passageiros tomem decisões informadas sobre seus deslocamentos.

## Arquitetura proposta para a solução Iot

![Captura de tela 2023-09-12 210509](https://github.com/fernandakaory/sprint3-edge/assets/126582859/bcd8aac6-c528-48d0-9b41-1229b5b4b837)

## Recursos necessários para implementação da solução
<h3>O Hardware deste projeto, é composto essencialmente por: </h3>
Uma placa ESP 32, que conta com dois núcleos de 32 bits, responsável por permitir a conexão ao wifi ou blutooth, garantindo, assim, a implementação da Internet das Coisas no nosso protótipo.

<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/2530d075-fcab-4b35-ad58-5eed09751ef7" >
</div>

E dois sensores de proximidade infravermelho E18-D80NK, para monitorar a entrada e saída dos passageiros.
<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/63ec5b37-304b-4e58-b125-b957be785dbb" >
</div>
<h3>Back-end</h3>
Para o Back-end do projeto será utilizado o Fiware. Esta, é uma plataforma de código aberto que fornece uma infraestrutura padrão e aberta para o desenvolvimento de aplicações e serviços inteligentes baseados em IoT. Desta maneira, faremos uso desta ferramenta para que os dados coletado a partir dos sensores infravermelhos sejam coletados, armazenados e transportado até a nossa plataforma Smartech, na qual serão exibidos para nossos clientes por meio de uma interface simples e amigável.
<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/dcd4980b-f53f-444d-99d6-4925a6668d87" >
</div>
<h3>Front-end</h3>
A base front-end que está sendo utilizada neste projeto na fase atual, é, basicamente, o <a href=https://freeboard.io/> freeboard </a>, uma plataforma que nos oferece todos os recursos necessários para a exibição dos dados de lotação que são enviados por MQTT, a partir do Fiware Orion. Assim é possível vizualizar os dados captados pelos sensores de maneira simples e intuitiva. Escolhemos o freeboard com o intuíto de ser simples e de fácil utilização, para garantir  acessibilidade e uma boa experiência.

<div>
  
  <img src="https://github.com/fernandakaory/sprint-edge/assets/126582859/0c402054-51ce-458e-94d4-6b334f72ed4b" width="300" >
  <img src="https://github.com/fernandakaory/sprint-edge/assets/126582859/bb98b7ad-7137-41fe-9c67-7894eaf4a095" width="300">
  <img src="https://github.com/fernandakaory/sprint-edge/assets/126582859/865fd769-c468-454f-b3a1-91394e4f72d5" width="300">
</div>


## Requisitos do projeto
- Docker e docker compose
- Fiware
- Postman
- ESP 32 e sensores de proximidade infravermelho E18-D80NK
- Conectividade Wifi ou blutooth
- Ambiente front-end, como o <a href=https://freeboard.io/> freeboard </a>
  
## Configuração e reprodução
1. Instalação de uma máquina virtual Linux
2. Instalação do docker e do docker compose como especificado <a href=https://docs.docker.com/engine/install/ubuntu/> aqui </a>.
3. Instalação do <a href=https://github.com/fabiocabrini/fiware> Fiware</a>.
4. Instalação do Postman
5. Importar as collection para o Fiware e executar os métodos HTTP de Health Check
6. Provisionar os sensores como dispositivos virtuais (como no arquivo json acima), definindo id, protocolo de comunicação, comandos e atributos.
7. Registrar esses dispositivos  (como no arquivo json acima).
8. Montar os sensores físicos na ESP 32.
9. Montar o código desses sensores para enviar por MQTT os dados.
10. Realizar a subscrição e métodos GET para receber os dados desejados.
11. Configurar <a href=https://freeboard.io/> freeboard </a>
12. Configurar os dashboards e gráficos desejados
