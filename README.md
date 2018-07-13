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

#Referencias

* [1] [FotoNostra - Teoría del color ¿Qué es el color?](https://www.fotonostra.com/grafico/coloresobjetos.htm)
* [2] [FotoNostra - Como son percibidos los colores de los objetos](https://www.fotonostra.com/grafico/coloresobjetos.htm)