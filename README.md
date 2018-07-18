# Sensor de color con Arduino
La idea del proyecto es el desarrollo de un sensor de color con Arduino y unos pocos componentes electrónicos. El dispositivo deberá ser capaz de "leer" el color de una determinada superficie y enviar el mismo codificado en RGB a través el puerto serie. El proyecto usa un módulo bluetooth HC-06 conectado a los pines 0 y 1, por lo que todo lo enviado por el puerto serie, también es enviado a través del módulo. Dentro del directorio apk se incluye una aplicación Android que puede conectarse con el módulo para interpretar de una manera intuitiva los colores.
## Principio de funcionamiento
Para poder entender el funcionamiento del proyecto, primero es necesario tener algunas ideas básicas de la teoría del color.
### Teoría del color. ¿Qué es el color?<sup>[1](#referencias)</sup>
*No podemos entender totalmente los colores sin entender qué es y cómo funciona la luz.*

El color es un atributo que percibimos de los objetos cuando hay luz. Todo el mundo que nos rodea es de colores siempre y cuando haya luz.

![Prisma](https://www.fotonostra.com/grafico/fotos/teoriacolor.jpg)

La luz está constituida por ondas electromagnéticas que se propagan a unos 300.000 km por segundo. Esa luz no viaja en línea recta sino en forma de ondas. Es lo que se conoce como el carácter ondulatorio de la luz.

Cada una de esas ondas tiene una longitud de onda diferente que es lo que produce los distintos tipos de luz, como la luz infrarroja, la luz ultravioleta o el espectro visible.

El espectro visible es aquel en el que la longitud de la onda está comprendida entre los 380 y los 770 nanómetros ya que el ojo humano sólo es capaz de percibir ese tipo de luz.

![](https://www.fotonostra.com/grafico/fotos/teoriacolor1.jpg)

Gracias a las propiedades de la luz los objetos devuelven los rayos que no absorben hacia su entorno. Nuestro cerebro interpreta esas radiaciones electromagnéticas que los objetos reflejan como lo que llamamos Color.

### Como son percibidos los colores de los objetos<sup>[2](#referencias)<sup>
*Somos capaces de ver colores gracias a dos de las propiedades de la luz. La absorción y la reflexión.*

Un cuerpo opaco, es decir no transparente, absorbe gran parte de la luz que lo ilumina y refleja una parte más o menos pequeña. Cuando este cuerpo absorbe todos los colores contenidos en la luz blanca, el objeto parece negro.

Cuando refleja todos los colores del espectro, el objeto parece blanco. Los colores absorbidos desaparecen en el interior del objeto, los reflejados llegan al ojo humano. Los colores que visualizamos son, por tanto, aquellos que los propios objetos no absorben, sino que los propagan.

#### Absorción y reflexión

![](https://www.fotonostra.com/grafico/fotos/reflexion.jpg)

Todos los cuerpos están constituidos por sustancias que absorben y reflejan las ondas electromagnéticas, es decir, absorben y reflejan colores.

Cuando un cuerpo se ve blanco es porque recibe todos los colores básicos del espectro (rojo, verde y azul) los devuelve reflejados, generándose así la mezcla de los tres colores, el blanco.

Si el objeto se ve negro es porque absorbe todas las radiaciones electromagnéticas (todos los colores) y no refleja ninguno.

![](https://www.fotonostra.com/grafico/fotos/absorcionrojo.jpg)

El tomate nos parece de color rojo, porque el ojo sólo recibe la luz roja reflejada por la hortaliza, absorbe el verde y el azul y refleja solamente el rojo. Un plátano amarillo absorbe el color azul y refleja los colores rojo y verde, los cuales sumados permiten visualizar el color amarillo.

### Colores primarios en la luz

Los colores producidos por la luz (Los de un monitor de un ordenador, en el cine, televisión, etc. por ejemplo) identifican como colores primarios al rojo, verde y al azul (RGB). Esto se debe a que el ojo humano está compuesto por conos y bastones que son los que nos permiten ver.

Existen tres tipos de conos, cada uno sensible a un tipo de luz. Unos a la luz roja, otros a la luz verde y otra a la azul. La suma de estos tres colores compone la luz blanca. A esta fusión se la denomina Síntesis aditiva y las mezclas parciales de estas luces dan origen a la mayoría de los colores del espectro visible.

### Funcionamiento del sensor
Basándonos en los principios enunciados anteriormente, se plantea un sistema que ilumine una superficie con luz roja, verde y azul, y al mismo tiempo mida la cantidad de luz que es reflejada por la misma. Conociendo la cantidad de luz reflejada de cada color estamos en condiciones de formar digitalmente el color de la superficie que se está observando.

Para poder realizar esto, es necesario que el sensor primero establezca límites para cada color. Esto quiere decir que el sensor debe almacenar los valores que manejará con una superficie blanca y una superficie negra, para luego usarlos de referencia en las mediciones subsiguientes. Estos límites y cómo calcularlos se explican más adelante en los detalles técnicos de funcionamiento.

Una vez que el sensor toma la luz que refleja la superficie para cada color, envía esa información a través del puerto serie, conectado a un módulo bluetooth. Estos valores pueden serán interpretados luego por la aplicación Android que se encuentra en el repositorio, para mostrar de manera gráfica una copia del color de la superficie que se está midiendo.

## Detalles técnicos de funcionamiento
### Componentes a utilizar
* Placa Arduino Uno
* LED RGB
* Fotorresistor
* Módulo Bluetooth HC-06
* Resistor 1K

### Lectura de los valores de color
El fotoresistor es un componente que varía sus resistencia al paso de la corriente eléctrica, en función de la luz que incide sobre él. Si construimos un circuito divisor de tensión con un resistor y el fotorresistor, podemos leer la tensión de salida del mismo con alguno de los pines *analog in* de la placa Arduino.

(IMAGEN DE DIVISOR DE TENSIÓN)

Dado que la resistencia del fotoresistor será variable a lo largo del tiempo, el valor leído en el pin *analog in* de la arduino será también variable, y estará comprendido entre 0 y 1023 (resolución analógica de la Arduino Uno). 

La idea entonces será ubicar el diodo LED RGB y el fotorresistor dentro de una "tapa" negra, con la cual se pueda tapar la superficie de la cual se desea conocer el color. 

(IMAGEN DE LA TAPA)

El diodo LED RGB se irá prendiendo de a un color a la vez. Con cada color que se prende, se leerá analógicamente el valor en el pin *analog in* de la placa Arduino UNO. Dado que el diodo LED y el fotorresistor se encuentran dentro  de la "tapa", parte de la luz que se emite se reflejará en la superficie, mientras que el resto rebotará y modificará la resistencia del fotorresistor. Podemos decir, para simplificar la explicación, que con el fotorresistor *leemos la cantidad de luz reflejada por la superficie*. 

Supongamos un caso práctico en el que tapamos una superficie amarilla. El color amarillo, en la luz, se forma con un 100% de reflexión de luz verde y roja. Al tapar la superficie, encendemos el color rojo del diodo LED RGB. Como la superficie es amarilla, la luz roja emitida por el diodo LED se reflejará en un 100% (esto se da en la teoría, suponiendo componentes ideales que no presentan error, y una superficie amarilla pura), por lo que en el pin *analog in* estaremos *leyendo una gran cantidad de luz reflejada*. Lo mismo sucederá cuando se encienda la luz verde del diodo LED RGB, ya que el 100% de la luz verde será reflejada. El caso contrario se presenta cuando encendemos la luz azul del diodo. Ya que la superficie es amarilla, la misma absorbe por completo la luz azul, haciendo que el fotorresistor *no lea luz reflejada*. Con esos tres valores que representan la *cantidad de luz reflejada de cada color*, estamos en condiciones de saber, combinando las tres magnitudes, qué color es el presente en la superficie.


# Referencias

* [1] [FotoNostra - Teoría del color ¿Qué es el color?](https://www.fotonostra.com/grafico/coloresobjetos.htm)
* [2] [FotoNostra - Como son percibidos los colores de los objetos](https://www.fotonostra.com/grafico/coloresobjetos.htm)