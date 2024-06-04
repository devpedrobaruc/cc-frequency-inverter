## Projeto atualmente esperando peças chegarem da china.

Irei pegar um motor 220V monofásico, desmonta-lo e refazer as ligações da bobina, que costuma ser em série, vou ligar em paralelo para diminuir a tensão de operação e não ter que rebobinar para conseguir o mesmo efeito.
Com isso feito, este projeto irá gerar uma onda senoidal pura para alimenta-lo, com a possibilidade de modificar a frequência para alcançar mais RPM.

## Por que não utilizar o EGS002?
O EGS002 tem configuração de frequência apenas para 50HZ ou 60HZ, utilizando o STM32 conseguirei gerar ondas senoidais de diferentes frequências e com diferentes périodos de PWM.

## Qual a motivação do projeto?
Preciso ligar um motor de grande potência em baterias de carro, procurando inversores senoidais na internet, vi que o preço está muito elevado até em inversores "mais simples", como nenhum mais "em conta" não iria suprir minha demanda por causa da potência do motor, irei diminuir a tensão de operação do mesmo e fazer um sistema capaz de controla-lo.
