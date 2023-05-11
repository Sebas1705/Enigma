# Enigma

Proyecto para la práctica 1 de la asignatura de Computación de Altas Prestaciones,
el proyecto se basa en la optimización de un algoritmo basado en la maquina de encriptación
enigma. En este caso nos centraremos en la parte de desencriptación, para ello se nos proporciono 
un código base situado en el directorio "Version_original" donde el algoritmo ya fue preparado
para la ejecución de pruebas. Para optimizar el código original se tuvo que usar MPI como tecnología 
de paso de mensajes para procesos con memoria distribuidas.

## Instalación:

Para instalar el proyecto simplemente hay que descargar el zip del proyecto y descomprimirlo, en caso de tener
permisos simplemente vale con hacer un clone en tu máquina.

También tendras que tener instalado MPI y Make:
```
  $ sudo apt-get install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi1.3 libopenmpi-dbg libopenmpi-dev;
  $ sudo apt-get install make;
```
## Ejecución:

Para ejecutaar el código de prueba simplemente en la raiz del proyecto tienes que usar el comando:

```
  $ make
```

En caso de querer ejecutar cada versión por separados te mueves a cada carpeta y ejecutas el mismo comando dentro de ellas.
